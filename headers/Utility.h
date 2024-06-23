#pragma once
#include <iostream>

namespace Utility
{
	constexpr char PROMPT = '> ';
	constexpr char COMMENT_SYMBOL = '#';
	constexpr char SPACE_SYMBOL = ' ';
	constexpr char NULL_TERMINATED = '\0';
	constexpr size_t BUFFER = 1024;

	//Directions to rotate
	constexpr bool RIGHT = true;
	constexpr bool LEFT = false;

	//Colours
	constexpr uint8_t COLOUR_COUNT = 3;
	constexpr uint8_t PBM_WHITE = 0;
	constexpr uint8_t PBM_DARK = 1;

	constexpr uint8_t PBM_MAX_COLOUR = 1;
	constexpr uint8_t PGM_MAX_COLOUR = 16;
	constexpr uint8_t PPM_MAX_COLOUR = 255;

	//Transformations from pixMap to grayMap
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
	constexpr char SYMBOL_FOR_MAGIC_NUMBER = 'P';

	constexpr unsigned DEFAULT_CAPACITY = 8;
	constexpr unsigned DEFAULT_SIZE = 0;

	//Bitset
	constexpr uint8_t MIN_BITS = 1;
	constexpr uint8_t MAX_BITS = 8;
	constexpr unsigned BITS_IN_BYTE = 8;

	int convertToNum(char ch);

	unsigned findBitsCount(unsigned num);
	bool getBit(uint8_t num, unsigned pos);
	void setBit(uint8_t& num, unsigned pos, bool value);
	unsigned nextPowerOfTwo(unsigned n);
}