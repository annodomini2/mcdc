#include "mcdc.h"

int main(void)
{
	uint32_t nthreads = get_nthreads();
	uint32_t nargs = get_nargs();
	uint32_t nlines = 1<<nargs;

	uint8_t *output = get_output(function, nargs, nlines);

	if (TRUE == get_show_truth_table())
	{
		print_truth_table(output, nargs, nlines);
	}

	printf("Total # of tests = %d\n", nlines);

	solve_with_threads(nthreads, nargs, nlines, output);

	free((uint8_t *) output);

	printf("\nEND\n");
	return 0;
}
