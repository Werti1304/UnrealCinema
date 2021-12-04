// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotC.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ARobotC::ARobotC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	HomingComponent = CreateDefaultSubobject<USceneComponent>("Homing Component");
	//VisualMesh3 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh3");

	player = CreateDefaultSubobject<APawn>("Player");

	SetRootComponent(VisualMesh);

	ProjectileMovement->bIsHomingProjectile = true;
	ProjectileMovement->HomingAccelerationMagnitude = 10000;
	ProjectileMovement->HomingTargetComponent = HomingComponent;
	ProjectileMovement->MaxSpeed = 250;

}

// Called when the game starts or when spawned
void ARobotC::BeginPlay()
{
	Super::BeginPlay();

	// Set player who is being followed
	player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

FVector PlayerLocation;

// Called every frame
void ARobotC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (player->IsValidLowLevelFast())
	{
		HomingComponent->SetWorldLocation(player->GetTargetLocation());
	}
}

