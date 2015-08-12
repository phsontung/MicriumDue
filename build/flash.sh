arm-none-eabi-objcopy -O binary generated/DueMicrium.elf generated/DueMic.bin

stty -F /dev/ttyACM0 raw ispeed 1200 ospeed 1200 cs8 -cstopb ignpar eol 255 eof 255
/home/sontung/.arduino15/packages/arduino/tools/bossac/1.3a-arduino/bossac  -R -e -w -v -b generated/DueMic.bin
