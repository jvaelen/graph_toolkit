#include <sstream>

#include "label.h"

Label::Label(int i)
{
    stringstream tempStream;
    tempStream << i;
    _labelString = tempStream.str();
}

bool Label::isCost() const
{
    bool result;
    toInt(result);
    return result;
}

int Label::getCost() const
{
    bool dummy;
    if (isCost())
        return (toInt(dummy));
    else
        return 0;
}

bool Label::operator==(const Label& other) const
{
    return _labelString == other._labelString;
}

Label& Label::operator=(const Label& other)
{
    this->_labelString = other._labelString;
    return *this;
}

int Label::toInt(bool& succes) const
{
    bool stop = false;
    // distinguish "" string
    if (_labelString.size() == 0)
    {
        succes = false;
        return 0;
    }
    // run through string and check if all chars are integers
    for (int i = 0; i < (int)this->_labelString.size() && !stop; ++i)
    {
        if (this->_labelString[i] < '0' || this->_labelString[i] > '9')
        {
            succes = false;
            stop = true;
        }
    }
    // we did not have to stop -> string is an integer
    if (!stop)
    {
        succes = true;
        return atoi(this->_labelString.c_str());
    }
    // failure
    return 0;
}

// friend
QDebug operator<<(QDebug dbg, const Label& other)
{
    dbg.nospace() << other._labelString.c_str();
    return dbg.nospace();
}

ostream& operator<<(ostream& dbg, const Label& other)
{
    dbg << other._labelString;
    return dbg;
}


