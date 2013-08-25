/*
 Author: Balazs Nemeth
 Description: this widget represents the new graph window that the user gets to see when he wants to create a new graph,
              it gives the possibility to enter a name for the graph and set the starting structure, mind that this class isn't an observer, it just sends commands to GraphToolKit
     */

#ifndef NEWGRAPHWINDOW_H
#define NEWGRAPHWINDOW_H


#include <QWidget>
#include <QDialog>
#include <QString>
#include <QLineEdit>

// needed for the enumerationtype
#include "graphtoolkit.h"

// foreward declare as much as possible to reduce recompile time
class QGridLayout;
class QWidget;
class QLabel;
class QSpacerItem;
class QHBoxLayout;
class QPushButton;
class QLineEdit;
class QRadioButton;

// the newgraphwindo is just a qdialog and accept() tells the GraphToolKitWindow class that the graph can be created
class NewGraphWindow : public QDialog
{
    Q_OBJECT
public:
    explicit NewGraphWindow(QWidget* parent = 0);
    // this functions is overriden so that the focus can be set just before the window is shown
    void show();
    ~NewGraphWindow();
    // returns the name of the new graph to be created
    QString getGraphName() const {return _newGraphNameText->text();}
    // this function returns the id of the type of the graph that is chosen to be created. the id is calculated by checking which radiobutton is selected
    GraphType getChosenGraphID();
    // sets the default name for the graph appending with a counter integer
    void setDefaultNameCounter(unsigned counter);
private:
   // help functions used to keep the construction of the widgets organized
    void createLabels();
    void createRadioButtons();
    void createButtons();
    // the main layout that the widget uses to align all the childwidgets
    QGridLayout* _mainLayout;
    QLabel* _newGraphNameLabel;
    QLineEdit* _newGraphNameText;
    QLabel* _newGraphTypeLabel;
    QRadioButton* _hybridRadioButton;
    QRadioButton* _ListRadioButton;
    QRadioButton* _MatrixRadioButton;
    QHBoxLayout* _buttonLayout;
    QPushButton* _createButton;
    QPushButton* _cancelButton;
};

#endif // NEWGRAPHWINDOW_H
