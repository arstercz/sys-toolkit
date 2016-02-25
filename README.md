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
Can be used without args.
