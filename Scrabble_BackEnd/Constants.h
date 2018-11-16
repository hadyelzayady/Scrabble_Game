#pragma once
constexpr auto ROWS_COUNT = 15;
constexpr auto COLUMNS_COUNT = 15;
constexpr auto TOTAL_TILE_COUNT = 100;
constexpr auto RACK_SIZE = 7;
constexpr auto BLANK_TILE = '_';
constexpr auto EMPTY_SQUARE = '\0';
constexpr auto EXCEPTION_OUT_OF_BOUND = "array out of bound (Board-> isEmpty)";

const unsigned int bitPosistion[27] = {
	1 ,
	1 << 1,
	1 << 2,
	1 << 3,
	1 << 4,
	1 << 5,
	1 << 6,
	1 << 7,
	1 << 8,
	1 << 9,
	1 << 10,
	1 << 11,
	1 << 12,
	1 << 13,
	1 << 14,
	1 << 15,
	1 << 16,
	1 << 17,
	1 << 18,
	1 << 19,
	1 << 20,
	1 << 21,
	1 << 22,
	1 << 23,
	1 << 24,
	1 << 25,
	1 << 26,
};

const unsigned int comulativeBitPosistion[27] = {
	0,
	1 ,
	3 ,
	7 ,
	15 ,
	31 ,
	63 ,
	127 ,
	255 ,
	511 ,
	1023 ,
	2047 ,
	4095 ,
	8191 ,
	16383  ,
	32767  ,
	65535  ,
	131071   ,
	262143  ,
	524287  ,
	1048575  ,
	2097151  ,
	4194303  ,
	8388607  ,
	16777215  ,
	33554431  ,
	67108863  ,
};

const char mapping[27] =
{
	'A',
	'B',
	'C',
	'D',
	'E',
	'F',
	'G',
	'H',
	'I',
	'J',
	'K',
	'L',
	'M',
	'N',
	'O',
	'P',
	'Q',
	'R',
	'S',
	'T',
	'U',
	'V',
	'W',
	'X',
	'Y',
	'Z',
	'['
};