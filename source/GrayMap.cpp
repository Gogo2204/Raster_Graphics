#include <fstream>
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

unsigned GrayMap::getMaxColour() const
{
	return maxColour;
}

const Vector<Bitset>& GrayMap::getData() const
{
	return data;
}

void GrayMap::rotate(bool direction)
{
    if (direction)
        rotateRight();
    else
        rotateLeft();
}

void GrayMap::save(const MyString& newFileName) const
{
    if (magicNumber == Utility::PGM_PLAIN)
        savePlain(newFileName);
    else if (magicNumber == Utility::PGM_RAW)
        saveRaw(newFileName);
}

void GrayMap::rotateLeft()
{
    Vector<Bitset> newData;

    for (size_t j = width; j > 0; --j)
    {
        Bitset newRow(height, Utility::findBitsCount(maxColour));
        for (size_t i = 0; i < height; i++)
        {
            newRow.setNumber(i, data[i].getNumber(j - 1));
        }
        newData.push_back(newRow);
    }

    data = newData;
    std::swap(width, height);
}

void GrayMap::rotateRight()
{
    Vector<Bitset> newData;

    for (size_t j = 0; j < width; j++)
    {
        Bitset newRow(height, Utility::findBitsCount(maxColour));
        for (size_t i = 0; i < height; i++)
        {
            newRow.setNumber(i, data[height - 1 - i].getNumber(j));
        }
        newData.push_back(newRow);
    }

    data = newData;
    std::swap(width, height);
}

void GrayMap::savePlain(const MyString& newFileName) const
{
    std::ofstream ofs(newFileName.c_str());

    if (!ofs.is_open())
        throw std::exception("Can’t save the image!");

    ofs << Utility::SYMBOL_FOR_MAGIC_NUMBER << magicNumber << std::endl;

    for (size_t i = 0; i < comments.getSize(); i++)
    {
        ofs << comments[i] << std::endl;
    }

    ofs << width << " " << height << std::endl << maxColour << std::endl;

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            ofs << data[i].getNumber(j) << " ";
        }
        ofs << std::endl;
    }

    ofs.close();
}

void GrayMap::saveRaw(const MyString& newFileName) const
{
}