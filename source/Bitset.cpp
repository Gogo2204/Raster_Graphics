#include "BitSet.h"


Bitset::Bitset(unsigned maxNumber, unsigned bits) : bitsPerNumber(bits)
{
	if (bits < Utility::MIN_BITS || bits > Utility::MAX_BITS)
		throw std::logic_error("invalid bit count");

	size = maxNumber;
	capacity = (size + 1) * bits; // 0
	if (capacity % Utility::BITS_IN_BYTE)
		capacity += Utility::BITS_IN_BYTE - capacity % Utility::BITS_IN_BYTE;

	container = new uint8_t[capacity / Utility::BITS_IN_BYTE]{};
}

Bitset::Bitset(const Bitset& other)
{
	copyFrom(other);
}

Bitset::Bitset(Bitset&& other) noexcept
{
	moveFrom(std::move(other));
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

Bitset& Bitset::operator=(Bitset&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Bitset::~Bitset()
{
	free();
}

unsigned Bitset::getMaxNumber() const
{
	return size;
}

unsigned Bitset::getNumber(unsigned number) const
{
	if (number > size)
		throw std::out_of_range("set does not contain the number");

	unsigned idx = number * bitsPerNumber;
	unsigned ret = 0;

	for (unsigned i = 0; i < bitsPerNumber; i++, idx++)
	{
		ret <<= 1;
		ret += Utility::getBit(container[idx / Utility::BITS_IN_BYTE], idx % Utility::BITS_IN_BYTE);
	}

	return ret;
}

void Bitset::setNumber(unsigned number, unsigned value)
{
	if (number > size)
		throw std::out_of_range("set does not contain the number");

	unsigned idx = (number + 1) * bitsPerNumber - 1;//0

	for (unsigned i = 0; i < bitsPerNumber; i++, idx--)
	{
		Utility::setBit(container[idx / Utility::BITS_IN_BYTE], idx % Utility::BITS_IN_BYTE, Utility::getBit(value, i));
	}
}

void Bitset::free()
{
	delete[] container;
	size = 0;
	capacity = 0;
}

void Bitset::copyFrom(const Bitset& other)
{
	capacity = other.capacity;
	size = other.size;
	bitsPerNumber = other.bitsPerNumber;
	container = new uint8_t[capacity / Utility::BITS_IN_BYTE]{};

	for (unsigned i = 0; i <= size; i++)
	{
		setNumber(i, other.getNumber(i));
	}
}

void Bitset::moveFrom(Bitset&& other) noexcept
{
	capacity = other.capacity;
	other.capacity = 0;

	size = other.size;
	other.size = 0;

	container = other.container;
	other.container = nullptr;
}