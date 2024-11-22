// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "TimerManager.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Runtime/AIModule/Classes/AITypes.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->SightRadius = 1000.0f;
	PawnSensingComponent->SetPeripheralVisionAngle(45.0f);
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemy::PawnSeen);
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

	if (!(EnemyController->GetMoveStatus() == EPathFollowingStatus::Moving) && AgentState != EAgentStates::EAS_Patrolling)
	{
		AgentState = EAgentStates::EAS_Patrolling;
		PatrolTarget = GetNextPatrolTarget();
		MoveToTarget(PatrolTarget);
	}

	if (AgentState == EAgentStates::EAS_Chasing)
		{
			CheckChaseTarget();
		}
	else if (AgentState == EAgentStates::EAS_Searching)
		{
			CheckSearchTarget();
		}
	else
	{
		CheckPatrolTarget();
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

bool AEnemy::InSearchingRange(FVector Location, double Range)
{
	const double DistanceToTarget = (Location - GetActorLocation()).Size();
	return DistanceToTarget <= Range;
}

void AEnemy::PatrolTimerFinished()
{
	MoveToTarget(PatrolTarget);
}

void AEnemy::MoveToTarget(AActor* Target)
{
	if (EnemyController == nullptr || Target == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("Moving to %s"), *Target->GetName());
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(20.0f);

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

void AEnemy::PawnSeen(APawn* SeenPawn)
{
	if (AgentState == EAgentStates::EAS_Chasing) return;
	// check if SeenPawn is the Player
	AActor* SeenActor = Cast<AActor>(SeenPawn);
	if (SeenActor->ActorHasTag(FName(TEXT("Player"))))
	{
		AgentState = EAgentStates::EAS_Chasing;
		GetWorldTimerManager().ClearTimer(PatrolTimer);
		GetCharacterMovement()->MaxWalkSpeed = 400.f;
		ChaseTarget = SeenPawn;
		LastKnownLocation = SeenActor->GetActorLocation();
		MoveToTarget(ChaseTarget);
	}
}

void AEnemy::CheckPatrolTarget()
{
	if (InTargetRange(PatrolTarget, PatrolRange))
	{
		PatrolTarget = GetNextPatrolTarget();
		const float WaitTime = FMath::FRandRange(WaitTimeMin, WaitTimeMax);
		GetWorldTimerManager().SetTimer(PatrolTimer, this,
		                                &AEnemy::PatrolTimerFinished, WaitTime, false);
	}
}

void AEnemy::CheckChaseTarget()
{
	if (ChaseTarget)
	{
		if (InTargetRange(ChaseTarget, 150.f))
		{
			UGameplayStatics::OpenLevel(this,  FName(*GetWorld()->GetName()), false);
		}
		else if (!InTargetRange(ChaseTarget, ChaseRange))
		{
			MoveToLocation(LastKnownLocation);
			AgentState = EAgentStates::EAS_Searching;
			GetCharacterMovement()->MaxWalkSpeed = 200.f;
		}
	}
}

void AEnemy::MoveToLocation(const FVector Location)
{
	if (EnemyController == nullptr) return;
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation(Location);
	MoveRequest.SetAcceptanceRadius(20.0f);

	EnemyController->MoveTo(MoveRequest);

	DrawDebugSphere(GetWorld(), Location,
	                50.0f, 32, FColor::Orange, false, 5.0f);
}

void AEnemy::CheckSearchTarget()
{
	if (InSearchingRange(LastKnownLocation, 20.f))
	{
		ChaseTarget = nullptr;
		AgentState = EAgentStates::EAS_Patrolling;
		PatrolTarget = GetNextPatrolTarget();
		GetCharacterMovement()->MaxWalkSpeed = 200.f;
	}
	
}
