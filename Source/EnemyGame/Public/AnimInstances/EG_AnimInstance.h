// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EG_AnimInstance.generated.h"

class UCharacterAnimDataAsset;
/**
 * 
 */
UCLASS()
class ENEMYGAME_API UEG_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
protected:

	UFUNCTION( BlueprintCallable, meta = (BlueprintThreadSafe) )
	UBlendSpace* GetLocomotionBlendspace() const;

	UFUNCTION( BlueprintCallable, meta = (BlueprintThreadSafe) )
	UAnimSequenceBase* GetIdleAnimation() const;

	UFUNCTION( BlueprintCallable, meta = (BlueprintThreadSafe) )
	UBlendSpace* GetCrouchLocomotionBlendspace() const;

	UFUNCTION( BlueprintCallable, meta = (BlueprintThreadSafe) )
	UAnimSequenceBase* GetCrouchIdleAnimation() const;

	/* 
	* We add one here so our character isn't T-Posing. 
	* Also in case the Getters return nullptr.
	*/
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "Animations" )
	UCharacterAnimDataAsset* DefaultCharacterAnimDataAsset;

private:

public:



};
