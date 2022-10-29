// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "EntityResource.h"
#include "SimpleEntityResource.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EntityResourcesLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TRICKYENTITYRESOURCES_API UEntityResourcesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources")
	static USimpleEntityResource* CreateSimpleEntityResource(UObject* Outer,
	                                                         const FSimpleResourceData& ResourceData,
	                                                         const FName Name = TEXT("New Simple Resource"));

	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources")
	static UEntityResource* CreateEntityResource(UObject* Outer,
	                                             const FResourceData& ResourceData,
	                                             const FResourceAutoData& AutoIncreaseData,
	                                             const FResourceAutoData& AutoDecreaseData,
	                                             const FName Name = TEXT("New Resource"));
};
