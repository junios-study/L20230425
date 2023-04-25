// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

//#include "InputAction.h"

#include "P38Pawn.generated.h"


class UPropellerComponent;
class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class UFloatingPawnMovement;
class UStaticMeshComponent;
struct FInputActionValue;


UCLASS()
class L20230425_API AP38Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AP38Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPropellerComponent* Left;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPropellerComponent* Right;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* PitchRollAction;

	//UFUNCTION(BlueprintImplementableEvent, Category = "Custom Spawn")
	UFUNCTION(BlueprintNativeEvent, Category = "Custom Spawn")
	void PostSpawn();
	void PostSpawn_Implementation();

	//UFUNCTION(Server)
	//void ServerExecute();
	//void ServerExecute_Implementation();

	UFUNCTION(BlueprintCallable, Category = "User Function")
	void BlueprintCall();


	void Fire(const FInputActionValue& Value);

	void PitchRoll(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<class ARocket> Projectile;
};
