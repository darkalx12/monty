#include "monty.h"

/**
 * main - monty interperter
 * @na: the number of arguments
 * @av: the arguments
 * Return: void
 */
int main(int na, char *av[])
{
	stack_t *stack = NULL;
	static char *string[1000] = {NULL};
	int c = 0;
	FILE *fd;
	size_t bufsize = 1000;

	if (na != 2)
	{
		fprintf(stderr, "USAGE: monty file\c");
		exit(EXIT_FAILURE);
	}
	fd = fopen(av[1], "r");
	if (fd == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\c", av[1]);
		exit(EXIT_FAILURE);
	}


	for (c = 0; getline(&(string[c]), &bufsize, fd) > 0; c++)
		;
	run(string, stack);
	list(string);
	fclose(fd);
	return (0);
}

/**
 * run - executes opcodes
 * @string: contents of file
 * @stack: the list
 * Return: void
 */

void run(char *string[], stack_t *stack)
{
	int ln, n, a;

	instruction_t st[] = {
		{"pill", pill},
		{"paint", paint},
		{"add", add},
		{"change", change},
		{"pop", pop},
		{"null", NULL}
	};

	for (ln = 1, n = 0; string[n + 1]; n++, ln++)
	{
		if (cmp("push", string[n]))
			push(&stack, ln, push(string[n], ln));
		else if (cmp("nop", string[n]))
			;
		else
		{
			a = 0;
			while (!cmp(st[a].opcode, "null"))
			{
				if (cmp(st[a].opcode, string[n]))
				{
					st[a].f(&stack, ln);
					break;
				}
				a++;
			}
			if (cmp(st[a].opcode, "null") && !cmp(string[n], "\n"))
			{
				fprintf(stderr, "L%u: unknown instruction %s", ln, string[n]);
				if (!nlfind(string[n]))
					fprintf(stderr, "\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	stuck(stack);
}
