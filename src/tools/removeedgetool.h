/*
 Author: Balazs Nemeth
 Description: this class represents a remove edge tool that can be used to remove edges from a graph,
              it also keeps track of all the previous actions making them undoable.
     */
#ifndef REMOVEEDGETOOL_H
#define REMOVEEDGETOOL_H

#include "toolstate.h"

class RemoveEdgeTool : public ToolState
{
public:
    RemoveEdgeTool(const string& title, const string& toolTip, const string& iconPath);
    void execute(const ToolParameters &toolParameters, ToolHandler* context = NULL);
    void executeNoActionSave(const ToolParameters& toolParameters);
    ToolType getToolType() const { return REMOVEEDGETOOL;}
    ToolType getInverseToolType() const { return ADDEDGETOOL;}
private:
    // helpfunction to create the inverse action
    ToolAction createInverseAction(const ToolParameters &toolParameters);
    Node* _source;
    Node* _target;
    Label _label;
};

#endif // REMOVEEDGETOOL_H
