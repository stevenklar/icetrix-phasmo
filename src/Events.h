#pragma once

#include "Game.h"

namespace Phasmo::Event
{
	// Updates
	struct GhostUpdate { Phasmo::GhostAI* ghost; };
	struct OuijaBoardUpdate { app::OuijaBoard* ouijaBoard; };
	struct DNAEvidenceUpdate { app::DNAEvidence* bone; };
	struct PlayerUpdate { Phasmo::Player_1* localPlayer; };
	struct MissionManagerUpdate { Phasmo::MissionManager* missionManager; };
	struct MainManagerUpdate { Phasmo::MainManager* mainManager; };
	struct ServerSettingsUpdate { app::ServerSettings* serverSettings; };
	struct FirstPersonControllerUpdate { app::FirstPersonController* firstPersonController;  };
	// Gargabe Collect
	struct SceneManagerLoadScene { app::String* sceneName; };
	struct GameControllerStart { app::GameController* gameController; };
	struct GameControllerExit { app::GameController* gameController; };
	struct RewardManagerAwake { app::RewardManager* rewardManager; };
	struct JournalControllerUpdate { app::JournalController* journalController; };
	struct TimeScale { float* timeScale; };
};
