#pragma once

#include "CoreMinimal.h"
#include "../Framework/YBCharacter.h"
#include "InputActionValue.h"
#include "UObject/ObjectMacros.h"
#include "YBCharacterState.h"
#include "YBPlayerCharacter.generated.h"

class UYBPlayerCharacterMovementComp;
class AYBWeaponBase;

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UAnimInstance;
class UAnimMontage;
class UYBComboComponent;

/**
 * 
 */
UCLASS()
class YOJIMBOT_UE_API AYBPlayerCharacter : public AYBCharacter
{
	GENERATED_BODY()

protected:
	////////////////// STATE //////////////////

	UPROPERTY(BlueprintGetter = GetCurrentState, BlueprintSetter = SetCurrentSate)
	ECharacterState m_characterState = ECharacterState::ECS_Unarmed;

	UPROPERTY(BlueprintGetter = GetCurrentActionState, BlueprintSetter = SetCurrentActionSate)
	ECharacterActionState m_characterActionState = ECharacterActionState::ECAS_Unoccupied;
	///////////////// END STATE ///////////////

	/// //////////// WEAPONS //////////////

	UPROPERTY(VisibleInstanceOnly, Category = RunTime)
	bool bIsWeaponOnHand = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapons, meta = (AllowPrivateAccess = "true"))
	AYBWeaponBase* m_weapon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapons, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AYBWeaponBase> m_weaponClassToSpawn = nullptr;
	/////////////// END WEAPON ///////////////

	////////////// MOVEMENT /////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UYBPlayerCharacterMovementComp* m_playerMovementComp = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement, meta = (DisplayName = "NormalSpeed", AllowPrivateAccess = "true"))
	float m_normalSpeed = 400.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement, meta = (DisplayName = "OneHandSwordSpeed", AllowPrivateAccess = "true"))
	float m_oneHandSwordSpeed = 500.f;
	///////////// END MOVEMENT /////////////

	///////////// COMBO /////////////
	UPROPERTY(EditAnywhere, Category = Combo, meta = (DisplayName = "ComboComponent"))
	TObjectPtr<UYBComboComponent> m_comboComp;
	//////////// END COMBO //////////

	////////////// ANIMATION /////////////////

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetUseRootMotion, Category = "Animation/Settings")
	bool bUseRootMotion = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, BlueprintGetter = GetInputDirection, Category = "Input")
	FVector2D m_inputDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation", meta = (DisplayName = "AnimInstanceRef"))
	UAnimInstance* m_animInstance = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation/Montages", meta = (DisplayName = "AttackMontage"))
	UAnimMontage* m_attackMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation/Montages", meta = (DisplayName = "EquipMontage"))
	UAnimMontage* m_equipMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation/SocketNames", meta = (AllowPrivateAccess = "true", DisplayName = "NameSocketScabber"))
	FName m_nameSocketScabber = "";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation/SocketNames", meta = (AllowPrivateAccess = "true", DisplayName = "NameSocketOneSwordHand"))
	FName m_nameSocketOneSwordHand = "";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	bool bShouldRotateToControllerDirectionBeforeAttacking = false;
	////////////// END ANIMATION /////////////////

	////////////// CAMERA /////////////////

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	////////////// END CAMERA /////////////////

	////////////// INPUT /////////////////

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	/** MappingContext */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true", DisplayName = "OneHandSwordMappingContext"))
	UInputMappingContext* m_oneHandSwordMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true", DisplayName = "EquipWeaponAction"))
	UInputAction* m_equipWeaponAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true", DisplayName = "PrimaryAttack"))
	UInputAction* m_primaryAttackAction;
	////////////// END INPUT /////////////////
public:

	AYBPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void EquipOneHandWeapon();

	UFUNCTION(BlueprintCallable)
	void OnAttackCollisionEnableDetected();

	UFUNCTION(BlueprintCallable)
	void OnAttackCollisionDisableDetected();

	UFUNCTION()
	void OnComboStopDetected();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for equip the weapon on the hand of the character*/
	UFUNCTION()
	void EquipWeapon(const FInputActionValue& Value);

	UFUNCTION()
	void PrimaryAttack(const FInputActionValue& Value);

	/** Take the weapon from Scabbard*/
	UFUNCTION()
	void TakeWeaponOnHand();

	/** return the weapon to Scabbard*/
	UFUNCTION()
	void StoreWeaponInScabbard();

	UFUNCTION()
	void SpawnDefaultWeapon();

	UFUNCTION()
	void GetAnimInstanceFromMesh();

	UFUNCTION()
	bool CanAttack();

	UFUNCTION()
	bool CanEquipWeapon();

	//////////////// GETTER SETTER //////////////////////
public:
	/** Returns CameraBoom subobject **/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** Returns Character State*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE ECharacterState GetCurrentState() const { return m_characterState; }

	/** Returns Character Action State*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE ECharacterActionState GetCurrentActionState() const { return m_characterActionState; }

	/** Return if use root motion*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE bool GetUseRootMotion() const { return bUseRootMotion; }

	/** return input direction*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE FVector2D GetInputDirection() const { return m_inputDirection; }

	/** Set Character State*/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetCurrentSate(ECharacterState NextState) { m_characterState = NextState; }

	/** Set Character Action State*/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetCurrentActionSate(ECharacterActionState NextState) { m_characterActionState = NextState; }


////////// OVERRIDES ////////////
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

public:

	virtual bool CanJumpInternal_Implementation() const override;
};
