#include "Grayscale.h"
#include "PixMap.h"
#include "GrayMap.h"

Grayscale::Grayscale(Vector < Polymorphic_Ptr<Image> >& images) : Commands(images) {}

void Grayscale::execute()
{
	for (size_t i = 0; i < images.getSize(); i++)
	{
		unsigned magicNumber = images[i]->getMagicNumber();
		if (magicNumber == Utility::PPM_PLAIN || magicNumber == Utility::PPM_RAW)
			turnToGrayMap(i);
	}
}

Commands* Grayscale::clone() const
{
	return new Grayscale(*this);
}

GrayMap* Grayscale::turnToGrayMap(size_t index)
{
	PixMap *pixMap = (PixMap*) images[index].get();

	Vector<Bitset> grayMapData;

	for (size_t i = 0; i < pixMap->getHeight(); i++)
	{
		Bitset row(pixMap->getWidth(), pixMap->getMaxColour());
		for (size_t j = 0; j < pixMap->getWidth(); j++)
		{
			Colour colour = pixMap->getData()[i][j];
			int temp = Utility::RED_TO_GRAY * colour.getRed() + Utility::GREEN_TO_GRAY * colour.getGreen()
				+ Utility::BLUE_TO_GRAY * colour.getBlue();
			row.add(j, temp);
		}
		grayMapData.push_back(row);
	}

	return new GrayMap(pixMap->getFileName(), pixMap->getMagicNumber(), pixMap->getComments(), pixMap->getWidth(), pixMap->getHeight(), pixMap->getMaxColour(), grayMapData);

}
