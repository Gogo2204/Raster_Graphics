#include <iostream>
#include "Bitmap.h"

BitMap::BitMap(const MyString& fileName, unsigned magicNumber, Vector<MyString>& comments, 
    unsigned width, unsigned height, Vector<Bitset>& data) : Image(fileName, magicNumber, comments, width, height)
{
    this->data = data;
}

Image* BitMap::clone() const
{
    return new BitMap(*this);
}

const Vector<Bitset>& BitMap::getData() const
{
    return data;
}
