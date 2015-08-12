# Micrium (uCos III) Porting on Arduino Due

## Setup
- Download Atmel Software Framework (asf) from Atmel website.
- Change build/Makefile:
    - ATMEL_DIR:=/path/to/your/atmel/xdk-asf-3.25.0
- Download and setup Arduino SDK. Update path for bossac flash command /path/to/arduino/tools/bossac/1.3a-arduino/bossac

## Build
- cd build/
- make clean ; make compile

## Flash to Arduino board
- run flash.sh

## Limitation
- Don't support statictis task, or time measurement (Temporary don't support CPU_TS_TmrInit, CPU_TS_TmrRd)
