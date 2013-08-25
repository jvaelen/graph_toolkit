#include "baseex.h"

BaseEx::BaseEx()
{
    _extraInfo = "";
    _priority = 0;
}

BaseEx::BaseEx(const string& extraInfo, int priority)
{
    _extraInfo = extraInfo;
    _priority = priority;
}

void BaseEx::overridePriority(int priority)
{
    if (priority >= 0)
        _priority = priority;
    else
        _priority = 0; // this is the lowest possible priority
}
