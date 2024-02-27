#include "TutorialEventManager.h"

TutorialEventManager* TutorialEventManager::GetInstance()
{
	static TutorialEventManager instance;
	return &instance;
}

void TutorialEventManager::Update()
{
	// à–¾‚ğŸ‚Éi‚ß‚é
	if (isNext) { tutorialEvent.NextPhase(); isNext = false; }
	tutorialEvent.Update();
}

void TutorialEventManager::Draw()
{
	tutorialEvent.Draw();
}
