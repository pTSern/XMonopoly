#include "LogManager.h"
#include <fstream>

LogManager* LogManager::sp_pInstance = nullptr;

LogManager::LogManager() :
p_bIsError(true)
{

}

bool LogManager::init()
{
    time_t time = std::time(nullptr);
    tm* timeinfo = localtime(&time);

    //file_name index
    int nNum = 1;

    //Get Current year/month/day
    p_sCurrentTime = std::to_string(timeinfo->tm_year + 1900) + "-" + std::to_string(timeinfo->tm_mon + 1) + "-" + std::to_string(timeinfo->tm_mday);

    //Create file_name = current_time-number.log
    p_sLogName = p_sCurrentTime + "-" + std::to_string(nNum) + ".log";


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    //Get root path = Root/
    p_sRootPath = CC_FILEUTILS_GI->getDefaultResourceRootPath() + "Log";

    //Create folder: Root/Log
    mkdir(p_sRootPath.c_str());

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //Get root path = Root/
    p_sRootPath = CC_FILEUTILS_GI->getDefaultResourceRootPath() + "Log";

    //Create folder: Root/Log
    if(!CC_FILEUTILS_GI->createDirectory(p_sRootPath))
        CCLOG("CALL LOG-MANAGER: CAN NOT CREATE DIRECTOR");
        p_bIsError = false;

#endif

    //Create path = Root/Log/file_name
    p_sPath = p_sRootPath + "/" + p_sLogName;

    //Loop check valid path
    if (checkValidPathLog(nNum))
    {
    }

    return true;
}
void LogManager::log(std::string sLog)
{
    if(p_bIsError) {
        time_t time = std::time(nullptr);
        tm *timeinfo = localtime(&time);
        std::string sCurrentTime =
                "[" + std::to_string(timeinfo->tm_hour) + ":" + std::to_string(timeinfo->tm_min) +
                ":" + std::to_string(timeinfo->tm_sec) + "] ";

        std::fstream as(p_sPath, std::fstream::app);
        if (as.is_open()) {
            as << (sCurrentTime + sLog + "\n");
            as.close();
        } else
            CCLOG("CALL LOG-MANAGER: CAN NOT OPEN THIS FILE");
        //cocos2d::FileUtils::getInstance()->writeStringToFile(sCurrentTime + sLog, p_sPath);
    }
    
}

void LogManager::log()
{
    std::string ts;
    std::string tab = ZY_SP_TAB(2);
    ZY_TSHS(ts, tab, " + Path: ", p_sPath);
    ZY_TSHS(ts, tab, " + Root Path: ", p_sRootPath);
    ZY_TSHS(ts, tab, " + Current Time: ", p_sCurrentTime);
    ZY_TSHS(ts, tab, " + Log Name: ", p_sLogName);
    CCLOG("CALL LOG-MANAGER: %s", ts.c_str());
}

bool LogManager::checkValidPathLog(int n)
{
    if (CC_FILEUTILS_GI->isFileExist(p_sPath))
    {
        p_sLogName = p_sCurrentTime + "-" + std::to_string(n + 1) + ".log";
        p_sPath = p_sRootPath + "/" + p_sLogName;
        return this->checkValidPathLog(n + 1);
    }
    else return true;
}