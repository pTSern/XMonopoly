#pragma once

#include "cocos2d.h"
#include "ZyUwU/platform/ZYMacros.h"
#include "ZyUwU/platform/CCMacrosSupport.h"
#include "renderer/backend/Device.h"

USING_NS_CC;

NS_ZY_BEGIN

class ZYEffect;
class ZYShaderHelper
{
public:
    ZYShaderHelper();
    virtual ~ZYShaderHelper();

    static int tupleSort(const std::tuple<ssize_t, ZYEffect*, QuadCommand> &tuple_1,
                         const std::tuple<ssize_t, ZYEffect*, QuadCommand> &tuple_2)
    {
        return std::get<0>(tuple_1) < std::get<0>(tuple_2);
    }
    static void updateUniforms(backend::ProgramState *programState);

protected:
    std::vector<std::tuple<ssize_t, ZYEffect*, cocos2d::QuadCommand>> m_vEffects;
    ZYEffect* m_pEffect;
};

NS_ZY_END