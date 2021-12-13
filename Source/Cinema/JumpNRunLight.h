// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpingPlatform.h"
#include "JumpNRunStartingPost.h"

#include "JumpNRunLight.generated.h"


UCLASS()
class CINEMA_API AJumpNRunLight : public AActor
{
	GENERATED_BODY()

	FName JumpNRunLight = "JNRLight";

public:	
	UPROPERTY(EditAnywhere, Category = JumpNRunLight)
		UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere, Category = JumpNRunLight)
		class USpotLightComponent* Light;

	UPROPERTY(EditAnywhere, Category = JumpNRunLight)
		UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditInstanceOnly, Category = JumpNRunLight)
		FString jumpGroup = "DefaultJumpGroup";

	UPROPERTY(EditAnywhere, Category = JumpNRunLight)
		float heightOverPlatform = 100;

	UPROPERTY(EditAnywhere, Category = JumpNRunLight)
		float heightOverStartingPost = 300;

	UPROPERTY(EditAnywhere, Category = JumpNRunLight)
		float speed = 500;

	// Sets default values for this actor's properties
	AJumpNRunLight();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

private:
  TArray<AJumpingPlatform*> JumpingPlatforms;
  TArray<AJumpingPlatform*> tempJumpingPlatforms;
	TPair<AJumpingPlatform*, float> NearestPlatform;
	AJumpingPlatform* currentPlatform;

  AJumpNRunStartingPost* StartingPost;

	FVector targetLocation;

	bool fin = false;

private:
  void ResetGameplay();

  /**
   * @brief Updates nearest platform. Excludes current platform
   */
  void updateNearestPlatform();

  void SetCurrentPlatform(AJumpingPlatform* newPlatform);
  void moveToNextPlatform();


	void Finished();
	FTimerHandle FuzeTimerHandle;
	UFUNCTION()
		void OnFinished();
	UFUNCTION()
		void EndAnimationAfterExplosion();
	UFUNCTION()
		void StartOver();

	UFUNCTION()
	void OnPlatformHit(AActor* Actor, AActor* Actor1, FVector Vector, const FHitResult& HitResult);

  UFUNCTION()
  void OnStartingPoleHit(AActor* Actor, AActor* Actor1, FVector Vector, const FHitResult& HitResult);
};
