// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AnimNotify_Step.h"

#include "Characters/PlayerCharacter.h"
#include "ActorComponents/FootstepsComponent.h"

void UAnimNotify_Step::Notify( USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation )
{
	Super::Notify( MeshComp, Animation );

	check( MeshComp );
	// TODO: Make it work for both AIs and players
	APlayerCharacter* Character = MeshComp ? Cast<APlayerCharacter>( MeshComp->GetOwner() ) : nullptr;
	if (Character)
	{
		if (UFootstepsComponent* FootstepsComponent = Character->GetFootstepsComponent())
		{
			FootstepsComponent->HandleFootstep( Foot );
		}
	}
}
