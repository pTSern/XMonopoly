#include "SoundManager.h"

SoundManager* SoundManager::sp_pInstance = nullptr;

//Constructor

SoundManager::SoundManager()
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
//	p_nBattleIndex = cocos2d::AudioEngine::play2d(User::GetInstance()->GetUserSound()->g_sGameFight, true, User::GetInstance()->GetUserSound()->g_fVolume);
//	cocos2d::AudioEngine::stop(p_nMenuIndex);
}
void SoundManager::playMainMenuSound()
{
//	p_nMenuIndex = cocos2d::AudioEngine::play2d(User::GetInstance()->GetUserSound()->g_sMenu, true, User::GetInstance()->GetUserSound()->g_fVolume);
//	cocos2d::AudioEngine::stop(p_nBattleIndex);
}
void SoundManager::setVolume()
{

}

void SoundManager::playSoundEffect(std::string sPath)
{
//	cocos2d::AudioEngine::play2d(sPath, false, User::GetInstance()->GetUserSound()->g_fVolume);
}
