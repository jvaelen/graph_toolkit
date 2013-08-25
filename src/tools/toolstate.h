/*
 Author: Balazs Nemeth
 Description: this is the abstract class from which actual tools are deriven from,
              it has a protected member _actions that makes the actions undoable
     */

#ifndef TOOLSTATE_H
#define TOOLSTATE_H

#include "toolparameters.h"
#include "graph/graph.h"
#include "tools/toolaction.h"
#include <map>

// the tooltype is used to know from outside what parameters have to be set before running execute
enum ToolType{ADDNODETOOL, ADDEDGETOOL, REMOVENODETOOL, REMOVEEDGETOOL, SELECTTOOL};

// wee need to tell the toolstate what prototypemanager it is in so that the tool can ask for an instance of the inverse tool (to create the undo action)
class ToolPM;
class ToolHandler;

class ToolState
{
public:
    /* when the tool is created, a human readable title should be given, NOT for
        typechecking (it musn't be unique) but to show the user the name of the tool*/
    ToolState(const string& title, const string& toolTip = "", const string& iconPath = "");
    void setGraph(Graph* graph) { _graph = graph; }
    // the toolparameters are passed to the toolstates, each state uses their own parameters, these are collected in ToolParameters
    virtual void execute(const ToolParameters& toolParameters, ToolHandler* context = NULL) = 0;
    // using this function will prevent the action from being undoable, this is used in cases where an action is actually undone
    virtual void executeNoActionSave(const ToolParameters& toolParameters) = 0;
    string getIconPath() const {return _iconPath;}
    string getTitle() const {return _title;}
    string getToolTip() const {return _toolTip;}
    // returns a pointer to the graph that is worked on
    Graph* getGraph() const {return _graph;}
    /* undo action, this function undoes the last action that this tool has executed,
        it will return a non NULL value if the last action was a change of the tool*/
    // see the important note above
    virtual ToolType getToolType() const = 0;
    // returns the oposite tool, if the function isn't reimplemented the oposite tool is the tool itself
    virtual ToolType getInverseToolType() {return getToolType();}
    void setPrototypeManger(ToolPM* toolPM) {_toolPM = toolPM;}
protected:
    /* the iconpath is set when the tool is created, this can (optionally) be used to tell the user where the icon is for the user
       a more obvious way to use this is when the gui develooper would want to show an icon that goes with the tool*/
    string _iconPath;
    // the title of the tool can be shown to the user in a command line interface or a GUI
    string _title;
    // same goes for the tooltip
    string _toolTip;
    // the graph that the tool will work on
    Graph* _graph;
    // the toolpm is needed so that the inverse tool can be asked for
    ToolPM* _toolPM;
};

#endif // TOOLSTATE_H
