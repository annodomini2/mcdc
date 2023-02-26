#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>
#include <stdint.h>

#include "solve.h"

typedef struct 
{
	uint32_t nargs;
	uint32_t nlines;
	uint8_t *output;
	uint32_t *start;
	uint32_t *saved_pairs;
	uint32_t *saved_ntests;
	bool *end;
	pthread_mutex_t *start_mux;
	pthread_mutex_t *solution_mux;
} ThreadArg;

uint32_t solve_with_threads(uint32_t nthreads, uint32_t nargs, uint32_t nlines, uint8_t *output);

//int compare_pairs(uint32_t *pairs1, uint32_t *pairs2, uint32_t npairs);

#endif /* THREADS_H */
