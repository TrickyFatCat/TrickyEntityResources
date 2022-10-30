// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "SimpleEntityResource.h"
#include "Components/ActorComponent.h"
#include "SimpleResourceComponent.generated.h"

/**
 *
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
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleResourceComponent")
	FOnSimpleResourceValueDecreasedSignature OnResourceValueDecreased;

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleResourceComponent")
	FOnSimpleResourceValueIncreasedSignature OnResourceValueIncreased;

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleResourceComponent")
	FOnSimpleResourceZeroValueSignature OnResourceValueZero;
	
	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleResourceComponent")
	FOnSimpleResourceMaxValueDecreasedSignature OnResourceMaxValueDecreased;

	UPROPERTY(BlueprintAssignable, Category="TrickyEntityResources|SimpleResourceComponent")
	FOnSimpleResourceMaxValueIncreasedSignature OnResourceMaxValueIncreased;
	
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleResourceComponent")
	void DecreaseValue(const int32 Amount);

	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleResourceComponent")
	void IncreaseValue(const int32 Amount, const bool bClampToMax = true);

	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleResourceComponent")
	void DecreaseMaxValue(int32 Amount, const bool bClampValue = true);
	
	UFUNCTION(BlueprintCallable, Category="TrickyEntityResources|SimpleResourceComponent")
	void IncreaseMaxValue(int32 Amount, const bool bClampValue = false);

	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|SimpleResourceComponent")
	int32 GetValue() const;

	UFUNCTION(BlueprintPure, Category="TrickyEntityResources|SimpleResourceComponent")
	int32 GetMaxValue() const;
	
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
