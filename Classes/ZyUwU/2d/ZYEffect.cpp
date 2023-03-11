#include <ZyUwU/platform/CCMacrosSupport.h>
#include "ZYEffect.h"
#include "../renderer/backend/Device.h"
#include "../renderer/ccShaders.h"
#include "ZyUwU/2d/ZYSprite.h"

NS_ZY_BEGIN

////ZYShader

//Constructor

ZYEffect::ZYEffect()
{}

ZYEffect::~ZYEffect()
{
    CC_SAFE_RELEASE_NULL(m_pProgramState);
}

bool ZYEffect::initProgramState(const std::string &fragmentFilename)
{
    auto fragmentSource = CCFU_GI->getStringFromFile(CCFU_GI->fullPathForFilename(fragmentFilename));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_sFragSource = fragmentSource;
#endif

    auto program = CCDV_GI->newProgram(positionTextureColor_vert, fragmentSource.c_str());
    return initProgramStateHelper(program);
}

bool ZYEffect::initProgramState(const std::string &vertexFilename,
                                const std::string &fragmentFilename)
{
    auto vertexSource = CCFU_GI->getStringFromFile(CCFU_GI->fullPathForFilename(vertexFilename));
    auto fragmentSource = CCFU_GI->getStringFromFile(CCFU_GI->fullPathForFilename(fragmentFilename));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_sFragSource = fragmentSource;
#endif

    auto program = CCDV_GI->newProgram(vertexSource, fragmentSource);
    return initProgramStateHelper(program);
}

bool ZYEffect::initProgramStateHelper(backend::Program *program)
{
    auto programState = new backend::ProgramState(program);

    CC_SAFE_RELEASE(m_pProgramState);
    CC_SAFE_RELEASE(program);

    m_pProgramState = programState;

    return m_pProgramState != nullptr;
}

////ZYBlurEffect

//Constructor

ZYBlurEffect::ZYBlurEffect() :
m_fBlurRadius(3), m_fBlurSampleNumber(5)
{

}

//Virtual

std::string ZYBlurEffect::toString(int nTab)
{
    std::string ts;
    return ts;
}

void ZYBlurEffect::log()
{

}

bool ZYBlurEffect::init()
{
    this->initProgramState("Shaders/SimpleBlur.fsh");

    return true;
}

void ZYBlurEffect::castTarget(ZYSprite *pSprite)
{
    if(!m_pProgramState) return;

    Size size = pSprite->getTexture()->getContentSizeInPixels();
    SET_UNIFORM(m_pProgramState, "resolution", size);
    SET_UNIFORM(m_pProgramState, "blurRadius", m_fBlurRadius);
    SET_UNIFORM(m_pProgramState, "sampleNum", m_fBlurSampleNumber);
}

//Public

//// ZY NULL EFFECT

//Constructor

ZYNullEffect::ZYNullEffect() {}

//Virtual

bool ZYNullEffect::init()
{
    this->initProgramState("Shaders/Null.fsh");
    return true;
}

std::string ZYNullEffect::toString(int nTab)
{
    std::string ts;
    return ts;
}

void ZYNullEffect::log()
{

}

//// ZYGLOWINGBORDER

//Constructor

ZYOutline::ZYOutline() :
m_fThreshold(1.75f),
m_fRadius(0.01f),
m_cColor(0.1f, 0.1f, 0.1f)
{

}

//Virtual

bool ZYOutline::init()
{
    this->initProgramState("Shaders/SimpleOutline.fsh");
    SET_UNIFORM(m_pProgramState, "u_outlineColor", m_cColor);
    SET_UNIFORM(m_pProgramState, "u_radius", m_fRadius);
    SET_UNIFORM(m_pProgramState, "u_threshold", m_fThreshold);
    return true;
}

std::string ZYOutline::toString(int nTab)
{
    std::string ts;
    return ts;
}

void ZYOutline::log() {}

//Public

//// GLOWING BORDER

//Constructor

ZYGlowingBorder::ZYGlowingBorder() :
m_fCTime(0.5f), m_fRadius(2), m_fGTime(0.5),
m_cColor(1.0f, 1.0f, 1.0f, 1.0f)
{

}

//Virtual

bool ZYGlowingBorder::init()
{
    this->initProgramState("Shaders/glow.fsh");
    SET_UNIFORM(m_pProgramState, "u_ctime", m_fCTime);
    SET_UNIFORM(m_pProgramState, "u_gtime", m_fGTime);
    SET_UNIFORM(m_pProgramState, "u_radius", m_fRadius);
    SET_UNIFORM(m_pProgramState, "u_outlineColor", m_cColor);
    return true;
}

std::string ZYGlowingBorder::toString(int nTab)
{
    std::string ts;
    return ts;
}

void ZYGlowingBorder::log()
{

}


//// ZYOutline-V2

//Constructor

ZYOutlineV2::ZYOutlineV2() :
m_cColor(1.0f, 1.0f, 0, 1.0f),
m_fWidth(2),
m_fTargetSize(0)
{

}

//Virtual

void ZYOutlineV2::castTarget(ZYSprite *pSprite)
{
    if(!m_pProgramState) return;
    m_fTargetSize = pSprite->getContentSize().width;

    auto widthPC = m_fWidth / m_fTargetSize;
    SET_UNIFORM(m_pProgramState, "u_outlineColor", m_cColor);
    SET_UNIFORM(m_pProgramState, "u_outlineWidth", widthPC);
}

bool ZYOutlineV2::init()
{
    this->initProgramState("Shaders/xOutline.vsh", "Shaders/xOutline.fsh");
    return true;
}

std::string ZYOutlineV2::toString(int nTab)
{
    std::string ts;
    return ts;
}

void ZYOutlineV2::setOutlineWidth(float fWidth)
{
    ZYASSERT_BREAK(m_pProgramState, "Program must not be null", );
    m_fWidth = fWidth;
    auto widthPC = m_fWidth / m_fTargetSize;
    SET_UNIFORM(m_pProgramState, "u_outlineWidth", widthPC);
}

void ZYOutlineV2::setColor(Color4F color)
{
    this->setColor(Vec4(color.r, color.g, color.b, color.a));
}

void ZYOutlineV2::log()
{
}

//// ZYShadow

//Constructor

ZYShadow::ZYShadow()
{

}

bool ZYShadow::init()
{
    this->initProgramState("Shaders/Shadow.vsh", "Shaders/Shadow.fsh");
    return true;
}

std::string ZYShadow::toString(int nTab)
{
    std::string ts;

    return ts;
}

void ZYShadow::log()
{

}

//// ZYMotion Blur

ZYMotionBlur::ZYMotionBlur() :
m_cBlur(0.25, 0.25)
{}

bool ZYMotionBlur::init()
{
    this->initProgramState( "Shaders/MotionBlur.vsh", "Shaders/MotionBlur.fsh");
    SET_UNIFORM(m_pProgramState, "u_blurVector", m_cBlur);
    return true;
}

std::string ZYMotionBlur::toString(int nTab)
{
    std::string ts;
    return ts;
}

void ZYMotionBlur::log()
{

}

NS_ZY_END