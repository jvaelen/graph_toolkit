#include <QGridLayout>
#include <QColorDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

#include "settingswindow.h"


SettingsWindow::SettingsWindow(QWidget *parent) : QDialog(parent), _fillColor(255,255,255)
{
    setFixedWidth(400);
    _colorDialog = new QColorDialog(this);
    _gridLayout = new QGridLayout(this);
    _fillColorLabel = new QLabel("node fill color");
    _timerLabel = new QLabel("Change timer interval: ");
    _timerInterval = new QLineEdit("400");
    _changeFillColor = new QPushButton(this);
    _changeFillColor->setText(QString::fromStdString(_fillColor.toString()));
    _accept = new QPushButton("Accept");
    _gridLayout->setColumnMinimumWidth(0, 200);
    _gridLayout->addWidget(_fillColorLabel, 0, 0);
    _gridLayout->addWidget(_changeFillColor, 0, 1);
    _gridLayout->addWidget(_timerLabel, 1,0);
    _gridLayout->addWidget(_timerInterval, 1, 1);
    _gridLayout->addWidget(_accept, 3, 0, 2, 0);
    connect(_changeFillColor, SIGNAL(clicked()), this, SLOT(showAndHandleColorDialog()));
    connect(_accept, SIGNAL(clicked()), this, SLOT(accept()));
}

unsigned SettingsWindow::getMsecs()
{
    return _timerInterval->text().toInt();
}

void SettingsWindow::showAndHandleColorDialog()
{
    _colorDialog->setCurrentColor(QColor(_fillColor.getRed(), _fillColor.getGreen(), _fillColor.getBlue()));
    _colorDialog->show();
    if (_colorDialog->exec() == QDialog::Accepted)
    {
        _fillColor.setRed(_colorDialog->currentColor().red());
        _fillColor.setGreen(_colorDialog->currentColor().green());
        _fillColor.setBlue(_colorDialog->currentColor().blue());
        _changeFillColor->setText(QString::fromStdString(_fillColor.toString()));
    }
}

SettingsWindow::~SettingsWindow()
{
    delete _gridLayout;
}
