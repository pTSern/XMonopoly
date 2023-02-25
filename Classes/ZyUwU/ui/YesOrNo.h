#pragma once

#include "ZyUwU/platform/ZYMacros.h"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

NS_ZY_BEGIN

class ZYSprite;
class ZYLabel;
BEGIN_CREATE_REFCLASS(YesOrNo, Layer)

public:
    static YesOrNo* createWithProperties(std::string sBackground, std::string sYes, std::string sNo, TTFConfig ttfConfig, std::string sMessage);

public:
    virtual ~YesOrNo();
    bool isReady() { return m_eStatus != ExpertBool::NONE; };
    bool getValue() { return m_eStatus == ExpertBool::TRUE; };
    bool initWithProperties(std::string sBackground, std::string sYes, std::string sNo, TTFConfig ttfConfig, std::string sMessage);
    bool countdown();

protected:
    enum class ExpertBool
    {
        TRUE = 1,
        FALSE = 0,
        NONE = -1
    };
protected:
    ZYSprite* m_pBackground;
    ZYLabel* m_pText;
    ui::Button* m_pYes, *m_pNo;
    int m_nGlobalZOrder;
    ExpertBool m_eStatus;

END_CREATE_REFCLASS

NS_ZY_END
