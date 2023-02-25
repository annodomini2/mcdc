#ifndef SOLVE_H
#define SOLVE_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "binary.h"
#include "bubblesort.h"
#include "print.h"

typedef uint8_t (*Function) (uint8_t *);

typedef enum sol{ False='f', True='t', End='e'} Status;

void decimal_to_binary(uint32_t decimal, uint8_t *binary, uint32_t size);
uint8_t *get_output(Function function, uint32_t nargs, uint32_t nlines);
int32_t find_solution (uint32_t nargs, uint32_t nlines, uint8_t *output);
void first_pair(uint32_t *pair, uint32_t nargs, uint32_t i);
uint32_t next_pair(uint32_t *pairs, uint32_t nargs, uint32_t nlines);
uint32_t next_pair_i(uint32_t *pairs, uint32_t nargs, uint32_t nlines, uint32_t i);
bool check_jump(uint32_t n, uint32_t nargs, uint32_t i);
uint32_t check_equal_output(uint32_t *pairs, uint32_t nargs, uint8_t *output);
uint32_t check_invalid_pairs(uint32_t *pairs, uint32_t nargs, uint32_t nlines, uint8_t *output);
uint32_t count_unique(uint32_t *pairs, uint32_t nargs);
Status check_solution(uint32_t *pairs, uint32_t nargs, uint32_t *saved_pairs, uint32_t *saved_ntests);
uint32_t filter_repeated_pairs(uint32_t *pairs, uint32_t nargs, uint32_t *saved_pairs);

#endif /* SOLVE_H */
