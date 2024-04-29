#include "Round.h"

int gez::math::RoundUp(int num, int multiple)
{
    if (multiple == 0)
    {
        return num;
    }

    int remainder = num % multiple;
    if (remainder == 0)
    {
        return num;
    }

    return num + multiple - remainder;
}

int gez::math::RoundDown(int num, int multiple)
{
    if (multiple == 0)
    {
        return num;
    }

    int remainder = num % multiple;
    if (remainder == 0)
    {
        return num;
    }

    return num - remainder;
}