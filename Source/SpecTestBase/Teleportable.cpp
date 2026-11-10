#include "Teleportable.h"

ATeleportable::ATeleportable()
{

}

void ATeleportable::TeleportToActor(AActor* DestinationActor)
{
	if(DestinationActor != nullptr)
	{
		SetActorLocation(DestinationActor->GetActorLocation());
	}
	else
	{
		UE_LOGFMT(LogTemp, Log, "Teleportable::TeleportToActor called with null destination.");
	}
}

void ATeleportable::SwapPositionWithActor(AActor* DestinationActor)
{
	if(DestinationActor != nullptr)
	{
		FVector OldLocation = GetActorLocation();

		SetActorLocation(DestinationActor->GetActorLocation());
		DestinationActor->SetActorLocation(OldLocation);
	}
	else
	{
		UE_LOGFMT(LogTemp, Log, "Teleportable::SwapPositionWithActor called with null destination.");
	}
}
