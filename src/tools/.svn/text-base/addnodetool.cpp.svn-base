#include "addnodetool.h"
#include "graph/graphComp/label.h"
#include "tools/toolpm.h"
#include "toolhandler.h"

#include <assert.h>

AddNodeTool::AddNodeTool(const string& title, const string& toolTip, const string& iconPath) : ToolState(title, toolTip, iconPath)
{
    // delegate the paramaters to the baseclass
}

void AddNodeTool::execute(const ToolParameters &toolParameters, ToolHandler *context)
{
    assert(_graph);
    executeNoActionSave(toolParameters);
    if (!context) // if the context has not been set, actions can not be undone
        return;
    context->addToolAction(createInverseAction());
}

ToolAction AddNodeTool::createInverseAction()
{
    // the created node is the last node that we have added to the graph
    Node* createdNode = _graph->getNodes().back();
    // now we create the oposite action (removing that node)
    // first we set up the paramters
    ToolParameters inverseToolParams;
    inverseToolParams.setSource(createdNode);
    return ToolAction(_toolPM->getTool(getInverseToolType()), _graph, inverseToolParams);
}

void AddNodeTool::executeNoActionSave(const ToolParameters& toolParameters)
{
    _graph->addNode(toolParameters.getNode());
}
