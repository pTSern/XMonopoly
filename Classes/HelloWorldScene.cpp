#include "HelloWorldScene.h"
#include "GameObject/GameObject.h"
#include "ui/CocosGUI.h"
#include "Statics/Statics.h"
#include "Skill/SkillCard/SkillCard.h"
#include "User/UI/IngameUI.h"
#include "Support/Coordinate.h"
#include "Champion/Champion.h"
#include "Arena/Property/Property.h"
#include "Arena/Arena.h"
#include "LogManager/LogManager.h"
#include "Player/Player.h"
#include "Dice/Dice.h"
#include "ChampionInGame/UI/ChampionUI.h"

USING_NS_ALL;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();

    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    this->setName("SCENE");


    auto visibleSize = ZYDirector::getInstance()->getVisibleSize();
    Vec2 origin = ZYDirector::getInstance()->getVisibleOrigin();

    //CCLOG("VISIBLE: %f - %f", visibleSize.width, visibleSize.height);

    auto c = ZYSprite::create("map/b2.png");
    c->setPosition(Point((visibleSize.width/2 + origin.x)/1, (visibleSize.height/2 + origin.y)/1 ));
    //CCLOG("MAP: %f - %f", c->getPositionX(), c->getPositionY());

    x = ZYSprite::create("skill_icon/skillcard2.png");

    auto y = ZYSprite::create("skill_icon/sc.png");
    auto z = ZYSprite::create("skill_icon/sc.png");
    auto a = ZYSprite::create("skill_icon/sc.png");
    auto b = ZYSprite::create("skill_icon/sc.png");

    auto hh = ZYSprite::create("HelloWorld.png");

    y->replaceTexture(hh);

    x->setPosition(Point((visibleSize.width/2 + origin.x)/1, (x->getContentSize().height/3 + origin.y)/1));
    CCLOG("X SIZE: %f - %f", x->getContentSize().width, y->getContentSize().height);
    //x->setContentSize(Size(x->getContentSize().width*0.5333, x->getContentSize().height*0.5333));
    y->setPosition(Point(x->getPositionX() + y->getContentSize().width/2, x->getPositionY() - y->getContentSize().height/10));
    y->setRotation(15);
    z->setPosition(Point(y->getPositionX() + z->getContentSize().width/2, y->getPositionY() - z->getContentSize().height/10));
    z->setRotation(30);

    //x->log();
    a->setPosition(Point(x->getPositionX() - a->getContentSize().width/2, x->getPositionY()-a->getContentSize().height/10 ));
    a->setRotation(-15);
    b->setPosition(Point(a->getPositionX() - b->getContentSize().width/2 , a->getPositionY() - b->getContentSize().height/10 ));
    b->setRotation(-30);

    auto bg = ZYSprite::create("bg.png");
    bg->setPosition(ZYDirector::getInstance()->getTrueVisibleSize()/2);
    this->addChild(bg,-10);

    this->addChild(x,0);

    //this->addChild(y,1);
    //this->addChild(z,3);
    //this->addChild(a,-1);
    //this->addChild(b,-2);

    auto zc = ZYSprite::create("skill_icon/sc.png");
    zc->setPosition(z->getPosition());
    //this->addChild(zc, 2);
    zc->setRotation(30);
    //auto zm = MoveBy::create(15, Point(500*sin(toRad(30)), 500*cos(toRad(30))));
    //z->runAction(zm);
    CCLOG("X SIZE: %f - %f", x->getContentSize().width, x->getContentSize().height);

    // auto u = ZYSprite::create("scene/main.png");
    // u->setPosition(Point((visibleSize.width/2 + origin.x)/1, (visibleSize.height/2 + origin.y)/1));
    // this->addChild(u, 5);
    z->setOpacity(z->getOpacity()/2);
    //z->setColor(Color3B::RED);
    CCLOG("OPACITY: %f", (float)z->getOpacity());
    BlendFunc bf = {backend::BlendFactor::SRC_ALPHA, backend::BlendFactor::ONE_MINUS_SRC_ALPHA};
    //z->setBlendFunc(bf);

    //button = ui::Button::create("HelloWorld.png", "HelloWorld.png" );
    //button->setPosition(Point( (visibleSize.width + origin.x)/4, (visibleSize.height + origin.y)/4) );
    //button->setTitleText("SELECT");

    //auto p = DrawNode::create();
    //Point an(150, 150);
    //p->drawRect(an, Point(an.x + 80, an.y), Point(an.x + 80, an.y + 128), Point(an.x, an.y + 128), Color4F::RED);
    //this->addChild(p, 500);

    //auto listener = EventListenerTouchOneByOne::create();
    //listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouch, this);
    //listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::endTouch, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //button->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, button);

    //void (HelloWorld::*func)(Ref*, ui::Widget::TouchEventType);
    //func = &HelloWorld::run;

    //button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::run, this));

    //sb = ui::Button::create("HelloWorld.png", "HelloWorld.png" );
    //sb->setPosition(Point( (visibleSize.width/1.5 + origin.x), (visibleSize.height + origin.y)/4) );
    //sb->setTitleText("UNSELECT");
    //sb->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sb);
    //sb->addTouchEventListener(CC_CALLBACK_2(HelloWorld::endS, this));

    //this->addChild(sb);
    //this->addChild(button);

    this->scheduleUpdate();

    MapManager::getInstance()->loadTileMap("TileMaps/map-13.tmx");
    //MapManager::getInstance()->config();
    this->addChild(MapManager::getInstance(), 0);
    MapManager::getInstance()->log();

   // auto ym = TMXTiledMap::create("map/2.tmx");
   // this->addChild(ym);

   // ym->setPosition(cocos2d::Point((visibleSize.width + origin.x)/2, -ym->getMapSize().height/2));

    ZYDirector::getInstance()->log();

    //auto pL = ZYLabel::createWithTTF("DARK", "fonts/arial.ttf", 50);
    //pL->setPosition(ZYDirector::getInstance()->getTrueVisibleSize()/2);
    //this->addChild(pL, 10);

    //y->log();
    CCLOG("Y SPRITE UP: %f - %f", y->getContentPositionMiddleTop().x, y->getContentPositionMiddleTop().y);

    MAP_MNG_GI->getTileMap()->setPosition(Point(x->getPositionX(), (ZYDirector::getInstance()->getTrueVisibleSize().height + x->getContentPositionMiddleTop().y )/2));
    auto pp = ZYSprite::create("point.png");
    pp->setPosition(MapManager::getInstance()->getPosition());
    this->addChild(pp,5);
    auto px = ZYSprite::create("point.png");
    px->setPosition(x->getContentPositionMiddleTop());

    this->addChild(px,5);

    //MapManager::getInstance()->setPosition(Point( (Director::getInstance()->getWinSizeInPixels().width - Director::getInstance()->getVisibleOrigin().x)/2,
     //                                             (Director::getInstance()->getWinSizeInPixels().height - Director::getInstance()->getVisibleOrigin().y)/2));
    //pp->setPosition(MapManager::getInstance()->getPosition());
    //MapManager::getInstance()->log();
    CCLOG("WIN SIZE PIXEL: %f - %f", Director::getInstance()->getWinSizeInPixels().width, Director::getInstance()->getWinSizeInPixels().height);
    auto move = MoveTo::create(3, Point(1585, 660));
    auto move_in = EaseBackOut::create(move->clone());

    //auto delay = DelayTime::create(0.5f);
    //auto sq = Sequence::create(move_in, delay, move_in->clone(), delay->clone(), move_in->clone(), delay->clone(), nullptr);
    //px7->runAction(sq);


    vua = Node::create();
    charx = ZYSprite::create("champion/char-3.png");
    vua->addChild(charx);
    this->addChild(vua, 1000);
    charx->setEffect(ZYOutlineV2::create());
    //charx_clone = charx->clone();
    //this->addChild(charx_clone, 500);
    //Vec2 dir(225, 225);
    //auto jump = JumpBy::create(2.5, dir, 20, 5);
    charx->setPosition(1213, 450);
    //this->addChild(charx,5);
    //charx->runAction(jump);

    //this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::spawn), 0);

    auto pL = ZYLabel::createWithTTF("DARK", "fonts/arial.ttf", 50);
    pL->setPosition(813,382);
    pL->enableOutline(Color4B::RED);

    pL->setRotation(- MAP_MNG_GI->getAngleHorizon());
    this->addChild(pL, 50);

    auto c1 = ChampionInGame::create();
    c1->setName("QUY");
    c1->setIcon("HelloWorld.png");
    c1->setIconPosition(visibleSize/1.25);

    auto c2 = ChampionInGame::create();
    c2->setName("LMAO");
    c2->setIcon("champion/char-2.png");
    c2->setIconPosition(visibleSize/2.5);

    //c1->addChampChild(c2);
    //c1->log();
    //this->addChild(c1, 50);

    //auto s1 = Skill::createWithProperties(XProperties::create(), SkillStatics::create());
    //this->addChild(s1, 50);
    //s1->log();

    auto a1 = Arena::create();
    //a1->log();
    this->addChild(a1);


    auto ig2 = IngameStatics::create();
    ig2->setStatics(Statics::createWithProperties(50, 20, 02), false);
    ig2->log();

    sc1 = SkillCard::createDefault();

    this->addChild(sc1, 50);
    sc1->setName("SKILL-CARD 1");
    sc1->setSkillPointCostLabel("5");
    sc1->setManaCostLabel("20");
    sc1->setCoolDownLabel("7");
    sc1->setDescriptionLabel("this is a lmao skill. freaking dark ,lafaksfl as;fk as;fk;asl kf;laskf;las kf, deal 100000 dmg to enemy, fajskflajslf jaslkf jalskj asf asf a as, asf asf asf, a ,a ,aasfasf asfaf asf as fas as");
    //sc1->log();
    //sc1->setF(12);

    sc1->setPosition(ZYDR_GVS/2 );
    //auto sct = ZYSprite::create("skill_card/x.png");
    //this->addChild(sct, 70);
    //sct->setPosition(Point(ZYDR_GVS.width/1.5, 0));

    sc1->log();
    LOG_MANAGER_GI->log(sc1->toString());
    LOG_MANAGER_GI->log();

    //auto ano = MAP_MNG_GI->getArenaGroup()->getObject("VIETZ");
    //auto arena_num = ano["width"].asFloat() / MAP_MNG_GI->getArenaGroup()->getObject("property")["width"].asFloat();
    //Point ans(ano["x"].asFloat(), ano["y"].asFloat());
    //auto ap = MAP_MNG_GI->getAngleHorizonInRad();
    //auto world = MAP_MNG_GI->getWorldSize();
    //auto os = MAP_MNG_GI->getObjectTileSize();
    //auto tos = MAP_MNG_GI->getTrueObjectTileSize();

    //auto yyy = (ans.y/os.height)*tos.height*sin(ap) + ((world.width - ans.x)/os.width)*tos.width*sin(ap) + (MAP_MNG_GI->getTileMap()->getPositionY() - MAP_MNG_GI->getTileMap()->getContentSize().height/2);
    //auto xxx = (ans.y/os.height)*tos.height*cos(ap) + (ans.x/os.width)*tos.width*cos(ap) + (MAP_MNG_GI->getTileMap()->getPositionX() - MAP_MNG_GI->getTileMap()->getContentSize().width/2);
    //CCLOG("AAAAAAAAAAAA: %f - %f - %f - %f", xxx, yyy,(MAP_MNG_GI->getTileMap()->getPositionX() - MAP_MNG_GI->getTileMap()->getContentSize().width/2) , (MAP_MNG_GI->getTileMap()->getPositionY() - MAP_MNG_GI->getTileMap()->getContentSize().height/2));

    //auto h = 143;
    //auto w = 89.5;

    //float xxz = xxx;
    //float yyz = yyy;

    //auto ray = DrawNode::create();
    //ray->drawRect(Vec2(xxz,yyz), Vec2(xxz + h*cos(ap), yyz + h*sin(ap)), Vec2(xxz + h*cos(ap) + w*cos(ap), yyz - w*sin(ap) + h*sin(ap)), Vec2(xxz+w*cos(ap), yyz - w*sin(ap)) ,Color4F::RED);
    //addChild(ray, 1000);
    //CCLOG("MAP %s", ZYSP_VTS(MAP_MNG_GI->getTileMap()->getPosition()).c_str());
    //CCLOG("%f - %f", xxz, yyz);

    //for(auto &x : MAP_MNG_GI->getArenas())
    //{
    //    x->log();
    //}
    //charx->removeEffect();

    //auto dn = DrawNode::create();
    //this->addChild(dn, 1000);

    MAP_MNG_GI->generateArenas();
    ZYDR_GI->log();

    dice = Dice::createWithProperties("dice/128.png");
    auto champ = Champion::createWithProperties("champion/char-2.png", Statics::createWithProperties(), ChampionStatics::create());
    //auto champ = Champion::create();
    //champ->setIcon("champion/char-2.png");
    //champ->setStatics(Statics::createWithProperties());
    //champ->setChampionStatics(ChampionStatics::create());

    ui = ChampionUI::createDefault();
    std::vector<SkillInGame*> vec;
    cig = ChampionInGame::createWithProperties(champ, ui, dice, vec);
    cig->setPosition(ZYDR_GVS/1.5);
    cig->setStatics(ig2);
    cig->getStatics()->log();
    cig->config();
    player = Player::create();
    player->addChampion(cig);
    this->addChild(player, 1000);
    MAP_MNG_GI->setClientPlayer(player);

    return true;
}

void HelloWorld::wt(Point a, Point b, float h)
{
    Point i((a+b)/2);
}

void HelloWorld::onEnter()
{
    Layer::onEnter();

}

void HelloWorld::runx()
{
    gh = GachaItem::createItemList(
            GachaItem::createWithProperties(1, 1, "A"),
            GachaItem::createWithProperties(10,2, "B"),
            GachaItem::createWithProperties(20,1, "C"),
            nullptr
    );
    gp = ZYGacha::generateSuccessList(gh, 10);

    for(int i = 0; i < gp.size(); i++)
    {
        gp[i]->log();
    }
}
cocos2d::Point HelloWorld::runwt(float newx)
{
    return Point::ZERO;
}
void HelloWorld::update(float dt)
{
    //float time = Director::getInstance()->getTotalFrames() * Director::getInstance()->getAnimationInterval();
    //Vec4 random(time / 10, time, time*2,time*4);
    //for(auto &loc : timeUniforms)
    //{
    //    loc.programState->setUniform(loc.location, &random, sizeof(random));
    //}
    if(player && i == 0)
    {
        if(player->getSelectType() == Player::SelectType::ARENA) {
            i++;
            (player->getSelectObject())->log();
        }
    }
}
void HelloWorld::spawn(float dt)
{
    if(listp.size() < 1000)
    {
        ZYSprite *p = ZYSprite::create("point.png" );
        p->setPosition(charx->getPosition());
        listp.push_back(p);
        this->addChild(listp[listp.size()-1], 7);
    }

   //auto p = Sprite::create("point.png");
   //p->setPosition(px7->getPosition());
   //pl.push_back(p)
   //this->addChild(pl[pl.size()-1], 7);

}
bool HelloWorld::onTouch(cocos2d::Touch *touch, cocos2d::Event *event)
{
    //CCLOG("TRUE");
    i++;
    //CCLOG("%d", i);
    return true;
}
bool HelloWorld::endTouch(cocos2d::Touch *touch, cocos2d::Event *event)
{
    //CCLOG("End");
    //if (i == 5)
    //{
    //    runa();
    //}
    CCLOG("TOUCH LOCATION: %f - %f", touch->getLocation().x, touch->getLocation().y);
    return true;
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
void HelloWorld::run(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:

            //runx();
            break;
        case ui::Widget::TouchEventType::ENDED:
            CCLOG("SELECT");
            //sc1->onSelect();
            //sc1->log();
            //if(sc1->getShapePosition() < ZYDR_GVS/2) sc1->setPosition(sc1->getShapePosition()*1.5);
            //else sc1->setPosition(sc1->getShapePosition()*0.5);
            break;
        default:
            break;
    }
}

void HelloWorld::endS(Ref* pSender, ui::Widget::TouchEventType type)
{

    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            CCLOG("UNSELECT");
            //sc1->onUnselect();
            //sc1->log();
            dice->rollDice();
            //vua->removeFromParentAndCleanup(true);
            ui->update(0);
            break;
        default:
            break;
    }
}

void HelloWorld::runa()
{

}