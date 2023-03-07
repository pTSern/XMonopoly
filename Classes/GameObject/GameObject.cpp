#include "GameObject.h"

//// Constructor

GameObject::GameObject() :
m_pProperties(XProperties::create())
{
}

GameObject::~GameObject()
{
	GameObject::destructLog();
	CC_SAFE_DELETE(m_pProperties);
}


//// Public

void GameObject::setDeputizeTexture(std::string var)
{
	if(FILE_CHECKER(var)) this->m_pProperties->setDeputizeTexture(var);
}

void GameObject::setName(std::string sName)
{
	this->m_pProperties->setName(sName);
}

void GameObject::setPriority(int nPriority)
{
	this->m_pProperties->setPriority(nPriority);
}

//Virtual

void GameObject::log()
{
	ZY_EZ_LOG;
}

bool GameObject::init()
{
	setName("GAME-OBJECT");
	if(!Node::init()) return false;
	return true;
}

void GameObject::destructLog()
{
	std::string dl;
	std::string tab = ZYSP_T();
	ZY_TSHS(dl, tab, " + Name: ", getName());
	CCLOG("SELF-DESTRUCT CALL %s:", dl.c_str());
}

std::string GameObject::toString(int nTab)
{
	std::string ts;
	std::string tab = ZY_SP_TAB(nTab);
	ts += (tab + " + Reference Count: " + ZYSP_NTS(getReferenceCount()));
	ts += (tab + " > XProperties: " + m_pProperties->toString(nTab+1));
	return ts;
}





