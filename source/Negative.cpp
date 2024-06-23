#include "Negative.h"

Negative::Negative(Vector<Polymorphic_Ptr<Image>>& images) : Commands(images) {}

void Negative::execute()
{
	for (size_t i = 0; i < images.getSize(); i++)
	{
		unsigned magicNumber = images[i]->getMagicNumber();
		switch (magicNumber)
		{
		case Utility::PBM_PLAIN:
		case Utility::PBM_RAW:
			images[i] = negativeToBitMap(i);
			break;
		case Utility::PGM_PLAIN:
		case Utility::PGM_RAW:
			images[i] = negativeToGrayMap(i);
			break;
		case Utility::PPM_PLAIN:
		case Utility::PPM_RAW:
			images[i] = negativeToPixMap(i);
			break;
		default:
			throw std::exception("Can’t find the right magic number!");
			break;
		}
	}
}

Commands* Negative::clone() const
{
	return new Negative(*this);
}

BitMap* Negative::negativeToBitMap(unsigned index)
{
	BitMap* bitMap = (BitMap*)images[index].get();

	Vector<Bitset> oldBitMapData = bitMap->getData();
	Vector<Bitset> newBitMapData;

	for (size_t i = 0; i < bitMap->getHeight(); i++)
	{
		Bitset row(bitMap->getWidth(), Utility::MIN_BITS);
		for (size_t j = 0; j < bitMap->getWidth(); j++)
		{
			unsigned temp = Utility::PBM_MAX_COLOUR - oldBitMapData[i].getNumber(j);
			row.setNumber(j, temp);
		}
		newBitMapData.push_back(row);
	}

	Vector<MyString> comments = bitMap->getComments();

	return new BitMap(bitMap->getFileName(), bitMap->getMagicNumber(), comments, bitMap->getWidth(),
		bitMap->getHeight(), newBitMapData);
}

GrayMap* Negative::negativeToGrayMap(unsigned index)
{
	GrayMap* grayMap = (GrayMap*)images[index].get();
	
	Vector<Bitset> oldGrayMapData = grayMap->getData();
	Vector<Bitset> newGrayMapData;

	for (size_t i = 0; i < grayMap->getHeight(); i++)
	{
		Bitset row(grayMap->getWidth(), Utility::PGM_MAX_COLOUR);
		for (size_t j = 0; j < grayMap->getWidth(); j++)
		{
			unsigned temp = Utility::PGM_MAX_COLOUR - oldGrayMapData[i].getNumber(j);
			row.setNumber(j, temp);
		}
		newGrayMapData.push_back(row);
	}

	Vector<MyString> comments = grayMap->getComments();
	unsigned newMaxColour = Utility::PPM_MAX_COLOUR;

	return new GrayMap(grayMap->getFileName(), grayMap->getMagicNumber(), comments, grayMap->getWidth(), grayMap->getHeight(),
		newMaxColour, newGrayMapData);
}

PixMap* Negative::negativeToPixMap(unsigned index)
{
	PixMap* pixMap = (PixMap*)images[index].get();

	Vector<Vector<Colour>> oldPixMapData = pixMap->getData();
	Vector<Vector<Colour>> newPixMapData;

	for (size_t i = 0; i < pixMap->getHeight(); i++)
	{
		Vector<Colour> row;
		for (size_t j = 0; j < pixMap->getWidth(); j++)
		{
			Colour oldColour = oldPixMapData[i][j];
			Colour newColour;
			newColour.setRed(Utility::PPM_MAX_COLOUR - oldColour.getRed());
			newColour.setGreen(Utility::PPM_MAX_COLOUR - oldColour.getGreen());
			newColour.setBlue(Utility::PPM_MAX_COLOUR - oldColour.getBlue());
			row.push_back(newColour);
		}
		newPixMapData.push_back(row);
	}

	Vector<MyString> comments = pixMap->getComments();
	unsigned newMaxColour = Utility::PPM_MAX_COLOUR;

	return new PixMap(pixMap->getFileName(), pixMap->getMagicNumber(), comments, pixMap->getWidth(),
		pixMap->getHeight(), newMaxColour, newPixMapData);
}