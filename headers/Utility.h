#pragma once
#include <iostream>

namespace Utility
{

	constexpr char COMMENT_SYMBOL = '#';
	constexpr size_t BUFFER = 1024;
	constexpr uint8_t SPACE_SYMBOL = 32;

	//Colours
	constexpr uint8_t COLOUR_COUNT = 3;
	constexpr double RED_TO_GRAY = 0.2126;
	constexpr double GREEN_TO_GRAY = 0.7152;
	constexpr double BLUE_TO_GRAY = 0.0722;

	//'Magic numbers'
	constexpr uint8_t DEFAULT_MAGIC_NUMBER = 0;
	constexpr uint8_t PBM_PLAIN = 1;
	constexpr uint8_t PGM_PLAIN = 2;
	constexpr uint8_t PPM_PLAIN = 3;
	constexpr uint8_t PBM_RAW = 4;	
	constexpr uint8_t PGM_RAW = 5;
	constexpr uint8_t PPM_RAW = 6;

	//Bitset
	constexpr uint8_t MIN_BITS = 1;
	constexpr uint8_t MAX_BITS = 8;

	bool checkBit(unsigned num, unsigned index);
	void makeBitZero(uint8_t& num, unsigned index);
	void makeBitOne(uint8_t& num, unsigned index);
	unsigned powerOfTwo(size_t power);
	unsigned findBitsCount(unsigned num);

	int convertToNum(char ch);
}