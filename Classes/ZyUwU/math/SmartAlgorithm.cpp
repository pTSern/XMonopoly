#include "SmartAlgorithm.h"

NS_ZY_BEGIN

int SmartAlgorithm::findGCD(int nFirst, int nSecond)
{
    if(nSecond == 0) return nFirst;

    return SmartAlgorithm::findGCD(nSecond, nFirst % nSecond);
}

int SmartAlgorithm::findLCM(int nNum, ...)
{
    va_list args;
    va_start(args, nNum);
    std::vector<int> list;

    int num = va_arg(args, int);
    list.push_back(nNum);

    while(num)
    {
        list.push_back(num);
        num = va_arg(args, int);
    }

    va_end(args);

    return SmartAlgorithm::findLCMWithVector(list);
}

int SmartAlgorithm::findLCMWithVector(std::vector<int> vList)
{
    int ans = vList[0];

    for(int i = 1; i < vList.size(); i++)
    {
        ans = ( vList[i] * ans ) / (SmartAlgorithm::findGCD(vList[i], ans));
    }
    return ans;
}

bool SmartAlgorithm::checkPointOnLine(Point A, Point B, Point M)
{
    if(A == B) return false;
    auto a = (A.y - B.y) / (A.x - B.x);
    auto b = B.y - B.x * a;

    return M.y == (M.x * a + b);
}
NS_ZY_END