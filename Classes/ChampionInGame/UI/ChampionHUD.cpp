#include "ChampionHUD.h"
#include "ChampionInGame/ChampionInGame.h"
#include "Player/Player.h"
#include "Support/GameConstant.h"

///] Static

ChampionHUD* ChampionHUD::createWithChampion(ChampionInGame* pOwner)
{
    auto ret = new (std::nothrow) ChampionHUD();
    if(ret && ret->initWithChampion(pOwner))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

///] Constructor

ChampionHUD::ChampionHUD() :
m_pOwner(nullptr),
m_pAvatar(nullptr),
m_pChampionName(nullptr),
m_pAtkDmg(nullptr), m_pMagicDmg(nullptr),
m_pArmor(nullptr), m_pMagicRes(nullptr),
m_pLifeSteal(nullptr), m_pMagicLifeSteal(nullptr),
m_pHpBar(nullptr), m_pManaBar(nullptr), m_pSpBar(nullptr),
m_pHpBackground(nullptr), m_pManaBackground(nullptr), m_pSpBackground(nullptr),
m_pHp(nullptr), m_pMana(nullptr), m_pSp(nullptr),
m_pLife(nullptr), m_pSpeed(nullptr),
m_pAtkBox(nullptr), m_pDefBox(nullptr),
m_pBackgroundBox(nullptr),
m_bIsShow(false), m_pTinyBox(nullptr),
m_pAtkBoxLabel(nullptr), m_pDefBoxLabel(nullptr)
{

}

///] Virtual

bool ChampionHUD::init()
{
    return true;
}

std::string ChampionHUD::toString(int nTab)
{

}

void ChampionHUD::log()
{
    ZY_EZ_LOG;
}

void ChampionHUD::update(float dt)
{
    this->updateString();
}

///] Public

void ChampionHUD::updateString()
{
    auto igs = m_pOwner->getStatics();
    auto statics = igs->getStatics();
    m_pAtkDmg->setString(ZYSP_SRF(statics->getAttackDmg(), 2));
    m_pMagicDmg->setString(ZYSP_SRF(statics->getMagicDmg(), 2));
    m_pLife->setString(std::to_string(statics->getLife()));
    m_pSpeed->setString(ZYSP_SRF(statics->getSpeed(), 2));
    m_pArmor->setString(ZYSP_SRF(statics->getArmor(), 2));
    m_pMagicRes->setString(ZYSP_SRF(statics->getMagicResistance(), 2));
    m_pLifeSteal->setString(ZYSP_SRF(statics->getPCLifeSteal(), 2));
    m_pMagicLifeSteal->setString(ZYSP_SRF(statics->getPCMagicLifeSteal(), 2));
    m_pHp->setString(ZYSP_SRF(igs->getCurrentHp(),2) + " / " + ZYSP_SRF(statics->getMaxHp(), 2));
    m_pMana->setString(ZYSP_SRF(igs->getCurrentMana(),2) + " / " + ZYSP_SRF(statics->getMaxMana(), 2));
    m_pSp->setString(ZYSP_SRF(igs->getCurrentSp(),2) + " / " + ZYSP_SRF(statics->getMaxSkillPoint(), 2));
    m_pHpBar->setPercent(igs->getCurrentHpInPercent() * 100);
    m_pManaBar->setPercent(igs->getCurrentMnInPercent() * 100);
    m_pSpBar->setPercent(igs->getCurrentSpInPercent() * 100);
}

void ChampionHUD::initAllElement()
{
    m_pManaBar = ui::LoadingBar::create(MNBF_DIR("default.png"));
    m_pManaBackground = ZYSprite::create(MNBGF_DIR("default.png"));
    this->addChild(m_pManaBar);
    this->addChild(m_pManaBackground, -1);
    m_pSpBar = ui::LoadingBar::create(SPBF_DIR("default.png"));
    m_pSpBackground = ZYSprite::create(SPBGF_DIR("default.png"));
    this->addChild(m_pSpBar);
    this->addChild(m_pSpBackground, -1);
    m_pAvatar = ui::Button::create("avatar/champion/char-3.png");
    this->addChild(m_pAvatar);

    auto ttf = defaultTTFConfig;
    ttf.fontSize = 16;

    auto igs = m_pOwner->getStatics();
    auto statics = igs->getStatics();
    m_pChampionName = ZYLabel::createWithTTF(ttf, m_pOwner->getName());
    this->addChild(m_pChampionName, 1);
    m_pAtkDmg = ZYLabel::createWithTTF(ttf, ZYSP_SRF(statics->getAttackDmg(), 2));
    this->addChild(m_pAtkDmg, 1);
    m_pMagicDmg = ZYLabel::createWithTTF(ttf, ZYSP_SRF(statics->getMagicDmg(), 2));
    this->addChild(m_pMagicDmg, 1);
    m_pArmor = ZYLabel::createWithTTF(ttf, ZYSP_SRF(statics->getArmor(), 2));
    this->addChild(m_pArmor, 1);
    m_pMagicRes = ZYLabel::createWithTTF(ttf, ZYSP_SRF(statics->getMagicResistance(), 2));
    this->addChild(m_pMagicRes, 1);
    m_pLifeSteal = ZYLabel::createWithTTF(ttf, ZYSP_SRF(statics->getPCLifeSteal(), 2));
    this->addChild(m_pLifeSteal, 1);
    m_pMagicLifeSteal = ZYLabel::createWithTTF(ttf, ZYSP_SRF(statics->getPCMagicLifeSteal(), 2));
    this->addChild(m_pMagicLifeSteal, 1);

    auto ls = EventListenerTouchOneByOne::create();
    ls->onTouchBegan = CC_CALLBACK_2(ChampionHUD::onTouchBegin, this);
    ls->onTouchEnded = CC_CALLBACK_2(ChampionHUD::onTouchEnd, this);
    m_pAvatar->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ls, m_pAvatar);
    m_pAvatar->addTouchEventListener(CC_CALLBACK_2(ChampionHUD::showMoreButton, this));

    ttf.fontSize = 24;
    ttf.bold = true;
    m_pAtkBox = ZYSprite::create("hud/helper/small_box.png");
    this->addChild(m_pAtkBox);
    m_pAtkBoxLabel = ZYLabel::createWithTTF(ttf, "ATTACK");
    this->addChild(m_pAtkBoxLabel, 1);
    m_pDefBox = ZYSprite::create("hud/helper/small_box.png");
    this->addChild(m_pDefBox);
    m_pDefBoxLabel = ZYLabel::createWithTTF(ttf, "DEFENSE");
    this->addChild(m_pDefBoxLabel, 1);
    m_pBackgroundBox = ZYSprite::create("hud/helper/big_box.png");
    this->addChild(m_pBackgroundBox, -1);
    m_pTinyBox = ZYSprite::create("hud/helper/tiny_box.png");
    this->addChild(m_pTinyBox, -1);

    if(m_pOwner->getOwner()->isClient())
    {
        m_pHpBar = ui::LoadingBar::create(HPBF_DIR("default.png"));
        m_pHpBackground = ZYSprite::create(HPBGF_DIR("default.png"));
    }
    else
    {
        m_pHpBar = ui::LoadingBar::create(HPBF_DIR("enemy.png"));
        m_pHpBackground = ZYSprite::create(HPBGF_DIR("enemy.png"));
    }
    this->addChild(m_pHpBar);
    this->addChild(m_pHpBackground, -1);

    ttf.bold = false;
    ttf.fontSize = m_pHpBar->getContentSize().height - 4;
    m_pHp = ZYLabel::createWithTTF(ttf, "");
    this->addChild(m_pHp, 1);
    ttf.fontSize = m_pManaBar->getContentSize().height - 4;
    m_pMana = ZYLabel::createWithTTF(ttf, "");
    this->addChild(m_pMana, 1);
    ttf.fontSize = m_pSpBar->getContentSize().height - 4;
    m_pSp = ZYLabel::createWithTTF(ttf, "");
    this->addChild(m_pSp, 1);
    m_pLife = ZYLabel::createWithTTF(ttf, ZYSP_SRF(statics->getLife(), 2));
    this->addChild(m_pLife, 1);
    m_pSpeed = ZYLabel::createWithTTF(ttf, ZYSP_SRF(statics->getSpeed(), 2));
    this->addChild(m_pSpeed, 1);

    SET_SHOW_MORE_BOARD_HELPER(setVisible(false));
    this->scheduleUpdate();
    this->config();
}

void ChampionHUD::config()
{
    m_pAvatar->setPosition(m_pAvatar->getContentSize()/2);

    m_pTinyBox->setPosition(Point(m_pAvatar->getPositionX(), m_pAvatar->getPositionY() + m_pAvatar->getContentSize().height/2), Vec2::ANCHOR_MIDDLE_BOTTOM);
    m_pBackgroundBox->setPosition(Point(m_pBackgroundBox->getContentSize().width/2, m_pTinyBox->getContentPositionMiddleTop().y + m_pBackgroundBox->getContentSize().height/2));
    auto distance = (m_pBackgroundBox->getContentSize().width - m_pAtkBox->getContentSize().width*2)/3;
    m_pAtkBox->setPosition(Point(distance + m_pAtkBox->getContentSize().width/2 ,m_pBackgroundBox->getPositionY()));
    m_pAtkBoxLabel->setPosition(Point(m_pAtkBox->getPositionX(), m_pAtkBox->getContentPositionMiddleTop().y - m_pAtkBoxLabel->getContentSize().height/2));
    m_pDefBox->setPosition(Point(distance*2 + m_pAtkBox->getContentSize().width/2*3, m_pBackgroundBox->getPositionY()));
    m_pDefBoxLabel->setPosition(Point(m_pDefBox->getPositionX(), m_pDefBox->getContentPositionMiddleTop().y - m_pAtkBoxLabel->getContentSize().height/2));



    m_pManaBackground->setPosition(Point(m_pAvatar->getContentSize().width + distance, m_pManaBackground->getContentSize().height/2), Vec2::ANCHOR_MIDDLE_LEFT);
    m_pManaBar->setPosition(m_pManaBackground->getPosition());
    m_pMana->setPosition(m_pManaBar->getPosition());
    m_pHpBackground->setPosition(Point(m_pManaBackground->getContentPositionMiddleLeft().x, m_pManaBackground->getContentPositionMiddleTop().y + distance + m_pHpBackground->getContentSize().height/2), Vec2::ANCHOR_MIDDLE_LEFT);
    m_pHpBar->setPosition(m_pHpBackground->getPosition());
    m_pHp->setPosition(m_pHpBar->getPosition());
    m_pSpBackground->setPosition(Point(m_pHpBackground->getContentPositionMiddleLeft().x, m_pHpBackground->getContentPositionMiddleTop().y + distance + m_pSpBackground->getContentSize().height/2), Vec2::ANCHOR_MIDDLE_LEFT);
    m_pSpBar->setPosition(m_pSpBackground->getPosition());
    m_pSp->setPosition(m_pSpBar->getPosition());
    if(!m_pOwner->getOwner()->isClient()) disable();
}

bool ChampionHUD::initWithChampion(ChampionInGame *pOwner)
{
    if(!GameObject::init()) return false;

    this->setOwner(pOwner);
    this->initAllElement();
    this->scheduleUpdate();

    return true;
}

bool ChampionHUD::onTouchBegin(Touch *touch, Event* event)
{
    return true;
}

void ChampionHUD::onTouchEnd(Touch *touch, Event* event)
{

}

void ChampionHUD::showMoreButton(Ref* pSender, ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::ENDED)
    {
        m_bIsShow = !m_bIsShow;
        showMore();
    }
}

void ChampionHUD::showMore()
{
    if(m_bIsShow)
    {
        SET_SHOW_MORE_BOARD_HELPER(setVisible(true));
    }
    else
    {
        SET_SHOW_MORE_BOARD_HELPER(setVisible(false));
    }
}

void ChampionHUD::disable()
{
    if(m_bIsShow)
    {
        m_bIsShow = !m_bIsShow;
        this->showMore();
    }
    SET_STATS_BOARD_HELPER(setVisible(false));
}

void ChampionHUD::enable()
{
    SET_STATS_BOARD_HELPER(setVisible(true));
}