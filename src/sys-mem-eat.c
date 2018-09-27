#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <getopt.h>

#define N 1024*1024
#define STEP_OPTION     'a'
#define MAX_OPTION      'b'
#define INTERVAL_OPTION 'c'
#define VERBOSE_OPTION  'd'
#define HELP_OPTION     'e'

char* get_current_time(void);
void set_options(int argc, char *argv[]);
void print_usage(void);

struct struct_options {
  int step;
  int max;
  int interval;
  int verbose;
};

struct struct_options options;

static struct option long_options[] = {
  { "step",    required_argument, NULL, STEP_OPTION },
  { "max",     required_argument, NULL, MAX_OPTION },
  { "interval",required_argument, NULL, MAX_OPTION },
  { "verbose", no_argument,       NULL, VERBOSE_OPTION},
  { "help",    no_argument,       NULL, HELP_OPTION },
  { 0, 0, 0, 0 }
};


int main(int argc, char** argv) {
  set_options(argc, argv);

  int mb = 0;
  char* buffer;

  if (options.verbose) {
    printf("[verbose] allocated max memory: %d MB, step size: %d\n\n", 
           options.max, options.step);
  }
  if ((options.max > -1) 
       && (options.max < options.step)) {
    fprintf(stderr, "error: step size can not less then max size, skip ...\n");
    exit(0);
  }
  while((buffer=malloc(N * options.step)) != NULL 
         && mb < options.max) {
    memset(buffer, 0, N * options.step);
    mb += options.step;
    printf("[%s] allocated %d MB\n", get_current_time(), mb);
    sleep(options.interval);
  }      
  return 0;
}

void set_options(int argc, char *argv[])
{
  int opt;
  int index;

  options.step     = 10;
  options.max      = 100000;
  options.interval = 2;

  do
  {
    opt = getopt_long(argc, argv, "", long_options, &index);
    switch (opt)
    {
      case STEP_OPTION:
      {
        options.step = atoi(optarg);
        break;
      }
      case MAX_OPTION:
      {
        options.max = atoi(optarg);
        break;
      }
      case INTERVAL_OPTION:
      {
        options.interval = atoi(optarg);
      }
      case HELP_OPTION:
      {
        print_usage();
        exit(0);
      }
      case VERBOSE_OPTION:
      {
        options.verbose = 1;
        break;
      }
      case '?':
      {
        print_usage();
        exit(0);
      }
    } 
  }
  while (opt != -1);
}

char *get_current_time(void)
{
  static char date_str[20];
  time_t date;

  time(&date);
  strftime(date_str, 
           sizeof(date_str), "%Y-%m-%d %H:%M:%S", localtime(&date));

  return date_str;
}

void print_usage(void)
{
  fprintf(stderr, "\
Usage:\n\
  [options]:\n\
    --step     step size(MB) to be allocate every once, default is 10 MB.\n\
    --max      max size(MB) to be allocated, default is 100000 MB.\n\
    --interval sleep time between allocated memory. default is 2(seconds)\n\
    --help     help usage.\n\
    --verbose  print verbose message\n\n");
}
