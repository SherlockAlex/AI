#include "AIMath.h"

diff A_Round(diff x)
{
    int t;
    diff  s;
    x = x * 1000;//保留2位，原有数据*10^（2+1）
    t = (x + 5) / 10;
    s = (diff)t / 100;
    return s;
}
