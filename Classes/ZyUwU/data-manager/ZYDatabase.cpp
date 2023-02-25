#include "ZYDatabase.h"

ZYDatabase* ZYDatabase::sp_pInstance = nullptr;

ZYDatabase::ZYDatabase()
{
	this->p_sPath = cocos2d::FileUtils::getInstance()->getWritablePath() + "database.db";
	this->openConnection();
}
bool ZYDatabase::openConnection()
{
	if (sqlite3_open(this->p_sPath.c_str(), &this->p_pZYDatabase) == SQLITE_OK)
	{
		cocos2d::log("DATABASE: Open connection successfully");
		return true;
	}
	cocos2d::log("DATABASE: CANNOT open connection");
	this->closeConnection();
	return false;
}

bool ZYDatabase::closeConnection()
{
	sqlite3_close(this->p_pZYDatabase);
	return true;
}
void ZYDatabase::createDatabase()
{

}
void ZYDatabase::supperInit()
{

}