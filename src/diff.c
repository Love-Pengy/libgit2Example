#include "git2.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void print_e(const char *message) {
  const git_error *e = git_error_last();
  fprintf(stderr, "%s: [%d] %s", message, e->klass, e->message);
}

// quick library existance verification
/*int main() {*/
/*    if (0 > git_libgit2_init()) {*/
/*        check_error("git_libgit2_init");*/
/*    }*/
/*    printf("init success\n");*/
/**/
/*    if (0 > git_libgit2_shutdown()) {*/
/*        check_error("git_libgit2_shutdown");*/
/*    }*/
/*    printf("shutdown success\n");*/
/*    return 0;*/
/*}*/

int main() {
  git_diff *diff = NULL;
  git_repository *repo = NULL;
  git_diff_stats *stats = NULL;

  assert(git_libgit2_init() >= 0);

  assert(git_repository_open(&repo, "/home/bee/Projects/git-stats") == 0);

  assert(git_diff_index_to_workdir(&diff, repo, NULL, NULL) == 0);

  assert(git_diff_get_stats(&stats, diff) == 0);

  printf("STATS:\n\tinsert %ld\n\tdeletions %ld\n",
         git_diff_stats_insertions(stats), git_diff_stats_deletions(stats));

  git_diff_stats_free(stats);
  git_diff_free(diff);
  git_repository_free(repo);

  assert(git_libgit2_shutdown() == 0);

  return 0;
}
