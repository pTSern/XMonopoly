#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class NoTarget;
class TargetPoint;
class TargetArena;
class Combination;
class WarpType
{
public:
    enum class Type
    {
        NONE = 0,
        NO_TARGET,
        POINT,
        ARENA,
        COMBINATION
    };

public:
    WarpType();
    explicit WarpType(NoTarget* ret);

    bool isNull() const
    {
        return p_eType == Type::NONE;
    }

public:
    NoTarget* asNoTarget() const;
    TargetPoint* asTargetPoint() const;
    TargetArena* asTargetArena() const;
    Combination* asCombination() const;

private:
    Type p_eType;
    union
    {
        NoTarget* pNoTarget;
        TargetPoint* pTargetPoint;
        TargetArena* pTargetArena;
        Combination* pCombine;
    } _field;
};

