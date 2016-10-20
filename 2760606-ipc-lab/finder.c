#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <errno.h>
#include <sys/wait.h>

#define BSIZE 256

#define BASH_EXEC  "/bin/bash"
#define FIND_EXEC  "/bin/find"
#define XARGS_EXEC "/usr/bin/xargs"
#define GREP_EXEC  "/bin/grep"
#define SORT_EXEC  "/bin/sort"
#define HEAD_EXEC  "/usr/bin/head"

int main(int argc, char *argv[])
{
  int status;
  pid_t pid_1, pid_2, pid_3, pid_4;

  //creating pipes
  int pipefd[6];
  if (pipe(pipefd) == -1 || pipe(pipefd+2) == -1 || pipe(pipefd+4) == -1)
  {
    perror("Error creating pipes");
    exit(EXIT_FAILURE);
  }

  if (argc != 4) {
    printf("usage: finder DIR STR NUM_FILES\n");
    exit(0);
  }

  pid_1 = fork();
  if (pid_1 == 0) {
    /* First Child */

    //replace find's std::out with write end of first pipe
    dup2(pipefd[1],1);

    close(pipefd[0]);
    close(pipefd[2]);
    close(pipefd[3]);
    close(pipefd[4]);
    close(pipefd[5]);

    execl(FIND_EXEC, FIND_EXEC, "-name", "*.[ch]", (char*) 0);

    exit(0);
  }

  pid_2 = fork();
  if (pid_2 == 0) {
    /* Second Child */

    //replace grep's std::in with read end of first pipe
    dup2(pipefd[0], 0);
    //replace greps std::out with write end of second pipe
    dup2(pipefd[3], 1);

    close(pipefd[1]);
    close(pipefd[2]);
    close(pipefd[4]);
    close(pipefd[5]);

    execl(GREP_EXEC, GREP_EXEC, "-c", "$2", (char*) 0);

    exit(0);
  }

  pid_3 = fork();
  if (pid_3 == 0) {
    /* Third Child */

    //replace sort's std::in with read end of second pipe
    dup2(pipefd[2], 0);
    //replace sort's std::out with write end of third pipe
    dup2(pipefd[5], 1);

    close(pipefd[0]);
    close(pipefd[1]);
    close(pipefd[3]);
    close(pipefd[4]);

    execl(SORT_EXEC, SORT_EXEC, "-t", ":", "+1.0", "-2.0", "--numeric", "--reverse", (char*) 0);

    exit(0);
  }

  pid_4 = fork();
  if (pid_4 == 0) {
    /* Fourth Child */

    //replace head's std::in with read end of third pipe
    dup2(pipefd[4], 0);

    close(pipefd[0]);
    close(pipefd[1]);
    close(pipefd[2]);
    close(pipefd[3]);
    close(pipefd[5]);

    execl(HEAD_EXEC, HEAD_EXEC, "--lines=$3", (char*) 0);

    exit(0);
  }


  if ((waitpid(pid_1, &status, 0)) == -1) {
    fprintf(stderr, "Process 1 encountered an error. ERROR%d", errno);
    return EXIT_FAILURE;
  }
  if ((waitpid(pid_2, &status, 0)) == -1) {
    fprintf(stderr, "Process 2 encountered an error. ERROR%d", errno);
    return EXIT_FAILURE;
  }
  if ((waitpid(pid_3, &status, 0)) == -1) {
    fprintf(stderr, "Process 3 encountered an error. ERROR%d", errno);
    return EXIT_FAILURE;
  }
  if ((waitpid(pid_4, &status, 0)) == -1) {
    fprintf(stderr, "Process 4 encountered an error. ERROR%d", errno);
    return EXIT_FAILURE;
  }

  return 0;
}
