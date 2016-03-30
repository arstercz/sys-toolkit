/*
  A simple TCP port forwarder.
  this tool fork from tcptunnel, remove windows feature.
  https://github.com/vakuum/tcptunnel

  zhe.chen<chenzhe07@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define VERSION "0.1"
#define LOCAL_PORT_OPTION   'a'
#define REMOTE_PORT_OPTION  'b'
#define REMOTE_HOST_OPTION  'c'
#define BIND_ADDRESS_OPTION 'd'
#define BUFFER_SIZE_OPTION  'e'
#define FORK_OPTION         'f'
#define LOG_OPTION          'g'
#define STAY_ALIVE_OPTION   'h'
#define HELP_OPTION         'i'
#define VERSION_OPTION      'j'

#define PATH_SEPARATOR '/'

const char *name;

int build_server(void);
int wait_for_clients(void);
void handle_client(void);
void handle_tunnel(void);
int build_tunnel(void);
int use_tunnel(void);
int fd(void);

void set_options(int argc, char *argv[]);
void set_option(char **option, char *value);

char *get_current_timestamp(void);

void print_help(void);
void print_helpinfo(void);
void print_usage(void);
void print_version(void);
void print_missing(const char *message);

struct struct_settings {
	unsigned int local_port   : 1;
	unsigned int remote_host  : 1;
	unsigned int remote_port  : 1;
	unsigned int bind_address : 1;
	unsigned int buffer_size  : 1;
	unsigned int fork         : 1;
	unsigned int log          : 1;
	unsigned int stay_alive   : 1;
};

struct struct_options {
	char *local_port;
	char *remote_host;
	char *remote_port;
	char *bind_address;
	unsigned int buffer_size;
};

struct struct_rc {
	int server_socket;
	int client_socket;
	int remote_socket;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	struct sockaddr_in remote_addr;
	struct hostent *remote_host;
};

struct struct_rc rc;
struct struct_options options;
struct struct_settings settings = {0 ,0 ,0, 0, 0, 0, 0, 0};

static struct option long_options[] = {
	{ "local-port",    required_argument, NULL, LOCAL_PORT_OPTION },
	{ "remote-host",   required_argument, NULL, REMOTE_HOST_OPTION },
	{ "remote-port",   required_argument, NULL, REMOTE_PORT_OPTION },
	{ "bind-address",  required_argument, NULL, BIND_ADDRESS_OPTION },
	{ "buffer-size",   required_argument, NULL, BUFFER_SIZE_OPTION },
        { "fork",          no_argument,       NULL, FORK_OPTION},
	{ "log",           no_argument,       NULL, LOG_OPTION },
	{ "stay-alive",    no_argument,       NULL, STAY_ALIVE_OPTION },
	{ "help",          no_argument,       NULL, HELP_OPTION },
	{ "version",       no_argument,       NULL, VERSION_OPTION },
	{ 0, 0, 0, 0 }
};

int main(int argc, char *argv[])
{
   name = argv[0];
   set_options(argc, argv);

   if (build_server() == 1)
   {
      exit(1);
   }

   do
   {
       if (wait_for_clients() == 0)
       {
           handle_client();
       }
   }
   while (settings.stay_alive);

   close(rc.server_socket);
   return 0;
}

void set_options(int argc, char *argv[])
{
   int opt;
   int index;

   options.buffer_size = 4096;

   do
   {
      opt = getopt_long(argc, argv, "", long_options, &index);
      switch (opt)
      {
          case LOCAL_PORT_OPTION:
          {
             options.local_port = optarg;
             settings.local_port = 1;
             break;
          }

          case REMOTE_PORT_OPTION:
          {
             options.remote_port = optarg;
             settings.remote_port = 1;
             break;
          }

          case REMOTE_HOST_OPTION:
          {
             options.remote_host = optarg;
             settings.remote_host = 1;
             break;
          }

          case BIND_ADDRESS_OPTION:
          {
             options.bind_address = optarg;
             settings.bind_address = 1;
             break;
          }

          case BUFFER_SIZE_OPTION:
          {
             options.buffer_size = atoi(optarg);
             settings.buffer_size = 1;
             break;
          }

          case FORK_OPTION:
          {
             settings.fork = 1;
             settings.stay_alive = 1;
             break;
          }

          case LOG_OPTION:
          {
             settings.log = 1;
             break;
          }

          case STAY_ALIVE_OPTION:
          {
             settings.stay_alive = 1;
             break;
          }

          case HELP_OPTION:
          {
             print_usage();
             print_help();
             exit(0);
          }

          case VERSION_OPTION:
          {
             print_version();
             exit(0);
          }

          case '?':
          {
             print_usage();
             print_helpinfo();
             exit(0);
          }
      }
   }
   while (opt != -1);

   if (!settings.local_port)
   {
       print_missing("missing '--local-port=' option.");
       exit(1);
   }

   if (!settings.remote_port)
   {
       print_missing("missing '--remote-port=' option.");
       exit(1);
   }

   if (!settings.remote_host)
   {
       print_missing("missing '--remote-host=' option.");
       exit(1);
   }
}

int build_server(void)
{
   memset(&rc.server_addr, 0, sizeof(rc.server_addr));

   rc.server_addr.sin_port = htons(atoi(options.local_port));
   rc.server_addr.sin_family = AF_INET;
   rc.server_addr.sin_addr.s_addr = INADDR_ANY;

   rc.server_socket = socket(AF_INET, SOCK_STREAM, 0);
   if (rc.server_socket < 0)
   {
      perror("build_server error: socket()");
      return 1;
   }

   int optval = 1;
   if( setsockopt(rc.server_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0 )
   {
      perror("build_server error: setsockopt(SO_REUSEADDR)");
      return 1;
   }

   if (settings.bind_address)
   {
      rc.server_addr.sin_addr.s_addr = inet_addr(options.bind_address);
   }

   if (bind(rc.server_socket, (struct sockaddr *) &rc.server_addr, sizeof(rc.server_addr)) < 0)
   {
      perror("build_server error: bind()");
      return 1;
   }

   if (listen(rc.server_socket, 1) < 0)
   {
      perror("build_server error: listen()");
      return 1;
   }
   return 0;
}

int wait_for_clients(void)
{
   unsigned int client_addr_size = sizeof(struct sockaddr_in);

   rc.client_socket = accept(rc.server_socket, (struct sockaddr *) &rc.client_addr, &client_addr_size);
   if (rc.client_socket < 0)
   {
      if (errno != EINTR)
      {
         perror("wait_for_clients: accept()");
      }
      return 1;
   }

   printf("tcp proxy > %s: request from %s\n", get_current_timestamp(), inet_ntoa(rc.client_addr.sin_addr));
   return 0;
}

void handle_client(void)
{
   if (settings.fork)
   {
      if (fork() == 0)
      {
         close(rc.server_socket);
         handle_tunnel();
         exit(0);
      }
      close(rc.client_socket);
   }
   else 
   {
      handle_tunnel();
   }
}

void handle_tunnel(void)
{
   if (build_tunnel() == 0)
   {
      use_tunnel();
   }
}

int build_tunnel(void)
{
   rc.remote_host = gethostbyname(options.remote_host);
   if (rc.remote_host == NULL)
   {
      perror("build_tunnel error: gethostbyname()");
      return 1;
   }

   memset(&rc.remote_addr, 0, sizeof(rc.remote_addr));

   rc.remote_addr.sin_family = AF_INET;
   rc.remote_addr.sin_port = htons(atoi(options.remote_port));

   memcpy(&rc.remote_addr.sin_addr.s_addr, rc.remote_host->h_addr, rc.remote_host->h_length);

   rc.remote_socket = socket(AF_INET, SOCK_STREAM, 0);
   if (rc.remote_socket < 0)
   {
      perror("build_tunnel error: socket()");
      return 1;
   }

   if (connect(rc.remote_socket, (struct sockaddr*) &rc.remote_addr, sizeof(rc.remote_addr)) < 0)
   {
      perror("build_tunnel error: connect()");
      return 1;
   }

   return 0;
}

int use_tunnel(void)
{
   fd_set io;
   char buffer[options.buffer_size];

   for(;;)
   {
      FD_ZERO(&io);
      FD_SET(rc.client_socket, &io);
      FD_SET(rc.remote_socket, &io);

      memset(buffer, 0, sizeof(buffer));

      if (select(fd(), &io, NULL, NULL, NULL) < 0)
      {
         perror("use_tunnel error: select()");
         break;
      }

      if (FD_ISSET(rc.client_socket, &io))
      {
         int count = recv(rc.client_socket, buffer, sizeof(buffer), 0);
         if (count < 0)
         {
            perror("use_tunnel error: recv(rc.client_socket)");
            close(rc.client_socket);
            close(rc.remote_socket);
            return 1;
         }

         if (count == 0)
         {
            close(rc.client_socket);
            close(rc.remote_socket);
            return 0;
         }

         send(rc.remote_socket, buffer, count, 0);

         if (settings.log)
         {
            printf("tcp proxy > %s: ", get_current_timestamp());
            fwrite(buffer, sizeof(char), count, stdout);
            fflush(stdout);
         }
      }

      if (FD_ISSET(rc.remote_socket, &io))
      {
          int count = recv(rc.remote_socket, buffer, sizeof(buffer), 0);
          if (count < 0)
          {
              perror("use_tunnel error: recv(rc.remote_socket)");
              close(rc.client_socket);
              close(rc.remote_socket);
              return 1;
          }

          if (count == 0)
          {
             close(rc.client_socket);
             close(rc.server_socket);
             return 0;
          }

          send(rc.client_socket, buffer, count, 0);
          if (settings.log)
          {
             printf("tcp proxy > %s: ", get_current_timestamp());
             fwrite(buffer, sizeof(char), count, stdout);
             fflush(stdout);
          }
      }
   }
   return 0;
}

int fd(void)
{
   unsigned int fd = rc.client_socket;
   if (fd < rc.remote_socket)
   {
      fd = rc.remote_socket;
   }
   return fd + 1;
}

char *get_current_timestamp(void)
{
   static char date_str[20];
   time_t date;

   time(&date);
   strftime(date_str, sizeof(date_str), "%Y-%m-%d %H:%M:%S", localtime(&date));
   return date_str;
}

void print_usage(void)
{
   fprintf(stderr, "Usage: %s [options]\n\n", name);
}

void print_helpinfo(void)
{
   fprintf(stderr, "Try `%s --help' for more options\n", name);
}

void print_help(void)
{
    fprintf(stderr, "\
Options:\n\
  --version\n\
  --help\n\n\
  --local-port=PORT    local port\n\
  --remote-port=PORT   remote port\n\
  --remote-host=HOST   remote host\n\
  --bind-address=IP    bind address\n\
  --buffer-size=BYTES  buffer size\n\
  --log\n\
  --stay-alive\n\n");
}

void print_version(void)
{
   fprintf(stderr, "\
sys-tcp-port-proxy " VERSION " fork from tcptunnel\n");
}

void print_missing(const char *message)
{
   print_usage();
   fprintf(stderr, "%s: %s\n", name, message);
   print_helpinfo();
}
