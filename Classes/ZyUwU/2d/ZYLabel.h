#pragma once

#include "ZyUwU/platform/ZYMacros.h"
#include "ZyUwU/base/ZYSupport.h"
#include "cocos2d.h"
#include "ZYShaderHelper.h"
#include "ZYSupport2D.h"
#include "ZyUwU/base/ZYDirector.h"

NS_ZY_BEGIN

class ZYEffect;
class ZYLabel : public cocos2d::Label, public ZYSupport2D
{
public:
    /**
     * Allocates and initializes a Label, base on FreeType2.
     *
     * @param text The text of this Label that will be displayed on the screen.
     * @param fontFile The direction of this Label's TrueType Font.
     * @param fontSize The size of the text of this Label.
     * @param dimensions I don't know what is this, the cocos2dx has this shit so i have to call it here.
     * @param hAlignment The text horizontal alignment.
     * @param vAlignment The text vertical alignment.
     * @return The automatic released Label object
     */
    static ZYLabel* createWithTTF(const std::string& text, const std::string& fontFile, float fontSize,
                                  const cocos2d::Size& dimensions = cocos2d::Size::ZERO,
                                  cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
                                  cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP);
    /**
     * Allocates and initializes a Label, base on FreeType2.
     *
     * @param ttfConfig The Label's config.
     * @param text The text of this Label that will be displayed on the screen.
     * @param hAlignment The text horizontal alignment.
     * @param maxLineWidth The max line width, its will automatic down line
     * @return The automatic released Label object
     */
    static ZYLabel* createWithTTF(const TTFConfig& ttfConfig, const std::string& text,
                                TextHAlignment hAlignment = TextHAlignment::CENTER, int maxLineWidth = ZYDR_TGVS.width/2);
public:
    /**
     * Log all Label properties that allow to be display
     * @note see what can be printed in toString(int) function
     */
    virtual void log();
    virtual float getRotation() const;
    void fixGetRotation();
    /**
     * Convert all this Label properties to string
     *
     * @param nTab The number of the space-tab of each line. This default = 2
     * @return The string contain this Label's properties
     */
    virtual std::string toString(int nTab = 2);

    virtual const Vec2& getAnchorPoint() const override
    {
        return Label::getAnchorPoint();
    }
    virtual float getPositionX() const override
    {
        return Label::getPositionX();
    }
    virtual float getPositionY() const override
    {
        return Label::getPositionY();
    }
    virtual const Size& getContentSize() const override
    {
        return Label::getContentSize();
    }

private:
    ZYLabel(TextHAlignment hAlignment = TextHAlignment::LEFT,
            TextVAlignment vAlignment = TextVAlignment::TOP);
    const std::string p_sClassName = "ZYLabel";
};

NS_ZY_END
