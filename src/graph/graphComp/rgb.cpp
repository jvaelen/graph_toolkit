#include <sstream>

#include "rgb.h"

RGB::RGB()
{
    // default color is black
    _red = 0;
    _green = 0;
    _blue = 0;
}

RGB::RGB(const RGB& other)
{
    _red   = other._red;
    _blue  = other._blue;
    _green = other._green;
}

RGB::RGB(unsigned char red, unsigned char green, unsigned char blue)
{
    _red = red;
    _green = green;
    _blue = blue;
}

RGB& RGB::operator=(const RGB& other)
{
    _red   = other._red;
    _blue  = other._blue;
    _green = other._green;
    return *this;
}

RGB RGB::operator-(const RGB& other) const
{
    RGB color;
    if (_red < other._red)
        color.setRed(0);
    else
        color.setRed(_red - other._red);

    if (_green < other._green)
        color.setGreen(0);
    else
        color.setGreen(_green - other._green);

    if (_blue < other._blue)
        color.setBlue(0);
    else
        color.setBlue(_blue - other._blue);
    return color;
}

bool RGB::operator!=(const RGB& other) const
{
    return (_red != other._red || _green != other._green || _blue != other._blue);
}

bool RGB::operator==(const RGB& other) const
{
    return (_red == other._red && _green == other._green && _blue == other._blue);
}

string RGB::toString() const
{
    stringstream tempStream;
    tempStream <<  "(" << (int)_red << "," <<  (int)_green << ", " << (int)_blue << ")";
    return tempStream.str();
}

// friends
QDebug operator<<(QDebug dbg, const RGB& other)
{
    dbg.nospace() << QString::fromStdString(other.toString());
    return dbg.space();
}
