#ifndef MISC_H
#define MISC_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// declare functions

extern char **database_creation(FILE *file, int database, int queries);
extern char **load_queries(FILE *file, int queries, int database);
extern void query_parser(FILE *output, int queries, char **tokens,
                         char **queries_tokens, int database);

#endif
