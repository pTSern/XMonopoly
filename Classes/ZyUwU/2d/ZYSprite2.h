#pragma once

#include "renderer/backend/Device.h"
#include "cocos2d.h"
#include "ZyUwU/platform/ZYMacros.h"
#include "ZyUwU/platform/CCMacrosSupport.h"
#include "ZyUwU/base/ZYDirector.h"

USING_NS_CC;

NS_ZY_BEGIN

class ZYEffect;
class ZYSprite : public cocos2d::Sprite
{
public:
	static ZYSprite* create(const char* pFileName, bool bIsScale = true);
	static ZYSprite* create(cocos2d::Texture2D *p);
	static int tupleSort(const std::tuple<ssize_t, ZYEffect*, QuadCommand> &tuple_1,
						 const std::tuple<ssize_t, ZYEffect*, QuadCommand> &tuple_2)
	{
		return std::get<0>(tuple_1) < std::get<0>(tuple_2);
	}
	static void updateUniforms(backend::ProgramState *programState);

public:
	cocos2d::Point getContentPositionWithNewAnchorPoint(cocos2d::Point cNewAnchorPoint);

    cocos2d::Point getContentPositionMiddleTop();
    cocos2d::Point getContentPositionMiddleBottom();
	cocos2d::Point getContentPositionTopLeft();
	cocos2d::Point getContentPositionTopRight();
	cocos2d::Point getContentPositionBottomRight();
	cocos2d::Point getContentPositionBottomLeft();
	cocos2d::Point getContentPositionMiddle();

	cocos2d::Point getDifferentAnchorPoint(cocos2d::Point cNewAnchorPoint);

	CREATE_GET_FUNC(getMemoryPosition, cocos2d::Point, m_cMemoryPosition);

	virtual std::string toString(int nTab = 2);
	virtual void setPosition(const cocos2d::Vec2& pos, cocos2d::Vec2 newAnchor);
	virtual void setPosition(const cocos2d::Vec2& pos);
	virtual void setPosition(const float xx, const float yy);
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

	bool config();
	void log();
	virtual bool initWithFile(const std::string& filename);
	bool replaceTexture(std::string sPath);
	bool replaceTexture(ZYSprite *pSprite);
	bool replaceTexture(cocos2d::Texture2D *pTexture);
	bool replaceSprite(std::string sPath);
	void loadPositionMemory();

	void setScale();
	CLEANER_ZYFUNC(ZYSprite);

	void setEffect(ZYEffect* pEffect);
	void addEffect(ZYEffect* pEffect, ssize_t order);


protected:
	cocos2d::Vec2 m_cMemoryPosition;
	std::vector<std::tuple<ssize_t, ZYEffect*, cocos2d::QuadCommand>> m_vEffects;
	ZYEffect* m_pEffect;

private:
	ZYSprite();
	virtual ~ZYSprite();
	FILE_CHECKER_ZYFUNC(ZYSprite);
	const char* p_sClassName = typeid(this).name();
};

NS_ZY_END
