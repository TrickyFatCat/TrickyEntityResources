// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "EntityResourcesLibrary.h"

#include "EntityResourceLight.h"

UEntityResourceLight* UEntityResourcesLibrary::CreateEntityResourceLight(UObject* Outer,
                                                                         const FLightResourceData& ResourceData,
                                                                         const FName Name)
{
	UEntityResourceLight* Resource = NewObject<UEntityResourceLight>(Outer, Name);
	Resource->SetResourceData(ResourceData);
	return Resource;
}
