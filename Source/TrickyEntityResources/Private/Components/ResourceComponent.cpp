// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "Components/ResourceComponent.h"


UResourceComponent::UResourceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UResourceComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (ResourceObject)
	{
		return;
	}

	ResourceObject = NewObject<UEntityResource>(this);

	if (ResourceObject)
	{
		ResourceObject->SetResourceData(ResourceData);
		ResourceObject->SetAutoDecreaseData(AutoDecreaseData);
		ResourceObject->SetAutoIncreaseData(AutoIncreaseData);

		ResourceObject->OnValueDecreased.AddDynamic(this, &UResourceComponent::HandleValueDecrease);
		ResourceObject->OnValueIncreased.AddDynamic(this, &UResourceComponent::HandleValueIncrease);
		ResourceObject->OnValueZero.AddDynamic(this, &UResourceComponent::HandleValueZero);
		ResourceObject->OnMaxValueDecreased.AddDynamic(this, &UResourceComponent::HandleMaxValueDecrease);
		ResourceObject->OnMaxValueIncreased.AddDynamic(this, &UResourceComponent::HandleMaxValueIncrease);
		ResourceObject->OnAutoDecreaseStarted.AddDynamic(this, &UResourceComponent::HandleAutoDecreaseStart);
		ResourceObject->OnAutoIncreaseStarted.AddDynamic(this, &UResourceComponent::HandleAutoIncreaseStart);
		ResourceObject->OnAutoDecreaseStopped.AddDynamic(this, &UResourceComponent::HandleAutoDecreaseStop);
		ResourceObject->OnAutoIncreaseStopped.AddDynamic(this, &UResourceComponent::HandleAutoIncreaseStop);

		if (GetNormalisedValue() >= AutoDecreaseData.Threshold)
		{
			ResourceObject->StartAutoDecrease();
		}

		if (GetNormalisedValue() <= AutoIncreaseData.Threshold)
		{
			ResourceObject->StartAutoIncrease();
		}
	}
}

bool UResourceComponent::DecreaseValue(const float Amount)
{
	if (!ResourceObject)
	{
		return false;
	}

	return ResourceObject->DecreaseValue(Amount);
}

bool UResourceComponent::IncreaseValue(const float Amount, const bool bClampToMax)
{
	if (!ResourceObject)
	{
		return false;
	}

	return ResourceObject->IncreaseValue(Amount, bClampToMax);
}

bool UResourceComponent::DecreaseMaxValue(const float Amount, const bool bClampValue)
{
	if (!ResourceObject)
	{
		return false;
	}

	return ResourceObject->DecreaseMaxValue(Amount, bClampValue);
}

bool UResourceComponent::IncreaseMaxValue(const float Amount, const bool bClampValue)
{
	if (!ResourceObject)
	{
		return false;
	}

	return ResourceObject->IncreaseMaxValue(Amount, bClampValue);
}

float UResourceComponent::GetValue() const
{
	if (!ResourceObject)
	{
		return -1.f;
	}

	return ResourceObject->GetValue();
}

float UResourceComponent::GetMaxValue() const
{
	if (!ResourceObject)
	{
		return -1.f;
	}

	return ResourceObject->GetMaxValue();
}

float UResourceComponent::GetNormalisedValue() const
{
	if (!ResourceObject)
	{
		return -1.f;
	}

	return ResourceObject->GetNormalisedValue();
}

void UResourceComponent::SetAutoDecreaseEnabled(const bool bIsEnabled)
{
	if (!ResourceObject)
	{
		return;
	}

	AutoDecreaseData.bIsEnabled = bIsEnabled;
	ResourceObject->SetAutoDecreaseEnabled(bIsEnabled);
}

void UResourceComponent::SetAutoIncreaseEnabled(const bool bIsEnabled)
{
	if (!ResourceObject)
	{
		return;
	}

	AutoIncreaseData.bIsEnabled = bIsEnabled;
	ResourceObject->SetAutoIncreaseEnabled(bIsEnabled);
}

FResourceAutoData UResourceComponent::GetAutoDecreaseData() const
{
	FResourceAutoData Data = AutoDecreaseData;

	if (ResourceObject)
	{
		ResourceObject->GetAutoDecreaseData(Data);
	}

	return Data;
}

FResourceAutoData UResourceComponent::GetAutoIncreaseData() const
{
	FResourceAutoData Data = AutoIncreaseData;

	if (ResourceObject)
	{
		ResourceObject->GetAutoIncreaseData(Data);
	}

	return Data;
}

void UResourceComponent::SetAutoDecreaseData(const FResourceAutoData& Data)
{
	if (!ResourceObject)
	{
		return;
	}

	AutoDecreaseData = Data;
	ResourceObject->SetAutoDecreaseData(AutoDecreaseData);
}

void UResourceComponent::SetAutoIncreaseData(const FResourceAutoData& Data)
{
	if (!ResourceObject)
	{
		return;
	}

	AutoIncreaseData = Data;
	ResourceObject->SetAutoDecreaseData(AutoIncreaseData);
}

bool UResourceComponent::StartAutoDecrease() const
{
	if (!ResourceObject)
	{
		return false;
	}

	return ResourceObject->StartAutoDecrease();
}

bool UResourceComponent::StartAutoIncrease() const
{
	if (!ResourceObject)
	{
		return false;
	}

	return ResourceObject->StartAutoIncrease();
}

bool UResourceComponent::StopAutoDecrease() const
{
	if (!ResourceObject)
	{
		return false;
	}

	return ResourceObject->StopAutoDecrease();
}

bool UResourceComponent::StopAutoIncrease() const
{
	if (!ResourceObject)
	{
		return false;
	}

	return ResourceObject->StopAutoIncrease();
}

void UResourceComponent::HandleValueDecrease(const float NewValue, const float Amount)
{
	ResourceData.Value = NewValue;
	OnValueDecreased.Broadcast(NewValue, Amount);
}

void UResourceComponent::HandleValueIncrease(const float NewValue, const float Amount)
{
	ResourceData.Value = NewValue;
	OnValueIncreased.Broadcast(NewValue, Amount);
}

void UResourceComponent::HandleValueZero()
{
	OnValueZero.Broadcast();
}

void UResourceComponent::HandleMaxValueDecrease(const float NewValue, const float Amount)
{
	ResourceData.MaxValue = NewValue;
	OnMaxValueDecreased.Broadcast(NewValue, Amount);
}

void UResourceComponent::HandleMaxValueIncrease(const float NewValue, const float Amount)
{
	ResourceData.MaxValue = NewValue;
	OnMaxValueIncreased.Broadcast(NewValue, Amount);
}

void UResourceComponent::HandleAutoDecreaseStart()
{
	OnAutoDecreaseStarted.Broadcast();
}

void UResourceComponent::HandleAutoIncreaseStart()
{
	OnAutoIncreaseStarted.Broadcast();
}

void UResourceComponent::HandleAutoDecreaseStop()
{
	OnAutoDecreaseStopped.Broadcast();
}

void UResourceComponent::HandleAutoIncreaseStop()
{
	OnAutoIncreaseStopped.Broadcast();
}
