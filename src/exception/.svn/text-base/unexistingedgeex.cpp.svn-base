#include "unexistingedgeex.h"

#include "uniqueedgeex.h"
#include "graph/graphComp/edge.h"
#include "graph/graphComp/node.h"

string UnexistingEdgeEx::getMessage() const
{
    string result;
    result += "The following edge does not exist in the graph: \n";
    result += "source label: " + _topic.getSource()->getLabel().getLabelString() + "\n";
    result += "edge label: "   + _topic.getLabel().getLabelString() + "\n";
    result += "target label: " + _topic.getTarget()->getLabel().getLabelString() + "\n";
    if (!_extraInfo.empty())
        result += "extra information: " + _extraInfo;
    return result;
}
