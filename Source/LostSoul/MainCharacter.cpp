// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"
#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up camera and spring arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f; // the default value for spring arm length
	CameraBoom->bUsePawnControlRotation = true; // rotate when the controller rotates

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // since the spring arm already rotates

	// Set up the sword
	Sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword"));
	GetMesh()->GetSocketByName("hand_r");
	Sword->SetupAttachment(GetMesh(), "hand_r");

	// Don't rotate when the controller rotates
	// However, in combat, we want the mesh facing the enemy i.e. we want the mesh rotates with the controller
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Log out the default max walk speed
	//UE_LOG(LogTemp, Warning, TEXT("Max walk speed: %f"), GetCharacterMovement()->MaxWalkSpeed);
}

void AMainCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		// compute current forward direction
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardDirection, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		// compute current right direction
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(RightDirection, Value);
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	// for movement (keyboard inputs)
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	// for camera rotation (mouse inputs)
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput); // controller is a varianble in Pawn class
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}
/*
void AMainCharacter::EquipWeapon()
{
	if (!Weapon) { return; }
	// check if this mesh is static or skeletal
	UStaticMeshComponent* StaticMesh = Weapon->GetStaticMeshComponent();
	if (!StaticMesh)
	{
		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("RightHandWeapon");
		if (!WeaponSocket) { return; }
		WeaponSocket->AttachActor(Weapon, GetMesh());
	}
}
*/