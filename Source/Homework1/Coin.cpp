// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

// Sets default values

ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin Mesh"));
	Mesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CoinMeshAssest(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder"));

	if (CoinMeshAssest.Succeeded())
	{
		Mesh->SetStaticMesh(CoinMeshAssest.Object);
		Mesh->SetRelativeRotation(FRotator(90,0,0),true);
		Mesh->SetRelativeScale3D(FVector(1,1,0.2));
		Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	
	}
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
		FString CoinMaterialPath;
		if (CoinType == ECoinType::Gold)
		{
			CoinMaterialPath="/Game/StarterContent/Materials/M_Metal_Gold";
		}
		else if (CoinType == ECoinType::Silver)
		{
			CoinMaterialPath="/Game/StarterContent/Materials/M_Metal_Steel";
		}
		else if (CoinType == ECoinType::Copper)
		{
			CoinMaterialPath="/Game/StarterContent/Materials/M_Metal_Copper";
		}
		UMaterial* CoinMaterialAssest=LoadObject<UMaterial>(nullptr,*CoinMaterialPath);
		if (CoinMaterialAssest)
		{
			Mesh->SetMaterial(0,CoinMaterialAssest);
		}
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mesh->AddLocalRotation(FRotator(0,0,DeltaTime*RotateSpeed),true);
}

