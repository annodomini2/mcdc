#include "threads.h"

static uint32_t determine_required_threads(uint32_t available_threads, uint32_t argument_count);
static ThreadArg *to_thread_arg(uint32_t nargs, uint32_t nlines, uint8_t *output, uint32_t *start, uint32_t *saved_pairs, uint32_t *saved_ntests, bool *end, pthread_mutex_t *start_mux, pthread_mutex_t *solution_mux);
static void from_thread_arg(ThreadArg *thread_arg, uint32_t *nargs, uint32_t *nlines, uint8_t **output, uint32_t **start, uint32_t **saved_pairs, uint32_t **saved_ntests, bool **end, pthread_mutex_t **start_mux, pthread_mutex_t **solution_mux);
static void *find_solution_thread(void *arg);
static uint32_t get_start_pairs(uint32_t  *pairs, uint32_t  *start, uint32_t  nargs, uint32_t  nlines, pthread_mutex_t *start_mux);
static Status check_solution_thread(uint32_t *pairs, uint32_t nargs, uint32_t *saved_pairs, uint32_t *saved_ntests, uint8_t *output, pthread_mutex_t *solution_mux);
static void copy_array(uint32_t *from, uint32_t *to, uint32_t n);
static bool check_invalid_pairs_thread(uint32_t  *pairs, uint32_t  nargs, uint32_t  nlines, uint8_t  *output, uint32_t  *i);


uint32_t solve_with_threads(uint32_t nthreads, uint32_t nargs, uint32_t nlines, uint8_t *output)
{
	pthread_t *threads;
	ThreadArg *thread_arg;
	uint32_t *start = (uint32_t*)malloc(2 * nargs * sizeof(uint32_t));
	uint32_t *saved_pairs = (uint32_t*) malloc( 2 * nargs * sizeof(uint32_t));	
	uint32_t saved_ntests = 2 * nargs + 1;
	uint32_t  index;
	bool end = false;

	pthread_mutex_t start_mux;
	pthread_mutex_t solution_mux;

	nthreads = determine_required_threads(nthreads, nargs);
	threads = (pthread_t *) malloc(nthreads*sizeof(pthread_t));

	pthread_mutex_init(&start_mux, NULL);
	pthread_mutex_init(&solution_mux, NULL);

	/* Initializing start pairs array */
	for (index = 0U; index < nargs; index++)
	{
		first_pair((start + (2 * index)), nargs, index);
	}
	
	/* Creating threads */
	for (index = 0U; index < nthreads; index++)
	{
		thread_arg = to_thread_arg(nargs, nlines, output, start, saved_pairs, &saved_ntests, &end, &start_mux, &solution_mux);

		pthread_create(&(threads[index]), NULL, find_solution_thread, (void *)thread_arg);
	}

	printf("Created %d threads.\n", nthreads);

	for (index = 0U; index < nthreads; index++)
	{
		pthread_join(threads[index], NULL);
	}

	printf("Exited %d threads.\n", nthreads);

	pthread_mutex_destroy(&start_mux);
	pthread_mutex_destroy(&solution_mux);

	free(threads);
	free(start);
	free(saved_pairs);

	return 0;
}

static uint32_t determine_required_threads(uint32_t available_threads, uint32_t argument_count) 
{
	uint32_t index;
	int32_t power = (argument_count - 1U);
	uint32_t permutation_count = 1U;
	bool limit_reached = false;
	uint32_t required_threads;

	if (argument_count == 0U)
	{
		required_threads = 0U;
	}
	else if ((argument_count == 1U) || (available_threads == 0U))
	{
		required_threads = 1U;
	}
	else
	{
		for (index = 0U; index < power; index++)
		{
			permutation_count <<= 1U;

			if (permutation_count >= available_threads)
			{
				limit_reached = true;
				required_threads = available_threads;
				break;
			}
		}

		if (false == limit_reached)
		{
			required_threads = permutation_count;
		}
	}

	return required_threads;
}

// TODO: Understand what this function is doing as the logic is irrational
// int compare_pairs(uint32_t *pairs1, uint32_t *pairs2, uint32_t npairs)
// {
// 	uint32_t index;
// 	int comparison = 0;	/* pairs1 are smaller than pairs2 */ 

// 	for (index = 0U; index < npairs; index++)
// 	{
// 		if (pairs1[index] < pairs2[index])
// 		{
// 			comparison = -1;
// 			break;
// 		}
// 		else if (pairs1[index] == pairs2[index])
// 		{
// 			continue;
// 		}
// 		else if (pairs1[index] > pairs2[index])
// 		{
// 			comparison = 1;
// 			break;
// 		}
// 	}

// 	return comparison;
// }

// TODO: Determine if this function serves any benefit.
static ThreadArg *to_thread_arg(uint32_t nargs, uint32_t nlines, uint8_t *output, uint32_t *start, uint32_t *saved_pairs, uint32_t *saved_ntests, bool *end, pthread_mutex_t *start_mux, pthread_mutex_t *solution_mux)
{
	ThreadArg *thread_arg = (ThreadArg*)malloc(sizeof(ThreadArg));

	thread_arg->nargs = nargs;
	thread_arg->nlines = nlines;
	thread_arg->output = output;
	thread_arg->start = start;
	thread_arg->saved_pairs = saved_pairs;
	thread_arg->saved_ntests = saved_ntests;
	thread_arg->end = end;
	thread_arg->start_mux = start_mux;
	thread_arg->solution_mux = solution_mux;

	return thread_arg;
}

// TODO: Determine if this function serves any benefit.
static void from_thread_arg(ThreadArg *thread_arg, uint32_t *nargs, uint32_t *nlines, uint8_t **output, uint32_t **start, uint32_t **saved_pairs, uint32_t **saved_ntests, bool **end, pthread_mutex_t **start_mux, pthread_mutex_t **solution_mux)
{
	*nargs = thread_arg->nargs;
	*nlines = thread_arg->nlines;
	*output = thread_arg->output;
	*start = thread_arg->start;
	*saved_pairs = thread_arg->saved_pairs;
	*saved_ntests = thread_arg->saved_ntests;
	*end = thread_arg->end;
	*start_mux = thread_arg->start_mux;
	*solution_mux = thread_arg->solution_mux;

	free(thread_arg);

	return;
}

static void *find_solution_thread(void *arg)
{
	uint32_t  nargs;
	uint32_t  nlines;
	uint8_t  *output;
	uint32_t  *start;
	uint32_t  *pairs;
	uint32_t  *saved_pairs;
	uint32_t  *saved_ntests;
	uint32_t  i;
	char res;
	bool *end;
	bool invalid;
	pthread_mutex_t *start_mux;
	pthread_mutex_t *solution_mux;

	from_thread_arg((ThreadArg *)arg, &nargs, &nlines, &output, &start, &saved_pairs, &saved_ntests, &end, &start_mux, &solution_mux);

	pairs = (uint32_t  *) malloc(2*nargs*sizeof(nargs));

	while(!(*end))
	{
		i = get_start_pairs(pairs, start, nargs, nlines, start_mux);
		
		if (i == nargs)
		{
			*end = true;
		}

		do
		{
			invalid = check_invalid_pairs_thread(pairs, nargs, nlines, output, &i);

			if (invalid && (i <= 0) && (i >= nargs))
				break;

			/* solution read-write lock and print mutex */
			res = check_solution_thread(pairs, nargs, saved_pairs, saved_ntests, output, solution_mux);

			if(res == End)
			{
				*end = true;
				break;
			}

			i = next_pair(pairs, nargs, nlines);
		} while(!(*end) && (i > 0) && (i < nargs));
	}

	free((uint32_t*)pairs);

	return 0;
}

static uint32_t get_start_pairs(uint32_t  *pairs, uint32_t  *start, uint32_t  nargs, uint32_t  nlines, pthread_mutex_t *start_mux)
{
	uint32_t  i;

	/* lock mutex */
	pthread_mutex_lock(start_mux);

	copy_array(start, pairs, 2 * nargs);

	i = next_pair_i(start, nargs, nlines, 0);

	/* unlock mutex */
	pthread_mutex_unlock(start_mux);

	return i;
}

static Status check_solution_thread(uint32_t *pairs, uint32_t nargs, uint32_t *saved_pairs, uint32_t *saved_ntests, uint8_t *output, pthread_mutex_t *solution_mux)
{
	Status code = False;
	uint32_t  min_ntests = nargs + 1;

	uint32_t  ntests = count_unique(pairs, nargs);

	if (ntests < *saved_ntests)
	{
		pthread_mutex_lock(solution_mux);

		if (ntests < *saved_ntests)
		{
			filter_repeated_pairs(pairs, ntests, saved_pairs);
			bubble_sort(saved_pairs, ntests);

			*saved_ntests = ntests;

			print_tests(saved_pairs, *saved_ntests, nargs, output);
			print_pairs(pairs, nargs);
			fflush(stdout);

			if (ntests > min_ntests)
				code = True;
			else
				code = End;
		}

		pthread_mutex_unlock(solution_mux);
	}

	return code;
}

static void copy_array(uint32_t *from, uint32_t *to, uint32_t n)
{
	uint32_t  i;

	for (i = 0; i < n; i++)
	{
		to[i] = from[i];
	}
}

static bool check_invalid_pairs_thread(uint32_t  *pairs, uint32_t  nargs, uint32_t  nlines, uint8_t  *output, uint32_t  *i)
{
	uint32_t  j;
	bool invalid = false;

	while ((j = check_equal_output(pairs, nargs, output)) < nargs)
	{
		/* printf("Equal output.\n");
		fflush(stdout); */
		invalid = true;
		*i = next_pair_i(pairs, nargs, nlines, j);
	}

	return invalid;
}
