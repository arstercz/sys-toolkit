# sys-toolkit

Some useful scripts to sysadmins/dbas.

Table of Contents
=================

* [sys-genpass](#sys-genpass)
* [sys-nton](#sys-nton)
* [sys-pubip](#sys-pubip)
* [sys-ascii](#sys-ascii)
* [sys-ipton](#sys-ipton)
* [sys-lock-run](#sys-lock-run)
* [sys-repeat](#sys-repeat)
* [sys-checkport](#sys-checkport)
* [sys-echo-stderr](#sys-echo-stderr)
* [sys-php-chroot](#sys-php-chroot)
* [sys-tcp-port-proxy](#sys-tcp-port-proxy)
* [sys-shell-type](#sys-shell-type)
* [sys-diskstats](#sys-diskstats)
* [sys-http-code](#sys-http-code)
* [sys-hosts-list](#sys-hosts-list)
* [sys-dns-response-time](#sys-dns-response-time)
* [sys-kill-close-wait](#sys-kill-close-wait)
* [sys-memory-maps](#sys-memory-maps)
* [sys-mem-redis-summary](#sys-mem-redis-summary)
* [sys-mysql-summary](#sys-mysql-summary)
* [sys-mysql-adj](#sys-mysql-adj)
* [sys-mysql-kill-blocked-thread](#sys-mysql-kill-blocked-thread)
* [sys-mysql-kill-long-query](#sys-mysql-kill-long-query)
* [sys-mysql-block-account](#sys-mysql-block-account)
* [sys-mysql-createdb](#sys-mysql-createdb)
* [sys-mysql-qps](#sys-mysql-qps)
* [sys-mysql-set-maxconnections](#sys-mysql-set-maxconnections)
* [sys-mysql-sql-reject](#sys-mysql-sql-reject)
* [License](#License)

sys-genpass
===========

`type: perl`

Generate complex random passwords.

Example:
```
$ ./sys-genpass 
IEZQS_hW7=exO}JG@L
```
help message: ./sys-genpass --help 

[Back to TOC](#table-of-contents)

sys-nton
========

`type: perl`

Convert specified number to binary/octal/decimal/hexadecimal format.

Example:
```
$ ./sys-nton -n 0b1111
  bin: 0b1111
  oct: 017 
  dec: 15 
  hex: 0x0F
$ ./sys-nton -n 017
  bin: 0b1111
  oct: 017 
  dec: 15 
  hex: 0x0F
$ ./sys-nton -n 15
  bin: 0b1111
  oct: 017 
  dec: 15 
  hex: 0x0F
$ ./sys-nton -n 0x0F
  bin: 0b1111
  oct: 017 
  dec: 15 
  hex: 0x0F
```
help message: ./sys-nton --help

[Back to TOC](#table-of-contents)

sys-pubip
=========

`type: shell`

Get my public ip address by curl command.
```
$ ./sys-pubip 
Get public ip address:
110.89.157.218
```
Can be used without args, return error if execute 5 seconds.

[Back to TOC](#table-of-contents)

sys-ascii
=========

`type: perl`

Display ascii table, output is the same as the command `man 7 ascii`
```
$ ./sys-ascii
...
           The following table contains the 128 ASCII characters.

           C program '\X' escapes are noted.

           Oct   Dec   Hex   Char                        Oct   Dec   Hex   Char
           ------------------------------------------------------------------------
           000   0     00    NUL '\0'                    100   64    40    @
           001   1     01    SOH (start of heading)      101   65    41    A
           002   2     02    STX (start of text)         102   66    42    B
           003   3     03    ETX (end of text)           103   67    43    C
           004   4     04    EOT (end of transmission)   104   68    44    D
           005   5     05    ENQ (enquiry)               105   69    45    E
           006   6     06    ACK (acknowledge)           106   70    46    F
           007   7     07    BEL '\a' (bell)             107   71    47    G
           010   8     08    BS  '\b' (backspace)        110   72    48    H
           011   9     09    HT  '\t' (horizontal tab)   111   73    49    I
           012   10    0A    LF  '\n' (new line)         112   74    4A    J
           013   11    0B    VT  '\v' (vertical tab)     113   75    4B    K
...
```

Can be used without args.

[Back to TOC](#table-of-contents)

sys-mysql-summary
================

`type: perl`

Get MySQL summary info.

#### DEPENDENCIES
```
DBI
DBD::mysql
perl-TermReadKey (if enable askpass option)
```

$ ./sys-mysql-summary --host 127.0.0.1 --port 19681 --user=root --askpass
```
Enter password : 
+-127.0.0.1
    version             5.6.15-rel63.0-log
    server_id           101
    has_gtid            1
    binlog_enable       1
    total_size          129.92MB
    filter              
    binlog_format       STATEMENT
    max_packet          4MB
    read_only           0
    is_slave            Yes
    repl_check          OK
```

help message: $ ./sys-mysql-summary --help

[Back to TOC](#table-of-contents)

sys-checkport
=============

`type: perl`

check a host port is wether opened or not
```
$ ./sys-checkport -h 127.0.0.1 -p 22
port 22: open

$ ./sys-checkport -h 127.0.0.1 -p 22 -v
port 22: open
  source info 127.0.0.1:53659

$ ./perl sys-checkport -h 127.0.0.1 -p 2000
port 2000: closed

$ ./sys-checkport -h 127.0.0.1 -p 2000 -u
port 2000: open | filtered -- udp port has no response
```

help message: $ ./sys-checkport --help

[Back to TOC](#table-of-contents)

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

[Back to TOC](#table-of-contents)

sys-mem-redis-summary
=====================

`type: perl`

#### No Dependencies

to get memcached or redis summary info, output is the same as stats(slabs, size) 
command on memcached, and info command on redis.

note: does not support password authentication when get redis info.

```
$ ./sys-mem-redis-summary -h 127.0.0.1 -p 6380 -t redis
Connected to 127.0.0.1:6380
# Server
redis_version:2.8.24
redis_git_sha1:00000000
redis_git_dirty:0
redis_build_id:4159b299ae09869c
redis_mode:standalone
os:Linux 2.6.32-573.18.1.el6.x86_64 x86_64
arch_bits:64
multiplexing_api:epoll
...
# Keyspace
db0:keys=1,expires=0,avg_ttl=0
db1:keys=1,expires=0,avg_ttl=0


$ ./sys-mem-redis-summary -h 127.0.0.1 -p 11211 -t memcached
Connected to 127.0.0.1:11211
STAT pid 2144
STAT uptime 529773
STAT time 1456898381
STAT version 1.4.4
STAT pointer_size 64
STAT rusage_user 582.232487
....
STAT 128 5837
END
```
help message: $ ./sys-mem-redis-summary --help

[Back to TOC](#table-of-contents)

sys-mysql-kill-blocked-thread
=============================

`type: perl`

#### Dependency
```
DBI
DBD::mysql
perl-TermReadKey (if enable askpass option)
```

kill the mysql blocking thread id if blocking times great than threthold(default is 10 times).

```
$ ./sys-mysql-killblockthread -h 127.0.0.1 -P 3306 -u root --askpass -v -k
Enter password : 
connect to 127.0.0.1, 3306, root, xxxxxxxx ...
no thread_id blocking.


 sys-mysql-killblockthread -h 127.0.0.1 -P 3306 -u root --askpass -v
Enter password : 
connect to 127.0.0.1, 3306, root, xxxxxxxx ...
kill 100123 ok.
kill 100251 ok.
```

help message: $ ./sys-mysql-killblockthread --help

[Back to TOC](#table-of-contents)

sys-shell-type
==============

`type: shell`

identifi the type of shell we used in current shell.
```
$ ./sys-shell-type 
bash
```
Can be used without args

[Back to TOC](#table-of-contents)

sys-mysql-kill-long-query
=========================

`type: perl`

#### Dependency
```
DBI
DBD::mysql
perl-TermReadKey (if enable askpass option)
```
kill the mysql long query's thread if query time greater than specified 
time value;

``
note: This script will kill running sql, some update/select statements 
will be killed, connection db is null , state in 'Binlog Dump', 
'Connect' and 'Sleep' is ignored.
``

```
$ ./sys-mysql-killlongquery -h 127.0.0.1 -u root --askpass -v -k -t 5
Enter password : 
connect to 127.0.0.1, 3306, root, xxxxxxxx ...
[INFO] thread: 92, user: test@127.0.0.1:45775, db: test, state: User sleep, time: 5, query: select sleep(15)
kill 92 ok
```
help message: $ ./sys-mysql-killlongquery --help

[Back to TOC](#table-of-contents)

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

[Back to TOC](#table-of-contents)

sys-ipton
==========

`type: perl`

Transformation of ipv4 to/from number.

```
$ ./sys-ipton
either ipv4 or number should be specified.

$ ./sys-ipton -i 127.0.0.1
ipv4 127.0.0.1 convert to : 2130706433

$ ./sys-ipton -n 2130706433
2130706433 convert to: 127.0.0.1

$ ./sys-ipton -i 127.0.0.1 -n 2130706685
both ipv4 address and number is not allowed
```

help message: `Usage: ./sys-ipton --help`

[Back to TOC](#table-of-contents)

sys-mysql-block-account
=======================

`type: perl`

block or release MySQL user account to disable/enable 
them login.

#### Dependency
```
DBI
DBD::mysql
perl-TermReadKey (if enable askpass option)
```

#### note
   The connect user must have create user or super privileges, the blocked
 account can't login when this script reverse account password.

   If use kill option, the process relatate to the account will be killed.

   this will set sql_log_bin off if you enable queit option, this can be 
 useful when you don't want the password changed replicate to slave.

#### samples
block account with dry-run:
```
$ ./sys-mysql-block-account --host 10.0.15.5 --user=root --askpass --account_user='spider' --account_host='10.0.15.%' --verbose --block --kill --dry-run
Enter password : 
connect to 10.0.15.5, 3306, root, xxxxxxxx ...
[dry-run] KILL thread 3867 for spider@10.0.15.7
[dry-run] SET PASSWORD FOR spider@10.0.15.% = 19E32FB52598AF5B642ACEB857CFC344F27D1664*
```
block account:
```

$ ./sys-mysql-block-account --host 10.0.15.5 --user=root --askpass --account_user='spider' --account_host='10.0.15.%'  --verbose --block --kill
Enter password : 
connect to 10.0.15.5, 3306, root, xxxxxxxx ...
kill 1 connections for spider@10.0.15.7
SET PASSWORD FOR spider@10.0.15.% ok
```
Then the spider user password was reversed in MySQL:
```
+----------------------------------------------------------------------------------------------------------------+
| Grants for spider@10.0.15.%                                                                                    |
+----------------------------------------------------------------------------------------------------------------+
| GRANT USAGE ON *.* TO 'spider'@'10.0.15.%' IDENTIFIED BY PASSWORD '*9E32FB52598AF5B642ACEB857CFC344F27D166D3'  |
| GRANT SELECT, INSERT, UPDATE, DELETE ON `spider`.* TO 'spider'@'10.0.15.%'                                     |
+----------------------------------------------------------------------------------------------------------------+
```
re-execute block, the following message occured:
```
[block] spider@10.0.15.% already blocked
```
```
$ ./sys-mysql-block-account --host 10.0.15.5 --user=root --askpass --account_user='spider' --account_host='10.0.15.%'  --verbose --release --kill
Enter password : 
connect to 10.0.15.5, 3306, root, xxxxxxxx ...
SET PASSWORD FOR spider@10.0.15.% ok
```
spider user password is normal:
```
+----------------------------------------------------------------------------------------------------------------+
| Grants for spider@10.0.15.%                                                                                    |
+----------------------------------------------------------------------------------------------------------------+
| GRANT USAGE ON *.* TO 'spider'@'10.0.15.%' IDENTIFIED BY PASSWORD '*4661D72F443CFC758BECA246B5FA89525BF23E91'  |
| GRANT SELECT, INSERT, UPDATE, DELETE ON `spider`.* TO 'spider'@'10.0.15.%'                                     |
+----------------------------------------------------------------------------------------------------------------+
```

help message: `Usage: ./sys-mysql-block-account --help`

[Back to TOC](#table-of-contents)

sys-lock-run
============

`type: shell`

bash script or command can only run once at any time by using flock

```
1. run command in session A
$ ./sys-lock-run sleep 20

2. run command in session B
# ./sys-lock-run sleep 20
2016_03_23_12_44_13 [warn] Only once can run at one time - sleep
```

note: as use flock, this tool will create lock file in /tmp dirs and 
delete lock file when exit.

[Back to TOC](#table-of-contents)

sys-repeat
==========

`type: shell`

execute one command repeatedly until it failure.

```
$ ./sys-repeat ls -hl sys-checkport
-rwxr-xr-x. 1 root root 1.9K Feb 29 17:10 sys-checkport
-rwxr-xr-x. 1 root root 1.9K Feb 29 17:10 sys-checkport
-rwxr-xr-x. 1 root root 1.9K Feb 29 17:10 sys-checkport
-rwxr-xr-x. 1 root root 1.9K Feb 29 17:10 sys-checkport
-rwxr-xr-x. 1 root root 1.9K Feb 29 17:10 sys-checkport
-rwxr-xr-x. 1 root root 1.9K Feb 29 17:10 sys-checkport
...
...
```

help message: ./sys-repeat command ...

[Back to TOC](#table-of-contents)

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

[Back to TOC](#table-of-contents)

sys-mysql-createdb
==================

`type: perl`

create mysql database with account user.

Connect user should be have create, create user, grant option and show databases privileges.

#### Dependency
```
DBI
DBD::mysql
perl-TermReadKey (if enable askpass option)
```

#### This tool will check privileges and replicate rules.

#### Usage

Check replication rule:
```
$ perl sys-mysql-createdb --host 127.0.0.1 --user root --database mysql  --askpass --createdb=test3 --account-user=user_test1 --account-host='10.0.21.%'
Enter password : 
ERROR: 
	The mysql is in the Binlog_Ignore_DB: mysql,test,information_schema,performance_schema
	maybe missing the slave update. specify the option --database value that is not in Binlog_Ignore_DB list
+-- database list: 
	information_schema
	cztest
	dashboard
	db1
        ...
        ...
```

Check user login privileges, grant maybe skip when login user has no privileges, default value of account-pass is random charaters
```
$ perl sys-mysql-createdb --host 127.0.0.1 --user root --database test1  --askpass --createdb=test3 --account-user=user_test1 --account-host='10.0.21.%' --priv="select, insert" --verbose
Enter password : 
connect to 127.0.0.1, 3306, root, xxxxxxxx ...
SQL: create database if not exists test3
SQL: CREATE USER user_test1@'10.0.21.%' IDENTIFIED BY 'XmhdGEZZ1KN{_fW0g3U}'
     GRANT select, insert ON test3.* TO user_test1@'10.0.21.%'
[WARN] login user root@127.0.0.1 has no Grant_priv, skip ..
    +-- Execute manually: GRANT select, insert ON test3.* TO user_test1@'10.0.21.%'
create database and user:
	host: 127.0.0.1
	port: 3306
	db  : test3
	user: user_test1
	pass: XmhdGEZZ1KN{_fW0g3U}
```

Create database and user ok.
```
$ perl sys-mysql-createdb --host 127.0.0.1 --user root --database test1  --askpass --createdb=test3 --account-user=user_test1 --account-host='10.0.21.%' --priv="select, insert" --verbose
Enter password : 
connect to 127.0.0.1, 3306, root, xxxxxxxx ...
SQL: create database if not exists test3
SQL: CREATE USER user_test1@'10.0.21.%' IDENTIFIED BY 'VyhQWQCeaKxZJrroeNVP'
     GRANT select, insert ON test3.* TO user_test1@'10.0.21.%'
create database and user:
	host: 127.0.0.1
	port: 3306
	db  : test3
	user: user_test1
	pass: VyhQWQCeaKxZJrroeNVP
The user user_test1@10.0.21.% connect ok
 
$ perl sys-mysql-createdb --host 127.0.0.1 --user root --database test1  --askpass --createdb=test3 --account-user=user_test1 --account-host='10.0.21.%' --priv="select, insert" --verbose
Enter password : 
Already exist database: test3
```

help message: perl sys-mysql-createdb --help

[Back to TOC](#table-of-contents)

sys-echo-stderr
===============

`type: shell`

echo message to STDERR.

#### Usage:
```
$ ./sys-echo-stderr hello world >1.txt 
hello world
```

[Back to TOC](#table-of-contents)

sys-mysql-qps
=============

`type: perl`

Get MySQL status, qps and conn

#### Dependency
```
DBI
DBD::mysql
perl-TermReadKey (if enable askpass option)
```

## Usage

```
$ ./perl sys-mysql-qps -h 127.0.0.1 -u root -P 3306 --askpass -i 1
Enter password :
                         |          -- QPS --           |     -- Innodb Rows Status --     | -- Threads --  |          -- Bytes --
     addr    time        |   ins  upd  del   sel    qps |      ins     upd     del    read |  run conn  cre |      recv           send
127.0.0.1:3306 16:47:28  |     0  110    0   891   1120 |        0       0       2       0 |    1    0    0 |     132044 bytes   2078183 bytes
127.0.0.1:3306 16:47:29  |     0  131    0   956   1244 |        0       0       0       0 |    4    1    0 |     144377 bytes   2226475 bytes
127.0.0.1:3306 16:47:30  |     0  142    0   996   1273 |        0       0       0       0 |    0    0    0 |     143185 bytes   2302739 bytes
127.0.0.1:3306 16:47:31  |     0  135    0   907   1179 |        0       0       1       0 |    0    0    0 |     134619 bytes   2241287 bytes
127.0.0.1:3306 16:47:32  |     0  133    0   952   1223 |        0       0       0       0 |    0  642    0 |     141494 bytes   2133514 bytes
127.0.0.1:3306 16:47:33  |     0  140    0   935   1208 |        0       0       0       0 |    0    2    0 |     131543 bytes   1962872 bytes
127.0.0.1:3306 16:47:34  |     0  133    0  1043   1318 |        0       0       1       0 |    0    1    0 |     153238 bytes   2253878 bytes
127.0.0.1:3306 16:47:35  |     0  147    0   967   1238 |        0       0       0       0 |    0    0    0 |     129724 bytes   2026643 bytes
127.0.0.1:3306 16:47:36  |     0  117    0   833   1056 |        0       0       1       0 |    1    0    0 |     121172 bytes   1974676 bytes
```

help message: perl sys-mysql-qps --help

[Back to TOC](#table-of-contents)

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

[Back to TOC](#table-of-contents)

sys-memory-maps
===============

`type: shell`

See the memory mapping of a process

## Usage
```
$ ./sys-memory-maps 25005
share   =   100164 Kbytes
private =    39332 Kbytes
total   =   139496 Kbytes (   71.80 % shareable)
```

help message: sys-memory-maps pid

[Back to TOC](#table-of-contents)


sys-mysql-sql-reject
====================

`type: c`

A simple tool to sniffer MySQL query and send RST to source ip and port
if you want to disable the sql execute.

This tool is similar to iptables which has the string option to match the 
data in tcp packages.

sys-mysql-sql-reject is fork from snapper:
https://github.com/vr000m/Snapper

#### Need
```
libpcap
```

#### How to Build
```
# gcc -g -Wall -o sys-mysql-sql-reject -lpcap sys-mysql-sql-reject.c
```

#### Usage

in session A, MySQL Server will send RST mark to client when you execute 
the sql "select user,host from mysql.user"

```
 ./sys-mysql-sql-reject em1 "tcp dst port 3306" "select user,host from mysql.user"
snapper - based on Sniffer example using libpcap
extended by Varun Singh / Copyright (c) 2005 The Tcpdump Group
THERE IS ABSOLUTELY NO WARRANTY FOR THIS PROGRAM.


NET: 10.3.254.0 a03fe00 CMASK: 255.255.255.0 ffffff00
Device: em1
Filter expression: tcp dst port 3306
MySQL query filter: select user,host from mysql.user

P107:	10.3.254.121	->	 10.3.254.119	TCP	64722	->	 3306	query: desc tm 
P108:	10.3.254.121	->	 10.3.254.119	TCP	64722	->	 3306	
P109:	10.3.254.121	->	 10.3.254.119	TCP	64722	->	 3306	query: delete from tm where a = 'hah' 
P110:	10.3.254.121	->	 10.3.254.119	TCP	64722	->	 3306	
P111:	10.3.254.121	->	 10.3.254.119	TCP	64722	->	 3306	query: select user,host from mysql.user 
P112:	10.3.254.121	->	 10.3.254.119	TCP	64722	->	 3306

```

in session B:
```
mysql> desc tm;
+-------+------------------+------+-----+---------+----------------+
| Field | Type             | Null | Key | Default | Extra          |
+-------+------------------+------+-----+---------+----------------+
| a     | int(10) unsigned | NO   | PRI | NULL    | auto_increment |
+-------+------------------+------+-----+---------+----------------+
1 row in set (0.03 sec)

mysql> delete from tm where a = 'hah';
Query OK, 0 rows affected (0.00 sec)

mysql> select user,host from mysql.user;
ERROR 2013 (HY000): Lost connection to MySQL server during query
```

help message:
```
Usage: sys-mysql-sql-reject [interface] [tcp_filter] [sql_filter]

Options:
    interface     Listen on <interface> for packets.
    tcp_filter        PCAP Filter to apply on packets.
    sql_filter        MySQL query to match on packets
```

[Back to TOC](#table-of-contents)

sys-diskstats
=============

`type: perl`

see the local device disk status

read more from kernel Documentation/iostats.txt

#### Usage 

```
$ ./sys-diskstats -d sda3 -i 5
                   iops        rs    rs_mer        ws       ws_mer    rs_sec       ws_sec          e_iot      e_iot_w          r_t          w_t
    19:32:36      98.00      0.00      0.00     98.00         0.40      0.00       574.20       6.60 ms       6.60 ms       0.00 ms       6.60 ms
    19:32:41     331.40      0.00      0.00    331.40         0.00      0.00      9550.20      19.20 ms      33.00 ms       0.00 ms      33.00 ms
    19:32:46      90.60      0.00      0.00     90.60         0.80      0.00       570.20       3.00 ms       3.00 ms       0.00 ms       3.20 ms
    19:32:51     125.80      0.00      0.00    125.80         0.00      0.00      3263.80       5.20 ms      14.20 ms       0.00 ms      14.20 ms
    19:32:56      93.20      0.00      0.00     93.20         0.00      0.00       533.00       3.80 ms       3.80 ms       0.00 ms       3.80 ms
    19:33:01     296.40      0.00      0.00    296.40         0.00      0.00      9362.20      15.80 ms      22.60 ms       0.00 ms      22.60 ms
```

help message: ./sys-diskstats -h

item list:

```
   iops     => io operations per second
   rs       => disk reads per second
   rs_mer   => disk read merged per second
   ws       => disk write per second
   ws_mer   => disk write merged per second
   rs_sec   => disk sectors read per second
   ws_sec   => disk sectors write per second
   e_iot    => disk io time in ms
   e_iot_w  => disk io time weighted
   r_t      => disk read time in ms
   w_t      => disk write time in ms
```

[Back to TOC](#table-of-contents)

sys-http-code
=============

`type: perl`

Explains the meaning of an HTTP status code.

#### Usage

```
$ ./sys-http-code -c 100
  Status code: 100
  Message: Continue
  Code explanation: Request received, please continue

$ ./sys-http-code -c 10x
  Status code: 100
  Message: Continue
  Code explanation: Request received, please continue

  Status code: 101
  Message: Switching Protocols
  Code explanation: Switching to new protocol; obey Upgrade header

  Status code: 102
  Message: Processing
  Code explanation: WebDAV; RFC 2518, Server has received and is processing the request.

  Status code: 103
  Message: Processing
  Code explanation: Server has received and is processing the request.

$ ./sys-http-code -c all
  Status code: 100
  Message: Continue
  Code explanation: Request received, please continue

  Status code: 101
  Message: Switching Protocols
  Code explanation: Switching to new protocol; obey Upgrade header
  ...
  ...
  Status code: 599
  Message: Network connect timeout error
  Code explanation: Network connect timeout behind the proxy.
```

help message: ./sys-http-code -h

[Back to TOC](#table-of-contents)

sys-hosts-list
==============

`type: shell`

Output the ip or host for the file: /etc/hosts

#### Usage

```
# output ip list
./sys-hosts-list ip
   10.3.254.2
   10.3.254.3
   127.0.0.1
   ::1

# output host list
./sys-hosts-list host
   localhost
   localhost.localdomain
   localhost4
   z2.com
   z3
```

help message: ./sys-hosts-list [ip|host]

[Back to TOC](#table-of-contents)

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

[Back to TOC](#table-of-contents)

sys-kill-close-wait
===================

`type: perl`

kill the tcp close_wait state connections without restart server program.

#### Usage

```
$ netstat -tulnap|grep CLOSE | grep '10.0.21.17'
tcp        0      0 ::ffff:10.0.21.5:7200    ::ffff:10.0.21.17:55365    CLOSE_WAIT  2681/./audit_server

$ ./sys-kill-close-wait --src_host 10.0.21.17 --src_port 55365 --dst_host 10.0.21.5 --dst_port 7200
kill close_wait connection 10.0.21.17:55365 => 10.0.21.5:7200
send ack ok!
```

help message: `./sys-kill-close-wait -h`

[Back to TOC](#table-of-contents)

License
=======

MIT / BSD
