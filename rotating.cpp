// reverse array
//1. In form of table of pointers, allocate memory
//2. In form of continuously allocated chunk of memory
//3. Return a poniter to new array
//4. Modify array
//5. Array on stack?
//6. Wyci¹gn¹æ z tegom bity
//7. Rozbudowaæ interfejs o mo¿liwoœæ obrotu w dowoln¹ stronê

//TODO There is a bug, most probebly in function responsible for rotating array allocated in one chunk
//RESOLVED Printing was off

#include <stdlib.h>
#include <iostream>
#include <time.h> 
#include <string.h>

//TODO

//Add bit valued array type
// 4 bits for each pixel
//unsigned or signed, decide type for bitmap

//Type defines
#define U16 short unsigned
#define U32 unsigned int

#define BITS_PER_BYTE 8
#define BITS_PER_WORD 32

//Bits per entry must fulfill 16 % bitsPerEntry = 0 
//TODO: Add padding somehow
//TODO: Investigate fulling, accesing and possibility of elastic handling

//For division x/y it is q = (x + y - 1) / y;
U32* AllocateBitArray(int bitsPerEntry, int matrixSize)
{	
	//take the celing of this to malloc
	const int bitsAmount = bitsPerEntry * matrixSize * matrixSize;
	
	//What to do with the remaining bits? This will allocate a byte and not all bits will be always used?
	//Invstigate
	U32* outputArray = (U16*)malloc((bitsAmount + BITS_PER_BYTE - 1) / BITS_PER_BYTE);
	return outputArray;
}

//Is arraySize really needed? Or it is necesssary only for restricting out-of-bound array access?
U32 AccessBitArrayElement(U32* array, int row, int column, int arraySize, int bitsPerEntry)
{
//calculate the position in array
//nieee
const int amountOfEntriesPerWord = BITS_PER_WORD / bitsPerEntry;
const int wordPositionInArray = ((row * arraySize) + column) / amountOfEntriesPerWord;
const int entryPositionInArray = ((row * arraySize) + column);
const int entryPositionOffset = entryPositionInArray % wordPositionInArray;

U32 arrayElementContainingEntry;
U32 entry;

//TODO: Investigate the corectness of it!
arrayElementContainingEntry = array[positionInArray];
//entry = arrayElementContainingEntry // right bitshift for getting the value
//must be masking also

//then, calculate the bit shift for certainn value
//Will it be positionInArray 

//store it in U32 and return

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
