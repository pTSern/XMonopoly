#pragma once

#include "renderer/backend/Device.h"
#include "cocos2d.h"
#include "ZyUwU/platform/ZYMacros.h"
#include "ZyUwU/platform/CCMacrosSupport.h"
#include "ZyUwU/base/ZYDirector.h"
#include "ZYShaderHelper.h"
#include "ZYSupport2D.h"

USING_NS_CC;

NS_ZY_BEGIN

class ZYEffect;
class ZYSprite : public cocos2d::Sprite, public ZYShaderHelper, public ZYSupport2D
{
public:
	static ZYSprite* create(const std::string& pFileName, bool bIsScale = true);
	static ZYSprite* create(const char* pFileName, bool bIsScale = true);
	static ZYSprite* create(const std::string& filename, const Rect& rect, bool bIsScale = true);
	static ZYSprite* create(cocos2d::Texture2D *p);

public:
	CREATE_GET_FUNC(getMemoryPosition, cocos2d::Point, m_cMemoryPosition);

	virtual std::string toString(int nTab = 2);
	virtual void setPosition(const cocos2d::Vec2& pos, cocos2d::Vec2 newAnchor);
	virtual void setPosition(const cocos2d::Vec2& pos) override;
	virtual void setPosition(const float xx, const float yy) override;
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

	virtual const Vec2& getAnchorPoint() const override
	{
		return Sprite::getAnchorPoint();
	}
	virtual float getPositionX() const override
	{
		return Sprite::getPositionX();
	}
	virtual float getPositionY() const override
	{
		return Sprite::getPositionY();
	}
	virtual const Size& getContentSize() const override
	{
		return Sprite::getContentSize();
	}

	bool config();
	void log();

	/**
	 *	@des	Replace current texture to a new one and DOES NOT change it's current size
	 * 	@prama	sPath A path to the new sprite file eg "NULL/null.png"
	 * 	@return True if replace success, false otherwise
	 */
	bool replaceTexture(const std::string& sPath);
	bool replaceTexture(ZYSprite *pSprite);
	bool replaceTexture(Sprite *pSprite);
	bool replaceTexture(cocos2d::Texture2D *pTexture);

	/**
	 * 	@des 	Replace current sprite to a new one and change it's current size equal to new sprite's size
	 * 	@prama	sPath A path to the new sprite file eg "NULL/null.png"
	 * 	@return True if replace success, false otherwise
	 */
	bool replaceSprite(const std::string& sPath);

	/**
	 * 	@des 	Replace current sprite to a new one and change it's current size equal to new sprite's size
	 * 	@prama	pSprite The target Sprite
	 * 	@return True if replace success, false otherwise
	 */
	bool replaceSprite(ZYSprite *pSprite);
	bool replaceSprite(Sprite *pSprite);
	bool replaceSprite(Texture2D *pTexture);
	void loadPositionMemory();

	void setScale();
	CLEANER_ZYFUNC(ZYSprite);

	void setEffect(ZYEffect* pEffect);
	void addEffect(ZYEffect* pEffect, ssize_t order);
	void removeEffect();

	ZYSprite* clone();

protected:
	cocos2d::Vec2 m_cMemoryPosition;
	//std::vector<std::tuple<ssize_t, ZYEffect*, cocos2d::QuadCommand>> m_vEffects;
	//ZYEffect* m_pEffect;

private:
	ZYSprite();
	virtual ~ZYSprite();
	FILE_CHECKER_ZYFUNC(ZYSprite);
	std::string p_sClassName = "ZYSprite";
};

NS_ZY_END
