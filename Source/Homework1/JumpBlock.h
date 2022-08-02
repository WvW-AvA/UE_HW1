// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Homework1Character.h"
#include "JumpBlock.generated.h"

UCLASS()
class HOMEWORK1_API AJumpBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpBlock();
	UStaticMeshComponent * Mesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* other)override;

private:
	float timer=0;
	bool isJumping=false;
	float last_v;
	AHomework1Character* temp;
public:	
	// Called every frame
	UPROPERTY(EditAnywhere)
	float AddForceValue=100;
	UPROPERTY(EditAnywhere)
	float JumpCount=0.2f;
	virtual void Tick(float DeltaTime) override;

};
