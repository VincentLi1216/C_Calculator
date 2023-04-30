#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 1000000 // 設定最大的字串長度

char tokens[MAXSIZE][MAXSIZE]; // 輸入的中序運算式
char token[MAXSIZE];
char output[MAXSIZE]; // 轉換後的後序運算式
int convert_error = 0;

int op_hierarchy(char op); // 回傳運算子的優先權
void append(char op);      // 將運算子加入後序運算式的字串尾端

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

void infix2Postfix()
{
  char nowchar;
  Stack *opStack = createStack(); // 創建 stack
  char skip_char = ' ';

  for (int i = 0; i < strlen(token); i++)
  {
    nowchar = token[i];
    switch (op_hierarchy(nowchar))
    {
    case 0: // 運算元直接加入後序運算式
      append(nowchar);
      if (op_hierarchy(token[i + 1]) != 0 || i == strlen(token) - 1)
      {
        append(skip_char);
      }
      break;
    case 1: // 加減運算子的處理
      while (!isEmpty(opStack) && op_hierarchy(top(opStack)) >= op_hierarchy(nowchar) && top(opStack) != '(')
      {
        append(pop(opStack));
        append(skip_char);
      }
      push(opStack, nowchar);
      break;
    case 2: // 乘除餘運算子的處理
      while (!isEmpty(opStack) && op_hierarchy(top(opStack)) >= op_hierarchy(nowchar) && top(opStack) != '(')
      {
        append(pop(opStack));
        append(skip_char);
      }
      push(opStack, nowchar);
      break;
    case 3: // 乘除餘運算子的處理
      while (!isEmpty(opStack) && op_hierarchy(top(opStack)) >= op_hierarchy(nowchar) && top(opStack) != '(')
      {
        append(pop(opStack));
        append(skip_char);
      }
      push(opStack, nowchar);
      break;
    case 4: // 左括號的處理
      push(opStack, nowchar);
      break;
    case 5: // 右括號的處理
      while (!isEmpty(opStack) && top(opStack) != '(')
      {
        append(pop(opStack));
        append(skip_char);
      }
      if (!isEmpty(opStack) && top(opStack) == '(')
      {
        pop(opStack);
      }
      else
      {
        printf("Error: Mismatched parentheses\n");
        return;
      }
      break;
    default:
      printf("Error: Invalid input\n");
      return;
    }
  }

  // 把 stack 中剩下的運算子加入後序運算式
  while (!isEmpty(opStack))
  {
    if (top(opStack) == '(' || top(opStack) == ')')
    {
      printf("Error: Mismatched parentheses\n");
      return;
    }
    append(pop(opStack));
    append(skip_char);
  }

  output[strlen(output) - 1] = '\0';
}

int op_hierarchy(char op)
{
  switch (op)
  {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
  case '%':
    return 2;
  case '^':
    return 3;
  case '(':
    return 4;
  case ')':
    return 5;
  default:
    return 0;
  }
}

void append(char op)
{
  if (op == '\n' || op == '\0') // 跳過換行與結束符號
  {
    return;
  }
  if (op == '/' && output[strlen(output) - 2] == '0') // 偵測除以零錯誤，若有的話那raise全域變數conver_error
  {
    strcpy(output, "!DivisionbyZeroException! ");
    convert_error = 1;
  }
  if (convert_error) // 如果先前有錯誤訊息，那麼不會再繼續加入字元到output陣列裡
  {
    return;
  }
  int len = strlen(output);
  output[len] = op;
  output[len + 1] = '\0';
}

int main()
{
  int line_num;
  printf("How many lines of calculation are needed: ");
  scanf("%d", &line_num);
  printf("Please enter an infix expression: \n");
  for (int i = 0; i < line_num; i++)
  {
    printf("->");
    scanf("%s", tokens[i]);
  }
  // fgets(token, MAXSIZE, stdin);
  for (int i = 0; i < line_num; i++)
  {
    strcpy(output, "");
    strcpy(token, tokens[i]);
    convert_error = 0;
    infix2Postfix();
    printf("Postfix expression: %s\n", output);
    strcpy(tokens[i], output);
  }
  for (int i = 0; i < line_num; i++)
  {
    printf("token:%s\n", tokens[i]);
  }
  return 0;
}