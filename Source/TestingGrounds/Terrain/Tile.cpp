// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#define MAX_ATTEMPS 100
// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{

	int32 NumToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
		for (int32 i = 0; i < NumToSpawn; i++) {
			FVector SpawnLocation;
			float RandomScale = FMath::RandRange(MinScale, MaxScale);
			if (FindEmptyLocation(SpawnLocation, Radius* RandomScale)) {
				PlaceActor(ToSpawn, SpawnLocation, FMath::RandRange(-180.f,180.f), RandomScale);
			}
		
		}
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = GetActorLocation() + Location;

	bool bHasHit = GetWorld()->SweepSingleByChannel(HitResult, GlobalLocation, GlobalLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));

	return !bHasHit;
}
bool ATile::FindEmptyLocation(FVector &OutLocation, float Radius)
{
	FVector Min(0, -1900, 0), Max(4000, 1900, 0);
	FBox BounceBox(Min, Max);
	for (int32 i = 0; i < MAX_ATTEMPS; i++) {
		FVector CadidateLocation = FMath::RandPointInBox(BounceBox);
		if (CanSpawnAtLocation(CadidateLocation, Radius)) {
			OutLocation = CadidateLocation;
			return true;
		}
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnLocation, float Rotation, float Scale)
{
	AActor *ActorSpawned = GetWorld()->SpawnActor<AActor>(ToSpawn, SpawnLocation, FRotator(0,Rotation,0));
	ActorSpawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	ActorSpawned->SetActorScale3D(FVector(Scale));

	UE_LOG(LogTemp,Warning,TEXT("%s"),*ActorSpawned->GetActorScale().ToString())
}

