// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ChooseNextWayPoint.h"
#include "Public/TP_ThirdPerson/PatrolThirdPersonCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	uint16 Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	APatrolThirdPersonCharacter* PatrolCharacter =Cast<APatrolThirdPersonCharacter>(OwnerComp.GetAIOwner()->GetControlledPawn());

	if (!ensure(PatrolCharacter))return EBTNodeResult::Failed;

	uint16 PatrolPintsLenght = PatrolCharacter->PatrolPoints.Num();
	if (PatrolPintsLenght > 0) {
		BlackBoardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolCharacter->PatrolPoints[Index]);
		Index++;
		BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index%PatrolPintsLenght);
	}
		

	return EBTNodeResult::Succeeded;
}


