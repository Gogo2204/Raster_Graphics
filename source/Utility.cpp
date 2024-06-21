#include <iostream>
#include "Utility.h"

bool Utility::checkBit(unsigned num, unsigned index)
{
	unsigned mask = 1;
	mask <<= index;
	return (mask & num) == mask;
}

void Utility::makeBitZero(uint8_t& num, unsigned index)
{
	uint8_t mask = 1;
	mask <<= index;
	mask = ~mask;
	num &= mask;
}

void Utility::makeBitOne(uint8_t& num, unsigned index)
{
	uint8_t mask = 1;
	mask <<= index;
	num |= mask;
}

unsigned Utility::powerOfTwo(size_t power)
{
	return 1 << power;
}

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
