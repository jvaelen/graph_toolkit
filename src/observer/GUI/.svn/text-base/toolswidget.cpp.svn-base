#include <QButtonGroup>
#include <QToolButton>
#include <QAction>
#include <QList>
#include <assert.h>

#include "toolswidget.h"
#include "tools/toolhandler.h"
#include "tools/addedgetool.h"
#include "tools/addnodetool.h"
#include "tools/removeedgetool.h"
#include "tools/removenodetool.h"
#include "tools/selectandmovetool.h"

ToolsWidget::ToolsWidget(QWidget *parent) : QToolBar(parent)
{
    _toolHandler = NULL;
    _buttonGroup = NULL;
    _beforeLock = 0;
    // the constructor does nothing for now
}

void ToolsWidget::lockTools()
{
    for (int i = 0; i < _actions.size(); ++i)
    {
        if (_actions[i]->isChecked())
            _beforeLock = i;
        _actions[i]->setEnabled(false);
    }
    _actions[0]->setChecked(true);
    setToolState();
}

void ToolsWidget::unlockTools()
{
    for (int i = 0; i < _actions.size(); ++i)
        _actions[i]->setEnabled(true);
    _actions[_beforeLock]->setChecked(true);
    setToolState();
}

void ToolsWidget::init(const list<ToolState *>& toolSet)
{
    // remove everything that could have been created before
    // first when initting the toolswidget, all the tools are copied from the parameter into a QVector
    _toolSet.clear();
    _toolSet.reserve(toolSet.size());
    for (list<ToolState *>::const_iterator i = toolSet.begin(); i != toolSet.end(); ++i)
        _toolSet.push_back(*i);
    cleanActionsAndButtons();
    // after that the set of tools has been set, the appropriate actions are created, these actions are immediatly linked with the right slots
    createActionsAndButtons();
}

void ToolsWidget::cleanActionsAndButtons()
{
    // if we have already created some actions, these have to be removed when this function is called
    if (!_actions.empty())
    {
        for (int i = 0; i < _actions.size(); ++i)
        {
            delete _toolButtons[i];
            delete _actions[i];
        }
        _toolButtons.clear();
        _actions.clear();
        delete _buttonGroup;
    }
}

void ToolsWidget::createActionsAndButtons()
{
    // create and add the buttons
    _buttonGroup = new QButtonGroup(this);
    for (int i = 0; i < _toolSet.size(); ++i)
    {
        _actions.push_back(new QAction(this));
        _toolButtons.push_back(new QToolButton(this));
        _toolButtons.last()->setDefaultAction(_actions.last());
        // add the button to the layout
        addWidget(_toolButtons.last());
        // adds the button to the group so that only one can be checked at the same time
        _buttonGroup->addButton(_toolButtons.last());
        setupAction(_actions.last(), _toolSet[i]);
    }
}

void ToolsWidget::setToolState()
{
    int index = -1;
    bool found = false;
    for (int i = 0; !found && i < _toolButtons.size(); ++i)
        if (_toolButtons[i]->isChecked())
        {
            found = true;
            index = i;
        }
    assert(index != -1);
    // sets the toolstate to the state that the action is linked to
    _toolSet[index]->setGraph(_toolHandler->getToolState()->getGraph());
    _toolHandler->setState(_toolSet[index]);
}

void ToolsWidget::setupAction(QAction *action, ToolState* state)
{
    // sets the action to be checkable
    action->setCheckable(true);
    // sets informative stuff for the user to see
    action->setIcon(QIcon(QString::fromStdString(state->getIconPath())));
    action->setToolTip(QString::fromStdString(state->getToolTip()));
    action->setText(QString::fromStdString(state->getTitle()));
    // connect the signal
    connect(action, SIGNAL(triggered()), this, SLOT(setToolState()));
}

void ToolsWidget::notify(Subject *subject)
{
    // if the toolhandler hasn't been set, set it and create the actions that are linked with the toolset in GraphToolKit class
    if (!_toolHandler)
    {
        _toolHandler = (ToolHandler*)subject;
        // create the actions that go with the tool
    }
    // if the toolhandler does have a state
    if (_toolHandler->getToolState())
    {
        // find that action that should be checked
        for (int i = 0; i < _toolSet.size(); ++i)
            if (_toolSet[i] == _toolHandler->getToolState())
                _actions[i]->setChecked(true); // show it visualy
    }
}

ToolsWidget::~ToolsWidget()
{
    // toolset is a copy of the tools created in GraphToolKit and thus have to be cleared there
    // on the other hand, the actions and toolbuttons have to be cleared
    cleanActionsAndButtons();
}


