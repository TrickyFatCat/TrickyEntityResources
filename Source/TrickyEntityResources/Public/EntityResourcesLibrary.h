// MIT License Copyright (c) 2023 Artyom "Tricky Fat Cat" Volkov

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

	/**
	 * Creates an EntityResource object.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources")
	static USimpleEntityResource* CreateSimpleEntityResource(UObject* Outer,
	                                                         const FSimpleResourceData& ResourceData,
	                                                         const FName Name = TEXT("New Simple Resource"));

	/**
	 * Creates a SimpleEntityResource object.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources")
	static UEntityResource* CreateEntityResource(UObject* Outer,
	                                             const FResourceData& ResourceData,
	                                             const FResourceAutoData& AutoIncreaseData,
	                                             const FResourceAutoData& AutoDecreaseData,
	                                             const FName Name = TEXT("New Resource"));
};
