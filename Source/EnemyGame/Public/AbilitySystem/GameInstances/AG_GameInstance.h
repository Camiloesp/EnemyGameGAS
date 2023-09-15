// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AG_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ENEMYGAME_API UAG_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	// Override Init to use it as a point to Init ability globals global data.
	virtual void Init() override;

};
