/*
 Author: Balazs Nemeth
 Description: This widget is used as the main window for the graphtoolkit. It's the first window that the user gets to see.
     */

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include "graph/graphComp/rgb.h"

class QGridLayout;
class QColorDialog;
class QLabel;
class QLineEdit;

class SettingsWindow : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget *parent = 0);
    // destructor destructs everything that has been allocated in the constructor
    ~SettingsWindow();
    const RGB& getFillColor() const {return _fillColor;}
    unsigned getMsecs();
signals:

private slots:
    void showAndHandleColorDialog();
private:
    RGB _fillColor;
    QGridLayout* _gridLayout;
    QLabel* _fillColorLabel;
    QPushButton* _changeFillColor;
    QPushButton* _accept;
    QLineEdit* _timerInterval;
    // dialog that is shown when the user clicks change for the fillcolor settings
    QColorDialog* _colorDialog;
    QLabel* _timerLabel;
};

#endif // SETTINGSWINDOW_H
