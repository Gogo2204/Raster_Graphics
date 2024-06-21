#include <iostream>
#include "GrayMap.h"

GrayMap::GrayMap(const MyString& fileName, unsigned magicNumber, Vector<MyString>& comments, 
	unsigned width, unsigned height, unsigned maxColour, Vector<Bitset>& data)
{
    this->fileName = fileName;
    this->magicNumber = magicNumber;
    this->comments = comments;
    this->width = width;
    this->height = height;
    this->maxColour = maxColour;
    this->data = data;
}

Image* GrayMap::clone() const
{
	return new GrayMap(*this);
}
