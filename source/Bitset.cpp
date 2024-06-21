#pragma once
#include "Bitset.h"
#include <iostream>
#include <fstream>

void Bitset::free()
{
	delete[] buckets;
	maxNum = 0;
	bits = 0;
	bucketsCount = 0;
}

void Bitset::copyFrom(const Bitset& other)
{
	maxNum = other.maxNum;
	bits = other.bits;
	bucketsCount = other.bucketsCount;
	buckets = new uint8_t[bucketsCount];

	for (size_t i = 0; i < bucketsCount; i++)
		buckets[i] = other.buckets[i];
}

void Bitset::setBitsCount(unsigned bitsCount)
{
	if (!(bitsCount >= Utility::MIN_BITS && bitsCount <= Utility::MAX_BITS))
		throw std::invalid_argument("The maximum bits must be in the interval [1,8]");
	this->bits = bitsCount;
}

void Bitset::setMaxNum(unsigned maxNum)
{
	this->maxNum = maxNum + 1; // plus one because of zero
}

void Bitset::setBucketsCount()
{
	unsigned totalBits = maxNum * bits;

	bucketsCount = (totalBits % Utility::MAX_BITS) ? (totalBits / Utility::MAX_BITS) + 1 :
		(totalBits / Utility::MAX_BITS);
}

unsigned Bitset::getNumIndex(unsigned num) const
{
	return (num * bits);
}

Bitset::Bitset(unsigned maxNum, unsigned bitsCount)
{
	setBitsCount(bitsCount);
	setMaxNum(maxNum);
	setBucketsCount();

	buckets = new uint8_t[bucketsCount];

	for (size_t i = 0; i < bucketsCount; i++)
		buckets[i] = 0;
}

Bitset::Bitset(const Bitset& other)
{
	copyFrom(other);
}

Bitset& Bitset::operator=(const Bitset& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Bitset::~Bitset()
{
	free();
}

void Bitset::add(unsigned index, unsigned value)
{
	if (index > maxNum)
		throw std::invalid_argument("The number must be smaller than the max number!");

	uint8_t count = countNum(index);
	if (count == Utility::powerOfTwo(bits) - 1)
		throw std::overflow_error("The bucket is full");

	count = value;
	unsigned numIndex = getNumIndex(index);
	for (size_t i = numIndex, j = bits - 1; i < (numIndex + bits); i++)
	{
		unsigned bucketIndex = i / Utility::MAX_BITS;
		unsigned bitIndex = i % Utility::MAX_BITS;

		if (Utility::checkBit(count, j--))
			Utility::makeBitOne(buckets[bucketIndex], bitIndex);
		else
			Utility::makeBitZero(buckets[bucketIndex], bitIndex);
	}
}

uint8_t Bitset::countNum(unsigned num) const
{
	if (num > maxNum)
		throw std::invalid_argument("The number must be smaller than the max number!");

	unsigned numIndex = getNumIndex(num);
	uint8_t res = 0;
	for (size_t i = numIndex, j = bits - 1; i < (numIndex + bits); i++)
	{
		unsigned bucketIndex = i / Utility::MAX_BITS;
		unsigned bitIndex = i % Utility::MAX_BITS;

		if (Utility::checkBit(buckets[bucketIndex], bitIndex))
			Utility::makeBitOne(res, j--);
		else
			Utility::makeBitZero(res, j--);
	}
	return res;
}
