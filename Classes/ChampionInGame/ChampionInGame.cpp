#include "ChampionInGame.h"
#include "Arena/Arena.h"
#include "Dice/Dice.h"
#include "ChampionInGame/UI/ChampionUI.h"
#include "Skill/SkillInGame/SkillInGame.h"
#include "Player/Player.h"

///Constructor

ChampionInGame::ChampionInGame() :
m_cCoordinate(Dir::NE, 0),
m_pIngameStatics(nullptr),
m_pLandingArena(nullptr),
m_pParent(nullptr),
m_eHead(HeadDir::FRONT),
m_pOwner(nullptr),
m_bIsRepresentPlayer(false),
m_pChampionUI(nullptr),
m_pDice(nullptr)
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
    auto ret = new (std::nothrow) ChampionInGame();
    if(ret && ret->init() && pChamp)
    {
        ret->autorelease();
        if(bIsClone)
        {
            auto cloner = pChamp->clone();
            if(cloner)
            {
                ret->m_pIcon = cloner->getIcon();
                ret->m_pStatics = cloner->getStatics();
                ret->m_pChampionStatics = cloner->getChampionStatics();
                //ret->m_pIngameStatics = IngameStatics::create(ret->m_pStatics, true, false);
                if(bIsDeleteCloner) CC_SAFE_DELETE(pChamp);
                return ret;
            }
            CC_SAFE_DELETE(cloner);
            CC_SAFE_DELETE(ret);
            return nullptr;
        }

        ret->m_pIcon = pChamp->getIcon();
        ret->m_pStatics = pChamp->getStatics();
        //ret->m_pIngameStatics = IngameStatics::create(ret->m_pStatics, true, false);
        ret->m_pChampionStatics = pChamp->getChampionStatics();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

ChampionInGame* ChampionInGame::createWithProperties(Champion *pChamp, ChampionUI *pUI, Dice* pDice, std::vector<SkillInGame*> vSkillDeck)
{
    auto ret = createWithChampion(pChamp, false);
    if(ret && ret->initWithProperties(pUI, pDice, vSkillDeck))
    {
        ret->config();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//Virtual

void ChampionInGame::config()
{
    m_pChampionUI->setPosition(Point(this->getIcon()->getPosition().x, this->getIcon()->getContentPositionMiddleTop().y + m_pChampionUI->getContentSize().height));
}

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

Point ChampionInGame::getPosition()
{
    return m_pIcon->getPosition();
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

void ChampionInGame::setPosition(cocos2d::Vec2 pos)
{
    this->m_pIcon->setPosition(pos);
    this->m_pSelfButton->setPosition(pos);
}

void ChampionInGame::update(float dt)
{
    CCLOG("VUA");
}

//Public

bool ChampionInGame::initWithProperties(ChampionUI *pUI, Dice* pDice, std::vector<SkillInGame*> vSkillDeck)
{
    if(!pUI || !pDice) return false;

    this->setDice(pDice);
    this->setUI(pUI);
    //this->setSkillDeck(vSkillDeck);

    this->addChild(m_pDice);
    m_pDice->disableDice();

    this->addChild(m_pChampionUI);
    m_pChampionUI->setOwner(this);

    this->addChild(m_pIcon);

    m_pSelfButton = ui::Button::create(m_pIcon->getResourceName());
    this->addChild(m_pSelfButton, 1);

    auto ls = EventListenerTouchOneByOne::create();
    ls->onTouchBegan = CC_CALLBACK_2(ChampionInGame::onTouch, this);
    ls->onTouchEnded = CC_CALLBACK_2(ChampionInGame::endTouch, this);
    m_pSelfButton->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ls, m_pIcon);
    m_pSelfButton->addTouchEventListener(CC_CALLBACK_2(ChampionInGame::run, this));
    return true;
}

void ChampionInGame::addChampChild(ChampionInGame *pChild)
{
    if(pChild)
    {
        m_vChilds.push_back(pChild);
        pChild->setParent(this);
        this->addChild(pChild );
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

void ChampionInGame::preDicePhase()
{

}

void ChampionInGame::doDice()
{

}

void ChampionInGame::postDicePhase()
{

}

void ChampionInGame::setOwner(Player *pOwner, bool bIsRepresent)
{
    this->m_pOwner = pOwner;
    m_bIsRepresentPlayer = bIsRepresent;
}

bool ChampionInGame::onTouch(Touch* touch, Event* event)
{
    return true;
}

bool ChampionInGame::endTouch(Touch* touch, Event* event)
{
    //CCLOG("TOUCH LOCATION: %f - %f", touch->getLocation().x, touch->getLocation().y);
    return true;
}

void ChampionInGame::run(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if(type ==  ui::Widget::TouchEventType::ENDED)
    {
        m_pOwner->setSelectType(Player::SelectType::CHAMPION);
        m_pOwner->setSelectObject(this);
    }
}
