#include "solve.h"

static bool check_jump(uint32_t n, uint32_t nargs, uint32_t index);

uint8_t *get_output(Function function, uint32_t nargs, uint32_t nlines)
{
	uint8_t *output;
	uint8_t *line;
	uint32_t index;

	output = (uint8_t*) malloc(nlines * sizeof(uint8_t));
	line = (uint8_t*)malloc(nargs * sizeof(uint8_t));

	for (index = 0; index < nlines; index++)
	{
		decimal_to_binary(index, line, nargs);
		output[index] = function(line);
	}

	free(line);

	return output;
}

int32_t find_solution(uint32_t nargs, uint32_t nlines, uint8_t *output)
{
	uint32_t index;
	uint32_t *pairs = (uint32_t*)malloc(2 * nargs * sizeof(uint32_t));	
	uint32_t *saved_pairs = (uint32_t*)malloc(2 * nargs * sizeof(uint32_t));	
	uint32_t saved_ntests = ((nargs * 2U) + 1U);
	Status res;

	/* Initializing pairs array */
	for (index = 0; index < nargs; index++)
	{
		first_pair(pairs + 2 * index, nargs, index);
	}

	index = 0;

	while (index < nargs)
	{
		index = check_invalid_pairs(pairs, nargs, nlines, output);

		res = check_solution(pairs, nargs, saved_pairs, &saved_ntests);

		if (res != False)
		{
			print_tests(saved_pairs, saved_ntests, nargs, output);
			print_pairs(pairs, nargs);
		}
		
		if (res == End)
			break;

		index = next_pair(pairs, nargs, nlines);
	}

	free((uint32_t*)pairs);
	free((uint32_t*)saved_pairs);

	return 0;	
}

void first_pair(uint32_t *pair, uint32_t nargs, uint32_t index)
{
	pair[0] = 0U;
	pair[1] = 1U << (nargs - index - 1U);

	return;
}

uint32_t next_pair(uint32_t *pairs, uint32_t nargs, uint32_t nlines)
{
	uint32_t index = nargs - 1U;
	uint32_t *x = pairs + (2U * (nargs - 1U));
	uint32_t *y = x + 1U;

	*x += 2U;
	*y += 2U;

	if (*x >= nlines)
	{
		first_pair(x, nargs, (nargs - 1U));
		return next_pair_i(pairs, nargs, nlines, (index - 1U));
	}
	else
	{
		return index;	/* return index of changed pair */
	}
}

uint32_t next_pair_i(uint32_t *pairs, uint32_t nargs, uint32_t nlines, uint32_t index)
{
	uint32_t *x = pairs + (2U * index);
	uint32_t *y = x + 1U;

	if (index >= nargs)
	{
		return nargs;
	}

	if (true == check_jump(*y, nargs, index))
	{
		*x = *y + 1U;
	}
	else
	{
		*x = *x + 1U;
	}
	
	*y = *x | (1U << (nargs - 1U - index));

	if (*x >= nlines)
	{
		if (index > 0)
		{
			first_pair(x, nargs, index);
			return next_pair_i(pairs, nargs, nlines, (index - 1U));
		}
		else
		{
			return nargs;
		}
	}
	else
	{
		return index;	/* return index of changed pair */
	}
}

static bool check_jump(uint32_t n, uint32_t nargs, uint32_t index)
{
	uint32_t mask = (1U << (nargs - index)) - 1U;

	return ((mask & n) == mask);
}

uint32_t check_equal_output(uint32_t *pairs, uint32_t nargs, uint8_t *output)
{
	uint32_t index;
	uint32_t  x, y;

	for (index = 0U; index < nargs; index++)
	{
		x = pairs[(2U * index)];
		y = pairs[((2U * index) + 1U)];

		if (output[x] == output[y])
		{
			return index;
		}
	}

	return nargs;
}

uint32_t check_invalid_pairs(uint32_t *pairs, uint32_t nargs, uint32_t nlines, uint8_t *output)
{
	uint32_t index = 0U;	/* default points to pair 0, which may mean nothing */
	uint32_t count;

	while ((count = check_equal_output(pairs, nargs, output)) < nargs)
	{
		/* printf("Equal output.\n"); */
		fflush(stdout);
		index = next_pair_i(pairs, nargs, nlines, count);
	}

	return index;
}

uint32_t count_unique(uint32_t *pairs, uint32_t nargs)
{
	uint32_t outer_index;
	uint32_t inner_index;
	uint32_t nentries = nargs * 2U;
	uint32_t count = nentries;

	for (outer_index = 0U; outer_index < nentries; outer_index++)
	{
		for(inner_index = (outer_index + 2U); inner_index < nentries; inner_index++)
		{
			if (pairs[outer_index] == pairs[inner_index])
			{
				count--;
				break;
			}
		}
	}

	return count;
}

Status check_solution(uint32_t *pairs, uint32_t nargs, uint32_t *saved_pairs, uint32_t *saved_ntests)
{
	uint32_t  ntests;
	uint32_t  min_ntests = (nargs + 1U);

	ntests = count_unique(pairs, nargs);

	if (ntests < *saved_ntests)
	{
		*saved_ntests = filter_repeated_pairs(pairs, nargs, saved_pairs);

		bubble_sort(saved_pairs, *saved_ntests);

		if (ntests == min_ntests)
		{
			return End;
		}
		else
		{
			return True;
		}
	}

	return False;
}

uint32_t filter_repeated_pairs(uint32_t *pairs, uint32_t nargs, uint32_t *saved_pairs)
{
	uint32_t outer_index;
	uint32_t inner_index;
	uint32_t result;
	bool unique;
	uint32_t nentries = (nargs * 2U);

	result = 0U;

	for (outer_index = 0U; outer_index < nentries; outer_index++)
	{
		unique = true;

		for (inner_index = (outer_index + 2U); inner_index < nentries; inner_index++)
		{
			if (pairs[outer_index] == pairs[inner_index])
			{
				unique = false;
				break;
			}
		}

		if (true == unique)
		{
			saved_pairs[result] = pairs[outer_index];
			result++;
		}
	}

	return result;
}
