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

double SmartAlgorithm::triangleArena(Point A, Point B, Point C)
{
    return 0.5*abs((B.x - A.x)*(C.y - A.y) - (C.x - A.x)*(B.y - A.y));
}

bool SmartAlgorithm::isPointInside4Point(Point A, Point B, Point C, Point D, Point M)
{
    double totalArena = SmartAlgorithm::triangleArena(A, B, C) + SmartAlgorithm::triangleArena(A, C, D);
    double pointArena = SmartAlgorithm::triangleArena(A, B, M) + SmartAlgorithm::triangleArena(B, C, M)
            + SmartAlgorithm::triangleArena(C, D, M) + SmartAlgorithm::triangleArena(D, A, M);
    return (totalArena == pointArena);
}

bool SmartAlgorithm::isPointInsideMultiPoints(std::vector<Point>& vList, Point M)
{
    int num = vList.size();
    int count = 0;
    for (int i = 0; i < num; i++)
    {
        Point A = vList[i];
        Point B = vList[(i + 1) % num];
        if ((A.y <= M.y && M.y < B.y) || (B.y <= M.y && M.y < A.y))
        {
            double t = (M.y - A.y) * (B.x - A.x) - (B.y - A.y) * (M.x - A.x);
            if (t < 0)
            {
                count++;
            }
        }
    }
    return (count % 2 == 1);
}

NS_ZY_END