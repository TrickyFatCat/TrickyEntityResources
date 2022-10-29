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
	else
	{
		StartAutoIncrease();
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
	StartAutoDecrease();
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

void UEntityResource::SetResourceData(const FResourceData& Data)
{
	ResourceData = Data;
	ResourceData.Value = ResourceData.bUseCustomInitialValue ? ResourceData.InitialValue : ResourceData.MaxValue;
}

void UEntityResource::GetResourceData(FResourceData& Data) const
{
	Data = ResourceData;
}

void UEntityResource::SetAutoIncreaseEnabled(const bool bIsEnabled)
{
	AutoIncreaseData.bIsEnabled = bIsEnabled;
	
	bIsEnabled ? StartAutoIncrease() : StopTimer(AutoIncreaseTimer);
}

void UEntityResource::SetAutoDecreaseEnabled(const bool bIsEnabled)
{
	AutoDecreaseData.bIsEnabled = bIsEnabled;

	bIsEnabled ? StartAutoDecrease() : StopTimer(AutoDecreaseTimer);
}

void UEntityResource::SetAutoIncreaseData(const FResourceAutoData& Data)
{
	AutoIncreaseData = Data;
	FResourceAutoData::CalculateTickDelay(AutoIncreaseData);
	StartAutoIncrease();
}

void UEntityResource::SetAutoDecreaseData(const FResourceAutoData& Data)
{
	AutoDecreaseData = Data;
	FResourceAutoData::CalculateTickDelay(AutoDecreaseData);
	StartAutoIncrease();
}

void UEntityResource::GetAutoIncreaseData(FResourceAutoData& Data)
{
	Data = AutoIncreaseData;
}

void UEntityResource::GetAutoDecreaseData(FResourceAutoData& Data)
{
	Data = AutoDecreaseData;
}

void UEntityResource::StopTimer(FTimerHandle& TimerHandle) const
{
	if (!GetWorld())
	{
		return;
	}

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (TimerManager.TimerExists(TimerHandle))
	{
		TimerManager.ClearTimer(TimerHandle);
	}
}

void UEntityResource::StartAutoIncrease()
{
	if (!AutoIncreaseData.bIsEnabled || GetNormalisedValue() >= AutoIncreaseData.Threshold || !GetWorld())
	{
		return;
	}

	StopTimer(AutoIncreaseTimer);
	GetWorld()->GetTimerManager().SetTimer(AutoIncreaseTimer,
	                                       this,
	                                       &UEntityResource::ProcessAutoIncrease,
	                                       AutoIncreaseData.TickDelay,
	                                       true,
	                                       AutoIncreaseData.StartDelay);
}

void UEntityResource::ProcessAutoIncrease()
{
	IncreaseValue(AutoIncreaseData.Power);

	if (GetNormalisedValue() >= AutoIncreaseData.Threshold)
	{
		StopTimer(AutoIncreaseTimer);
	}
}

void UEntityResource::StartAutoDecrease()
{
	if (!AutoDecreaseData.bIsEnabled || GetNormalisedValue() <= AutoDecreaseData.Threshold || !GetWorld())
	{
		return;
	}

	StopTimer(AutoDecreaseTimer);
	GetWorld()->GetTimerManager().SetTimer(AutoDecreaseTimer,
	                                       this,
	                                       &UEntityResource::ProcessAutoDecrease,
	                                       AutoDecreaseData.TickDelay,
	                                       true,
	                                       AutoIncreaseData.StartDelay);
}

void UEntityResource::ProcessAutoDecrease()
{
	DecreaseValue(AutoDecreaseData.Power);

	if (GetNormalisedValue() <= AutoDecreaseData.Threshold)
	{
		StopTimer(AutoDecreaseTimer);
	}
}