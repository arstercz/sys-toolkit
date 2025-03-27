/*
 delete a file slowly, useful to delete big file
 arstercz - 20250327
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#ifndef HAVE_FALLOCATE
# include <sys/syscall.h>
#endif

struct option_set {
  char  *file;
  loff_t   length;
  loff_t   offset;
};
static struct option_set options;

void set_options(int argc, char *argv[]);
void usage(void);

void usage(void)
{
  fprintf(stderr, "\
Usage:\n\
  [options]:\n\
    -o  offset for range operations, in bytes. default: 0;\n\
    -l  length for range operations, in bytes. default: 1048576(1MB)\n\
    -f  the file name to be unmapped;\n\
    -h  help usage,\n\n");
}

static loff_t cvtnum(char *s)
{
	int x;

	x = strtosize(s);
    if (x < 0)
		return -1LL;
	
	return x;
}

int strtosize(char *str)
{
  int file_size = 0;
  int arg_len = strlen(str);
  if (arg_len > 20) {
      printf("the input size is not supported %s, please use B,K,M,G\n", str);
  }

  char *pEnd, dim;
  if (str[arg_len - 1] < '0' || str[arg_len - 1] > '9') {
      dim = str[arg_len - 1];
  }
  else
      dim = 'B';
  dim = tolower(dim);

  file_size = strtol(str, &pEnd, 10);

  switch (dim) {
      case 'b':
          break;
      case 'k':
          file_size <<= 10;
          break;
      case 'm':
          file_size <<= 20;
          break;
      case 'g':
          file_size <<= 30;
          break;
      default:
          printf("Wrong units: %c\n", dim);
          return -1;
  }

  return file_size;
}

void set_options(int argc, char *argv[])
{
  int opt;

  options.length  = 1048576; // 1MB
  options.offset    = 0;

  char *opts = "hf:l:o:";
  while((opt = getopt(argc, argv, opts)) != -1)
  {
    switch(opt)
    {
      case 'l':
        options.length  = cvtnum(optarg);
        break;
      case 'o':
        options.offset  = cvtnum(optarg);
        break;
      case 'f':
        options.file    = optarg;
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

  int error;

  /*
    FALLOC_FL_COLLAPSE_RANGE  - 0x08
    * Different filesystems may implement different limitations on the
    * granularity of the operation. Most will limit operations to
    * filesystem block size boundaries, but this boundary may be larger or
    * smaller depending on the filesystem and/or the configuration of the
    * filesystem or file.

    so the offset and length option must be multiple 4096 bytes. such as 0, 4k, 1m...
  */
  int mode = 0x08; //as we just want truncate from begin to end;
  int flags = O_WRONLY;

  int fd = open(options.file, flags);
  if ( fd == -1 ) {
    fprintf(stderr, "Could not open file %s\n", options.file);
    exit(1);
  }

  if (options.length <= 0) {
    fprintf(stderr, "invalid length value specified\n");
  }

  if (options.offset < 0) {
    fprintf(stderr, "invalid offset value specified\n");
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

  if (options.length > fd_stat.st_size) {
    fprintf(stderr, "%s is small(%d bytes), option length too big\n", options.file, fd_stat.st_size);
  }

#ifdef HAVE_FALLOCATE
  error = fallocate(fd, mode, options.offset, options.length);
#else
  error = syscall(SYS_fallocate, fd, mode, options.offset, options.length);
#endif

  if (error != 0){
    fprintf(stderr, "Could fallocate(truncate) for file %s\n", options.file);
  }
  close(fd);
  return 0;
}
