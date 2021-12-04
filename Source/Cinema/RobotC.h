// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RobotC.generated.h"

UCLASS()
class CINEMA_API ARobotC : public AActor
{
	GENERATED_BODY()

private:
	FName Robot = "Robot";
	
public:	

	UPROPERTY(EditAnywhere, Category = Robot)
	class UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere, Category = Robot)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = Robot)
  class USceneComponent* HomingComponent;

	UPROPERTY(VisibleAnywhere, Category = Robot)
	class APawn* player;

	//UPROPERTY(EditAnywhere, Category = Robot)
	//class UStaticMeshComponent* VisualMesh3;

	// Sets default values for this actor's properties
	ARobotC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
