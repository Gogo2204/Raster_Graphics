#pragma once
#include "Image.h"

class BitMap : public Image
{
public:
	BitMap() = default;
	BitMap(const MyString& fileName, unsigned magicNumber, Vector<MyString>& comments,
		unsigned width, unsigned height, Vector<Bitset>& data);

	Image* clone() const override;

	const Vector<Bitset>& getData() const;

	void rotate(bool direction) override;
	void save(const MyString& newFileName) const override;

private:
	Vector<Bitset> data;

	void rotateLeft();
	void rotateRight();

	void savePlain(const MyString& newFileName) const;
	void saveRaw(const MyString& newFileName) const;
};