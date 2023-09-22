#pragma once
#include "PointAudio.h"
#include <list>
#include <memory>
#include <string>
#include <map>

class AudioManager
{
private:
	static std::map<bool, std::list<std::unique_ptr<Audio>>> audios;
	static std::map<bool, std::list<std::unique_ptr<PointAudio>>> pointAudios;

public:
	static Audio* CreateAudio(const std::string& fileName, bool isLoop = false);
	static PointAudio* CreatePointAudio(const std::string& fileName,
		bool isLoop = false, Vector3 audioPos = {}, bool useCamera = true, bool usePan = true);
	static void Update();
};