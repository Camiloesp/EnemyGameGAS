// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GameplayAbility_Jump.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"

UGameplayAbility_Jump::UGameplayAbility_Jump()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
}

bool UGameplayAbility_Jump::CanActivateAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags ) const
{
	if (!Super::CanActivateAbility( Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags ))
	{
		return false;
	}

	const ACharacter* Character = CastChecked<ACharacter>( ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed );
	return Character->CanJump();
}

void UGameplayAbility_Jump::ActivateAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData )
{
	/*
	* Code taken from the already existing ability UGameplayAbility_CharacterJump::ActivateAbility()
	*/
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			return;
		}

		Super::ActivateAbility( Handle, ActorInfo, ActivationInfo, TriggerEventData );

		// Perform ability
		ACharacter* Character = CastChecked<ACharacter>( ActorInfo->AvatarActor.Get());
		Character->Jump();

		/*
		// Apply jump effects using our effect: JumpEffect
		if (UAbilitySystemComponent* AbilityComponent = ActorInfo->AbilitySystemComponent.Get())
		{
			FGameplayEffectContextHandle EffectContext = AbilityComponent->MakeEffectContext(); 

			FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec( JumpEffect, 1, EffectContext );
			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilityComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				if (!ActiveGEHandle.WasSuccessfullyApplied())
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to apply jump effect!! %s"), *GetNameSafe(Character));
				}
			}
		}*/
	}
}
