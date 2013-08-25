#include "toolhandler.h"
#include "selectandmovetool.h"
#include <assert.h>

ToolHandler::ToolHandler()
{
    _state = NULL;
}

ToolHandler::~ToolHandler()
{
    // remember to remove this delete if we choose the manage the states with a prototype manager
    // delete _state;
}

void ToolHandler::setState(ToolState* state)
{
    // if no state change occured, just finish because nothing happened (for efficiency)
    if (_state == state)
        return ;
    if(dynamic_cast<SelectAndMoveTool*>(state))
        _selectionState = dynamic_cast<SelectAndMoveTool*>(state);
    // set the new state
    _state = state;
    deselectIfNeeded();
    notifyObservers();
}

void ToolHandler::setGraph(Graph* graph)
{
    assert(_state);
    _graph = graph;

    // if we have saved the last state for a graph
    _state->setGraph(graph);
    SelectAndMoveTool* tempState;
    if ((tempState = dynamic_cast<SelectAndMoveTool*>(_state)))
        tempState->notifyObservers();
    deselectIfNeeded();
}

void ToolHandler::deselectIfNeeded()
{
    if (_state->getToolType() != SELECTTOOL )
        _selectionState->deselectAll(_state->getGraph());
}

void ToolHandler::execute(const ToolParameters& toolParameters)
{
    assert(_state);
    // delegate to state
    _state->execute(toolParameters, this);
}

void ToolHandler::unexecute()
{
    assert(_state);
    // if we have undoactions for that graph
    if (_undoStacks.count(_state->getGraph()) && !(_undoStacks[_state->getGraph()].empty()))
    {
        _undoStacks[_state->getGraph()].top().execute();
        _undoStacks[_state->getGraph()].pop();
    }
}

void ToolHandler::clearActionsForGraph(Graph* graph)
{
    if (_undoStacks.count(graph))
        _undoStacks.erase(graph);
}

void ToolHandler::addToolAction(ToolAction toolAction)
{
    _undoStacks[toolAction.getGraph()].push(toolAction);
}
