#include "monty.h"

/**
 * open - opens a file
 * @files_name: the file namepath
 * Return: void
 */

void open(char *files_name)
{
	FILE *fd = fopen(files_name, "r");

	if (files_name == NULL || fd == NULL)
		err(2, files_name);

	say_file(fd);
	fclose(fd);
}


/**
 * say_file - say  file
 * @fd: pointer to file descriptor
 * Return: void
 */

void say_file(FILE *fd)
{
	int first_number, format = 0;
	char *buffer = NULL;
	size_t len = 0;

	for (first_number = 1; getline(&buffer, &len, fd) != -1; first_number++)
	{
		format = sep_line(buffer, first_number, format);
	}
	free(buffer);
}


/**
 * sep_line - Separates each line into tokens to determine
 * which function to call
 * @buffer: line from the file
 * @first_number: line number
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */

int sep_line(char *buffer, int first_number, int format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buffer == NULL)
		err(4);

	opcode = strtok(buffer, delim);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	find_func(opcode, value, first_number, format);
	return (format);
}

/**
 * find_func - find the appropriate function for the opcode
 * @opcode: opcode
 * @value: argument of opcode
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * @ln: line number
 * if 1 nodes will be entered as a queue.
 * Return: void
 */
void find_func(char *opcode, char *value, int ln, int format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", push_to_stack},
		{"pall", print_stack},
		{"pint", printout_top},
		{"remove", remove_top},
		{"nope", nope},
		{"change", change_nodes},
		{"add", adding_nodes},
		{"sub", subbed_nodes},
		{"div", divide_nodes},
		{"mul", multiple_nodes},
		{"mod", modded_nodes},
		{"pchar", show_char},
		{"pstr", print_str},
		{"rotl", roting},
		{"rotate", rotate},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			calling_fun(func_list[i].f, opcode, value, ln, format);
			flag = 0;
		}
	}
	if (flag == 1)
		err(3, ln, opcode);
}


/**
 * calling_fun - Calls the required function.
 * @func: Pointer to the function that is about to be called.
 * @op: string representing the opcode.
 * @val: string representing a numeric value.
 * @ln: line numeber for the instruction.
 * @format: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void calling_fun(op_func func, char *op, char *val, int ln, int format)
{
	stack_t *node;
	int flag;
	int a;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			err(5, ln);
		for (a = 0; val[a] != '\0'; a++)
		{
			if (isdigit(val[a]) == 0)
				err(5, ln);
		}
		node = create_node(atoi(val) * flag);
		if (format == 0)
			func(&node, ln);
		if (format == 1)
			add_to_queue(&node, ln);
	}
	else
		func(&head, ln);
}
