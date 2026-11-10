#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleportable.generated.h"

UCLASS()
class SPECTESTBASE_API ATeleportable : public AActor
{
	GENERATED_BODY()
	
public:	
	ATeleportable();

	// Teleports this actor to the destination actor's location.
	UFUNCTION(BlueprintCallable)
	void TeleportToActor(AActor* DestinationActor);

	// Swaps this actor's location with the destination actor.
	UFUNCTION(BlueprintCallable)
	void SwapPositionWithActor(AActor* DestinationActor);

};
