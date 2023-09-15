// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "DataAssets/InputActions.h"
#include "DataAssets/CharacterDataAsset.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AttributeSets/AttributeSetBase.h"
#include "AbilitySystem/Components/AbilitySystemComponentBase.h"

#include "Net/UnrealNetwork.h"

#include "ActorComponents/EG_CharacterMovementComponent.h"
#include "ActorComponents/FootstepsComponent.h"
#include "ActorComponents/EG_MotionWarpingComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter( const FObjectInitializer& ObjectInitializer ) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UEG_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>( TEXT( "CameraBoom" ) );
	SpringArm->SetupAttachment( RootComponent );
	SpringArm->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 10.f;
	SpringArm->CameraRotationLagSpeed = 600.f;

	Camera = CreateDefaultSubobject<UCameraComponent>( TEXT("Camera") );
	Camera->SetupAttachment( SpringArm, USpringArmComponent::SocketName ); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	// GAS
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponentBase>( TEXT("AbilitySystemComponent") );
	AbilitySystemComponent->SetIsReplicated( true );
	AbilitySystemComponent->SetReplicationMode( EGameplayEffectReplicationMode::Mixed );

	AttributeSet = CreateDefaultSubobject<UAttributeSetBase>( TEXT("AttributeSet") );

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate( AttributeSet->GetMaxMovementSpeedAttribute() ).AddUObject(this, &APlayerCharacter::OnMaxMovementSpeedChanged);
	// End GAS

	FootstepsComponent = CreateDefaultSubobject<UFootstepsComponent>( TEXT("FootstepsComponent") );

	EGCharacterMovementComponent = Cast<UEG_CharacterMovementComponent>( GetCharacterMovement() );

	EGMotionWarpingComponent = CreateDefaultSubobject<UEG_MotionWarpingComponent>( TEXT( "MotionWarpingComponent" ) );
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Move to PawnClientRestart() ?
	if (APlayerController* PlayerController = Cast<APlayerController>( Controller ))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>( PlayerController->GetLocalPlayer() ))
		{
			Subsystem->AddMappingContext( DefaultMappingContext, 0 );
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>( PlayerInputComponent )) {

		//Jumping
		EnhancedInputComponent->BindAction( InputActions->JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::OnJumpActionStarted );
		EnhancedInputComponent->BindAction( InputActions->JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnJumpActionEnded );

		//Moving
		EnhancedInputComponent->BindAction( InputActions->MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move );

		//Looking
		EnhancedInputComponent->BindAction( InputActions->LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look );

		//Crouch
		EnhancedInputComponent->BindAction( InputActions->CrouchAction, ETriggerEvent::Started, this, &APlayerCharacter::OnCrouchActionStarted );
		EnhancedInputComponent->BindAction( InputActions->CrouchAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnCrouchActionEnded );

		// Sprint
		EnhancedInputComponent->BindAction( InputActions->SprintAction, ETriggerEvent::Started, this, &APlayerCharacter::OnSprintActionStarted );
		EnhancedInputComponent->BindAction( InputActions->SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnSprintActionEnded );
	}
}

void APlayerCharacter::Move( const FInputActionValue& Value )
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation( 0, Rotation.Yaw, 0 );

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::X );

		// get right vector 
		const FVector RightDirection = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::Y );

		// add movement 
		AddMovementInput( ForwardDirection, MovementVector.Y );
		AddMovementInput( RightDirection, MovementVector.X );
	}
}

void APlayerCharacter::Look( const FInputActionValue& Value )
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput( LookAxisVector.X );
		AddControllerPitchInput( LookAxisVector.Y );
	}
}

void APlayerCharacter::OnJumpActionStarted( const FInputActionValue& Value )
{
	//Jump();
	
	// Send gameplay event.
	// FGameplayEventData Payload;
	// Payload.Instigator = this;
	// Payload.EventTag = JumpEventTag;
	// UAbilitySystemBlueprintLibrary::SendGameplayEventToActor( this, JumpEventTag, Payload );

	EGCharacterMovementComponent->TryTraversal( AbilitySystemComponent );
}

void APlayerCharacter::OnJumpActionEnded( const FInputActionValue& Value )
{
	//StopJumping();
}

void APlayerCharacter::OnCrouchActionStarted( const FInputActionValue& Value )
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->TryActivateAbilitiesByTag( CrouchTags, true );
	}
}

void APlayerCharacter::OnCrouchActionEnded( const FInputActionValue& Value )
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAbilities( &CrouchTags );
	}
}

void APlayerCharacter::OnSprintActionStarted( const FInputActionValue& Value )
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->TryActivateAbilitiesByTag( SprintTags, true );
	}
}

void APlayerCharacter::OnSprintActionEnded( const FInputActionValue& Value )
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAbilities( &SprintTags );
	}
}

void APlayerCharacter::Landed( const FHitResult& Hit )
{
	Super::Landed(Hit);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->RemoveActiveEffectsWithTags( InAirTags );
	}
}

UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

bool APlayerCharacter::ApplyGameplayEffectToSelf( TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext )
{
	// Helper function.
	if (!Effect.Get()) return false;

	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec( Effect, 1, InEffectContext );
	if (SpecHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf( *SpecHandle.Data.Get() );
		return ActiveGEHandle.WasSuccessfullyApplied();
	}

	return false;
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsValid( CharacterDataAsset ))
	{
		SetCharacterData( CharacterDataAsset->CharacterData );
	}
}

void APlayerCharacter::InitFromCharacterData( const FCharacterData& InCharacterData, bool bFromReplication )
{

}

void APlayerCharacter::SetCharacterData( const FCharacterData& InCharacterData )
{
	CharacterData = InCharacterData;

	InitFromCharacterData( CharacterData );
}

void APlayerCharacter::OnRep_CharacterData()
{
	InitFromCharacterData( CharacterData, true );
}

void APlayerCharacter::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for ( auto DefaultAbility : CharacterData.Abilities/*DefaultAbilities*/ )
		{
			AbilitySystemComponent->GiveAbility( FGameplayAbilitySpec(DefaultAbility) );
		}
	}
}

void APlayerCharacter::ApplyStartupEffects()
{
	if (GetLocalRole() == ROLE_Authority) // HasAuthority();
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject( this );

		for (auto CharacterEffect : CharacterData.Effects/*DefaultEffects*/)
		{
			ApplyGameplayEffectToSelf( CharacterEffect, EffectContext );
		}
	}
}

void APlayerCharacter::OnMaxMovementSpeedChanged( const FOnAttributeChangeData& Data )
{
	GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}

void APlayerCharacter::PossessedBy( AController* NewController )
{
	Super::PossessedBy( NewController );

	// PossessedBy used for server side initialization.
	AbilitySystemComponent->InitAbilityActorInfo( this, this );

	GiveAbilities();
	ApplyStartupEffects();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// OnRep_PlayerState used for client side initialization.
	AbilitySystemComponent->InitAbilityActorInfo( this, this );
}

void APlayerCharacter::OnStartCrouch( float HalfHeightAdjust, float ScaledHalfHeightAdjust )
{
	Super::OnStartCrouch( HalfHeightAdjust, ScaledHalfHeightAdjust );

	if (!CrouchStateEffect.Get()) return;

	/* I was able to compile fine without this IF, but tutorial needed it */
	if (AbilitySystemComponent)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec( CrouchStateEffect, 1, EffectContext );
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf( *SpecHandle.Data.Get() );
			if (!ActiveGEHandle.WasSuccessfullyApplied())
			{
				//ABILITY_LOG( Log, TEXT("Ability %s failed to apply crouch effect %s"), *GetName(), *GetNameSafe(CrouchStateEffect));
			}
		}
	}
}

void APlayerCharacter::OnEndCrouch( float HalfHeightAdjust, float ScaledHalfHeightAdjust )
{
	if ( AbilitySystemComponent && CrouchStateEffect.Get() )
	{
		AbilitySystemComponent->RemoveActiveGameplayEffectBySourceEffect( CrouchStateEffect, AbilitySystemComponent );
	}

	Super::OnEndCrouch( HalfHeightAdjust, ScaledHalfHeightAdjust );
}

void APlayerCharacter::GetLifetimeReplicatedProps( TArray<class FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( APlayerCharacter, CharacterData );
}