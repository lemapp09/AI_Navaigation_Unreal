// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <shlobj_core.h>

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AgentStates.h"
#include "Enemy.generated.h"

enum class EAgentStates : uint8;

class UPawnSensingComponent;

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
	AActor* ChaseTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere,Category = "AI Navigation")
	double PatrolRange = 200.f;

	UPROPERTY(EditAnywhere,Category = "AI Navigation")
	double ChaseRange = 200.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	float WaitTimeMin = 1.f;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	float WaitTimeMax = 5.f;
	
	FTimerHandle PatrolTimer;

	EAgentStates AgentState = EAgentStates::EAS_Patrolling;

	void PatrolTimerFinished();

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool InTargetRange(AActor* Target, double Range);
	
	bool InSearchingRange(FVector Location, double Range);
	
	void MoveToTarget(AActor* Target);

	void MoveToLocation(FVector Location);

	void CheckPatrolTarget();

	void CheckChaseTarget();

	void CheckSearchTarget();

	AActor* GetNextPatrolTarget();

private:	

	int32 CurrentTargetselection = 0;

	FVector LastKnownLocation;

};
