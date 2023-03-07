#include "Condition.h"
#include "Skill/SkillManager/SkillManager.h"
#include "Skill/SkillInGame/SkillInGame.h"
#include "ChampionInGame/ChampionInGame.h"

//// Constructor

SkillCondition::SkillCondition() :
m_bIsValid(true)
{

}

//// Static
SkillCondition* SkillCondition::createWithEffects(GameEffect *effect, ...)
{
    va_list args;
    va_start(args, effect);

    SkillCondition *ret = SkillCondition::createWithEffectsArg(effect, args);

    va_end(args);

    return ret;
}

SkillCondition* SkillCondition::createWithEffectsArg(GameEffect* effect, va_list args)
{
    std::vector<GameEffect*> effects;
    if(effect)
    {
        effects.push_back(effect);
        GameEffect* e = va_arg(args, GameEffect*);
        while(e)
        {
            effects.push_back(e);
            e = va_arg(args, GameEffect*);
        }
    }

    return SkillCondition::createWithVector(effects);
}

SkillCondition* SkillCondition::createWithVector(std::vector<GameEffect*>& effects)
{
    auto ret = new (std::nothrow) SkillCondition();
    if (ret && ret->initWithVector(effects))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//// Virtual

bool SkillCondition::init()
{
    std::vector<GameEffect*> s;
    return this->initWithVector(s);
}

void SkillCondition::update(float dt)
{
    /// Check if this skill's owner meet game-effects

    auto sig_static = m_pOwner->getSkillStatics();
    auto champ_static = m_pOwner->getOwner()->getOwner()->getStatics();
    m_bIsValid = false;
    NOTIFICATION_HELPER(!m_pOwner->isReady(), "SKILL NOT READY YET!")
    NOTIFICATION_HELPER(m_pOwner->getType() == Skill::SkillType::PASSIVE, "THIS IS PASSIVE SKILL")
    NOTIFICATION_HELPER(champ_static->getCurrentMana() < sig_static->getManaCost(), "NOT ENOUGH MANA")
    NOTIFICATION_HELPER(champ_static->getCurrentHp() < sig_static->getHpCost(), "NOT ENOUGH HEALTH POINT")
    NOTIFICATION_HELPER(champ_static->getCurrentSp() < sig_static->getSpCost(), "NOT ENOUGH SKILL POINT")
    m_bIsValid = true;
}

void SkillCondition::log()
{
}

std::string SkillCondition::toString(int nTab)
{
    std::string ts;
    return ts;
}

//// Public

bool SkillCondition::initWithVector(std::vector<GameEffect*>& effect)
{
    if(Node::init())
    {
        this->scheduleUpdate();

        this->m_vEffectCondition = effect;

        m_font = TTFConfig(defaultTTFConfig);
        m_font.fontSize = 50;
        m_font.outlineSize = 1;
        m_font.bold = true;

        return true;
    }
    return false;
}

void SkillCondition::notify()
{
    auto label = ZYLabel::createWithTTF(m_font, m_sMessage);
    this->addChild(label);
    label->setGlobalZOrder(100);
    label->setColor(Color3B::RED);
    label->setPosition(ZYDR_GVS/2);
    auto delay = DelayTime::create(1.0f);
    auto fadeOut = FadeOut::create(0.5f);
    auto remove = RemoveSelf::create();
    auto sequence = Sequence::create(delay, fadeOut, remove, nullptr);
    label->runAction(sequence);
}