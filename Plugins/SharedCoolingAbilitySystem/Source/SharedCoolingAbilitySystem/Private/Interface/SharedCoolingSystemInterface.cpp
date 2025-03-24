// Fill out your copyright notice in the Description page of Project Settings.

#include "Interface/SharedCoolingSystemInterface.h"
//#include "Ability/GA_SharedCoolingBase.h"
#include "AbilitySystemComponent.h"


void ISharedCoolingSystemInterface::RegisterSharedCoolingAbilities(const FGameplayTag& InTag, const FGameplayAbilitySpecHandle& GASpecHandle)
{
	TArray<FGameplayAbilitySpecHandle>& SpecHandleArrayRef = SharedCoolingAbilities.FindOrAdd(InTag);
	SpecHandleArrayRef.Add(GASpecHandle);
}

void ISharedCoolingSystemInterface::CancelSharedCoolingAbilities(const FGameplayTag& InTag, const FGameplayAbilitySpecHandle& GASpecHandle)
{
	TArray<FGameplayAbilitySpecHandle>* SpecHandleArrayPtr = SharedCoolingAbilities.Find(InTag);
	if (SpecHandleArrayPtr)
	{
		if (FGameplayAbilitySpecHandle* InSpecHandle = SpecHandleArrayPtr->FindByPredicate([&](FGameplayAbilitySpecHandle& SpecHandle) {
			return GASpecHandle == SpecHandle ? true : false;
			}))
		{
			FGameplayAbilitySpecHandle TempSpecHandle = *InSpecHandle;
			SpecHandleArrayPtr->Remove(TempSpecHandle);
		}
	}
}

void ISharedCoolingSystemInterface::NotifyAllSharedAbilityRefreshCoolTime(FGameplayTagContainer SharedCoolingGameplayEffectTag, FGameplayAbilitySpecHandle InstigatorHandle /*= FGameplayAbilitySpecHandle()*/)
{
 	for (TArray<FGameplayTag>::TConstIterator Ite = SharedCoolingGameplayEffectTag.CreateConstIterator(); Ite; Ite++)
 	{
		if (TArray<FGameplayAbilitySpecHandle>* SpecHandleArrayPtr = SharedCoolingAbilities.Find(*Ite))
		{
			for (const FGameplayAbilitySpecHandle& Handle : *SpecHandleArrayPtr)
			{
				check(Cast<UAbilitySystemComponent>(this) && "It must be inherited from the UAbilitySystemComponent class.");
				FGameplayAbilitySpec* Spec = (Cast<UAbilitySystemComponent>(this))->FindAbilitySpecFromHandle(Handle);
				//UGA_SharedCoolingBase* GA = Cast<UGA_SharedCoolingBase>(Spec->GetPrimaryInstance());
				//GA->RefreshSharedCoolAbilityTime(InstigatorHandle);
			}
		}
 	}
}