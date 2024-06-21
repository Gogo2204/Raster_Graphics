#pragma once
#include "Image.h"

class PixMap : public Image
{
public:
	PixMap() = default;
	PixMap(const MyString& fileName, unsigned magicNumber, Vector <MyString>& comments,
		unsigned width, unsigned height, unsigned maxColour, Vector<Vector<Colour>>& data);

	Image* clone() const override;

	unsigned getMaxColour() const;
	const Vector<Vector<Colour>>& getData() const;

private:
	unsigned maxColour = 0;
	Vector<Vector<Colour>> data;
};