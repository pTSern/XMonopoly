#pragma once

#include "../../ZyUwU/ZyUwU.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(UserAudio, Ref)

public:
    int getMenuThemeId();
    int getBattleThemeId();

    void setMenuTheme(std::string sPath);
    void setBattleTheme(std::string sPath);

protected:
    std::string m_sMenuTheme, m_sBattleTheme;

private:
    int p_nMenuId, p_nBattleId;

END_CREATE_REFCLASS