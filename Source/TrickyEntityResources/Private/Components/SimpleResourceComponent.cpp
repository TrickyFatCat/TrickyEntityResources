// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "Components/SimpleResourceComponent.h"
#include "SimpleEntityResource.h"
#include "EntityResourcesLibrary.h"


USimpleResourceComponent::USimpleResourceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USimpleResourceComponent::BeginPlay()
{
	Super::BeginPlay();

	ResourceObject = NewObject<USimpleEntityResource>(this);

	if (ResourceObject)
	{
		ResourceObject->SetResourceData(ResourceData);
		ResourceObject->OnValueDecreased.AddDynamic(this, &USimpleResourceComponent::OnValueDecreased);
		ResourceObject->OnValueIncreased.AddDynamic(this, &USimpleResourceComponent::OnValueIncreased);
		ResourceObject->OnValueZero.AddDynamic(this, &USimpleResourceComponent::OnValueZero);
		ResourceObject->OnMaxValueDecreased.AddDynamic(this, &USimpleResourceComponent::OnMaxValueDecreased);
		ResourceObject->OnMaxValueIncreased.AddDynamic(this, &USimpleResourceComponent::OnMaxValueIncreased);
	}
}

void USimpleResourceComponent::DecreaseValue(const int32 Amount)
{
	if (!ResourceObject)
	{
		return;
	}
	
	ResourceObject->DecreaseValue(Amount);
}

void USimpleResourceComponent::IncreaseValue(const int32 Amount, const bool bClampToMax)
{
	if (!ResourceObject)
	{
		return;
	}
	
	ResourceObject->IncreaseValue(Amount, bClampToMax);
}

void USimpleResourceComponent::DecreaseMaxValue(int32 Amount, const bool bClampValue)
{
	if (!ResourceObject)
	{
		return;
	}

	ResourceObject->DecreaseMaxValue(Amount, bClampValue);
}

void USimpleResourceComponent::IncreaseMaxValue(int32 Amount, const bool bClampValue)
{
	if (!ResourceObject)
	{
		return;
	}

	ResourceObject->IncreaseMaxValue(Amount, bClampValue);
}

int32 USimpleResourceComponent::GetValue() const
{
	if (!ResourceObject)
	{
		return 0;
	}

	return ResourceObject->GetValue();
}

int32 USimpleResourceComponent::GetMaxValue() const
{
	if (!ResourceObject)
	{
		return 0;
	}

	return ResourceObject->GetMaxValue();
}

float USimpleResourceComponent::GetNormalisedValue() const
{
	if (!ResourceObject)
	{
		return 0.f;
	}

	return ResourceObject->GetNormalisedValue();
}

void USimpleResourceComponent::OnValueDecreased(const int32 NewValue, const int32 Amount)
{
	ResourceData.Value = NewValue;
	OnResourceValueDecreased.Broadcast(NewValue, Amount);
}

void USimpleResourceComponent::OnValueIncreased(const int32 NewValue, const int32 Amount)
{
	ResourceData.Value = NewValue;
	OnResourceValueIncreased.Broadcast(NewValue, Amount);
}

void USimpleResourceComponent::OnValueZero()
{
	OnResourceValueZero.Broadcast();
}

void USimpleResourceComponent::OnMaxValueDecreased(const int32 NewMaxValue, const int32 Amount)
{
	ResourceData.MaxValue = NewMaxValue;
	OnResourceMaxValueDecreased.Broadcast(NewMaxValue, Amount);
}

void USimpleResourceComponent::OnMaxValueIncreased(const int32 NewMaxValue, const int32 Amount)
{
	ResourceData.MaxValue = NewMaxValue;
	OnResourceMaxValueIncreased.Broadcast(NewMaxValue, Amount);
}

