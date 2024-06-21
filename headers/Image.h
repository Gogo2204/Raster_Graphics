#pragma once
#include "Utility.h"
#include "Vector.hpp"
#include "MyString.h"
#include "Bitset.h"

class Image
{
public:
	virtual Image* clone() const = 0;
	virtual ~Image() = default;

protected:
	MyString fileName;
	unsigned magicNumber = Utility::DEFAULT_MAGIC_NUMBER;
	unsigned height = 0;
	unsigned width = 0;
	Vector<MyString> comments;
	Vector<Bitset> data;
};
