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
uint32_t check_valid_nthreads(uint32_t available_threads, uint32_t argument_count);
int compare_pairs(uint32_t *pairs1, uint32_t *pairs2, uint32_t npairs);
ThreadArg *to_thread_arg (uint32_t nargs, uint32_t nlines, uint8_t *output, uint32_t *start, uint32_t *saved_pairs, uint32_t *saved_ntests, bool *end, pthread_mutex_t *start_mux, pthread_mutex_t *solution_mux);
void from_thread_arg (ThreadArg *thread_arg, uint32_t *nargs, uint32_t *nlines, uint8_t **output, uint32_t **start, uint32_t **saved_pairs, uint32_t **saved_ntests, bool **end, pthread_mutex_t **start_mux, pthread_mutex_t **solution_mux);
void *find_solution_thread(void *arg);
uint32_t get_start_pairs (uint32_t *pairs, uint32_t *start, uint32_t nargs, uint32_t nlines, pthread_mutex_t *start_mux);
Status check_solution_thread(uint32_t *pairs, uint32_t nargs, uint32_t *saved_pairs, uint32_t *saved_ntests, uint8_t *output, pthread_mutex_t *solution_mux);
void copy_array(uint32_t *from, uint32_t *to, uint32_t n);
bool check_invalid_pairs_thread(uint32_t *pairs, uint32_t nargs, uint32_t nlines, uint8_t *output, uint32_t *i);

#endif /* THREADS_H */
