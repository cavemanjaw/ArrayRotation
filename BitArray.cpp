#include "BitArray.h"

BitArray::BitArray(int arraySize, int bitsPerEntry)
	:arraySize(arraySize)
{
	array_p = AllocateBitArray(bitsPerEntry, arraySize);
}

U32* BitArray::AllocateBitArray(int bitsPerArrayElement, int araySize)
{
	//take the celing of this to malloc
	const int bitsAmount = bitsPerArrayElement * arraySize * arraySize;

	//What to do with the remaining bits? This will allocate a byte and not all bits will be always used?
	//Invstigate

	//For division x/y it is q = (x + y - 1) / y;
	U32* outputArray = (U32*)malloc((bitsAmount + BITS_PER_BYTE - 1) / BITS_PER_BYTE);
	return outputArray;
}

//bitsPerEntry and matrixSize should be held by some member variable
void BitArray::PrintBitArray()
{
	//Iterate over words and then over the entries or just over entries?
	//For every entry - get entry, invoke PrintsBitsOfWord aso
	//What do we want to display? Bits? Or value interpreted by bits?

	const int numOfEntries = arraySize * arraySize;

	for (int row = 0; row < arraySize; ++row)
	{
		for (int column = 0; column < arraySize; ++column)
		{
			//TODO: Make GetBitArrayElement member function
			//r-value reference needed?
			PrintBitsOfWord(
				GetBitArrayElement(array, row, column, matrixSize, bitsPerEntry), bitsPerEntry);
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}
