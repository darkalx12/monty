#include "monty.h"

/**
 * stuck - frees the singly linked list
 * @head: pointer to list
 * Return: Nothing
 */
void stuck(stack_t *head)
{
	stack_t *node = head;

	if (head == NULL)
		return;

	while (head != NULL)
	{
		node = head;
		head = head->next;
		free(node);
	}
}

/**
 * list - frees getline list
 * @a: pointer to array of strings
 * Return: Nothing
 */
void list(char *b[])
{
	int a = 0;

	while (b[a] != NULL)
	{
		free(b[a]);
		a++;
	}
}
