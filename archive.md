# Unused list

```
sys-disk-error
sys-nginx-subdir
sys-dns-response-time
sys-echo-stderr
sys-tcp-port-proxy
sys-php-chroot
sys-qtunnel-manage
sys-wechat-ops
sys-mysql-adj
sys-mysql-error
sys-mysql-set-maxconnections
sys-redis-rdb-backup
sys-mem-eat
```

sys-disk-error
==============

`type: shell`

check the disk media or other error count.
All the check are based on [Broadcom's](https://www.broadcom.com/) `MegaCli` command.

### Usage
```
# ./sys-disk-error
=> disk numbers: 5
   slot: 0
   inquiry: SEAGATE ST9600205SS
   raw_size: 572325MB
   media_error: 0
   other_error: 6
   predictive_failure: 0
   type: SAS
   firmware_state: Online

   slot: 2
   inquiry: SEAGATE ST9600205SS
   raw_size: 572325MB
   media_error: 12
   other_error: 6
   predictive_failure: 0
   type: SAS
   firmware_state: Online
```

sys-nginx-subdir
================

`type: perl`

create the subdirectory in `year/month/day` format at nginx log directory.
you can use `sys-nginx-subdir` to create the sub dirs with dynamic nginx
`access_log` path(the method `cronolog and pipe` is very inconvenient and
maybe block when pipe is no consumer; the `nginx perl` module can reduce
performance when you use perl module to check and create dirs).

### Usage
the access_log in nginx configure:
```
  location ~ ^/xxx/ {
     if ($time_iso8601 ~ "^(\d{4})-(\d{2})-(\d{2})T(\d{2})")
     {
         set $year $1;
         set $month $2;
         set $day $3;
         set $hour $4;
     }
     access_log /data/nginx/logs/$year/$month/$day/$hour.log;
  }
```
create dir with `sys-nginx-subdir`:
```
# ./sys-nginx-subdir -v -d /data/nginx/logs -t 1 -m
datestring: 2017-08-12 17:30:43
will create /web/nginx/logs/2017/08/12
[ok] already exists /web/nginx/logs/2017/08/12
create ok!
```

then reload the nginx with `-s` option.

use help option to read more.

sys-dns-response-time
=====================

`type: perl`

Measure the dns server response time.

#### Dependency

```
perl-Net-DNS
```
`centos/redhat can install bind-utils so that perl-Net-DNS lookup domain easily`

#### Usage

```
$ ./sys-dns-response-time -d highdb.com
query from dns server: 114.114.114.114, elapsed ms: 31
query from dns server: 114.114.114.114, elapsed ms: 29
query from dns server: 114.114.114.114, elapsed ms: 28
```

help message: `./sys-dns-response-time -h`

sys-echo-stderr
===============

`type: shell`

echo message to STDERR.

#### Usage:
```
$ ./sys-echo-stderr hello world >1.txt
hello world
```

sys-tcp-port-proxy
==================

`type: c`

A simple TCP port forwarder. (fork from tcptunnel)

#### How to build

``$ gcc -o sys-tcp-port-proxy sys-tcp-port-proxy.c``

### Usage

```
$ ./sys-tcp-port-proxy --help
Usage: ./sys-tcp-port-proxy [options]

Options:
  --version
  --help

  --local-port=PORT    local port
  --remote-port=PORT   remote port
  --remote-host=HOST   remote host
  --bind-address=IP    bind address
  --buffer-size=BYTES  buffer size
  --log
  --daemon
  --stay-alive

1. in session A, start a proxy:
$ ./sys-tcp-port-proxy --local-port=13306 --remote-port=3306 --remote-host=127.0.0.1 --fork

2. in session B, login with mysql:
$ mysql -h 127.0.0.1 -P 13306 -uroot -p

3. session A output the connection:
tcp proxy > 2016-03-30 15:07:02: request from 127.0.0.1
```

sys-php-chroot
=============

`type: shell`

php chroot initialization work, covering DNS , php iconv and and ssl(https).

```
$ ./sys-php-chroot /web/php/chroot
tar: Removing leading `/' from member names
...
chroot directory /web/php/chroot initialized as
   162    0 drwxr-xr-x   7 root     root           71 Mar 11 14:58 /web/php/chroot
...

Calling ssl secured sites via curl in an chroot env, some /usr/lib64 library was needed:
http://jameskirsop.com/calling-ssl-secured-sites-via-curl-in-an-apache-chroot/
```

help message: `Usage: ./sys-php-chroot /path/to/chrootdir`

sys-qtunnel-manage
==================

`type: shell`

manage the [qtunnel](https://github.com/arstercz/qtunnel) by the configure file.

### Usage

```
$ sys-qtunnel-manage -l
 All tags in config file: /etc/conn.conf:
      server1 - mode: server;       10.0.21.5:16380 --> 10.0.21.7:6380
      server2 - mode: server;       10.0.21.5:13310 --> 10.0.21.7:3310

$ sys-qtunnel-manage -r
 Already running tags:
      10844 -> server1
      10898 -> server2

$ sys-qtunnel-manage -t server1 -k
  2018_09_01_09_42_56 [info] kill the qtunnel with tag server1 ok

$ sys-qtunnel-manage -r
  Already running tags:
      10898 -> server2
```

use `-h` option for more usage message.

sys-wechat-ops
==============

`type: perl`

send message, file, image to your wechat.

**note**: `sys-wechat-ops` will read file content and send when type is text.

### install dependency

```
for redhat/centos:
   yum install perl-Config-Tiny perl-JSON perl-libwww-perl perl-HTTP-Message

for debian/ubuntu:
   apt install libconfig-tiny-perl libjson-perl libhttp-message-perl
```

### Set your wechat config, such as:
```
# cat /etc/wechat.conf
agentid = ...wechat-agentid....
secret  = ...wechat-secret.....
corpid  = ...wechat-corpid.....
touser  = userA|userB...
# toparty = 5|6
# totag   = ...

```

### Usage
```
sys-wechat-ops --conf /etc/wechat.conf --type text  --attach name.log
sys-wechat-ops --conf /etc/wechat.conf --type file  --attach name.xlsx
sys-wechat-ops --conf /etc/wechat.conf --type image --attach name.png
```

use `--help` option for more usage message.

sys-mysql-error
===============

`type: perl`

Explain MySQL error codes, like the mysql `perror` command.
Covers up to `MySQL 5.7.14-8`. All of the code msg from `Percona Server 5.7.14-8`.

read more from `source_code/sql/share/errmsg-utf8.txt`.

### Usage

```
# perl sys-mysql-error -c 1087
MySQL error code 1087 (ER_LOAD_INFO): Records: %ld  Deleted: %ld  Skipped: %ld  Warnings: %ld

# perl sys-mysql-error -c 4000
Illegal error code: 4000
```

use help option to read more.

sys-redis-rdb-backup
====================

`type: shell`

remote backup redis rdb file, execute `bgsave` before transfer rdb file.

### Usage

```
# ./sys-redis-rdb-backup -h 10.0.21.5 -P 6380 -d /srv/redis_backup
2017_06_27_14_59_40 [info] test with ssh to 10.0.21.5 ok
-NOAUTH, maybe need redis password, use -p options

# ./sys-redis-rdb-backup -i /home/mysql/.ssh/id_rsa -h 10.0.21.5 -P 6380 -d /srv/redis_backup -p xxxxxx
2017_06_27_14_59_49 [info] test with ssh to 10.0.21.5 ok
2017_06_27_14_59_52 [info] start at 20170627145949
receiving incremental file list
redis32.rdb

sent 30 bytes  received 467 bytes  994.00 bytes/sec
total size is 389  speedup is 0.78
2017_06_27_14_59_52 [info] 10.0.21.5:6380 backup to /srv/redis_backup/10.0.21.5-6380-20170627145949.rdb ok
```

use help option to read more.

sys-mem-eat
===========

`type: c`

simple tool to eat system memory, and it does not release the allocated memory.

### Usage
```
# ./mem --verbose
[verbose] allocated max memory: 100000 MB, step size: 10

[2018-09-27 19:07:06] allocated 10 MB
[2018-09-27 19:07:08] allocated 20 MB
[2018-09-27 19:07:10] allocated 30 MB
[2018-09-27 19:07:12] allocated 40 MB
```

use --help option to read usage message.

sys-mysql-adj
=============

`type: shell`

prevent system killing MySQL process by oom-killer
```
$ ./sys-mysql-adj
oom_adj mysqld process
pid 31265 oom_adj = -17
pid 25653 oom_adj = -17
pid 20247 oom_adj = -17

$ ./sys-mysql-adj
no MySQL process
```
Can be used without args.

sys-mysql-set-maxconnections
============================

`type shell`

Set local MySQL's max_connections to avoid error "Too many connections.."

#### Risk

Maybe crash when MySQL Server is very busy.

#### Need
```
gdb
```

## Usage
```
$ mysql -p -e 'select @@max_connections'
Enter password:
+-------------------+
| @@max_connections |
+-------------------+
|               100 |
+-------------------+

$ ./sys-mysql-set-maxconnections 3000
[New LWP 9029]
[New LWP 30058]
[New LWP 28201]
[New LWP 27571]
[New LWP 27476]
[New LWP 27474]
[New LWP 27473]
[New LWP 27472]
[New LWP 27471]
[New LWP 27470]
[New LWP 27469]
[New LWP 27466]
[New LWP 27465]
[New LWP 27464]
[New LWP 27463]
[New LWP 27462]
[New LWP 27461]
[New LWP 27460]
[New LWP 27459]
[New LWP 27458]
[New LWP 27457]
[Thread debugging using libthread_db enabled]
0x00007fa0b2371113 in poll () from /lib64/libc.so.6
set pid 27454 max_connections = 3000

$ mysql -p -e 'select @@max_connections'
Enter password:
+-------------------+
| @@max_connections |
+-------------------+
|              3000 |
+-------------------+
```

help message: ./sys-mysql-set-maxconnections connections_number
