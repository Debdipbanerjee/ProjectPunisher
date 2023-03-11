// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PunisherCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class USoundCue;
class UParticleSystem;

UCLASS()
class PUNISHER_API APunisherCharacter : public ACharacter
{
	GENERATED_BODY()

#pragma region Character

public:
	// Sets default values for this character's properties
	APunisherCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Movement Input
	void MoveForward(float Value);

	void MoveRight(float Value);

	// Called via input to turn at a given rate (Normalized)
	void TurnAtRate(float Rate);

	// Called via input to look up down at a given rate (Normalized)
	void LookUpAtRate(float Rate);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma endregion



#pragma region Camera

private:
	// Camera boom Spring arm to hold camera behind the actor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	// Camera to follow the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	// Turn rate Deg/Sec
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	// Base Look Up rate Deg/sec
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

public:

	// Returns Camera Boom
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Return Follow Camera
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

#pragma endregion

#pragma region Combat

private:

	// Randomized Gunshot sound cue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	USoundCue* FireSound;

	// Flash Spawned at BarrelSocket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* MuzzleFlash;

protected:

	// Called when Fire Button is Pressed
	void FireWeapon();

#pragma endregion

};
