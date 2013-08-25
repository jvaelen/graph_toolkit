#include "uniquenodeex.h"
#include "graph/graphComp/node.h"

string UniqueNodeEx::getMessage() const
{
    string result;
    result += "Unique Node Exception about the following node (the node already exists): ";
    result += "node label: " + _topic.getLabel().getLabelString();
    if (!_extraInfo.empty())
        result += "\nextra information: " + _extraInfo;
    return result;
}
