/*
 Author: Balazs Nemeth
 Description: this class represents a selection tool that can be used to remove edges from a graph,
              the selection actions are saved so that the nodes can be unselected and restored to their original color
     */

#ifndef SELECTANDMOVETOOL_H
#define SELECTANDMOVETOOL_H

#include <stack>

#include "toolstate.h"
#include "observer/subject.h"

class SelectAndMoveTool : public ToolState, public Subject
{
public:
    SelectAndMoveTool(const string& title, const string& toolTip, const string& iconPath);
    void execute(const ToolParameters &toolParameters, ToolHandler* context = NULL);
    void executeNoActionSave(const ToolParameters& toolParameters);
    ToolType getToolType() const { return SELECTTOOL;}
    void deselectAll(Graph* graph);
    // the oposite tool is actually the tool itself, deselection is the same basicly the same action but with little differences
    // returns the last selected node or NULL if there is no selection
    GraphComp* getLastSelection(Graph* graph) const;
    GraphComp* getLastSelection() const;
private:
    // deselection without notifying the observers
    void silentDeselectAll(Graph* graph);
    // helpfunction to create the inverse action
    ToolAction createInverseAction(const ToolParameters &toolParameters);
    // keep all the selection so that deselection can be executed
    map<Graph*, stack<ToolAction> > _unselects;
};

#endif // SELECTANDMOVETOOL_H
