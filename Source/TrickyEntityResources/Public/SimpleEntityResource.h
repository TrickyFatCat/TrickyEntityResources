// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SimpleEntityResource.generated.h"

USTRUCT(BlueprintType)
struct FSimpleResourceData
{
	GENERATED_BODY()

	/**
	 * Curren value.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="SimpleEntityResource")
	int32 Value = 100;

	/**
	 * Max value.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SimpleEntityResource", meta=(ClampMin="0"))
	int32 MaxValue = 100;

	/**
	 * If true Value = InitialValue, else Value = MaxValue on resource creation.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SimpleEntityResource")
	bool bUseCustomInitialValue = false;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="SimpleEntityResource",
		meta=(EditCondition="bCustomInitialValue", ClampMin="0"))
	int32 InitialValue = 100;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSimpleResourceValueChangedSignature, int32, NewValue, int32, Amount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSimpleResourceZeroValueSignature);

/**
 * A simple version of the entity resource. It doesn't have auto increase/decrease functionality and uses int32. 
 */
UCLASS(NotBlueprintable, BlueprintType)
class TRICKYENTITYRESOURCES_API USimpleEntityResource : public UObject
{
	GENERATED_BODY()

public:
	USimpleEntityResource();

	/**
	 * Called when Value was successfully decreased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleEntityResource")
	FOnSimpleResourceValueChangedSignature OnValueDecreased;

	/**
	 * Called when Value was successfully increased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleEntityResource")
	FOnSimpleResourceValueChangedSignature OnValueIncreased;

	/**
	 * Called when Value reached zero.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleEntityResource")
	FOnSimpleResourceZeroValueSignature OnValueZero;

	/**
	 * Called when MaxValue was successfully decreased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleEntityResource")
	FOnSimpleResourceValueChangedSignature OnMaxValueDecreased;	

	/**
	 * Called when MaxValue was successfully increased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleEntityResource")
	FOnSimpleResourceValueChangedSignature OnMaxValueIncreased;

	/**
	 * Decreases value.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleEntityResource")
	bool DecreaseValue(const int32 Amount);

	/**
	 * Increases value. If ClampToMax == true, it'll be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleEntityResource")
	bool IncreaseValue(const int32 Amount, bool bClampToMax = true);

	/**
	 * Decreases MaxValue. If ClampValue == true and Value > MaxValue, Value will be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleEntityResource")
	bool DecreaseMaxValue(int32 Amount, const bool bClampValue = true);

	/**
	 * Increases MaxValue. If ClampValue == true and Value < MaxValue, Value will be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleEntityResource")
	bool IncreaseMaxValue(int32 Amount, const bool bClampValue = false);

	/**
	 * Returns normalised Value.
	 */
	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|SimpleEntityResource")
	float GetNormalisedValue() const;

	/**
	 * Returns Value;
	 */
	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|SimpleEntityResource")
	int32 GetValue() const;

	/**
	 * Returns MaxValue;
	 */
	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|SimpleEntityResource")
	int32 GetMaxValue() const;

	void SetResourceData(const FSimpleResourceData& Data);

	void GetResourceData(FSimpleResourceData& Data) const;
	
private:
	UPROPERTY(BlueprintReadOnly, Category="TrickyEntityResources|SimpleEntityResource", meta=(AllowPrivateAccess))
	FSimpleResourceData ResourceData;
};
