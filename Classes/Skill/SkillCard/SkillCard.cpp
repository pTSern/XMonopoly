#include "SkillCard.h"
#include "../SkillInGame/SkillInGame.h"
#include "../SkillManager/SkillManager.h"

USING_NS_ALL

//// Constructor

SkillCard::SkillCard() :
p_pIconSprite(nullptr),
p_pShapeSprite(nullptr),
p_pNameSprite(nullptr),
p_pManaCostSprite(nullptr),
p_pSkillPointCostSprite(nullptr),
p_pDescriptionSprite(nullptr),
p_pCoolDownSprite(nullptr),
p_pNameLabel(nullptr),
p_pDescriptionLabel(nullptr),
p_pManaCostLabel(nullptr),
p_pSkillPointCostLabel(nullptr),
p_pCoolDownLabel(nullptr),
p_bSelected(false),
p_bSelectable(false)
{

}

SkillCard::~SkillCard()
{
    PRESET_FULL_VARIABLE(CC_SAFE_RELEASE);
    CCLOG("SKILL CARD DESTRUCOT");
}

//// Static

SkillCard* SkillCard::createWithProperties(std::string sIconSprite, std::string sShapeSprite, std::string sNameSprite,
                                           std::string sManaCostSprite, std::string sSkillPointCostSprite, std::string sDescriptionSprite,
                                           std::string sCoolDownSprite, std::string sNameLabel, std::string sManaCostLabel,
                                           std::string sSKillPointCostLabel, std::string sCoolDownLabel, std::string sDescriptionLabel)
{
    auto ret = new (std::nothrow) SkillCard();
    if (ret && ret->initWithProperties(sIconSprite, sShapeSprite, sNameSprite, sManaCostSprite, sSkillPointCostSprite, sDescriptionSprite, sCoolDownSprite,
                                       sNameLabel, sManaCostLabel, sSKillPointCostLabel, sCoolDownLabel, sDescriptionLabel))
    {
        ret->autorelease();
        return ret;
    }
    delete ret;
    ret = nullptr;
    return nullptr;
}

SkillCard* SkillCard::createDefault()
{
    auto ret = new (std::nothrow) SkillCard();
    if (ret && ret->initWithProperties("skill_card/icon/default.png",
                                 "skill_card/shape/default.png",
                                 "skill_card/name/default.png",
                                 "skill_card/mana/default.png",
                                 "skill_card/sp/default.png",
                                 "skill_card/description/default.png",
                                 "skill_card/cd/default.png",
                                 "",
                                 "",
                                 "",
                                 "",
                                 ""))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;

}

//// Public

void SkillCard::update(float dt)
{
    if(!p_pOwner || !p_pOwner->isSelectable())
    {
        this->unSelectable();
    }
    else
    {
        this->selectable();
    }
}

bool SkillCard::init()
{
    return this->initWithProperties("skill_card/icon/default.png",
                              "skill_card/shape/default.png",
                              "skill_card/name/default.png",
                              "skill_card/mana/default.png",
                              "skill_card/sp/default.png",
                              "skill_card/description/default.png",
                              "skill_card/cd/default.png",
                              "",
                              "",
                              "",
                              "",
                              "");
}

//Protected

bool SkillCard::initWithProperties(std::string sIconSprite, std::string sShapeSprite, std::string sNameSprite,
                        std::string sManaCostSprite, std::string sSkillPointCostSprite, std::string sDescriptionSprite,
                        std::string sCoolDownSprite, std::string sNameLabel, std::string sManaCostLabel,
                        std::string sSKillPointCostLabel, std::string sCoolDownLabel, std::string sDescriptionLabel)
{
    this->setName("SKILL - CARD");

    p_pIconSprite = ZYSprite::create(sIconSprite.c_str());
    p_pShapeSprite = (ZYSprite::create(sShapeSprite.c_str()));
    p_pNameSprite = (ZYSprite::create(sNameSprite.c_str()));
    p_pManaCostSprite = (ZYSprite::create(sManaCostSprite.c_str()));
    p_pSkillPointCostSprite = (ZYSprite::create(sSkillPointCostSprite.c_str()));
    p_pDescriptionSprite = (ZYSprite::create(sDescriptionSprite.c_str()));
    p_pCoolDownSprite = (ZYSprite::create(sCoolDownSprite.c_str()));

    TTFConfig ttfConfig(globalFont, 18, GlyphCollection::DYNAMIC,nullptr,true);

    p_pSkillPointCostLabel = (ZYLabel::createWithTTF(ttfConfig, sSKillPointCostLabel));
    p_pCoolDownLabel = (ZYLabel::createWithTTF(ttfConfig, sCoolDownLabel));

    ttfConfig.fontSize = p_pNameSprite->getContentSize().height - 2;
    p_pNameLabel = (ZYLabel::createWithTTF(ttfConfig, sNameLabel));

    ttfConfig.fontSize = 20;
    p_pManaCostLabel = (ZYLabel::createWithTTF(ttfConfig, sManaCostLabel));

    ttfConfig.fontSize = 18;
    p_pDescriptionLabel = (ZYLabel::createWithTTF(ttfConfig, sDescriptionLabel));
    p_pDescriptionLabel->setAlignment(TextHAlignment::LEFT);
    p_pDescriptionLabel->setMaxLineWidth(p_pDescriptionSprite->getContentSize().width - 2);

    SET_FULL_LABEL(setTextColor(Color4B::BLACK));
    SET_FULL_LABEL(setTTFConfig(ttfConfig));
    SET_FULL_LABEL(enableOutline(Color4B::RED));

    //PRESET_FULL_VARIABLE(addChild);

    this->addChild(p_pShapeSprite, 0);
    this->addChild(p_pNameSprite, 2);
    this->addChild(p_pManaCostSprite, 3);
    this->addChild(p_pSkillPointCostSprite,2);
    this->addChild(p_pIconSprite, 1);
    this->addChild(p_pDescriptionSprite, 1);
    this->addChild(p_pCoolDownSprite, 1);

    this->addChild(p_pNameLabel, 4);
    this->addChild(p_pDescriptionLabel, 4);
    this->addChild(p_pManaCostLabel, 4);
    this->addChild(p_pSkillPointCostLabel, 4);
    this->addChild(p_pCoolDownLabel, 4);

    p_pButton = ui::Button::create(p_pShapeSprite->getResourceName());
    p_pButton->setOpacity(0);
    this->addChild(p_pButton, 5);

    auto ls = EventListenerTouchOneByOne::create();
    ls->onTouchBegan = CC_CALLBACK_2(SkillCard::onTouch, this);
    ls->onTouchEnded = CC_CALLBACK_2(SkillCard::endTouch, this);
    p_pButton->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ls, p_pButton);
    p_pButton->addTouchEventListener(CC_CALLBACK_2(SkillCard::run, this));

    this->scheduleUpdate();
    return true;
}

//Public![](../../../Resources/skill_card/cd/v4.png)

void SkillCard::setDescriptionLabel(std::string sDescription)
{
    ZYSP_FSIS(p_pDescriptionLabel, sDescription, p_pDescriptionSprite->getContentSize(), MIN_LABEL_SIZE);
    p_pDescriptionLabel->setPosition(Point(p_pDescriptionSprite->getPositionX(), p_pDescriptionSprite->getPositionY() + (p_pDescriptionSprite->getContentSize().height/2 - p_pDescriptionLabel->getContentSize().height/2) ));
    //CCLOG("LLLLLLLL %s - %f", p_pDescriptionLabel->getString().c_str(), p_pDescriptionLabel->getTTFConfig().fontSize);
    //p_pDescriptionLabel->setString(sDescription);

    //this->setDescriptionLabelHelper();
}

void SkillCard::setDescriptionLabelHelper()
{
    //bool isBreak = false;
    //bool isRerun = false;
    //std::string str;
    //auto _c = p_pDescriptionLabel->getTTFConfig();
    //TTFConfig new_c(_c);
    //while(!isBreak)
    //{
    //    if(p_pDescriptionLabel->getContentSize().height > p_pDescriptionSprite->getContentSize().height)
    //    {
    //        new_c.fontSize--;
    //        if(new_c.fontSize < MIN_LABEL_SIZE)
    //        {
    //            str = p_pDescriptionLabel->getString();
    //            str.erase(str.end() - (int)(str.length()*0.1), str.end());
    //            str.insert(str.length(), "...");
    //            isBreak = true;
    //            isRerun = true;
    //        }
    //        else p_pDescriptionLabel->setTTFConfig(new_c);
    //    }
    //    else isBreak = true;
    //}
    //if(!isRerun) p_pDescriptionLabel->setPosition(Point(p_pDescriptionSprite->getPositionX(), p_pDescriptionSprite->getPositionY() + (p_pDescriptionSprite->getContentSize().height/2 - p_pDescriptionLabel->getContentSize().height/2) ));
    //else setDescriptionLabel(str);
}

void SkillCard::config()
{
    //Set Position follow ShapeSprite
    p_pIconSprite->setPosition(p_pShapeSprite->getContentPositionMiddleTop(), Vec2::ANCHOR_MIDDLE_TOP);
    p_pManaCostSprite->setPosition(p_pShapeSprite->getContentPositionTopLeft(), Vec2::ANCHOR_MIDDLE_TOP);

    p_pCoolDownSprite->setPosition(Point(p_pShapeSprite->getContentPositionTopLeft().x, p_pShapeSprite->getContentPositionTopLeft().y - p_pNameSprite->getContentSize().height), Vec2::ANCHOR_TOP_LEFT);

    p_pDescriptionSprite->setPosition(Point(p_pShapeSprite->getContentPositionMiddle().x,
                                            (p_pShapeSprite->getContentSize().height - p_pIconSprite->getContentSize().height)/2 + p_pShapeSprite->getContentPositionMiddleBottom().y + 1));


    //Set Position follow ManaCostSprite
    p_pSkillPointCostSprite->setPosition(Point(p_pManaCostSprite->getContentPositionMiddleTop().x, p_pManaCostSprite->getContentPositionMiddleTop().y - p_pManaCostSprite->getContentSize().height/4*3), Vec2::ANCHOR_MIDDLE_TOP);
    p_pNameSprite->setPosition(p_pManaCostSprite->getContentPositionTopRight(), Vec2::ANCHOR_TOP_LEFT);

    p_pNameLabel->setPosition(Point(p_pShapeSprite->getContentPositionMiddleTop().x, p_pNameSprite->getPositionY()));
    p_pManaCostLabel->setPosition(p_pManaCostSprite->getPosition());
    p_pSkillPointCostLabel->setPosition(p_pSkillPointCostSprite->getPosition());
    p_pCoolDownLabel->setPosition(Point(p_pCoolDownSprite->getPositionX(), p_pCoolDownSprite->getContentPositionWithNewAnchorPoint(Vec2(0.5, 0.75)).y));

    //p_pDescriptionLabel->setPosition(Point(p_pDescriptionSprite->getPositionX(), p_pDescriptionSprite->getPositionY() + (p_pDescriptionSprite->getContentSize().height/2 - p_pDescriptionLabel->getContentSize().height/2) ));
    //setDescriptionLabelHelper();

    p_pDescriptionLabel->setPosition(Point(p_pDescriptionSprite->getPositionX(), p_pDescriptionSprite->getPositionY() + (p_pDescriptionSprite->getContentSize().height/2 - p_pDescriptionLabel->getContentSize().height/2) ));
    //Set Position follow NameSprite
    p_pButton->setPosition(p_pShapeSprite->getPosition());

}

Vec2 SkillCard::getShapePosition()
{
    return p_pShapeSprite->getPosition();
}

//Virtual

void SkillCard::setOpacity(uint8_t opacity)
{
    //cocos2d::Node::setOpacity(opacity);
    SET_FULL_VARIABLE(setOpacity(opacity));
}

void SkillCard::setPosition(const cocos2d::Point &position)
{
    if(position != p_pShapeSprite->getContentPositionMiddle())
    {
        p_pShapeSprite->setPosition(position);
        this->config();
        //auto vec2 = position - p_pShapeSprite->getPosition();
        //auto mb = MoveBy::create(0, vec2);
        //SET_FULL_VARIABLE(runAction(mb->clone()));
    }
}

void SkillCard::selfRepair()
{
    if(p_pManaCostSprite->getContentPositionMiddleTop() != p_pShapeSprite->getContentPositionTopLeft())
    {
        this->config();
    }
}

void SkillCard::onSelect()
{
    if(p_bSelectable)
    {
        p_pOwner->onSelect();
        Vec2 targetPoint(0, p_pShapeSprite->getContentSize().height / 2);
        //this->setPosition(getShapePosition() + targetPoint);
        auto mt = MoveBy::create(0.1, targetPoint);

        runAction(mt);
        p_bSelected = true;
    }
    else p_pOwner->conNotify();
}

void SkillCard::onUnselect()
{
    /// Hard fix, Update later
    p_pOwner->getOwner()->setSelectingSkill(nullptr);

    Vec2 targetPoint(0, -p_pShapeSprite->getContentSize().height/2);
    //this->setPosition(getShapePosition() + targetPoint);
    auto mt = MoveBy::create(0.1, targetPoint);

    this->runAction(mt);
    p_bSelected = false;
}

//Action* SkillCard::runAction(Action* action)
//{
//    CCASSERT(action != nullptr, "Argument must be non-nil");
//    SET_FULL_VARIABLE(runAction(action));
//    return action;
//}

void SkillCard::log()
{
    ZY_EZ_LOG;
}

std::string SkillCard::toString(int nTab)
{
    std::string ts = GameObject::toString(nTab);
    std::string tab = ZYSP_T(nTab);
    ts += (tab + " + Self Position: " + ZYSP_VTS(getPosition()));
    ZY_TSHP(ts, tab, nTab, " > Icon Sprite: ", p_pIconSprite);
    ZY_TSHP(ts, tab, nTab, " > Shape Sprite: ", p_pShapeSprite);
    ZY_TSHP(ts, tab, nTab, " > Name Sprite: ", p_pNameSprite);
    ZY_TSHP(ts, tab, nTab, " > Mana Cost Sprite: ", p_pManaCostSprite);
    ZY_TSHP(ts, tab, nTab, " > Skill Point Cost Sprite: ", p_pSkillPointCostSprite);
    ZY_TSHP(ts, tab, nTab, " > Description Sprite: ", p_pDescriptionSprite);
    ZY_TSHP(ts, tab, nTab, " > Cool Down Sprite: ", p_pCoolDownSprite);
    ZY_TSHP(ts, tab, nTab, " > Name Label: ", p_pNameLabel);
    ZY_TSHP(ts, tab, nTab, " > Description Label: ", p_pDescriptionLabel);
    return ts;
}

Action* SkillCard::runAction(Action *action)
{
    CCASSERT( action != nullptr, "Argument must be non-nil");
    SET_FULL_VARIABLE(runAction(action->clone()));
    return action;
}

bool SkillCard::onTouch(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

bool SkillCard::endTouch(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

void SkillCard::run(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::ENDED)
    {
        if(!p_bSelected)
        {
            onSelect();
        }
        else if(p_bSelected)
        {
            onUnselect();
        }
    }
}

void SkillCard::unSelectable()
{
    p_bSelectable = false;
    SET_FULL_VARIABLE(setColor(Color3B::GRAY));
}

void SkillCard::selectable()
{
    p_bSelectable = true;
    SET_FULL_VARIABLE(setColor(Color3B::WHITE));
}

void SkillCard::disable()
{
    SET_FULL_VARIABLE(setVisible(false));
}

void SkillCard::enable()
{
    SET_FULL_VARIABLE(setVisible(true));
}