// Fill out your copyright notice in the Description page of Project Settings.

#include "Street.h"
#include "JSRCharacterMovementComponent.h"
#include "JSRCharacter.h"


// Sets default values
AJSRCharacter::AJSRCharacter(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer.SetDefaultSubobjectClass<UJSRCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AJSRCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Init JSR Character"));
	
}

// Called every frame
void AJSRCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (!GetCharacterMovement()) {
		UE_LOG(LogTemp, Warning, TEXT("NULL MOVEMENT COMP"));
	} 
	else {
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *CharacterMovement->GetFullName());
	}
}

// Called to bind functionality to input
void AJSRCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

