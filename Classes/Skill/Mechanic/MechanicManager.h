#pragma once

#include "ZyUwU/ZyUwU.h"

USING_NS_ALL;

class SkillMechanic;
class SkillInGame;

class MechanicManager : public Node
{
public:
    static MechanicManager* create(SkillInGame* owner, SkillMechanic *mechanic);

public:

    virtual bool initWithProperties(SkillInGame* owner, SkillMechanic* mechanic);
    virtual void onTrigger();
    virtual void endTrigger();
    virtual void loop(float dt);
    void setup();

public:
    CREATE_GET_FUNC(getOwner, SkillInGame*, m_pOwner);

public:
    MechanicManager();

protected:
    SkillMechanic *m_pMechanic;
    SkillInGame *m_pOwner;
};