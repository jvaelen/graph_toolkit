/*
 Author: Balazs Nemeth
 Description: for each type of excpetion, another exception class is used to keep al the excpetiontypes seperatly
     */
#ifndef BASEEX_H
#define BASEEX_H

#include <string>

using namespace std;

class BaseEx
{
public:
    BaseEx();
    // constructor, this constructor also implies the default constructor
    BaseEx(const string& extraInfo, int priority = 0);
    // default destructor is good enough here.
    // getMessage is specified in the derived classes
    virtual string getMessage() const = 0;
    int getPriority() const {return _priority;}
    // change the priority, this should only very rarely, mind that the priority can also be overridden using the constructor
    void overridePriority(int priority);
    // extra information that may be usefull to guide the user
    void setExtraInfo(string extraInfo) {_extraInfo = extraInfo;}
protected:
    int _priority;
    string _extraInfo;
};

#endif // BASEEX_H
