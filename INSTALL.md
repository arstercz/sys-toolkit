How to install
==============

sys-toolkit install

Most tools require:

   * Perl v5.8 or newer
   * Bash v3 or newer

### DEPENDENCIES

some perl tools need the following modules:

```
DBI
DBD::mysql
Term::ReadKey
Net::DNS
```

some shell tools need the following commands:

```
gdb
tcpdump
```

some c tools need the following libraries:

```
libpcap
```

### install perl and shell tool

To install perl/shell tools type the following:

```
perl Makefile.PL
make
make install
```

To install c tools type the following:

```
$ gcc -g -Wall -o sys-mysql-sql-reject -lpcap src/sys-mysql-sql-reject.c
$ gcc -o sys-tcp-port-proxy src/sys-tcp-port-proxy.c
```
