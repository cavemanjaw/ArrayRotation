#include <stdlib.h>
#include <iostream>
#include <time.h> 
#include <string.h>
#include "rotating.h"

//TODO

//Add bit valued array type
// 4 bits for each pixel
//unsigned or signed, decide type for bitmap

//Type defines


//Bits per entry must fulfill 16 % bitsPerEntry = 0 
//TODO: Add padding somehow
//TODO: Investigate fulling, accesing and possibility of elastic handling

U32* RandomCreateBitArray(int bitsPerEntry, int matrixSize)
{
	U32* array = AllocateBitArray(bitsPerEntry, matrixSize);

	const int bitsAmount = bitsPerEntry * matrixSize * matrixSize;
	const int wordsAmount = (bitsAmount + BITS_PER_BYTE - 1) / BITS_PER_BYTE;
	
	for (int i = 0; i < wordsAmount; ++i)
	{
		array[i] = rand();
	}

	//There is a possibility of usage of the malloc argument from AllocateBitArray to determine the number of U32 used for array

	return array;
}

void PrintBitsOfWord(const U32& word, int bitsAmount)
{
	for (int i = 0; i < bitsAmount; ++i)
	{
		if (word & 1U << i)
		{
			std::cout << "1";
		} 
		else
		{
			std::cout << "0";
		}
	}
}

void PrintBitArray(U32* array, int bitsPerEntry, int matrixSize)
{
	//Iterate over words and then over the entries or just over entries?
	//For every entry - get entry, invoke PrintsBitsOfWord aso
	//What do we want to display? Bits? Or value interpreted by bits?
	
	const int numOfEntries = matrixSize * matrixSize;
	
	for (int row = 0; row < matrixSize; ++row)
	{
		for (int column = 0; column < matrixSize; ++column)
		{	
			//r-value reference needed?
			PrintBitsOfWord(
				GetBitArrayElement(array, row, column, matrixSize, bitsPerEntry), bitsPerEntry);
			std::cout << " ";
		}
		std::cout << std::endl;
	}		
}

//For division x/y it is q = (x + y - 1) / y;
U32* AllocateBitArray(int bitsPerEntry, int matrixSize)
{	
	//take the celing of this to malloc
	const int bitsAmount = bitsPerEntry * matrixSize * matrixSize;
	
	//What to do with the remaining bits? This will allocate a byte and not all bits will be always used?
	//Invstigate
	U32* outputArray = (U32*)malloc((bitsAmount + BITS_PER_BYTE - 1) / BITS_PER_BYTE);
	return outputArray;
}


//Something - start doing it xD
U32* Rotate90BitArray(const U32* inputArray, const int matrixSize, const int bitsPerEntry)
{
	//Returned pointer to newly allocated array, which will be rotated in this function
	U32* outputArray = AllocateBitArray(bitsPerEntry, matrixSize);
	
	for (int row = 0; row < matrixSize; ++row)
	{
		for (int column = 0; column < matrixSize; ++column)
		{
		
		//Use SetValueToWord here	
		//Do we need a function for returning reference or a pointer to word?
		}
	}
	
	//
	return outputArray;
}

//Is arraySize really needed? Or it is necesssary only for restricting out-of-bound array access?
U32 GetBitArrayElement(U32* array, int row, int column, int arraySize, int bitsPerEntry)
{
	//Works only for power of two bitsPerEntry values
	const int amountOfEntriesPerWord = BITS_PER_WORD / bitsPerEntry;

	//The position of word containing entry in continuously allocated bit array
	const int wordPositionInArray = ((row * arraySize) + column) / amountOfEntriesPerWord;

	//The position of actual entry, starting from zero, independent of word that stores the entry
	const int entryPositionInArray = ((row * arraySize) + column);

	//Relative position of entry in certain word, starting from zero, max index depends on bitsPerEnry
	const int entryPositionOffset = entryPositionInArray - (wordPositionInArray * bitsPerEntry);

	U32 arrayElementContainingEntry;
	U32 entry;

	arrayElementContainingEntry = array[entryPositionInArray];
	entry = GetValueFromWord(arrayElementContainingEntry, entryPositionOffset, bitsPerEntry);

return entry;
}

U32* GetBitArrayWord(U32* array, int row, int column, int arraySize, int bitsPerEntry)
{
	//TODO: This computation are redundant GetBitArrayWord() and GetBitArrayElement() are using almost the same logic
	//TODO: They differ only at the point of returned value, since this cannot be overloaded, the redundant part can be moved
	//      to some other function
	
	//Works only for power of two bitsPerEntry values
	const int amountOfEntriesPerWord = BITS_PER_WORD / bitsPerEntry;

	//The position of word containing entry in continuously allocated bit array
	const int wordPositionInArray = ((row * arraySize) + column) / amountOfEntriesPerWord;

	//The position of actual entry, starting from zero, independent of word that stores the entry
	const int entryPositionInArray = ((row * arraySize) + column);

	//Relative position of entry in certain word, starting from zero, max index depends on bitsPerEnry
	const int entryPositionOffset = entryPositionInArray - (wordPositionInArray * bitsPerEntry);

	return &array[entryPositionInArray];
}

//Instead of bitsToShift put offset here
U32 GetValueFromWord(U32 word, int elementIndexInWord, int bitsPerEntry)
{
	//Bits to shift depend on element index and bitsPerEnty value, there is max shift to right in U32 word
	const int bitsToShift = ((BITS_PER_WORD / bitsPerEntry) - 1 - elementIndexInWord) * bitsPerEntry;

	//Return the bits of entry, they are located from the right, not used bits will be zeroes, since the mask
	return word >> bitsToShift & (U32)(2 ^ bitsPerEntry - 1); //Mask for returned bits, bits that are not the part of entry will be clear
}

//Function declared as void for now, could be extended to bool for checking if the setting of value was correct
void SetValueToWord(U32* word, U32 valueToSet, int bitsPerEntry, int positionOfEntryInWord)
{
	//Get bits in valueToSet in the right place in U32 word
	valueToSet <<= bitsPerEntry * ((BITS_PER_WORD / bitsPerEntry - 1) - positionOfEntryInWord);
	
	//Clear the bits corresponding to occupied in  new entry in passed by pointer word variable
	*word &= ~(((2 ^ bitsPerEntry - 1) << bitsPerEntry));

	//Make bitwise "or" operation to merge bits of valueToSet moved to the right place with the rest of bits of word, that won't be modified
	*word |= valueToSet;
}

//allocate integral multiplicity of sizeof(U16)

int* RandomCreateArrayOneChunk(int arraySize)
{
	//arrayDimension is the length of continuously allocated chunk of memory
	//that is (arraySize * arraySize)
	const int arrayDimension = arraySize * arraySize;
	//Allocate memory for array in one chunk
	int* outputArray = (int*)malloc(sizeof(int) * arrayDimension);
	
	for (int i = 0; i < arrayDimension; ++i)
	{
		outputArray[i] = rand();
	}
	
	return outputArray;
}

int** RandomCreateArray(int arraySize)
{
	int** outputArray = (int**)malloc(sizeof(int*) * arraySize);
	for (int i = 0; i < arraySize; ++i)
	{
		outputArray[i] = (int*)malloc(sizeof(int) * arraySize);
	}

	for (int i = 0; i < arraySize; ++i)
	{
		for (int j = 0; j < arraySize; ++j)
		{
			outputArray[i][j] = rand();
		}
	}

	return outputArray;
}

void PrintArrayOneChunk(int* inputArray, int arraySize)
{
	for (int i = 0; i < arraySize; ++i)
	{
		for(int j = 0; j < arraySize; ++j)
		{
			std::cout << inputArray[(i * arraySize) + j] << " ";
		}
	std::cout << std::endl;
	}
}

//For printing results
void PrintArray(int** inputArray, int arraySize)
{
	for (int i = 0; i < arraySize; ++i)
	{
		for (int j = 0; j < arraySize; ++j)
		{
			std::cout << inputArray[i][j] << " ";
		}
	std::cout << std::endl;
	}
}

//Returning array
int** Rotate90Array(int** inputArray, int arraySize)
{
	int** outputArray = (int**)malloc(sizeof(int*) * arraySize);
	
	//Allocate memory for every pointer in outputArray[]
	for (int i = 0; i < arraySize; ++i)
	{
		outputArray[i] = (int*)malloc(sizeof(int) * arraySize);
	}

	//Process newly allocated array
	for (int i = 0; i < arraySize; ++i)
	{
		for (int j = 0; j < arraySize; ++j)
		{
			outputArray[i][j] = inputArray[j][arraySize - i - 1];
		}
	}

	return outputArray;
}

//Can it be done as template? I mean, this would need 
int* Rotate90ArrayOneChunk(int* inputArray, int arraySize)
{
	const int arrayDimension = arraySize * arraySize;
	int* outputArray = (int*)malloc(sizeof(int) * arrayDimension);
	
	for (int i = 0; i < arraySize; ++i)
	{
		for (int j = 0; j < arraySize; ++j)
		{
			outputArray[(i * arraySize) + j] = inputArray[(j * arraySize) + (arraySize - i - 1)];
		}
	}

	return outputArray;
}

//Modify array
int** Rotate90ArrayModify(int** inputArray, int arraySize)
{
	//No new memory allocation needed
	//Do it on stack
	int originalArray[arraySize][arraySize];
	
	//Copy memory underneath inputArray's pointers
	for (int i = 0; i < arraySize; ++i)
	{
		memcpy(&originalArray[i][0], inputArray[i], (sizeof(int) * arraySize));
	}

	for (int i = 0; i < arraySize; ++i)
	{
		for (int j = 0; j < arraySize; ++j)
		{
			inputArray[i][j] = originalArray[j][arraySize - i - 1];
		}
	}

	return inputArray;
}

int main()
{
	//Seed the rand!
	srand(time(NULL));

	//For testing the output
	const int arraySize = 7;
	int** array = RandomCreateArray(arraySize);
	int** rotatedArray = Rotate90Array(array, arraySize);

	//Print original array
	PrintArray(array, arraySize);
	
	std::cout << std::endl;

	//Print rotated array
	PrintArray(rotatedArray, arraySize);

	std::cout << std::endl;
	
	//Modify and print original array
	Rotate90ArrayModify(array, arraySize);
	PrintArray(array, arraySize);	

	std::cout << "*****************************" << std::endl;
	std::cout << "One chunk array" << std::endl;
	std::cout << std::endl;

	//One chunk array
	int* arrayOneChunk = RandomCreateArrayOneChunk(arraySize);
	
	PrintArrayOneChunk(arrayOneChunk, arraySize);

	std::cout << std::endl;
	std::cout << std::endl;

	int* arrayOneChunkRotated = Rotate90ArrayOneChunk(arrayOneChunk, arraySize);

	PrintArrayOneChunk(arrayOneChunkRotated, arraySize);

	return 0; 
}
