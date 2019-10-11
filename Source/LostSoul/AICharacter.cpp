// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementStatus = EAIMovementStatus::AMS_Idle;
	
	ReachingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ReachingSphere"));
	ReachingSphere->SetupAttachment(RootComponent);
	ReachingSphere->InitSphereRadius(1000.f);

	AttackingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackingSphere"));
	AttackingSphere->SetupAttachment(RootComponent);
	AttackingSphere->InitSphereRadius(125.f);

	EscapingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("EscapingSphere"));
	EscapingSphere->SetupAttachment(RootComponent);
	EscapingSphere->InitSphereRadius(1600.f);
	
	Health = 100.f;
	Speed = 0.f;
	bIsHit = false;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// initialize max walk speed
	GetCharacterMovement()->MaxWalkSpeed = 250.f;

	AttackingDistance = 80.f;
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

