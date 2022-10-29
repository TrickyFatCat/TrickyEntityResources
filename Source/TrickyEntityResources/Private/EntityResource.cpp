// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "EntityResource.h"

void FResourceAutoData::CalculateTickDelay(FResourceAutoData& Data)
{
	Data.TickDelay = Data.Frequency <= 0 ? 0 : 1.f / Data.Frequency;
}

UEntityResource::UEntityResource()
{
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
