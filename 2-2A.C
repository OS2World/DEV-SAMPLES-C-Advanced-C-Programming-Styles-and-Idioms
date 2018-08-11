/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#define STACK_SIZE 10

struct Stack {
    long items[STACK_SIZE];
    int sp;
};

void Stack_initialize(s)
struct Stack *s;
{
    s->sp = -1;
}

long Stack_top(s)
struct Stack *s;
{
    return s->items[s->sp];
}

long Stack_pop(s)
struct Stack *s;
{
    return s->items[s->sp--];
}

void Stack_push(s, i)
struct Stack *s; long i;
{
    s->items[++s->sp] = i;
}

int main()
{
    struct Stack q;
    int i;
    Stack_initialize(&q);
    Stack_push(&q,1);
    i = Stack_top(&q);
    Stack_pop(&q);
}
