#include "Dice.h"

// Constructor

Dice::Dice() :
m_pDice(nullptr),
m_nDiceNum(0)
{
}

// Static

Dice* Dice::createWithProperties(const std::string& sPath)
{
    auto p = new (std::nothrow) Dice();
    if(p && p->init())
    {
        p->autorelease();
        p->loadElement(sPath);
        return p;
    }
    CC_SAFE_RELEASE(p);
    return nullptr;
}

// Public

bool Dice::initWithProperties(const std::string& sPath)
{
    return true;
}

void Dice::loadElement(const std::string& sPath)
{
    std::string path = sPath;
    if(!CC_FILEUTILS_GI->isFileExist(sPath)) path = "dice/default.png";

    m_pDice = ZYSprite::create(path.c_str());
    m_pDice->setVisible(false);
    m_pDice->setPosition(Point(MAP_MNG_GI->getPosition().x, MAP_MNG_GI->getPosition().y + MAP_MNG_GI->getMapPixelSize().height/4));

    diceSize = Size(m_pDice->getContentSize().width/6, m_pDice->getContentSize().height);
    m_centerRect = Rect(Point(0,0), diceSize);
    this->addChild(m_pDice);
}

// Virtual

void Dice::config()
{
}

bool Dice::init()
{
    //this->scheduleUpdate();
    return true;
}

std::string Dice::toString(int nTab)
{
    std::string ts;
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
    this->enableDice();
    CCLOG("%s", std::to_string(dice).c_str());
    return m_vDiceMemory.back();
}

void Dice::enableDice()
{
    m_pDice->setVisible(true);
}

void Dice::disableDice()
{
    m_pDice->setVisible(false);
}