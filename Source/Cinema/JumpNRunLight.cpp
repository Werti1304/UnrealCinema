// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpNRunLight.h"

#include "EngineUtils.h"
#include "JumpingPlatform.h"
#include "Components/SpotLightComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AJumpNRunLight::AJumpNRunLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>("Shell");
	Light = CreateDefaultSubobject<USpotLightComponent>("Light");
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("Particles");

	SetRootComponent(VisualMesh);

	VisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	NearestPlatform.Value = MAX_flt;

	targetLocation = this->GetActorLocation();
}

// Called when the game starts or when spawned
void AJumpNRunLight::BeginPlay()
{
	Super::BeginPlay();

	int platformCount = 0;

	// Iterate over all jumping platform actors
	for (TActorIterator<AJumpingPlatform> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		const AJumpingPlatform* tempPlatform = *ActorItr;
		platformCount++;
		if (tempPlatform->jumpGroup == jumpGroup)
		{
			// Follow iterator object to my actual actor pointer
			JumpingPlatforms.Add(*ActorItr);
		}
	}
	if (JumpingPlatforms.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No suitable Jumping Platform Actor(s) Found. Actors in Level: %d"), platformCount++);
		return;
	}

	int startingActorCount = 0;
	// Iterate over all jumping platform actors
	for (TActorIterator<AJumpNRunStartingPost> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		startingActorCount++;
		if (*ActorItr->jumpGroup == jumpGroup)
		{
			// Follow iterator object to my actual actor pointer
			StartingPost = *ActorItr;
			break;
		}
	}
	if (StartingPost == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No suitable Starting Post Actor Found. Actors in Level: %d"), startingActorCount);
		return;
	}

	ResetGameplay();

	//Finished();
}

// Called every frame
void AJumpNRunLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  const FVector cLocation = this->GetActorLocation();
	if (cLocation != targetLocation)
	{
		const auto newLocation = UKismetMathLibrary::VInterpTo_Constant(cLocation, targetLocation, DeltaTime, speed);
		SetActorLocation(newLocation);
	}
	else if(fin)
	{
		Finished();
	}
}

void AJumpNRunLight::updateNearestPlatform()
{
	if (NearestPlatform.Key == currentPlatform)
	{
		NearestPlatform.Key = nullptr;
		NearestPlatform.Value = FLT_MAX;
	}

	// Go to closest, only has to change when play is moving or idk
	for (const auto jumpingPlatform : tempJumpingPlatforms)
	{
		auto distance = this->GetDistanceTo(jumpingPlatform);

		if (distance < NearestPlatform.Value)
		{
			NearestPlatform.Key = jumpingPlatform;
			NearestPlatform.Value = distance;
		}
	}
}

void AJumpNRunLight::SetCurrentPlatform(AJumpingPlatform* newPlatform)
{
	if(currentPlatform == newPlatform)
	{
		UE_LOG(LogTemp, Error, TEXT("Tried to set the current platform as a new one!"));
		return;
	}

	// Remove Event OnHit from old currentPlatform
	if (currentPlatform)
	{
		currentPlatform->OnActorHit.RemoveAll(this);
	}

  currentPlatform = newPlatform;
	tempJumpingPlatforms.Remove(currentPlatform);
	currentPlatform->OnActorHit.AddDynamic(this, &AJumpNRunLight::OnPlatformHit);
}

void AJumpNRunLight::moveToNextPlatform()
{
	updateNearestPlatform();

	if (NearestPlatform.Key == nullptr) { UE_LOG(LogTemp, Error, TEXT("A Jumping Platform became unavailable / wasn't found!")); }
	else
	{
		SetCurrentPlatform(NearestPlatform.Key);
		targetLocation = NearestPlatform.Key->GetActorLocation() + FVector(0, 0, heightOverPlatform);
	}
}

void AJumpNRunLight::Finished()
{
	fin = false;
	/* Handle to manage the timer */
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AJumpNRunLight::OnFinished, 2.0f, false, 2.0f);
}

void AJumpNRunLight::OnFinished()
{
	ParticleSystem->Activate();
	this->VisualMesh->SetVisibility(false);
	this->Light->SetVisibility(false);

	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AJumpNRunLight::EndAnimationAfterExplosion, 2.0f, false, 2.0f);
}

void AJumpNRunLight::EndAnimationAfterExplosion()
{
	ParticleSystem->Deactivate();

	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AJumpNRunLight::StartOver, 2.0f, false, 5.0f);
}

void AJumpNRunLight::StartOver()
{
	this->VisualMesh->SetVisibility(true);
	this->Light->SetVisibility(true);
}

void AJumpNRunLight::ResetGameplay()
{
	SetActorTickEnabled(false);

	tempJumpingPlatforms = JumpingPlatforms;
	
	if(currentPlatform)
	{
		currentPlatform->OnActorHit.RemoveAll(this);
	}
	currentPlatform = nullptr;
	NearestPlatform.Value = FLT_MAX;
	NearestPlatform.Key = nullptr;

	// Set initial position
	if (StartingPost == nullptr) { UE_LOG(LogTemp, Error, TEXT("Starting Post was deleted or no Starting Post exists!")); }
	else
	{
		targetLocation = StartingPost->GetActorLocation() + FVector(0, 0, heightOverStartingPost);
	}

	SetActorTickEnabled(true);

	StartingPost->OnActorHit.AddDynamic(this, &AJumpNRunLight::OnStartingPoleHit);
}

void AJumpNRunLight::OnPlatformHit(AActor* Actor, AActor* Actor1, FVector Vector, const FHitResult& HitResult)
{
	if(tempJumpingPlatforms.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Moving to next platform %d"), tempJumpingPlatforms.Num());
		moveToNextPlatform();
	}
	else
	{
		fin = true;
		UE_LOG(LogTemp, Warning, TEXT("Resetting to post.. %d"), tempJumpingPlatforms.Num());
		ResetGameplay();
	}
}

void AJumpNRunLight::OnStartingPoleHit(AActor* Actor, AActor* Actor1, FVector Vector, const FHitResult& HitResult)
{
	StartingPost->OnActorHit.RemoveAll(this);
	moveToNextPlatform();
}