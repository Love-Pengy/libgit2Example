#include "git2/diff.h"
#include "git2/errors.h"
#include "git2/global.h"
#include "git2/repository.h"
#include "git2/types.h"
#include <stdio.h>
#include <stdlib.h>
/*#include "common.h"*/

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

  if (git_libgit2_init() < 0) {
    print_e("Init Failed");
    exit(EXIT_FAILURE);
  }

  if(git_repository_open_ext(&repo, ".", 0, NULL)){
    print_e("Open repo failed");
    exit(EXIT_FAILURE);
  };

  if (git_diff_index_to_workdir(&diff, repo, NULL, NULL)) {
    print_e("Diff Failed");
    exit(EXIT_FAILURE);
  }

  if (git_diff_get_stats(&stats, diff)) {
    print_e("Diff Get Stats Failed");
    exit(EXIT_FAILURE);
  };

  printf("STATS:\ninsert: %ld\ndeletions: %ld\n", git_diff_stats_insertions(stats),
         git_diff_stats_deletions(stats));

  git_diff_stats_free(stats);
  git_diff_free(diff);

  if (git_libgit2_shutdown() < 0) {
    
    print_e("Init Failed");
    exit(EXIT_FAILURE);
  }
  return 0;
}
