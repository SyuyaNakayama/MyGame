#include "TutorialEventManager.h"

TutorialEventManager* TutorialEventManager::GetInstance()
{
	static TutorialEventManager instance;
	return &instance;
}

void TutorialEventManager::Update()
{
	// ���������ɐi�߂�
	if (isNext) { tutorialEvent.NextPhase(); isNext = false; }
	tutorialEvent.Update();
}

void TutorialEventManager::Draw()
{
	tutorialEvent.Draw();
}
