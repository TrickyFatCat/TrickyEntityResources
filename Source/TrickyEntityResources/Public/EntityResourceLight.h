// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EntityResourceLight.generated.h"

USTRUCT(BlueprintType)
struct FLightResourceData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="EntityResourceLight")
	int32 Value = 100;
	
	UPROPERTY(BlueprintReadWrite, Category="EntityResourceLight", meta=(ClampMin="0"))
	int32 MaxValue = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EntityResourceLight", meta=(InlineEditConditionToggle))
	bool bCustomInitialValue = false;

	UPROPERTY(BlueprintReadWrite, Category="EntityResourceLight", meta=(EditCondition="bCustomInitialValue", ClampMin="0"))
	int32 InitialValue = 100;	
};

/**
 * 
 */
UCLASS(NotBlueprintable, BlueprintType)
class TRICKYENTITYRESOURCES_API UEntityResourceLight : public UObject
{
	GENERATED_BODY()

public:
	UEntityResourceLight();

	UFUNCTION(BlueprintCallable, Category="EntityResources|Light")
	void DecreaseValue(const int32 Amount);

	UFUNCTION(BlueprintCallable, Category="EntityResources|Light")
	void IncreaseValue(const int32 Amount, bool bClampToMax = true);

	UFUNCTION(BlueprintCallable, Category="EntityResources|Light")
	void DecreaseMaxValue(int32 Amount, const bool bClampValue = true);
	
	UFUNCTION(BlueprintCallable, Category="EntityResources|Light")
	void IncreaseMaxValue(int32 Amount, const bool bClampValue = false);

	UFUNCTION(BlueprintPure, Category="EntityResources|Light")
	float GetNormalisedValue() const;

	void SetResourceData(const FLightResourceData& Data);
private:
	UPROPERTY(BlueprintReadOnly, Category="EntityResources|Light", meta=(AllowPrivateAccess));
	FLightResourceData ResourceData;
};
