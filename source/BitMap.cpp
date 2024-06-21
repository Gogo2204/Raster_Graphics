#include <iostream>
#include "Bitmap.h"

BitMap::BitMap(const MyString& fileName, unsigned magicNumber, Vector<MyString>& comments, 
    unsigned width, unsigned height, Vector<Bitset>& data)
{
    this->fileName = fileName;
    this->magicNumber = magicNumber;
    this->comments = comments;
    this->width = width;
    this->height = height;
    this->data = data;
}

Image* BitMap::clone() const
{
    return new BitMap(*this);
}
