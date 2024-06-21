#pragma once
#include "BitMap.h"
#include "GrayMap.h"
#include "PixMap.h"

class ImageCreator
{
public:
	static Image* readImageFile(const MyString& fileName);

private:
	static Vector<MyString> readComments(std::ifstream& ifs);

	static Image* readBitMap(const MyString& fileName);
	static Image* readGrayMap(const MyString& fileName);
	static Image* readPixMap(const MyString& fileName);
	static Image* readBitMapBinary(const MyString& fileName);
	static Image* readGrayMapBinary(const MyString& fileName);
	static Image* readPixMapBinary(const MyString& fileName);
};
