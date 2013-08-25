#ifndef TIMERCHANGER_H
#define TIMERCHANGER_H

#include <QWidget>

class QGroupBox;
class QPushButton;
class QGridLayout;
class QLineEdit;

class TimerChanger : public QWidget
{
    Q_OBJECT
public:
    explicit TimerChanger(QWidget *parent = 0);
    int getTimerInterval() const { return _timerVal; }

signals:

public slots:
    void changeTimerVal();
private:
    QGridLayout* _widgetLayout;
    QGridLayout* _groupBoxLayout;
    QGroupBox* _groupBox;
    QPushButton* _updateTimer;
    QLineEdit* _intervalField;
    int _timerVal;
};

#endif // TIMERCHANGER_H
