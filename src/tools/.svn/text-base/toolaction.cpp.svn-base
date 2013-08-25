#include "toolaction.h"
#include "tools/toolstate.h"
#include <assert.h>

ToolAction::ToolAction()
{
    // set the default values to NULL
    _graph = NULL;
}

ToolAction::ToolAction(ToolState *toolState)
{
    _toolStates.push_back(toolState);
}

ToolAction::ToolAction(ToolState* toolState, Graph* graph, ToolParameters toolParameters)
{
    _toolStates.push_back(toolState);
    _graph = graph;
    _toolParameters.push_back(toolParameters);
}

void ToolAction::addExtraAction(ToolState* toolState, ToolParameters toolParameters)
{
    _toolStates.push_back(toolState);
    _toolParameters.push_back(toolParameters);
}

void ToolAction::execute()
{
    assert(!_toolParameters.empty());
    // the old Graph of a tool is saved here so that it can, if needed be restored
    Graph* tempGraph;
    list<ToolParameters>::iterator j = _toolParameters.begin();
    for (list<ToolState*>::iterator i = _toolStates.begin(); i != _toolStates.end(); ++i, ++j)
    {
        tempGraph = (*i)->getGraph();
        (*i)->setGraph(_graph);
        (*i)->executeNoActionSave(*j);
        // if the graph was different than from what this action is used on
        if (tempGraph != _graph)
            (*i)->setGraph(tempGraph);
    }
}
