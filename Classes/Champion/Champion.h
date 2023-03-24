#pragma once

#include "../GameObject/GameObject.h"
#include "../ZyUwU/ZyUwU.h"
#include "../Statics/Statics.h"
#include "ui/CocosGUI.h"

USING_NS_ALL;

BEGIN_CREATE_REFCLASS(Champion, GameObject)

public:
    static Champion* createWithProperties(const std::string& icon, Statics* pStatics, ChampionStatics* pChampStatics);

public:
    Champion* clone();

    CREATE_GET_FUNC(getIcon, ZYSprite*, m_pIcon);
    CREATE_GET_FUNC(getStatics, Statics*, m_pStatics);
    CREATE_GET_FUNC(getChampionStatics, ChampionStatics*, m_pChampionStatics);

    CREATE_CLONE_SET_FUNC(setStatics, Statics, m_pStatics);
    CREATE_CLONE_SET_FUNC(setChampionStatics, ChampionStatics, m_pChampionStatics);

    void setIcon(std::string sTexture);
    void setIconPosition(Point pos);


public:
    virtual void update(float dt);
    virtual void config();

protected:
    ZYSprite* m_pIcon, *m_pAvatar;
    Statics* m_pStatics;
    ChampionStatics* m_pChampionStatics;

private:


END_CREATE_REFCLASS
