// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIMovementStatus = EAIMovementStatus::AMS_NotMoving;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), "hand_r_weapon");
	// set collision stuff
	Weapon->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Weapon->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Weapon->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Weapon->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
	Health = 100.f;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// initialize max walk speed
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FRotator AAICharacter::ComputeLookAtRotationYaw(AActor* TargetActor)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetActor->GetActorLocation());
	FRotator LookAtRotationYaw(0.f, LookAtRotation.Yaw, 0.f);

	return LookAtRotationYaw;
}

