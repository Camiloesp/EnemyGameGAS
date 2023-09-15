// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/EG_GameplayAbility.h"
#include "GameplayAbility_Crouch.generated.h"

/**
 * 
 */
UCLASS()
class ENEMYGAME_API UGameplayAbility_Crouch : public UEG_GameplayAbility
{
	GENERATED_BODY()
	
public:

	UGameplayAbility_Crouch();

	/** Returns true if this ability can be activated right now. Has no side effects */
	virtual bool CanActivateAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr ) const override;

	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData ) override;

	/** Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server */
	virtual void EndAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled ) override;

	
};
