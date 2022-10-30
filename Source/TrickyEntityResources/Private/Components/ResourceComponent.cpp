// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "Components/ResourceComponent.h"


UResourceComponent::UResourceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();

	ResourceObject = NewObject<UEntityResource>(this);

	if (ResourceObject)
	{
		ResourceObject->SetResourceData(ResourceData);
		ResourceObject->SetAutoDecreaseData(AutoDecreaseData);
		ResourceObject->SetAutoIncreaseData(AutoIncreaseData);

		ResourceObject->OnValueDecreased.AddDynamic(this, &UResourceComponent::OnValueDecreased);
		ResourceObject->OnValueIncreased.AddDynamic(this, &UResourceComponent::OnValueIncreased);
		ResourceObject->OnValueZero.AddDynamic(this, &UResourceComponent::OnValueZero);
		ResourceObject->OnMaxValueDecreased.AddDynamic(this, &UResourceComponent::OnMaxValueDecreased);
		ResourceObject->OnMaxValueIncreased.AddDynamic(this, &UResourceComponent::OnMaxValueIncreased);
		ResourceObject->OnAutoDecreaseStarted.AddDynamic(this, &UResourceComponent::OnAutoDecreaseStarted);
		ResourceObject->OnAutoIncreaseStarted.AddDynamic(this, &UResourceComponent::OnAutoIncreaseStarted);
		ResourceObject->OnAutoDecreaseStopped.AddDynamic(this, &UResourceComponent::OnAutoDecreaseStopped);
		ResourceObject->OnAutoIncreaseStopped.AddDynamic(this, &UResourceComponent::OnAutoIncreaseStopped);
		
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

void UResourceComponent::TickComponent(float DeltaTime,
                                       ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UResourceComponent::DecreaseValue(const float Amount) const
{
	if (!ResourceObject)
	{
		return;
	}

	ResourceObject->DecreaseValue(Amount);
}

void UResourceComponent::IncreaseValue(const float Amount, const bool bClampToMax) const
{
	if (!ResourceObject)
	{
		return;
	}

	ResourceObject->IncreaseValue(Amount, bClampToMax);
}

void UResourceComponent::DecreaseMaxValue(const float Amount, const bool bClampValue) const
{
	if (!ResourceObject)
	{
		return;
	}

	ResourceObject->DecreaseMaxValue(Amount, bClampValue);
}

void UResourceComponent::IncreaseMaxValue(const float Amount, const bool bClampValue) const
{
	if (!ResourceObject)
	{
		return;
	}

	ResourceObject->IncreaseMaxValue(Amount, bClampValue);
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

void UResourceComponent::StartAutoDecrease() const
{
	if (!ResourceObject)
	{
		return;
	}

	ResourceObject->StartAutoDecrease();
}

void UResourceComponent::StartAutoIncrease() const
{
	if (!ResourceObject)
	{
		return;
	}

	ResourceObject->StartAutoIncrease();
}

void UResourceComponent::StopAutoDecrease() const
{
	if (!ResourceObject)
	{
		return;
	}

	ResourceObject->StopAutoDecrease();
}

void UResourceComponent::StopAutoIncrease() const
{
	if (!ResourceObject)
	{
		return;
	}

	ResourceObject->StopAutoIncrease();
}

void UResourceComponent::OnValueDecreased(const float NewValue, const float Amount)
{
	ResourceData.Value = NewValue;
	OnResourceValueDecreased.Broadcast(NewValue, Amount);
}

void UResourceComponent::OnValueIncreased(const float NewValue, const float Amount)
{
	ResourceData.Value = NewValue;
	OnResourceValueIncreased.Broadcast(NewValue, Amount);
}

void UResourceComponent::OnValueZero()
{
	OnResourceValueZero.Broadcast();
}

void UResourceComponent::OnMaxValueDecreased(const float NewValue, const float Amount)
{
	ResourceData.MaxValue = NewValue;
	OnResourceMaxValueDecreased.Broadcast(NewValue, Amount);
}

void UResourceComponent::OnMaxValueIncreased(const float NewValue, const float Amount)
{
	ResourceData.MaxValue = NewValue;
	OnResourceMaxValueIncreased.Broadcast(NewValue, Amount);
}

void UResourceComponent::OnAutoDecreaseStarted()
{
	OnResourceAutoDecreaseStarted.Broadcast();
}

void UResourceComponent::OnAutoIncreaseStarted()
{
	OnResourceAutoIncreaseStarted.Broadcast();
}

void UResourceComponent::OnAutoDecreaseStopped()
{
	OnResourceAutoDecreaseStopped.Broadcast();
}

void UResourceComponent::OnAutoIncreaseStopped()
{
	OnResourceAutoIncreaseStopped.Broadcast();
}
