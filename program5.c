#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
        size_t size;         //stack
        int top;
        int* arr;
        }stack_t;



//creating a stack
  stack_t*  create(size_t size)
  {
    stack_t* stack = malloc(sizeof(stack_t));
    if (stack != NULL)
    {
      stack->size = size;
      stack->arr = calloc(size , sizeof(int));
      if (stack->arr != NULL)
      {
        stack->top = -1; // stack is empty
      }
      else
      {
      free(stack);
      stack = NULL;
      }
    }  return stack;
  }

  bool  isfull(stack_t* s)
  {
    if (s->top == s->size)
    {
       return true;
    }
    else
    {
       return false;
    }
  }


  int  isempty(stack_t* s)
  {
     if (s->top == -1)
     {
        return true;
     }
     else
     {
        return false;
     }
  }




  int  push(stack_t* s, int oprtr)
  {
    if (isfull(s))                  // is stack full?
    {
       return 0;
    }
    s->arr[++s->top]=oprtr;
    return 1;
  }


  int  pop(stack_t* s)
  {
    if (isempty(s))                // is stack empty
    {
      return 0;
    }
    return (s->arr[s->top--]);
  }


  int computer(stack_t* s1 , char op)
  {
    int second = pop(s1);
    int first  = pop(s1);

    switch (op) {
    case '^':
	    return (first^second);
    case '*':
        return (first*second);
    case '/':
        return (first/second);
    case '%':
        return (first%second);
    case '+':
        return (first+second);
    case '-':
        return (first-second);
   default :
        return 0;
  }
  }

int main()
{
    char postfix[50];
    char str[2];
    int d;

    printf("enter postfix exp:");
    scanf("%s",postfix);

    stack_t* s1 = create(strlen(postfix));

    for(size_t i=0;i<strlen(postfix);i++)
    {
      if(isdigit(postfix[i]))
      {
        str[0]=postfix[i];
        str[1]='\0';
        d=atoi(str);
        push(s1 , d);
      }
      else
      {
        int value = computer(s1 , postfix[i]);
        push(s1 , value);
      }

    }
    d= pop(s1);
    printf("the entered expression value is = %d\n",d);
    return 0;

    }
