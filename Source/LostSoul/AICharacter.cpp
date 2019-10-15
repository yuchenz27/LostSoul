// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementStatus = EAIMovementStatus::AMS_Idle;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), "hand_r_weapon");
	// set collision stuff
	Weapon->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Weapon->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Weapon->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Weapon->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
	Health = 100.f;
	Speed = 0.f;
	bIsHit = false;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// initialize max walk speed
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

}

void AAICharacter::GetHit(float Damage)
{
	bIsHit = true;
	Health -= Damage;
}

void AAICharacter::UpdateSpeed()
{
	FVector CurrentSpeed = GetVelocity();
	FVector LateralSpeed = FVector(CurrentSpeed.X, CurrentSpeed.Y, 0.f);
	Speed = LateralSpeed.Size();
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateSpeed();
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

