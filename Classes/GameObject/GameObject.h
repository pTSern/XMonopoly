#pragma once

#include "XProperties.h"
#include "../ZyUwU/ZyUwU.H"

/**	@des GameObject class. This class inherit CCNode
 *	@var *XProperties: \n+ priority (int) \n+ name (string) \n+ deputize texture (string) The represent of this game-object
 *	@virtual void update(float dt) > Describe how this game-object will be changed per main-loop. Must describe this function in inherit class
 *	@func string getName() > Return this game-object's name
 *	@func int getPriority() > Return this game-object's priority
 */
class GameObject : public cocos2d::Node
{
public:
	GameObject();
	virtual ~GameObject();

public:
	virtual void update(float dt) = 0;
	virtual void log();
	virtual void destructLog();
	virtual std::string toString(int nTab = 2);
	virtual bool init();

public:
	virtual void setName(const std::string& sName) override;
	void setPriority(int nPriority);
	void setDeputizeTexture(std::string var);

	CREATE_GET_FUNC(getName, std::string, this->m_pProperties->getName());
	CREATE_GET_FUNC(getPriority, int, this->m_pProperties->getPriority());
protected:
	CREATE_GET_FUNC(getDeputizeTexture, std::string, this->m_pProperties->getDeputizeTexture());

protected:
	XProperties *m_pProperties;
private:
	std::string p_sClassName = "GameObject";
};


