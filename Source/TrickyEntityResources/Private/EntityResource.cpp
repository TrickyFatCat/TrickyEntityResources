// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "EntityResource.h"

void FResourceAutoData::CalculateTickDelay(FResourceAutoData& Data)
{
	Data.TickDelay = Data.Frequency <= 0 ? 0 : 1.f / Data.Frequency;
}

UEntityResource::UEntityResource()
{
}

void UEntityResource::DecreaseValue(float Amount)
{
	if (Amount <= 0.f)
	{
		return;
	}

	ResourceData.Value -= Amount;
	ResourceData.Value = FMath::Max(ResourceData.Value, 0.f);
	// TODO Call delegate

	if (ResourceData.Value <= 0.f)
	{
		// TODO Call delegate
	}
}

void UEntityResource::IncreaseValue(const float Amount, const bool bClampToMax)
{
	if (Amount <= 0.f)
	{
		return;
	}

	ResourceData.Value += Amount;

	if (bClampToMax)
	{
		ResourceData.Value = FMath::Min(ResourceData.Value, ResourceData.MaxValue);
	}

	// TODO Call delegate
	// TODO Start/Stop auto increase/decrease
}

void UEntityResource::DecreaseMaxValue(float Amount, const bool bClampValue)
{
	if (Amount <= 0.f)
	{
		return;
	}

	ResourceData.MaxValue -= Amount;
	ResourceData.MaxValue = FMath::Max(ResourceData.MaxValue, 0.f);
	// TODO Call delegate

	if (bClampValue && ResourceData.Value > ResourceData.MaxValue)
	{
		Amount = FMath::Abs(ResourceData.MaxValue - ResourceData.Value);
		DecreaseValue(Amount);
	}

	// TODO Start/Stop auto increase/decrease
}

void UEntityResource::IncreaseMaxValue(float Amount, const bool bClampValue)
{
	if (Amount <= 0.f)
	{
		return;
	}

	ResourceData.MaxValue += Amount;
	// TODO Call delegate

	if (bClampValue)
	{
		Amount = FMath::Abs(ResourceData.MaxValue - ResourceData.Value);
		ResourceData.Value > ResourceData.MaxValue ? DecreaseValue(Amount) : IncreaseValue(Amount);
	}

	// TODO Start/Stop auto increase/decrease
}

float UEntityResource::GetNormalisedValue() const
{
	if (ResourceData.Value <= 0.f || ResourceData.MaxValue <= 0.f)
	{
		return 0.f;
	}

	return ResourceData.Value / ResourceData.MaxValue;
}

float UEntityResource::GetValue() const
{
	return ResourceData.Value;
}

float UEntityResource::GetMaxValue() const
{
	return ResourceData.MaxValue;
}

void UEntityResource::SetResourceData(const FResourceData& Data,
                                      const FResourceAutoData& IncreaseData,
                                      const FResourceAutoData& DecreaseData)
{
	ResourceData = Data;
	AutoIncreaseData = IncreaseData;
	AutoDecreaseData = DecreaseData;

	ResourceData.Value = ResourceData.bUseCustomInitialValue ? ResourceData.InitialValue : ResourceData.MaxValue;
	FResourceAutoData::CalculateTickDelay(AutoIncreaseData);
	FResourceAutoData::CalculateTickDelay(AutoDecreaseData);

	// TODO start auto increase
	// TODO start auto decrease
}

void UEntityResource::GetResourceData(FResourceData& Data,
                                      FResourceAutoData& IncreaseData,
                                      FResourceAutoData& DecreaseData) const
{
	Data = ResourceData;
	IncreaseData = AutoIncreaseData;
	DecreaseData = AutoDecreaseData;
}
