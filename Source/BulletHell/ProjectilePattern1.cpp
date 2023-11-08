// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilePattern1.h"

// Sets default values
AProjectilePattern1::AProjectilePattern1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProjectilePattern1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectilePattern1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

