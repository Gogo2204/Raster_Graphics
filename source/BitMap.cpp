#include <fstream>
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

void BitMap::rotate(bool direction)
{
    if (direction)
        rotateRight();
    else
        rotateLeft();
}

void BitMap::save(const MyString& newFileName) const
{
    if (magicNumber == Utility::PBM_PLAIN)
        savePlain(newFileName);
    else if(magicNumber == Utility::PBM_RAW)
        saveRaw(newFileName);
}

void BitMap::rotateLeft()
{
    Vector<Bitset> newData;

    for (size_t j = width; j > 0; --j)
    {
        Bitset newRow(height, Utility::MIN_BITS);
        for (size_t i = 0; i < height; i++)
        {
            newRow.setNumber(i, data[i].getNumber(j - 1));
        }
        newData.push_back(newRow);
    }

    data = newData;
    std::swap(width, height);
}

void BitMap::rotateRight()
{
    Vector<Bitset> newData;

    for (size_t j = 0; j < width; j++)
    {
        Bitset newRow(height, Utility::MIN_BITS);
        for (size_t i = 0; i < height; i++)
        {
            newRow.setNumber(i, data[height - 1 - i].getNumber(j));
        }
        newData.push_back(newRow);
    }

    data = newData;
    std::swap(width, height);
}

void BitMap::savePlain(const MyString& newFileName) const
{
    std::ofstream ofs(newFileName.c_str());

    if (!ofs.is_open())
        throw std::exception("Can’t save the image!");

    ofs << Utility::SYMBOL_FOR_MAGIC_NUMBER << magicNumber << std::endl;

    for (size_t i = 0; i < comments.getSize(); i++)
    {
        ofs << comments[i] << std::endl;
    }

    ofs << width << " " << height << std::endl;

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

void BitMap::saveRaw(const MyString& newFileName) const
{

}