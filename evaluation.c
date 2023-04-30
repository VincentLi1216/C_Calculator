#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXSIZE 1000000 // 設定最大的字串長度

typedef struct
{
  char arr[MAXSIZE];
  int top;
} Stack;

Stack *createStack() // 創建 stack
{
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->top = -1;
  return stack;
}

void push(Stack *stack, char data) // 壓入元素到 stack 中
{
  if (stack->top == MAXSIZE - 1)
  {
    printf("Error: Stack overflow\n");
    return;
  }
  stack->arr[++stack->top] = data;
}

char pop(Stack *stack) // 彈出 stack 中的元素
{
  if (stack->top == -1)
  {
    printf("Error: Stack underflow\n");
    return '\0';
  }
  char data = stack->arr[stack->top--];
  return data;
}

char top(Stack *stack) // 回傳 stack 頂端的元素
{
  if (stack->top == -1)
  {
    printf("Error: Stack is empty\n");
    return '\0';
  }
  return stack->arr[stack->top];
}

int isEmpty(Stack *stack) // 檢查 stack 是否為空
{
  return stack->top == -1;
}

int isFull(Stack *stack) // 檢查 stack 是否已滿
{
  return stack->top == MAXSIZE - 1;
}

void display(Stack *stack) // 顯示 stack 中的元素
{
  if (stack->top == -1)
  {
    printf("Stack is empty\n");
    return;
  }
  printf("Stack: ");
  for (int i = stack->top; i >= 0; i--)
  {
    printf("%c ", stack->arr[i]);
  }
  printf("\n");
}

// #define STACK_SIZE 100

// float stack[STACK_SIZE];
// int top = -1;
// float j;
// float a, b, c;

// void push(float item)
// {
//   if (top >= STACK_SIZE - 1)
//   {
//     printf("Stack Overflow\n");
//     exit(1);
//   }
//   else
//   {
//     top++;
//     stack[top] = item;
//   }
// }

// float pop()
// {
//   float item;

//   if (top < 0)
//   {
//     printf("Stack Underflow\n");
//     exit(1);
//   }
//   else
//   {
//     item = stack[top];
//     top--;
//     return item;
//   }
// }

// float evaluatePostfix(char *output)
// {
//   float operand1, operand2, result;
//   int i;

//   for (i = 0; i < strlen(output); i++)
//   {
//     char c = output[i];
//     if (isdigit(c))
//     {
//       push(c - '0');
//     }
//     else
//     {
//       operand2 = pop();
//       operand1 = pop();

//       switch (c)
//       {
//       case '+':
//         result = operand1 + operand2;
//         break;
//       case '-':
//         result = operand1 - operand2;
//         break;
//       case '*':
//         result = operand1 * operand2;
//         break;
//       case '/':
//         result = operand1 / operand2;
//         break;
//       case '%':
//         result = fmod(operand1, operand2);
//         break;
//       case '^':
//         a = operand1;
//         b = operand2;
//         c = a;
//         for (j = 1; j < b; j++)
//         {
//           c *= a;
//         }
//         result = c;
//         break;
//       default:
//         printf("Invalid operator\n");
//         exit(1);
//       }

//       push(result);
//     }
//   }

//   return pop();
// }

int main()
{
  Stack *Stack1 = createStack(); // 創建 stack

  // char output[STACK_SIZE] = "1.50.7%";
  // float result = evaluatePostfix(output);
  // printf("Result: %d\n", result);
  return 0;
}
