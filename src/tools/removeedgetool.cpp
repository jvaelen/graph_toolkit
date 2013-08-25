#include "removeedgetool.h"
#include "tools/toolpm.h"
#include "toolhandler.h"

#include <assert.h>

RemoveEdgeTool::RemoveEdgeTool(const string& title, const string& toolTip, const string& iconPath) : ToolState(title, toolTip, iconPath)
{
    // constructor delegates the parameters to the baseclass
}

void RemoveEdgeTool::execute(const ToolParameters &toolParameters, ToolHandler *context)
{
    assert(_graph);
    executeNoActionSave(toolParameters);
    if (!context) // if the context has not been set, actions can not be undone
        return;

    context->addToolAction(createInverseAction(toolParameters));
}

ToolAction RemoveEdgeTool::createInverseAction(const ToolParameters &toolParameters)
{
    // now we create the oposite action (adding that edge)
    // first we set up the paramters, in this case the parameters to remove the edge are exactly the same
    ToolParameters inverseToolParams = toolParameters;
    return ToolAction(_toolPM->getTool(getInverseToolType()), _graph, inverseToolParams);
}

void RemoveEdgeTool::executeNoActionSave(const ToolParameters& toolParameters)
{
    _graph->removeEdge(toolParameters.getSourceID(), toolParameters.getTargetID(), toolParameters.getLabel());

}
