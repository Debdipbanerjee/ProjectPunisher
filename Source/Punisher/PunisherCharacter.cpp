// Fill out your copyright notice in the Description page of Project Settings.


#include "PunisherCharacter.h"

#include "Camera/CameraComponent.h"

#include "DrawDebugHelpers.h"

#include "Engine/SkeletalMeshSocket.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Sound/SoundCue.h"


// Sets default values
APunisherCharacter::APunisherCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Camera

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	// Don't rotate when controller rotates
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Confggure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Moves direction of input
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;


}

// Called when the game starts or when spawned
void APunisherCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APunisherCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// WHich way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		AddMovementInput(Direction, Value);

	}
}

void APunisherCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// WHich way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
		AddMovementInput(Direction, Value);

	}
}

void APunisherCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APunisherCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// Called every frame
void APunisherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APunisherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APunisherCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APunisherCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &APunisherCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APunisherCharacter::LookUpAtRate);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("FireButton", IE_Pressed, this, &APunisherCharacter::FireWeapon);
}

void APunisherCharacter::FireWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire"));

	if (FireSound)
	{
		UGameplayStatics::PlaySound2D(this, FireSound);
	}

	const USkeletalMeshSocket* BarrelSocket = GetMesh()->GetSocketByName("BarrelSocket");
	if (BarrelSocket)
	{
		const FTransform SocketTransform = BarrelSocket->GetSocketTransform(GetMesh());

		if (MuzzleFlash)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, SocketTransform);
		}

		FHitResult FireHit;
		const FVector Start{ SocketTransform.GetLocation() };
		const FQuat Rotation{ SocketTransform.GetRotation() };
		const FVector RotationAxis{ Rotation.GetAxisX() };
		const FVector End{ Start + RotationAxis * 50000.0f };

		GetWorld()->LineTraceSingleByChannel(FireHit,Start, End, ECollisionChannel::ECC_Visibility);
		if (FireHit.bBlockingHit)
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 3.0f);
			DrawDebugPoint(GetWorld(), FireHit.Location, 5.0f, FColor::Red, false, 3.0f);

			if (ImpactParticles)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, FireHit.Location);
			}
		}
	}

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && HipFireMontage)
	{
		AnimInstance->Montage_Play(HipFireMontage);
		AnimInstance->Montage_JumpToSection(FName("StartFire"));
	}
}

