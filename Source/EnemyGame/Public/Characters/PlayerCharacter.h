// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

/* Gas includes */
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemInterface.h"

#include "EnemyGameTypes.h"

#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputActions;
class UInputMappingContext;

/* Gas definitions */
class UAbilitySystemComponentBase;
class UAttributeSetBase;
class UGameplayEffect;
class UGameplayAbility; // do we need? its already included.

class UCharacterDataAsset;
class UEG_MotionWarpingComponent;
class UFootstepsComponent;
class UEG_CharacterMovementComponent;

UCLASS()
class ENEMYGAME_API APlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter( const FObjectInitializer& ObjectInitializer );


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	/* APlayerCharacter */

public:

	// GAS
	bool ApplyGameplayEffectToSelf( TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext );

	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void OnRep_CharacterData();

	virtual void InitFromCharacterData( const FCharacterData& InCharacterData, bool bFromReplication = false );

	UPROPERTY( EditDefaultsOnly, Category = "Player|GAS" )
	UCharacterDataAsset* CharacterDataAsset;

	void OnMaxMovementSpeedChanged( const FOnAttributeChangeData& Data );

protected:

	virtual void PossessedBy( AController* NewController ) override;
	virtual void OnRep_PlayerState() override;

	virtual void OnStartCrouch( float HalfHeightAdjust, float ScaledHalfHeightAdjust ) override;
	virtual void OnEndCrouch( float HalfHeightAdjust, float ScaledHalfHeightAdjust ) override;

	// GAS
	void GiveAbilities();
	void ApplyStartupEffects();

	UPROPERTY( EditDefaultsOnly )
	UAbilitySystemComponentBase* AbilitySystemComponent;
	UPROPERTY( Transient )
	UAttributeSetBase* AttributeSet;

	UPROPERTY( ReplicatedUsing = OnRep_CharacterData )
	FCharacterData CharacterData;

	UPROPERTY( EditDefaultsOnly, Category = "Player|GAS" )
	FGameplayTag JumpEventTag;

	UPROPERTY( EditDefaultsOnly, Category = "Player|GAS" )
	FGameplayTagContainer InAirTags;
	UPROPERTY( EditDefaultsOnly, Category = "Player|GAS" )
	FGameplayTagContainer CrouchTags;
	UPROPERTY( EditDefaultsOnly, Category = "Player|GAS" )
	FGameplayTagContainer SprintTags;

	UPROPERTY( EditDefaultsOnly, Category = "Player|GAS" )
	TSubclassOf<UGameplayEffect> CrouchStateEffect;

	FDelegateHandle MaxMovementSpeedChangedDelegateHandle;

	// END GAS

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	UFootstepsComponent* FootstepsComponent;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Player|MotionWarp" )
	UEG_MotionWarpingComponent* EGMotionWarpingComponent;

	UEG_CharacterMovementComponent* EGCharacterMovementComponent;

private:

	/* Variables */

	UPROPERTY( EditDefaultsOnly )
	UCameraComponent* Camera;
	UPROPERTY( EditDefaultsOnly )
	USpringArmComponent* SpringArm;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true") )
	UInputActions* InputActions;

	

	
	/* Functions */

	void Move( const FInputActionValue& Value );
	void Look( const FInputActionValue& Value ); 

	void OnJumpActionStarted( const FInputActionValue& Value );
	void OnJumpActionEnded( const FInputActionValue& Value );

	void OnCrouchActionStarted( const FInputActionValue& Value );
	void OnCrouchActionEnded( const FInputActionValue& Value );

	void OnSprintActionStarted( const FInputActionValue& Value );
	void OnSprintActionEnded( const FInputActionValue& Value );

	virtual void Landed( const FHitResult& Hit ) override;

public: // Setters and getters

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UFUNCTION( BlueprintCallable )
	FCharacterData GetCharacterData() const { return CharacterData; }
	UFUNCTION( BlueprintCallable )
	void SetCharacterData( const FCharacterData& InCharacterData );

	FORCEINLINE UFootstepsComponent* GetFootstepsComponent() const { return FootstepsComponent; }
	FORCEINLINE UEG_MotionWarpingComponent* GetEGMotionWarpingComponent() const { return EGMotionWarpingComponent; }
};
