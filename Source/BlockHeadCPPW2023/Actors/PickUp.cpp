// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "PlayerCharacter.h"
#include "../DebugHelper.h"
#include "NiagaraComponent.h"
#include "Components/PointLightComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
APickUp::APickUp() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLight->SetupAttachment(Cube);
	PickupFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraSystem"));
	PickupFX->SetupAttachment(Cube);
	RootComponent = Cube;
}

// Called when the game starts or when spawned
void APickUp::BeginPlay() {
	Super::BeginPlay();

	if (Cube) {
		Cube->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnBeginOverlap);
	}
}

// Will re-run when Point Light color is changed for instances.
// Syncs the color of the cube and the particle system to the point light color.
// Point Light color isn't available until now (0,0,0,0) in constructor.
// Dynamic material can't be created/set until now also.
void APickUp::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);
	const FLinearColor LightColor = PointLight->GetLightColor();

	if (PickupFX) {
		// Niagara system must have user parameter named "Pickup Color"
		PickupFX->SetVariableLinearColor(FName{"Pickup Color"}, LightColor);
	}

	if (!DynamicMaterial) {
		DynamicMaterial = Cube->CreateAndSetMaterialInstanceDynamic(0);
	}

	if (DynamicMaterial) {
		// Material Instance for Cube must have a vector parameter named "Base Color"
		DynamicMaterial->SetVectorParameterValue(FName{"Base Color"}, LightColor);
	}
}

void APickUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                             const FHitResult& SweepResult) {
	if (OtherActor && OtherActor->IsA(APlayerCharacter::StaticClass())) {
		ScoreChanged.Broadcast(ScoreValue);
		Destroy();
	}
}
