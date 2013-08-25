/*
 Author: Balazs Nemeth
 Description: this class represents an action that is executed by a specific tool,
              basicly it encapsulates the state, the graph that the action is executed on and the tool that is used for the action.
              by using this class we can save the opsit actions of the user, an example is when the user deletes a node, an oposit action is saved
              that adds that node back again. This allows undoable actions and expands the capabilities of the application even furthur!
              it can also represent a change of a tool
     */
#ifndef TOOLACTION_H
#define TOOLACTION_H

// we need to include the parameters here because we need them in a list
#include "tools/toolparameters.h"
#include <list>

using namespace std;

class Graph;
class ToolState;

class ToolAction
{
public:
    // creates an empty tool action
    ToolAction();
    // when toolState is the only variable being set, we know that only a change of a tool is what this action is
    ToolAction(ToolState* toolState);
    // the toolaction can also be created instaniously with the membervariables,
    ToolAction(ToolState* toolState, Graph* graph, ToolParameters toolParameters);
    // getter and setter for the graph
    void setGraph(Graph* graph) {_graph = graph;}
    Graph* getGraph() const {return _graph;}
    ToolState* getFirstTool() { return _toolStates.front();}
    // returns true if this action is only a tool change action
    bool isChangetoolAction() {return (_toolParameters.empty());}
    // this function makes it possible to expand the action by combining more actions into one (this comes in handy especially when a node and edges are deleted in one user action
    void addExtraAction(ToolState* toolState, ToolParameters toolParameters);
    // returns the toolparameters for the last subaction
    ToolParameters getLastToolParameter() const { return _toolParameters.back();}
    /* convenience function that call the executeNoActionSave function of the tool with the
       graph and with the toolParameters, also resets the graph to what it was if it were different*/
    void execute();
private:
    // the graph that the action is executed on
    Graph* _graph;
    // the tool that is used to execute the action, this is a list because some actions are actually more actions (removing nodes may also remove edges)
    list<ToolState*> _toolStates;
    // the parameters that the tool needs to complete the action
    list<ToolParameters> _toolParameters;
};

#endif // TOOLACTION_H
