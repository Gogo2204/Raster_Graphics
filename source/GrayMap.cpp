#include <iostream>
#include "GrayMap.h"

GrayMap::GrayMap(const MyString& fileName, unsigned magicNumber, Vector<MyString>& comments, 
	unsigned width, unsigned height, unsigned maxColour, Vector<Bitset>& data) : Image(fileName, magicNumber, comments, width, height)
{
	this->maxColour = maxColour;
    this->data = data;
}

Image* GrayMap::clone() const
{
	return new GrayMap(*this);
}

const Vector<Bitset>& GrayMap::getData() const
{
	return data;
}