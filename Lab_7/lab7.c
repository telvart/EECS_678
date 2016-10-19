
#include <stdlib.h>
#include <stdio.h>

/*
int myData[]={5, 2, 7, 3, 1, 4, 6,
              10, 4, 14, 6, 2, 8 ,12,
              3, 0, 0, 1, 1, 2, 3};

int pids[]= {5, 2, 7, 3, 1, 4, 6};
int arivaltimes[]= {10, 4, 14, 6, 2, 8, 12};
int priorities[]= {3, 0, 0, 1, 1, 2, 3};
*/

int theFile[3][7] = {
    {5, 2, 7, 3, 1, 4, 6} ,
    {10, 4, 14, 6, 2, 8, 12} ,
    {3, 0, 0, 1, 1, 2, 3}
};

int copy1[3][7] = {
    {5, 2, 7, 3, 1, 4, 6} ,
    {10, 4, 14, 6, 2, 8, 12} ,
    {3, 0, 0, 1, 1, 2, 3}
};

int copy2[3][7] = {
    {5, 2, 7, 3, 1, 4, 6} ,
    {10, 4, 14, 6, 2, 8, 12} ,
    {3, 0, 0, 1, 1, 2, 3}
};

struct process
{
  int jobid;
  int arrivaltime;
  int priority;
};

struct process list[7] = {
  {5, 10, 3},
  {2, 4, 0},
  {7, 14, 0},
  {3, 6, 1},
  {1, 2, 1},
  {4, 8, 2},
  {6, 12, 3}
};

int arrivalcompare(const void *a, const void *b)
{
  struct process *p1 = (struct process *)a;
  struct process *p2 = (struct process *)b;
  return (p1-> arrivaltime) - (p2->arrivaltime);

}

int prioritycompare(const void *a, const void *b)
{
  struct process *p1 = (struct process *)a;
  struct process *p2 = (struct process *)b;
  return (p2-> priority) - (p1->priority);
}

void printArray(int array[3][7])
{
  for (int i=0; i < 3; i++)
  {
    if (i == 0)
    {
      printf("PIDs: ");
    }
    else if (i == 1)
    {
      printf("Arrival Times: ");
    }
    else if (i == 2)
    {
      printf("Priorities: ");
    }
    printf("[");
    for(int j=0; j < 7; j++)
    {

      if ( j < 6)
      {
        printf("%d, ", array[i][j]);
      }
      else
      {
        printf("%d", array[i][j]);
      }
    }
    printf("]\n");
  }
  printf("\n");
}

int main(int argc, char* argv[])
{
  //printf("Hello world!\n");
  //qsort();
  puts("");
  printf("Welcome to Tim's Lab 7!\n\n");
  printf("Unsorted File: \n");
  printArray(theFile);

  //use this
  //http://stackoverflow.com/questions/13372688/sorting-members-of-structure-array


  size_t num_length = (sizeof(theFile))/(sizeof(int));
  qsort(&copy1[0][0], num_length, sizeof(int), arrivalcompare);
  qsort(&copy2[0][0], num_length, sizeof(int), prioritycompare);
  printf("\nFile sorted according to Arrival Times: \n\n");
  printArray(copy1);
  printf("\nFile sorted according to Priorities: \n\n");
  printArray(copy2);

  return 0;
}
































//Just here to add space
