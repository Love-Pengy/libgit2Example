#include "git2.h"
#include <assert.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_e(const char *message) {
  const git_error *e = git_error_last();
  fprintf(stderr, "%s: [%d] %s", message, e->klass, e->message);
}

int main(void) {

  char path[256] = {0};

  assert(git_libgit2_init() >= 0);

  git_diff *diff = NULL;
  git_repository *repo = NULL;
  git_diff_stats *stats = NULL;

  snprintf(path, strlen(getenv("HOME")) + 24, "%s%s", getenv("HOME"),
           "/Projects/study-tracker");

  assert(git_repository_open(&repo, path) == 0);

  git_diff_options opts;
  assert(!git_diff_options_init(&opts, GIT_DIFF_OPTIONS_VERSION));

  opts.flags |= GIT_DIFF_SHOW_UNTRACKED_CONTENT;
  opts.flags |= GIT_DIFF_RECURSE_UNTRACKED_DIRS;
  opts.flags |= GIT_DIFF_IGNORE_WHITESPACE;

  assert(git_diff_index_to_workdir(&diff, repo, NULL, &opts) == 0);

  assert(git_diff_get_stats(&stats, diff) == 0);

  printf("[INSERTIONS] %ld\n", git_diff_stats_insertions(stats));
  printf("[DELETIONS] %ld\n", git_diff_stats_deletions(stats));

  git_diff_stats_free(stats);
  git_diff_free(diff);

  assert(git_libgit2_shutdown() >= 0);

  printf("\nExited Succesfully\n");
  return 0;

}
