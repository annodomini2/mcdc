#include "bubblesort.h"

// TODO: Determine if this can be optimised
void bubble_sort(uint32_t *list, uint32_t count)
{
	uint32_t newn;
	uint32_t index;
	uint32_t temp_element;

	do
	{
		newn = 0;

		for (index = 1; index < count; index++)
		{
			if (list[index - 1] > list[index]) 
			{
				temp_element = list[index - 1];
				list[index - 1] = list[index];
				list[index] = temp_element;
				newn = index;
			}
		}

		count = newn;
	} while (count > 1);
}
