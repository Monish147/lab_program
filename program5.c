#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
        size_t size;         //stack
        int top;
        int* arr;
        }stack_t;

//--------------------------------------------------------------

typedef enum Menu {CH_EXIT, CH_POSTFIX_EVAL, CH_TOWER_OF_HANOI
                  } menu_t;
//CH_EXIT - 0, CH_POSTFIX_EVAL - 1, CH_TOWER_OF_HANOI - 2

//-------------------------------------------------------------

//menu that asks for input until a valid choice is entered
menu_t menu() {
  menu_t choice = CH_TOWER_OF_HANOI;
  do {
    printf("Enter your menu choice:\n");
    printf("%u for Postfix expression evaluation\n", CH_POSTFIX_EVAL);
    printf("%u for Tower of Hanoi solution\n", CH_TOWER_OF_HANOI);
    printf("%u for Exit.\n", CH_EXIT);
    scanf("%u", & choice);
  } while (choice >CH_TOWER_OF_HANOI);

  return choice;
}
//-------------------------------------------------------------

//creating a stack for postfix evaluation
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


  bool  isempty(stack_t* s)
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




void fn_exit() {
  exit(0);
}


int postfix_evaluation()
{
    char postfix[50];
    char str[2];
    int ans;

    printf("enter postfix exp:");
    scanf("%s",postfix);

    stack_t* s1 = create(strlen(postfix));

    for(size_t i=0;i<strlen(postfix);i++)
    {
      if(isdigit(postfix[i]))
      {
        str[0]=postfix[i];
        str[1]='\0';
        //since atoi will accept string as its parameter
        // we put a single character in the srting
        ans=atoi(str);//converting character to integer
        push(s1 , ans);
      }
      else
      {
        int value = computer(s1 , postfix[i]);
        push(s1 , value);
      }

    }
    //the answer for the postfix expression will be in the stack so we pop at the last
    ans = pop(s1);
    printf("the entered expression value is = %d\n",ans);
    free(s1);
    return 0;
}

//----------------------------------------------------------------

//this function prints gives moves the user has to follow to solve tower of Hanoi
void TowerofHanoi(int n,int t1,int t2,int t3)
{
  if(n>0){
    TowerofHanoi(n-1,t1,t3,t2);
    printf("  move a disc from tower-%d to tower-%d\n",t1,t3);
    TowerofHanoi(n-1,t2,t1,t3);
  }
}


int main()
{
  int choice;
  //until the user enters exit option continue  the program
  while(1)
  {
    choice = menu();
    if(choice==1)
    {
      //call postfix evaluation function
      postfix_evaluation();
    }
    else if(choice==2){
      //call tower of haonoi function
      int N,t1,t2,t3;
      printf("enter the sourse tower and the destination tower:");
      scanf("%d %d",&t1,&t3);
      printf("enter the number of disks in tower-%d :",t1);
      scanf("%d",&N);
      t2=6-t1-t3;
      TowerofHanoi(N,t1,t2,t3);
    }
    else{
      //choice is 0 so call exit function
      fn_exit();
    }
  }
   return 0;
}
