#include "SkillManager.h"
#include "Skill/SkillInGame/SkillInGame.h"
#include "ChampionInGame/ChampionInGame.h"

//// Constructor

SkillManager::SkillManager() :
m_pUse(nullptr), m_pOwner(nullptr),
m_pSelecting(nullptr)
{

}

//// Static

SkillManager* SkillManager::createWithSkillInGame(SkillInGame* sig, ...)
{
    va_list args;
    va_start(args, sig);

    SkillManager *ret = SkillManager::createWithSkills(sig, args);

    va_end(args);

    return ret;
}

SkillManager* SkillManager::createWithSkills(SkillInGame* skill, va_list args)
{

    std::vector<SkillInGame*> skills;
    if( skill )
    {
        skills.push_back(skill);
        SkillInGame *s = va_arg(args, SkillInGame*);
        while(s)
        {
            skills.push_back(s);
            s = va_arg(args, SkillInGame*);
        }
    }

    return SkillManager::createWithVector(skills);
}

SkillManager* SkillManager::createWithVector(std::vector<SkillInGame*>& vectorOfSkills )
{
    auto ret = new (std::nothrow) SkillManager();
    if (ret && ret->initWithVector(vectorOfSkills))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//// Virtual

bool SkillManager::init()
{
    std::vector<SkillInGame*> s;
    return this->initWithVector(s);
}

void SkillManager::log()
{

}

std::string SkillManager::toString(int nTab)
{
    std::string ts;
    return ts;
}

//// Public

bool SkillManager::initWithVector(std::vector<SkillInGame*>& vectorOfSkills)
{
    if(Node::init())
    {
        this->scheduleUpdate();

        m_pUse = ui::Button::create(sr_button_default, sr_button_clicked, sr_button_disable);
        m_pUse->setTitleText("USE");

        this->addChild(m_pUse, 2);

        this->setContentSize(ZYDR_GVS);

        int z = 0;

        float s = vectorOfSkills.size();
        auto ap = vectorOfSkills[0]->getSkillCard();
        auto yy = ap->getShapeSize().height/3;
        auto scw = ap->getShapeSize().width;
        auto max_size = scw * MAX_SKILL_IN_DECK;
        auto first = (ZYDR_GVS.width - max_size)/2;
        auto minus = (scw * s - max_size)/(s - 1);

        m_pUse->setPosition(Point(first + max_size + + scw/2 + m_pUse->getContentSize().width/2, yy));

        auto ls = EventListenerTouchOneByOne::create();

        ls->onTouchBegan = CC_CALLBACK_2(SkillManager::onTouch, this);
        ls->onTouchEnded = CC_CALLBACK_2(SkillManager::endTouch, this);
        m_pUse->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ls, m_pUse);
        m_pUse->addTouchEventListener(CC_CALLBACK_2(SkillManager::clickButton, this));
        CCUB_SSTFSP(m_pUse, 0.3f);

        if(s <= 1)
        {
            first = ZYDR_GVS.width/2 - scw/2;
            minus = 0;
        }

        for(int i = 0; i < vectorOfSkills.size(); i++)
        {
            vectorOfSkills[i]->getSkillCard()->setPosition(Point(first + scw/2 * (i + z + 1) - (i * minus), yy));
            vectorOfSkills[i]->setOwner(this);
            this->addChild(vectorOfSkills[i], z);
            z++;
        }
        this->m_vSkillDecks = vectorOfSkills;
        return true;
    }
    return false;
}

const Vec2& SkillManager::getUseButtonPosition()
{
    return m_pUse->getPosition();
}

void SkillManager::update(float dt)
{
    if(m_pSelecting && m_pOwner->isTurn())
    {
        if(m_pSelecting->getTarget() ==  Skill::TargetType::NONE)
        {
            m_pUse->setEnabled(true);
        }
        else
        {
            if(m_pSelecting->isFinishSelect()) m_pUse->setEnabled(true);
        }
    }
    else 
    {
        m_pUse->setEnabled(false);
    }
}

bool SkillManager::onTouch(Touch *touch, Event *event)
{
    return true;
}
bool SkillManager::endTouch(Touch *touch, Event *event)
{
    return true;
}
void SkillManager::clickButton(Ref* pSender, ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::ENDED)
    {
        m_pSelecting->onTrigger();
    }
}

void SkillManager::unselectSkill()
{
    if(m_pSelecting)
    {
        m_pSelecting->unSelect();
    }
}

void SkillManager::setUseButton(bool var)
{
    this->m_pUse->setVisible(var);
}

void SkillManager::enable()
{
    for(auto &x : m_vSkillDecks)
    {
        x->enable();
    }
    if(!this->m_pUse->isVisible())
    {
        this->setUseButton(true);
    }
}

void SkillManager::disable()
{
    this->unselectSkill();
    for(auto &x : m_vSkillDecks)
    {
        x->disable();
    }
    m_pUse->setVisible(false);
}