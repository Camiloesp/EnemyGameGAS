// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "EG_PhysicalMaterial.generated.h"

class USoundBase;

UCLASS()
class ENEMYGAME_API UEG_PhysicalMaterial : public UPhysicalMaterial
{
	GENERATED_BODY()
	
public:

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PhysicalMaterial )
	USoundBase* FootstepSound = nullptr;

};
