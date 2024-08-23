#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macros
#define BUFFER_SIZE 1024
#define MAX_TOKENS 100

// Structure for department
typedef struct
{
  char *name;
  int id;
  char *transformed_name;
} department;

// Function Prototypes

/**
 * @brief Reads data from the file and processes it by replacing newlines with
 * colons.
 *
 * @param filename The name of the file to read.
 * @param output_str The output string after processing.
 */
void read_file_and_process(char *filename, char *output_str);

/**
 * @brief Replaces newline characters in a string with colons.
 *
 * @param str The input string.
 */
void replace_newline_with_colon(char *str);

/**
 * @brief Tokenizes the input string based on a given delimiter.
 *
 * @param str The string to tokenize.
 * @param delim The delimiter to use for tokenization.
 * @param num_tokens Pointer to an integer that will store the number of tokens.
 * @return char** Array of tokens.
 */
char **tokenize(char *str, const char *delim, int *num_tokens);

/**
 * @brief Searches for the department name in the tokens and sets the ID.
 *
 * @param tokens Array of tokens.
 * @param num_tokens Number of tokens.
 * @param dept Pointer to the department structure to store the result.
 */
void search_department(char **tokens, int num_tokens, department *dept);

/**
 * @brief Converts the department name to uppercase.
 *
 * @param dept Pointer to the department structure.
 */
void letter_transform(department *dept);

/**
 * @brief Reverses the first half of the department name.
 *
 * @param dept Pointer to the department structure.
 */
void reverse_first_half(department *dept);

/**
 * @brief Frees the memory allocated for tokens.
 *
 * @param tokens Array of tokens.
 * @param num_tokens Number of tokens.
 */
void free_tokens(char **tokens, int num_tokens);

#endif // DEPARTMENT_H
