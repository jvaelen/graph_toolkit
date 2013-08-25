/*
 Author: Balazs Nemeth
 Description: this class represents an add edge tool that can be used to add edges to a graph,
              it also keeps track of all the previous actions making them undoable.
     */
#ifndef ADDEDGETOOL_H
#define ADDEDGETOOL_H

#include "toolstate.h"

class AddEdgeTool : public ToolState
{
public:
    AddEdgeTool(const string& title, const string& toolTip = "", const string& iconPath = "");
    void execute(const ToolParameters& toolParameters, ToolHandler* context = NULL);
    void executeNoActionSave(const ToolParameters& toolParameters);
    ToolType getToolType() const { return ADDEDGETOOL;}
    ToolType getInverseToolType() const { return REMOVEEDGETOOL;}
    ToolState* getLastStateChange() const;
private:
    // helpfunction to create the inverse action
    ToolAction createInverseAction(const ToolParameters &toolParameters);
};

#endif // ADDEDGETOOL_H
