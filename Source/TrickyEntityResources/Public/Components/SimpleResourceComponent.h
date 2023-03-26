// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "SimpleEntityResource.h"
#include "Components/ActorComponent.h"
#include "SimpleResourceComponent.generated.h"

/**
 * A component which handles creating and controlling one SimpleEntityResource object.
 */
UCLASS(Blueprintable, ClassGroup=(TrickyEntityResources), meta=(BlueprintSpawnableComponent))
class TRICKYENTITYRESOURCES_API USimpleResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USimpleResourceComponent();

protected:
	virtual void InitializeComponent() override;
	
public:
	/**
	 * Called when Value was successfully decreased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleResourceComponent")
	FOnSimpleResourceValueChangedSignature OnValueDecreased;

	/**
	 * Called when Value was successfully increased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleResourceComponent")
	FOnSimpleResourceValueChangedSignature OnValueIncreased;

	/**
	 * Called when Value reached zero.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleResourceComponent")
	FOnSimpleResourceZeroValueSignature OnValueZero;
	
	/**
	 * Called when MaxValue was successfully decreased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleResourceComponent")
	FOnSimpleResourceValueChangedSignature OnMaxValueDecreased;

	/**
	 * Called when MaxValue was successfully increased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleResourceComponent")
	FOnSimpleResourceValueChangedSignature OnMaxValueIncreased;
	
	/**
	 * Decreases value.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleResourceComponent")
	bool DecreaseValue(const int32 Amount);

	/**
	 * Increases value. If ClampToMax == true, it'll be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleResourceComponent")
	bool IncreaseValue(const int32 Amount, const bool bClampToMax = true);

	/**
	 * Decreases MaxValue. If ClampValue == true and Value > MaxValue, Value will be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleResourceComponent")
	bool DecreaseMaxValue(int32 Amount, const bool bClampValue = true);
	
	/**
	 * Increases MaxValue. If ClampValue == true and Value < MaxValue, Value will be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleResourceComponent")
	bool IncreaseMaxValue(int32 Amount, const bool bClampValue = false);

	/**
	 * Returns Value;
	 */
	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|SimpleResourceComponent")
	int32 GetValue() const;

	/**
	 * Returns MaxValue;
	 */
	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|SimpleResourceComponent")
	int32 GetMaxValue() const;
	
	/**
	 * Returns normalised Value.
	 */
	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|SimpleResourceComponent")
	float GetNormalisedValue() const;
	
private:
	UPROPERTY()
	TObjectPtr<USimpleEntityResource> ResourceObject = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Resource", meta=(AllowPrivateAccess))
	FSimpleResourceData ResourceData;

	UFUNCTION()
	void HandleValueDecrease(const int32 NewValue, const int32 Amount);
	
	UFUNCTION()
	void HandleValueIncrease(const int32 NewValue, const int32 Amount);

	UFUNCTION()
	void HandleValueZero();

	UFUNCTION()
	void HandleMaxValueDecrease(const int32 NewMaxValue, const int32 Amount);

	UFUNCTION()
	void HandleMaxValueIncrease(const int32 NewMaxValue, const int32 Amount);
};
