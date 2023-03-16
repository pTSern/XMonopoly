#pragma once

#include "ZyUwU/ZyUwU.h"
#include "ui/CocosGUI.h"

USING_NS_ALL;

class MainMenuScene : public Layer
{
public:
    static Scene* createScene();

    virtual bool init();

    void goToPvP(Ref* pSender);
    virtual void onEnter();

    ZY_CREATE_FUNC(MainMenuScene);

private:
    Menu* p_pIconList;
};
