#pragma once

/** @def FUNC_REPLACE_UI(__FUNC__NAME__, __VAR__1__, __VAR__2__, __PATH__)
 *
 *  @des Fast create a function to set a new Sprite
 *
 *  @pragma __FUNC__NAME__: function name
 *  @pragma __VAR__1__: the ZYSprite need to be replaced
 *  @pragma __VAR__2__: the String variable store the ZYSprite path
 *
 */
#define FUNC_REPLACE_UI(__FUNC_NAME__, __VAR__1__, __VAR__2__) \
void __FUNC_NAME__(std::string sPath)                            \
{                                                                   \
if(__VAR__1__->replaceTexture(sPath))                            \
{this->__VAR__2__ = sPath;}                                       \
}                                                                        \
