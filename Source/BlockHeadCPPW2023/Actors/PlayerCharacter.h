// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

// Forward Declarations:
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class ABlockHeadGameMode;
class UBlockHeadGameInstance;

UCLASS()
class BLOCKHEADCPPW2023_API APlayerCharacter : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void PlayerDied();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Cube;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	void MoveRightLeft(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float ForwardForce = 1900;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SideForce = 1800;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float KillZThreshold = -300.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bLevelEnded = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBlockHeadGameInstance* GameInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABlockHeadGameMode* GameMode;

private:
	// Function to handle hit events:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	           FVector NormalImpulse, const FHitResult& Hit);

	// Function to handle overlap events:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
