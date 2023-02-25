#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "binary.h"

void print_truth_table(uint8_t *output, uint32_t nargs, uint32_t nlines);
void print_dash_line(uint32_t nargs);
void print_pairs(uint32_t *pairs, uint32_t nargs);
void print_tests(uint32_t *tests, uint32_t ntests, uint32_t nargs, uint8_t *output);

#endif /* PRINT_H */
