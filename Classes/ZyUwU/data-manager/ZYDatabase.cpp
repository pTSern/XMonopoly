#include "ZYDatabase.h"

ZYDatabase* ZYDatabase::sp_pInstance = nullptr;

ZYDatabase::ZYDatabase() :
p_sPath(),
p_bIsReady(false),
p_pZYDatabase(nullptr),
p_pStatement(nullptr)
{
}

bool ZYDatabase::openConnection()
{
	if (sqlite3_open(this->p_sPath.c_str(), &this->p_pZYDatabase) == SQLITE_OK)
	{
		CCLOG("DATABASE: Open connection successfully");
		p_bIsReady = true;
		return true;
	}
	CCLOG("DATABASE: CANNOT open connection");
	this->closeConnection();
	p_bIsReady = false;
	return false;
}

bool ZYDatabase::closeConnection()
{
	sqlite3_finalize(p_pStatement);
	sqlite3_close(this->p_pZYDatabase);
	return true;
}

void ZYDatabase::init(const std::string& name)
{
	p_sPath = CC_FILEUTILS_GI->getWritablePath() + name;
    p_sFileName = name;
	if(this->openConnection())
	{
		this->transferDataToWriteablePath();
	}
}

///] Public

sqlite3* ZYDatabase::getZYDatabase()
{
	if(p_bIsReady) return p_pZYDatabase;
	return nullptr;
}

sqlite3_stmt* ZYDatabase::getStatement()
{
	if(p_bIsReady) return p_pStatement;
	return nullptr;
}

sqlite3_stmt** ZYDatabase::getPStatement()
{
	if(p_bIsReady) return &p_pStatement;
	return nullptr;
}

bool ZYDatabase::getPrepareV2(const std::string& command, const char **pzTail)
{
	if(!p_bIsReady) return false;
	int result = sqlite3_prepare_v2(p_pZYDatabase, command.c_str(), -1, &p_pStatement, pzTail);
	if(result == SQLITE_OK)
	{
		return true;
	}
	return false;
}

bool ZYDatabase::getExec(const std::string& command)
{
	if(!p_bIsReady) return false;
	int result = sqlite3_exec(this->p_pZYDatabase, command.c_str(), nullptr, nullptr, nullptr);
	if (result == SQLITE_OK)
	{
		return true;
	}
	return false;
}

bool ZYDatabase::isEmpty()
{
	auto command = "SELECT name FROM sqlite_master WHERE type = 'table';";
	if(getPrepareV2(command))
	{
		if(isRowStepStatement())
		{
			auto tableName = reinterpret_cast<const char*>(sqlite3_column_text(p_pStatement, 0));

			std::string select = "SELECT COUNT(*) FROM " + std::string(tableName) + ";";

			if(getPrepareV2(select))
			{
				int numRow = 0;
				if(isRowStepStatement())
				{
					numRow = sqlite3_column_int(p_pStatement, 0);
				}
				if(numRow > 0)
				{
					return false;
				}
			}
		}
	}
	CCLOG("ZY-DATABASE: EMPTY DATABASE");
	return true;
}

void ZYDatabase::transferDataToWriteablePath()
{
    auto path = CC_FILEUTILS_GI->fullPathForFilename(p_sFileName);
	if(!CC_FILEUTILS_GI->isFileExist(path))
	{
		return;
	}
	auto data = CC_FILEUTILS_GI->getDataFromFile(path);
	CC_FILEUTILS_GI->writeDataToFile(data, p_sPath);
}

void ZYDatabase::transferDataToResourcePath()
{
	auto path = CC_FILEUTILS_GI->fullPathForFilename(p_sFileName);
	if(!CC_FILEUTILS_GI->isFileExist(path))
	{
		return;
	}
	auto data = CC_FILEUTILS_GI->getDataFromFile(p_sPath);
	CC_FILEUTILS_GI->writeDataToFile(data, path);
}

bool ZYDatabase::isRowStepStatement()
{
	if(sqlite3_step(p_pStatement) == SQLITE_ROW)
	{
		return true;
	}
	return false;
}