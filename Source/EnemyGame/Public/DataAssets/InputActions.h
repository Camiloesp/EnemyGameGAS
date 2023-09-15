// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputActions.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class ENEMYGAME_API UInputActions : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true") )
	UInputAction* MoveAction;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true") )
	UInputAction* LookAction;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true") )
	UInputAction* JumpAction;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true") )
	UInputAction* AttackAction;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true") )
	UInputAction* InteractAction;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true") )
	UInputAction* CrouchAction;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true") )
	UInputAction* SprintAction;


	/*
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true") )
	UInputAction* Action;

	*/

};
