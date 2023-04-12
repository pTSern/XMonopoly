#pragma once

#include "audio/include/AudioEngine.h"

#include "ZyUwU/ZyUwU.h"

#define SM_GI SoundManager::getInstance()

BEGIN_CREATE_INSTANCE_REFCLASS(SoundManager, cocos2d::Ref)

public:
	void playGameFightSound();
	void playMainMenuSound();
	void setBackgroundVolume(float percent);
    void setSFXVolume(float percent);
	void stop();

    CREATE_GET_FUNC(getBackgroundVolume, float, p_fVol * 100);
    CREATE_GET_FUNC(getSFXVolume, float, p_fSFXVol * 100);
	void playSoundEffect(const std::string& sPath);

private:
	int p_nMenuIndex, p_nBattleIndex;

    float p_fVol, p_fSFXVol;

END_CREATE_INSTANCE_REFCLASS;
