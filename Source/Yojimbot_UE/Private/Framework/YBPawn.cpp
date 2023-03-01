// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/YBPawn.h"

// Sets default values
AYBPawn::AYBPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AYBPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYBPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AYBPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

