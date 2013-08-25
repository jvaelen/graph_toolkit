#include "bitvector.h"
#include <assert.h>
#include <bitset>
#include <iostream>
#include <QDebug>

BitVector::BitVector(unsigned number)
{
    // we only take the last 3 bytes
    unsigned mask = 1;
    for(unsigned i = 0; i < 18; ++i)
    {
        _list.push_back(mask & number);
        mask <<= 1;
    }
}

BitVector::BitVector()
{
    // default constructor
}

void BitVector::appendByte(char value, unsigned size)
{
    // use a temp list of bools which always gets the bits pushed at the front, at the end we push temp list behind what we already have
    list<bool> temp;
    unsigned mask = 1;
    for(unsigned i = 0; i < size; ++i)
    {
        temp.push_front(mask & value);
        mask <<= 1;
    }
    for(list<bool>::iterator i = temp.begin(); i != temp.end(); ++i)
        _list.push_back(*i);
}

void BitVector::appendBit(bool value)
{
    _list.push_back(value);
}

void BitVector::prependbit(bool value)
{
    _list.push_front(value);
}

void BitVector::padR(unsigned multipleOf, bool padWith)
{
    while(_list.size() % multipleOf != 0)
        _list.push_back(padWith);
}

void BitVector::unPadR(unsigned multipleOf)
{
    while(_list.size() % multipleOf != 0)
        _list.pop_back();
}

void BitVector::padL(unsigned multipleOf)
{
    while(_list.size() % multipleOf != 0)
        _list.push_front(0);
}
char BitVector::getIntBit(unsigned index, unsigned length) const
{
    // index and length must be inbounds
    assert(index + length <= _list.size());
    // length can only be a maximum of 8 (1 byte)
    assert(length < 8);
    // this is the variable that will hold the bits selected by the user
    char result = 0; // 00000000
    // we will bitshift the mask so that we can add the right bits to the result
    char mask = 1;
    // iterator that points to the right place in the list
    list<bool>::const_iterator it = _list.begin();
    // put the iterator where index points to
    while(index > 0)
    {
        ++it;
        --index;
    }
    unsigned tempLength = length;
    while(tempLength > 1)
    {
        ++it;
        tempLength--;
    }
    while (length > 0)
    {
        if (*it)
            result |= mask;
        mask <<= 1;
        // decrease the length
        --length;
        it--;
    }
    return result;
}

void BitVector::setReadMode()
{
    // clear any previous bits in the bitvector
    _readVector.clear();
    // reserve the size so we don't have to resize the vector after each push_back
    _readVector.reserve(_list.size());
    for (list<bool>::const_iterator it = _list.begin(); it != _list.end(); ++it)
    {
        _readVector.push_back(*it);
    }
}

bool BitVector::bitAt(unsigned index) const
{
    // small assert that is not completly error proof but this condition NEEDS to be true otherwise setReadMode defenitly been called!
    assert(_readVector.size() == _list.size());
    return _readVector[index];
}

// friend
QDebug operator<<(QDebug dbg, const BitVector& other)
{
    unsigned int counter = 0;
    for(list<bool>::const_iterator i = other._list.begin(); i != other._list.end(); ++i)
    {
        if(counter % 6 == 0)
            dbg.nospace() << " ";
        dbg.nospace() <<  (*i ? 1 : 0);
        counter ++;
    }
    return dbg.space();
}
