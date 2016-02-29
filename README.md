# sys-toolkit

Some useful scripts to sysadmins/dbas.

## sys-genpass

`type: perl`

Generate complex random passwords.

Example:
```
$ ./sys-genpass 
IEZQS_hW7=exO}JG@L
```
help message: ./sys-genpass --help 

## sys-nton

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

## sys-pubip

`type: shell`

Get my public ip address by curl command.
```
$ ./sys-pubip 
Get public ip address:
110.89.157.218
```
Can be used without args, return error if execute 5 seconds.

## sys-ascii

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

## sys-mysql-summary

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

## sys-checkport

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
