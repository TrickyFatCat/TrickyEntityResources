// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "EntityResource.h"
#include "Components/ActorComponent.h"
#include "ResourceComponent.generated.h"

/**
 * A component which handles creating and controlling one EntityResource object.
 */
UCLASS(Blueprintable, ClassGroup=(TrickyEntityResources), meta=(BlueprintSpawnableComponent))
class TRICKYENTITYRESOURCES_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UResourceComponent();

protected:
	virtual void InitializeComponent() override;

public:
	virtual void TickComponent(float DeltaTime,
	                           ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Called when Value was successfully decreased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceValueDecreasedSignature OnResourceValueDecreased;

	/**
	 * Called when Value was successfully increased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceValueIncreasedSignature OnResourceValueIncreased;

	/**
	 * Called when Value has reached zero.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceValueZeroSignature OnResourceValueZero;
	
	/**
	 * Called when MaxValue was successfully decreased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceMaxValueDecreasedSignature OnResourceMaxValueDecreased;
	
	/**
	 * Called when MaxValue was successfully increased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceMaxValueIncreasedSignature OnResourceMaxValueIncreased;

	/**
	 * Called when auto decrease started.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceAutoDecreaseStartedSignature OnResourceAutoDecreaseStarted;

	/**
	 * Called when auto increase started.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceAutoIncreaseStartedSignature OnResourceAutoIncreaseStarted;
	
	/**
	 * Called when auto decrease stopped.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceAutoDecreaseStoppedSignature OnResourceAutoDecreaseStopped;

	/**
	 * Called when auto increase stopped.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceAutoIncreaseStoppedSignature OnResourceAutoIncreaseStopped;
	
	/**
	 * Decreases Value and clamps it to zero.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void DecreaseValue(const float Amount) const;

	/** 
	 * Increases Value. If ClampToMax == true, the Value will be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void IncreaseValue(const float Amount, const bool bClampToMax = true) const;

	/**
	 * Decreases MaxValue. If ClampValue == true and Value > MaxValue, Value will be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void DecreaseMaxValue(float Amount, const bool bClampValue = true) const;

	/**
	 * Increases MaxValue. If ClampValue == true and Value < MaxValue, Value will be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void IncreaseMaxValue(float Amount, const bool bClampValue = false) const;

	/**
	 * Returns value.
	 */
	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|ResourceComponent")
	float GetValue() const;

	/**
	 * Returns max value
	 */
	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|ResourceComponent")
	float GetMaxValue() const;

	/**
	 * Returns normalised value of the resource.
	 */
	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|ResourceComponent")
	float GetNormalisedValue() const;

	/**
	 * Toggles auto decrease.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void SetAutoDecreaseEnabled(const bool bIsEnabled);

	/**
	 * Toggles auto increase.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void SetAutoIncreaseEnabled(const bool bIsEnabled);

	UFUNCTION(BlueprintGetter, Category="TrickyEntityResources|ResourceComponent")
	FResourceAutoData GetAutoDecreaseData() const;

	UFUNCTION(BlueprintGetter, Category="TrickyEntityResources|ResourceComponent")
	FResourceAutoData GetAutoIncreaseData() const;

	UFUNCTION(BlueprintSetter, Category="TrickyEntityResources|ResourceComponent")
	void SetAutoDecreaseData(const FResourceAutoData& Data);

	UFUNCTION(BlueprintSetter, Category="TrickyEntityResources|ResourceComponent")
	void SetAutoIncreaseData(const FResourceAutoData& Data);

	/**
	 * Starts auto decrease.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void StartAutoDecrease() const;

	/**
	 * Starts auto increase.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void StartAutoIncrease() const;

	/**
	 * Stops auto decrease.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void StopAutoDecrease() const;

	/**
	 * Stops auto increase.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void StopAutoIncrease() const;
private:
	UPROPERTY()
	UEntityResource* ResourceObject = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Resource", meta=(AllowPrivateAccess))
	FResourceData ResourceData;

	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetAutoDecreaseData,
		BlueprintSetter=SetAutoDecreaseData,
		Category="Resource",
		meta=(AllowPrivateAccess))
	FResourceAutoData AutoDecreaseData;

	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetAutoIncreaseData,
		BlueprintSetter=SetAutoIncreaseData,
		Category="Resource",
		meta=(AllowPrivateAccess))
	FResourceAutoData AutoIncreaseData;

	UFUNCTION()
	void OnValueDecreased(const float NewValue, const float Amount);

	UFUNCTION()
	void OnValueIncreased(const float NewValue, const float Amount);

	UFUNCTION()
	void OnValueZero();

	UFUNCTION()
	void OnMaxValueDecreased(const float NewValue, const float Amount);

	UFUNCTION()
	void OnMaxValueIncreased(const float NewValue, const float Amount);

	UFUNCTION()
	void OnAutoDecreaseStarted();

	UFUNCTION()
	void OnAutoIncreaseStarted();

	UFUNCTION()
	void OnAutoDecreaseStopped();

	UFUNCTION()
	void OnAutoIncreaseStopped();
};
