#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXSIZE 100000 // 設定最大的字串長度

char tokens[MAXSIZE][MAXSIZE]; // 輸入的中序運算式
char token[MAXSIZE];
char output[MAXSIZE]; // 轉換後的後序運算式
int convert_error = 0;
int eval_error = 0;

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

void push(Stack *stack, char data) // pust元素到 stack 中
{
  if (stack->top == MAXSIZE - 1)
  {
    printf("Error: Stack overflow\n");
    return;
  }
  stack->arr[++stack->top] = data;
}

char pop(Stack *stack) // pop stack 中的元素
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

/* 給double Stack用的函式 */

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

void infix2Postfix() // 將infix式子轉成postfix式子
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
      { // 括號不對稱錯誤
        append('(');
        return;
      }
      break;
    default: // 錯誤輸入
      // printf("Error: Invalid input\n");
      append('!');
      return;
    }
  }

  // 把 stack 中剩下的運算子加入後序運算式
  while (!isEmpty(opStack))
  {
    if (top(opStack) == '(' || top(opStack) == ')')
    {
      // printf("Error: Mismatched parentheses\n");
      append('(');
      return;
    }
    append(pop(opStack));
    append(skip_char);
  }

  output[strlen(output) - 1] = '\0';
}

double evaluation() // 計算postfix式子
{
  dStack d_Stack;
  d_init(&d_Stack);
  int i = 0;
  double total = 0;
  double result;
  int decimal_places = 0;
  bool isDecimal = false;

  while (eval_error == 0 && token[i] != '\0' && token[i] != '\n' && i < strlen(token))
  {
    char nowchar = token[i];
    if (nowchar == '!') // 當token存在錯誤時
    {
      eval_error = 1;
      return 0.0;
    }
    if (isdigit(nowchar) || nowchar == '.') // 數字push到d_Stack裡
    {
      while (nowchar != ' ' && nowchar != '\0' && nowchar != '\n')
      {
        if (isdigit(nowchar)) // 整數以上處理
        {
          if (!isDecimal)
          {
            total *= 10;
            total += nowchar - '0';
          }
          else // 小數位處理
          {
            decimal_places++;
            total = total + ((nowchar - '0') / pow(10, decimal_places));
          }
        }
        else if (nowchar == '.') // 小數點
        {
          isDecimal = true;
        }
        i++;
        nowchar = token[i];
      }
      d_push(&d_Stack, total);
      // 重設變數
      total = 0;
      decimal_places = 0;
      isDecimal = false;
    }
    else if (nowchar == ' ') // 空格
    {
      i++;
    }
    else // 計算運算子
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

  return result;
}

int op_hierarchy(char op) // 定義運算子優先順序
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

void append(char op) // 加入output最後面
{
  if (op == '\n' || op == '\0') // 跳過換行與結束符號
  {
    return;
  }
  if (op == '/' && output[strlen(output) - 2] == '0') // 偵測除以零錯誤，若有的話那raise全域變數conver_error
  {
    strcpy(output, "!DivisionByZeroException! ");
    convert_error = 1;
  }
  if (op == '%' && output[strlen(output) - 2] == '0') // 偵測餘數零錯誤，若有的話那raise全域變數conver_error
  {
    strcpy(output, "!ModuloByZeroException! ");
    convert_error = 1;
  }
  if (op == '(') // 偵測括號不對稱錯誤，若有的話那raise全域變數conver_error
  {
    strcpy(output, "!MismatchParenthesesException! ");
    convert_error = 1;
  }
  if (op == '!' || !isdigit(op)) // 偵測錯誤輸入錯誤，若有的話那raise全域變數conver_error
  {
    if (op != '+' && op != '-' && op != '*' && op != '/' && op != '^' && op != '%' && op != '(' && op != ')' && op != ' ')
    {
      strcpy(output, "!InvalidInputException! ");
      convert_error = 1;
    }
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
  printf("How many lines of calculation are needed: "); // 請使用者輸入有幾行運算式
  scanf("%d", &line_num);
  printf("Please enter an infix expression: \n");
  for (int i = 0; i < line_num; i++) // 使用者輸入運算式
  {
    printf("->");
    scanf("%s", tokens[i]);
  }

  for (int i = 0; i < line_num; i++) // 將每個運算式從infix轉成postfix
  {
    strcpy(output, "");
    strcpy(token, tokens[i]);
    convert_error = 0;
    infix2Postfix();
    printf("Postfix expression: %s\n", output);
    strcpy(tokens[i], output);
  }
  printf("\n\n---Final Result---\n");

  for (int i = 0; i < line_num; i++) // 將計算每個運算式並輸出結果
  {
    eval_error = 0;
    strcpy(token, tokens[i]);
    double result = evaluation();
    if (eval_error)
    {
      printf("->%s\n", token);
    }
    else
    {
      printf("->%.10lf\n", evaluation());
    }
  }

  return 0;
}