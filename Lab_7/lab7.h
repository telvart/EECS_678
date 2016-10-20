#ifndef LAB7_H
#define LAB7_H

typedef struct process
{
  int jobid;
  int arrivaltime;
  int priority;
} process;

int arrivalcompare(const void *, const void *);
int prioritycompare(const void*, const void *);
void printValues(struct process array[]);


#endif
