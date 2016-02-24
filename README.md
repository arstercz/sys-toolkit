# sys-toolkit

Some useful scripts to sysadmins/dbas.

## sysgenpass

`type: perl`

Generate complex random passwords.

Example:
```
$ ./sysgenpass 
IEZQS_hW7=exO}JG@L
```
help message: ./sysgenpass --help 

## sysnton

`type: perl`

Convert specified number to binary/octal/decimal/hexadecimal format.

Example:
```
$ ./sysnton -n 0b1111
  bin: 0b1111
  oct: 017 
  dec: 15 
  hex: 0x0F
$ ./sysnton -n 017
  bin: 0b1111
  oct: 017 
  dec: 15 
  hex: 0x0F
$ ./sysnton -n 15
  bin: 0b1111
  oct: 017 
  dec: 15 
  hex: 0x0F
$ ./sysnton -n 0x0F
  bin: 0b1111
  oct: 017 
  dec: 15 
  hex: 0x0F
```
help message: ./sysnton --help

## syspubip

`type: shell`

Get my public ip address by curl command.
```
$ ./syspubip 
Get public ip address:
110.89.157.218
```
Can be used with no args.
