// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VoxelPawn.generated.h"


// Forward Declarations:
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class BLOCKHEADCPPW2023_API AVoxelPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVoxelPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float ZoomSpeed = 1;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed = 1;

	void Zoom(float axisValue);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
