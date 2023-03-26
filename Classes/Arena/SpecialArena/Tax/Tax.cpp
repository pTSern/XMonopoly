#include "Tax.h"

//// Factory Register

static SpecialArenaTypeRegister<TaxArena> s_register(special_arena_tax_key);

//// Static

TaxArena* TaxArena::createWithProperties(const std::string& title, Coordinate& coord, Size& rectSize, Point& left)
{
    auto ret = new (std::nothrow) TaxArena();
    if(ret && ret->SpecialArena::initWithProperties(title, coord, rectSize, left))
    {
        ret->autorelease();
        ret->config();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

TaxArena* TaxArena::createFullPath(const std::string& title, Coordinate& coord, Size& rectSize, Point& left, float& tax)
{
    auto ret = TaxArena::createWithProperties(title, coord, rectSize, left);
    if(ret)
    {
        ret->setTax(tax);
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//// Constructor

TaxArena::TaxArena()
{

}

//// Virtual

bool TaxArena::init()
{
    return true;
}

void TaxArena::update(float dt)
{
    SpecialArena::update(dt);
}

void TaxArena::onLand(ChampionInGame* pChamp)
{
    SpecialArena::onLand(pChamp);
    auto target = pChamp->getOwner();

    /**
     *  This Champion is not represent its owner
     */
    if(!pChamp->isRepresentPlayer()) return;

    if(target->doPay(target->getNetWorth()*m_fTax))
    {
        /**
         *   Player pay this property's tax
         *   Ask player to repurchase this property
         */
         target->finishAction();
         return;
    }

    /**
     *  This target player can not pay this property's tax
     *  Force player to sell their property
     */
    //if(target->getNetWorth() >= this->getTax())
    //{
    //    target->sellPropertyForTax(this);
    //    return;
    //}

    target->lose();
}

void TaxArena::config()
{
    SpecialArena::config();
    this->setName("TAX ARENA");
    int x = 1;
    if ((int)m_Coord.g_eDir < 0) x = -1;

    m_pTitle->setRotationSkewX(x*GM_GI->getMap()->getAngleVertical());
    m_pTitle->setRotationSkewY(x*GM_GI->getMap()->getAngleHorizon());
}

void TaxArena::log()
{
    SpecialArena::log();
}

std::string TaxArena::toString(int nTab)
{
    return SpecialArena::toString(nTab);
}