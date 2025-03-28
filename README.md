# sys-toolkit

Some useful scripts to sysadmins/dbas.

Read [INSTALL](INSTALL.md) to install toolkit.

Table of Contents
=================

* [sys-genpass](#sys-genpass)
* [sys-nton](#sys-nton)
* [sys-pubip](#sys-pubip)
* [sys-align](#sys-align)
* [sys-ascii](#sys-ascii)
* [sys-easyhosts](#sys-easyhosts)
* [sys-ipton](#sys-ipton)
* [sys-lock-run](#sys-lock-run)
* [sys-logtail](#sys-logtail)
* [sys-swap](#sys-swap)
* [sys-repeat](#sys-repeat)
* [sys-daemon](#sys-daemon)
* [sys-checkport](#sys-checkport)
* [sys-murmur3](#sys-murmur3)
* [sys-needrestart](#sys-needrestart)
* [sys-numa-maps](#sys-numa-maps)
* [sys-sift](#sys-sift)
* [sys-stalk](#sys-stalk)
* [sys-summary](#sys-summary)
* [sys-glusterfs-rm](#sys-glusterfs-rm)
* [sys-glusterfs-gfidpath](#sys-glusterfs-gfidpath)
* [sys-google-totp](#sys-google-totp)
* [sys-traffic-capture](#sys-traffic-capture)
* [sys-diskstats](#sys-diskstats)
* [sys-http-code](#sys-http-code)
* [sys-http-stat](#sys-http-stat)
* [sys-rmcolor](#sys-rmcolor)
* [sys-kill-close-wait](#sys-kill-close-wait)
* [sys-unmap-file](#sys-unmap-file)
* [sys-slow-delete-file](#sys-slow-delete-file)
* [sys-mapstat-file](#sys-mapstat-file)
* [sys-memory-maps](#sys-memory-maps)
* [sys-memcached-check](#sys-memcached-check)
* [sys-memcached-capture](#sys-memcached-capture)
* [sys-mysql-summary](#sys-mysql-summary)
* [sys-mysql-kill-blocked-thread](#sys-mysql-kill-blocked-thread)
* [sys-mysql-kill-long-query](#sys-mysql-kill-long-query)
* [sys-mysql-block-account](#sys-mysql-block-account)
* [sys-mysql-health](#sys-mysql-health)
* [sys-mysql-createdb](#sys-mysql-createdb)
* [sys-mysql-pitr](#sys-mysql-pitr)
* [sys-mysql-purge-binlog](#sys-mysql-purge-binlog)
* [sys-mysql-qps](#sys-mysql-qps)
* [sys-mysql-repl](#sys-mysql-repl)
* [sys-mysql-report](#sys-mysql-report)
* [sys-mysql-sql-reject](#sys-mysql-sql-reject)
* [sys-mysql-diff](#sys-mysql-diff)
* [sys-mysql-search](#sys-mysql-search)
* [sys-mysql-switchdb](#sys-mysql-switchdb)  
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

sys-memcached-check
=====================

`type: perl`

check memcached whether is alive or not

#### No Dependencies

set/get a memcached key to check memcached whether is alive or not, 
this can check a memcached even it's hang or timeout.

```
./sys-memcached-check -h 10.0.21.5 -p 11211   
memcached 10.0.21.5:11211 check ok!

./sys-memcached-check -6 -h fe80::222:19ff:fe54:33c5%em1 -p 11211
memcached fe80::222:19ff:fe54:33c5%em1:11211 check ok!
```
help message: $ ./sys-memcached-check --help

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
waiting_thread_id:  4
waiting_query:      delete from t1 where a = 1
waiting_time:       5
blocking_host:      10.0.21.5:53150
blocking_thread_id: 18
blocking_query:     null
kill 100123 ok.
kill 100251 ok.
```

help message: $ ./sys-mysql-killblockthread --help

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
$ ./sys-lock-run -f /var/run/lockrun sleep 20

2. run command in session B
# ./sys-lock-run -f /var/run/lockrun sleep 20
2016_03_23_12_44_13 [warn] Only once can run at one time - sleep 20
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


NET: 10.0.21.0 a03fe00 CMASK: 255.255.255.0 ffffff00
Device: em1
Filter expression: tcp dst port 3306
MySQL query filter: select user,host from mysql.user

P107:	10.0.21.7	->	 10.0.21.17	TCP	64722	->	 3306	query: desc tm 
P108:	10.0.21.7	->	 10.0.21.17	TCP	64722	->	 3306	
P109:	10.0.21.7	->	 10.0.21.17	TCP	64722	->	 3306	query: delete from tm where a = 'hah' 
P110:	10.0.21.7	->	 10.0.21.17	TCP	64722	->	 3306	
P111:	10.0.21.7	->	 10.0.21.17	TCP	64722	->	 3306	query: select user,host from mysql.user 
P112:	10.0.21.7	->	 10.0.21.17	TCP	64722	->	 3306

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
                   iops        rs    rs_mer        ws       ws_mer    rs_kB       ws_kB          e_iot      e_iot_w          r_t          w_t
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
   rs_kB    => disk kBytes read per second
   ws_kB    => disk kBytes write per second
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

sys-easyhosts
==============

`type: perl`

managing your /etc/hosts file.

#### Usage

```
$ sys-easyhosts -m list
localhost               => 127.0.0.1        (on)
localhost               => ::1              (on)
localhost.localdomain   => 127.0.0.1        (on)
localhost.localdomain   => ::1              (on)
localhost4              => 127.0.0.1        (on)
localhost4.localdomain4 => 127.0.0.1        (on)
localhost6              => ::1              (on)
localhost6.localdomain6 => ::1              (on)

# check domain
$ sys-easyhosts -m has google.com
google.com not found in hosts file

# add domain
$ sys-easyhosts -m add google.com 172.217.8.14
ok - [add] google.com 172.217.8.14

# new list in /etc/hosts
$ cat /etc/hosts
127.0.0.1 localhost.localdomain localhost4.localdomain4 localhost4 localhost 
172.217.8.14 google.com 
::1 localhost6.localdomain6 localhost.localdomain localhost6 localhost 

# disable doamain list
$ sys-easyhosts -m off google.com             
ok - [off] google.com

$ cat /etc/hosts
127.0.0.1 localhost4.localdomain4 localhost.localdomain localhost4 localhost 
# 172.217.8.14 google.com 
::1 localhost6.localdomain6 localhost.localdomain localhost6 localhost 
```

use `--help` option for more usage message, ipv4 and ipv6 are both support.

mode must set `list, fix, add, aff, on, off, del, has`. and the domain value is `$ARGV[0]`(google.com), ip value is `$ARGV[1]`(172.217.8.14), all mode support `dryrun`
 that only print result, don't change hosts file. 

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

sys-traffic-capture
===================

`type: shell`

capture interface packets when traffic greater than a value  

### need:

   ```
   tcpdump
   ```
#### Usage:
capture when interface em1's in traffic greater than  1000000 bytes
```
$ bash sys-traffic-capture em1 in 1000000
2016_10_22_11_21_19 [info] capture em1 300000 packets into em1-2016_10_22_11_21_15.pcap
```

[Back to TOC](#table-of-contents)

sys-http-stat
=============

`type: shell`

get curl statistics made simple.

fork from https://github.com/b4b4r07/httpstat with no bc command need.

#### Usage:
get https://highdb.com url statistics
```
sys-http-stat https://highdb.com -k
HTTP/1.1 200 OK
Server: nginx
Date: Mon, 06 Feb 2017 10:04:57 GMT
Content-Type: text/html; charset=UTF-8
Transfer-Encoding: chunked
Connection: keep-alive
Link: <https://highdb.com/wp-json/>; rel="https://api.w.org/"

website ip address: 85.90.244.138:443
Body stored in: /tmp/httpstat-body.6525266621486375037

  DNS Lookup   TCP Connection   SSL Handshake   Server Processing   Content Transfer
[       4ms  |       233ms    |      620ms    |       2322ms      |        233ms     ]
             |                |               |                   |                  |
    namelookup:4ms            |               |                   |                  |
                        connect:237ms         |                   |                  |
                                    pretransfer:857ms             |                  |
                                                      starttransfer:3179ms           |
                                                                                 total:3412ms 

speed_download 7440.4 KiB, speed_upload 0.0 KiB
```

[Back to TOC](#table-of-contents)

sys-mysql-diff
==============

`type: perl`

compare MySQL database schema and privilege at different time.
inspired by https://github.com/aspiers/mysqldiff

#### Usage:

#### 1. drop table.
```
mysql root@[localhost:s3306 test] > drop table table_add;
Query OK, 0 rows affected (0.02 sec)

```
#### check with sys-mysql-diff
```
# perl sys-mysql-diff -h 127.0.0.1 -P 3306 -u root --askpass -d test
Enter password : 
DROP TABLE `table_add`;
```

#### 2. create table.
```
mysql root@[localhost:s3306 test] > CREATE TABLE `table_add` (
   `id` int(10) NOT NULL AUTO_INCREMENT,
   `name` varchar(20) DEFAULT NULL,
   `source` tinyint(1) DEFAULT NULL,
   `create_time` datetime DEFAULT NULL,
   `type` tinyint(1) NOT NULL DEFAULT '0',
   PRIMARY KEY (`id`),
   KEY `idx_cretime` (`create_time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
Query OK, 0 rows affected (0.02 sec)
```
#### check with sys-mysql-diff
```
#perl sys-mysql-diff -h 127.0.0.1 -P 3306 -u root --askpass -d test
Enter password : 
CREATE TABLE table_add (
  id int(10) NOT NULL AUTO_INCREMENT,
  name varchar(20) DEFAULT NULL,
  source tinyint(1) DEFAULT NULL,
  create_time datetime DEFAULT NULL,
  type tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (id),
  KEY idx_cretime (create_time)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
```

#### 3. alter table add column and add key.
```
mysql root@[localhost:s3306 test] > alter table table_add add column descrips varchar(100) not null default '';
Query OK, 0 rows affected (0.03 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql root@[localhost:s3306 test] > alter table table_add add key idx_source(`source`);
Query OK, 0 rows affected (0.01 sec)
Records: 0  Duplicates: 0  Warnings: 0
```
#### check with sys-mysql-diff
```
# perl sys-mysql-diff -h 127.0.0.1 -P 3306 -u root --askpass -d test
Enter password : 
ALTER TABLE `table_add` ADD COLUMN `descrips` varchar(100) NOT NULL DEFAULT '';
ALTER TABLE `table_add` ADD INDEX `idx_source` (`source`);
```

#### 4. alter table drop column and drop key.
```
mysql root@[localhost:s3306 test] > alter table table_add drop key idx_source;
Query OK, 0 rows affected (0.01 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql root@[localhost:s3306 test] > alter table table_add drop column descrips;
Query OK, 0 rows affected (0.02 sec)
Records: 0  Duplicates: 0  Warnings: 0
```
#### check with sys-mysql-diff
```
# perl sys-mysql-diff -h 127.0.0.1 -P 3306 -u root --askpass -d test
Enter password : 
ALTER TABLE `table_add` DROP COLUMN `descrips`;
ALTER TABLE `table_add` DROP INDEX `idx_source`;
```

#### 5. alter variables and user privileges.
```
mysql root@[localhost:s3301 test] > set global wait_timeout = 1000;
Query OK, 0 rows affected (0.00 sec)
mysql root@[localhost:s3301 test] > revoke all on test.* from user_test@`10.3.254.%`;
Query OK, 0 rows affected (0.00 sec)
```

#### check with sys-mysql-diff with -r option
```
# perl sys-mysql-diff -h 127.0.0.1 -P 3301 -u root --askpass -d test -t -r
Enter password :
SET GLOBAL wait_timeout = 1000;
REVOKE ALL PRIVILEGES ON test.* FROM 'user_test'@'10.0.21.%';
```

#### 6. change user password and privileges with -r option
```
mysql root@[localhost:s3301 test] > set password for user_test@`10.0.21.%` = password('xxxxxx');
Query OK, 0 rows affected (0.00 sec)

mysql root@[localhost:s3301 test] > revoke select on test.* from user_test@`10.0.21.%`;
Query OK, 0 rows affected (0.00 sec)

```

#### check with sys-mysql-diff
```
# perl sys-mysql-diff -h 127.0.0.1 -P 3301 -u root --askpass -d test -t -r
Enter password : 
SET PASSWORD FOR 'user_test'@'10.0.21.%' = '*4661D72F443CFC758BECA246B5FA89525BF23E91';
REVOKE SELECT ON test.* FROM 'user_test'@'10.0.21.%';
```

help message: `perl sys-mysql-diff --help`

[Back to TOC](#table-of-contents)

sys-glusterfs-rm
================

`type: shell`

remove glusterfs file

### Usage:
switch to glusterfs volum dir before you remove a file
```
$ sys-glusterfs-rm slave_info.log 
Would remove the following
  .glusterfs/9f/88/9f880673-f47f-458c-b0a5-46316f9377b0
  rm: remove regular file `.glusterfs/9f/88/9f880673-f47f-458c-b0a5-46316f9377b0'? y
  rm: remove regular file `slave_info.log'? y
```

help message: `sys-glusterfs-rm --help`

[Back to TOC](#table-of-contents)


sys-glusterfs-gfidpath
======================

`type: shell`

turns a GFID into a real file path.

### Usage:

```
$ sys-glusterfs-gfidpath /export/gfs_brick/dl_resource 9f880673-f47f-458c-b0a5-46316f9377b0
9f880673-f47f-458c-b0a5-46316f9377b0 == File: /export/gfs_brick/dl_resource/.trashcan/archive/Qtest.qmlc.zip_2022-11-24_040445_+0000
```

[Back to TOC](#table-of-contents)

sys-daemon
==========

`type: perl`

run script with daemonize way.

### Usage:

#### make a tiny shell

```
#!/bin/bash

while(true); do
   F=$(date +%s.%N)
   echo $F
   sleep 1
done
```

run t.sh with sys-daemon:
```
./sys-daemon -p /tmp/tt.pid -o /tmp/tt.log /tmp/t.sh
```
or
```
perl sys-daemon -p /tmp/tt.pid -o /tmp/tt.log /tmp/t.sh
Overwritting PID file /tmp/tt.pid because PID 5705 is not running.
```
### check the running process
```
# ps -ef|grep t.sh | grep -v 'grep'
root      5705     1  0 19:31 ?        00:00:00 /bin/bash /tmp/t.sh
```
use help option to read more.

[Back to TOC](#table-of-contents)

sys-rmcolor
==========

`type: perl`

remove color and control code from text file.

### Usage
```
# read from STDIN and print to STDOUT if --file is not set
$ cat color-file | sys-rmcolor

$ sys-rmcolor -f color-file -d rmcolor-file
```

use help option to read more.

[Back to TOC](#table-of-contents)

sys-google-totp
===============

`type: perl`

get google Authentication which used the Time-based One-time password Algorithm.

### Usage
```
# ./sys-google-totp --secret FNENMTM3BTB42EKM
totp message:
  secret: FNENMTM3BTB42EKM
  494065 (9 second(s) remaining)
```

use help option to read more.

[Back to TOC](#table-of-contents)

sys-swap
========

`type: shell`

simple swap setup script for Linux

### Usage
```
# sys-swap 8G /web/swap/swapfile
step 1. dd /web/swap/swapfile with bs: 4096 and count: 2097152
2097152+0 records in
2097152+0 records out
8589934592 bytes (8.6 GB) copied, 66.3824 s, 129 MB/s
step 2. mkswap file /web/swap/swapfile
Setting up swapspace version 1, size = 8388604 KiB
no label, UUID=34ebfcf2-9d88-4326-8e16-a48aec26e1f1
step 3. chmod file /web/swap/swapfile to 0600
step 4. swapon file /web/swap/swapfile
step 5. add swap info to fstab
/web/swap/swapfile        swap     swap   defaults         0 0

Done! You now have a 8 swap file at /web/swap/swapfile
```
show the help message with no argument.

[Back to TOC](#table-of-contents)

sys-mysql-search
================

`type: perl`

search mysql metadata info with `REGEXP` syntax, include database name, table name, column name, variable or status.

### Usage
```
# sys-mysql-search -h 10.0.21.5 -P 3301 -u root --askpass -s '.*count|test' -m t
Enter password : 
  10.0.21.5:3301
      SCHEMA: graph, TABLE: endpoint_counter, BASE TYPE: BASE TABLE
      SCHEMA: test, TABLE: count_test, BASE TYPE: BASE TABLE
      SCHEMA: test, TABLE: share_count, BASE TYPE: BASE TABLE
      SCHEMA: test, TABLE: test_count, BASE TYPE: BASE TABLE
```
you can use `SQL regexp` in `--search` option. use the help option to read more.

[Back to TOC](#table-of-contents)

sys-mysql-switchdb
==================

`type: perl`

switch two database name and rename all tables.

### Usage

> need: Config::Tiny

create config file, eg:
```
[game_db]
instance=10.0.1.53:3396,10.0.1.54:3397    # comma split
db=information_schema 
username=user_use
password=xxxxxxxx
```

check switch:
```
# sys-mysql-switchdb --conf switch.cnf --suffix _bak
[2024-01-29 15:11:43] [verbose] need switch: 10.0.1.53:3396 - t_5100 -> t_5100_bak
[2024-01-29 15:11:43] -------------------------------------------
[2024-01-29 15:11:43] [verbose] need switch: 10.0.1.53:3397 - percona -> percona_bak
[2024-01-29 15:11:43] -------------------------------------------
```

check and force switch db name:
```
# sys-mysql-switchdb --conf  switch.cnf --suffix _bak --switch --force
[2024-01-29 15:11:52] [verbose] need switch: 10.0.1.53:3396 - t_5100 -> t_5100_bak
[2024-01-29 15:11:52] [ok] create database t_5100_temp ok
[2024-01-29 15:11:52] [ok] RENAME TABLE t_5100.usert TO t_5100_temp.usert ok
[2024-01-29 15:11:52] [ok] RENAME TABLE t_5100.usert2 TO t_5100_temp.usert2 ok
[2024-01-29 15:11:52] [ok] RENAME TABLE t_5100.usert3 TO t_5100_temp.usert3 ok
[2024-01-29 15:11:52] [ok] RENAME TABLE t_5100.usert4 TO t_5100_temp.usert4 ok
[2024-01-29 15:11:52] [ok] switch t_5100 to t_5100_temp ok
[2024-01-29 15:11:52] [ok] RENAME TABLE t_5100_bak.usert TO t_5100.usert ok
[2024-01-29 15:11:52] [ok] RENAME TABLE t_5100_bak.usert2 TO t_5100.usert2 ok
[2024-01-29 15:11:52] [ok] switch t_5100_bak to t_5100 ok
[2024-01-29 15:11:52] [ok] RENAME TABLE t_5100_temp.usert TO t_5100_bak.usert ok
[2024-01-29 15:11:52] [ok] RENAME TABLE t_5100_temp.usert2 TO t_5100_bak.usert2 ok
[2024-01-29 15:11:52] [ok] RENAME TABLE t_5100_temp.usert3 TO t_5100_bak.usert3 ok
[2024-01-29 15:11:52] [ok] RENAME TABLE t_5100_temp.usert4 TO t_5100_bak.usert4 ok
[2024-01-29 15:11:52] [ok] switch t_5100_temp to t_5100_bak ok
[2024-01-29 15:11:52] [ok] drop database t_5100_temp ok.
[2024-01-29 15:11:52] [ok] switch from t_5100 to t_5100_bak ok!
[2024-01-29 15:11:52] [ok] switch: 10.0.1.53:3396 - t_5100 -> t_5100_bak ok.
[2024-01-29 15:11:52] -------------------------------------------
[2024-01-29 15:11:52] [verbose] need switch: 10.0.1.53:3397 - percona -> percona_bak
[2024-01-29 15:11:52] [ok] create database percona_temp ok
[2024-01-29 15:11:52] [ok] RENAME TABLE percona.user TO percona_temp.user ok
[2024-01-29 15:11:52] [ok] switch percona to percona_temp ok
[2024-01-29 15:11:52] [ok] RENAME TABLE percona_bak.user TO percona.user ok
[2024-01-29 15:11:52] [ok] switch percona_bak to percona ok
[2024-01-29 15:11:52] [ok] RENAME TABLE percona_temp.user TO percona_bak.user ok
[2024-01-29 15:11:52] [ok] switch percona_temp to percona_bak ok
[2024-01-29 15:11:52] [ok] drop database percona_temp ok.
[2024-01-29 15:11:52] [ok] switch from percona to percona_bak ok!
[2024-01-29 15:11:52] [ok] switch: 10.0.1.53:3397 - percona -> percona_bak ok.
[2024-01-29 15:11:52] -------------------------------------------
[2024-01-29 15:11:52] [ok] switch all instances ok.
```

[Back to TOC](#table-of-contents)

sys-murmur3
===========

`type: perl`

murmur Murmur3 32bit hash calculate. read more from [murmurHash](https://en.wikipedia.org/wiki/MurmurHash)

### Usage
```
# sys-murmur3 -s "hello world"
2951810136
```
use help option to read more.

[Back to TOC](#table-of-contents)

sys-mysql-repl
==============

`type: perl`

A simple tool for discover MySQL replication topology, also support master-master topology.

`sys-mysql-repl` can get the master, slave status, common info(server_id, binlog, filter ...) and check repl health, but cann't get replication info if the master and slave have different port and give the `--host` option with slave value.

### Usage

the `--host` can be set both master and slave ip address:
```
perl sys-mysql-repl --host 10.0.21.17 --port 3303 --user monitor --askpass
Enter password : 
+-10.0.21.17:3303
version             5.5.36-34.1-rel34.1-log
server_id           68839
has_gtid            Not Support
tx_isolation        REPEATABLE-READ
binlog_enable       1
filter              binlog_ignore_db: information_schema,mysql,performance_schema,test; 
binlog_format       ROW
max_packet          32MB
read_only           0
  +-10.0.21.7:3303
  version             5.5.36-34.1-rel34.1-log
  server_id           462055
  has_gtid            Not Support
  tx_isolation        REPEATABLE-READ
  binlog_enable       1
  filter              replicate_ignore_db: information_schema,mysql,performance_schema,test; 
  binlog_format       ROW
  max_packet          32MB
  read_only           1
  repl_check          OK
```
use help option to read more.

[Back to TOC](#table-of-contents)

sys-mysql-report
================

`type: Bash`

Report MySQL information nicely. fork from [pt-mysql-summary 3.4.0](https://www.percona.com/doc/percona-toolkit/LATEST/pt-mysql-summary.html), but add more features:
```
1. add database size section, sort by database size;
2. add innodb wait count section, response to innodb blocked blocker;
3. add innodb longest trx section, to get longest trx sql info;
4. add innodb blocked blocker section, to get blocked sql info;
5. record mysql open tables info;
```

#### Usage

```
# get report and save samples to /tmp/save_3396_1
$ sys-mysql-report --save-samples /tmp/save_3396_1 --host 10.1.1.26 --port 3396 --user root --ask-pass

# details report file
$ ls /tmp/save_3396_1
collect.err             innodb-status      mysql-data-size     mysql-master-logs    mysql-plugins      mysql-slave        mysql-status-defer  ndb-status
innodb-blocked-blocker  mysql-config-file  mysqld-executables  mysql-master-status  mysql-processlist  mysql-slave-hosts  mysql-users
innodb-longest-trx      mysql-databases    mysqld-instances    mysql-open-tables    mysql-roles        mysql-status       mysql-variables

# read samples from /tmp/save_3396_1 and get the report
$ sys-mysql-report --read-samples /tmp/save_3396_1 --host 10.1.1.26 --port 3396 --user root --ask-pass
```

use help option to read more.

[Back to TOC](#table-of-contents)

sys-mysql-health
================

`type: perl`

check the mysql health, this is forked from [MySQLTunner-perl](https://github.com/major/MySQLTuner-perl), read more from [mysql_health](https://github.com/arstercz/mysql_health).

use help option to read more.

[Back to TOC](#table-of-contents)

sys-logtail
==============

`type: shell`

Read the log file from last checkpoint, it's useful when analsis log file with a incrementally way.

### Usage
```
$ echo 1 >/tmp/t.log
$ sys-logtail -f /tmp/t.log 
1
$ echo 2 >>/tmp/t.log        
$ sys-logtail -f /tmp/t.log 
2
```
use `--help` option for more usage message.

[Back to TOC](#table-of-contents)

sys-numa-maps
=============

`type: perl`

report the numa information about running processes.

### Usage
```
# ./sys-numa-maps -p 31647
N0                :         597833 (  2.28GB)
N1                :         581409 (  2.22GB)
active            :           1864 (  7.28MB)
anon              :        1176537 (  4.49GB)
dirty             :        1176537 (  4.49GB)
kernelpagesize_kB :           1740 (  6.80MB)
mapmax            :            638 (  2.49MB)
mapped            :           2804 ( 10.95MB)
```

read more from `kernel-doc/Documentation/vm/numa_memory_policy.txt`, and use --help option to read usage message.

[Back to TOC](#table-of-contents)

sys-memcached-capture
=====================

`type: shell`

capture memcached traffic and parsed to get item list.

### Usage
```
$ sys-memcached-capture -p 11212 -i eth0 -e 'src 10.0.21.5'
- start tcpdump ...
- use 'Crtl+c' to stop!
tcpdump: listening on any, link-type LINUX_SLL (Linux cooked), capture size 65535 bytes
^C5 packets captured
10 packets received by filter
0 packets dropped by kernel
- SIGINT received, kill tcpdum...
- parse the traffic file /tmp/2018_12_11_12_07_22-11212-memcached.pcap...
  2018-12-10 12:02:58.950259 - get tags
  2018-12-10 12:03:04.910211 - set msg 0 0 3
  2018-12-10 12:03:10.103213 - get msg
  2018-12-10 12:03:13.430215 - delete msg
```
`-e` is optional, use `-h` option for more usage message.

[Back to TOC](#table-of-contents)

sys-align
=========

`type: perl`

aligns output from other tools to columns.

### Usage
```
# vmstat | tail -2              
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
  0  0      0 5588044      0 2459224    0    0     0     1    0    0  0  0 100  0  0

# vmstat | tail -2 | sys-align
   r b swpd    free buff   cache si so bi bo in cs us sy  id wa st
   1 0    0 5585928    0 2459304  0  0  0  1  0  0  0  0 100  0  0
```
use `--help` option for more usage message.

[Back to TOC](#table-of-contents)

sys-sift
========

`type: Bash`

Browses files created by sys-stalk.


### Usage

fork from [pt-sift](https://www.percona.com/doc/percona-toolkit/LATEST/pt-sift.html). but add the following features:
```
1. remove all about MySQL summary info;
2. add report on tcpdump, tcprstat, perf, disk io, httpstat, netstat.. etc;
3. remove the pt-pmap, pt-diskstats ... dependencies;
```

use --help option for more usage message.

[Back to TOC](#table-of-contents)

sys-stalk
=========

`type: Bash`

Collect forensic data about system when problems occur.

### Usage

fork from [pt-stalk](https://www.percona.com/doc/percona-toolkit/LATEST/pt-stalk.html). but add the following features:
```
1. remove all about MySQL summary info;
2. add tcpdump, tcprstat, numactl, ss ... commands;
3. add perf support;
```

use --help option for more usage message.


[Back to TOC](#table-of-contents)

sys-summary
===========

`type: Bash`

Summarize system information nicely.

### Usage

fork from [pt-summary](https://www.percona.com/doc/percona-toolkit/LATEST/pt-summary.html), but add the following features:
```
1. fix the file command read symblinks file error;
2. ignore /lib/libc.so.6 error when load snoopy library;
3. fix fio-status output parse error;
4. fix partition error when sort and join doesn't match;
5. fix process list parse error;
6. add Centos7/RHEL7 support when parse free command output;
7. MegaCli support MegaCli and MegaCli64;
8. add zpool/zfs report;
9. fix top command output;
```
use --help option for more usage message.


[Back to TOC](#table-of-contents)

sys-mysql-pitr
==============

`type: Perl`

recover mysql based on PITR(point in time recover).

> only support `mysqldump + binlog`

```
$ sys-mysql-pitr --conf /etc/wt-pitr.conf --sql /tmp/backup-20230413171112.sql.lz4 --stoptime '2023-04-13 17:14:01' --update --full
2023-04-13T17:16:08 [--] the file /tmp/backup-20230413171112.sql.lz4 maybe in compress..
2023-04-13T17:16:08 [--] try to decompress /tmp/backup-20230413171112.sql.lz4
2023-04-13T17:16:08 [OK] decompress /tmp/backup-20230413171112.sql.lz4 ok
2023-04-13T17:16:08 [--] get server_id:3476804, log_file:mysql-bin.000033, at_pos:7921, end_pos:7986
2023-04-13T17:16:08 [--] get mysql-bin.000033: 7921(230413 17:12:17)
2023-04-13T17:16:08 [--] pitr-instance disabled gtid, will add --skip-gtids option
2023-04-13T17:16:08 [OK] generate increment sql /export/mysql_pitr/10.1.1.3_3396-3476804_7921.sql
2023-04-13T17:16:08 [OK] general increment ok, 7921(230413 17:12:17) ~ 2023-04-13 17:14:01
2023-04-13T17:16:08 [--] will import the /tmp/backup-20230413171112.sql or /export/mysql_pitr/10.1.1.3_3396-3476804_7921.sql
2023-04-13T17:16:08 [^^] [warn] different mysql version in binlog-dump[5.7.28-31-log] and pitr-instance[5.7.35-38-log]
2023-04-13T17:16:08 [^^] [warn] be aware of the potential risks
2023-04-13T17:16:08 [--] not set --database option, used with --full option
2023-04-13T17:16:08 [--] begining full backup recover - /tmp/backup-20230413171112.sql
2023-04-13T17:16:42 [OK] mysql full backup recover /tmp/backup-20230413171112.sql ok
2023-04-13T17:16:42 [--] begining increment backup recover - /export/mysql_pitr/10.1.1.3_3396-3476804_7921.sql
2023-04-13T17:16:42 [OK] mysql binlog dump recover /export/mysql_pitr/10.1.1.3_3396-3476804_7921.sql ok
2023-04-13T17:16:42 [OK] pitr recover ok, from mysql-bin.000033:7921(230413 17:12:17) to (2023-04-13 17:14:01)
```

use `--help` for more message.

[Back to TOC](#table-of-contents)

sys-mysql-purge-binlog
======================

`type: Perl`

purge MySQL binary logs, you can retain binlog files by count or hours type. the option `retain` is integer value, default is 5, it retain number files if `type` is count, retain about number hours files if `type` is hour. 

the connect user must have `super`, `process`, `replication_client` privileges. option `--host` can be set both master and slave ip address, `--host` and `--port` option must be slave info if master and slave have different port:
```
$ sys-mysql-purge-binlog --host 10.0.21.5 --port 3301 --user monitor --askpass --purge --type count --retain 2
Enter password : 
2019-05-09T18:43:11 [purge check] mysql replication status:
  +-10.0.21.5:3301
  version             5.6.38-83.0-log
  server_id           1379557
  has_gtid            0
  binlog_enable       1
  tx_isolation        REPEATABLE-READ
  binlog_format       MIXED
  charset             utf8
  max_packet          1024MB
  read_only           0
    +-10.0.21.7:3301
    version             5.6.38-83.0-log
    server_id           1445093
    has_gtid            0
    binlog_enable       1
    tx_isolation        REPEATABLE-READ
    binlog_format       MIXED
    relay_master_file   mysql-bin.000083
    relay_behind_second 0
    charset             utf8
    max_packet          1024MB
    read_only           0
    repl_check          OK
2019-05-09T18:43:11 retain 2 binary logs is approximate to purge before mysql-bin.000081
2019-05-09T18:43:11 purge binary logs to mysql-bin.000081 ok!

$ sys-mysql-purge-binlog --host 10.0.21.5 --port 3301 --user monitor --askpass --purge --type hour --retain 3     
Enter password : 
2019-05-09T18:43:25 [purge check] mysql replication status:
  +-10.0.21.5:3301
  version             5.6.38-83.0-log
  server_id           1379557
  has_gtid            0
  binlog_enable       1
  tx_isolation        REPEATABLE-READ
  binlog_format       MIXED
  charset             utf8
  max_packet          1024MB
  read_only           0
    +-10.0.21.7:3301
    version             5.6.38-83.0-log
    server_id           1445093
    has_gtid            0
    binlog_enable       1
    tx_isolation        REPEATABLE-READ
    binlog_format       MIXED
    relay_master_file   mysql-bin.000083
    relay_behind_second 0
    charset             utf8
    max_packet          1024MB
    read_only           0
    repl_check          OK
2019-05-09T18:43:25 master generate 0 binlog files at per hours
```
use `--help` option for more usage message.

[Back to TOC](#table-of-contents)

sys-slow-delete-file
====================

`type: c`

truncate a file from begining, fork from [fallocate.c](https://github.com/util-linux/util-linux/blob/v2.23.2/sys-utils/fallocate.c).

> use fallocate FALLOC_FL_COLLAPSE_RANGE mode, note the -o and -l option must be multiple IO Block size(most filesystem is 4096 bytes)
> note: FALLOC_FL_COLLAPSE_RANGE is not support in lower kernel version(such as `centos 6 - 2.6.32`).

truncate 10MB from begining:
```
✗ ls -hl /tmp/test.csv 
-rw-r--r-- 1 root root 75M Mar 27 15:40 /tmp/test.csv

✗ head -n 1 /tmp/test.csv 
'10035','371f523bbaa744c4b238084dce2a8061','2',1721062810,'行动',0,1,0,0,0,0

# truncate file content from begining
✗ sys-slow-delete-file -o 0 -l 10M -f /tmp/test.csv

✗ ls -hl /tmp/test.csv 
-rw-r--r-- 1 root root 65M Mar 27 16:46 /tmp/test.csv

✗ head -n 1 /tmp/test.csv
aa9ea02e4ac229e700','2',1721062810,'已恢复',0,1,1,0,0,0
```

use `-h` option for more usage message.

[Back to TOC](#table-of-contents)

sys-unmap-file
==============

`type: c`

unmap a file from file system cache, read more from [unmap_mysql_logs](https://github.com/yoshinorim/unmap_mysql_logs).

### Usage
```
$ free -m
            total          used        free      shared  buff/cache   available
Mem:          64216       22761        3188        3210       38266       37630

$ sys-unmap-file -f /var/lib/mysql/data/mysql-bin.000087 -n 90 -s

$ free -m
            total          used        free      shared  buff/cache   available
Mem:          64216       22760        3937        3210       37518       37631
```
use `-h` option to read more usage.


[Back_to_TOC](#table-of-contents)

sys-mapstat-file
================

`type: c`

get cache statistics for a file. read more from [nocache](https://github.com/Feh/nocache).

### Usage
```
$ sys-mapstat-file -f MySQL-Linux.x86_64.ssl101.tar.gz 
page in cache: 16791/16791 (100.0%) [filesize=67161.5K, pagesize=4K]
```

use `-h` option to read more usage.

[Back_to_TOC](#table-of-contents)


sys-needrestart
===============

`type: perl`

check and report the need restart services, does not support `auto restart` sevice.

**note**: only useful when Linux is running in systemd service. almost of the check method is reference from [needrestart](https://github.com/liske/needrestart).

### Usage

```
# sys-needrestart -p 1841
pid(1841) - [systemd-machined.service] is need restart.

# sys-needrestart
The following service should restart as it
uses deleted or non-existing binary file.

   pid   service
   1 - systemd manager
   526 - systemd-journald.service
   548 - lvm2-lvmetad.service
   560 - systemd-udevd.service
   765 - NetworkManager.service
   766 - polkit.service
   772 - irqbalance.service
   775 - systemd-logind.service
   1082 - tuned.service
```
use `--help` option for more usage message.

License
=======

MIT / BSD

[Back to TOC](#table-of-contents)
