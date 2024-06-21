#pragma once
#include "Utility.h"
#include "Vector.hpp"
#include "MyString.h"
#include "Bitset.h"
#include "Colour.h"

class Image
{
public:
	Image(const MyString& fileName, unsigned magicNumber, Vector<MyString>& comments,
		unsigned width, unsigned height);

	virtual Image* clone() const = 0;
	virtual ~Image() = default;

	const MyString& getFileName() const;
	unsigned getMagicNumber() const;
	unsigned getWidth() const;
	unsigned getHeight() const;
	const Vector<MyString>& getComments() const;

protected:
	MyString fileName;
	unsigned magicNumber = Utility::DEFAULT_MAGIC_NUMBER;
	unsigned height = 0;
	unsigned width = 0;
	Vector<MyString> comments;
};