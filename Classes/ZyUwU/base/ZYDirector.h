#pragma once

#include "ZyUwU/platform/ZYMacros.h"
#include "ZyUwU/math/ZYFraction.h"
#include "cocos2d.h"
#include "ZYConstant.h"

#define ZY_DIRECTOR_GI zy::ZYDirector::getInstance()
#define ZYDR_GI ZY_DIRECTOR_GI

#define ZY_DR_GET_VISIBLE_SIZE ZY_DIRECTOR_GI->getVisibleSize()
#define ZYDR_GVS ZY_DR_GET_VISIBLE_SIZE

#define ZYDR_GET_TRUE_VISIBLE_SIZE ZY_DIRECTOR_GI->getTrueVisibleSize()
#define ZYDR_TGVS ZYDR_GET_TRUE_VISIBLE_SIZE

NS_ZY_BEGIN
BEGIN_CREATE_INSTANCE_REFCLASS(ZYDirector, cocos2d::Ref)

public:
    void setContentScaleWidth(Fraction tFraction);
    void setContentScaleHeigth(Fraction tFraction);
    void setContentScaleWidth(float fScaleFactor);
    void setContentScaleHeight(float fScaleFactor);
    void setTheRunningScene(cocos2d::Scene *pScene);
    void setResolutionName(std::string sName) {this->p_sResolutionName = sName;}
    cocos2d::Point recalculateScale(cocos2d::Point cScale);

public:
    Fraction getDesignAspectRatio() {return Fraction::fastShortCut(designResolutionSize.width, designResolutionSize.height);}
    Fraction getDeviceAspectRatio() {return Fraction::fastShortCut(getOpenGLView()->getFrameSize().width, getOpenGLView()->getFrameSize().height);}
    cocos2d::Size getVisibleSize() {return p_pDirector->getVisibleSize();}
    cocos2d::Point getVisibleOrigin() {return p_pDirector->getVisibleOrigin();}
    cocos2d::GLView* getOpenGLView() {return p_pDirector->getOpenGLView();}

    float getContentScaleWidth() { return m_fContentScale_Width; }
    float getContentScaleHeight() { return m_fContentScale_Height; }
public:
    cocos2d::Size getTrueVisibleSize() {return cocos2d::Size(getVisibleSize().width + getVisibleOrigin().x, getVisibleSize().height + getVisibleOrigin().y);}


protected:
    float m_fContentScale_Width = 1.0f;
    float m_fContentScale_Height = 1.0f;

private:
    std::string p_sResolutionName;
    cocos2d::Scene *p_pRunningScene = nullptr;
    cocos2d::Director* p_pDirector;

END_CREATE_INSTANCE_REFCLASS;
NS_ZY_END
