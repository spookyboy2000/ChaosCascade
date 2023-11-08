#include "Player1.h"

#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

// Sets default values
APlayer1::APlayer1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NewMoveSpeed = MoveSpeed;
	
	Timer = ShootingSpeed;
	
	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Location"));
}

// Called when the game starts or when spawned
void APlayer1::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}

	
}

// Called every frame
void APlayer1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer += DeltaTime;
	
}

// Called to bind functionality to input
void APlayer1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &APlayer1::Shoot);
		EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &APlayer1::StartDrag);
		EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &APlayer1::StopDrag);
	}
	
	PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &APlayer1::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayer1::MoveRight);
}

void APlayer1::StartDrag(const FInputActionValue& Value)
{
	NewMoveSpeed = MoveSpeed * 0.5f;
}

void APlayer1::StopDrag(const FInputActionValue& Value)
{
	NewMoveSpeed = MoveSpeed;
}

void APlayer1::Shoot(const FInputActionValue& Value)
{
	bool ShootPressed = Value.Get<bool>();

	FVector Location = GetActorLocation();
	Location = FVector (Location.X + LocationXFloat, Location.Y + LocationYFloat, Location.Z);
	
	if (ShootPressed == true)
	{

		if (Timer >= ShootingSpeed)
		{
			Timer = 0;
			FActorSpawnParameters SpawnParams;
			AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location, GetActorRotation(), SpawnParams);
		}
	}
	
}

void APlayer1::MoveUp(float Value)
{
	
	NewLocation = GetActorLocation() + FVector(Value * NewMoveSpeed * GetWorld()->GetDeltaSeconds(), 0.0f, 0.0f);	
	
	NewLocation.X = FMath::Clamp(NewLocation.X, MinBoundary.X, MaxBoundary.X);

	SetActorLocation(NewLocation)
	
}

void APlayer1::MoveRight(float Value)
{
	
	NewLocation = GetActorLocation() + FVector(0.0f,Value * NewMoveSpeed * GetWorld()->GetDeltaSeconds(), 0.0f);	
	
	NewLocation.Y = FMath::Clamp(NewLocation.Y, MinBoundary.Y, MaxBoundary.Y);

	SetActorLocation(NewLocation);
	
}
