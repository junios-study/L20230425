// Fill out your copyright notice in the Description page of Project Settings.


#include "P38Pawn.h"

#include "PropellerComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AP38Pawn::AP38Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_P38_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));
	if (SM_P38_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_P38_Body.Object);
	}

	Left = CreateDefaultSubobject<UPropellerComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);

	Right = CreateDefaultSubobject<UPropellerComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Left->AddLocalOffset(FVector(37.5f, -21.0f, 1.17f));
		Right->SetStaticMesh(SM_Propeller.Object);
		Right->AddLocalOffset(FVector(37.5f, 21.0f, 1.17f));
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);
	SpringArm->TargetArmLength = 150.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);
	Arrow->AddLocalOffset(FVector(100, 0, 0));

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Movement->MaxSpeed = 2000.0f;
}

// Called when the game starts or when spawned
void AP38Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP38Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector());
}

// Called to bind functionality to input
void AP38Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		if (FireAction)
		{
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AP38Pawn::Fire);
		}
		if (PitchRollAction)
		{
			EnhancedInputComponent->BindAction(PitchRollAction, ETriggerEvent::Triggered, this, &AP38Pawn::PitchRoll);
		}
	}

}

void AP38Pawn::Fire(const FInputActionValue& Value)
{
}

void AP38Pawn::PitchRoll(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("PitchRoll"));

	FVector2D Values = Value.Get<FVector2D>();
	FRotator DesireRotation(Values.Y, 0, Values.X);

	AddActorLocalRotation(DesireRotation * 60.0f * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()));
}

