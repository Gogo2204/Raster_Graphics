#pragma once
#include "Image.h"

class GrayMap : public Image
{
public:
	GrayMap() = default;
	GrayMap(const MyString& fileName, unsigned magicNumber, Vector<MyString>& comments,
		unsigned width, unsigned height, unsigned maxColour, Vector<Bitset>& data);

	Image* clone() const override;

	const Vector<Bitset>& getData() const;

private:
	unsigned maxColour = 0;
	Vector<Bitset> data;
};