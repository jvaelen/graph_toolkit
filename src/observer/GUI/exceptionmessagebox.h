/*
 Author: Balazs Nemeth
 Description: This class gets an exception from the model and displays the proper messagebox with the right text and icon
     */

#ifndef EXCEPTIONMESSAGEBOX_H
#define EXCEPTIONMESSAGEBOX_H

#include <QMessageBox>
#include <QWidget>
#include "exception/baseex.h"

class ExceptionMessageBox
{
public:
    ExceptionMessageBox(const BaseEx& ex, QWidget* parent = 0);

private:
    // handle the exception, chose a messageboxicon and display it with the proper text
    void handleEx();
    QString _message;
    unsigned _priority;
    QWidget* _parent;
};

#endif // EXCEPTIONMESSAGEBOX_H
