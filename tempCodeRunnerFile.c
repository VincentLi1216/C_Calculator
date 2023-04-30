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

float evaluatePostfix(char *output)
{
  float operand1, operand2, result;
  int i;

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
        result = fmod(operand1, operand2);
        break;
      case '^':
        a = operand1;
        b = operand2;
        c = a;
        for (j = 1; j < b; j++)
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
