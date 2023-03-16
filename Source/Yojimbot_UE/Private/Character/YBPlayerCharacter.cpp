// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/YBPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../../Public/Character/YBPlayerCharacterMovementComp.h"
#include "../../Public/WeaponSystem/YBWeaponBase.h"

#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Kismet/KismetMathLibrary.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "../../Public/Components/YBComboComponent.h"
#include "../../Public/ComboSystem/YBComboState.h"

#include "../../Public/Utils/CustomDebugMacro.h"


AYBPlayerCharacter::AYBPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UYBPlayerCharacterMovementComp>(ACharacter::CharacterMovementComponentName))
{
	//Set the custom movement component
	m_playerMovementComp = Cast<UYBPlayerCharacterMovementComp>(GetCharacterMovement());

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Create A combo component
	m_comboComp = CreateDefaultSubobject<UYBComboComponent>(TEXT("ComboComponent"));
}

void AYBPlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	GetCharacterMovement()->MaxWalkSpeed = m_normalSpeed;

	SpawnDefaultWeapon();
	GetAnimInstanceFromMesh();
}

void AYBPlayerCharacter::SpawnDefaultWeapon()
{
	UWorld* lWorld = GetWorld();

	if (lWorld != nullptr)
	{
		FActorSpawnParameters lParams = FActorSpawnParameters();
		lParams.Owner = this;

		m_weapon = lWorld->SpawnActor<AYBWeaponBase>(m_weaponClassToSpawn, lParams);

		if (m_weapon != nullptr)
		{
			FAttachmentTransformRules lTransRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);

			m_weapon->AttachToComponent(GetMesh(), lTransRules, m_nameSocketScabber);
		}
	}
}

void AYBPlayerCharacter::GetAnimInstanceFromMesh()
{
	if (GetMesh() != nullptr && GetMesh()->GetAnimInstance() != nullptr)
	{
		m_animInstance = GetMesh()->GetAnimInstance();
	}
}

///////////////////////// Combo /////////////////////////////

void AYBPlayerCharacter::OnAttackCollisionEnableDetected()
{
	if (m_weapon != nullptr)
	{
		DEBUG_LOG(TEXT("WeaponColl activate"));
		m_weapon->ActivateAttackCollision();
	}
}

void AYBPlayerCharacter::OnAttackCollisionDisableDetected()
{
	if (m_weapon != nullptr)
	{
		DEBUG_LOG(TEXT("WeaponColl Desactivate"));
		m_weapon->DesactivateAttackCollision();
	}
}

void AYBPlayerCharacter::StartComboAttack()
{
	if (bIsWeaponOnHand && CanAttack())
	{
		if (m_animInstance != nullptr && m_attackMontage != nullptr)
		{
			if (bShouldRotateToControllerDirectionBeforeAttacking)
			{
				const FRotator Rotation = Controller->GetControlRotation();
				const FRotator YawRotation(0, Rotation.Yaw, 0);

				SetActorRotation(YawRotation);
			}


			if (m_comboComp)
			{
				//the component will check by itself which anim on combo to play
				m_comboComp->PlayComboAnimation();

				ListenComboEvents();
			}

			m_characterActionState = ECharacterActionState::ECAS_Attacking;
		}
	}
}

void AYBPlayerCharacter::ListenComboEvents()
{
	if (!m_comboComp->OnComboEnd.IsBound())
		m_comboComp->OnComboEnd.AddDynamic(this, &AYBPlayerCharacter::OnComboEnd);

	if (!m_comboComp->OnComboFinish.IsBound())
		m_comboComp->OnComboFinish.AddDynamic(this, &AYBPlayerCharacter::OnComboEnd);
}

bool AYBPlayerCharacter::CheckComboCompletion()
{
	//if Combo state is on Attack window this mean next input will continue the combo
	if (m_comboComp->GetComboState() == EComboState::ECS_OnAttackWindow)
	{
		if (m_comboComp)
		{
			//the component will check by itself which anim on combo to play
			m_comboComp->PlayComboAnimation();
		}

		//make sure the ActionState is attacking
		m_characterActionState = ECharacterActionState::ECAS_Attacking;

		return true;
	}

	return false;
}

void AYBPlayerCharacter::OnComboEnd()
{
	m_characterActionState = ECharacterActionState::ECAS_Unoccupied;

	StopListeningComboEvent();
}

void AYBPlayerCharacter::OnComboFinish()
{
	m_characterActionState = ECharacterActionState::ECAS_Unoccupied;

	StopListeningComboEvent();
}

void AYBPlayerCharacter::StopListeningComboEvent()
{
	if (!m_comboComp->OnComboEnd.IsBound())
		m_comboComp->OnComboEnd.RemoveDynamic(this, &AYBPlayerCharacter::OnComboEnd);

	if (!m_comboComp->OnComboFinish.IsBound())
		m_comboComp->OnComboFinish.RemoveDynamic(this, &AYBPlayerCharacter::OnComboEnd);
}

///////////////////////// Input /////////////////////////////

void AYBPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//equip/unequip weapon
		EnhancedInputComponent->BindAction(m_equipWeaponAction, ETriggerEvent::Triggered, this, &AYBPlayerCharacter::EquipWeapon);
		EnhancedInputComponent->BindAction(m_primaryAttackAction, ETriggerEvent::Triggered, this, &AYBPlayerCharacter::PrimaryAttack);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AYBPlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AYBPlayerCharacter::Look);

	}
}

void AYBPlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (bUseRootMotion)
	{
		m_inputDirection = MovementVector;

		if (GetCharacterMovement()->Velocity.Length() > 10)
		{

			FRotator lNewRot = UKismetMathLibrary::RInterpTo(GetActorRotation(), GetControlRotation(), GetWorld()->GetDeltaSeconds(), 5);
			lNewRot.Pitch = 0;
			lNewRot.Roll = 0;

			SetActorRotation(lNewRot);
		}
		return;
	}

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AYBPlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

bool AYBPlayerCharacter::CanJumpInternal_Implementation() const
{
	return Super::CanJumpInternal_Implementation() && m_characterActionState != ECharacterActionState::ECAS_Attacking;
}

void AYBPlayerCharacter::EquipWeapon(const FInputActionValue& Value)
{
	// is weapon is on hand store it otherwise take the weapon
	if (bIsWeaponOnHand)
		StoreWeaponInScabbard();
	else
		TakeWeaponOnHand();
}

void AYBPlayerCharacter::PrimaryAttack(const FInputActionValue& Value)
{
	if (!CheckComboCompletion())
	{
		if (m_comboComp->GetComboState() == EComboState::ECS_OnWaiting)
		{
			StartComboAttack();
		}
	}
}

void AYBPlayerCharacter::TakeWeaponOnHand()
{
	if (!bIsWeaponOnHand && CanEquipWeapon())
	{
		if (m_animInstance != nullptr && m_equipMontage != nullptr)
		{
			m_animInstance->Montage_Play(m_equipMontage);
		}
	}
}

void AYBPlayerCharacter::EquipOneHandWeapon()
{
	bIsWeaponOnHand = true;
	m_characterState = ECharacterState::ECS_OneHandWeapon;

	//new speed while holding the weapon
	GetCharacterMovement()->MaxWalkSpeed = m_oneHandSwordSpeed;

	// add battle mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(m_oneHandSwordMappingContext, 1);
		}
	}

	//Setup new transform rules for the weapon
	if (m_weapon != nullptr)
	{
		FAttachmentTransformRules lTransRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, false);

		m_weapon->AttachToComponent(GetMesh(), lTransRules, m_nameSocketOneSwordHand);
	}
}

void AYBPlayerCharacter::StoreWeaponInScabbard()
{
	bIsWeaponOnHand = false;
	m_characterState = ECharacterState::ECS_Unarmed;
	GetCharacterMovement()->MaxWalkSpeed = m_normalSpeed;

	// remove battle mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(m_oneHandSwordMappingContext);
		}
	}

	if (m_weapon != nullptr)
	{
		FAttachmentTransformRules lTransRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, false);

		m_weapon->AttachToComponent(GetMesh(), lTransRules, m_nameSocketScabber);
	}
}

bool AYBPlayerCharacter::CanAttack()
{
	return m_characterActionState == ECharacterActionState::ECAS_Unoccupied && m_characterState == ECharacterState::ECS_OneHandWeapon;
}

bool AYBPlayerCharacter::CanEquipWeapon()
{
	return m_characterActionState == ECharacterActionState::ECAS_Unoccupied && m_characterState == ECharacterState::ECS_Unarmed;
}


