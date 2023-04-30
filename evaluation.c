#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define STACK_SIZE 100

float stack[STACK_SIZE];
int top = -1;
int i;
float a, b, c;

void push(float item)
{
  if (top >= STACK_SIZE - 1)
  {
    printf("Stack Overflow\n");
    exit(1);
  }
  else
  {
    top++;
    stack[top] = item;
  }
}

float pop()
{
  float item;

  if (top < 0)
  {
    printf("Stack Underflow\n");
    exit(1);
  }
  else
  {
    item = stack[top];
    top--;
    return item;
  }
}

int evaluatePostfix(char *output)
{
  int i, operand1, operand2, result;

  for (i = 0; i < strlen(output); i++)
  {
    char c = output[i];
    if (isdigit(c))
    {
      push(c - '0');
    }
    else
    {
      operand2 = pop();
      operand1 = pop();

      switch (c)
      {
      case '+':
        result = operand1 + operand2;
        break;
      case '-':
        result = operand1 - operand2;
        break;
      case '*':
        result = operand1 * operand2;
        break;
      case '/':
        result = operand1 / operand2;
        break;
      case '%':
        result = operand1 % operand2;
        break;
      case '^':
        a = operand1;
        b = operand2;
        c = a;
        for (i = 1; i < b; i++)
        {
          c *= a;
        }
        result = c;
        break;
      default:
        printf("Invalid operator\n");
        exit(1);
      }

      push(result);
    }
  }

  return pop();
}

int main()
{
  char output[STACK_SIZE] = "53^3/";
  int result = evaluatePostfix(output);
  printf("Result: %d\n", result);
  return 0;
}
