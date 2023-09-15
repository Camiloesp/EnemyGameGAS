// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/*
*	HOW CHARACTERS ARE CREATED:
*	1) Starting Effects and abilities are assigned on a CharacterDataAsset.
*	2) Assign that asset to the AI or player BP.
*	3) If CharacterDataAsset is valid, from PostInitializeComponents() we set the FCharacterData from the DataAsset.
*	4) Once SetCharacterData is called, it then calls InitFromCharacterData.
*	5) ... InitFromCharacterData() ?
*	6) Once PossessedBy() is called, GiveAbilities() and ApplyStartupEffects() are called. Both functions search for CharacterData.Effects/Abilities to apply/give the character.
* 
*	HOW ANIMATION BPs WORK: In this project animation BPs are data driven. At least for AIs/Players with the same locomotions like jumping, strafing, falling and landing.
*	1) We have a struct called FCharacterAnimationData in the EnemyGameTypes.h that holds blendspaces and idle animations. Animations will be set in the UCharacterAnimDataAsset. 
*	The FCharacterData that holds the GAS effects and abilities will reference the UCharacterAnimDataAsset since its something we want all characters to have. that  and the _____ will reference that asset.
*	Basically, a data asset inside a data asset.
*	2) Create Getters for those animations inside the UCharacterAnimDataAsset and call them in the locomotions. (You can expose the sequence pin)
* 
*	PHYSICAL MATERIALS:
*	1) Create a class based of UPhysicalMaterial.
*	2) Add a USoundBase to have a reference of the Footstep sound or any other sounds for this surface. (BulletHit sound, landing sound, etc...)
*	We could store GAS effects or abilities to be granted once a character steps on this material.
*	3) Assign Physical Material to ParentMaterial or MaterialInstance or it can also be assigned to a material placed on the level.
*	4) We created two classes: FootstepsComponent derived from ActorComponent and a AnimNotify_Step Derived from AnimNotify class.
*	5) assign the UFootstepsComponent component to the characters we want to use physical materials for.
*	6) For the footstep notify we Create an enum to specify which foot it is. EFoot::EF_Right or EFoot::EF_Left
*	7) In the UFootstepsComponent create a callback function for the notify like: HandleFootstep( EFoot Foot ) that plays a footstep sound, getting the sound from the custom PhysicalMaterial class we created.
*	8) In the AnimNotify_Step class, override Notify(). This function will call the UFootstepsComponent::HandleFootstep, passing in a variable created in the header as EFoot Foot and its EditAnywhere so we can edit it in when we place the notify in our animation.
*	9) Add notifies in Walk, Run, Sprint, Landing, TurnInPlace, and all animations that move their feet. Add the notify in the frame where the feet lands by right clicking the notify track and then "Add Notify" section and we should be able to see our AnimNotifyStep.
*	then in the notify added, in the details panel, select which foot was the one that touched the ground.
*	10) In the character BP, select the UFootstepsComponent and populate the feet socket/bone names.
* 
* 
*	HOW TO SETUP GAS FOR THE FIRST TIME AND CREATE-ACTIVATE A BASIC JUMP ABILITY:
*	My super cool secret big brain documentation: https://docs.google.com/document/d/1ZjZIwHAhGMgU6lxfY2pKgErPZmpb2NwuiDtvJa93iDg/edit
*/


/*
* TODO:
* 1) UFootstepsComponent TODOs
* 2) UAnimNotify_Step TODOs
* 3) Refactor repetitive code in PlayerCharacter & UEG_AnimInstance
*/