#pragma once
#include "cocos2d.h"
#include <iostream>
#include <fstream>
#include "ZyUwU/ZyUwU.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "direct.h"
#endif

USING_NS_ALL;

#define LOG_MANAGER_GI LogManager::getInstance()

class LogManager
{
public:
	static LogManager* getInstance()
	{
		if(!sp_pInstance)
		{
			sp_pInstance = new (std::nothrow) LogManager();
        	CCASSERT(sp_pInstance, "FATAL: Not enough memory");
			sp_pInstance->init();
		}
		return sp_pInstance;
	}
	static void selfDestroyInstance()
	{
    	delete LogManager::sp_pInstance;
		LogManager::sp_pInstance = nullptr;
	}
	void log(std::string sLog);
	bool checkValidPathLog(int n);
	void log();
private:
	LogManager();
	bool init();

private:
    bool p_bIsError;
	std::string p_sPath, p_sCurrentTime, p_sLogName, p_sRootPath;
	static LogManager* sp_pInstance;
};
