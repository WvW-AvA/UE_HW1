// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpBlock.h"
#include "Homework1Character.h"

// Sets default values
AJumpBlock::AJumpBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAssest(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder"));
	if (MeshAssest.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAssest.Object);
		Mesh->SetRelativeScale3D(FVector(1,1,0.1));
		Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	}
}

// Called when the game starts or when spawned
void AJumpBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJumpBlock::NotifyActorBeginOverlap(AActor* other)
{
	temp=nullptr;
	temp=Cast<AHomework1Character>(other);
	if (temp != nullptr)
	{
		last_v=temp->GetCharacterMovement()->JumpZVelocity;
		temp->GetCharacterMovement()->JumpZVelocity=AddForceValue;
		temp->Jump();
		isJumping=true;
	}
}

// Called every frame
void AJumpBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isJumping)
	{
		timer+=DeltaTime;
		if (timer >= JumpCount)
		{
			isJumping=false;
			timer=0;
			if(temp!=nullptr)
			temp->StopJumping();
			temp->GetCharacterMovement()->JumpZVelocity=last_v;
		}
	}
}

