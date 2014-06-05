#
# Adapted from Atmel's ASF
#

# Get the project name
MKFILE_PATH := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BOARD_PATH := $(abspath $(addsuffix /.., $(MKFILE_PATH)))
PROJ_PATH := $(abspath $(addsuffix /.., $(BOARD_PATH)))

BOARD_NAME := $(shell basename $(BOARD_PATH))
PROJ_NAME := $(shell basename $(PROJ_PATH))

# Relative to ASF_PATH, because Atmel's Makefile doesn't like absolute
# include paths. >:C
PROJ_ROOT := $(addprefix avr32/applications/, $(PROJ_NAME))

# Target CPU architecture: ap, ucr1, ucr2 or ucr3
ARCH = ucr2

# Target part: none, ap7xxx or uc3xxxxx
PART = uc3a3256

# Target device flash memory details (used by the avr32program programming
# tool: [cfi|internal]@address
FLASH = internal@0x80000000

# Clock source to use when programming; xtal, extclk or int
PROG_CLOCK = int

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET = $(PROJ_NAME).elf

# List of C source files.
CSRCS = \
       $(PROJ_ROOT)/main.c                                \
       $(PROJ_ROOT)/util/init.c                           \
       $(PROJ_ROOT)/util/hexdump.c                        \
       $(PROJ_ROOT)/util/memcheck.c                       \
       avr32/boards/uc3_a3_xplained/init.c                \
       avr32/boards/uc3_a3_xplained/led.c                 \
       avr32/drivers/flashc/flashc.c                      \
       avr32/drivers/ebi/sdramc/sdramc.c                  \
       avr32/drivers/intc/intc.c                          \
       avr32/drivers/gpio/gpio.c                          \
       avr32/drivers/usart/usart.c                        \
       common/utils/stdio/read.c                          \
       common/utils/stdio/write.c                         \
       common/services/clock/uc3a3_a4/sysclk.c            \

# List of assembler source files.
ASSRCS = \
       avr32/drivers/intc/exception.S                     \
       $(PROJ_ROOT)/lowlevel/startup_uc3.S                \
       avr32/utils/startup/trampoline_uc3.S

# List of include paths.
INC_PATH = \
       $(PROJ_ROOT)/util                                  \
       $(PROJ_ROOT)/$(BOARD_NAME)                         \
       $(PROJ_ROOT)/$(BOARD_NAME)/gcc                     \
       avr32/boards                                       \
       avr32/boards/uc3_a3_xplained                       \
       avr32/drivers/cpu/cycle_counter                    \
       avr32/drivers/flashc                               \
       avr32/drivers/ebi/sdramc                           \
       avr32/drivers/gpio                                 \
       avr32/drivers/intc                                 \
       avr32/drivers/usart                                \
       avr32/utils                                        \
       avr32/utils/preprocessor                           \
       common/boards                                      \
       common/services/clock                              \
       common/services/delay                              \
       common/services/serial                             \
       common/utils                                       \
       common/utils/stdio                                 \
       common/utils/stdio/stdio_serial                    \

# Additional search paths for libraries.
LIB_PATH =  

# List of libraries to use during linking.
LIBS =

# Path relative to top level directory pointing to a linker script.
LINKER_SCRIPT = $(PROJ_ROOT)/$(BOARD_NAME)/gcc/link_uc3a3256.lds

# Additional options for debugging. By default the common Makefile.in will
# add -g3.
DBGFLAGS = 

# Application optimization used during compilation and linking:
# -O0, -O1, -O2, -O3 or -Os
OPTIMIZATION = -Os

# Extra flags to use when archiving.
ARFLAGS = 

# Extra flags to use when assembling.
ASFLAGS = 

# Extra flags to use when compiling.
CFLAGS = 

# Extra flags to use when preprocessing.
#
# Preprocessor symbol definitions
#   To add a definition use the format "-D name[=definition]".
#   To cancel a definition use the format "-U name".
#
# The most relevant symbols to define for the preprocessor are:
#   BOARD      Target board in use, see boards/board.h for a list.
#   EXT_BOARD  Optional extension board in use, see boards/board.h for a list.
CPPFLAGS = \
       -D BOARD=USER_BOARD

# Extra flags to use when linking
LDFLAGS = \
       -nostartfiles -Wl,-e,_trampoline

# Pre- and post-build commands
PREBUILD_CMD = 
POSTBUILD_CMD = 
