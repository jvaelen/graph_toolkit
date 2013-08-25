#ifndef INVALIDFORMATEX_H
#define INVALIDFORMATEX_H

#include "baseex.h"

class InvalidFormatEx : public BaseEx
{
public:
    InvalidFormatEx(string extraInfo = "", int priority = 0) : BaseEx(extraInfo, priority) {}
    string getMessage() const;
};

#endif // INVALIDFORMATEX_H
