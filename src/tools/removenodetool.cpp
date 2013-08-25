#include "removenodetool.h"
#include "tools/toolpm.h"
#include "toolhandler.h"

#include <assert.h>

RemoveNodeTool::RemoveNodeTool(const string& title, const string& toolTip, const string& iconPath) : ToolState(title, toolTip, iconPath)
{
    _node = 0;
}

void RemoveNodeTool::execute(const ToolParameters &toolParameters, ToolHandler *context)
{
    assert(_graph);
    if (!context) // if the context has not been set, actions can not be undone
    {
        executeNoActionSave(toolParameters);
        return;
    }
    /* removing the node is a little bit special in the sence that we first
       create the undo action, doing it afterwards is impossible because we lose the node after removing it
       another special thing about removing nodes is that when a node is removed, it can also remove edges, so we have to save those edges aswell*/

    context->addToolAction(createInverseAction(toolParameters));
    // finally remove the node
    executeNoActionSave(toolParameters);
}

ToolAction RemoveNodeTool::createInverseAction(const ToolParameters &toolParameters)
{
    // first we set up the paramters
    ToolParameters inverseToolParams;
    // copy the node over that will be removed
    inverseToolParams.setNode(*(toolParameters.getSource()));
    ToolAction newToolAction(_toolPM->getTool(getInverseToolType()), _graph, inverseToolParams);
    // once we set excludeSelfEdges to true and once to false to prevent savind selfEdges twice
    saveEdges(&newToolAction, _graph->getIncomingEdges(toolParameters.getSource()), true);
    saveEdges(&newToolAction, _graph->getOutgoingEdges(toolParameters.getSource()), false);
    return newToolAction;
}

void RemoveNodeTool::saveEdges(ToolAction *toolAction, const list<Edge *> &edges, bool excludeSelfEdges)
{
    ToolParameters ToolParams;
    for (list<Edge*>::const_iterator i = edges.begin(); i != edges.end(); ++i)
    {
        if (!(excludeSelfEdges && (*i)->isSelfEdge()))
        {
            // we can easely reuse the ToolParams instance to add all the edges that need to be added again
            ToolParams.reset();
            ToolParams.setParametersFromEdge(*i);
            toolAction->addExtraAction(_toolPM->getTool(ADDEDGETOOL), ToolParams);
        }
    }
}

void RemoveNodeTool::executeNoActionSave(const ToolParameters& toolParameters)
{
    _graph->removeNode(toolParameters.getSourceID());
}
