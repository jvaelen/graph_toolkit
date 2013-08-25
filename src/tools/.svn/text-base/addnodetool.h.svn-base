/*
 Author: Balazs Nemeth
 Description: this class represents an add node tool that can be used to add nodes to a graph,
              it also keeps track of all the previous actions making them undoable.
     */

#ifndef ADDNODETOOL_H
#define ADDNODETOOL_H

#include "toolstate.h"
#include <string>
#include "graph/graphComp/point.h"

using namespace std;

class AddNodeTool : public ToolState
{
public:
    AddNodeTool(const string& title, const string& toolTip, const string& iconPath);
    void execute(const ToolParameters &toolParameters, ToolHandler* context = NULL);
    void executeNoActionSave(const ToolParameters& toolParameters);
    ToolType getToolType() const { return ADDNODETOOL;}
    ToolType getInverseToolType() const { return REMOVENODETOOL;}
private:
    // helpfunction to create the inverse action
    ToolAction createInverseAction();
    Label _label;
    Point _coord;
};

#endif // ADDNODETOOL_H
