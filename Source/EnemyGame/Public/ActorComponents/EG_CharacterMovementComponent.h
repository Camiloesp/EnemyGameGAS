// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EG_CharacterMovementComponent.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
/**
 * 
 */
UCLASS()
class ENEMYGAME_API UEG_CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:

	bool TryTraversal( UAbilitySystemComponent* ASC );

protected:

	// Traversal actions such as Jump, Vault, Wallrun. The action with the lowest index had more priority.
	UPROPERTY( EditDefaultsOnly )
		TArray<TSubclassOf<UGameplayAbility>> TraversalAbilitiesOrdered;

private:


};
