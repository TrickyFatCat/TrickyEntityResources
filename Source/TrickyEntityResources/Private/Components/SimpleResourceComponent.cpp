// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "Components/SimpleResourceComponent.h"
#include "SimpleEntityResource.h"


USimpleResourceComponent::USimpleResourceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void USimpleResourceComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (!ResourceObject)
	{
		ResourceObject = NewObject<USimpleEntityResource>(this);

		if (!ResourceObject)
		{
			return;
		}

		ResourceObject->SetResourceData(ResourceData);
		ResourceObject->OnValueDecreased.AddDynamic(this, &USimpleResourceComponent::HandleValueDecrease);
		ResourceObject->OnValueIncreased.AddDynamic(this, &USimpleResourceComponent::HandleValueIncrease);
		ResourceObject->OnValueZero.AddDynamic(this, &USimpleResourceComponent::HandleValueZero);
		ResourceObject->OnMaxValueDecreased.AddDynamic(this, &USimpleResourceComponent::HandleMaxValueDecrease);
		ResourceObject->OnMaxValueIncreased.AddDynamic(this, &USimpleResourceComponent::HandleMaxValueIncrease);
	}
}

bool USimpleResourceComponent::DecreaseValue(const int32 Amount)
{
	if (!ResourceObject)
	{
		return false;
	}

	return ResourceObject->DecreaseValue(Amount);
}

bool USimpleResourceComponent::IncreaseValue(const int32 Amount, const bool bClampToMax)
{
	if (!ResourceObject)
	{
		return false;
	}

	return ResourceObject->IncreaseValue(Amount, bClampToMax);
}

bool USimpleResourceComponent::DecreaseMaxValue(int32 Amount, const bool bClampValue)
{
	if (!ResourceObject)
	{
		return false;
	}

	return ResourceObject->DecreaseMaxValue(Amount, bClampValue);
}

bool USimpleResourceComponent::IncreaseMaxValue(int32 Amount, const bool bClampValue)
{
	if (!ResourceObject)
	{
		return false;
	}

	return ResourceObject->IncreaseMaxValue(Amount, bClampValue);
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

void USimpleResourceComponent::HandleValueDecrease(const int32 NewValue, const int32 Amount)
{
	ResourceData.Value = NewValue;
	OnValueDecreased.Broadcast(NewValue, Amount);
}

void USimpleResourceComponent::HandleValueIncrease(const int32 NewValue, const int32 Amount)
{
	ResourceData.Value = NewValue;
	OnValueIncreased.Broadcast(NewValue, Amount);
}

void USimpleResourceComponent::HandleValueZero()
{
	OnValueZero.Broadcast();
}

void USimpleResourceComponent::HandleMaxValueDecrease(const int32 NewMaxValue, const int32 Amount)
{
	ResourceData.MaxValue = NewMaxValue;
	OnValueDecreased.Broadcast(NewMaxValue, Amount);
}

void USimpleResourceComponent::HandleMaxValueIncrease(const int32 NewMaxValue, const int32 Amount)
{
	ResourceData.MaxValue = NewMaxValue;
	OnValueIncreased.Broadcast(NewMaxValue, Amount);
}
