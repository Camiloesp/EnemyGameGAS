// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/EG_GameplayAbility.h"
#include "GameplayAbility_Jump.generated.h"

class UGameplayEffect;
/**
 * 
 */
UCLASS()
class ENEMYGAME_API UGameplayAbility_Jump : public UEG_GameplayAbility
{
	GENERATED_BODY()

public:

	UGameplayAbility_Jump();

	/** Returns true if this ability can be activated right now. Has no side effects */
	virtual bool CanActivateAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr ) const override;

	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData ) override;

protected:

private:


};
