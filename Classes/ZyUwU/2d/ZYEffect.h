#pragma once

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ZyUwU/platform/ZYMacros.h"
#include "ZyUwU/platform/CCMacrosSupport.h"

USING_NS_CC;

#define CREATE_SET_EFFECT_FUNC_HELPER(__FUNC_NAME__, __VAR_TYPE__, __VAR__, __UNIFORM_NAME__) \
void __FUNC_NAME__(__VAR_TYPE__ var)                                                               \
{                                                                                             \
    ZYASSERT_BREAK(m_pProgramState, "Program must not be null", );                            \
    __VAR__ = var;                                                                            \
    SET_UNIFORM(m_pProgramState, __UNIFORM_NAME__, __VAR__);                                  \
}                                                                                             \

NS_ZY_BEGIN

class ZYSprite;
class ZYLabel;
class ZYEffect : public Ref
{
public:
    CREATE_GET_FUNC(getProgramState, backend::ProgramState*, m_pProgramState);
    virtual void castTarget(ZYSprite* pSprite){}
    virtual void castTarget(ZYLabel* pLabel){}

protected:
    ZYEffect();
    virtual ~ZYEffect();
    bool initProgramState(const std::string &vertexFilename, const std::string &fragmentFilename);
    bool initProgramState(const std::string &fragmentFilename);
    backend::ProgramState* m_pProgramState = nullptr;
    bool initProgramStateHelper(backend::Program *program);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string m_sFragSource;
    EventListenerCustom* m_pBackgroundListener;
#endif
};

BEGIN_CREATE_REFCLASS(ZYNullEffect, ZYEffect)
END_CREATE_REFCLASS

BEGIN_CREATE_REFCLASS(ZYBlurEffect, ZYEffect)

public:
    virtual void castTarget(ZYSprite* pSprite) override;

public:
    CREATE_SET_EFFECT_FUNC_HELPER(setRadius, float, m_fBlurRadius, "blurRadius");
    CREATE_SET_EFFECT_FUNC_HELPER(setSampleNumber, float, m_fBlurSampleNumber, "sampleNum");

protected:
    float m_fBlurRadius;
    float m_fBlurSampleNumber;

END_CREATE_REFCLASS


BEGIN_CREATE_REFCLASS(ZYOutline, ZYEffect)

public:

public:
    CREATE_SET_EFFECT_FUNC_HELPER(setThreshold, float, m_fThreshold, "u_threshold");
    CREATE_SET_EFFECT_FUNC_HELPER(setRadius, float, m_fRadius, "u_radius");
    CREATE_SET_EFFECT_FUNC_HELPER(setColor, Vec3, m_cColor, "u_outlineColor");

protected:
    float m_fThreshold;
    float m_fRadius;
    Vec3 m_cColor;

END_CREATE_REFCLASS

BEGIN_CREATE_REFCLASS(ZYGlowingBorder, ZYEffect)

public:
    CREATE_SET_EFFECT_FUNC_HELPER(setCTime, float , m_fCTime, "u_ctime");
    CREATE_SET_EFFECT_FUNC_HELPER(setGTime, float , m_fGTime, "u_gtime");
    CREATE_SET_EFFECT_FUNC_HELPER(setRadius, float , m_fRadius, "u_radius");
    CREATE_SET_EFFECT_FUNC_HELPER(setColor, Vec4, m_cColor, "u_outlineColor");

protected:
    float m_fCTime, m_fGTime, m_fRadius;
    Vec4 m_cColor;

END_CREATE_REFCLASS

BEGIN_CREATE_REFCLASS(ZYOutlineV2, ZYEffect)

public:
    virtual void castTarget(ZYSprite* pSprite);

public:
    CREATE_SET_EFFECT_FUNC_HELPER(setColor, Vec4, m_cColor, "u_outlineColor");
    void setOutlineWidth(float fWidth);

protected:
    Vec4 m_cColor;
    float m_fWidth, m_fTargetSize;

END_CREATE_REFCLASS

BEGIN_CREATE_REFCLASS(ZYShadow, ZYEffect)
END_CREATE_REFCLASS

BEGIN_CREATE_REFCLASS(ZYMotionBlur, ZYEffect)
public:
    CREATE_SET_EFFECT_FUNC_HELPER(setBlur, Vec2, m_cBlur, "u_blurVector");
protected:
    Vec2 m_cBlur;
END_CREATE_REFCLASS

NS_ZY_END
