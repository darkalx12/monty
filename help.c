#include "monty.h"

/**
 * cmp - compares strings
 * @opcode: a string to be compared
 * @listed: a string to be compared
 * Return: 0
 */
int cmp(char *opcode, char *listed)
{
	while (*listed != '\0')
	{
		if (*listed == ' ')
			listed++;
		else if (*opcode == *listed)
		{
			opcode++;
			listed++;
			if (*opcode == '\0' && (*listed == ' ' || *listed == '\n' || *listed == '\0'))
				return (1);
		}
		else
			return (0);
	}
	return (0);
}

/**
 * look - finds newline
 * @list: the string to find \n
 * Return: 1 || 0
 */
int look(char *list)
{
	char *code = "\n";

	while (*list != '\0')
	{
		if (*code == *list)
		{
			code++;
			list++;
			if (*code == '\0')
				return (1);
		}
		else
			list++;
	}
	return (0);
}

/**
 * dragint - int for push opcode
 * @list: the content of the file
 * @ln: line number
 * Return: the number
 */
int dragint(char *list, int ln)
{
	char *opcode = "pushing";

	while (*list != '\0')
	{
		if (*opcode == *list)
		{
			opcode++;
			list++;
			if (*opcode == '\0')
				while (*list)
				{
					if ((*list >= '0' && *list <= '9') || *list == '-')
					{
						search(list, ln);
						return (atoi(list));
					}
					else if (*list == ' ')
						list++;
					else
					{
						fprintf(stderr, "L%d: usage: push integer\n", ln);
						exit(EXIT_FAILURE);
					}
				}
		}
		else
			list++;
	}
	return (0);
}

/**
 * search - finds nonnumbers and number combinations
 * @list: the string
 * @ln: line number
 * Return: 1
 */
int search(char *list, int ln)
{
	int a = 1;

	while (list[a])
	{
		if (list[a] == '\0' || list[a] == '\n')
			break;
		if ((list[a] >= '0' && list[a] <= '9') || list[a] == ' ')
			a++;
		else
		{
			fprintf(stderr, "L%d: usage: push integer\n", ln);
			exit(EXIT_FAILURE);
		}
	}
	return (1);
}
