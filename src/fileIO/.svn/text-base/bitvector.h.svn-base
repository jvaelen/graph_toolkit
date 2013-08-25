/*
 Author: Balazs Nemeth
 Description: bitvector represents a vector bits, it's basicly a wrapper around std::vector but extends it's capabilities
     */

#ifndef BITVECTOR_H
#define BITVECTOR_H

// use stdlib, a better way would be to use bitfields
#include <list>
#include <QDebug>

using namespace std;

class BitVector
{
public:

    // constructs the bitvector from an unsigned integer
    BitVector(unsigned number);
    BitVector();

    /* converts the list into a vector for random acces, this function is called onces before reading is done.
       Normally the bitvector won't be used to read 1 bit, instead one will read more bits, by implementing this function
       we can take the advantage of the vector only when we read*/
    void setReadMode();
    // returns true if the bit at the index is true, else return false
    bool bitAt(unsigned index) const;
    // adds a bit at the and of the bitvector
    void appendBit(bool value);
    // adds a bit at the beginning of the bitvector
    void prependbit(bool value);
    // pads the bitvector by adding zero's or one's at the end so that the length of the bitvector is a multiple of unsigned multipleOf
    void padR(unsigned multipleOf = 6, bool padWith = false);
    // unpads (removes) bits from the end of the bitvector so that the length of the bitvector is a multiple of unsigned multipleOf
    void unPadR(unsigned multipleOf = 6);
    // pads the bitvector by adding zeros at the beginning so that the length of the bitvector is a multiple of unsigned multipleOf
    void padL(unsigned multipleOf = 6);
    // returns the size of the bitvector
    unsigned size() const {return _list.size();}
    /* returns and unsigned integer containing all the bits, if length is bigger
        than 8, an assertion is made, if length is ie 2 then the 2 bits are in the lowest order bits of the integer*/
    char getIntBit(unsigned index, unsigned length) const;
    // appends size number of bits of the byte "value"
    void appendByte(char value, unsigned size);
    // for debugging
    friend QDebug operator<<(QDebug dbg, const BitVector& other);
private:
    // use a list so we can pop_front, no random access is needed, alot of bits will be added so a list is the obvious choice here
    list<bool> _list;
    // is used when reading with bitAt;
    vector<bool> _readVector;
};

#endif // BITVECTOR_H
