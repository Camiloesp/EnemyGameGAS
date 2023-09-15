// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"

#include "AbilitySystemComponent.h"

#include "AttributeSetBase.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ENEMYGAME_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	// Health
	UPROPERTY( BlueprintReadOnly, Category = "00-Attributes|Health", ReplicatedUsing = OnRep_Health )
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS( UAttributeSetBase, Health );
	UPROPERTY( BlueprintReadOnly, Category = "00-Attributes|Health", ReplicatedUsing = OnRep_MaxHealth )
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS( UAttributeSetBase, MaxHealth );

	// Stamina - Electricity ?
	UPROPERTY( BlueprintReadOnly, Category = "00-Attributes|Stamina", ReplicatedUsing = OnRep_Stamina )
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS( UAttributeSetBase, Stamina );
	UPROPERTY( BlueprintReadOnly, Category = "00-Attributes|Stamina", ReplicatedUsing = OnRep_MaxStamina )
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS( UAttributeSetBase, MaxStamina );

	// Max movement speed
	UPROPERTY( BlueprintReadOnly, Category = "00-Attributes|Movement", ReplicatedUsing = OnRep_MaxMovementSpeed )
	FGameplayAttributeData MaxMovementSpeed;
	ATTRIBUTE_ACCESSORS( UAttributeSetBase, MaxMovementSpeed );

protected:

	virtual void PostGameplayEffectExecute( const struct FGameplayEffectModCallbackData& Data ) override;

	// Health
	UFUNCTION()
	virtual void OnRep_Health( const FGameplayAttributeData& OldHealth );
	UFUNCTION()
	virtual void OnRep_MaxHealth( const FGameplayAttributeData& OldMaxHealth );

	// Stamina
	UFUNCTION()
	virtual void OnRep_Stamina( const FGameplayAttributeData& OldStamina );
	UFUNCTION()
	virtual void OnRep_MaxStamina( const FGameplayAttributeData& OldMaxStamina );

	// Movement 
	UFUNCTION()
	virtual void OnRep_MaxMovementSpeed( const FGameplayAttributeData& OldMaxMovementSpeed );
};
