#include "Misc/AutomationTest.h"
#include "Teleportable.h"
#include "EngineUtils.h"

class FWorldFixture
{
public:
	explicit FWorldFixture(const FURL& URL = FURL())

	{
		if (GEngine != nullptr)
		{
			static uint32 WorldCounter = 0;
			const FString WorldName = FString::Printf(TEXT("WorldFixture_%d"),
				WorldCounter++);

			if (UWorld* World = UWorld::CreateWorld(EWorldType::Game,
				false,
				*WorldName,
				GetTransientPackage()))
			{
				FWorldContext& WorldContext =
					GEngine->CreateNewWorldContext(EWorldType::Game);

				WorldContext.SetCurrentWorld(World);

				World->InitializeActorsForPlay(URL);
				if (IsValid(World->GetWorldSettings()))
				{
					// The following functions are usually called by the game
					// mode, but we don't have one in this case, so we need to
					// call them manually.
					World->GetWorldSettings()->NotifyBeginPlay();
					World->GetWorldSettings()->NotifyMatchStarted();
				}
				World->BeginPlay();

				WeakWorld = MakeWeakObjectPtr(World);

			}
		}
	}

	~FWorldFixture()
	{
		UWorld* World = WeakWorld.Get();
		if (World != nullptr && GEngine != nullptr)
		{
			World->EndPlay(EEndPlayReason::Quit);

			// Technically, DestroyWorld will destroy any Actors it is
			// aware of, but they will only get destroyed once the GC
			// gets to them. This for loop ensures they get destroyed
			// immediately so the resources don't end up hanging around.
			for (auto It = TActorIterator<AActor>(World); It; ++It)
			{
				It->Destroy();
			}

			GEngine->DestroyWorldContext(World);
			World->DestroyWorld(false);
		}
	}

	UWorld* GetWorld() const
	{
		return WeakWorld.Get();
	}

private:
	TWeakObjectPtr<UWorld> WeakWorld;
};

BEGIN_DEFINE_SPEC(TeleportableSpec,
	"CMP302 Lab 8",
	EAutomationTestFlags::ProductFilter |
	EAutomationTestFlags_ApplicationContextMask)
	TUniquePtr<FWorldFixture> WorldFixture;
	TWeakObjectPtr<ATeleportable> TeleportableActor;
	TWeakObjectPtr<AActor> DestinationActor;
END_DEFINE_SPEC(TeleportableSpec)

void TeleportableSpec::Define()
{
	Describe("Teleportable: SwapPositionWithActor", [this]()
		{
			BeforeEach([this]()
				{
					// Create our temporary World so we can spawn Actors.
					WorldFixture = MakeUnique<FWorldFixture>();

					if (TestNotNull("World", WorldFixture->GetWorld()))
					{
						// Add our 2 actors to the world.
						TeleportableActor =
							WorldFixture->GetWorld()->SpawnActor<ATeleportable>();
						TeleportableActor->SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
						TestNotNull("TeleportableActor", TeleportableActor.Get());

						DestinationActor = WorldFixture->GetWorld()->SpawnActor<AActor>();
						DestinationActor->SetActorLocation(FVector(10.0f, 10.0f, 10.0f));
						TestNotNull("DestinationActor", DestinationActor.Get());

					}
				});

			It("should swap locations with the destination actor", [this]()
				{
					FVector Source = TeleportableActor->GetActorLocation();
					FVector Destination = DestinationActor->GetActorLocation();

					TeleportableActor->SwapPositionWithActor(DestinationActor.Get());

					TestTrue("SwapPositionWithActor",
						((TeleportableActor->GetActorLocation() == Destination) &&
							(DestinationActor->GetActorLocation() == Source)));
				});

			AfterEach([this]()
				{
					WorldFixture.Reset();
				});
		});
}