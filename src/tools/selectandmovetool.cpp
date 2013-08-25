#include "selectandmovetool.h"
#include "toolpm.h"
#include "toolhandler.h"
#include <assert.h>

SelectAndMoveTool::SelectAndMoveTool(const string& title, const string& toolTip, const string& iconPath) : ToolState(title, toolTip, iconPath)
{
    // parameters are passed to the baseclass of the tool
}

void SelectAndMoveTool::execute(const ToolParameters &toolParameters, ToolHandler *context)
{
    // first deselect everything that might have been selected before this selection happens
    silentDeselectAll(_graph);
    // if no source has been set, then there was no selection
    if (!toolParameters.getSource() && !toolParameters.getEdge())
    {
        // still have to notify the observers about the deselection that might have happened
        notifyObservers();
        return ;
    }
    /* in the case of the selectiontool the createInveserAction will save the action
        locally in the state so that everything can be unsellected when a new node is selected*/
    _unselects[_graph].push(createInverseAction(toolParameters));
    // if the context has not been set, actions can not be undone, but in this case this is pretty senceless, good thing is we don't get compilerwarnings
    if (!context)
        executeNoActionSave(toolParameters);
    else
        executeNoActionSave(toolParameters);
    notifyObservers();
}

ToolAction SelectAndMoveTool::createInverseAction(const ToolParameters &toolParameters)
{
    ToolParameters inverseToolParameters;
    // if it about a node
    if (!toolParameters.getEdge())
    {
        inverseToolParameters.setSource(toolParameters.getSource());
        inverseToolParameters.setRGB(toolParameters.getSource()->getColor());
    }
    else
    {
        inverseToolParameters.setEdge(toolParameters.getEdge());
        inverseToolParameters.setRGB(toolParameters.getEdge()->getColor());
    }
    return ToolAction(_toolPM->getTool(getInverseToolType()), _graph, inverseToolParameters);
}

void SelectAndMoveTool::executeNoActionSave(const ToolParameters& toolParameters)
{
    // if the node is in the current graph
    if (_graph->nodeToIndex(toolParameters.getSource()) != -1)
    {
        toolParameters.getSource()->setColor(toolParameters.getRGB());
        return ;
    }
    if (_graph->edgeExists(toolParameters.getEdge()->getSource(), toolParameters.getEdge()->getTarget(), toolParameters.getEdge()->getLabel()))
        toolParameters.getEdge()->setColor(toolParameters.getRGB());
}

GraphComp* SelectAndMoveTool::getLastSelection(Graph* graph) const
{
    // if there are no selections, immediatly return NULL
    if (_unselects.count(graph) == 0 || _unselects.at(graph).empty())
        return NULL;
    // if the graph has been used in the unselects and if there are some unselects
    if (_unselects.at(graph).top().getLastToolParameter().getEdge())
        return _unselects.at(graph).top().getLastToolParameter().getEdge();
    else
        return _unselects.at(graph).top().getLastToolParameter().getSource();
}

GraphComp* SelectAndMoveTool::getLastSelection() const
{
    return getLastSelection(_graph);
}

void SelectAndMoveTool::silentDeselectAll(Graph *graph)
{
    // for a given graph, if we had previous selections
    if (_unselects.count(graph))
    {
        // pop all the selection actions after executing them
        while(!_unselects[graph].empty())
        {
            _unselects[graph].top().execute();
            _unselects[graph].pop();
        }
    }
}

void SelectAndMoveTool::deselectAll(Graph* graph)
{
    silentDeselectAll(graph);
    notifyObservers();
}
