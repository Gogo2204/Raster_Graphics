#include "Grayscale.h"

Grayscale::Grayscale(Vector <Polymorphic_Ptr<Image>>& images) : Commands(images) {}

void Grayscale::execute()
{
	for (size_t i = 0; i < images.getSize(); i++)
	{
		unsigned magicNumber = images[i]->getMagicNumber();
		if (magicNumber == Utility::PPM_PLAIN || magicNumber == Utility::PPM_RAW)
			images[i] = turnToGrayMap(i);
	}
}

MyString Grayscale::message() const
{
	return MyString("grayscale");
}

Commands* Grayscale::clone() const
{
	return new Grayscale(*this);
}

GrayMap* Grayscale::turnToGrayMap(size_t index)
{
	PixMap *pixMap = (PixMap*)images[index].get();

	Vector<Bitset> grayMapData;
	Vector<Vector<Colour>> pixMapData = pixMap->getData();

	for (size_t i = 0; i < pixMap->getHeight(); i++)
	{
		Bitset row(pixMap->getWidth(), pixMap->getMaxColour());
		for (size_t j = 0; j < pixMap->getWidth(); j++)
		{
			Colour colour = pixMapData[i][j];
			int temp = Utility::RED_TO_GRAY * colour.getRed() + Utility::GREEN_TO_GRAY * colour.getGreen()
				+ Utility::BLUE_TO_GRAY * colour.getBlue();
			row.setNumber(j, temp);
		}
		grayMapData.push_back(row);
	}

	Vector<MyString> comments = pixMap->getComments();
	unsigned newMagicNumber = pixMap->getMagicNumber() == Utility::PPM_PLAIN ? Utility::PGM_PLAIN : Utility::PGM_RAW;

	return new GrayMap(pixMap->getFileName(), newMagicNumber, comments, pixMap->getWidth(),
		pixMap->getHeight(), pixMap->getMaxColour(), grayMapData);
}