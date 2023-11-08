// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Microsoft/AllowMicrosoftPlatformTypes.h"
#include "InputActionValue.h"
#include "Player1.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class BULLETHELL_API APlayer1 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* PlayerMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ShiftAction;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "SpawnLocation")
	USceneComponent* SpawnLocation;

	//void Shift(const FInputActionValue& Value);
	void StartDrag(const FInputActionValue& Value);
	void StopDrag(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MinBoundary = FVector(-500.0f, -500.0f, 0.0f);	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MaxBoundary = FVector(500.0f, 500.0f, 0.0f);

	//UFUNCTION()
	//void PlayerHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//bool ShootPressed;

	

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float PlayerHealth = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth = 200.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float NewMoveSpeed = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LocationXFloat = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LocationYFloat = 1;
	
	FVector NewLocation; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShootingSpeed = 1;

	float Timer;
	
	void MoveUp(float Value);
	void MoveRight(float Value);

};
