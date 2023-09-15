// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/EG_CharacterMovementComponent.h"

#include "AbilitySystemComponent.h"

static TAutoConsoleVariable<int32> CVarShowTraversal(
	TEXT( "ShowDebugTraversal" ),
	0,
	TEXT( "Draws debug info about traversal" )
	TEXT( " 0: off/n" )
	TEXT( " 1: on/n" ),
	ECVF_Cheat
);

bool UEG_CharacterMovementComponent::TryTraversal( UAbilitySystemComponent* ASC )
{
	for ( TSubclassOf<UGameplayAbility> AbilityClass : TraversalAbilitiesOrdered )
	{
		if ( ASC->TryActivateAbilityByClass(AbilityClass, true) )
		{
			// We need to get the ability spec and check whether the spec here is active.
			// This is important for Vault or another ability because it will perform a specific commit check,
			// which means that when we are going to run it, it will activate, but then it will perform a 
			// commit check and we'll check if the environment is suitable for it to be activated. and if it is, it will run forward.
			FGameplayAbilitySpec* Spec;
			Spec = ASC->FindAbilitySpecFromClass( AbilityClass );
			if ( Spec && Spec->IsActive() )
			{
				return true;
			}
		}
	}

	return false;
}
