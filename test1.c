#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXSIZE 1000000

typedef struct
{
  double data[MAXSIZE];
  int top;
} dStack;

void d_init(dStack *s)
{
  s->top = -1;
}

int d_isFull(dStack *s)
{
  return s->top == MAXSIZE - 1;
}

int d_isEmpty(dStack *s)
{
  return s->top == -1;
}

void d_push(dStack *s, double value)
{
  if (d_isFull(s))
  {
    printf("dStack is full!\n");
    return;
  }

  s->data[++s->top] = value;
}

double d_pop(dStack *s)
{
  if (d_isEmpty(s))
  {
    printf("dStack is empty!\n");
    return -1;
  }

  return s->data[s->top--];
}

int main()
{
  dStack d_Stack;
  d_init(&d_Stack);
  double d1 = 1.23;
  double d2 = 2.34;
  d_push(&d_Stack, d1);
  d_push(&d_Stack, d2);
  printf("%.2lf\n", d_pop(&d_Stack));
  printf("%.2lf\n", d_pop(&d_Stack));
  return 0;
}
