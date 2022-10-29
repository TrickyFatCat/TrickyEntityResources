// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SimpleEntityResource.generated.h"

USTRUCT(BlueprintType)
struct FSimpleResourceData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="EntityResourceSimple")
	int32 Value = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EntityResourceSimple", meta=(ClampMin="0"))
	int32 MaxValue = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EntityResourceSimple")
	bool bCustomInitialValue = false;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="EntityResourceSimple",
		meta=(EditCondition="bCustomInitialValue", ClampMin="0"))
	int32 InitialValue = 100;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSimpleResourceValueDecreasedSignature, int32, NewValue, int32, Amount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSimpleResourceValueIncreasedSignature, int32, NewValue, int32, Amount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSimpleResourceZeroValueSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSimpleResourceMaxValueDecreasedSignature,
                                             int32,
                                             NewMaxValue,
                                             int32,
                                             Amount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSimpleResourceMaxValueIncreasedSignature,
                                             int32,
                                             NewMaxValue,
                                             int32,
                                             Amount);

/**
 * 
 */
UCLASS(NotBlueprintable, BlueprintType)
class TRICKYENTITYRESOURCES_API USimpleEntityResource : public UObject
{
	GENERATED_BODY()

public:
	USimpleEntityResource();

	UPROPERTY(BlueprintAssignable, Category="EntityResources|Simple")
	FOnSimpleResourceValueDecreasedSignature OnValueDecreased;

	UPROPERTY(BlueprintAssignable, Category="EntityResources|Simple")
	FOnSimpleResourceValueIncreasedSignature OnValueIncreased;

	UPROPERTY(BlueprintAssignable, Category="EntityResources|Simple")
	FOnSimpleResourceZeroValueSignature OnValueZero;

	UPROPERTY(BlueprintAssignable, Category="EntityResources|Simple")
	FOnSimpleResourceMaxValueDecreasedSignature OnMaxValueDecreased;	

	UPROPERTY(BlueprintAssignable, Category="EntityResources|Simple")
	FOnSimpleResourceMaxValueIncreasedSignature OnMaxValueIncreased;
	
	UFUNCTION(BlueprintCallable, Category="EntityResources|Simple")
	void DecreaseValue(const int32 Amount);

	UFUNCTION(BlueprintCallable, Category="EntityResources|Simple")
	void IncreaseValue(const int32 Amount, bool bClampToMax = true);

	UFUNCTION(BlueprintCallable, Category="EntityResources|Simple")
	void DecreaseMaxValue(int32 Amount, const bool bClampValue = true);

	UFUNCTION(BlueprintCallable, Category="EntityResources|Simple")
	void IncreaseMaxValue(int32 Amount, const bool bClampValue = false);

	UFUNCTION(BlueprintPure, Category="EntityResources|Simple")
	float GetNormalisedValue() const;

	UFUNCTION(BlueprintPure, Category="EntityResources|Simple")
	int32 GetValue() const;

	UFUNCTION(BlueprintPure, Category="EntityResources|Simple")
	int32 GetMaxValue() const;

	void SetResourceData(const FSimpleResourceData& Data);

	void GetResourceData(FSimpleResourceData& Data) const;
	
private:
	UPROPERTY(BlueprintReadOnly, Category="EntityResources|Simple", meta=(AllowPrivateAccess))
	FSimpleResourceData ResourceData;
};
