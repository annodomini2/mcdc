#include "function.h"

uint32_t nthreads = 4;
uint8_t show_truth_table = 0;
uint32_t nargs = 6;

// TODO: Understand this, looks to be some logical combination operation
uint8_t function(uint8_t input[])
{
	return (uint8_t) ((input[0] & input[1]) ^ (input[2] & input[3]) ^ (input[4] & input[5]));

}

// TODO: This looks like it needs to be updated to support operating system
uint32_t get_nthreads(void)
{
	return nthreads;
}

// TODO: This looks to do nothing
uint8_t get_show_truth_table(void)
{
	return show_truth_table;
}

// TODO: This likely needs to be updated to support file under analysis
uint32_t get_nargs(void)
{
	return nargs;
}
