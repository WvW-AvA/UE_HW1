// Copyright Epic Games, Inc. All Rights Reserved.

#include "Homework1GameMode.h"

#include "Homework1Character.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AHomework1GameMode::AHomework1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<AHomework1Character> CharacterBP(
		TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_C"));
	if (CharacterBP.Succeeded()) {
		DefaultPawnClass = CharacterBP.Class;
	}
}

void AHomework1GameMode::BeginPlay()
{
	Super::BeginPlay();
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	AHomework1Character* character = Cast<AHomework1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (GameInstance && character)
	{
		TargetCopperNum = GameInstance->LevelMission[GameInstance->CurrentLevel].TargetCopperNum;
		TargetSilverNum = GameInstance->LevelMission[GameInstance->CurrentLevel].TargetSilverNum;
		TargetGoldNum = GameInstance->LevelMission[GameInstance->CurrentLevel].TargetGoldNum;
	}
	if (!OnPlayerDied.IsBound())
	{
		OnPlayerDied.AddDynamic(this, &AHomework1GameMode::PlayerDied);

	}
}

int AHomework1GameMode::GetTargetCoinNum(ECoinType CoinType)
{
	if (CoinType == ECoinType::Copper) return TargetCopperNum;
	if (CoinType == ECoinType::Silver) return TargetSilverNum;
	if (CoinType == ECoinType::Gold) return TargetGoldNum;
	return 0;
}
void AHomework1GameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);
}
void AHomework1GameMode::PlayerDied(ACharacter* Character)
{
	AController* CharacterController = Character->GetController();
	RestartPlayer(CharacterController);
}
bool AHomework1GameMode::CheckIsFullTarget()
{
	AHomework1Character* player = Cast<AHomework1Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player->m_CopperCoinNumber >= TargetCopperNum &&
		player->m_SilverCoinNumber >= TargetSilverNum &&
		player->m_GoldCoinNumber >= TargetGoldNum) {
		return true;
	}
	return false;
}
void AHomework1GameMode::CheckGoNextLevel()
{
	if (CheckIsFullTarget())
	{
		UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			GameInstance->LoadNextLevel();
		}
	}
}
