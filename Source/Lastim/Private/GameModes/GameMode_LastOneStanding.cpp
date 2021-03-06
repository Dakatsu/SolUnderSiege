// Copyright Kyle Taylor Lange

#include "Lastim.h"
#include "SolGameState.h"
#include "SolPlayerState.h"
#include "SolPlayerController.h"
#include "SolBot.h"
#include "HUD_LastOneStanding.h"
#include "GameMode_LastOneStanding.h"

AGameMode_LastOneStanding::AGameMode_LastOneStanding(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	DisplayName = NSLOCTEXT("GameMode_LastOneStanding", "LastOneStanding", "Last One Standing");
	HUDClass = AHUD_LastOneStanding::StaticClass();

	KillScore = 0;
	DeathScore = -1;
	SuicideScore = -1;

	bDelayedStart = true;
}

void AGameMode_LastOneStanding::HandleMatchHasStarted()
{
	// Always force respawn, despite server option.
	ASolGameState* const MyGameState = Cast<ASolGameState>(GameState);
	if (MyGameState)
	{
		MyGameState->bForceRespawn = true;
	}
	Super::HandleMatchHasStarted();
}

void AGameMode_LastOneStanding::PostLogin(APlayerController* NewPlayer)
{
	// Set the player's score (lives) to the score limit.
	// TODO: Find a way to start the player at the same amount of lives as the lowest place player.
	//       (So players can join in the middle of the game, but they're handicapped.)
	//       Also, doesn't work for bots, so we had to override InitBot to do it. Better solution later?
	Super::PostLogin(NewPlayer);
	ASolPlayerState* NewPlayerState = CastChecked<ASolPlayerState>(NewPlayer->PlayerState);
	if (NewPlayerState)
	{
		if (GetMatchState() == MatchState::InProgress)
		{
			ASolGameState const* const MyGameState = CastChecked<ASolGameState>(GameState);
			int32 MyStartingLives = ScoreLimit;

			for (int32 i = 0; i < MyGameState->PlayerArray.Num(); i++)
			{
				const float EnemyLives = MyGameState->PlayerArray[i]->Score;
				if (MyStartingLives >= EnemyLives)
				{
					// Always start with one less life than the lowest player.
					MyStartingLives = FMath::Max(0.0f, EnemyLives - 1);
					if (MyStartingLives <= 0.0f)
					{
						return;
					}
				}
			}
		}
		else
		{
			NewPlayerState->Score = ScoreLimit;
		}
	}
}

void AGameMode_LastOneStanding::InitBot(ASolAIController* AIC, FBotProfile* InBotProfile)
{
	Super::InitBot(AIC, InBotProfile);
	if (AIC)
	{
		ASolPlayerState* BotPlayerState = CastChecked<ASolPlayerState>(AIC->PlayerState);
		if (BotPlayerState)
		{
			BotPlayerState->Score = ScoreLimit;
		}
	}
}

void AGameMode_LastOneStanding::RestartPlayer(AController* NewPlayer)
{
	// Return if we are out of lives, and go into spectator mode. Maybe not the best implementation?
	if (NewPlayer->PlayerState)
	{
		if (NewPlayer->PlayerState->Score <= 0)
		{
			ASolPlayerController* LPC = Cast<ASolPlayerController>(NewPlayer);
			if (LPC)
			{
				LPC->BeginWaiting();
			}
			return;
		}
	}
	Super::RestartPlayer(NewPlayer);
}

void AGameMode_LastOneStanding::DetermineMatchWinner()
{
	// Identical to Anarchy's implementation.
	ASolGameState const* const MyGameState = CastChecked<ASolGameState>(GameState);
	float BestScore = MAX_FLT;
	int32 BestPlayer = -1;
	int32 NumBestPlayers = 0;

	for (int32 i = 0; i < MyGameState->PlayerArray.Num(); i++)
	{
		const float PlayerScore = MyGameState->PlayerArray[i]->Score;
		if (BestScore < PlayerScore)
		{
			BestScore = PlayerScore;
			BestPlayer = i;
			NumBestPlayers = 1;
		}
		else if (BestScore == PlayerScore)
		{
			NumBestPlayers++;
		}
	}

	//WinnerPlayerState = (NumBestPlayers == 1) ? Cast<ASolPlayerState>(MyGameState->PlayerArray[BestPlayer]) : NULL;
}

void AGameMode_LastOneStanding::CheckForMatchWinner()
{
	ASolGameState const* const MyGameState = CastChecked<ASolGameState>(GameState);

	int32 AlivePlayers = 0;
	for (int32 i = 0; i < MyGameState->PlayerArray.Num(); i++)
	{
		const float Lives = MyGameState->PlayerArray[i]->Score;
		if (Lives > 0)
		{
			AlivePlayers++;
		}
	}
	// Finish the game if there is one (or no) players with lives.
	if (AlivePlayers <= 1)
	{
		FinishMatch();
	}
}


