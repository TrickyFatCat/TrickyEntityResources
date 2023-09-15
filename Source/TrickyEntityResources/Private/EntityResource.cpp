// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "EntityResource.h"
#include "TimerManager.h"
#include "Engine/World.h"

void FResourceAutoData::CalculateTickDelay(FResourceAutoData& Data)
{
	Data.TickDelay = Data.Frequency <= 0 ? 0 : 1.f / Data.Frequency;
}

UEntityResource::UEntityResource()
{
}

bool UEntityResource::DecreaseValue(const float Amount)
{
	if (Amount <= 0.f || ResourceData.Value <= 0.f)
	{
		return false;
	}

	ResourceData.Value -= Amount;
	ResourceData.Value = FMath::Max(ResourceData.Value, 0.f);
	OnValueDecreased.Broadcast(ResourceData.Value, Amount);

	if (ResourceData.Value <= 0.f)
	{
		OnValueZero.Broadcast();

		if (AutoDecreaseData.bDisableOnZeroValue)
		{
			SetAutoDecreaseEnabled(false);
		}

		if (AutoIncreaseData.bDisableOnZeroValue)
		{
			SetAutoIncreaseEnabled(false);
		}
	}
	else
	{
		StartAutoIncrease();
	}

	if (GetNormalisedValue() <= AutoDecreaseData.Threshold)
	{
		StopAutoDecrease();
	}

	return true;
}

bool UEntityResource::IncreaseValue(const float Amount, const bool bClampToMax)
{
	if (Amount <= 0.f || ResourceData.Value >= ResourceData.MaxValue && bClampToMax)
	{
		return false;
	}

	ResourceData.Value += Amount;

	if (bClampToMax)
	{
		ResourceData.Value = FMath::Min(ResourceData.Value, ResourceData.MaxValue);
	}

	OnValueIncreased.Broadcast(ResourceData.Value, Amount);
	StartAutoDecrease();

	if (GetNormalisedValue() >= AutoIncreaseData.Threshold)
	{
		StopAutoIncrease();
	}

	return true;
}

bool UEntityResource::DecreaseMaxValue(float Amount, const bool bClampValue)
{
	if (Amount <= 0.f || ResourceData.MaxValue <= 0.f)
	{
		return false;
	}

	ResourceData.MaxValue -= Amount;
	ResourceData.MaxValue = FMath::Max(ResourceData.MaxValue, 0.f);
	OnMaxValueDecreased.Broadcast(ResourceData.MaxValue, Amount);

	if (bClampValue && ResourceData.Value > ResourceData.MaxValue)
	{
		Amount = FMath::Abs(ResourceData.MaxValue - ResourceData.Value);
		DecreaseValue(Amount);
	}
	else
	{
		StartAutoDecrease();
	}

	return true;
}

bool UEntityResource::IncreaseMaxValue(float Amount, const bool bClampValue)
{
	if (Amount <= 0.f)
	{
		return false;
	}

	ResourceData.MaxValue += Amount;
	OnMaxValueIncreased.Broadcast(ResourceData.MaxValue, Amount);

	if (bClampValue && ResourceData.Value < ResourceData.MaxValue)
	{
		Amount = FMath::Abs(ResourceData.MaxValue - ResourceData.Value);
		IncreaseValue(Amount);
	}
	else
	{
		ResourceData.Value > ResourceData.MaxValue ? StartAutoDecrease() : StartAutoIncrease();
	}

	return true;
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

	if (bIsEnabled)
	{
		StartAutoIncrease();
	}
	else
	{
		StopTimer(AutoIncreaseTimer);
	}
}

void UEntityResource::SetAutoDecreaseEnabled(const bool bIsEnabled)
{
	AutoDecreaseData.bIsEnabled = bIsEnabled;

	if (bIsEnabled)
	{
		StartAutoDecrease();
	}
	else
	{
		StopTimer(AutoDecreaseTimer);
	}
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

bool UEntityResource::StartAutoDecrease()
{
	if (!AutoDecreaseData.bIsEnabled || GetNormalisedValue() <= AutoDecreaseData.Threshold || !GetWorld())
	{
		return false;
	}

	StopTimer(AutoDecreaseTimer);
	GetWorld()->GetTimerManager().SetTimer(AutoDecreaseTimer,
	                                       this,
	                                       &UEntityResource::ProcessAutoDecrease,
	                                       AutoDecreaseData.TickDelay,
	                                       true,
	                                       AutoDecreaseData.StartDelay);
	return true;
}

bool UEntityResource::StartAutoIncrease()
{
	if (!AutoIncreaseData.bIsEnabled || GetNormalisedValue() >= AutoIncreaseData.Threshold || !GetWorld())
	{
		return false;
	}

	StopTimer(AutoIncreaseTimer);
	GetWorld()->GetTimerManager().SetTimer(AutoIncreaseTimer,
	                                       this,
	                                       &UEntityResource::ProcessAutoIncrease,
	                                       AutoIncreaseData.TickDelay,
	                                       true,
	                                       AutoIncreaseData.StartDelay);

	return true;
}

bool UEntityResource::StopAutoDecrease()
{
	if (!IsTimerActive(AutoDecreaseTimer))
	{
		return false;
	}

	StopTimer(AutoDecreaseTimer);
	OnAutoDecreaseStopped.Broadcast();
	return true;
}

bool UEntityResource::StopAutoIncrease()
{
	if (!IsTimerActive(AutoIncreaseTimer))
	{
		return false;
	}

	StopTimer(AutoIncreaseTimer);
	OnAutoIncreaseStopped.Broadcast();
	return true;
}


bool UEntityResource::IsTimerActive(const FTimerHandle& Timer) const
{
	if (!GetWorld())
	{
		return false;
	}

	const FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	return TimerManager.IsTimerActive(Timer);
}

void UEntityResource::StopTimer(FTimerHandle& TimerHandle) const
{
	if (!GetWorld())
	{
		return;
	}

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (TimerManager.IsTimerActive(TimerHandle))
	{
		TimerManager.ClearTimer(TimerHandle);
	}
}


void UEntityResource::ProcessAutoIncrease()
{
	IncreaseValue(AutoIncreaseData.Power);

	if (GetNormalisedValue() >= AutoIncreaseData.Threshold)
	{
		StopAutoIncrease();
	}
}


void UEntityResource::ProcessAutoDecrease()
{
	DecreaseValue(AutoDecreaseData.Power);

	if (GetNormalisedValue() <= AutoDecreaseData.Threshold)
	{
		StopAutoDecrease();
	}
}
