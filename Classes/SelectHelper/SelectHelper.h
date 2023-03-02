#pragma once

#include "ZyUwU/ZyUwU.h"

USING_NS_ALL;

class GameObject;
BEGIN_CREATE_REFCLASS(Selector, Ref)

public:
    void glowingTarget(float radius);
    void selectTarget(std::string type);
    void disable();

    enum class TargetType
    {
        NONE,
        Arena,
        Champion,
        Both
    };

protected:
    std::vector<GameObject*> m_vTargets;
    bool m_bFinish;


END_CREATE_REFCLASS