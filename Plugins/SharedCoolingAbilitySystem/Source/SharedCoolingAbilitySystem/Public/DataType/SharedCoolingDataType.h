// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "SharedCoolingDataType.generated.h"

#define TAG_EVENT_COOLING_START  FGameplayTag::RequestGameplayTag("Event.Cooling.Start")		//冷却开始
#define TAG_EVENT_COOLING_END    FGameplayTag::RequestGameplayTag("Event.Cooling.End")		//冷却结束

USTRUCT(BlueprintType)
struct SHAREDCOOLINGABILITYSYSTEM_API FSharedCoolingInfo
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
		FGameplayAbilitySpecHandle GASpecHandle;

	UPROPERTY(BlueprintReadOnly)
		FGameplayTag CoolingAssetTag;

	UPROPERTY(BlueprintReadOnly)
		float Remaining;

	UPROPERTY(BlueprintReadOnly)
		float Duration;
};

UCLASS(BlueprintType)
class USharedCoolingInfoObject : public UObject
{
	GENERATED_BODY()
public:
	static USharedCoolingInfoObject* GenerateSharedCoolingInfoObject(FGameplayAbilitySpecHandle InGASpecHandle, FGameplayTag InCoolingAssetTag, float InRemaining, float InDuration);

	void SetSharedCoolingInfo(FGameplayAbilitySpecHandle InGASpecHandle, FGameplayTag InCoolingTag, float InRemaining, float InDuration);
	UFUNCTION(BlueprintPure)
	FSharedCoolingInfo GetSharedCoolingInfo() const;
private:
	FSharedCoolingInfo SharedCoolingInfo;
};


struct SHAREDCOOLINGABILITYSYSTEM_API FSharedCoolingNativeTags : public FGameplayTagNativeAdder
{
	/*
		有些不喜欢用FGameplayTag::RequestGameplayTag去访问Tag。
		所以提供直接方式访问:
			FSharedCoolingNativeTags::Get().CoolingStart
			FSharedCoolingNativeTags::Get().CoolingEnd
	*/
	FGameplayTag CoolingStart;
	FGameplayTag CoolingEnd;

	virtual void AddTags() override
	{
		UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

		CoolingStart = Manager.AddNativeGameplayTag(TEXT("Event.Cooling.Start"));
		CoolingEnd = Manager.AddNativeGameplayTag(TEXT("Event.Cooling.End"));
	}

	FORCEINLINE static const FSharedCoolingNativeTags& Get() { return NativeTags; }
private:
	static FSharedCoolingNativeTags NativeTags;
};
