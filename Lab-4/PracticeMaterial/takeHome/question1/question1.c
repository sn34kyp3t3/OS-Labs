#include "question1.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{

  char filename[] = "input.txt";

  pid_t p2, p3, p4, p5, p6;

  printf("Root process: PID = %d, creating P2 and P3\n", getpid());

  if ((p2 = fork()) == 0)
  {
    printf("Process P2: PID = %d, creating P4 and P5\n", getpid());

    if ((p4 = fork()) == 0)
    {
      char buffer[MAX_LINE_LENGTH];
      read_line_from_file(filename, 0, buffer);
      printf("Process P4: PID = %d, read line: %s\n", getpid(), buffer);
      exit(0);
    }
    if ((p5 = fork()) == 0)
    {
      char buffer[MAX_LINE_LENGTH];
      read_line_from_file(filename, 1, buffer);
      printf("Process P5: PID = %d, read line: %s\n", getpid(), buffer);
      exit(0);
    }

    waitpid(p4, NULL, 0);
    waitpid(p5, NULL, 0);
    exit(0);
  }
  else if ((p3 = fork()) == 0)
  {
    printf("Process P3: PID = %d, creating P6 \n", getpid());

    if ((p6 = fork()) == 0)
    {
      char buffer[MAX_LINE_LENGTH];
      read_line_from_file(filename, 2, buffer);
      printf("Process P6: PID = %d, read line: %s\n", getpid(), buffer);
    }

    waitpid(p6, NULL, 0);
    exit(0);
  }

  waitpid(p2, NULL, 0);
  waitpid(p3, NULL, 0);

  printf("Root process printing lines\n");

  char buffer[MAX_LINE_LENGTH];
  FILE *f = fopen("input.txt", "r");
  if (f == NULL)
  {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  while (fgets(buffer, sizeof(buffer), f) != NULL)
  {
    printf("%s", buffer);
  }

  fclose(f);
  return 0;
}

void read_line_from_file(const char *filename, int line_number, char *buffer)
{

  int fd = open(filename, O_RDONLY);
  if (fd < 0)
  {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  off_t offset = 0;
  int current_line = 0;
  ssize_t bytes_read;
  while (current_line < line_number)
  {
    bytes_read = pread(fd, buffer, MAX_LINE_LENGTH - 1, offset);
    if (bytes_read <= 0)
    {
      close(fd);
      buffer[0] = '\0'; // In case of failure, ensure buffer is empty
      return;
    }

    buffer[bytes_read] = '\0'; // Null-terminate the buffer
    char *newline = strchr(buffer, '\n');
    if (newline)
    {
      offset += newline - buffer + 1;
      current_line++;
    }
    else
    {
      offset += bytes_read;
    }
  }

  bytes_read = pread(fd, buffer, MAX_LINE_LENGTH - 1, offset);
  if (bytes_read <= 0)
  {
    close(fd);
    buffer[0] = '\0'; // In case of failure, ensure buffer is empty
    return;
  }

  buffer[bytes_read] = '\0'; // Null-terminate the buffer
  char *newline = strchr(buffer, '\n');
  if (newline)
  {
    *newline = '\0'; // Remove newline character
  }

  close(fd);
}
