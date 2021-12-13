// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpingPlatform.generated.h"

UCLASS()
class CINEMA_API AJumpingPlatform : public AActor
{
	GENERATED_BODY()
	
	FName JumpingPlatform = "Platform";

public:	
	UPROPERTY(EditAnywhere, Category = JumpingPlatform)
		UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditInstanceOnly, Category = JumpingPlatform)
		FString jumpGroup = "DefaultJumpGroup";

	// Sets default values for this actor's properties
	AJumpingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
