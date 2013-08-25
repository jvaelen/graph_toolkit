/*
 Author: Balazs Nemeth
 Description: this class cis a prototypemanager that keeps instances of the tools,
              it also observes each graph and if that graph is being deleted, it will
              let the tools know that all the undoactions concerning the graph are not
              needed anymore
     */
#ifndef TOOLPM_H
#define TOOLPM_H

#include <map>
#include "toolstate.h"

using namespace std;
class Graph;

class ToolPM
{
public:
    ToolPM();
    // cleans up the prototypemanager
    ~ToolPM();
    // removes all the tools from the prototypmanager
    void clear();
    // add a tool to the prototypemanager;
    void addTool(ToolState* newTool);
    // returns a list with all the tools in, this is used to create the appropeate observers
    const list<ToolState*>& getTools() const {return _tools;}
    // the hash is actaully the tools type
    ToolState* getTool(ToolType toolType);
    ToolState* getReader(unsigned index) const;
    // deselects all selected nodes in the graph
    void deselectAll(Graph* graph);
private:
    // using a list instead of a map because the order matters
    list<ToolState*> _tools;
};

#endif // TOOLPM_H
