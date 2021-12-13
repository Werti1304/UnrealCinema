// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpNRunStartingPost.h"

// Sets default values
AJumpNRunStartingPost::AJumpNRunStartingPost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	
}

// Called when the game starts or when spawned
void AJumpNRunStartingPost::BeginPlay()
{

	Super::BeginPlay();
	
}

// Called every frame
void AJumpNRunStartingPost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

