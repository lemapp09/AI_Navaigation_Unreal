// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class AI_NAVIGATION_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	class AAIController* EnemyController;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere,Category = "AI Navigation")
	double PatrolRange = 200.f;
	FTimerHandle PatrolTimer;

	void PatrolTimerFinished();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool InTargetRange(AActor* Target, double Range);

	void MoveToTarget(AActor* Target);

	AActor* GetNextPatrolTarget();

private:	

	int32 CurrentTargetselection = 0;

};