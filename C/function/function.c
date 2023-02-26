#include "function.h"

uint32_t nthreads = 4;
uint8_t show_truth_table = 0;
uint32_t nargs = 6;

uint8_t function (uint8_t input[])
{
	return (uint8_t) ((input[0] & input[1]) ^ (input[2] & input[3]) ^ (input[4] & input[5]));
}

uint32_t get_nthreads(void)
{
	return nthreads;
}

uint8_t get_show_truth_table(void)
{
	return show_truth_table;
}

uint32_t get_nargs(void)
{
	return nargs;
}
