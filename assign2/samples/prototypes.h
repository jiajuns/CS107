/* File: prototypes.h
 * ------------------
 * Defines the required interface for the functions of CS107 assign2.
 * Refer to assignment writeup for more information.
 */

#ifndef _prototypes_h
#define _prototypes_h

#include <stdbool.h>
#include <stddef.h>

const char *get_env_value(const char *envp[], const char *varname);

bool scan_token(const char **p_input, const char *delimiters, char buf[], size_t buflen);

#endif
