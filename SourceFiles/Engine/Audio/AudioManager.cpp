#include "AudioManager.h"

std::map<bool, std::list<std::unique_ptr<Audio>>> AudioManager::audios;
std::map<bool, std::list<std::unique_ptr<PointAudio>>> AudioManager::pointAudios;

Audio* AudioManager::CreateAudio(const std::string& fileName, bool isLoop)
{
	std::unique_ptr<Audio> newAudio = std::make_unique<Audio>();
	newAudio->Initialize(fileName);
	audios[isLoop].push_back(std::move(newAudio));
	return audios[isLoop].front().get();
}

PointAudio* AudioManager::CreatePointAudio(const std::string& fileName, 
	bool isLoop, Vector3 audioPos, bool useCamera, bool usePan)
{
	std::unique_ptr<PointAudio> newAudio = std::make_unique<PointAudio>();
	newAudio->Initialize(fileName, audioPos, useCamera, usePan);
	pointAudios[isLoop].push_back(std::move(newAudio));
	return pointAudios[isLoop].front().get();
}

void AudioManager::Update()
{
	for (auto& audio : audios[true]) { if (audio->IsFinished()) { audio->SetPlayPosition(0); } }
	for (auto& audio : pointAudios[true]) { if (audio->IsFinished()) { audio->SetPlayPosition(0); } }
	for (auto& audios : pointAudios) { for (auto& audio : audios.second) { audio->Update(); } }
}