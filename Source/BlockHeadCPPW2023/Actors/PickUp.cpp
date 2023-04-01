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
	PrimaryActorTick.bCanEverTick = true;

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

// Called every frame
void APickUp::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void APickUp::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);
	const FLinearColor LightColor = PointLight->GetLightColor();

	if (PickupFX) {
		PickupFX->SetVariableLinearColor(FName{"Pickup Color"}, LightColor);
	}

	if (!DynamicMaterial) {
		DynamicMaterial = Cube->CreateAndSetMaterialInstanceDynamic(0);
	}

	if (DynamicMaterial) {
		DynamicMaterial->SetVectorParameterValue(FName{"Base Color"}, LightColor);
	}
}

void APickUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                             const FHitResult& SweepResult) {
	if (OtherActor && OtherActor->IsA(APlayerCharacter::StaticClass())) {
		GLUTTON_LOG(PREP("PickUp::OnBeginOverlap: %s", *OtherActor->GetName()));
		ScoreChanged.Broadcast(ScoreValue);
		Destroy();
	}
}
