#include "PixMap.h"

PixMap::PixMap(const MyString& fileName, unsigned magicNumber, Vector <MyString>& comments,
    unsigned width, unsigned height, unsigned maxColour, Vector <Vector<Colour>>& data) : Image(fileName, magicNumber, comments, width, height)
{
    this->maxColour = maxColour;
    this->data = data;
}

Image* PixMap::clone() const
{
    return new PixMap(*this);
}

unsigned PixMap::getMaxColour() const
{
    return maxColour;
}

const Vector<Vector<Colour>>& PixMap::getData() const
{
    return data;
}

void PixMap::rotate(bool direction)
{
}

void PixMap::save(const MyString& newFileName) const
{
}

void PixMap::rotateLeft()
{
}

void PixMap::rotateRight()
{
}
