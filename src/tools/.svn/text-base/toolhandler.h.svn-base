/*
 Author: Jeroen vaelen and Balazs Nemeth
 Description: toolhandler that is the context of the state (a state is a specific tool)
     */

#ifndef TOOLHANDLER_H
#define TOOLHANDLER_H

#include "toolstate.h"
#include "observer/subject.h"
#include "toolaction.h"
#include <stack>

class Graph;
class SelectAndMoveTool;

class ToolHandler : public Subject
{
public:
    ToolHandler();
    ~ToolHandler();
    // change current tool
    // for example, when the tool state is add node, you must set newState.setParameters("someString")
    // this is normally done in the GUI
    void setState(ToolState* state);
    // returns the graph that the toolhandler is linked to
    Graph* getGraph() const {return _state->getGraph();}
    // returns the current sate
    ToolState* getToolState() const {return _state;}
    void setGraph(Graph* graph);
    // executes an action on the selected graph
    void execute(const ToolParameters& toolParameters);
    // adds a toolaction to the undolist
    void addToolAction(ToolAction toolAction);
    // undoes the last action
    void unexecute();
    // returns the type of the tool, this is ONLY used to know what parameters have to be set for the tool
    ToolType getToolType() const {return _state->getToolType();}
    // should be called wenever a graph is deleted, all the actions are not needed anymore, calling this function will free up some memory
    void clearActionsForGraph(Graph* graph);
private:
    // call deselection if needed
    void deselectIfNeeded();
    // each graph has his own undostack
    map<Graph*, stack<ToolAction> > _undoStacks;
    ToolState* _state;
    // this state needs special care
    SelectAndMoveTool* _selectionState;
    Graph* _graph;
};

#endif // TOOLHANDLER_H
