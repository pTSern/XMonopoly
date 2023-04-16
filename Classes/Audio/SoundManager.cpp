#include "SoundManager.h"

SoundManager* SoundManager::sp_pInstance = nullptr;

//Constructor

SoundManager::SoundManager() :
p_fVol(0.50f), p_fSFXVol(1.0f)
{

}

//Public

bool SoundManager::init()
{
    return true;
}

void SoundManager::log()
{

}

std::string SoundManager::toString(int nTab)
{
    std::string ts;
    return ts;
}

void SoundManager::playGameFightSound()
{
	auto rand = cocos2d::random(1, 3);
	auto path = StringUtils::format("m_%d.mp3", rand);
	p_nBattleIndex = cocos2d::AudioEngine::play2d(path, true, p_fVol);
	cocos2d::AudioEngine::stop(p_nMenuIndex);
}
void SoundManager::playMainMenuSound()
{
	p_nMenuIndex = cocos2d::AudioEngine::play2d("audio/menu/default.mp3", true, 1);
	cocos2d::AudioEngine::stop(p_nBattleIndex);
}

void SoundManager::setBackgroundVolume(float percent)
{
	p_fVol *= (1-percent/100);
	cocos2d::AudioEngine::setVolume(p_nMenuIndex, p_fVol);
	cocos2d::AudioEngine::setVolume(p_nBattleIndex, p_fVol);
}

void SoundManager::setSFXVolume(float percent)
{
	p_fSFXVol *= (1-percent/100);
}

void SoundManager::playSoundEffect(const std::string& sPath)
{
	cocos2d::AudioEngine::play2d(sPath, false, p_fSFXVol);
}

void SoundManager::stop()
{
	cocos2d::AudioEngine::end();
}