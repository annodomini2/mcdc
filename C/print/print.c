#include "print.h"

static void print_dash_line(uint32_t nargs);

static void print_dash_line(uint32_t nargs)
{
	uint32_t index = 0;

	for (index = 0; index < (8 * (nargs + 4)); index++)
	{
		putchar('-');
	}

	putchar('\n');
	fflush(stdout);
}


void print_truth_table(uint8_t  *output, uint32_t nargs, uint32_t nlines)
{
	uint8_t *input = (uint8_t *)malloc(nargs * sizeof(uint8_t));
	uint32_t outer_index;
	uint32_t inner_index;

	print_dash_line(nargs);

	printf("i\t|\t");
	
	for (outer_index = 0; outer_index < nargs; outer_index++)
	{
		printf("%d\t", outer_index);
	}

	printf("|\to\n");

	print_dash_line(nargs);

	for (outer_index = 0; outer_index < nlines; outer_index++)
	{
		printf("%d\t|\t", outer_index);

		decimal_to_binary(outer_index, input, nargs);

		for (inner_index = 0; inner_index < nargs; inner_index++)
		{
			printf("%u\t", input[inner_index]);
		}

		printf("|\t%u\n", output[outer_index]);
	}

	print_dash_line(nargs);

	free((uint8_t  *) input);
	fflush(stdout);
	return;
}

void print_pairs(uint32_t *pairs, uint32_t nargs)
{
	uint32_t index;

	printf("Pairs:\n");

	for (index = 0; index < nargs; index++)
	{
		printf("(%d, %d) \t", pairs[(2 * index)], pairs[((2 * index) + 1)]);
	}

	printf("\n");

	fflush(stdout);
	return;
}

void print_tests(uint32_t *tests, uint32_t ntests, uint32_t nargs, uint8_t  *output)
{
	uint8_t  *input = (uint8_t*)malloc(nargs * sizeof(uint8_t));
	uint32_t outer_index;
	uint32_t inner_index;
	uint32_t test;

	printf("\nSolution: %d tests\n", ntests);
	print_dash_line(nargs);

	printf("i\t|\t");

	for (outer_index = 0; outer_index < nargs; outer_index++)
	{
		printf("%d\t", outer_index);
	}

	printf("|\to\n");

	print_dash_line(nargs);

	for (outer_index = 0; outer_index < ntests; outer_index++)
	{
		test = tests[outer_index];

		printf("%d\t|\t", test);

		decimal_to_binary(test, input, nargs);

		for (inner_index = 0; inner_index < nargs; inner_index++)
		{
			printf("%u\t", input[inner_index]);
		}

		printf("|\t%u\n", output[test]);
	}

	print_dash_line(nargs);

	free((uint8_t*)input);

	fflush(stdout);
	return;
}
