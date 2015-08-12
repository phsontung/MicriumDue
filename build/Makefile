#!/usr/bin/make
# makefile for the arduino due.
#


#user specific settings:
ATMEL_DIR:=/media/sontung/SOURCE/IoT/atmel/xdk-asf-3.25.0

#then some general settings. They should not be necessary to modify.
CXX:=/usr/bin/arm-none-eabi-g++
CC:=/usr/bin/arm-none-eabi-gcc
C:=$(CC)
TMPDIR:=$(PWD)/generated
AR:=/usr/bin/arm-none-eabi-ar

PROJ_PATH:=..
PROJNAME:=DueMicrium

#all these values are hard coded and should maybe be configured somehow else,
#like olikraus does in his makefile.
DEFINES:=-Dprintf=iprintf \
	-DF_CPU=84000000L \
	-DARDUINO=152 \
	-D__SAM3X8E__ \
	-DBOARD=ARDUINO_DUE_X

INCLUDES:=-I$(PROJ_PATH)/uCOS-III/Source \
			-I$(PROJ_PATH)/uCOS-III/Ports/ARM-Cortex-M3/Generic/GNU \
			-I$(PROJ_PATH)/uC-CPU/ARM-Cortex-M3/GNU \
			-I$(PROJ_PATH)/uC-CPU \
			-I$(PROJ_PATH)/uC-LIB \
			-I$(PROJ_PATH)/EvalBoards/Atmel/SAM3X8E/BSP

#also include the application dir
INCLUDES += -I$(PROJ_PATH)/EvalBoards/Atmel/SAM3X8E/uCOS-III

#compilation flags common to both c and c++
COMMON_FLAGS:=-g -Os -w  -fpermissive -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -mcpu=cortex-m3  -mthumb

CFLAGS:=$(COMMON_FLAGS)
CXXFLAGS:=$(COMMON_FLAGS) -fno-rtti -fno-exceptions

# FreeRTOS Source
OSSRC:=$(shell ls $(PROJ_PATH)/uCOS-III/Source/*.c \
			$(PROJ_PATH)/uCOS-III/Ports/ARM-Cortex-M3/Generic/GNU/os_cpu_c.c \
			$(PROJ_PATH)/uCOS-III/Ports/ARM-Cortex-M3/Generic/GNU/os_cpu_a.s)

#uC-LIB
OSSRC += $(shell ls $(PROJ_PATH)/uC-LIB/*.c \
			$(PROJ_PATH)/uC-LIB/Ports/ARM-Cortex-M3/GNU/lib_mem_a.s)

#uC-CPU
OSSRC += $(PROJ_PATH)/uC-CPU/cpu_core.c \
			$(PROJ_PATH)/uC-CPU/ARM-Cortex-M3/GNU/cpu_a.s \
			$(PROJ_PATH)/uC-CPU/ARM-Cortex-M3/GNU/cpu_c.c

#BSP
OSSRC +=$(PROJ_PATH)/EvalBoards/Atmel/SAM3X8E/BSP/startup_sam3x.c \
		$(PROJ_PATH)/EvalBoards/Atmel/SAM3X8E/BSP/exceptions.c \
		$(PROJ_PATH)/EvalBoards/Atmel/SAM3X8E/BSP/system_sam3x.c \
		$(PROJ_PATH)/EvalBoards/Atmel/SAM3X8E/BSP/bsp.c \
		$(PROJ_PATH)/EvalBoards/Atmel/SAM3X8E/uCOS-III/app.c \
			$(PROJ_PATH)/EvalBoards/Atmel/SAM3X8E/uCOS-III/os_app_hooks.c

OSOBJS:=$(addprefix $(TMPDIR)/UCOSIII/, $(notdir $(OSSRC)))
OSOBJS:=$(addsuffix .o, $(OSOBJS))

#Atmel
ATSRC:= $(ATMEL_DIR)/common/services/clock/sam3x/sysclk.c \
		$(ATMEL_DIR)/common/services/spi/sam_spi/spi_master.c \
		$(ATMEL_DIR)/common/utils/interrupt/interrupt_sam_nvic.c \
		$(ATMEL_DIR)/common/utils/stdio/read.c \
		$(ATMEL_DIR)/common/utils/stdio/write.c \
		$(ATMEL_DIR)/common/drivers/nvm/sam/sam_nvm.c \
		$(ATMEL_DIR)/sam/boards/arduino_due_x/init.c \
		$(ATMEL_DIR)/sam/boards/arduino_due_x/led.c \
		$(ATMEL_DIR)/sam/drivers/pdc/pdc.c \
		$(ATMEL_DIR)/sam/drivers/pio/pio.c \
		$(ATMEL_DIR)/sam/drivers/pio/pio_handler.c \
		$(ATMEL_DIR)/sam/drivers/pmc/pmc.c \
		$(ATMEL_DIR)/sam/drivers/pmc/sleep.c \
		$(ATMEL_DIR)/sam/drivers/uart/uart.c \
		$(ATMEL_DIR)/sam/drivers/usart/usart.c \
		$(ATMEL_DIR)/sam/drivers/spi/spi.c \
		$(ATMEL_DIR)/sam/drivers/efc/efc.c \
		$(ATMEL_DIR)/sam/drivers/tc/tc.c \
		$(ATMEL_DIR)/sam/drivers/wdt/wdt.c \
		$(ATMEL_DIR)/sam/drivers/trng/trng.c \
		$(ATMEL_DIR)/sam/drivers/rstc/rstc.c \
		$(ATMEL_DIR)/sam/services/flash_efc/flash_efc.c \
		$(ATMEL_DIR)/sam/utils/syscalls/gcc/syscalls.c \
		$(ATMEL_DIR)/sam/drivers/dmac/dmac.c
ATOBJS:=$(addprefix $(TMPDIR)/Atmel/, $(notdir $(ATSRC)))
ATOBJS:=$(addsuffix .o, $(ATOBJS))

ATMEL_INC:=-I$(ATMEL_DIR)/common/boards \
			-I$(ATMEL_DIR)/common/services/clock \
			-I$(ATMEL_DIR)/common/services/clock/sam3x \
			-I$(ATMEL_DIR)/common/services/gpio \
			-I$(ATMEL_DIR)/common/services/ioport \
			-I$(ATMEL_DIR)/common/services/freertos/sam \
			-I$(ATMEL_DIR)/common/services/serial/sam_uart \
			-I$(ATMEL_DIR)/common/services/serial \
			-I$(ATMEL_DIR)/common/services/spi \
			-I$(ATMEL_DIR)/common/services/sam_spi \
			-I$(ATMEL_DIR)/common/services/spi/sam_spi/module_config \
			-I$(ATMEL_DIR)/common/utils \
			-I$(ATMEL_DIR)/common/utils/stdio/stdio_serial \
			-I$(ATMEL_DIR)/common/drivers/nvm \
			-I$(ATMEL_DIR)/common/nvm/sam/module_config \
			-I$(ATMEL_DIR)/sam/boards \
			-I$(ATMEL_DIR)/sam/boards/arduino_due_x \
			-I$(ATMEL_DIR)/sam/drivers/pio \
			-I$(ATMEL_DIR)/sam/drivers/pmc \
			-I$(ATMEL_DIR)/sam/drivers/tc \
			-I$(ATMEL_DIR)/sam/drivers/trng \
			-I$(ATMEL_DIR)/sam/drivers/pdc \
			-I$(ATMEL_DIR)/sam/drivers/uart \
			-I$(ATMEL_DIR)/sam/drivers/usart \
			-I$(ATMEL_DIR)/sam/drivers/spi \
			-I$(ATMEL_DIR)/sam/drivers/efc \
			-I$(ATMEL_DIR)/sam/utils \
			-I$(ATMEL_DIR)/sam/drivers/wdt \
			-I$(ATMEL_DIR)/sam/utils/cmsis/sam3x/include \
			-I$(ATMEL_DIR)/sam/utils/cmsis/sam3x/source/templates \
			-I$(ATMEL_DIR)/sam/utils/cmsis/sam3x/include/component \
			-I$(ATMEL_DIR)/sam/utils/header_files \
			-I$(ATMEL_DIR)/sam/utils/preprocessor \
			-I$(ATMEL_DIR)/sam/services/flash_efc \
			-I$(ATMEL_DIR)/thirdparty/CMSIS/Include \
			-I$(ATMEL_DIR)/thirdparty/CMSIS/Lib/GCC \
			-I$(ATMEL_DIR)/sam/boards/arduino_due_x/board_config \
			-I$(ATMEL_DIR)/config \
			-I$(ATMEL_DIR)/common/services/clock/sam3x/module_config \
			-I$(ATMEL_DIR)/common/services/clock/sam3x \
			-I$(ATMEL_DIR)/sam/drivers/dmac \
			-I$(ATMEL_DIR)/sam/drivers/rstc
CFLAGS += -std=gnu99


default:
	@echo default rule, does nothing. Try make compile or make upload.
	@$(foreach src,$(CTLSRC), @echo $(src))

#This rule is good to just make sure stuff compiles, without having to wait
#for bossac.
compile: $(TMPDIR)/$(PROJNAME).elf

#This is a make rule template to create object files from the source files.
# arg 1=src file
# arg 2=object file
# arg 3= XX if c++, empty if c
define OBJ_template
$(2): $(1)
	$(C$(3)) -MD -c $(C$(3)FLAGS) $(DEFINES) $(4) $(1) -o $(2)
endef
#now invoke the template both for c++ sources
#$(foreach src,$(CORESRCXX), $(eval $(call OBJ_template,$(src),$(addsuffix .o,$(addprefix $(TMPDIR)/core/,$(notdir $(src)))),XX) ) )

OS_INCLUDES:= $(INCLUDES) $(ATMEL_INC)
#...and for c sources:
$(foreach src,$(OSSRC), $(eval $(call OBJ_template,$(src),$(addsuffix .o,$(addprefix $(TMPDIR)/UCOSIII/,$(notdir $(src)))),,$(OS_INCLUDES)) ) )

#...and for c sources:
$(foreach src,$(ATSRC), $(eval $(call OBJ_template,$(src),$(addsuffix .o,$(addprefix $(TMPDIR)/Atmel/,$(notdir $(src)))),,$(ATMEL_INC)) ) )


clean:
	test ! -d $(TMPDIR) || rm -rf $(TMPDIR)

.PHONY: upload default

$(TMPDIR):
	mkdir -p $(TMPDIR)/UCOSIII/
	mkdir -p $(TMPDIR)/Atmel/

#include the dependencies for our own files
-include $(MYOBJFILES:.o=.d)

-include $(FREEOBJS:.o=.d)

#link our own object files with core to form the elf file
$(TMPDIR)/$(PROJNAME).elf: $(TMPDIR) $(OSOBJS) $(ATOBJS)
	$(CC) -Os -Wl,--gc-sections -mcpu=cortex-m3 -T$(ATMEL_DIR)/sam/utils/linker_scripts/sam3x/sam3x8/gcc/flash.ld -Wl,-Map,ucos.map -o $@ -L$(TMPDIR) -lm -lgcc -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -Wl,--warn-unresolved-symbols -Wl,--start-group  $(OSOBJS) $(ATOBJS) -Wl,--end-group

#copy from the hex to our bin file (why?)
$(TMPDIR)/$(PROJNAME).bin: $(TMPDIR)/$(PROJNAME).elf
	$(ADIR)/tools/g++_arm_none_eabi/bin/arm-none-eabi-objcopy -O binary $< $@

