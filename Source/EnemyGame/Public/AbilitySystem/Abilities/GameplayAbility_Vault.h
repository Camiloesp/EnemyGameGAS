// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/EG_GameplayAbility.h"
#include "GameplayAbility_Vault.generated.h"

class UAbilityTask_PlayMontageAndWait;
/**
 * 
 */
UCLASS()
class ENEMYGAME_API UGameplayAbility_Vault : public UEG_GameplayAbility
{
	GENERATED_BODY()
	

public:

	UGameplayAbility_Vault();

	/** The last chance to fail before committing, this will usually be the same as CanActivateAbility. Some abilities may need to do extra checks here if they are consuming extra stuff in CommitExecute */
	virtual bool CommitCheck( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr ) override;

	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData ) override;

	/** Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server */
	virtual void EndAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled ) override;

protected:

	UPROPERTY( EditDefaultsOnly, Category = "Trace|HorizontalTrace" )
	float HorizontalTraceRadius = 30.f;
	UPROPERTY( EditDefaultsOnly, Category = "Trace|HorizontalTrace" )
	float HorizontalTraceLength = 500.f;
	UPROPERTY( EditDefaultsOnly, Category = "Trace|HorizontalTrace" )
	float HorizontalTraceCount = 5.f;
	UPROPERTY( EditDefaultsOnly, Category = "Trace|HorizontalTrace" )
	float HorizontalTraceStep = 30.f;

	UPROPERTY( EditDefaultsOnly, Category = "Trace|VerticalTrace" )
	float VerticalTraceRadius = 30.f;
	///UPROPERTY( EditDefaultsOnly, Category = "Trace|VerticalTrace" )
	///float VerticalTraceLength = 500.f;
	///UPROPERTY( EditDefaultsOnly, Category = "Trace|VerticalTrace" )
	///float VerticalTraceCount = 5.f;
	UPROPERTY( EditDefaultsOnly, Category = "Trace|VerticalTrace" )
	float VerticalTraceStep = 30.f;

	UPROPERTY( EditDefaultsOnly )
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	UPROPERTY( EditDefaultsOnly )
	UAnimMontage* VaultMontage = nullptr;

	UPROPERTY()
	UAbilityTask_PlayMontageAndWait* MontageTask = nullptr;

	FVector JumpToLocation;
	FVector JumpOverLocation;

	UPROPERTY( EditDefaultsOnly )
	TArray<TEnumAsByte<ECollisionChannel>> CollisionChannelsToIgnore;

private:



};
