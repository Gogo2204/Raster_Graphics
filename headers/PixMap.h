#pragma once
#include "Image.h"

class PixMap : public Image
{
public:
	PixMap() = default;
	PixMap(const MyString& fileName, unsigned magicNumber, Vector<MyString>& comments,
		unsigned width, unsigned height, unsigned maxColour, Vector<Bitset>& data);

	Image* clone() const override;

private:
	unsigned maxColour = 0;
};
