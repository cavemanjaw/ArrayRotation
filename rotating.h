#ifndef ROTATING_H
#define ROTATING_H

// Defines
#define U16 short unsigned
#define U32 unsigned int

#define BITS_PER_BYTE 8
#define BITS_PER_WORD 32

// Struct declarations
struct BitArrayEntryInfo
{
	int amountOfEntriesPerWord;
	int wordPositionInArray;
	int entryPositionInArray;
	int entryPositionInWord;
}


// Function declarations

U32* RandomCreateBitArray(int bitsPerEntry, int matrixSize);
void PrintBitsOfWord(U32& word, int bitsAmount);
void PrintBitArray(U32* array, int bitsPerEntry, int matrixSize);
U32* AllocateBitArray(int bitsPerEntry, int matrixSize);
U32 GetBitArrayElement(U32* array, int row, int column, int arraySize, int bitsPerEntry);
U32 GetValueFromWord(U32 word, int elementIndexInWord, int bitsPerEntry);
void SetValueToWord(U32* word, U32 valueToSet, int bitsPerEntry, int positionOfEntryInWord);
int* RandomCreateArrayOneChunk(int arraySize);
int** RandomCreateArray(int arraySize);
void PrintArrayOneChunk(int* inputArray, int arraySize);
void PrintArray(int** inputArray, int arraySize);
int** Rotate90Array(int** inputArray, int arraySize);
int* Rotate90ArrayOneChunk(int* inputArray, int arraySize);
int** Rotate90ArrayModify(int** inputArray, int arraySize);
U32 GetBitArrayWord(U32* array, int row, int column, int arraySize, int bitsPerEntry);
//Struct tempate?
//Think it is impossible, you can overload only on type 
//Another way is to use a function version, which can shift the bits certain amount, thus providing pseudo-variable-size bitfrlds over int or other type

//unsigned int - 32 bit structure

#endif //ROTATING_H
