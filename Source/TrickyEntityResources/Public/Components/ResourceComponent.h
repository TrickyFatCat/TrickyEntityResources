// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "EntityResource.h"
#include "Components/ActorComponent.h"
#include "ResourceComponent.generated.h"


UCLASS(ClassGroup=(TrickyEntityResources), meta=(BlueprintSpawnableComponent))
class TRICKYENTITYRESOURCES_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UResourceComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime,
	                           ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceValueDecreasedSignature OnResourceValueDecreased;

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceValueIncreasedSignature OnResourceValueIncreased;

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceValueZeroSignature OnResourceValueZero;

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceMaxValueDecreasedSignature OnResourceMaxValueDecreased;

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceMaxValueIncreasedSignature OnResourceMaxValueIncreased;

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceAutoDecreaseStartedSignature OnResourceAutoDecreaseStarted;

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceAutoIncreaseStartedSignature OnResourceAutoIncreaseStarted;
	
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceAutoDecreaseStoppedSignature OnResourceAutoDecreaseStopped;

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|ResourceComponent")
	FOnResourceAutoIncreaseStoppedSignature OnResourceAutoIncreaseStopped;
	
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void DecreaseValue(const float Amount) const;

	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void IncreaseValue(const float Amount, const bool bClampToMax = true) const;

	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void DecreaseMaxValue(float Amount, const bool bClampValue = true) const;

	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void IncreaseMaxValue(float Amount, const bool bClampValue = false) const;

	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|ResourceComponent")
	float GetValue() const;

	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|ResourceComponent")
	float GetMaxValue() const;

	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|ResourceComponent")
	float GetNormalisedValue() const;

	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void SetAutoDecreaseEnabled(const bool bIsEnabled);

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

	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void StartAutoDecrease() const;

	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void StartAutoIncrease() const;

	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|ResourceComponent")
	void StopAutoDecrease() const;

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
