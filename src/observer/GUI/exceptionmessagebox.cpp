/*
 Author: Balazs Nemeth
 Description: Whenever an exception is caught and needs to be displayed to the user, the constructor is called with the excpetion
    */
#include "exceptionmessagebox.h"

ExceptionMessageBox::ExceptionMessageBox(const BaseEx &ex, QWidget *parent)
{
    _parent = parent;
    _priority = ex.getPriority();
    _message = QString::fromStdString(ex.getMessage());
    handleEx();
}

void ExceptionMessageBox::handleEx()
{
    // the switch desides what icon to display when displaying the messagebox
    switch (_priority)
    {
        case 0:
            QMessageBox::critical(_parent, "Critical error!", _message);
            break;
        case 1:
            QMessageBox::warning(_parent, "Warning", _message);
            break;
        case 2:
            QMessageBox::warning(_parent, "Warning", _message);
            break;
        case 3:
            QMessageBox::critical(_parent, "Critical error!", _message);
            break;
        default:
            QMessageBox::critical(_parent, "Fatal error occurred", _message);
    }
}
