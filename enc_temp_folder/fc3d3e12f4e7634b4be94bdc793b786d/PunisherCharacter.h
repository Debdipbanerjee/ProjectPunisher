// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PunisherCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class USoundCue;
class UParticleSystem;
class UAnimMontage;

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

	// Rotate controller based on mouse X movement
	void Turn(float Value);

	// Rotate controller based on mouse Y movement
	void LookUp(float Value);

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

	// Turn rate while not aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float HipTurnRate;

	// Look up rate while not aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float HipLookUpRate;

	// Turn rate while aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float AimingTurnRate;

	// Look up rate while aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float AimingLookUpRate;

	/* Mouse */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseHipTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseHipLookUpRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingLookUpRate;


	/* Camera Zoom Settings for Aiming */
	// Default camera field of view value
	float CameraDefaultFOV;

	// Field of view value for when zoomed in
	float CameraZoomedFOV;

	// Current field of view this frame
	float CameraCurrentFOV;

	// Interp speed for zooming while aiming
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float ZoomInterpSpeed;

public:

	// Returns Camera Boom
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Return Follow Camera
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool GetAiming() const { return bAiming; }


protected:

	void CameraInterpZoom(float DeltaTime);
	void SetLookRates();

#pragma endregion

#pragma region Combat

private:

	// Randomized Gunshot sound cue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	USoundCue* FireSound;

	// Flash Spawned at BarrelSocket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* MuzzleFlash;

	// Monatage for firing weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* HipFireMontage;

	// Particles Spawned upon bullet impact
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ImpactParticles;

	// Smoke trails for bullets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* BeamParticles;

	// true when aiming
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bAiming;

	// if the fire button is pressed
	bool bFireButtonPressed;


	// True when we can fire, false when waiting for timer
	bool bShouldFire;


	// Rate of automatic gun fire
	float AutomaticFireRate;

	// Timer for automatic Fire
	FTimerHandle AutoFireTimer;

protected:

	// Called when Fire Button is Pressed
	void FireWeapon();

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation);

	// set bAiming to true or false based on button pressed
	void AimingButtonPressed();
	void AimingButtonReleased();

	void FireButtonPressed();
	void FireButtonReleased();

	void StartFireTimer();

	UFUNCTION()
	void AutoFireReset();

#pragma endregion

};
