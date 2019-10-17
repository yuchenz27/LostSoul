// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	MS_Walk          UMETA(DeplayName = "Walk"),
	MS_Run           UMETA(DeplayName = "Run"),
	MS_Sprint        UMETA(DeplayName = "Sprint"),

	MS_MAX           UMETA(DeplayName = "DefaultMax")
};

UCLASS()
class LOSTSOUL_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	/** The spring arm positions the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) // if I don't add this private access shit, I have to make this variable public
	class USpringArmComponent* CameraBoom;

	/** The follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// The sword, which is now attached to the skeletal mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Sword;

	// if I put this variable after bIsAttacking, the game would crash. Don't know why
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AWeapon* Weapon;

	// the combat target
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AAICharacter* CombatTarget;
	
public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// This function is called when there is a forward/backward input
	void MoveForward(float Value);

	// This function is called when there is a right/left input
	void MoveRight(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/*
	UFUNCTION(BlueprintCallable)
	void EquipWeapon();
	*/
};
