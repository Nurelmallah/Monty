#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "monty.h"
#include <string.h>
#include <stddef.h>

void process_file(FILE *file, stack_t **stack);
void free_memory(FILE *file, char *line);
char *strtok(char *str, const char *delim);
int strcmp(const char *s1, const char *s2);

/**
 * main - Entry point of the Monty interpreter
 * @argc: Argument count
 * @argv: Argument vector
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}

	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	process_file(file, &stack);

	free_memory(file, NULL);
	return (EXIT_SUCCESS);
}

/**
 * free_memory - Frees memory and closes the file
 * @file: File pointer to be closed
 * @line: Line buffer to be freed
 */
void free_memory(FILE *file, char *line)
{
	if (file != NULL)
		fclose(file);

	if (line != NULL)
		free(line);
}

/**
 * process_line - Processes a single line of the file
 * @line: Line to be processed
 * @len: Length of the line
 * @stack: Pointer to the stack
 * @line_number: Line number in the file
 */
void process_line(char *line, size_t len, stack_t **stack,
		unsigned int *line_number)
{
	char *opcode = strtok(line, " \n");

	if (opcode != NULL && strcmp(opcode, "push") == 0)
	{
		char *arg = strtok(NULL, " \n");

		push(stack, *line_number, arg);
	}
	else if (opcode != NULL && strcmp(opcode, "pall") == 0)
	{
		pall(stack, *line_number);
	}
}

/**
 * process_file - Processes the entire file
 * @file: File to be processed
 * @stack: Pointer to the stack
 */
void process_file(FILE *file, stack_t **stack)
{
	char *line = NULL;
	size_t len = 0;
	unsigned int line_number = 0;

	while (getline(&line, &len, file) != -1)
	{
		line_number++;
		process_line(line, len, stack, &line_number);
		free_memory(NULL, line);
		line = NULL;
		len = 0;
	}

	free_memory(NULL, line);
}
