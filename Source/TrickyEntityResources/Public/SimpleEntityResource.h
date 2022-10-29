// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SimpleEntityResource.generated.h"

USTRUCT(BlueprintType)
struct FSimpleResourceData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="SimpleEntityResource")
	int32 Value = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SimpleEntityResource", meta=(ClampMin="0"))
	int32 MaxValue = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SimpleEntityResource")
	bool bCustomInitialValue = false;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="SimpleEntityResource",
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

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleEntityResource")
	FOnSimpleResourceValueDecreasedSignature OnValueDecreased;

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleEntityResource")
	FOnSimpleResourceValueIncreasedSignature OnValueIncreased;

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleEntityResource")
	FOnSimpleResourceZeroValueSignature OnValueZero;

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleEntityResource")
	FOnSimpleResourceMaxValueDecreasedSignature OnMaxValueDecreased;	

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleEntityResource")
	FOnSimpleResourceMaxValueIncreasedSignature OnMaxValueIncreased;
	
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleEntityResource")
	void DecreaseValue(const int32 Amount);

	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleEntityResource")
	void IncreaseValue(const int32 Amount, bool bClampToMax = true);

	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleEntityResource")
	void DecreaseMaxValue(int32 Amount, const bool bClampValue = true);

	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleEntityResource")
	void IncreaseMaxValue(int32 Amount, const bool bClampValue = false);

	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|SimpleEntityResource")
	float GetNormalisedValue() const;

	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|SimpleEntityResource")
	int32 GetValue() const;

	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|SimpleEntityResource")
	int32 GetMaxValue() const;

	void SetResourceData(const FSimpleResourceData& Data);

	void GetResourceData(FSimpleResourceData& Data) const;
	
private:
	UPROPERTY(BlueprintReadOnly, Category="TrickyEntityResources|SimpleEntityResource", meta=(AllowPrivateAccess))
	FSimpleResourceData ResourceData;
};
