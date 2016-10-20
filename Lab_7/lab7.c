
#include <stdlib.h>
#include <stdio.h>
#include "lab7.h"

int arrivalcompare(const void *a, const void *b)
{
  struct process *p1 = (struct process *)a;
  struct process *p2 = (struct process *)b;
  return (p1->arrivaltime) - (p2->arrivaltime);

}

int prioritycompare(const void *a, const void *b)
{
  struct process *p1 = (struct process *)a;
  struct process *p2 = (struct process *)b;
  return (p2-> priority) - (p1->priority);
}

void printValues(struct process array[])
{
  printf(" ID    ArriveTime   Priority\n\n");
  for(int i = 0; i < 7; i++)
  {

    printf(" %d        %d            ", array[i].jobid, array[i].arrivaltime);
    if (array[i].arrivaltime < 10)
    {
      printf(" ");
    }
    printf("%d\n",array[i].priority);
  }
}

int main(int argc, char* argv[])
{

  struct process list[7] = {
    {5, 10, 3},
    {2, 4, 0},
    {7, 14, 0},
    {3, 6, 1},
    {1, 2, 1},
    {4, 8, 2},
    {6, 12, 3}
  };

  printf("\n Welcome to Tim's Lab 7!\n\n");
  printf(" Unsorted File: \n\n");
  printValues(list);


  printf("\n File sorted according to Arrival Times: \n\n");
  qsort(list, 7, sizeof(struct process), arrivalcompare);
  printValues(list);


  printf("\n File sorted according to Priorities: \n\n");
  qsort(list, 7, sizeof(struct process), prioritycompare);
  printValues(list);
  puts("\n");
  printf(" See you next time!\n\n");


  return 0;
}
































//Just here to add space
