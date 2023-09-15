// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GameplayAbility_Crouch.h"
#include "GameFramework/Character.h"

UGameplayAbility_Crouch::UGameplayAbility_Crouch()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool UGameplayAbility_Crouch::CanActivateAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags ) const
{
	if ( !Super::CanActivateAbility( Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags ))
	{
		return false;
	}

	const ACharacter* Character = CastChecked< ACharacter >( ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed );
	return Character->CanCrouch();
}

void UGameplayAbility_Crouch::ActivateAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData )
{
	Super::ActivateAbility( Handle, ActorInfo, ActivationInfo, TriggerEventData );

	ACharacter* Character = CastChecked< ACharacter >( ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed );
	Character->Crouch();
}

void UGameplayAbility_Crouch::EndAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled )
{
	ACharacter* Character = CastChecked< ACharacter >( ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed );
	Character->UnCrouch();

	Super::EndAbility( Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled );
}
