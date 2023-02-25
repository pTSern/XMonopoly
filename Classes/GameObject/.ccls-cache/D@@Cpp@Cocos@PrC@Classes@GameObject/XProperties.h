#pragma once
#include "cocos2d.h"
#include "ZyUwU/ZyUwU.h"

class XProperties : public cocos2d::Ref
{
public:
	inline int getPiority()
	{
		return this->p_nPiority;
	}

	inline std::string getName()
	{
		return this->p_sName;
	}
private:
	std::string p_nName;
	int p_nPiority;
	std::string p_sTextureId;
	int p_nZLocal;
};
