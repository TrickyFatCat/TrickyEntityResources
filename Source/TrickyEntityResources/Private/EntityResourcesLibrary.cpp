// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


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
