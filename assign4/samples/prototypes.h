/* File: prototypes.h
 * ------------------
 * Defines the required interface for the functions of CS107 assign3.
 * Refer to assignment writeup for more information.
 */

#ifndef _prototypes_h
#define _prototypes_h

#include <stddef.h>

void *binsert(const void *key, void *base, size_t *nel, size_t width, int (*cmp)(const void *, const void *));

#endif