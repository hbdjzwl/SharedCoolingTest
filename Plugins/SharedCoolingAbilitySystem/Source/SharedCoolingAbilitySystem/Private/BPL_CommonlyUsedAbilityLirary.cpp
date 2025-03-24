// Fill out your copyright notice in the Description page of Project Settings.


#include "BPL_CommonlyUsedAbilityLirary.h"
#include "AbilitySystemComponent.h"

FString UBPL_CommonlyUsedAbilityLirary::Conv_ActiveGameplayEffectHandleToString(const FActiveGameplayEffectHandle& AGEHandle)
{
	return AGEHandle.ToString();
}

bool UBPL_CommonlyUsedAbilityLirary::EqualEqual_GameplayAbilitySpecHandle(const FGameplayAbilitySpecHandle& A, const FGameplayAbilitySpecHandle& B)
{
	return A==B;
}

FString UBPL_CommonlyUsedAbilityLirary::Conv_GameplayAbilitySpecHandleToString(const FGameplayAbilitySpecHandle& GameplayAbilitySpecHandle)
{
	return GameplayAbilitySpecHandle.ToString();
}

FGameplayAbilitySpecHandle UBPL_CommonlyUsedAbilityLirary::K2_GiveAbility(UAbilitySystemComponent* AbilitySystemComponent, TSubclassOf<UGameplayAbility> InAbilityClass, int32 Level, int32 InputID /*= -1 */)
{
	return AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(InAbilityClass, Level, InputID));

}

bool UBPL_CommonlyUsedAbilityLirary::TryActivateAbilityByHandle(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAbilitySpecHandle& AbilityToActivate, bool bAllowRemoteActivation /*= true*/)
{
	return AbilitySystemComponent->TryActivateAbility(AbilityToActivate, bAllowRemoteActivation);

}

void UBPL_CommonlyUsedAbilityLirary::K2_ClearAbility(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAbilitySpecHandle& Handle, bool InRemoveAbilityOnEnd)
{
	if (InRemoveAbilityOnEnd)
	{
		AbilitySystemComponent->SetRemoveAbilityOnEnd(Handle);
	}
	else
	{
		AbilitySystemComponent->ClearAbility(Handle);
	}
}

void UBPL_CommonlyUsedAbilityLirary::ModifyGameplayEffectRemainingTimeByClass(UAbilitySystemComponent* AbilitySystemComponent, const TSubclassOf<UGameplayEffect> QueryGE, float ModifiedIncrement)
{
	if (AbilitySystemComponent)
	{
		FGameplayEffectQuery Querys;
		Querys.EffectDefinition = QueryGE;
		TArray<FActiveGameplayEffectHandle> Handles = AbilitySystemComponent->GetActiveEffects(Querys);

		for (const FActiveGameplayEffectHandle& Handle : Handles)
		{
			UBPL_CommonlyUsedAbilityLirary::ModifyGameplayEffectRemainingTimeByHandle(AbilitySystemComponent, Handle, ModifiedIncrement);
		}
	}
}

void UBPL_CommonlyUsedAbilityLirary::ModifyGameplayEffectRemainingTimeByHandle(UAbilitySystemComponent* AbilitySystemComponent, const FActiveGameplayEffectHandle& AGEHandle, float ModifiedIncrement)
{
	if (AbilitySystemComponent && AGEHandle.IsValid())
	{
		if (const FActiveGameplayEffect* Effect = AbilitySystemComponent->GetActiveGameplayEffect(AGEHandle))
		{
			//ÐÞÕýÊ±¼ä
			if ((Effect->GetEndTime() + ModifiedIncrement) < AbilitySystemComponent->GetWorld()->GetTimeSeconds())
			{
				ModifiedIncrement = AbilitySystemComponent->GetWorld()->GetTimeSeconds() - Effect->GetEndTime() + 0.1f;
			}
			AbilitySystemComponent->ModifyActiveEffectStartTime(AGEHandle, ModifiedIncrement);
		}
	}
}

void UBPL_CommonlyUsedAbilityLirary::ModifyGameplayEffectRemainingTimeByTags(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTagContainer Tags, float ModifiedIncrement)
{
	if (AbilitySystemComponent && Tags.IsValid())
	{
		TArray<FActiveGameplayEffectHandle> AllAGEHandle = AbilitySystemComponent->GetActiveEffectsWithAllTags(Tags);
		for (const auto& Handle : AllAGEHandle)
		{
			UBPL_CommonlyUsedAbilityLirary::ModifyGameplayEffectRemainingTimeByHandle(AbilitySystemComponent, Handle, ModifiedIncrement);
		}
	}
}

float UBPL_CommonlyUsedAbilityLirary::GetGameplayEffectDuration(UAbilitySystemComponent* AbilitySystemComponent, const FActiveGameplayEffectHandle& Handle)
{
	return AbilitySystemComponent->GetGameplayEffectDuration(Handle);
}

void UBPL_CommonlyUsedAbilityLirary::GetGameplayEffectStartTimeAndDuration(UAbilitySystemComponent* AbilitySystemComponent, const FActiveGameplayEffectHandle& Handle, float& StartEffectTime, float& Duration)
{
	AbilitySystemComponent->GetGameplayEffectStartTimeAndDuration(Handle, StartEffectTime, Duration);
}

void UBPL_CommonlyUsedAbilityLirary::GetAbilityCooldownTimeRemainingAndDurationByHandle(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAbilitySpecHandle& Handle, float& TimeRemaining, float& CooldownDuration)
{
	if (AbilitySystemComponent)
	{
		if (FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromHandle(Handle))
		{
			if (UGameplayAbility* Ability = AbilitySpec->GetPrimaryInstance())
			{
				const FGameplayAbilityActorInfo& AbilityActorInfo = Ability->GetActorInfo();
				Ability->GetCooldownTimeRemainingAndDuration(Ability->GetCurrentAbilitySpecHandle(), &AbilityActorInfo, TimeRemaining, CooldownDuration);
			}
		}
	}
}

void UBPL_CommonlyUsedAbilityLirary::GetAbilityCooldownTimeRemainingAndDurationByAbility(UAbilitySystemComponent* AbilitySystemComponent, UGameplayAbility* Ability, float& TimeRemaining, float& CooldownDuration)
{
	const FGameplayAbilityActorInfo& AbilityActorInfo = Ability->GetActorInfo();
	Ability->GetCooldownTimeRemainingAndDuration(Ability->GetCurrentAbilitySpecHandle(), &AbilityActorInfo, TimeRemaining, CooldownDuration);
}

UGameplayAbility* UBPL_CommonlyUsedAbilityLirary::GetPrimaryAbilityInstanceFromClass(UAbilitySystemComponent* AbilitySystemComponent, TSubclassOf<UGameplayAbility> InAbilityClass)
{
	if (AbilitySystemComponent)
	{
		if (FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromClass(InAbilityClass))
		{
			return Cast<UGameplayAbility>(AbilitySpec->GetPrimaryInstance());
		}
	}
	return nullptr;
}

UGameplayAbility* UBPL_CommonlyUsedAbilityLirary::GetPrimaryAbilityInstanceFromHandle(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAbilitySpecHandle& Handle)
{
	if (AbilitySystemComponent)
	{
		if (FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromHandle(Handle))
		{
			return Cast<UGameplayAbility>(AbilitySpec->GetPrimaryInstance());
		}
	}
	return nullptr;
}
