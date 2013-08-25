#include "addedgetool.h"
#include <assert.h>
#include "tools/toolpm.h"
#include "toolhandler.h"

AddEdgeTool::AddEdgeTool(const string& title, const string& toolTip, const string& iconPath) : ToolState(title, toolTip, iconPath)
{
    // delegate the parameters to the baseclass
}

void AddEdgeTool::execute(const ToolParameters &toolParameters, ToolHandler *context)
{
    assert(_graph);
    executeNoActionSave(toolParameters);
    if (!context) // if the context has not been set, actions can not be undone
        return;
    // now we create the oposite action (removing that edge)
    context->addToolAction(createInverseAction(toolParameters));
}

ToolAction AddEdgeTool::createInverseAction(const ToolParameters &toolParameters)
{
    // first we set up the paramters, in this case the parameters to remove the edge are exactly the same
    ToolParameters inverseToolParams = toolParameters;
    return ToolAction(_toolPM->getTool(getInverseToolType()), _graph, inverseToolParams);
}

void AddEdgeTool::executeNoActionSave(const ToolParameters& toolParameters)
{
    _graph->addEdge(toolParameters.getSourceID(), toolParameters.getTargetID(), toolParameters.getLabel());
}
