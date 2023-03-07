#pragma once

#include "ZyUwU/ZyUwU.h"
#include "Support/GameConstant.h"

USING_NS_ALL;

class SkillInGame;
class GameEffect;
BEGIN_CREATE_REFCLASS(SkillCondition, Node)

public:
    static SkillCondition* createWithEffects(GameEffect* effect, ...);
    static SkillCondition* createWithEffectsArg(GameEffect* effect, va_list args);
    static SkillCondition* createWithVector(std::vector<GameEffect*>& effects);

public:
    void update(float dt);

#define NOTIFICATION_HELPER(__COND__, __MESSAGE__)                  \
do{                                                                 \
    if(__COND__)                                                    \
    {                                                               \
        m_sMessage = __MESSAGE__;                                   \
        return;                                                     \
    }                                                               \
}while(0);                                                          \



public:
    CREATE_GET_FUNC(isValid, bool, m_bIsValid);
    CREATE_SET_GET_FUNC(setOwner, getOwner, SkillInGame*, m_pOwner);

    bool initWithVector(std::vector<GameEffect*>& effects);
    void notify();

protected:
    SkillInGame* m_pOwner;
    bool m_bIsValid;
    std::vector<GameEffect*> m_vEffectCondition;
    TTFConfig m_font;
    std::string m_sMessage;

END_CREATE_CLASS

using Condition = SkillCondition;
