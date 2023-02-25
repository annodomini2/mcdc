#include "binary.h"

void decimal_to_binary(uint32_t decimal, uint8_t *binary, uint32_t size)
{
	uint32_t index;

	for (index = 0U; index < size; index++)
	{
		binary[index] = (unsigned char) ((decimal >> (size - index - 1)) & 1);
	}
}
