// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

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

	/** Is the character attacking? */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking;

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

	FORCEINLINE bool GetIsAttacking() { return bIsAttacking; }
	FORCEINLINE void SetIsAttacking(bool Value) { bIsAttacking = Value; }
};
