#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
        size_t size;         //stack
        int top;
        char* arr;
        }stack_t;

typedef struct precedence{
        char ch;
        int preced;
        }preced_t;

 preced_t array[] = {
                      {'^',3} , {'*',2} , {'/',2} , {'%',2} , {'+',1} , {'-',1}
                    };

//creating a stack
  stack_t*  create(size_t size)
  {
    stack_t* stack = malloc(sizeof(stack_t));
    if (stack != NULL)
    {
      stack->size = size;
      stack->arr = calloc(size , sizeof(char));
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




  int  push(stack_t* s, char oprtr)
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


int oprtr_priority(char ch)
{
    for(unsigned short int i=0 ; i< 6 ;i++)
    {
      if(ch == array[i].ch)
        return (array[i].preced);
    }
    return 0;
}



int main()
{
  char str[40];
  char ans[40];
  unsigned short int i,j;
  i=j=0;

  printf("please enter an expression:   ");
  scanf("%s",str);

  stack_t* s1=create(25);

  while(str[i]!='\0')
  {
    if(isalnum(str[i]))
    {
      ans[j++]=str[i++];
    }
    else if(str[i]=='(') {
      push(s1 , str[i++]);
    }
    else if(str[i]==')') {
      while(s1->arr[s1->top]!='(') {
        ans[j++]=pop(s1);
      }
      pop(s1);
      i++;
    }
    else {
      while((oprtr_priority(str[i]))<=(oprtr_priority(s1->arr[s1->top]))) {
        ans[j++]=pop(s1);
      }
      push(s1 , str[i++]);
    }
  }

  while(s1->top>=0) {
    ans[j++]=pop(s1);
  }

  ans[j]='\0';
  printf(" postfix is : %s\n",ans);
return 0;
}
