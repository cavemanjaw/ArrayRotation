#include "BitArrayWord.h"

void BitArrayWord::PrintBitsOfWord(const U32& word, int bitsAmount)
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

