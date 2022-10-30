// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TimerManager.h"
#include "EntityResource.generated.h"

USTRUCT(BlueprintType)
struct FResourceAutoData
{
	GENERATED_BODY()
	/**
	 * Toggles auto increase/decrease.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EntityResource")
	bool bIsEnabled = false;

	/**
	 * The amount of the resource on which current value is increased/decreased every tick.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="EntityResource",
		meta=(EditCondition="bIsEnabled", ClampMin="0.0"))
	float Power = 1.f;

	/**
	 * How often the resource will increase/decrease automatically per second.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="EntityResource",
		meta=(EditCondition="bIsEnabled", ClampMin="0.0"))
	float Frequency = 1.f;

	/**
	 * The relative value of resource after which auto increase/decrease starts.
	 * For increase current Value <= Threshold.
	 * For decrease current Value >= Threshold.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="EntityResource",
		meta=(EditCondition="bIsEnabled", ClampMin="0.0", ClampMax="1.0"))
	float Threshold = 1.f;

	/**
	 * A delay time after which auto increase/decrease starts. If == 0, they start immediately.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="EntityResource",
		meta=(EditCondition="bIsEnabled", ClampMin="0.0"))
	float StartDelay = 1.f;

	/**
	 * If true, auto increase/decrease will be stopped if Value reached zero.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EntityResource", meta=(EditCondition="bIsEnabled"))
	bool bDisableOnZeroValue = false;

	UPROPERTY()
	float TickDelay = 1.f; // Time between ticks in seconds.
	
	static void CalculateTickDelay(FResourceAutoData& Data);
};

USTRUCT(BlueprintType)
struct FResourceData
{
	GENERATED_BODY()

	/**
	 * Current Value of the resource.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="EntityResource")
	float Value = 100.f;

	/**
	 * Maximum Value of the resource.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EntityResource", meta=(ClampMin="0.0"))
	float MaxValue = 100.f;

	/**
	 * If true Value = ValueInitial, else Value = ValueMax on resource creation.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EntityResource")
	bool bUseCustomInitialValue = false;

	/**
	 * Determines custom Value.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="EntityResource",
		meta=(EditCondition="bUseCustomInitialValue", ClampMin="0.0"))
	float InitialValue = 100.f;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResourceValueDecreasedSignature, float, NewValue, float, Amount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResourceValueIncreasedSignature, float, NewValue, float, Amount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourceValueZeroSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResourceMaxValueDecreasedSignature, float, NewValue, float, Amount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResourceMaxValueIncreasedSignature, float, NewMaxValue, float, Amount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourceAutoDecreaseStartedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourceAutoIncreaseStartedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourceAutoDecreaseStoppedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourceAutoIncreaseStoppedSignature);

/**
 * Main entity resource which can automatically increase and decrease current value.
 */
UCLASS(NotBlueprintable, BlueprintType)
class TRICKYENTITYRESOURCES_API UEntityResource : public UObject
{
	GENERATED_BODY()

public:
	UEntityResource();
	
	/**
	 * Called when Value was successfully decreased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|EntityResource")
	FOnResourceValueDecreasedSignature OnValueDecreased;

	/**
	 * Called when Value was successfully increased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|EntityResource")
	FOnResourceValueIncreasedSignature OnValueIncreased;

	/**
	 * Called when Value has reached zero.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|EntityResource")
	FOnResourceValueZeroSignature OnValueZero;

	/**
	 * Called when MaxValue was successfully decreased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|EntityResource")
	FOnResourceMaxValueDecreasedSignature OnMaxValueDecreased;

	/**
	 * Called when MaxValue was successfully increased.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|EntityResource")
	FOnResourceMaxValueIncreasedSignature OnMaxValueIncreased;

	/**
	 * Decreases Value and clamps it to zero.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|EntityResource")
	void DecreaseValue(const float Amount);

	/** 
	 * Increases Value. If ClampToMax == true, the Value will be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|EntityResource")
	void IncreaseValue(const float Amount, const bool bClampToMax = true);

	/**
	 * Decreases MaxValue. If ClampValue == true and Value > MaxValue, Value will be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|EntityResource")
	void DecreaseMaxValue(float Amount, const bool bClampValue = true);

	/**
	 * Increases MaxValue. If ClampValue == true and Value < MaxValue, Value will be clamped to MaxValue.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|EntityResource")
	void IncreaseMaxValue(float Amount, const bool bClampValue = false);

	/**
	 * Returns normalised value of the resource.
	 */
	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|EntityResource")
	float GetNormalisedValue() const;

	/**
	 * Returns current value.
	 */
	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|EntityResource")
	float GetValue() const;

	/**
	 * Returns max value.
	 */
	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|EntityResource")
	float GetMaxValue() const;
	
	void SetResourceData(const FResourceData& Data);

	void GetResourceData(FResourceData& Data) const;

private:
	UPROPERTY(BlueprintReadOnly, Category="EntityResource", meta=(AllowPrivateAccess))
	FResourceData ResourceData;

public:
	/**
	 * Called when auto decrease started.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|EntityResource")
	FOnResourceAutoDecreaseStartedSignature OnAutoDecreaseStarted;

	/**
	 * Called when auto increase started.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|EntityResource")
	FOnResourceAutoIncreaseStartedSignature OnAutoIncreaseStarted;

	/**
	 * Called when auto decrease stopped.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|EntityResource")
	FOnResourceAutoDecreaseStoppedSignature OnAutoDecreaseStopped;

	/**
	 * Called when auto increase stopped.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|EntityResource")
	FOnResourceAutoIncreaseStoppedSignature OnAutoIncreaseStopped;

	/**
	 * Toggles auto increase.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|EntityResource")
	void SetAutoIncreaseEnabled(const bool bIsEnabled);

	/**
	 * Toggles auto decrease.
	 */
	UFUNCTION(BlueprintCallable, Category="TriciyEntityResources|EntityResource")
	void SetAutoDecreaseEnabled(const bool bIsEnabled);

	/**
	 * Sets AutoIncreaseData.
	 */
	UFUNCTION(BlueprintCallable, Category="TriciyEntityResources|EntityResource")
	void SetAutoIncreaseData(const FResourceAutoData& Data);

	/**
	 * Sets AutoDecreaseData;
	 */
	UFUNCTION(BlueprintCallable, Category="TriciyEntityResources|EntityResource")
	void SetAutoDecreaseData(const FResourceAutoData& Data);

	/**
	 * Returns AutoIncreaseData by reference.
	 */
	UFUNCTION(BlueprintCallable, Category="TriciyEntityResources|EntityResource")
	void GetAutoIncreaseData(FResourceAutoData& Data);

	/**
	 * Returns AutoDecreaseData by reference.
	 */
	UFUNCTION(BlueprintCallable, Category="TriciyEntityResources|EntityResource")
	void GetAutoDecreaseData(FResourceAutoData& Data);

	/**
	 * Starts auto decrease.
	 */
	UFUNCTION(BlueprintCallable, Category="TriciyEntityResources|EntityResource")
	void StartAutoDecrease();

	/**
	 * Starts auto increase.
	 */
	UFUNCTION(BlueprintCallable, Category="TriciyEntityResources|EntityResource")
	void StartAutoIncrease();

	/**
	 * Stops auto decrease.
	 */
	UFUNCTION(BlueprintCallable, Category="TriciyEntityResources|EntityResource")
	void StopAutoDecrease();

	/**
	 * Stops auto increase.
	 */
	UFUNCTION(BlueprintCallable, Category="TriciyEntityResources|EntityResource")
	void StopAutoIncrease();
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EntityResource", meta=(AllowPrivateAccess))
	FResourceAutoData AutoIncreaseData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EntityResource", meta=(AllowPrivateAccess))
	FResourceAutoData AutoDecreaseData;

	bool IsTimerActive(const FTimerHandle& Timer) const;
	
	void StopTimer(FTimerHandle& TimerHandle) const;
	
	FTimerHandle AutoIncreaseTimer;
	
	void ProcessAutoIncrease();

	FTimerHandle AutoDecreaseTimer;

	void ProcessAutoDecrease();
};
