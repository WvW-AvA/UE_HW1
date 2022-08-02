// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Homework1Character.h"
#include "MySaveGame.h"
#include "MyGameInstance.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct FLevelMission
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere)
		FString LevelName;
	UPROPERTY(EditAnywhere)
		int TargetCopperNum = 0;
	UPROPERTY(EditAnywhere)
		int TargetSilverNum = 0;
	UPROPERTY(EditAnywhere)
		int TargetGoldNum = 0;
};

class AHomework1GameMode;

UCLASS()
class HOMEWORK1_API UMyGameInstance : public UGameInstance {
	GENERATED_BODY()
public:
	UMyGameInstance();
	UPROPERTY(EditAnywhere)
		int CurrentLevel = 0;
	UPROPERTY(EditAnywhere)
		TArray<FLevelMission> LevelMission;

	UPROPERTY(EditAnywhere)
		FString CurrSlotName;


	UPROPERTY(EditAnywhere)
		UMySaveGame* GameSaveInstance;

	void virtual Init() override;
	void GameModeInit(AHomework1GameMode* GameMode);
	void CharacterInit(AHomework1Character* character);
	void LoadLevel(int LevelIndex);
	UFUNCTION(BlueprintCallable)
		void MyLoadValue(FString SlotName);
	UFUNCTION(BlueprintCallable)
		void CreateNewSaveInstance(FString SlotName);
	void LoadNextLevel();
	void MySaveGame();
};
