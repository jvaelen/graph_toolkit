/*
 Author: Jeroen Vaelen
 Description:
     */

#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <iostream>
#include <QDebug>

using namespace std;

class Label
{
public:
    Label() { }
    Label(int i);
    Label(const Label& other) { _labelString = other._labelString;}
    Label(string labelString) { _labelString = labelString; }
    string getLabelString() const { return _labelString; }
    void setLabelString(const string& labelString) { _labelString = labelString; }
    // check if the label is an integer (a number)
    bool isCost() const;
    // return the cost of the label
    // we gave label costs because nodes and edges both have labels and they can both have costs
    // that way we can, for example, get an edge e's cost with e.getLabel().getCost()
    int getCost() const;
    // same label?
    bool operator==(const Label& other) const;
    Label& operator=(const Label& other);
    bool isEmptyLabel() { return _labelString == ""; }
    // friends
    friend QDebug operator<<(QDebug dbg, const Label& other);
    friend ostream& operator<<(ostream& dbg, const Label& other);

private:
    string _labelString;

    // function used to calculate the integer of a string
    // like QString::toInt, you can pass a bool to see wether the conversion was a succes
    int toInt(bool& succes) const;
};

#endif // LABEL_H
