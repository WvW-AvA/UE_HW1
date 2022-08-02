// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 *
 */
UCLASS()
class HOMEWORK1_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		int SaveGoldCoinNum = 0;
	UPROPERTY(EditAnywhere)
		int SaveSilverCoinNum = 0;
	UPROPERTY(EditAnywhere)
		int SaveCopperCoinNum = 0;
	UPROPERTY(EditAnywhere)
		int SaveLevel = 0;
};
