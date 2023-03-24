#include "ChampionUI.h"
#include "ChampionInGame/ChampionInGame.h"

//// Constructor

ChampionUI::ChampionUI() :
m_pOwner(nullptr),
m_pHpBar(nullptr), m_pManaBackground(nullptr), m_pHpFrontEnd(nullptr),
m_pManaBar(nullptr), m_pHpBackground(nullptr), m_pManaFrontEnd(nullptr),
m_pSkillPoint(nullptr), m_pGlobalBackground(nullptr)
{

}

ChampionUI::~ChampionUI()
{
    CC_SAFE_RELEASE(m_pHpBackground);
    CC_SAFE_RELEASE(m_pHpFrontEnd);
    CC_SAFE_RELEASE(m_pHpBar);
    CC_SAFE_RELEASE(m_pManaFrontEnd);
    CC_SAFE_RELEASE(m_pManaBar);
    CC_SAFE_RELEASE(m_pManaBackground);
    CC_SAFE_RELEASE(m_pSkillPoint);
};
//// Static

ChampionUI* ChampionUI::createWithProperties(const ChampUISup& hp,const ChampUISup& mana, const std::string& globalBackground)
{
    auto ret = new (std::nothrow) ChampionUI();
    if(ret && ret->init() )
    {
        ret->autorelease();
        ret->loadElement(hp, mana, globalBackground);
        ret->config();
        return ret;
    }
    CC_SAFE_RELEASE(ret);
    return nullptr;
}

ChampionUI* ChampionUI::createWithProperties(std::string hp_background, std::string hp_main, std::string hp_front_end, std::string mana_background, std::string mana_main, std::string mana_front_end, std::string global_background)
{
    auto ret = new (std::nothrow) ChampionUI();
    if(ret && ret->init())
    {
        ret->autorelease();
        ret->loadElement(hp_background, hp_main, hp_front_end, mana_background, mana_main, mana_front_end, global_background);
        ret->config();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

ChampionUI* ChampionUI::createDefault()
{
    auto ret = new (std::nothrow) ChampionUI();
    if(ret && ret->init())
    {
        ret->autorelease();
        ret->loadElement(ChampionUISupport("ui/health_bar/background/default.png", "ui/health_bar/health/default.png", "ui/health_bar/front_end/default.png"),ChampionUISupport("ui/mana_bar/background/default.png", "ui/mana_bar/mana/default.png", "ui/mana_bar/front_end/default.png"),"ui/background/default.png");
        ret->config();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//// Virtual

bool ChampionUI::init()
{
    this->scheduleUpdate();
    return true;
}

std::string ChampionUI::toString(int nTab)
{
    std::string ts;
    return ts;
}

void ChampionUI::log()
{

}

void ChampionUI::setPosition(Point position)
{
    m_pGlobalBackground->setPosition(position);
    this->config();
}

//// Public

void ChampionUI::update(float dt)
{
    //auto size = m_pManaBackground->getContentSize().height + m_pHpBackground->getContentSize().height;
    //Size fit(size, size);
    //ZYSP_FSIS(m_pSkillPoint, ZY_SUPPORT_GI->shorterDecimal(m_pOwner->getStatics()->getCurrentSp(), 1), fit, 6);
    //m_pSkillPoint->setString(ZY_SUPPORT_GI->shorterDecimal(m_pOwner->getStatics()->getCurrentSp(), 1));
    m_pHpBar->setPercent(m_pOwner->getStatics()->getCurrentHpInPercent() * 100);
    m_pManaBar->setPercent(m_pOwner->getStatics()->getCurrentMnInPercent() * 100);
}

void ChampionUI::updateAfterMoving()
{
    this->setPosition(Point(m_pOwner->getPosition().x, m_pOwner->getIcon()->getContentPositionMiddleTop().y + m_pGlobalBackground->getContentSize().height/2));
}

void ChampionUI::config()
{
    auto border = (m_pGlobalBackground->getContentSize().height - m_pManaBackground->getContentSize().height - m_pHpBackground->getContentSize().height)/2;

    m_pHpBackground->setPosition(Point(m_pGlobalBackground->getPositionX(), m_pGlobalBackground->getContentPositionMiddleTop().y - border), Vec2::ANCHOR_MIDDLE_TOP);
    m_pHpBar->setPosition(m_pHpBackground->getPosition());
    m_pHpFrontEnd->setPosition(m_pHpBackground->getPosition());

    m_pManaBackground->setPosition(Point(m_pGlobalBackground->getPositionX(), m_pGlobalBackground->getContentPositionMiddleBottom().y + border), Vec2::ANCHOR_MIDDLE_BOTTOM);
    m_pManaBar->setPosition(m_pManaBackground->getPosition());
    m_pManaFrontEnd->setPosition(m_pManaBackground->getPosition());

    m_pSkillPoint->setPosition(Point(m_pGlobalBackground->getContentPositionTopRight().x - m_pSkillPoint->getContentSize().width/2,m_pGlobalBackground->getPositionY()));
}

//// Protected

void ChampionUI::loadElement(const ChampUISup& hp, const ChampUISup& mana, const std::string& globalBackground)
{
    this->loadElement(hp.g_sBackground, hp.g_sMain, hp.g_sFrontEnd, mana.g_sBackground, mana.g_sMain, mana.g_sFrontEnd, globalBackground);
}

void ChampionUI::loadElement(std::string hp_background, std::string hp_main, std::string hp_front_end, std::string mana_background, std::string mana_main, std::string mana_front_end, std::string global_background)
{
    m_pHpBar = ui::LoadingBar::create(hp_main);
    m_pHpFrontEnd = ZYSprite::create(hp_front_end.c_str());
    m_pHpBackground = ZYSprite::create(hp_background.c_str());

    m_pManaBar = ui::LoadingBar::create(mana_main);
    m_pManaBackground = ZYSprite::create(mana_background.c_str());
    m_pManaFrontEnd = ZYSprite::create(mana_front_end.c_str());

    TTFConfig ttfConfig(globalFont, 14, GlyphCollection::DYNAMIC,nullptr);
    m_pSkillPoint = ZYLabel::createWithTTF(ttfConfig, "");

    m_pGlobalBackground = ZYSprite::create(global_background.c_str());

    this->addChild(m_pGlobalBackground, 0);

    this->addChild(m_pHpBackground, 1);
    this->addChild(m_pManaBackground, 1);

    this->addChild(m_pHpBar, 2);
    this->addChild(m_pManaBar, 2);
    this->addChild(m_pSkillPoint, 2);

    this->addChild(m_pManaFrontEnd, 3);
    this->addChild(m_pHpFrontEnd, 3);
}