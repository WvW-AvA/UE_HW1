// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UENUM(BlueprintType)
enum class ECoinType:uint8
{
	Gold=0,
	Silver=1,
    Copper=2,
};

UCLASS()
class HOMEWORK1_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere)
	float RotateSpeed=180;
	UPROPERTY(EditAnywhere)
	ECoinType CoinType=ECoinType::Copper;
};
