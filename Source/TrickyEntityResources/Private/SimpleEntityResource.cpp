// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "SimpleEntityResource.h"

USimpleEntityResource::USimpleEntityResource()
{
}

void USimpleEntityResource::DecreaseValue(const int32 Amount)
{
	if (Amount <= 0)
	{
		return;
	}
	
	ResourceData.Value -= Amount;
	ResourceData.Value = FMath::Max(ResourceData.Value, 0);
	OnValueDecreased.Broadcast(ResourceData.Value, Amount);

	if (ResourceData.Value == 0)
	{
		OnValueZero.Broadcast();
	}
}

void USimpleEntityResource::IncreaseValue(const int32 Amount, bool bClampToMax)
{
	if (Amount <= 0)
	{
		return;
	}
	
	ResourceData.Value += Amount;

	if (bClampToMax)
	{
		ResourceData.Value = FMath::Min(ResourceData.Value, ResourceData.MaxValue);
	}

	OnValueIncreased.Broadcast(ResourceData.Value, Amount);
}

void USimpleEntityResource::DecreaseMaxValue(int32 Amount,const bool bClampValue)
{
	if (Amount <= 0)
	{
		return;
	}

	ResourceData.MaxValue -= Amount;
	ResourceData.MaxValue = FMath::Max(ResourceData.MaxValue, 0);
	OnMaxValueDecreased.Broadcast(ResourceData.MaxValue, Amount);

	if (bClampValue && ResourceData.Value > ResourceData.MaxValue)
	{
		Amount = FMath::Abs(ResourceData.MaxValue - ResourceData.Value);
		DecreaseValue(Amount);
	}
}

void USimpleEntityResource::IncreaseMaxValue(int32 Amount, const bool bClampValue)
{
	if (Amount <= 0)
	{
		return;
	}

	ResourceData.MaxValue += Amount;
	OnMaxValueIncreased.Broadcast(ResourceData.MaxValue, Amount);

	if (bClampValue)
	{
		Amount = ResourceData.MaxValue - ResourceData.Value;
		IncreaseValue(Amount);
	}
}

float USimpleEntityResource::GetNormalisedValue() const
{
	if (ResourceData.Value == 0 || ResourceData.MaxValue == 0)
	{
		return 0.f;
	}

	return static_cast<float>(ResourceData.Value) / static_cast<float>(ResourceData.MaxValue);
}

int32 USimpleEntityResource::GetValue() const
{
	return ResourceData.Value;
}

int32 USimpleEntityResource::GetMaxValue() const
{
	return ResourceData.MaxValue;
}

void USimpleEntityResource::SetResourceData(const FSimpleResourceData& Data)
{
	ResourceData = Data;
	ResourceData.Value = ResourceData.bCustomInitialValue ? ResourceData.InitialValue : ResourceData.MaxValue;
	OnValueIncreased.Broadcast(ResourceData.Value, 0);
	OnMaxValueIncreased.Broadcast(ResourceData.MaxValue, 0);
}

void USimpleEntityResource::GetResourceData(FSimpleResourceData& Data) const
{
	Data = ResourceData;
}
