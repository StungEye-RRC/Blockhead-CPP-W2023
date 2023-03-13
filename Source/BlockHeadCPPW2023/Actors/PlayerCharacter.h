// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"

// Forward Declarations:
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class BLOCKHEADCPPW2023_API APlayerCharacter : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	UStaticMeshComponent* Cube;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	UCameraComponent* Camera;

	// class keyword forward declares so we don't need to include the headers.

	UPROPERTY(EditAnywhere, Category = "Floats")
	float ForwardForce = 2000;

	UPROPERTY(EditAnywhere, Category = "Floats")
	float SideForce = 5;
};
