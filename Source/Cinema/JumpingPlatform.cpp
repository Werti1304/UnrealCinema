// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpingPlatform.h"

#include "Particles/ParticleSystemComponent.h"

// Sets default values
AJumpingPlatform::AJumpingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	SetRootComponent(VisualMesh);
}

// Called when the game starts or when spawned
void AJumpingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJumpingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

