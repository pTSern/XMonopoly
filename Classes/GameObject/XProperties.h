#pragma once

#include "cocos2d.h"
#include "ZyUwU/ZyUwU.h"

USING_NS_ALL;

//BEGIN_CREATE_REFCLASS(XProperties, Ref)
class XProperties
{
public:
	static XProperties* create();
	std::string toString(int nTab = 2);
	void log();

public:
	CREATE_SET_GET_FUNC(setPriority, getPriority, int, p_nPriority);

	CREATE_SET_GET_FUNC(setName, getName, std::string, p_sName);

	CREATE_SET_GET_FUNC(setDeputizeTexture, getDeputizeTexture, std::string, p_sDeputizeTexture);

	CREATE_SET_GET_FUNC(setLocalZOrder, getLocalZOrder, int, p_nLocalZOrder);

	CREATE_SET_GET_FUNC(setGlobalZOrder, getGlobalZOrder, int, p_nGlobalZOrder);

public:
	XProperties *clone();
	XProperties();
	virtual ~XProperties();

protected:
	bool init();

private:
	std::string p_sName;
	int p_nPriority;
	int p_nLocalZOrder, p_nGlobalZOrder;
	std::string p_sDeputizeTexture;
};
//END_CREATE_REFCLASS
