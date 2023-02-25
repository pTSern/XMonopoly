#include "YesOrNo.h"
#include "ZyUwU/2d/ZYSprite.h"

NS_ZY_BEGIN

YesOrNo::YesOrNo() :
m_eStatus(ExpertBool::NONE),
m_nGlobalZOrder(100),
m_pBackground(nullptr),
m_pYes(nullptr), m_pNo(nullptr),
m_pText(nullptr)
{

}

YesOrNo::~YesOrNo()
{
    CC_SAFE_RELEASE(m_pBackground);
    CC_SAFE_RELEASE(m_pText);
    CC_SAFE_RELEASE(m_pYes);
    CC_SAFE_RELEASE(m_pNo);
}

// Static

YesOrNo *YesOrNo::createWithProperties(std::string sBackground, std::string sYes, std::string sNo, TTFConfig ttfConfig, std::string sMessage)
{
    auto ret = new (std::nothrow) YesOrNo();
    if(ret)
    {
        return ret;
    }
    CC_SAFE_RELEASE(ret);
    return nullptr;
}

// Virtual

bool YesOrNo::init()
{
    return true;
}

std::string YesOrNo::toString(int nTab)
{
    std::string ts;
    return ts;
}

void YesOrNo::log()
{
    ZY_EZ_LOG;
}

// Public

bool YesOrNo::initWithProperties(std::string sBackground, std::string sYes, std::string sNo, TTFConfig ttfConfig, std::string sMessage)
{
    m_pBackground = ZYSprite::create(sBackground.c_str());
    m_pYes = ui::Button::create(sYes);
    m_pNo = ui::Button::create(sNo);
    m_pText = ZYLabel::createWithTTF(ttfConfig, sMessage);

    m_pBackground->setPosition(ZYDR_GVS/2);
    m_pBackground->setGlobalZOrder(m_nGlobalZOrder-1);
    m_pText->setPosition(Point(m_pBackground->getPositionX(), m_pBackground->getContentPositionMiddleTop().y - m_pText->getContentSize().height));
    m_pYes->setPosition(m_pBackground->getContentPositionBottomLeft() + m_pYes->getContentSize());
    m_pNo->setPosition(Point(m_pBackground->getContentPositionBottomRight().y + m_pNo->getContentSize().height, m_pBackground->getContentPositionBottomRight().y-m_pNo->getContentSize().width));

    m_pYes->setTitleText("YES");
    m_pNo->setTitleText("NO");

    this->addChild(m_pBackground);
    this->addChild(m_pText);
    this->addChild(m_pNo);
    this->addChild(m_pYes);

    m_pYes->addTouchEventListener([&](Ref* ref, ui::Widget::TouchEventType type)
        {
            if(type == ui::Widget::TouchEventType::ENDED)
            {
                m_eStatus = ExpertBool::TRUE;
            }
        });

    m_pNo->addTouchEventListener([&](Ref* ref, ui::Widget::TouchEventType type)
        {
            if(type == ui::Widget::TouchEventType::ENDED)
            {
                m_eStatus = ExpertBool::FALSE;
            }
        });
    return true;
}


NS_ZY_END