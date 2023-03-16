#pragma once

#include "ZyUwU/ZyUwU.h"
#include "ui/CocosGUI.h"

USING_NS_ALL;

class GameOverScene : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    void goToMainMenu(Ref* sender);
    ZY_CREATE_FUNC(GameOverScene);

};