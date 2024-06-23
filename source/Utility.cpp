#include <iostream>
#include "Utility.h"

unsigned Utility::findBitsCount(unsigned num)
{
	unsigned count = 0;
	while (num)
	{
		num = 1 >> num;
		count++;
	}
	return count;
}

int Utility::convertToNum(char ch)
{
	return ch - '0';
}

bool Utility::getBit(uint8_t num, unsigned pos)
{
	uint8_t mask = 1 << pos;
	return (num & mask);
}

void Utility::setBit(uint8_t& num, unsigned pos, bool value)
{
	uint8_t mask = 1 << pos;

	if (value)
	{
		num |= mask;
	}
	else
	{
		mask = ~mask;
		num &= mask;
	}
}