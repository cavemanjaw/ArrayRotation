#ifndef BIT_ARRAY_WORD_H
#define BIT_ARRAY_WORD_H

typedef unsigned int U32;

class BitArrayWord
{
	// Member variable declarations
public:
	U32 word;

	//Member function declarations
public:
	void PrintBitsOfWord(const U32& word, int bitsAmount);
};

#endif
