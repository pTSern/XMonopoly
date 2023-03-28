#include "PlayerUI.h"
#include "ChampionInGame/UI/ChampionHUD.h"
#include "Player/Player.h"

//// Constructor

PlayerUI::PlayerUI() :
m_pAtk(nullptr),
m_pArmor(nullptr),
m_pSpeed(nullptr),
m_pLife(nullptr)
{

}

///] Statics

PlayerUI* PlayerUI::createClientUI()
{
    auto ret = new (std::nothrow) PlayerUI();
    if(ret && ret->initWithUserData())
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

///] Public

bool PlayerUI::initWithUserData()
{
    m_pArmor = ZYSprite::create(icon_armor_dir);
    m_pSpeed = ZYSprite::create(icon_speed_dir);
    m_pAtk = ZYSprite::create(icon_attack_dir);
    m_pLife = ZYSprite::create(icon_life_dir);

    auto hj = fixed_avatar_size.height/5;
    auto hw = fixed_avatar_size.width;

    m_pLife->setPosition(Point(hw - m_pLife->getContentSize().width, hj), Vec2::ANCHOR_MIDDLE_BOTTOM);
    m_pSpeed->setPosition(Point(hw - m_pSpeed->getContentSize().width, hj*2), Vec2::ANCHOR_MIDDLE_BOTTOM);
    m_pArmor->setPosition(Point(hw - m_pArmor->getContentSize().width, hj*3), Vec2::ANCHOR_MIDDLE_BOTTOM);
    m_pAtk->setPosition(Point(hw - m_pAtk->getContentSize().width, hj*4), Vec2::ANCHOR_MIDDLE_BOTTOM);

    this->addChild(m_pAtk);
    this->addChild(m_pArmor);
    this->addChild(m_pLife);
    this->addChild(m_pSpeed);

    m_pBackground = ZYSprite::create("ui/hud/default.png");
    m_pBackground->setPosition(m_pBackground->getContentSize()/2);
    this->addChild(m_pBackground , -1);
    m_pBackground->setGlobalZOrder(-1);

    return true;
}

//// Virtual

bool PlayerUI::init()
{
    return true;
}

void PlayerUI::log()
{

}

std::string PlayerUI::toString(int nTab)
{
    std::string ts;
    return ts;
}

//// Public