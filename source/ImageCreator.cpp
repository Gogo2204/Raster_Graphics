#include <iostream>
#include <fstream>
#include <exception>
#include "ImageCreator.h"

Image* ImageCreator::readImageFile(const MyString& fileName)
{
	std::ifstream ifs(fileName.c_str());

	if (!ifs.is_open())
		throw std::exception("Can’t load the image!");

	MyString strMagicNumber;
	ifs >> strMagicNumber;

	ifs.close();

	unsigned magicNumber = Utility::convertToNum(strMagicNumber[1]); // there is 'P' on possition 0

	Image* img = nullptr;

	switch (magicNumber) 
	{
	case Utility::PBM_PLAIN:
		img = readBitMap(fileName);
		break;
	case Utility::PGM_PLAIN:
		img = readGrayMap(fileName);
		break;
	case Utility::PPM_PLAIN:
		img = readPixMap(fileName);
		break;
	case Utility::PBM_RAW:
		img = readBitMapBinary(fileName);
		break;
	case Utility::PGM_RAW:
		img = readGrayMapBinary(fileName);
		break;
	case Utility::PPM_RAW:
		img = readPixMapBinary(fileName);
		break;
	default:
		throw std::logic_error("The image is not in proper format!");
		break;
	}

	return img;
}

Image* ImageCreator::readBitMap(const MyString& fileName)
{
	std::ifstream ifs(fileName.c_str());

	if (!ifs.is_open())
		throw std::exception("Can not load the image!");

	char temp1[Utility::BUFFER];
	ifs.getline(temp1, Utility::BUFFER);

	MyString strMagicNumber(temp1);

	unsigned magicNumber = Utility::convertToNum(strMagicNumber[1]);

	Vector<MyString> comments = readComments(ifs);

	unsigned width = 0;
	unsigned height = 0;

	ifs >> width;
	ifs >> height;

	Vector<Bitset> data;

	for (size_t i = 0; i < height; i++)
	{
		Bitset row(width, Utility::MIN_BITS);
		for (size_t j = 0; j < width; j++)
		{
			unsigned temp;
			ifs >> temp;
			if (temp != Utility::PBM_DARK && temp != Utility::PBM_WHITE)
				j--;
			else 
				row.setNumber(j, temp);
		}
		data.push_back(row);
	}

	ifs.close();

	return new BitMap(fileName, magicNumber, comments, width, height, data);
}

Image* ImageCreator::readGrayMap(const MyString& fileName)
{
	std::ifstream ifs(fileName.c_str());

	if (!ifs.is_open())
		throw std::exception("Can not load the image!");

	char temp1[Utility::BUFFER];
	ifs.getline(temp1, Utility::BUFFER);

	MyString strMagicNumber(temp1);

	unsigned magicNumber = Utility::convertToNum(strMagicNumber[1]);

	Vector<MyString> comments = readComments(ifs);

	unsigned width = 0;
	unsigned height = 0;
	unsigned maxColour = 0;

	ifs >> width;
	ifs >> height;
	ifs >> maxColour;

	Vector<Bitset> data;

	for (size_t i = 0; i < height; i++)
	{
		Bitset row(width, Utility::findBitsCount(maxColour));
		for (size_t j = 0; j < width; j++)
		{
			unsigned temp = 0;
			ifs >> temp;
			if (temp <= maxColour)
				row.setNumber(j, temp);
		}
		data.push_back(row);
	}

	ifs.close();

	return new GrayMap(fileName, magicNumber, comments, width, height, maxColour, data);
}

Image* ImageCreator::readPixMap(const MyString& fileName)
{
	std::ifstream ifs(fileName.c_str());

	if (!ifs.is_open())
		throw std::exception("Can not load the image!");

	char temp1[Utility::BUFFER];
	ifs.getline(temp1, Utility::BUFFER);

	MyString strMagicNumber(temp1);

	unsigned magicNumber = Utility::convertToNum(strMagicNumber[1]);

	Vector<MyString> comments = readComments(ifs);

	unsigned width = 0;
	unsigned height = 0;
	unsigned maxColour = 0;

	ifs >> width;
	ifs >> height;
	ifs >> maxColour;

	Vector<Vector<Colour>> data;

	for (size_t i = 0; i < height; i++)
	{
		Vector<Colour> row;
		
		for (size_t j = 0; j < width; j++)
		{
			Colour colour;
			unsigned temp = 0;

			ifs >> temp;
			colour.setRed(temp);
			ifs >> temp;
			colour.setGreen(temp);
			ifs >> temp;
			colour.setBlue(temp);

			row.push_back(colour);
		}
		data.push_back(row);
	}
	
	ifs.close();

	return new PixMap(fileName, magicNumber, comments, width, height, maxColour, data);
}

Image* ImageCreator::readBitMapBinary(const MyString& fileName)
{
	return nullptr;
}

Image* ImageCreator::readGrayMapBinary(const MyString& fileName)
{
	return nullptr;
}

Image* ImageCreator::readPixMapBinary(const MyString& fileName)
{
	return nullptr;
}

Vector<MyString> ImageCreator::readComments(std::ifstream& ifs)
{
	Vector<MyString> comments;

	MyString row;
	char temp[Utility::BUFFER];

	int getPointer = ifs.tellg();
	ifs.getline(temp, Utility::BUFFER);
	row = temp;

	while (row[0] == Utility::COMMENT_SYMBOL)
	{
		comments.push_back(row);
		getPointer = ifs.tellg();
		ifs.getline(temp, Utility::BUFFER);
		row = temp;
	}
	ifs.seekg(getPointer);
	
	return comments;
}