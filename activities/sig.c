#define _POSIX_C_SOURCE 1
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void handle_sight(int);

static char *buffer = "CTRL-C pressed.\n";

void handle_sigint(int signum) { write(STDOUT_FILENO, buffer, strlen(buffer)); }

int main() {
  pid_t pid;
  pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid) {
    struct sigaction handler;
    handler.sa_handler = handle_sight;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGINT, &handler, NULL);

    while (1) {
      sleep(5);
    }
  } else {
    if (kill(getppid(), SIGINT) == -1) {
      perror("kill");
      exit(EXIT_FAILURE);
    }
  }
}
