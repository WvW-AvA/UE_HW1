// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Coin.h"
#include "Engine.h"
#include "Blueprint/UserWidget.h"
#include "Homework1Character.h"
#include "MyGameInstance.h"
#include "Homework1GameMode.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDiedSignature, ACharacter*, Character);
UCLASS(minimalapi)
class AHomework1GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AHomework1GameMode();
	UPROPERTY(EditAnywhere)
		int TargetCopperNum = 0;
	UPROPERTY(EditAnywhere)
		int TargetSilverNum = 0;
	UPROPERTY(EditAnywhere)
		int TargetGoldNum = 0;
	UFUNCTION(BlueprintCallable)
		int GetTargetCoinNum(ECoinType CoinType);


	const FOnPlayerDiedSignature& GetOnPlayerDied() const { return OnPlayerDied; }
	virtual void RestartPlayer(AController* NewPlayer)override;

	UFUNCTION()
		virtual void PlayerDied(ACharacter* Character);

	UPROPERTY()
		FOnPlayerDiedSignature OnPlayerDied;

	UMyGameInstance* MyGetGameInstance();
	bool CheckIsFullTarget();
	void CheckGoNextLevel();
};
