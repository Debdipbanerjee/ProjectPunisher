// Fill out your copyright notice in the Description page of Project Settings.


#include "PunisherAnimInstance.h"
#include "Punisher/PunisherCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

void UPunisherAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (PunisherCharacter == nullptr)
	{
		PunisherCharacter = Cast<APunisherCharacter>(TryGetPawnOwner());
	}

	if (PunisherCharacter)
	{
		// get lateral speed of character from velocity
		FVector Velocity = PunisherCharacter->GetVelocity();
		Velocity.Z = 0;

		Speed = Velocity.Size();

		// is character in the air
		bIsInAir = PunisherCharacter->GetCharacterMovement()->IsFalling();

		// is character accelerating
		if (PunisherCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.0f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

	}
}

void UPunisherAnimInstance::NativeInitializeAnimation()
{
	PunisherCharacter = Cast<APunisherCharacter>(TryGetPawnOwner());
}
