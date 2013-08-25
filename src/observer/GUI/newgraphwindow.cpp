#include <QRadioButton>
#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QDebug>
#include <assert.h>

#include "newgraphwindow.h"

NewGraphWindow::NewGraphWindow(QWidget *parent) : QDialog(parent)
{
    _mainLayout = new QGridLayout(this);

    createLabels();
    createRadioButtons();
    createButtons();
    _newGraphNameText = new QLineEdit("New Graph", this);

    _mainLayout->addWidget(_newGraphNameLabel, 0, 0);
    _mainLayout->addWidget(_newGraphNameText, 0, 1);
    _mainLayout->addWidget(_newGraphTypeLabel, 1, 0);
    _mainLayout->addWidget(_hybridRadioButton, 1, 1);
    _mainLayout->addWidget(_ListRadioButton, 2, 1);
    _mainLayout->addWidget(_MatrixRadioButton, 3, 1);
    _mainLayout->addWidget(_cancelButton, 4, 0);
    _mainLayout->addWidget(_createButton, 4, 1);
    // cosmetic stuff
    setWindowTitle("Create a new graph");
    setFixedSize(sizeHint());
}

NewGraphWindow::~NewGraphWindow()
{
    delete _newGraphTypeLabel;
    delete _newGraphNameLabel;

    delete _newGraphNameText;
    delete _hybridRadioButton;
    delete _ListRadioButton;
    delete _MatrixRadioButton;
    delete _mainLayout;
}

void NewGraphWindow::setDefaultNameCounter(unsigned counter)
{
    _newGraphNameText->setText(QString("New Graph ") + QString::number(counter));
}

void NewGraphWindow::show()
{
    _newGraphNameText->setFocus(Qt::OtherFocusReason);
    QDialog::show();
}

void NewGraphWindow::createButtons()
{
    // allocate the appropeate memory
    _createButton = new QPushButton("Create", this);
    _cancelButton = new QPushButton("Cancel", this);
    // link signals and slots
    connect(_createButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(hide()));
}

void NewGraphWindow::createLabels()
{
    _newGraphNameLabel = new QLabel("Graph Name: ", this);
    _newGraphTypeLabel = new QLabel("Graph Type: ", this);
}

GraphType NewGraphWindow::getChosenGraphID()
{
    GraphType chosenGraphID;
    if (_hybridRadioButton->isChecked())
        chosenGraphID = HYBRID;
    else if(_ListRadioButton->isChecked())
        chosenGraphID = LIST;
    else if (_MatrixRadioButton->isChecked())
        chosenGraphID = MATRIX;
    else
        chosenGraphID = INVALIDGRAPHTYPE; // this should never happen

    assert(chosenGraphID != INVALIDGRAPHTYPE);
    return chosenGraphID;
}

void NewGraphWindow::createRadioButtons()
{
    // radio buttons that belong to the same parent widget behave as if they were part of the same exclusive button group.
    _hybridRadioButton = new QRadioButton("Hybrid Graph", this);
    _hybridRadioButton->setChecked(true);
    _ListRadioButton = new QRadioButton("List Graph", this);
    _MatrixRadioButton = new QRadioButton("Matrix Graph", this);
}
