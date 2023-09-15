// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "EG_GameplayAbility.generated.h"

class APlayerCharacter;
/**
 * 
 */
UCLASS()
class ENEMYGAME_API UEG_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData ) override;

	/** Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server */
	virtual void EndAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled ) override;

protected:

	UPROPERTY( EditDefaultsOnly, Category = "Ability|Effects")
	TArray<TSubclassOf<UGameplayEffect>> OngoingEffectsToRemoveOnEnd;
	UPROPERTY( EditDefaultsOnly, Category = "Ability|Effects" )
	TArray<TSubclassOf<UGameplayEffect>> OngoingEffectsToJustApplyOnStart;

	TArray<FActiveGameplayEffectHandle> RemoveOnEndEffectHandles;

	UFUNCTION( BlueprintCallable, BlueprintPure )
	APlayerCharacter* GetActionGameCharacterFromActorInfo() const;
private:

public:

};
