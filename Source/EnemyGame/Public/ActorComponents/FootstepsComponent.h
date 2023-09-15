// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "EnemyGameTypes.h"

#include "FootstepsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENEMYGAME_API UFootstepsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFootstepsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* UFootstepsComponent */

public: // Public functions then variables

	void HandleFootstep( EFoot Foot );

protected: // protected functions then variables

	UPROPERTY( EditDefaultsOnly )
	FName LeftFootSocketName = TEXT( "LeftFootSocketName" );
	UPROPERTY( EditDefaultsOnly )
	FName RightFootSocketName = TEXT( "RightFootSocketName" );

private: // private functions then variables

public: // Public setters and getters
};
