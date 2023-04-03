// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Obstacle.h"
#include "EndPoint.h"
#include "Kismet/GameplayStatics.h"
#include "../Game/BlockHeadGameMode.h"
#include "../GluttonTools.h"

using UEILPS = UEnhancedInputLocalPlayerSubsystem;
using UEIC = UEnhancedInputComponent;

// Sets default values
APlayerCharacter::APlayerCharacter() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetSimulatePhysics(true);
	Cube->SetNotifyRigidBodyCollision(true);
	RootComponent = Cube;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Cube);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay() {
	Super::BeginPlay();

	GameMode = Cast<ABlockHeadGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		if (UEILPS* SubSystem = ULocalPlayer::GetSubsystem<UEILPS>(LocalPlayer)) {
			if (InputMappingContext) {
				SubSystem->AddMappingContext(InputMappingContext, 0);
			} else {
				GLUTTON_LOG("No Mapping Context Selected in Blueprint.");
			}
		}
	}

	if (Cube) {
		GLUTTON_LOG("Setting up on component hit event!");
		Cube->OnComponentHit.AddDynamic(this, &APlayerCharacter::OnHit);
		Cube->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
	}
}

void APlayerCharacter::PlayerDied() {
	GLUTTON_LOG("Player Died!");
	bLevelEnded = true;
	Cube->SetPhysicsLinearVelocity(Cube->GetPhysicsLinearVelocity() * 0.5f);
	// Call the game mode game complete (with a false arg)
	// But do so using a timer, such that it triggers after 2 seconds.
	// A timer handle will need to be added to this class (header).
	GetWorldTimerManager().SetTimer(GameCompleteTimerHandle, [this]() { GameMode->GameCompleted(false); }, 2.0f, false);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!bLevelEnded) {
		const FVector CubeForce{ForwardForce, 0.0f, 0.0f};
		Cube->AddForce(CubeForce, NAME_None, true);

		const FVector WorldLocation{GetActorLocation()};
		if (WorldLocation.Z < KillZThreshold) {
			PlayerDied();
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEIC* EnhancedInputComponent = CastChecked<UEIC>(PlayerInputComponent)) {
		if (MoveAction) {
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
			                                   &APlayerCharacter::MoveRightLeft);
		} else {
			GLUTTON_LOG("No Move Action Selected in Blueprint.");
		}
	}
}

void APlayerCharacter::MoveRightLeft(const FInputActionValue& Value) {
	const float MovementAxis = Value.Get<float>();
	GLUTTON_LOG(PRINTF("Movement Axis: %f", MovementAxis));

	if (!bLevelEnded) {
		const FVector CubeForce{0.0f, MovementAxis * SideForce, 0.0f};
		Cube->AddForce(CubeForce, NAME_None, true);
	}
}

void APlayerCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
                             FVector NormalImpulse, const FHitResult& Hit) {
	GLUTTON_LOG("ON HIT");
	if (OtherActor && OtherActor->IsA(AObstacle::StaticClass())) {
		GLUTTON_LOG("ON HIT: OBSTACLE");
		PlayerDied();
	}
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult) {
	if (OtherActor && OtherActor->IsA(AEndPoint::StaticClass())) {
		GLUTTON_LOG("ON OVERLAP: END POINT");
		bLevelEnded = true;
		Cube->SetPhysicsLinearVelocity(Cube->GetPhysicsLinearVelocity() * 0.5f);
		GameMode->LevelCompleted();
	}
}
