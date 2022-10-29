// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "EntityResourceLight.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EntityResourcesLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TRICKYENTITYRESOURCES_API UEntityResourcesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="EntityResources")
	static UEntityResourceLight* CreateEntityResourceLight(UObject* Outer,
	                                                       const FLightResourceData& ResourceData,
	                                                       const FName Name = TEXT("New Light Resource"));
};
