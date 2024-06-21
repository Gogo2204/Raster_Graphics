#pragma once
#include "Image.h"

class BitMap : public Image
{
public:
	BitMap() = default;
	BitMap(const MyString& fileName, unsigned magicNumber, Vector<MyString>& comments,
		unsigned width, unsigned height, Vector<Bitset>& data);

	Image* clone() const override;
};
