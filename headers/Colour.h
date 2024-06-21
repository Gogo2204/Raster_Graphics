#pragma once

class Colour
{
public:
	void setRed(unsigned red);
	void setGreen(unsigned green);
	void setBlue(unsigned blue);

	unsigned getRed() const;
	unsigned getGreen() const;
	unsigned getBlue() const;

private:
	unsigned red = 0;
	unsigned green = 0;
	unsigned blue = 0;

};