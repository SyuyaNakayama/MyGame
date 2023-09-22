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
	/// <param name="useCamera">true�ɂ���ƃJ�����̈ʒu���}�C�N���W�ɂȂ�</param>
	/// <param name="usePan">true�ɂ���Ɖ��������E�ړ�����</param>
	static PointAudio* CreatePointAudio(const std::string& fileName,
		bool isLoop = false, Vector3 audioPos = {}, bool useCamera = true, bool usePan = true);
	static void Update();
};