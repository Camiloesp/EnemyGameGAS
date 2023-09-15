// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/EG_AnimInstance.h"

#include "EnemyGameTypes.h"
#include "DataAssets/CharacterAnimDataAsset.h"
#include "Characters/PlayerCharacter.h"

UBlendSpace* UEG_AnimInstance::GetLocomotionBlendspace() const
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>( GetOwningActor() ))
	{
		FCharacterData Data = PlayerCharacter->GetCharacterData();

		if (Data.CharacterAnimDataAsset)
		{
			return Data.CharacterAnimDataAsset->CharacterAnimationData.MovementBlendspace;
		}
	}

	return DefaultCharacterAnimDataAsset ? DefaultCharacterAnimDataAsset->CharacterAnimationData.MovementBlendspace : nullptr;
}

UAnimSequenceBase* UEG_AnimInstance::GetIdleAnimation() const
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>( GetOwningActor() ))
	{
		FCharacterData Data = PlayerCharacter->GetCharacterData();

		if (Data.CharacterAnimDataAsset)
		{
			return Data.CharacterAnimDataAsset->CharacterAnimationData.IdleAnimationAsset;
		}
	}

	return DefaultCharacterAnimDataAsset ? DefaultCharacterAnimDataAsset->CharacterAnimationData.IdleAnimationAsset : nullptr;
}

UBlendSpace* UEG_AnimInstance::GetCrouchLocomotionBlendspace() const
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>( GetOwningActor() ))
	{
		FCharacterData Data = PlayerCharacter->GetCharacterData();

		if (Data.CharacterAnimDataAsset)
		{
			return Data.CharacterAnimDataAsset->CharacterAnimationData.CrouchMovementBlendspace;
		}
	}

	return DefaultCharacterAnimDataAsset ? DefaultCharacterAnimDataAsset->CharacterAnimationData.CrouchMovementBlendspace : nullptr;
}

UAnimSequenceBase* UEG_AnimInstance::GetCrouchIdleAnimation() const
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>( GetOwningActor() ))
	{
		FCharacterData Data = PlayerCharacter->GetCharacterData();

		if (Data.CharacterAnimDataAsset)
		{
			return Data.CharacterAnimDataAsset->CharacterAnimationData.CrouchIdleAnimationAsset;
		}
	}

	return DefaultCharacterAnimDataAsset ? DefaultCharacterAnimDataAsset->CharacterAnimationData.CrouchIdleAnimationAsset : nullptr;
}
