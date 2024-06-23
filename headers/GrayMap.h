#pragma once
#include "Image.h"

class GrayMap : public Image
{
public:
	GrayMap() = default;
	GrayMap(const MyString& fileName, unsigned magicNumber, Vector<MyString>& comments,
		unsigned width, unsigned height, unsigned maxColour, Vector<Bitset>& data);

	Image* clone() const override;

	unsigned getMaxColour() const;
	const Vector<Bitset>& getData() const;

	void rotate(bool direction) override;
	void save(const MyString& newFileName) const override;

private:
	unsigned maxColour = 0;
	Vector<Bitset> data;

	void rotateLeft();
	void rotateRight();
};