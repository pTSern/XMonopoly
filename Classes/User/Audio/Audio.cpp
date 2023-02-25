#include "Audio.h"

//Constructor

UserAudio::UserAudio()
{

}

//Public

bool UserAudio::init()
{
    return true;
}

void UserAudio::log()
{

}

std::string UserAudio::toString(int nTab)
{
    std::string ts;
    std::string tab = ZY_SP_TAB(nTab);
    return ts;
}

int UserAudio::getMenuThemeId()
{
    return this->p_nMenuId;
}

int UserAudio::getBattleThemeId()
{
    return this->p_nMenuId;
}

void UserAudio::setMenuTheme(std::string sPath)
{
    this->m_sMenuTheme = sPath;
}

void UserAudio::setBattleTheme(std::string sPath)
{
    this->m_sBattleTheme = sPath;
}