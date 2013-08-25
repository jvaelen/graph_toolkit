#include "toolpm.h"
#include "selectandmovetool.h"
#include "algorithm"
#include <assert.h>

ToolPM::ToolPM()
{

}

ToolPM::~ToolPM()
{
    clear();
}

void ToolPM::addTool(ToolState* newTool)
{
    // the hash is given by the tools type
    _tools.push_back(newTool);
    // we also tell the tools that they are in this prototypemanager, this way they can ask for the instance of the oposite tool
    newTool->setPrototypeManger(this);
}

void ToolPM::clear()
{
    for (list<ToolState*>::iterator i = _tools.begin(); i != _tools.end(); ++i)
        delete *i;
    _tools.clear();
}

void ToolPM::deselectAll(Graph *graph)
{
    // find the tool that is a select and movetool and tell it do deselect the graph
    for (list<ToolState*>::iterator i = _tools.begin(); i != _tools.end(); ++i)
        if((*i)->getToolType() == SELECTTOOL)
        {
            dynamic_cast<SelectAndMoveTool*>((*i))->deselectAll(graph);
            return ;
        }
}

ToolState* ToolPM::getTool(ToolType toolType)
{
    ToolState* tool = NULL;
    bool found = false;
    for (list<ToolState*>::iterator i = _tools.begin();!found && i != _tools.end(); ++i)
        if ((found = ((*i)->getToolType() == toolType)))
            tool = *i;
    // should never be left NULL
    assert(tool);

    return tool;
}
