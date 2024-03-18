#include "TutorialEventManager.h"

TutorialEventManager* TutorialEventManager::GetInstance()
{
	static TutorialEventManager instance;
	return &instance;
}

void TutorialEventManager::Update()
{
	// 説明を次に進める
	if (isNext) { tutorialEvent.NextPhase(); isNext = false; }
	tutorialEvent.Update();
}

void TutorialEventManager::Draw()
{
	tutorialEvent.Draw();
}
