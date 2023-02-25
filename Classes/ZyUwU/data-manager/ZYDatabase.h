#pragma once

#include "sqlite3.h"
#include "cocos2d.h"

#define FALSE 0
#define TRUE 1

class ZYDatabase
{
public:
	inline static ZYDatabase* getInstance()
	{
		return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new ZYDatabase();
	}
	inline sqlite3* GetZYDatabase()
	{
		return this->p_pZYDatabase;
	}
	inline sqlite3_stmt* getStatement()
	{
		return this->p_pStatement;
	}
	inline sqlite3_stmt** getPStatement()
	{
		return &this->p_pStatement;
	}
	inline bool getPrepareV2(std::string command, const char **pzTail = 0)
	{
		int result = sqlite3_prepare_v2(this->p_pZYDatabase, command.c_str(), -1, &this->p_pStatement, pzTail);
		if ( result == SQLITE_OK)
		{
			return true;
		}
		return false;
	}
	inline bool getExec(std::string command)
	{
		int result = sqlite3_exec(this->p_pZYDatabase, command.c_str(), NULL, NULL, NULL);
		if (result == SQLITE_OK)
		{
			return true;
		}
		return false;
	}
public:
	bool openConnection();
	bool closeConnection();
	void supperInit();
private:
	void createDatabase();
private:
	static ZYDatabase *sp_pInstance;
	std::string p_sPath;

	sqlite3 *p_pZYDatabase;
	sqlite3_stmt *p_pStatement;
private:
	ZYDatabase();
};
