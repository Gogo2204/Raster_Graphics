#include "Image.h"

Image::Image(const MyString& fileName, unsigned magicNumber, Vector<MyString>& comments,
	unsigned width, unsigned height)
{
	this->fileName = fileName;
	this->magicNumber = magicNumber;
	this->comments = comments;
	this->width = width;
	this->height = height;
}

const MyString& Image::getFileName() const
{
	return fileName;
}

unsigned Image::getMagicNumber() const
{
	return magicNumber;
}

unsigned Image::getWidth() const
{
	return width;
}

unsigned Image::getHeight() const
{
	return height;
}

const Vector<MyString>& Image::getComments() const
{
	return comments;
}