#include "ChampionInGame.h"
#include "Arena/Arena.h"
#include "Dice/Dice.h"
#include "ChampionInGame/UI/ChampionUI.h"
#include "ChampionInGame/UI/ChampionHUD.h"
#include "Skill/SkillManager/SkillManager.h"
#include "Player/Player.h"
#include "GameMaster/GameMaster.h"
#include "Audio/SoundManager.h"

///Constructor

ChampionInGame::ChampionInGame() :
m_cCoordinate(Dir::NE, 0),
m_pIngameStatics(nullptr),
m_pLandingArena(nullptr), m_pMemArena(nullptr),
m_pParent(nullptr),
m_eHead(HeadDir::FRONT),
m_pOwner(nullptr),
m_bIsRepresentPlayer(false),
m_pChampionUI(nullptr),
m_pDice(nullptr),
m_eStatus(ChampionStatus::NORMAL),
m_eAction(ChampionAction::IDLE),
m_eTurnPhase(ChampionTurnPhase::NONE),
m_pChampionHUD(nullptr),
m_pPreDiceSkillDeck(nullptr),
m_pPostDiceSkillDeck(nullptr),
m_pSelfButton(nullptr),
m_bIsTurn(false), m_bIsEndTurn(false),
m_bIsAction(false),
p_nCurrentJump(0), p_nJumpTime(0)
{

}

///] Static

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
                //ret->m_pIngameStatics = IngameStatics::createWithStatics(ret->m_pStatics, true, false);
                if(bIsDeleteCloner) CC_SAFE_DELETE(pChamp);
                return ret;
            }
            CC_SAFE_DELETE(cloner);
            CC_SAFE_DELETE(ret);
            return nullptr;
        }

        ret->m_pIcon = pChamp->getIcon();
        ret->m_pStatics = pChamp->getStatics();
        //ret->m_pIngameStatics = IngameStatics::createWithStatics(ret->m_pStatics, true, false);
        ret->m_pChampionStatics = pChamp->getChampionStatics();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

ChampionInGame* ChampionInGame::createWithProperties(Champion *pChamp , ChampionUI *pUI, Dice* pDice, SkillManager* vSkillDeck)
{
    //auto ret = createWithChampion(pChamp, false);
    auto ret = new (std::nothrow) ChampionInGame();

    if(ret && ret->initWithProperties(pChamp, pUI, pDice, vSkillDeck))
    {
        ret->autorelease();
        ret->disable();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

///] Virtual

bool ChampionInGame::initWithProperties(Champion* champ, ChampionUI *pUI, Dice* pDice, SkillManager* vSkillDeck)
{
    this->m_pIcon = champ->getIcon()->clone();
    this->m_pStatics = champ->getStatics()->clone();
    this->m_pChampionStatics = champ->getChampionStatics()->clone();
    return initWithProperties(pUI, pDice, vSkillDeck);
}

void ChampionInGame::config()
{
    m_pChampionUI->setPosition(Point(this->getIcon()->getPosition().x, this->getIcon()->getContentPositionMiddleTop().y + m_pChampionUI->getContentSize().height));
    m_pSelfButton->setPosition(m_pIcon->getPosition());
    m_pPhysicBody->setPositionOffset(m_pIcon->getPosition());
    auto y = m_pIcon->getPositionY();
    m_pAnimate->setPosition(Point(m_pIcon->getPositionX(), m_pIcon->getContentSize().height/4 + y));
}

bool ChampionInGame::init()
{
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
    this->setPosition(GM_GI->getMap()->getArenaByCoord(coord));
}

void ChampionInGame::setPosition(Arena *pArena)
{
    auto pos = pArena->getMoveAblePosition();
    this->setPosition(Point(pos.x, pos.y + m_pIcon->getContentSize().height/2));
    this->m_pLandingArena = pArena;
    this->onLand(false);
    //this->m_pMemArena = m_pLandingArena;
    //this->m_pLandingArena = pArena;
    //this->endLand();
    //this->onLand(false);
}

void ChampionInGame::setPosition(cocos2d::Vec2 pos)
{
    this->m_pIcon->setPosition(pos);
    //this->m_pSelfButton->setPosition(pos);
}

void ChampionInGame::update(float dt)
{
    this->config();
    this->lifeCheck();
    this->autoFlip();
}

void ChampionInGame::contactTo(PhysicsContact& contact, GameObject* target)
{
    //CCLOG("%s Contact to %s", getName().c_str(), target->getName().c_str());
}

void ChampionInGame::contactBy(PhysicsContact& contact, GameObject* target)
{
    //CCLOG("%s Contact by %s", getName().c_str(), target->getName().c_str());
}

///] Public

void ChampionInGame::setLandingArena(Arena *pArena)
{
    this->m_pLandingArena = pArena;
}

bool ChampionInGame::initWithProperties(ChampionUI *pUI, Dice* pDice, SkillManager* vSkillDeck)
{
    if(!pUI || !pDice || !vSkillDeck || !Champion::init()) return false;
    this->setName("CHAMPION IN GAME");

    //m_pIcon->setOpacity(0);
    m_pIcon->setVisible(false);

    this->setDice(pDice);
    this->setUI(pUI);
    this->setPreDiceSkillDeck(vSkillDeck);

    this->addChild(m_pPreDiceSkillDeck);
    m_pPreDiceSkillDeck->setOwner(this);

    this->addChild(m_pDice);
    const auto pos = vSkillDeck->getUseButtonPosition();
    m_pDice->setDiceButtonPosition(Point(pos.x, pos.y + m_pDice->getDiceButtonSize().height));
    m_pDice->disableDice();

    this->addChild(m_pChampionUI);
    m_pChampionUI->setOwner(this);

    this->addChild(m_pIcon);

    m_pSelfButton = ui::Button::create(m_pIcon->getResourceName());
    this->m_pSelfButton->setOpacity(0);

    this->addChild(m_pSelfButton, 1);

    auto ls = EventListenerTouchOneByOne::create();
    ls->onTouchBegan = CC_CALLBACK_2(ChampionInGame::onTouch, this);
    ls->onTouchEnded = CC_CALLBACK_2(ChampionInGame::endTouch, this);
    m_pSelfButton->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ls, m_pSelfButton);
    m_pSelfButton->addTouchEventListener(CC_CALLBACK_2(ChampionInGame::run, this));

    this->m_pIngameStatics = IngameStatics::create();
    this->m_pIngameStatics->setStatics(m_pStatics->clone());
    this->m_pIngameStatics->fillStatics(100);

    m_pPhysicBody = PhysicsBody::createBox(m_pIcon->getContentSize());
    m_pPhysicBody->setDynamic(false);
    m_pPhysicBody->setGravityEnable(false);
    m_pPhysicBody->setContactTestBitmask(GM_GI->getBitMask());
    this->setPhysicsBody(m_pPhysicBody);

    this->scheduleUpdate();
    initAnimation();
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

void ChampionInGame::onLand(bool attack)
{
    if(attack)
    {
        auto v = m_pLandingArena->getChampionInArena();
        this->attack(v);
    }
    else
    {
        this->m_pLandingArena->addChampion(this, attack);
        this->m_cCoordinate = m_pLandingArena->getCoordinate();
    }
}

void ChampionInGame::landOnArena()
{
    this->m_pLandingArena->addChampion(this, true);
    this->m_cCoordinate = m_pLandingArena->getCoordinate();
}

void ChampionInGame::endLand()
{
    if(m_pMemArena)
    {
        m_pMemArena->removeChampion(this);
    }
}

void ChampionInGame::applyEffectToSelf(std::vector<GameEffect*> vEffects)
{

}

void ChampionInGame::attack(std::vector<ChampionInGame*>& vChampions)
{
    auto delay = GM_GI->attackScene(this, vChampions);
    //for(auto &x : vChampions)
    //{
    //    x->beAttacked(this);
    //}
    auto seq = Sequence::create(DelayTime::create(delay),
                                CallFunc::create(
                                        [&]()
                                        {
                                            landOnArena();
                                        }
                                        ), nullptr);
    runAction(seq);
}

void ChampionInGame::beAttacked(ChampionInGame* attacker)
{
    //TEST
    this->getStatics()->reduceHp(attacker->getStatics()->getStatics()->getAttackDmg());
}

void ChampionInGame::beAttacked(SkillStatics *pStatics, ChampionInGame* attacker)
{

}

void ChampionInGame::reduceHp(float amount)
{
    this->getStatics()->reduceHp(amount);
}

void ChampionInGame::setOwner(Player *pOwner, bool bIsRepresent)
{
    this->m_pOwner = pOwner;
    this->m_bIsRepresentPlayer = bIsRepresent;

    ///\ Set champion out line color
    auto outline = ZYOutlineV2::create();
    outline->setColor(this->m_pOwner->getTheColor());
    this->m_pIcon->setEffect(outline);

    this->m_pChampionHUD = ChampionHUD::createWithChampion(this);
    this->addChild(m_pChampionHUD);
}

bool ChampionInGame::onTouch(Touch* touch, Event* event)
{
    return true;
}

bool ChampionInGame::endTouch(Touch* touch, Event* event)
{
    return true;
}

void ChampionInGame::run(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::BEGAN)
    {
        m_pSelfButton->setOpacity(125);
    }
    else if(type ==  ui::Widget::TouchEventType::ENDED)
    {
        GM_GI->getClientPlayer()->setSelectObject(this, Player::SelectType::CHAMPION);
        m_pSelfButton->setOpacity(0);
    }
}

void ChampionInGame::startTurn()
{
    ///v This condition to force the bot to stop start turn
    ///) Enable this champion
    //this->enable();

    ///v Cooldown all skill
    if(m_pPreDiceSkillDeck) m_pPreDiceSkillDeck->cooldown();
    if(m_pPostDiceSkillDeck) m_pPostDiceSkillDeck->cooldown();

    ///) Regen stats
    this->m_pIngameStatics->regen();

    ///) Add check buff/debuff condition here

    ///) This champion is on turn and does not finish the turn(end turn)
    this->m_bIsTurn = true;
    this->m_bIsEndTurn = false;

    ///) The owner now controlling this champion
    this->m_pOwner->setControlChampion(this);

    ///) Enter the pre-dice phase
    this->enterPreDicePhase();
}

void ChampionInGame::enterPreDicePhase()
{
    ///) This player is now on pre-dice phase
    this->m_eTurnPhase = ChampionTurnPhase::PRE_DICE;
}

void ChampionInGame::endPreDicePhase()
{
    ///) Check if this champion can enter the pos-dice phase. Call endTurn() if not
    if(!canEnterPostDice()) endTurn();
}

bool ChampionInGame::canEnterPostDice()
{
    return false;
}

void ChampionInGame::enterPostDicePhase()
{
    this->m_eTurnPhase = ChampionTurnPhase::POS_DICE;
}

void ChampionInGame::endPostDicePhase()
{
}

void ChampionInGame::endTurn()
{
    ///) This champion is not on turn and finishes the turn
    CCLOG("CHAMPION END TURN %s", getOwner()->getName().c_str());
    this->m_bIsTurn = false;
    this->m_bIsEndTurn = true;
    this->m_eAction = ChampionAction::IDLE;
    m_eTurnPhase = ChampionTurnPhase::NONE;
}

void ChampionInGame::enableDice()
{
    ///) Enable the dice
    this->m_pDice->enableDice();
}

void ChampionInGame::lifeCheck()
{
     if(!m_pIngameStatics->isAlive())
     {
         this->onDying();

         if (m_pIngameStatics->doRespawn())
         {
             this->respawn();
             this->endTurn();
         }
         else this->onDeath();
     }
}

void ChampionInGame::onDeath()
{
    /// replace sprite to death image
    this->m_pIcon->replaceSprite("champion/death.png");
    this->m_pIcon->setVisible(true);
    this->m_pAnimate->setVisible(false);
    this->m_pSelfButton->setVisible(false);
    this->m_eStatus = ChampionStatus::DEATH;
    this->m_pOwner->checkLoseCondition();
}

void ChampionInGame::onDying()
{
    /// Do dying thing
    this->m_eStatus = ChampionStatus::DYING;
    this->m_pMemArena = m_pLandingArena;
    this->endLand();
}

void ChampionInGame::respawn()
{
    /// Respawn champion
    this->m_eStatus = ChampionStatus::NORMAL;

    /// Respawn at Hospital
    auto hospital = GM_GI->getMap()->getArenaByCoord(GM_GI->getMap()->getHospitalCoord());
    //this->m_pLandingArena = hospital;
    m_pSelfButton->setVisible(true);
    this->setPosition(hospital);
    //this->onLand();
}

void ChampionInGame::autoFlip()
{
    this->m_pIcon->setFlippedX(m_cCoordinate.g_bIsFlip);
    this->m_pAnimate->setFlippedX(m_cCoordinate.g_bIsFlip);
    this->m_pSelfButton->setFlippedX(m_cCoordinate.g_bIsFlip);
}

void ChampionInGame::jumpTo(int num)
{
    this->p_nJumpTime = num;
    this->p_nCurrentJump = 0;
    this->jumpToNextCoord();
}

void ChampionInGame::jumpToNextCoord()
{
    //this->m_cCoordinate.g_nIndex += 1;
    m_cCoordinate.nextIndex();
    this->p_nCurrentJump ++;
    //if(m_cCoordinate.g_nIndex >= GM_GI->getMap()->getArenas().size())
    //{
    //    m_cCoordinate.g_nIndex-=(GM_GI->getMap()->getArenas().size());
    //}
    this->jumpTo(m_cCoordinate);
}

void ChampionInGame::jumpTo(Point pos)
{
    m_eAction = ChampionAction::MOVING;
    ///v Target point
    auto target = Point(pos.x, pos.y + m_pIcon->getContentSize().height/2);
    ///v Jump distance
    auto distance = this->getPosition().distance(target);
    ///v Start create actions
    auto jump = JumpTo::create(distance/400, target, this->m_pIcon->getContentSize().height/2, 1);
    auto callback = CallFunc::create(CC_CALLBACK_0(ChampionInGame::endJump, this));
    auto playSound = CallFunc::create(
            [&]()
            {
                SM_GI->playSoundEffect("audio/move/move.mp3");
            }
            );
    auto seq = Sequence::create(jump, playSound, callback, nullptr);
    ///^ End create actions
    this->m_pIcon->runAction(seq);
    //this->m_pSelfButton->runAction(seq->clone());
}

void ChampionInGame::jumpTo(Coordinate coord)
{
    this->jumpTo(GM_GI->getMap()->getArenaByCoord(coord));
}

void ChampionInGame::jumpTo(Arena *arena)
{
    this->m_pMemArena = m_pLandingArena;
    this->m_pLandingArena = arena;
    this->jumpTo(arena->getMoveAblePosition());
}

void ChampionInGame::endJump()
{
    auto attack = false;
    if(p_nCurrentJump == p_nJumpTime)
    {
        attack = true;
        ///< Force champion to end the current phase
        switch (m_eTurnPhase)
        {
            case ChampionTurnPhase::PRE_DICE:
                this->endPreDicePhase();
                break;
            case ChampionTurnPhase::POS_DICE:
                this->endPostDicePhase();
                break;
        }
    }
    this->endLand();
    this->onLand(attack);
    if(p_nCurrentJump < p_nJumpTime)
    {
        jumpToNextCoord();
    }
}
void ChampionInGame::castingSkill(float& manaCost, float& hpCost, float& SpCost)
{
    this->m_eAction = ChampionInGame::ChampionAction::CASTING_SKILL;

    /// Reduce Static
    this->m_pIngameStatics->reduceHp(hpCost);
    this->m_pIngameStatics->reduceMana(manaCost);
    this->m_pIngameStatics->reduceSp(SpCost);
}

void ChampionInGame::enable()
{
    this->m_pOwner->enable();
    this->m_pDice->enable();
    this->m_pPreDiceSkillDeck->enable();
}

void ChampionInGame::disable()
{
    this->m_pDice->disable();
    this->m_pPreDiceSkillDeck->disable();
}

void ChampionInGame::setHUD(bool var)
{
    if(var) this->m_pChampionHUD->enable();
    else this->m_pChampionHUD->disable();
}

bool ChampionInGame::isValidTurn()
{
    return m_bIsEndTurn;
}

void ChampionInGame::initAnimation()
{
    auto path = m_pIcon->getResourceName();
    m_pAnimate = m_pIcon->clone();
    this->addChild(m_pAnimate, 1);
    //Remove ".png"
    auto path_name = (path.substr(9, path.length() - 13) + "_idle");
    auto ani_path = "champion/ani/" + path_name + ".png";
    auto ani_plist = "champion/ani/" + path_name + ".plist";

    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile(ani_plist);

    //auto ani_cache = AnimationCache::getInstance();
    //ani_cache->addAnimationsWithFile(ani_plist);
    //auto ani = Animate::create(ani_cache->getAnimation("run"));
    //m_pIcon->runAction(RepeatForever::create(ani));

    int num = GM_GI->numberFrames(ani_plist, path_name);

    Vector<SpriteFrame*> frames;
    for (int i = 0; i <= num; i++) {
        std::string frameName = StringUtils::format((path_name + "_%d.png").c_str(), i);
        auto frame = cache->getSpriteFrameByName(frameName);
        frames.pushBack(frame);
    }

    float frameDelay = 0.1f;
    auto animation = Animation::createWithSpriteFrames(frames, frameDelay);
    auto animate = Animate::create(animation);
    auto repeat = RepeatForever::create(animate);

    m_pAnimate->runAction(repeat);
}

SkillManager* ChampionInGame::getCurrentSkillDeck()
{
    return m_pPreDiceSkillDeck;
    //switch (m_eTurnPhase)
    //{
    //    case ChampionTurnPhase::PRE_DICE:
    //        return m_pPreDiceSkillDeck;
    //    case ChampionTurnPhase::POS_DICE:
    //        return m_pPostDiceSkillDeck;
    //}
}
