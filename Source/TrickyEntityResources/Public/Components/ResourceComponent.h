// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

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
	/**
	 * Called when Value was successfully decreased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceValueChangedSignature OnValueDecreased;

	/**
	 * Called when Value was successfully increased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceValueChangedSignature OnValueIncreased;

	/**
	 * Called when Value has reached zero.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceValueZeroSignature OnValueZero;
	
	/**
	 * Called when MaxValue was successfully decreased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceValueChangedSignature OnMaxValueDecreased;
	
	/**
	 * Called when MaxValue was successfully increased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceValueChangedSignature OnMaxValueIncreased;

	/**
	 * Called when auto decrease started.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceAutoChangeToggleSignature OnAutoDecreaseStarted;

	/**
	 * Called when auto increase started.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceAutoChangeToggleSignature OnAutoIncreaseStarted;
	
	/**
	 * Called when auto decrease stopped.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceAutoChangeToggleSignature OnAutoDecreaseStopped;

	/**
	 * Called when auto increase stopped.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceAutoChangeToggleSignature OnAutoIncreaseStopped;
	
	/**
	 * Decreases Value and clamps it to zero.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	bool DecreaseValue(const float Amount);

	/** 
	 * Increases Value. If ClampToMax == true, the Value will be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	bool IncreaseValue(const float Amount, const bool bClampToMax = true);

	/**
	 * Decreases MaxValue. If ClampValue == true and Value > MaxValue, Value will be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	bool DecreaseMaxValue(float Amount, const bool bClampValue = true);

	/**
	 * Increases MaxValue. If ClampValue == true and Value < MaxValue, Value will be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	bool IncreaseMaxValue(float Amount, const bool bClampValue = false);

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
	bool StartAutoDecrease() const;

	/**
	 * Starts auto increase.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	bool StartAutoIncrease() const;

	/**
	 * Stops auto decrease.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	bool StopAutoDecrease() const;

	/**
	 * Stops auto increase.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	bool StopAutoIncrease() const;
private:
	UPROPERTY()
	TObjectPtr<UEntityResource> ResourceObject = nullptr;

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
	void HandleValueDecrease(const float NewValue, const float Amount);

	UFUNCTION()
	void HandleValueIncrease(const float NewValue, const float Amount);

	UFUNCTION()
	void HandleValueZero();

	UFUNCTION()
	void HandleMaxValueDecrease(const float NewValue, const float Amount);

	UFUNCTION()
	void HandleMaxValueIncrease(const float NewValue, const float Amount);

	UFUNCTION()
	void HandleAutoDecreaseStart();

	UFUNCTION()
	void HandleAutoIncreaseStart();

	UFUNCTION()
	void HandleAutoDecreaseStop();

	UFUNCTION()
	void HandleAutoIncreaseStop();
};
