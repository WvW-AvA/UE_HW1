// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Containers/UnrealString.h"
#include "Homework1GameMode.h"
#include "Kismet/GameplayStatics.h"

UMyGameInstance::UMyGameInstance() {
}

void UMyGameInstance::Init()
{
	MyLoadValue("DefaultSave");
}

void UMyGameInstance::GameModeInit(AHomework1GameMode* GameMode) {
	GameMode->TargetCopperNum = LevelMission[CurrentLevel].TargetCopperNum;
	GameMode->TargetSilverNum = LevelMission[CurrentLevel].TargetSilverNum;
	GameMode->TargetGoldNum = LevelMission[CurrentLevel].TargetGoldNum;
}

void UMyGameInstance::CharacterInit(AHomework1Character* character) {
	character->m_SilverCoinNumber = GameSaveInstance->SaveSilverCoinNum;
	character->m_CopperCoinNumber = GameSaveInstance->SaveCopperCoinNum;
	character->m_GoldCoinNumber = GameSaveInstance->SaveGoldCoinNum;
}

void UMyGameInstance::CreateNewSaveInstance(FString SlotName) {
	GameSaveInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	CurrSlotName = SlotName;
	CurrentLevel = GameSaveInstance->SaveLevel;
	UGameplayStatics::SaveGameToSlot(GameSaveInstance, *CurrSlotName, 0); // 保存游戏
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, "Create new Save Slot! Instance Name:" + GameSaveInstance->GetName());
}
void UMyGameInstance::LoadLevel(int LevelIndex) {
	if (LevelIndex >= LevelMission.Num()) {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, *FString::Printf(TEXT("Not Level Index %d"), LevelIndex));
		return;
	}
	GameSaveInstance->SaveLevel = LevelIndex;
	MySaveGame();
	UGameplayStatics::OpenLevel(GetWorld(), *LevelMission[LevelIndex].LevelName, false);
}

void UMyGameInstance::MyLoadValue(FString SlotName) {
	// 先检测是否有存档
	if (UGameplayStatics::DoesSaveGameExist(*SlotName, 0))
	{
		GameSaveInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(*SlotName, 0));
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, "Load Save Slot:" + SlotName + "Instance Name:" + GameSaveInstance->GetName());
	}
	else
	{
		GameSaveInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	}
	CurrSlotName = SlotName;
	CurrentLevel = GameSaveInstance->SaveLevel;
}

void UMyGameInstance::LoadNextLevel() {
	CurrentLevel++;
	LoadLevel(CurrentLevel);
}

void UMyGameInstance::MySaveGame()
{
	AHomework1Character* HWCharacter = Cast<AHomework1Character>(
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (HWCharacter) {
		GameSaveInstance->SaveCopperCoinNum = HWCharacter->m_CopperCoinNumber;
		GameSaveInstance->SaveGoldCoinNum = HWCharacter->m_SilverCoinNumber;
		GameSaveInstance->SaveSilverCoinNum = HWCharacter->m_GoldCoinNumber;
	}
	UGameplayStatics::SaveGameToSlot(GameSaveInstance, *CurrSlotName, 0); // 保存游戏
}
