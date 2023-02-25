#include "ZYShaderHelper.h"
#include "ZYEffect.h"

NS_ZY_BEGIN

ZYShaderHelper::ZYShaderHelper() :
m_pEffect(nullptr)
{
    m_vEffects.reserve(2);
}

ZYShaderHelper::~ZYShaderHelper()
{
    for(auto &tuple: m_vEffects)
    {
        std::get<1>(tuple)->release();
    }
    CC_SAFE_RELEASE(m_pEffect);
}

void ZYShaderHelper::updateUniforms(backend::ProgramState *programState)
{
    float time = CCDR_GI->getTotalFrames() * CCDR_GI->getAnimationInterval();

    Vec4 uTime(time / 10.0f, time, time * 2.0f, time * 4.0f);
    Vec4 sinTime(time / 8.0f, time / 4.0f, time / 2.0f, sinf(time));
    Vec4 cosTime(time / 8.0f, time / 4.0f, time / 2.0f, cosf(time));

    SET_UNIFORM(programState, "u_Time", uTime);
    SET_UNIFORM(programState, "u_SinTime", sinTime);
    SET_UNIFORM(programState, "u_CosTime", cosTime);
}

NS_ZY_END