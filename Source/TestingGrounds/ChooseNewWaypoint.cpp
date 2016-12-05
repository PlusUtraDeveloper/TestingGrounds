// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "ChooseNewWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNewWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get Patrol Points
	auto AIController = OwnerComp.GetAIOwner();
	auto AIPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(AIPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPointCPP;
	
	// Set Next Waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	//auto NextWaypoint = BlackboardComp->GetKeyName(NextWaypointKey.GetSelectedKeyID);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
	
	// Cycle Index
	auto NewIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NewIndex);
	
	//UE_LOG(LogTemp, Warning, TEXT("Index: %i"), Index);
	return EBTNodeResult::Succeeded;
}
