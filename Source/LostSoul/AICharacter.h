// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UENUM(BlueprintType)
enum class EAIMovementStatus : uint8
{
	AMS_Idle          UMETA(DeplayName = "Idle"),
	AMS_MoveToTarget  UMETA(DeplayName = "MoveToTarget"),
	AMS_Attacking     UMETA(DeplayName = "Attacking"),

	AMS_MAX           UMETA(DeplayName = "DefaultMax")
};

UCLASS()
class LOSTSOUL_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAIMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Health;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Speed;

	// Is the AI character currently being hit?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsHit;

	// The accepted distance when AI moves to the character
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AttackingDistance;

public:
	// Sets default values for this character's properties
	AAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void GetHit(float Damage);

	// Compute the current speed
	UFUNCTION(BlueprintCallable)
	void UpdateSpeed();

	//void ReachingSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE float GetHealth() { return Health; }
	FORCEINLINE void SetHealth(float Value) { Health = Value; }

};
