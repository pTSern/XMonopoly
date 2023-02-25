#include "GameObject.h"
GameObject::GameObject() : cocos2d::Node()
{
}

std::string GameObject::getName()
{
	return this->pProperties->getName();
}
int GameObject::getPiority()
{
	return this->pProperties->getPiority();
}
