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
	static void Initialize();
	static void Finalize();
	static Audio* CreateAudio(const std::string& fileName, bool isLoop = false);
	/// <param name="useCamera">trueにするとカメラの位置がマイク座標になる</param>
	/// <param name="usePan">trueにすると音源が左右移動する</param>
	static PointAudio* CreatePointAudio(const std::string& fileName,
		bool isLoop = false, Vector3 audioPos = {}, bool useCamera = true, bool usePan = true);
	static void Update();
};