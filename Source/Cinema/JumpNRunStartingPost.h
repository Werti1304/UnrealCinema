// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpNRunStartingPost.generated.h"

UCLASS()
class CINEMA_API AJumpNRunStartingPost : public AActor
{
	GENERATED_BODY()

	FName StartingPost = "Starting Post";

public:	
	// Sets default values for this actor's properties
	AJumpNRunStartingPost();

	UPROPERTY(EditAnywhere, Category = StartingPost)
		UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere, Category = StartingPost)
		FString jumpGroup = "DefaultJumpGroup";

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
