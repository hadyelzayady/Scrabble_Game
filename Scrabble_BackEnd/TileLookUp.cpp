#include "TileLookUp.h"



TileLookUp::TileLookUp()
{

	letterMap['A'].setValues(9, 1);
	letterMap['B'].setValues(2, 3);
	letterMap['C'].setValues(2, 3);
	letterMap['D'].setValues(4, 2);
	letterMap['E'].setValues(12, 1);
	letterMap['F'].setValues(2, 4);
	letterMap['G'].setValues(3, 2);
	letterMap['H'].setValues(2, 4);
	letterMap['I'].setValues(9, 1);
	letterMap['J'].setValues(1, 8);
	letterMap['K'].setValues(1, 5);
	letterMap['L'].setValues(4, 1);
	letterMap['M'].setValues(2, 3);
	letterMap['N'].setValues(6, 1);
	letterMap['O'].setValues(8, 1);
	letterMap['P'].setValues(2, 3);
	letterMap['Q'].setValues(1, 10);
	letterMap['R'].setValues(6, 1);
	letterMap['S'].setValues(4, 1);
	letterMap['T'].setValues(6, 1);
	letterMap['U'].setValues(4, 1);
	letterMap['V'].setValues(2, 4);
	letterMap['W'].setValues(2, 4);
	letterMap['X'].setValues(1, 8);
	letterMap['Y'].setValues(2, 4);
	letterMap['Z'].setValues(1, 10);
	letterMap[BLANK_TILE].setValues(2, 0);
}


TileLookUp::~TileLookUp()
{
}

int TileLookUp::getFrequency(char c)
{
	return letterMap.find(c)->second.frequency;
}

int TileLookUp::getScore(char c)
{
	return letterMap.find(c)->second.score;
}

void TileLookUp::setFrequency(char c,int f)
{
	letterMap.find(c)->second.frequency = f;
}


