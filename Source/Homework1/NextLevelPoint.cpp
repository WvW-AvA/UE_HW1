// Fill out your copyright notice in the Description page of Project Settings.


#include "NextLevelPoint.h"
#include "Components/StaticMeshComponent.h"
#include "Homework1Character.h"
#include "Homework1GameMode.h"

// Sets default values
ANextLevelPoint::ANextLevelPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAssest(TEXT("/Game/StarterContent/Props/SM_WindowFrame"));
	if (MeshAssest.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAssest.Object);
		Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	}
}
// Called when the game starts or when spawned
void ANextLevelPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANextLevelPoint::NotifyActorBeginOverlap(AActor* OtherActor)
{
	auto HWCharacter= Cast<AHomework1Character>(OtherActor);
	if (HWCharacter != nullptr)
	{
		AHomework1GameMode* mode= Cast<AHomework1GameMode>(GetWorld()->GetAuthGameMode());
		if (mode != nullptr)
		{
			mode->CheckGoNextLevel();
		}
	}
}

// Called every frame
void ANextLevelPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

