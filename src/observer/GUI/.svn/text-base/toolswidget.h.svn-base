/*
 Author: Balazs Nemeth
 Description: This is the toolbar that represents all the tools available for editing a graph
     */

#ifndef TOOLSWIDGET_H
#define TOOLSWIDGET_H

#include <QToolBar>
#include <QList>
#include "observer/observer.h"
#include <vector>

using namespace std;

class QToolButton;
class QButtonGroup;
class QAction;
class ToolState;
class ToolHandler;

const int NUMBEROFTOOLS = 5;

class ToolsWidget : public QToolBar, public Observer
{
    Q_OBJECT
public:
    explicit ToolsWidget(QWidget *parent = 0);
    ~ToolsWidget();
    // returns the actions so that it can be linked to other gui elements, this is purely for displaying perpouse
    void createActionsAndButtons();
    // does the inverse of what createActionsAndButtons does
    void cleanActionsAndButtons();
    // when the GUI is created and the working toolset is known, the init function is used to set the tools and create the appropeate actions
    void init(const list<ToolState*>& toolSet);
    QList<QAction*> getActions() const {return _actions;}
    /* the toolswidget is notifed once at the beginning and every time the user changes the tool,
        this may look like overkill but it should be possible to change the tool and still update the GUI without user intervention*/
    void notify(Subject *subject);
    void lockTools();
    void unlockTools();
signals:

private slots:
    // changes the actual state of the tool
    void setToolState();
private:
    void createActions();
    // help function that sets the right layout for the buttons
    void setupAction(QAction* action, ToolState* state);
     // define an enumeration for readability
    enum toolButtons {SELECT, ADDNODE, ADDEDGE, REMOVENODE, REMOVEEDGE};
    // QButtonGroup used to group together the tools
    // all the tools available to the user, each tool has it's own button
    QList<QToolButton*> _toolButtons;
    // toolset keeps an instance of all the possible tools
    QVector<ToolState*> _toolSet;
    // each toolbutton has an assosiated action with it
    QList<QAction*> _actions;
    QButtonGroup* _buttonGroup;
    // to keep track of what is being observed the _toolHandler variable has to be set
    ToolHandler* _toolHandler;
    int _beforeLock;
};

#endif // TOOLSWIDGET_H
