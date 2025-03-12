#include "git2.h"
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static bool cont = true;
static void quitter(int signum) {
  if (signum == SIGINT) {
    cont = false;
  }
}
void print_e(const char *);

void *printDeleted(void *repoDir) {
  git_diff *diff = NULL;
  git_repository *repo = NULL;
  git_diff_stats *stats = NULL;

  if (git_repository_open_ext(&repo, repoDir, 0, NULL)) {
    print_e("Open repo failed");
    exit(EXIT_FAILURE);
  }

  while (cont) {

    if (git_diff_index_to_workdir(&diff, repo, NULL, NULL)) {
      print_e("Diff Failed");
      exit(EXIT_FAILURE);
    }
    if (git_diff_get_stats(&stats, diff)) {
      print_e("Diff Get Stats Failed");
      exit(EXIT_FAILURE);
    }

    printf("[DELETIONS] %ld\n", git_diff_stats_deletions(stats));

    sleep(1);
  }

  git_diff_stats_free(stats);
  git_diff_free(diff);
  pthread_exit(NULL);
}

void *printInserted(void *repoDir) {
  git_diff *diff = NULL;
  git_repository *repo = NULL;
  git_diff_stats *stats = NULL;

  if (git_repository_open_ext(&repo, repoDir, 0, NULL)) {
    print_e("Open repo failed");
    exit(EXIT_FAILURE);
  }

  while (cont) {
    if (git_diff_index_to_workdir(&diff, repo, NULL, NULL)) {
      print_e("Diff Failed");
      exit(EXIT_FAILURE);
    }

    if (git_diff_get_stats(&stats, diff)) {
      print_e("Diff Get Stats Failed");
      exit(EXIT_FAILURE);
    }

    printf("[INSERTIONS] %ld\n", git_diff_stats_insertions(stats));
    sleep(1);
  }

  git_diff_stats_free(stats);
  git_diff_free(diff);
  pthread_exit(NULL);
}

int main(void) {
  pthread_t untrackedThread, trackedThread;

  struct sigaction sa;
  sa.sa_handler = quitter;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if (sigaction(SIGINT, &sa, NULL) == -1) {
    printf("sigaction failed");
    exit(EXIT_FAILURE);
  }
  if (git_libgit2_init() < 0) {
    print_e("Init Failed");
    exit(EXIT_FAILURE);
  }

  pthread_create(&untrackedThread, NULL, printDeleted,
                 (void *)"/home/bee/Projects/git-stats");
  pthread_create(&trackedThread, NULL, printInserted,
                 (void *)"/home/bee/Projects/git-stats");

  pthread_join(untrackedThread, NULL);
  pthread_join(trackedThread, NULL);

  if (git_libgit2_shutdown() < 0) {

    print_e("Init Failed");
    exit(EXIT_FAILURE);
  }
  printf("\nExited Succesfully\n");
  return 0;
}

void print_e(const char *message) {
  const git_error *e = git_error_last();
  fprintf(stderr, "%s: [%d] %s", message, e->klass, e->message);
}
