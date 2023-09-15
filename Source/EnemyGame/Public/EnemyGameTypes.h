// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyGameTypes.generated.h"

class UGameplayEffect;
class UGameplayAbility;

class UAnimSequenceBase;
class UBlendSpace;
class UCharacterAnimDataAsset;
/*
* Data driven GAS system
*/
USTRUCT( BlueprintType )
struct FCharacterData
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "Data|Gas" )
	TArray< TSubclassOf<UGameplayEffect> > Effects;

	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "Data|Gas" )
	TArray< TSubclassOf<UGameplayAbility> > Abilities;

	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "Data|Animations" )
	UCharacterAnimDataAsset* CharacterAnimDataAsset;
};

/*
* Data driven Animations
*/

USTRUCT( BlueprintType )
struct FCharacterAnimationData
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY( EditDefaultsOnly )
	UBlendSpace* MovementBlendspace = nullptr;

	UPROPERTY( EditDefaultsOnly )
	UAnimSequenceBase* IdleAnimationAsset = nullptr;// Not UAnimationAsset Or UAnimSequenceBase

	UPROPERTY( EditDefaultsOnly )
	UBlendSpace* CrouchMovementBlendspace = nullptr;

	UPROPERTY( EditDefaultsOnly )
	UAnimSequenceBase* CrouchIdleAnimationAsset = nullptr;
};

UENUM( BlueprintType )
enum class EFoot : uint8
{
	EF_Left		UMETA( DisplayName = "Left" ),
	EF_Right	UMETA( DisplayName = "Right" )
};
