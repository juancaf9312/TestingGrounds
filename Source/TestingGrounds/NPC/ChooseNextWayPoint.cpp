// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"
#include "PatrolComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	uint16 Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	APawn* PatrolCharacter = OwnerComp.GetAIOwner()->GetControlledPawn();

	if (!ensure(PatrolCharacter))return EBTNodeResult::Failed;
	UPatrolComponent *PatrolComp = PatrolCharacter->FindComponentByClass<UPatrolComponent>();

	if (!ensure(PatrolComp))return EBTNodeResult::Failed;
	TArray<AActor*> PatrolPoints = PatrolComp->GetPatrolPints();
	uint16 PatrolPintsLenght = PatrolPoints.Num();

	if (PatrolPintsLenght > 0) {
		BlackBoardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
		BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, ++Index%PatrolPintsLenght);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing patrol points"))
	}
		

	return EBTNodeResult::Succeeded;
}


