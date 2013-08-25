/*
 Author: Balazs Nemeth
 Description: this class represents a remove node tool that can be used to remove nodes from a graph,
              it also keeps track of all the previous actions making them undoable.
     */

#ifndef REMOVENODETOOL_H
#define REMOVENODETOOL_H

#include "toolstate.h"

class RemoveNodeTool : public ToolState
{
public:
    RemoveNodeTool(const string& title, const string& toolTip, const string& iconPath);
    void execute(const ToolParameters &toolParameters, ToolHandler* context = NULL);
    void executeNoActionSave(const ToolParameters& toolParameters);
    ToolType getToolType() const { return REMOVENODETOOL;}
    ToolType getInverseToolType() const { return ADDNODETOOL;}
private:
    // this function is a helpfunction that adds all the edges to the ToolAction, the nodepointer tells how to fix the edges for saving
    // if the excludeSelfEdges variable is set, then selfEdges won't be saved
    void saveEdges(ToolAction* toolAction, const list<Edge*>& edges, bool excludeSelfEdges);
    // helpfunction to create the inverse action
    ToolAction createInverseAction(const ToolParameters &toolParameters);
    Node* _node;
};

#endif // REMOVENODETOOL_H
