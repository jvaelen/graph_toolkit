#ifndef INVALIDGRAPH_H
#define INVALIDGRAPH_H

#include "exception/baseex.h"

class InvalidGraph : public BaseEx
{
public:
    InvalidGraph(string extraInfo = "", int priority = 2) : BaseEx(extraInfo, priority) {}
    string getMessage() const;
};

#endif // INVALIDGRAPH_H
