#include "bubblesort.h"

void bubble_sort(Element *list, uint32_t count)
{
	uint32_t newn;
	uint32_t index;
	Element temp_element;

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
