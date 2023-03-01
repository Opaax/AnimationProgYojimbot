// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/YBCharacter.h"

// Sets default values
AYBCharacter::AYBCharacter(const FObjectInitializer& ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AYBCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYBCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AYBCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

