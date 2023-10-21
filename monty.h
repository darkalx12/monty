#ifndef MONTY_H
#define MONTY_H

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern stack_t *head;
typedef void (*op_func)(stack_t **, unsigned int);

/*file operations*/
void open(char *files_name);
int sep_line(char *buffer, int line_number, int format);
void say_file(FILE *);
int len_chars(FILE *);
void find_func(char *, char *, int, int);

/*Stack operations*/
stack_t *create_node(int a);
void free_node(void);
void printout_stack(stack_t **, unsigned int);
void push_to_stack(stack_t **, unsigned int);
void added_to_queue(stack_t **, unsigned int);

void calling_fun(op_func, char *, char *, int, int);

void print_top(stack_t **, unsigned int);
void remove_top(stack_t **, unsigned int);
void nope(stack_t **, unsigned int);
void change_nodes(stack_t **, unsigned int);

/*Math operations with nodes*/
void adding_nodes(stack_t **, unsigned int);
void subbed_nodes(stack_t **, unsigned int);
void divide_nodes(stack_t **, unsigned int);
void multiple_nodes(stack_t **, unsigned int);
void modded_nodes(stack_t **, unsigned int);

/*String operations*/
void show_char(stack_t **, unsigned int);
void print_str(stack_t **, unsigned int);
void roting(stack_t **, unsigned int);

/*Error hanlding*/
void err(int wrong_code, ...);
void more_err(int error_code, ...);
void str_err(int error_code, ...);
void rotate(stack_t **, unsigned int);

#endif
