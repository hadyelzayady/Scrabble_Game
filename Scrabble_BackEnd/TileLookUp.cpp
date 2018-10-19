#include "TileLookUp.h"



TileLookUp::TileLookUp()
{
	letterArray[0] = new Letter('A', 9, 1);
	letterArray[1] = new Letter('B', 2, 3);
	letterArray[2] = new Letter('C', 2, 3);
	letterArray[3] = new Letter('D', 4, 2);
	letterArray[4] = new Letter('E', 12, 1);
	letterArray[5] = new Letter('F', 2, 4);
	letterArray[6] = new Letter('G', 3, 2);
	letterArray[7] = new Letter('H', 2, 4);
	letterArray[8] = new Letter('I', 9, 1);
	letterArray[9] = new Letter('J', 1, 8);
	letterArray[10] = new Letter('K', 1, 5);
	letterArray[11] = new Letter('L', 4, 1);
	letterArray[12] = new Letter('M', 2, 3);
	letterArray[13] = new Letter('N', 6, 1);
	letterArray[14] = new Letter('O', 8, 1);
	letterArray[15] = new Letter('P', 2, 3);
	letterArray[16] = new Letter('Q', 1, 10);
	letterArray[17] = new Letter('R', 6, 1);
	letterArray[18] = new Letter('S', 4, 1);
	letterArray[19] = new Letter('T', 6, 1);
	letterArray[20] = new Letter('U', 4, 1);
	letterArray[21] = new Letter('V', 2, 4);
	letterArray[22] = new Letter('W', 2, 4);
	letterArray[23] = new Letter('X', 1, 8);
	letterArray[24] = new Letter('Y', 2, 4);
	letterArray[25] = new Letter('Z', 1, 10);
	letterArray[26] = new Letter(BLANK_TILE, 2, 0);
}


TileLookUp::~TileLookUp()
{
}
