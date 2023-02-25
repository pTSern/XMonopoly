#pragma once

#include "audio/include/AudioEngine.h"

#include "ZyUwU/ZyUwU.h"

BEGIN_CREATE_INSTANCE_REFCLASS(SoundManager, cocos2d::Ref)

public:
	void playGameFightSound();
	void playMainMenuSound();
	void setVolume();
	void playSoundEffect(std::string sPath);

private:

END_CREATE_INSTANCE_REFCLASS;
