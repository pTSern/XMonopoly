#include "ZYDirector.h"

NS_ZY_BEGIN

//Static variable

ZYDirector* ZYDirector::sp_pInstance = nullptr;

//Constructor

ZYDirector::ZYDirector()
{
}

bool ZYDirector::init()
{
    p_pDirector = cocos2d::Director::getInstance();

    //m_fContentScale_Width = p_pDirector->getVisibleSize().width/designResolutionSize.width;
    //m_fContentScale_Height = p_pDirector->getVisibleSize().height/designResolutionSize.height;

    m_fContentScale_Width = getTrueVisibleSize().width/designResolutionSize.width;
    m_fContentScale_Height = getTrueVisibleSize().height/designResolutionSize.height;

    //auto p = this->recalculateScale(cocos2d::Point(m_fContentScale_Width, m_fContentScale_Height));
    //m_fContentScale_Width = p.x;
    //m_fContentScale_Height = p.y;

    //this->autorelease();

    CCLOG("CALL ZYDirector: Init succ");
    return true;
}

cocos2d::Point ZYDirector::recalculateScale(cocos2d::Point cScale)
{
    if(cScale.x > 1) cScale.x = 1;
    if(cScale.y > 1) cScale.y = 1;

    if((cScale.x - cScale.y) > 0.25) cScale.x = cScale.y + 0.25;
    if((cScale.y - cScale.x) > 0.25) cScale.y = cScale.x + 0.25;

    return cScale;
}

std::string ZYDirector::toString(int nTab)
{
    std::string ts;
    std::string tab = ZY_SP_TAB(nTab);

    ts += tab + " + Resolution Name: " + p_sResolutionName;
    ts += tab + " + Visible Size: " + ZY_SP_NUMBER_TO_STRING(getVisibleSize().width) + " - " + ZY_SP_NUMBER_TO_STRING(getVisibleSize().height);
    ts += tab + " + Visible Origin: " + ZY_SP_NUMBER_TO_STRING(getVisibleOrigin().x) + " - " + ZY_SP_NUMBER_TO_STRING(getVisibleOrigin().y);
    ts += tab + " + True Visible Size: " + ZY_SP_NUMBER_TO_STRING(getTrueVisibleSize().width) + " - " + ZY_SP_NUMBER_TO_STRING(getTrueVisibleSize().height);
    ts += tab + " + Design Aspect Ratio: " + ZY_SP_NUMBER_TO_STRING(getDesignAspectRatio().getNumerator()) + ":" + ZY_SP_NUMBER_TO_STRING(getDesignAspectRatio().getDenominator());
    ts += tab + " + Device Aspect Ratio: " + ZY_SP_NUMBER_TO_STRING(getDeviceAspectRatio().getNumerator()) + ":" + ZY_SP_NUMBER_TO_STRING(getDeviceAspectRatio().getDenominator());
    ts += tab + " + Device Resolution: " + ZY_SP_NUMBER_TO_STRING(p_pDirector->getOpenGLView()->getFrameSize().width) + "x" + ZY_SP_NUMBER_TO_STRING(p_pDirector->getOpenGLView()->getFrameSize().height);
    ts += tab + " + Content Scale: " + ZY_SP_NUMBER_TO_STRING(m_fContentScale_Width) + " - " + ZY_SP_NUMBER_TO_STRING(m_fContentScale_Height);
    ts += tab + " + Scale Factor: " + ZY_SP_NUMBER_TO_STRING(cocos2d::Director::getInstance()->getContentScaleFactor());

    return ts;
}

void ZYDirector::log()
{
    ZY_EZ_LOG;
}

void ZYDirector::setContentScaleWidth(float fScaleFactor)
{
    if(fScaleFactor != m_fContentScale_Width)
    {
        m_fContentScale_Width = fScaleFactor;
    }
}

void ZYDirector::setContentScaleHeight(float fScaleFactor)
{
    if(fScaleFactor != m_fContentScale_Height)
    {
        m_fContentScale_Height = fScaleFactor;
    }
}

void ZYDirector::setContentScaleWidth(Fraction tFraction)
{
    if(tFraction.toFloat() != m_fContentScale_Width)
    {
        m_fContentScale_Width = tFraction.toFloat();
    }
}
void ZYDirector::setContentScaleHeigth(Fraction tFraction)
{
    if(tFraction.toFloat() != m_fContentScale_Width)
    {
        m_fContentScale_Height = tFraction.toFloat();
    }
}

NS_ZY_END
