/*
 unmap a file from file system cache, read more from 
 https://github.com/yoshinorim/unmap_mysql_logs
 arstercz - 20190610
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <getopt.h>

struct option_set {
  char  *file;
  int   factor;
  int   sync;
};
static struct option_set options;

void set_options(int argc, char *argv[]);
void usage(void);

void usage(void)
{
  fprintf(stderr, "\
Usage:\n\
  [options]:\n\
    -n  factors to unmap the file in cache, \n\
        90 mean reserve 10%% in cache, default is 100\n\
    -f  the file name to be unmapped;\n\
    -s  whether invoke fdatasync() before unmap;\n\
    -h  help usage,\n\n");
}

void set_options(int argc, char *argv[])
{
  int opt;

  options.factor  = 100;
  options.sync    = 0;

  char *opts = "shf:n:";
  while((opt = getopt(argc, argv, opts)) != -1)
  {
    switch(opt)
    {
      case 'n':
        options.factor  = atoi(optarg);
        break;
      case 'f':
        options.file    = optarg;
        break;
      case 's':
        options.sync    = 1;
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
    exit(1);
  }
	
  int flags = O_RDONLY;
  int fd = open(options.file, flags);
  if ( fd == -1 ) {
    fprintf(stderr, "Could not open file %s\n", options.file);
    exit(1);
  }

  struct stat fd_stat;
  if (fstat (fd, &fd_stat ) < 0 ) {
    fprintf(stderr, "Could not stat file %s\n", options.file);
    exit(1);
  }

  if (options.sync) {
    fdatasync(fd);
  }

  loff_t offset = 0;
  loff_t length = fd_stat.st_size;

  int result 
     = posix_fadvise(fd, offset, (int)(options.factor * length / 100), POSIX_FADV_DONTNEED);

  if (result != 0){
    fprintf(stderr, "Could not set POSIX_FADV_DONTNEED for file %s\n", options.file);
  }
  close(fd);
  return 0;
}
