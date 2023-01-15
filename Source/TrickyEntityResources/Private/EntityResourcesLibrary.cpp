// MIT License Copyright (c) 2023 Artyom "Tricky Fat Cat" Volkov


#include "EntityResourcesLibrary.h"

#include "SimpleEntityResource.h"

USimpleEntityResource* UEntityResourcesLibrary::CreateSimpleEntityResource(UObject* Outer,
                                                                           const FSimpleResourceData& ResourceData,
                                                                           const FName Name)
{
	USimpleEntityResource* Resource = NewObject<USimpleEntityResource>(Outer, Name);
	Resource->SetResourceData(ResourceData);
	return Resource;
}

UEntityResource* UEntityResourcesLibrary::CreateEntityResource(UObject* Outer,
                                                               const FResourceData& ResourceData,
                                                               const FResourceAutoData& AutoIncreaseData,
                                                               const FResourceAutoData& AutoDecreaseData,
                                                               const FName Name)
{
	UEntityResource* Resource = NewObject<UEntityResource>(Outer, Name);
	Resource->SetResourceData(ResourceData);
	Resource->SetAutoIncreaseData(AutoIncreaseData);
	Resource->SetAutoDecreaseData(AutoDecreaseData);
	return Resource;
}
