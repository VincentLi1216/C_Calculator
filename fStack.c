#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXSIZE 100000

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

void d_display(dStack *s)
{
  if (d_isEmpty(s))
  {
    printf("dStack is empty!\n");
    return;
  }

  int i;
  printf("dStack: ");
  for (i = s->top; i >= 0; i--)
  {
    printf("%.10lf ", s->data[i]);
  }
  printf("\n");
}

void evaluation()
{
  dStack d_Stack;
  d_init(&d_Stack);
  char token[MAXSIZE] = "73 5 / 3 ^ 23 * 65 4 * -";
  int i = 0;
  double total = 0;
  double result;
  int decimal_places = 0;
  bool isDecimal = false;
  while (token[i] != '\0' && token[i] != '\n' && i < strlen(token))
  {
    char nowchar = token[i];
    if (isdigit(nowchar) || nowchar == '.')
    {
      while (nowchar != ' ' && nowchar != '\0' && nowchar != '\n')
      {
        if (isdigit(nowchar))
        {
          if (!isDecimal)
          {
            total *= 10;
            total += nowchar - '0';
          }
          else
          {
            decimal_places++;
            total = total + ((nowchar - '0') / pow(10, decimal_places));
          }
        }
        else if (nowchar == '.')
        {
          isDecimal = true;
        }
        i++;
        nowchar = token[i];
      }
      d_push(&d_Stack, total);
      // d_display(&d_Stack);
      // printf("%.10lf\n", total);
      // 重設變數
      total = 0;
      decimal_places = 0;
      isDecimal = false;
    }
    else if (nowchar == ' ')
    {
      i++;
    }
    else
    {
      double operand2 = d_pop(&d_Stack);
      double operand1 = d_pop(&d_Stack);

      switch (nowchar)
      {
      case '+':
        result = operand1 + operand2;
        d_push(&d_Stack, result);
        break;
      case '-':
        result = operand1 - operand2;
        d_push(&d_Stack, result);
        break;
      case '*':
        result = operand1 * operand2;
        d_push(&d_Stack, result);
        break;
      case '/':
        result = operand1 / operand2;
        d_push(&d_Stack, result);
        break;
      case '%':
        result = fmod(operand1, operand2);
        d_push(&d_Stack, result);
        break;
      case '^':
        result = pow(operand1, operand2);
        d_push(&d_Stack, result);
        break;
      default:
        printf("Invalid operator\n");
        exit(1);
      }

      i++; // 避免進入無窮迴圈
    }
  }

  printf("result: %lf", result);
}

int main()
{
  evaluation();
  return 0;
}
