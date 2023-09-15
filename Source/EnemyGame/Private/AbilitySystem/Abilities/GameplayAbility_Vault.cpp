// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GameplayAbility_Vault.h"

#include "Characters/PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ActorComponents/EG_MotionWarpingComponent.h"

UGameplayAbility_Vault::UGameplayAbility_Vault()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool UGameplayAbility_Vault::CommitCheck( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags )
{
	if (!Super::CommitCheck( Handle, ActorInfo, ActivationInfo, OptionalRelevantTags ))
	{
		return false;
	}
	
	APlayerCharacter* Character = GetActionGameCharacterFromActorInfo();
	if (!Character) return false;

	const FVector StartLocation = Character->GetActorLocation();
	const FVector ForwardVector = Character->GetActorForwardVector();
	const FVector UpVector = Character->GetActorUpVector();

	TArray<AActor*> ActorsToIgnore = { Character };

	static const auto CVar = IConsoleManager::Get().FindConsoleVariable( TEXT("ShowDebugTraversal") );
	const bool bShowTraversal = CVar->GetInt() > 0;

	EDrawDebugTrace::Type DebugDrawType = bShowTraversal ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

	bool bJumpToLocationSet = false;

	int32 JumpToLocationIdx = INDEX_NONE;

	int i = 0; // Index of the trace

	FHitResult TraceHit;

	float MaxJumpDistance = HorizontalTraceLength;

	for (;i<HorizontalTraceCount; i++)
	{
		const FVector TraceStart = StartLocation + i * UpVector * HorizontalTraceStep;
		const FVector TraceEnd = TraceStart + ForwardVector * HorizontalTraceLength;

		if ( UKismetSystemLibrary::SphereTraceSingleForObjects( this, TraceStart, TraceEnd, HorizontalTraceRadius, TraceObjectTypes, true, ActorsToIgnore, DebugDrawType, TraceHit, true ) )
		{
			if ( JumpToLocationIdx == INDEX_NONE && (i < HorizontalTraceCount - 1) )
			{
				JumpToLocationIdx = i;
				JumpToLocation = TraceHit.Location;
			}
			else if ( JumpToLocationIdx == ( i - 1) )
			{
				MaxJumpDistance = FVector::Dist2D( TraceHit.Location, TraceStart );
				break;
			}
		}
		else
		{
			if (JumpToLocationIdx != INDEX_NONE)
			{
				break;
			}
		}
	}

	if (JumpToLocationIdx == INDEX_NONE)
	{
		return false;
	}

	const float DistanceToJumpTo = FVector::Dist2D( StartLocation, JumpToLocation );
	const float MaxVerticalTraceDistance = MaxJumpDistance - DistanceToJumpTo;

	if (MaxVerticalTraceDistance < 0)
	{
		return false;
	}

	if ( i == HorizontalTraceCount )
	{
		i = HorizontalTraceCount - 1;
	}

	const float VerticalTraceLength = FMath::Abs( JumpToLocation.Z - (StartLocation + i * UpVector * HorizontalTraceStep ).Z);

	// 33:24
	return 1;
}

void UGameplayAbility_Vault::ActivateAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData )
{
	Super::ActivateAbility( Handle, ActorInfo, ActivationInfo, TriggerEventData );
}

void UGameplayAbility_Vault::EndAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled )
{
	Super::EndAbility( Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled );
}
