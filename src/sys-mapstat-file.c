/*
 get the file's cache status in system cache, read more from 
 https://github.com/Feh/nocache
 arstercz - 20191210
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <getopt.h>

struct option_set {
  char  *file;
  int   quiet;
};
static struct option_set options;

void set_options(int argc, char *argv[]);
void usage(void);

void usage(void)
{
  fprintf(stderr, "\
Usage:\n\
  [options]:\n\
    -f  the file name to be get cache stat\n\
    -q  print nothing, only return code;\n\
    -h  help usage\n\n");
}

void set_options(int argc, char *argv[])
{
  int opt;

  options.quiet    = 0;

  char *opts = "qhf:";
  while((opt = getopt(argc, argv, opts)) != -1)
  {
    switch(opt)
    {
      case 'f':
        options.file  = optarg;
        break;
      case 'q':
        options.quiet = 1;
        break;
      case 'h':
        usage();
        exit(0);
      case '?':
        usage();
        exit(0);
    }
  }
}

int main (int argc, char *argv[]) 
{
  set_options(argc, argv);
  if (NULL == options.file) {
    fprintf(stderr, "the option file can't be empty!\n");
    usage();
    exit(1);
  }

  int pages;
  unsigned char *pageinfo = NULL;

  int PAGESIZE = getpagesize();
	
  int flags = O_RDONLY;
  int fd = open(options.file, flags);
  if (fd == -1) {
    fprintf(stderr, "Could not open file %s\n", options.file);
    exit(1);
  }

  struct stat fd_stat;
  if (fstat (fd, &fd_stat ) < 0 ) {
    fprintf(stderr, "Could not stat file %s\n", options.file);
    exit(1);
  }

  if (!S_ISREG(fd_stat.st_mode)) {
    fprintf(stderr, "%s is not a regular file\n", options.file);
    exit(1);
  }

  if (fd_stat.st_size == 0) {
    printf("page in cache: %d/%d (%.1f%%) [filesize=%.1fK, pagesize=%dK]\n",
           0, 0, 0.0, 0.0, PAGESIZE / 1024);
    return 0;
  }

  // use `PAGESIZE - 1` to ensure the right pages.
  pages = (fd_stat.st_size + (PAGESIZE - 1)) / PAGESIZE;
  pageinfo = calloc(sizeof(*pageinfo), pages);
  if (!pageinfo) {
    fprintf(stderr, "cann't calloc pageinfo\n");
    exit(1);
  }

  void *mapfile = NULL;
  mapfile = mmap(NULL, fd_stat.st_size, PROT_NONE, MAP_SHARED, fd, 0);
  if (mapfile == MAP_FAILED) {
    fprintf(stderr, "mmap error!\n");
    exit(1);
  }

  if (mincore(mapfile, fd_stat.st_size, pageinfo) == -1) {
    fprintf(stderr, "pageinfo is not resident in memory!\n");
    exit(1);
  }

  int i, j;
  i = j = 0;
  while(i < pages) {
    // page in cache
    if (pageinfo[i++] & 1) {
      j++;
    }
  }

  if (options.quiet) {
    return 0;
  }

  printf("page in cache: %d/%d (%.1f%%) [filesize=%.1fK, pagesize=%dK]\n",
         j, i, 100.0 * j / i, 1.0 * fd_stat.st_size / 1024, PAGESIZE / 1024);

  return 0;
}
