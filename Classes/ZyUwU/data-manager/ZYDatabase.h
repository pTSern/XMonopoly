#pragma once

#include "sqlite3.h"
#include "cocos2d.h"
#include "ZyUwU/platform/CCMacrosSupport.h"
#include "ZyUwU/platform/ZYMacros.h"

#define FALSE 0
#define TRUE 1

#define ZYDB_GI ZYDatabase::getInstance()

class ZYDatabase
{
public:
	inline static ZYDatabase* getInstance()
	{
		return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new ZYDatabase();
	}
	sqlite3* getZYDatabase();
	sqlite3_stmt* getStatement();
	sqlite3_stmt** getPStatement();
	bool getPrepareV2(const std::string& command, const char **pzTail = 0);
	bool getExec(const std::string& command);
	bool isRowStepStatement();
	CREATE_GET_FUNC(isReady, bool, p_bIsReady);

public:
	bool openConnection();
	bool closeConnection();
	void init(const std::string& name);
	bool isEmpty();
	void transferDataToResourcePath();

protected:
	void transferDataToWriteablePath();

private:
	static ZYDatabase *sp_pInstance;
	std::string p_sPath;
	std::string p_sFileName;

	sqlite3 *p_pZYDatabase;
	sqlite3_stmt *p_pStatement;

	bool p_bIsReady;
private:
	ZYDatabase();
};
