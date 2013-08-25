#include <QGroupBox>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <assert.h>

#include "selectionobserverwidget.h"
#include "tools/selectandmovetool.h"

SelectionObserverWidget::SelectionObserverWidget(QWidget *parent) : QWidget(parent), Observer()
{
    _selectionAndMoveTool = NULL;
    _graphComp = NULL;
    _widgetLayout = new QGridLayout(this);
    _groupBox = new QGroupBox(this);
    _widgetLayout->addWidget(_groupBox, 0, 0);
    _groupBox->setTitle("Selected Component");
    // by setting the parent for the QGridLayout to be the groupbox, it is automatically aligned to it
    _groupBoxLayout = new QGridLayout(_groupBox);
    _nodeLabelQLabel = new QLabel("label: ");
    _componentLabelLineEdit = new QLineEdit(this);

    _positionQLabel = new QLabel("position: ", this);
    _coordsLabel = new QLabel(this);
    _groupBoxLayout->addWidget(_nodeLabelQLabel, 0,0);
    _groupBoxLayout->addWidget(_componentLabelLineEdit, 0, 1);
    _groupBoxLayout->addWidget(_positionQLabel, 1, 0);
    _groupBoxLayout->addWidget(_coordsLabel, 1, 1);
    connect(_componentLabelLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateNodeText(QString)));
    // set the width of the widget, this widget has a fixed with
    setEnabled(false);
}

void SelectionObserverWidget::updateNodeText(QString newNodeLabel)
{
    if (_graphComp)
        _graphComp->setLabel(newNodeLabel.toStdString());
}

SelectionObserverWidget::~SelectionObserverWidget()
{
    delete _nodeLabelQLabel;
    delete _positionQLabel;
    delete _coordsLabel;
    delete _componentLabelLineEdit;
    delete _groupBoxLayout;
    delete _groupBox;
    delete _widgetLayout;
}

void SelectionObserverWidget::updateLabels(GraphComp* graphComp)
{
    assert(graphComp);
    if (_componentLabelLineEdit->text().toStdString() != graphComp->getLabel().getLabelString())
        _componentLabelLineEdit->setText(QString::fromStdString(graphComp->getLabel().getLabelString()));
    Node* tempNode = dynamic_cast<Node*>(graphComp);
    Edge* tempEdge = dynamic_cast<Edge*>(graphComp);

    if (tempNode)
        _coordsLabel->setText(QString::fromStdString(tempNode->getCoords().toString()));
    else if (tempEdge)
        _coordsLabel->setText(QString::fromStdString(Point::median(tempEdge->getSource()->getCoords(),
                                                                   tempEdge->getTarget()->getCoords()).toString()));
}

void SelectionObserverWidget::clearLabels()
{
    _componentLabelLineEdit->setText("");
    _coordsLabel->setText("");
}

void SelectionObserverWidget::notify(Subject *subject)
{
    GraphComp* graphComp = NULL;
    // if the subject was a selectiontool
    if ((_selectionAndMoveTool = dynamic_cast<SelectAndMoveTool*>(subject)))
    {
        // update the display with information about the node
        graphComp = _selectionAndMoveTool->getLastSelection(_selectionAndMoveTool->getGraph());
        setEnabled(!!graphComp);
    }
    else if (dynamic_cast<Node*>(subject))// the subject should have been a node, otherwise deselection will happen
       graphComp = dynamic_cast<Node*>(subject);
    else if (dynamic_cast<Edge*>(subject))
        graphComp = dynamic_cast<Edge*>(subject);

    /* if a node notified the selectionobserver and it will be deleted, clean up and set _node to NULL
       mind that this can ONLY happen if a node is selected and deleted immediatly afterwards */
    if (graphComp && graphComp->getWillBeDeleted())
    {
        clearLabels();
        _graphComp = NULL;
        return ;
    }
    else if (graphComp)
    {
        if (_graphComp != graphComp)
        {
            // if a previously _node was set, first unregister
            if (_graphComp)
                _graphComp->unregisterObserver(this);

            _graphComp = graphComp;
            _graphComp->registerObserver(this);
        }
        updateLabels(_graphComp);
    }
    else
    {
        _graphComp = NULL;
        clearLabels();
    }
}
