#!/bin/bash
rm -f main.o main.hex
cppcheck -q .
avr-gcc -std=c99 -mmcu=attiny167 -Wall -Wextra -Wno-unused-function -Wunused-variable -Wfatal-errors -I. -Os -fpack-struct -fshort-enums -funsigned-bitfields main.c -o main.o -Wl,--gc-sections
# -E - after preprocessor
# -S - before assembling
flash=16000
sram=1000
text=-1
data=-1
bss=-1
#if [ $text == 0 ]
#then
# echo "lol"
#fi
avr-size main.o|grep -Eo '[0-9]+'|\
while read line;
do
if [ $text == -1 ]
then
text=$line
else
if [ $data == -1 ]
then
data=$line
else
if [ $bss == -1 ]
then
bss=$line
a0=`expr  $text + $data`
a=`expr 10000 '*' $a0 '/' $flash`
a1=`expr $a / 100`
a2=`expr $a % 100`
echo "flash used: $a1.$a2% ($a0 from $flash)"
a0=`expr  $bss + $data`
a=`expr 10000 '*' $a0 '/' $sram`
a1=`expr $a / 100`
a2=`expr $a % 100`
echo " SRAM used: $a1.$a2% ($a0 from $sram)"
fi
fi
fi
done
avr-objcopy -O ihex main.o main.hex && avrdude -q -q -p attiny167 -c usbasp -U flash:w:main.hex
