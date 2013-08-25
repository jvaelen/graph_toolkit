#include "unexistingnodeex.h"

string UnexistingNodeEx::getMessage() const
{
    string result;
    result += "The following node does not exist in the graph: \n";
    result += "node label: " + _topic.getLabel().getLabelString();
    if (!_extraInfo.empty())
        result += "\nextra information: " + _extraInfo;
    return result;
}
