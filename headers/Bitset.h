#pragma once
#include <iostream>
#include "Utility.h";

class Bitset
{
private:
	uint8_t* buckets = nullptr;
	unsigned maxNum = 0;
	unsigned bits = 0;

	size_t bucketsCount = 0;

	void free();
	void copyFrom(const Bitset& other);

	void setBitsCount(unsigned bitsCount);
	void setMaxNum(unsigned maxNum);
	void setBucketsCount();

	unsigned getNumIndex(unsigned num) const;
public:
	Bitset() = default;
	Bitset(unsigned maxNum, unsigned bitsCount);
	Bitset(const Bitset& other);
	Bitset& operator=(const Bitset& other);
	~Bitset();

	void add(unsigned index, unsigned value);
	uint8_t countNum(unsigned num) const;
};
