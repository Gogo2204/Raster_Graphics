#pragma once
#include <iostream>
#include "Utility.h"

class Bitset
{
public:
	Bitset() = default;
	Bitset(unsigned maxNumber, unsigned bits);
	Bitset(const Bitset& other);
	Bitset(Bitset&& other)noexcept;
	Bitset& operator=(const Bitset& other);
	Bitset& operator=(Bitset&& other)noexcept;
	~Bitset();

	unsigned getMaxNumber()const;

	unsigned getNumber(unsigned number)const;
	void setNumber(unsigned number, unsigned value);

private:

	void free();
	void copyFrom(const Bitset& other);
	void moveFrom(Bitset&& other)noexcept;

	uint8_t* container = nullptr;
	unsigned size = 0;
	unsigned capacity = 0;
	unsigned bitsPerNumber = Utility::MIN_BITS;
};