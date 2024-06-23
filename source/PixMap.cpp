#include <fstream>
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
    if (direction)
        rotateRight();
    else
        rotateLeft();
}

void PixMap::save(const MyString& newFileName) const
{
    if (magicNumber == Utility::PPM_PLAIN)
        savePlain(newFileName);
    else if (magicNumber == Utility::PPM_RAW)
        saveRaw(newFileName);
}

void PixMap::rotateLeft()
{
    Vector<Vector<Colour>> newData;

    for (size_t j = width; j > 0; --j)
    {     
        for (size_t i = 0; i < height; i++)
        {
            newData[j][i] = data[i][j - 1];
        }      
    }

    data = newData;
    std::swap(width, height);
}

void PixMap::rotateRight()
{
    Vector<Vector<Colour>> newData;

    for (size_t j = 0; j < width; j++)
    {      
        for (size_t i = 0; i < height; i++)
        {
            newData[j][i] = data[height - 1 - i][j];           
        }        
    }

    data = newData;
    std::swap(width, height);
}

void PixMap::savePlain(const MyString& newFileName) const
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
            ofs << data[i][j].getRed() << " " << data[i][j].getGreen() << " " << data[i][j].getBlue() << std::endl;
        }        
    }

    ofs.close();
}

void PixMap::saveRaw(const MyString& newFileName) const
{}