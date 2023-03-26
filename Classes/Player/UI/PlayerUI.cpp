#include "PlayerUI.h"

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