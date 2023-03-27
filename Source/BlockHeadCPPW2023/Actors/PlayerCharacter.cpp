// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Obstacle.h"
#include "EndPoint.h"
#include "Kismet/GameplayStatics.h"
#include "../Game/BlockHeadGameInstance.h"
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
	GameInstance = CastChecked<UBlockHeadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

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

	if (GameInstance) {
		GameInstance->TestMethod();
	}

	if (GameMode) {
		GameMode->TestMethod();
	}
}

void APlayerCharacter::PlayerDied() {
	GLUTTON_LOG("Player Died!");
	bLevelEnded = true;
	Cube->SetPhysicsLinearVelocity({0, 0, 0});
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
	if (OtherActor && OtherActor->IsA(AObstacle::StaticClass())) {
		PlayerDied();
	}
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult) {
	if (OtherActor && OtherActor->IsA(AEndPoint::StaticClass())) {
		GLUTTON_LOG("ON OVERLAP: END POINT");
		bLevelEnded = true;
	}
}


/*
 * - Add two pointer properties to your player character:
 *   - One for a pointer to the game mode.
 *	 - One for a pointer to the game instance.
 * - From the constructor (or maybe beginplay) get a pointer to both of these
 *   things from the Gameplay Statics functions.
 * - Cast those returned pointers to the Blockhead versions of those classes.
 * - Add a simple method to each of your C++ class (game mode and instance)
 *   that include log statements that you can call from your player character for testing.
*/
