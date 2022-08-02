// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"
/**
 *
 */
UCLASS()
class HOMEWORK1_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	void virtual BeginPlay() override;
public:
	AMenuGameMode();
	UPROPERTY(EditAnywhere)
		UUserWidget* WidgetInstance;

	UFUNCTION(BlueprintCallable)
		void MyGameBegin();

	UFUNCTION(BlueprintCallable)
		void MyGameContinue();

	UFUNCTION(BlueprintCallable)
		void MyGameQuit();
};
