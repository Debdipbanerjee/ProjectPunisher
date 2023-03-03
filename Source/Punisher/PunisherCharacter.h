// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PunisherCharacter.generated.h"


class USpringArmComponent; 

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

public:

	// Returns Camera Boom
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

#pragma endregion


};
