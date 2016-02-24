# sys-toolkit

Some useful scripts to sysadmins/dbas.

## sysgenpass

Generate complex random passwords.

Example:
```
$ ./sysgenpass 
IEZQS_hW7=exO}JG@L
```

## sysnton

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
