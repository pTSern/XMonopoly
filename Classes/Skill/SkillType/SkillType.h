#pragma once

#include "ZyUwU/ZyUwU.h"

USING_NS_ALL;

BEGIN_CREATE_CLASS(SkillType)

public:
    enum class Type
    {
        ACTIVE,
        PASSIVE,
        TOGGLE
    };

public:
    static SkillType* createWithProperties(Type type);

public:
    SkillType(Type eType);

public:
    CREATE_GET_FUNC(getType, Type, m_eType);
    std::string toDescription();

protected:
    Type m_eType;

END_CREATE_CLASS;