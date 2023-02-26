#include "binary.h"

void decimal_to_binary(uint32_t decimal, uint8_t *binary, uint32_t size)
{
	uint32_t index;

	/* Loop through every bit in input and convert to a binary output */
	for (index = 0U; index < size; index++)
	{
		// TODO: Needs to be updated to handle different memory formats
		/* Shift the indexed bit, down to bit 0 and mask*/
		binary[index] = (uint8_t)((decimal >> ((size - 1U) - index)) & 0x01U);
	}
}
