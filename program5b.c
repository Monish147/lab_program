/*
*tower of HANOI for N disks
*/


#include <stdio.h>
#include <stdlib.h>


void TowerofHanoi(int n,int t1,int t2,int t3)
{
  if(n>0){
    TowerofHanoi(n-1,t1,t3,t2);
    printf("  move a disc from tower-%d to tower-%d\n",t1,t3);
    TowerofHanoi(n-1,t2,t1,t3);
  }
}


void main()
{
  int N,t1,t2,t3;
  printf("enter the sourse tower and the destination tower:");
  scanf("%d %d",&t1,&t3);
  printf("enter the number of disks in tower-%d :",t1);
  scanf("%d",&N);
  t2=6-t1-t3;
  TowerofHanoi(N,t1,t2,t3);
}
