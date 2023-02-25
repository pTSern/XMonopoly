#include "ChampionInGame.h"
#include "Arena/Arena.h"

///Constructor

ChampionInGame::ChampionInGame() :
m_cCoordinate(Dir::NE, 0),
m_pIngameStatics(IngameStatics::create()),
m_pLandingArena(nullptr),
m_pParent(nullptr),
m_eHead(HeadDir::FRONT),
m_pOwner(nullptr),
m_bIsRepresentPlayer(false)
{

}

////Public

void ChampionInGame::setLandingArena(Arena *pArena)
{
    this->m_pLandingArena = pArena;
}

//Static

ChampionInGame* ChampionInGame::createWithChampion(Champion *pChamp, bool bIsClone, bool bIsDeleteCloner)
{
    auto ret = ChampionInGame::create();
    if(ret && pChamp)
    {
        if(bIsClone)
        {
            auto cloner = pChamp->clone();
            if(cloner)
            {
                ret->m_pIcon = cloner->getIcon();
                ret->m_pStatics = cloner->getStatics();
                ret->m_pChampionStatics = cloner->getChampionStatics();
                if(bIsDeleteCloner) CC_SAFE_DELETE(pChamp);
                return ret;
            }
            CC_SAFE_DELETE(cloner);
            CC_SAFE_DELETE(ret);
            return nullptr;
        }

        ret->m_pIcon = pChamp->getIcon();
        ret->m_pStatics = pChamp->getStatics();
        ret->m_pChampionStatics = pChamp->getChampionStatics();
        return ret;
    }
}

//Virtual

bool ChampionInGame::init()
{
    if(!Champion::init()) return false;
    return true;
}

void ChampionInGame::log()
{
    CCLOG("CALL %s: %s %s", ZY_SP_NO_NUMBER_STRING(p_sClassName).c_str(),
          this->toString().c_str(),
          getChildsString(2 + 1).c_str());
}

std::string ChampionInGame::toString(int nTab)
{
    return this->toStringHelper(nTab);
}

void ChampionInGame::setPosition(Coordinate &coord)
{

}

void ChampionInGame::setPosition(Arena *pArena)
{
}

void ChampionInGame::update(float dt)
{

}

//Public

void ChampionInGame::addChampChild(ChampionInGame *pChild)
{
    if(pChild)
    {
        m_vChilds.push_back(pChild);
        pChild->setParent(this);
        this->addChild(pChild, pChild->getGlobalZOrder());
    }
}

void ChampionInGame::setParent(ChampionInGame *pParent)
{
    if(pParent)
    {
        this->m_pParent = pParent;
    }
}

std::string ChampionInGame::toStringHelper(int nTab, bool bIsShowParent)
{
    std::string ts = Champion::toString(nTab);
    std::string tab = ZY_SP_TAB(nTab);
    ZY_TSHP(ts, tab, nTab, " > Ingame Statics: ", m_pIngameStatics);
    ts += (tab + " > Coordinate: " + m_cCoordinate.toString(nTab + 1));
    ts += (tab + " + Head Direction: " + ZYSP_NTS((int)m_eHead));
    ZY_TSHP(ts, tab, nTab, " > Landing Arena: ", m_pLandingArena);
    if(m_pParent && bIsShowParent) ts += (tab + " > Parent: " + m_pParent->toString(nTab + 1));

    return ts;
}

std::string ChampionInGame::getChildsString(int nTab)
{
    std::string child;
    std::string tab = ZY_SP_TAB(nTab);
    for(int i = 0; i < m_vChilds.size(); i++) {
        child += (tab + " + Child[" + ZYSP_NTS(i) + "]: " + m_vChilds[i]->toStringHelper(nTab + 1, false));
    }
    return child;
}

void ChampionInGame::onLand(Arena *arena)
{
    this->attack(arena->getChampionInArena());
    this->applyEffectToSelf(arena->getEffectLayer());
}

void ChampionInGame::applyEffectToSelf(std::vector<GameEffect*> vEffects)
{

}

void ChampionInGame::attack(std::vector<ChampionInGame*> vChampions)
{

}