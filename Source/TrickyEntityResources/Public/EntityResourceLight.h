// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EntityResourceLight.generated.h"

USTRUCT(BlueprintType)
struct FLightResourceData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="EntityResourceLight")
	int32 Value = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EntityResourceLight", meta=(ClampMin="0"))
	int32 MaxValue = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EntityResourceLight")
	bool bCustomInitialValue = false;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="EntityResourceLight",
		meta=(EditCondition="bCustomInitialValue", ClampMin="0"))
	int32 InitialValue = 100;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLightResourceValueDecreasedSignature, int32, NewValue, int32, Amount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLightResourceValueIncreasedSignature, int32, NewValue, int32, Amount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLightResourceZeroValueSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLightResourceMaxValueDecreasedSignature,
                                             int32,
                                             NewMaxValue,
                                             int32,
                                             Amount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLightResourceMaxValueIncreasedSignature,
                                             int32,
                                             NewMaxValue,
                                             int32,
                                             Amount);

/**
 * 
 */
UCLASS(NotBlueprintable, BlueprintType)
class TRICKYENTITYRESOURCES_API UEntityResourceLight : public UObject
{
	GENERATED_BODY()

public:
	UEntityResourceLight();

	UPROPERTY(BlueprintAssignable, Category="EntityResources|Light")
	FOnLightResourceValueDecreasedSignature OnValueDecreased;

	UPROPERTY(BlueprintAssignable, Category="EntityResources|Light")
	FOnLightResourceValueIncreasedSignature OnValueIncreased;

	UPROPERTY(BlueprintAssignable, Category="EntityResources|Light")
	FOnLightResourceZeroValueSignature OnValueZero;

	UPROPERTY(BlueprintAssignable, Category="EntityResources|Light")
	FOnLightResourceMaxValueDecreasedSignature OnMaxValueDecreased;	

	UPROPERTY(BlueprintAssignable, Category="EntityResources|Light")
	FOnLightResourceMaxValueIncreasedSignature OnMaxValueIncreased;
	
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

	UFUNCTION(BlueprintPure, Category="EntityResources|Light")
	int32 GetValue() const;

	UFUNCTION(BlueprintPure, Category="EntityResources|Light")
	int32 GetMaxValue() const;

	void SetResourceData(const FLightResourceData& Data);

	void GetResourceData(FLightResourceData& Data) const;
	
private:
	UPROPERTY(BlueprintReadOnly, Category="EntityResources|Light", meta=(AllowPrivateAccess))
	FLightResourceData ResourceData;
};
