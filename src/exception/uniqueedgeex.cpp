#include "uniqueedgeex.h"
#include "graph/graphComp/edge.h"
#include "graph/graphComp/node.h"

string UniqueEdgeEx::getMessage() const
{
    string result;
    result += "Unique Edge Exception about the following edge (the edge already exists): ";
    result += "source label: " + _topic.getSource()->getLabel().getLabelString() + "\n";
    result += "edge label: "   + _topic.getLabel().getLabelString() + "\n";
    result += "target label: " + _topic.getTarget()->getLabel().getLabelString() + "\n";
    if (!_extraInfo.empty())
        result += "extra information: " + _extraInfo;
    return result;
}
