#pragma once

#include "cocos2d.h"
#include "ZyUwU/ZyUwU.h"
#include "GameObject/GameObject.h"
#include "ui/CocosGUI.h"
#include "Map/Map.h"

#include "Skill/SkillCard/SkillCard.h"
#include "Statics/Statics.h"

class TestLayer;
class Player;
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void onEnter();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void run(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    void endS(Ref* pSender, ui::Widget::TouchEventType type);
    bool onTouch(cocos2d::Touch *touch, cocos2d::Event *event);
    bool endTouch(cocos2d::Touch *touch, cocos2d::Event *event);
    void update(float dt);
    void runx();
    void runa();

    void spawn(float dt);

    void wt(cocos2d::Point a, cocos2d::Point b, float h);

    cocos2d::Point runwt(float newx);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

protected:
    zy::ZYSprite *x, *charx, *charx_clone;
    zy::ZYSprite *px7;
    std::vector<zy::ZYSprite *> listp;
    std::vector<cocos2d::Sprite *> pl;
    zy::ZYBlurEffect *bc;
    std::vector<zy::GachaItem*> gh, gp;
    cocos2d::ui::Button *button, *sb;
    cocos2d::Point touchPoint;
    int i = 0;
    SkillCard *sc, *sc1;
    Statics *zd;

    float ya, yb,yc;
    struct Locations {
        Locations(cocos2d::backend::ProgramState *ps, cocos2d::backend::UniformLocation loc)
                : programState(ps), location(loc) {}

        cocos2d::backend::ProgramState *programState = nullptr;
        cocos2d::backend::UniformLocation location;
    };

    std::vector<Locations> timeUniforms;

    Player* player;
};
