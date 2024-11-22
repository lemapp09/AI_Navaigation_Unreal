// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "TimerManager.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Runtime/AIModule/Classes/AITypes.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyController = Cast<AAIController>(GetController());
	CurrentTargetselection = 0;
	PatrolTarget = GetNextPatrolTarget();
	MoveToTarget(PatrolTarget);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InTargetRange(PatrolTarget, PatrolRange))
	{
		PatrolTarget = GetNextPatrolTarget();
		
		GetWorldTimerManager().SetTimer(PatrolTimer, this,
			&AEnemy::PatrolTimerFinished, 5.0f, false);
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


bool AEnemy::InTargetRange(AActor* Target, double Range)
{
	if (Target == nullptr) return false;
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	return DistanceToTarget <= Range;
}

void AEnemy::PatrolTimerFinished()
{
	MoveToTarget(PatrolTarget);
}

void AEnemy::MoveToTarget(AActor* Target)
{
	if (EnemyController == nullptr || PatrolTarget == nullptr) return;
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(50.0f);

	EnemyController->MoveTo(MoveRequest);

	DrawDebugSphere(GetWorld(), Target->GetActorLocation(),
	                50.0f, 32, FColor::Orange, false, 5.0f);
}

AActor* AEnemy::GetNextPatrolTarget()
{
	const int32 NumberOfPatrolTargets = PatrolTargets.Num();
	if (NumberOfPatrolTargets > 0)
	{
		AActor* NewTarget = PatrolTargets[CurrentTargetselection];
		CurrentTargetselection = (CurrentTargetselection + 1) % (NumberOfPatrolTargets);
		return NewTarget;
	}
	return nullptr;
}
