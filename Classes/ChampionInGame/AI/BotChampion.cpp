#include "BotChampion.h"
#include "Skill/SkillManager/SkillManager.h"
#include "Dice/Dice.h"
#include "ChampionInGame/UI/ChampionUI.h"
#include "Skill/SkillInGame/SkillInGame.h"

///] Constructor

TesterBot::TesterBot()
{

}

///] Virtual

TesterBot* TesterBot::createWithProperties(Champion *pChamp, ChampionUI *pUI, Dice* pDice, SkillManager* vSkillDeck)
{
    auto ret = new (std::nothrow) TesterBot();
    if(ret && pChamp)
    {
        ret->autorelease();
        ret->m_pIcon = pChamp->getIcon();
        ret->m_pStatics = pChamp->getStatics();
        //ret->m_pIngameStatics = IngameStatics::create(ret->m_pStatics, true, false);
        ret->m_pChampionStatics = pChamp->getChampionStatics();
        if (ret->initWithProperties(pUI, pDice, vSkillDeck))
        {
            ret->disable();
            return ret;
        }

    }
    CC_SAFE_DELETE(ret);
    return nullptr;

}

bool TesterBot::init()
{
    auto dice = Dice::createWithProperties("dice/128.png");
    setDeputizeTexture("champion/char-3.png");
    m_pIcon = ZYSprite::create("champion/char-3.png");
    m_pAvatar = ZYSprite::create("avatar/champion/char-3.png");
    m_pChampionStatics = ChampionStatics::create();
    m_pStatics = Statics::createWithProperties();
    auto ui = ChampionUI::createDefault();
    auto sig = SkillInGame::createTest();
    sig->setName("move");
    sig->setSkillMechanic(SkillInGame::MoveBySkill);
    auto sm = SkillManager::createWithSkillInGame(sig, nullptr);
    auto coord = Coordinate(Dir::WS, 0);
    this->setPosition(coord);
    return ChampionInGame::initWithProperties(ui, dice, sm);
}

void TesterBot::log()
{
    ZY_EZ_LOG;
}

std::string TesterBot::toString(int nTab)
{
    return ChampionInGame::toString(nTab);
}

void TesterBot::startTurn()
{
    ChampionInGame::startTurn();

    chooseSkill();
}

void TesterBot::chooseSkill()
{
    auto target_skill = m_pPreDiceSkillDeck->getSkillByName("move");
    target_skill->getSkillCard()->onSelect();
    m_pPreDiceSkillDeck->setSelectingSkill(target_skill);
    m_pPreDiceSkillDeck->clickButton(this, ui::Widget::TouchEventType::ENDED);
    if(target_skill->getNeedDice())
    {
        this->m_pDice->run(this, ui::Widget::TouchEventType::ENDED);
    }
}