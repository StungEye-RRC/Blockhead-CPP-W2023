// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndPoint.generated.h"

// Forward Declarations:
class UBoxComponent;

UCLASS()
class BLOCKHEADCPPW2023_API AEndPoint : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEndPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Setup)
	UStaticMeshComponent* Plane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Setup)
	UBoxComponent* CollisionBox;
};
