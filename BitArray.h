#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#include "rotating.h"

class BitArray
{
	//Member variable declarations
private:
	U32* array_p;
	int arraySize;
	int bitsPerArrayElement;

	//Member function declarations
public:
	BitArray(int arraySize, int bitsPerEntry);
	void PrintBitArray();
private:
	U32* AllocateBitArray(int bitsPerEntry, int matrixSize);
};

#endif
