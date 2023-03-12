#pragma once

#include "../platform/ZYMacros.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

NS_ZY_BEGIN

class ZYSprite;
class ZYLabel;
class ZYUI : public Ref
{
public:
    virtual void execute() = 0;
    virtual void clean() = 0;
    virtual ~ZYUI(){};

protected:
    Node *m_pTarget;
};

class ZYFloatingNotify : public ZYUI
{
public:
    static ZYFloatingNotify* create(const std::string& title, Point& targetPos);

public:
    virtual void execute(){};
    virtual void clean(){};

};

NS_ZY_END