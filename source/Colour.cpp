#include "Colour.h"

void Colour::setRed(unsigned red)
{
	this->red = red;
}

void Colour::setGreen(unsigned green)
{
	this->green = green;
}

void Colour::setBlue(unsigned blue)
{
	this->blue = blue;
}

unsigned Colour::getRed() const
{
	return red;
}

unsigned Colour::getGreen() const
{
	return green;
}

unsigned Colour::getBlue() const
{
	return blue;
}
