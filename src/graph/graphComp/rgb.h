/*
 Author: Balazs Nemeth
 Description: This class is used to keep the color of node,
this property of the node is used mostly for graphcoloring but also nodes can have a color is this way
     */

#ifndef RGB_H
#define RGB_H

#include <QDebug>
#include <string>

using namespace std;

class RGB
{
public:
    // default constructor constructs a black color
    RGB();
    RGB(const RGB& other);
    // construct a color using these rgb values
    RGB(unsigned char red, unsigned char green, unsigned char blue);
    // used to set the red green and blue values at the same time
    RGB& operator=(const RGB& other);
    // can be used to easely get a brighter version of a color
    RGB operator-(const RGB& other) const;
    bool operator==(const RGB& other) const;
    bool operator!=(const RGB& other) const;
    // getters and setters for the individual colors
    void setRed(const unsigned char red) {_red = red;}
    void setGreen(const unsigned char green) {_green = green;}
    void setBlue(const unsigned char blue) {_blue = blue;}
    unsigned char getRed() const {return _red;}
    unsigned char getGreen() const {return _green;}
    unsigned char getBlue() const {return _blue;}

    // returns a rgb object set with values to represent the color
    static RGB colorRed() { return RGB(255,0,0); }
    static RGB colorBlue() { return RGB(0,0,255); }
    static RGB colorBlack() { return RGB(0,0,0); }
    static RGB colorOrange() { return RGB(255, 140, 0); }
    static RGB colorGreen() {return RGB(0, 255, 0); }
    static RGB colorWhite() {return RGB(255, 255, 255); }
    static RGB colorHoverSelection() {return RGB(0, 125, 255);}

    // the next static functions define the colorlayout of the application, these colors are predefined
    static RGB colorSelection() {return RGB::colorBlue();}
    static RGB colorDefault() {return RGB::colorBlack();}
    static RGB colorDelete() {return RGB::colorRed();}
    string toString() const;

    // friends
    friend QDebug operator<<(QDebug dbg, const RGB& other);
private:
    unsigned char _red;
    unsigned char _green;
    unsigned char _blue;
};

#endif // RGB_H
