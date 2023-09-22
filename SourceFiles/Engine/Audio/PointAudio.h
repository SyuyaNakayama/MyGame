#pragma once
#include "Audio.h"
#include "Vector.h"

class PointAudio : public Audio
{
private:
	Vector3 audioPos;
	Vector3 micPos;
	Vector3 forward;
	bool useCamera = true;
	bool usePan = true;
	float sPressRate = 1.0f; // Œ´‹È‚Æ‚Ì‰¹ˆ³‚Ì”ä—¦
	long panStrength = 2500; // ƒpƒ“‚Ì‹­‚³(‘å‚«‚¢‚Ù‚Ç¶‰E‚Ì‰¹—Ê·‚ª‘å‚«‚­‚È‚é)

	void Initialize(const std::string& fileName, Vector3 audioPos, bool useCamera, bool usePan);
	void Update();

public:
	friend AudioManager;
	void SetAudioPos(Vector3 pos) { audioPos = pos; }
	void SetMicPos(Vector3 pos) { micPos = pos; }
	void SetForward(Vector3 forward_) { forward = forward_; }
	void SetPanStrength(long panStrength_) { panStrength = panStrength_; }
};