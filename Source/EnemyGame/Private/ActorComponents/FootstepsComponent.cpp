// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/FootstepsComponent.h"
#include "Characters/PlayerCharacter.h"
#include "PhysicalMaterials/EG_PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"

#include "DrawDebugHelpers.h"

static TAutoConsoleVariable<int32> CVarShowFootsteps(
	TEXT( "ShowDebugFootsteps" ),
	0,
	TEXT( "Draws debug info about footsteps" )
	TEXT( " 0: off/n" )
	TEXT( " 1: on/n" ),
	ECVF_Cheat
);

// Sets default values for this component's properties
UFootstepsComponent::UFootstepsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UFootstepsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFootstepsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// DISABLED ON CONSTRUCTOR
}

void UFootstepsComponent::HandleFootstep( EFoot Foot )
{
	// TODO:
	// Make it work with AIs
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>( GetOwner() ))
	{
		const int32 DebugShowFootsteps = CVarShowFootsteps.GetValueOnAnyThread();

		if ( USkeletalMeshComponent* Mesh = PlayerCharacter->GetMesh() )
		{
			FHitResult HitResult;
			const FVector SocketLocation = Mesh->GetSocketLocation( Foot == EFoot::EF_Left ? LeftFootSocketName : RightFootSocketName );
			const FVector Location = SocketLocation + FVector::UpVector * 20.f;

			FCollisionQueryParams QueryParams;
			QueryParams.bReturnPhysicalMaterial = true;
			QueryParams.AddIgnoredActor( PlayerCharacter );

			if (GetWorld()->LineTraceSingleByChannel( HitResult, Location, Location + FVector::UpVector * -50.f, ECollisionChannel::ECC_WorldStatic, QueryParams ))
			{
				if (HitResult.bBlockingHit)
				{
					if (HitResult.PhysMaterial.Get())
					{
						UEG_PhysicalMaterial* PhysicalMaterial = Cast<UEG_PhysicalMaterial>( HitResult.PhysMaterial.Get() ); // move inside if?
						if (PhysicalMaterial)
						{
							UGameplayStatics::PlaySoundAtLocation( this, PhysicalMaterial->FootstepSound, Location, 1.f );
						}

						if (DebugShowFootsteps > 0)
						{
							DrawDebugString( GetWorld(), Location, GetNameSafe( PhysicalMaterial ), nullptr, FColor::White, 4.f );
						}
					}

					if (DebugShowFootsteps > 0)
					{
						DrawDebugSphere( GetWorld(), Location, 16, 16, FColor::Red, false, 4.f );
					}
				}
				else
				{
					if (DebugShowFootsteps > 0)
					{
						DrawDebugLine( GetWorld(), Location, Location + FVector::UpVector * -50.f, FColor::Red, false, 4, 0, 1 );
					}
				}
			}
			else
			{
				if (DebugShowFootsteps > 0)
				{
					DrawDebugLine( GetWorld(), Location, Location + FVector::UpVector * -50.f, FColor::Red, false, 4, 0, 1 );
					DrawDebugSphere( GetWorld(), Location, 16, 16, FColor::Red, false, 4.f );
				}
			}
		}
	}
}

