#include <exception>
#include "Monochrome.h"

Monochrome::Monochrome(Vector<Polymorphic_Ptr<Image>>& images) : Commands(images) {}

void Monochrome::execute()
{
	for (size_t i = 0; i < images.getSize(); i++)
	{
		unsigned magicNumber = images[i]->getMagicNumber();
		switch (magicNumber)
		{
		case Utility::PBM_PLAIN:
		case Utility::PBM_RAW:
			break;
		case Utility::PGM_PLAIN:
		case Utility::PGM_RAW:
			images[i] = fromGrayToBitMap(i);
			break;
		case Utility::PPM_PLAIN:
		case Utility::PPM_RAW:
			images[i] = fromPixToBitMap(i);
			break;
		default:
			throw std::exception("Can’t find the right magic number!");
			break;
		}
	}
}

Commands* Monochrome::clone() const
{
	return new Monochrome(*this);
}

BitMap* Monochrome::fromGrayToBitMap(size_t index)
{
	GrayMap* grayMap = (GrayMap*)images[index].get();

	Vector<Bitset> bitMapData;
	Vector<Bitset> grayMapData = grayMap->getData();

	for (size_t i = 0; i < grayMap->getHeight(); i++)
	{
		Bitset bitMapRow(grayMap->getWidth(), Utility::MIN_BITS);
		for (size_t j = 0; j < grayMap->getWidth(); j++)
		{
			if (grayMapData[i].getNumber(j) <= (grayMap->getMaxColour() / 2))
			{
				bitMapRow.setNumber(j, Utility::PBM_DARK);
			}
			else
			{
				bitMapRow.setNumber(j, Utility::PBM_WHITE);
			}
		}
		bitMapData.push_back(bitMapRow);
	}

	Vector<MyString> comments = grayMap->getComments();

	return new BitMap(grayMap->getFileName(), grayMap->getMagicNumber(), comments, grayMap->getWidth(),
		grayMap->getHeight(), bitMapData);
}

BitMap* Monochrome::fromPixToBitMap(size_t index)
{
	PixMap* pixMap = (PixMap*)images[index].get();

	Vector<Bitset> bitMapData;
	Vector<Vector<Colour>> pixMapData = pixMap->getData();

	unsigned pixMapMaxColour = pixMap->getMaxColour();

	for (size_t i = 0; i < pixMap->getWidth(); i++)
	{
		Bitset bitMapRow(pixMap->getWidth(), Utility::MIN_BITS);
		for (size_t j = 0; j < pixMap->getHeight(); j++)
		{
			Colour colour = pixMapData[i][j];
			int temp = Utility::RED_TO_GRAY * colour.getRed() + Utility::GREEN_TO_GRAY * colour.getGreen()
				+ Utility::BLUE_TO_GRAY * colour.getBlue();

			if (temp <= pixMapMaxColour / 2)
			{
				bitMapRow.setNumber(j, Utility::PBM_DARK);
			}
			else
			{
				bitMapRow.setNumber(j, Utility::PBM_WHITE);
			}
		}
		bitMapData.push_back(bitMapRow);
	}

	Vector<MyString> comments = pixMap->getComments();

	return new BitMap(pixMap->getFileName(), pixMap->getMagicNumber(), comments, pixMap->getWidth(),
		pixMap->getHeight(), bitMapData);
}