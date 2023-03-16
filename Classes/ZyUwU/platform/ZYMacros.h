#pragma once

#include "../../../cocos2d/cocos/cocos2d.h"

/** @def INIT_CHECKER(__CC_TYPE__, __CC_ID__)
 *  @des Define a auto check valid function for a specific type such as Sprite
 *
 *  @pragma __CC_TYPE__ a cocos class type to check valid __CC_ID__
 *  @pragma __CC_ID__ a variable need to be checked if it existed or cocos class can create a variable with it
 */ 
#define INIT_CHECKER(__CC_TYPE__, __CC_ID__) \
{\
	__CC_TYPE__ *pElement = __CC_TYPE__::create(__CC_ID__); \
	if(!pElement) \
	{ \
		CC_SAFE_DELETE(pElement); \
		return false; \
	} \
}                                            \

/**	@def CREATE_SET_FUNC(__FUNC_NAME__, __RETURN_TYPE__, __RETURN_VAR__)
 * 	@des Create a function that set the selected variable a new value
 *
 * 	@pragma __FUNC_NAME__ The function's name
 * 	@pragma __VAR_TYPE__ The type of the input variable
 *  @pragma __SET_VAR__ The variable will be replace a new value after call the function
 *
 */
#define CREATE_SET_FUNC(__FUNC_NAME__, __VAR_TYPE__, __SET_VAR__) \
inline void __FUNC_NAME__(__VAR_TYPE__ var)                       \
{                                                                 \
    __SET_VAR__ = var;                                            \
}                                                                 \

/**	@def CREATE_GET_FUNC(__FUNC_NAME__, __RETURN_TYPE__, __RETURN_VAR__)
 * 	@des Create a function that return a value
 *
 * 	@pragma __FUNC_NAME__ The function's name
 * 	@pragma __RETURN_TYPE__ The return type of the function
 *  @pragma __RETURN_VAR__ The variable will be returned after call the function
 *
 * 	@return __RETURN_VAR__
 */
#define CREATE_GET_FUNC(__FUNC_NAME__, __RETURN_TYPE__, __RETURN_VAR__) 	\
inline __RETURN_TYPE__ __FUNC_NAME__()                                     	\
{                                                                          	\
    return __RETURN_VAR__;                                           		\
}                                                                          	\


#define CREATE_SET_GET_FUNC(__SET_FUNC_NAME__, __GET_FUNC_NAME__, __VAR_TYPE__, __VAR__) \
CREATE_SET_FUNC(__SET_FUNC_NAME__, __VAR_TYPE__, __VAR__)		  \
CREATE_GET_FUNC(__GET_FUNC_NAME__, __VAR_TYPE__, __VAR__)         \

/**	@def CREATE_CLONE_GET_FUNC(__GET_FUNC_NAME__, __RETURN_TYPE__, __RETURN_VAR__)
 *
 * 	@des Create a function that can clone and delete the input variable
 *
 * 	@pragma __FUNC_NAME__ The function's name
 * 	@prama __RETURN_TYPE__ The return type of the function
 *  @prama __RETURN_VAR__ The variable will be returned after call the function
 *
 * 	@warning the
 */
#define CREATE_CLONE_GET_FUNC(__GET_FUNC_NAME__, __RETURN_TYPE__, __RETURN_VAR__)

/** @def CREATE_CLONE_SET_FUNC(__FUNC_NAME__, __VAR_TYPE__, __SET_VAR__ )
 *  @des Create a function that can clone and delete the input variable
 *
 *  @pragma __FUNC_NAME__ The function's name
 *  @pragma __VAR_TYPE__ The type of your input variable. THIS ONLY WORK FOR POINTER
 *  @pragma __SET_VAR__ The variable will be replace a new value after call the function
 *  @pragma bIsClone If this is true, the input variable (var) will be clone.
 *  @pragma bIsClean If this is true, the input variable (var) will be clean. Only work if bIsClone = true
 *
 *  @warning If you don't clone the input, DON'T DELETE IT.
 *  @warning Your input must have clone() function
 *  @warning Careful to delete the input function.
 *
 */
#define CREATE_CLONE_SET_FUNC(__FUNC_NAME__, __VAR_TYPE__, __SET_VAR__ ) 						\
void __FUNC_NAME__(__VAR_TYPE__* var, bool bIsClone = true, bool bIsClean = true) 				\
{                                                                            					\
	if(var)                                                                     				\
    {                                                                          					\
        CC_SAFE_DELETE(__SET_VAR__);                                                            \
        if(bIsClone)                                                                            \
        {                                                                      					\
            __SET_VAR__ = var->clone();                                                    		\
        	if(bIsClean) CC_SAFE_DELETE(var);                                 					\
        }                                                                                    	\
        else                                                                                	\
        {                                                                                    	\
            __SET_VAR__ = var;                                                 					\
        }                                                                                    	\
    }                                                                             				\
}                                                                          						\



#define FILE_CHECKER(__FILE_ADDRESS__) (cocos2d::FileUtils::getInstance()->isFileExist(__FILE_ADDRESS__)) \

#define FILE_CHECKER_ZYFUNC(__TYPE__) \
bool isValidFile(std::string sFileName) \
{ \
	return FILE_CHECKER(sFileName);      \
}                                     \


/** @def ZY_CREATE_FUNC(__TYPE__)
 *	Define a create function for a specific type and easy control autorelease
 *
 *	@prama __TYPE__ The class type to add this function
 */
#define ZY_CREATE_FUNC(__TYPE__) \
static __TYPE__* create(bool bIsAutoRelease = true)        \
{                                \
	__TYPE__ *pRet = new (std::nothrow) __TYPE__();\
	if (pRet && pRet->init())       \
	{                               \
    	if(bIsAutoRelease) pRet->autorelease();               \
		return pRet;\
	}                               \
	delete pRet;                    \
	pRet = nullptr;                 \
	return nullptr;\
}                                \


/** @def BEGIN_CREATE_REFCLASS(__NAME__, __REF_CLASS__)\n
 *  @des Define a new class inherits other class
 *
 *  @pragma __NAME__ this is the new class's name
 *  @pragma __REF_CLASS__ this is the name of class which this class will inherit
 *
 * 	@func public: __NAME__() -> Constructor function
 * 	@virutal public: ~__NAME__() -> Destructor function
 * 	@virtual public: bool init() -> Init function, must define it.
 * 	@virtual public: string toString(int nTab) -> Convert this class to string, must define it \n > > > Pragma: nTab The number of tab will be printed on console screen. Default = 2
 * 	@virtual public: void log() -> Write down all this class's information into console, must define it
 *
 *  @warning Must call END_CREATE_REFCLASS after call this
 */
#define BEGIN_CREATE_REFCLASS(__NAME__, __REF_CLASS__) 	\
class __NAME__ : public __REF_CLASS__                  	\
{                                                   	\
public:                                              	\
    ZY_CREATE_FUNC(__NAME__);                           \
    virtual bool init();                               	\
    virtual std::string toString(int nTab = 2);        	\
    virtual void log();                                 \
    __NAME__();                                         \
private:                                               	\
	std::string p_sClassName = #__NAME__;               \

#define END_CREATE_REFCLASS };

/** @def BEGIN_CREATE_INSTANCE_REFCLASS(__NAME__,__REF_CLASS__)\n
 * 	@des Define a new class have an instance pointer
 *
 * 	@pragma __NAME__ this is the new class's name
 * 	@pragma __REF_CLASS__ this is the name of class which tis class will inherit
 *
 * 	@func public: __NAME__() -> Constructor function
 * 	@virutal public: ~__NAME__() -> Destructor function
 * 	@virtual public: bool init() -> Init function, must define it.
 * 	@virtual public: string toString(int nTab) -> Convert this class to string, must define it \n > > > Pragma: nTab The number of tab will be printed on console screen. Default = 2
 * 	@virtual public: void log() -> Write down all this class's information into console, must define it
 *
 * 	@warning Must call END_CREATE_INSTANCE_REFCLASS after call this
 * 	@warning Make sp_pInstance = nullptr att source file
 * 	@warning Must define the CREATE() function
 */
#define BEGIN_CREATE_INSTANCE_REFCLASS(__NAME__, __REF_CLASS__)                          	\
class __NAME__ : public __REF_CLASS__                                                    	\
{                                                                                        	\
public:                                                                                  	\
	static __NAME__* getInstance()                                              	 	 	\
    {                                                                                    	\
		if(!sp_pInstance)                                                                	\
		{                                                                                	\
			sp_pInstance = new (std::nothrow) __NAME__();                                	\
        	CCASSERT(sp_pInstance, "FATAL: Not enough memory");                          	\
			sp_pInstance->init();                                                     	 	\
		}                                                                                	\
		return sp_pInstance;                                                             	\
	}                                                                                       \
    static void selfDestroyInstance()                                                    	\
	{                                                                                       \
    	CC_SAFE_DELETE(__NAME__::sp_pInstance);                                             \
		__NAME__::sp_pInstance = nullptr;													\
	}																						\
	virtual bool init();                                                                 	\
    virtual std::string toString(int nTab = 2);                                          	\
    virtual void log();                                                                  	\
	__NAME__();                                                                          	\
private:                                                                                 	\
	static __NAME__* sp_pInstance;                                                       	\
	std::string p_sClassName = #__NAME__;               \

#define END_CREATE_INSTANCE_REFCLASS };

#define BEGIN_CREATE_CLASS(__NAME__)  					\
class __NAME__                        					\
{                                                   	\
public:                               					\
    static __NAME__* create()         					\
	{                                    				\
    	auto ret = new (std::nothrow) __NAME__();       \
    	if(ret && ret->init())           				\
		{                                   			\
        	return ret;                              	\
		}                                   			\
    	CC_SAFE_DELETE(ret);             				\
    	return nullptr;                                 \
	}													\
    virtual bool init();                               	\
    virtual std::string toString(int nTab = 2);        	\
    virtual void log();                                 \
    __NAME__();                                         \
private:                                               	\
	std::string p_sClassName = #__NAME__;               \

#define END_CREATE_CLASS };

/**
 * 	@des Easy write down the log() function
 * 	@warning This class must have (p_sClassName) variable to execute
 */
#define ZY_EZ_LOG \
do{\
CCLOG("CALL %s: %s", p_sClassName.c_str(), this->toString().c_str()); \
} while(0);       \

#define ZY_EZ_DE_LOG \
do{\
CCLOG("CALL %s: SELF DESTRUCT > ADDRESS: %p", p_sClassName.c_str(), this);                     \
} while(0)\


/** @def ZY_TO_STRING_HELPER_POINTER(__TO_STRING__, __TAB__, __TAB_NUMBER__, __LOG_STRING__, __VAR_POINTER__)
 * 	@des Help the toString(int nTab) function easier
 *
 *	@pragma __TO_STRING__ The input string will be added. This string is the return of toString(int nTab) function (Just put ts here)
 *	@pragma __TAB__ The string contain number of tab have been calculated post this action (Just put tab here)
 *	@pragma __TAB_NUMBER__ The number of tab (Just put nTab here)
 *	@pragma __LOG_STRING__ The title
 *	@pragma __VAR_POINTER__ The pointer have toString(int nTab) function
 *
 */
#define ZY_TO_STRING_HELPER_POINTER(__TO_STRING__, __TAB__, __TAB_NUMBER__, __LOG_STRING__, __VAR_POINTER__) 		\
if(__VAR_POINTER__) __TO_STRING__ += (__TAB__ + __LOG_STRING__ + __VAR_POINTER__->toString(__TAB_NUMBER__ + 1)); 	\
else __TO_STRING__ += (__TAB__ + __LOG_STRING__ + " nullptr");                                                 \

/**	@def
 * 	@des The short-cut of ZY_TO_STRING_HELPER_POINTER define
 */
#define ZY_TSHP(__TO_STRING__, __TAB__, __TAB_NUMBER__, __LOG_STRING__, __VAR_POINTER__) ZY_TO_STRING_HELPER_POINTER(__TO_STRING__, __TAB__, __TAB_NUMBER__, __LOG_STRING__, __VAR_POINTER__)

/**
 *
 *
 */
#define ZY_TO_STRING_HELPER_VECTOR(__TO_STRING__, __TAB__, __TAB_NUMBER__, __LOG_STRING__, __VAR_VECTOR__) \
if(__VAR_VECTOR__.empty()) __TO_STRING__ += (__TAB__ + __LOG_STRING__ + "have no member");             \
else for(int i = 0; i < __VAR_VECTOR__.size(); i++) {                                                              					\
    __TO_STRING__ += (__TAB__ + __LOG_STRING__ + "[" + ZYSP_NTS(i) + "]" + __VAR_VECTOR__[i]->toString(__TAB_NUMBER__ + 1)); 	\
}                                                                                                                				\

#define ZY_TSHV(__TO_STRING__, __TAB__, __TAB_NUMBER__, __LOG_STRING__, __VAR_VECTOR__) ZY_TO_STRING_HELPER_VECTOR(__TO_STRING__, __TAB__, __TAB_NUMBER__, __LOG_STRING__, __VAR_VECTOR__)

/**
 *
 *
 *
 */
#define ZY_TO_STRING_HELPER_NONE_POINTER(__TO_STRING__, __TAB__, __TAB_NUMBER__, __LOG_STRING__, __VAR__) \
__TO_STRING__ += (__TAB__ + __LOG_STRING__ + __VAR__.toString(__TAB_NUMBER__ + 1));

#define ZY_TSHNP(__TO_STRING__, __TAB__, __TAB_NUMBER__, __LOG_STRING__, __VAR__) ZY_TO_STRING_HELPER_NONE_POINTER(__TO_STRING__, __TAB__, __TAB_NUMBER__, __LOG_STRING__, __VAR__) \


/**
 *
 *
 *
 *
 */
#define ZY_TO_STRING_HELPER_NUMBER(__TO_STRING__, __TAB__, __LOG_STRING__, __VAR_NUMBER__) \
__TO_STRING__ += (__TAB__ + __LOG_STRING__ + ZYSP_NTS(__VAR_NUMBER__));                    \

#define ZY_TSHN(__TO_STRING__, __TAB__, __LOG_STRING__, __VAR_NUMBER__) ZY_TO_STRING_HELPER_NUMBER(__TO_STRING__, __TAB__, __LOG_STRING__, __VAR_NUMBER__)

/**
 *
 *
 */
#define ZY_TO_STRING_HELPER_STRING(__TO_STRING__, __TAB__, __LOG_STRING__, __VAR_STRING__) \
__TO_STRING__ += (__TAB__ + __LOG_STRING__ + __VAR_STRING__);                              \

#define ZY_TSHS(__TO_STRING__, __TAB__, __LOG_STRING__, __VAR_STRING__) ZY_TO_STRING_HELPER_STRING(__TO_STRING__, __TAB__, __LOG_STRING__, __VAR_STRING__)

/** @def CLEANER(__TYPE__)
*  @des Define a cleaner function for a specific class
* 
*  @pragma __TYPE__ class type to add cleaner() function
*/
#define CLEANER_ZYFUNC(__TYPE__)\
inline static void cleaner(__TYPE__ *pElement) \
{ \
	CC_SAFE_DELETE(pElement); \
}

#define GET_CLASS_ADDRESS(__TYPE__, __VARIABLE__)\
{ \
std::stringstream ss; \
ss << __VARIABLE__; \
std::string address = ss.str(); \
CCLOG("Address: %s", address.c_str()); \
} \

#define SET_UNIFORM(ps, name, value)  do {   \
decltype(value) __v = value;                           \
auto __loc = (ps)->getUniformLocation(name);  \
(ps)->setUniform(__loc, &__v, sizeof(__v));  \
} while(false) 

#define SET_TEXTURE(ps, name, idx, value)  do {   \
auto * __v = value;                           \
auto __loc = (ps)->getUniformLocation(name);  \
(ps)->setTexture(__loc, idx, __v);  \
} while(false) 

/* Generic macros
* @namespace nova
* @{
*/
#ifdef __cplusplus
	#define NS_ZY_BEGIN namespace zy { 
	#define NS_ZY_END }
	#define USING_NS_ZY using namespace zy
	#define USING_NS_JSON using namespace nlohmann

	#define USING_NS_ALL  \
		USING_NS_ZY;        \
		USING_NS_CC;         \

	#define NS_ZY ::zy
#endif

