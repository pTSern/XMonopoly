#include "Dice.h"

// Constructor

Dice::Dice() :
m_pDice(nullptr),
m_nDiceNum(0)
{
}

Dice::~Dice()
{
    ZY_EZ_DE_LOG;
}

//// Static

Dice* Dice::createWithProperties(const std::string& sPath)
{
    auto p = new (std::nothrow) Dice();
    if(p && p->init())
    {
        p->autorelease();
        p->loadElement(sPath);
        p->config();
        p->enableDice();
        return p;
    }
    CC_SAFE_RELEASE(p);
    return nullptr;
}

//// Public

bool Dice::initWithProperties(const std::string& sPath)
{
    return true;
}

void Dice::loadElement(const std::string& sPath)
{
    std::string path = sPath;
    if(!CC_FILEUTILS_GI->isFileExist(sPath)) path = "dice/128.png";

    m_pDice = ZYSprite::create(path.c_str());
    m_pDice->setVisible(false);
    m_pDice->setPosition(Point(GM_GI->getMap()->getPosition().x, GM_GI->getMap()->getPosition().y + GM_GI->getMap()->getMapPixelSize().height/4));

    diceSize = Size(m_pDice->getContentSize().width/6, m_pDice->getContentSize().height);
    m_centerRect = Rect(Point(0,0), diceSize);

    m_pButton = ui::Button::create(sr_button_default, sr_button_clicked);
    m_pButton->setTitleText("DICE");
    CCUB_SSTFSP(m_pButton, 0.3f);
    m_pButton->setPosition(Point(ZYDR_GVS.width/6*5, ZYDR_GVS.height/6));

    auto ls = EventListenerTouchOneByOne::create();
    ls->onTouchBegan = CC_CALLBACK_2(Dice::onTouch, this);
    ls->onTouchEnded = CC_CALLBACK_2(Dice::endTouch, this);
    m_pButton->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ls, m_pButton);
    m_pButton->addTouchEventListener(CC_CALLBACK_2(Dice::run, this));

    this->rollDice();

    this->addChild(m_pButton);
    this->addChild(m_pDice);
}

void Dice::setDiceButtonPosition(const Vec2 &pos)
{
    this->m_pButton->setPosition(pos);
}

// Virtual

void Dice::config()
{
    //this->scheduleUpdate();
}

bool Dice::init()
{
    return true;
}

std::string Dice::toString(int nTab)
{
    std::string ts;
    std::string tab = ZYSP_T(nTab);
    return ts;
}

void Dice::log()
{

}

int Dice::rollDice()
{
    auto dice = random(1, 6);
    m_vDiceMemory.push_back(dice);

    m_centerRect.origin.x = diceSize.width * (dice - 1);
    m_pDice->setTextureRect(m_centerRect);
    //CCLOG("DICE NUM: %d", dice);

    //// Disable Roll button
    this->m_pButton->setVisible(false);

    return m_vDiceMemory.back();
}

const Size& Dice::getDiceButtonSize()
{
    return m_pButton->getContentSize();
}

void Dice::enableDice()
{
    m_pButton->setVisible(true);
}

void Dice::disableDice()
{
    //m_pDice->setVisible(false);
    m_pButton->setVisible(false);
}

void Dice::enable()
{
    m_pDice->setVisible(true);
}
void Dice::disable()
{
    m_pDice->setVisible(false);
}

bool Dice::onTouch(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

bool Dice::endTouch(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

void Dice::run(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::ENDED) this->rollDice();
}
