// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

void AMenuGameMode::BeginPlay() {
	if (WidgetInstance != nullptr) {
		WidgetInstance->RemoveFromViewport();
		WidgetInstance = nullptr;
	}
	TSubclassOf<UUserWidget> Meum_Finder = LoadClass<UUserWidget>(
		nullptr, TEXT("/Game/ThirdPersonCPP/Blueprints/MeumUI.MeumUI_C"));
	if (Meum_Finder) {
		auto PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
		if (PC != nullptr) {
			WidgetInstance = CreateWidget(PC, Meum_Finder);
			if (WidgetInstance) {
				WidgetInstance->AddToViewport();
			}
			PC->bShowMouseCursor = true;
			WidgetInstance->SetCursor(PC->CurrentMouseCursor);
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("NotFindAssest"));
	}
}
AMenuGameMode::AMenuGameMode() {}
void AMenuGameMode::MyGameBegin() {
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (GameInstance) {
		GameInstance->CreateNewSaveInstance("DefaultSave");
		GameInstance->LoadLevel(GameInstance->CurrentLevel);
	}
}
void AMenuGameMode::MyGameContinue() {
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (GameInstance) {
		GameInstance->MyLoadValue("DefaultSave");
		GameInstance->LoadLevel(GameInstance->CurrentLevel);
	}
}
void AMenuGameMode::MyGameQuit() {}
