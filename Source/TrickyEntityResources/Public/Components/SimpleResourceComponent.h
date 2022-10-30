// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "SimpleEntityResource.h"
#include "Components/ActorComponent.h"
#include "SimpleResourceComponent.generated.h"

/**
 * A component which handles creating and controlling one SimpleEntityResource object.
 */
UCLASS(ClassGroup=(TrickyEntityResources), meta=(BlueprintSpawnableComponent))
class TRICKYENTITYRESOURCES_API USimpleResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USimpleResourceComponent();

protected:
	virtual void BeginPlay() override;

public:
	/**
	 * Called when Value was successfully decreased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleResourceComponent")
	FOnSimpleResourceValueDecreasedSignature OnResourceValueDecreased;

	/**
	 * Called when Value was successfully increased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleResourceComponent")
	FOnSimpleResourceValueIncreasedSignature OnResourceValueIncreased;

	/**
	 * Called when Value reached zero.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleResourceComponent")
	FOnSimpleResourceZeroValueSignature OnResourceValueZero;
	
	/**
	 * Called when MaxValue was successfully decreased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleResourceComponent")
	FOnSimpleResourceMaxValueDecreasedSignature OnResourceMaxValueDecreased;

	/**
	 * Called when MaxValue was successfully increased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleResourceComponent")
	FOnSimpleResourceMaxValueIncreasedSignature OnResourceMaxValueIncreased;
	
	/**
	 * Decreases value.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleResourceComponent")
	void DecreaseValue(const int32 Amount);

	/**
	 * Increases value. If ClampToMax == true, it'll be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleResourceComponent")
	void IncreaseValue(const int32 Amount, const bool bClampToMax = true);

	/**
	 * Decreases MaxValue. If ClampValue == true and Value > MaxValue, Value will be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleResourceComponent")
	void DecreaseMaxValue(int32 Amount, const bool bClampValue = true);
	
	/**
	 * Increases MaxValue. If ClampValue == true and Value < MaxValue, Value will be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleResourceComponent")
	void IncreaseMaxValue(int32 Amount, const bool bClampValue = false);

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
	USimpleEntityResource* ResourceObject = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Resource", meta=(AllowPrivateAccess))
	FSimpleResourceData ResourceData;

	UFUNCTION()
	void OnValueDecreased(const int32 NewValue, const int32 Amount);
	
	UFUNCTION()
	void OnValueIncreased(const int32 NewValue, const int32 Amount);

	UFUNCTION()
	void OnValueZero();

	UFUNCTION()
	void OnMaxValueDecreased(const int32 NewMaxValue, const int32 Amount);

	UFUNCTION()
	void OnMaxValueIncreased(const int32 NewMaxValue, const int32 Amount);
};
