#pragma once

/** @des Define the direction of game object
 *  @note NE: North East = 1
 *  @note ES: East South = -1
 *  @note WS: West South = 2
 *  @note NW: North West = -2
 *  @note UK: UNKNOWN = 0
 */
enum class Dir
{
    NE = 1,
    ES = -1,
    WS = 2,
    NW = -2,
    UK = 0
};