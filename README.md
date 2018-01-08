uc3a3-xplained-templates
========================

Wasted **way** too much time getting Atmel's stuff up and running. There's an SDRAM chip on the board, an old port of FreeRTOS, and **no** mention of how to get everything working. Hopefully this will help you get going a little faster.

Everything here assumes your IDE is a plain ol' text editor, and you do your building with Make/GCC. I can't help you with IAR, or C++.

Atmel's ASF is very rigid and a pain in the butt for path structure. There's not a pretty way to setup your environment. I've tried to abstract the ASF's structure away as much as possible, but I can't fix everything. It's not a good idea to make an ASF-replacement-for-autoconf, or modify the ASF's files. If you can think of a simple, non-complicated way to improve on this, please let me know!

Dev Environment Setup
---------------------
* Get the board [here](http://www.digikey.com/product-detail/en/AT32UC3A3-XPLD/AT32UC3A3-XPLD-ND/2522717) for about $32.
* Make an account with atmel so you can download their super secret files
* Download the dev board [documentation](http://www.atmel.com/Images/doc32159.pdf)
* Download the avr32 toolchain and header files for linux [here](http://www.microchip.com/avr-support/avr-and-sam-downloads-archive)
* Download the ASF [here](http://www.microchip.com/avr-support/avr-and-sam-downloads-archive)
* Extract all three downloads to ~/atmel or /opt
* Symlink or move the headers into the toolchain (see below)
* Add the avr32 toolchain to your path by sourcing setup\_env.sh in your ~/.bashrc
* Install [dfu-programmer](http://dfu-programmer.sourceforge.net/) (Ubuntu 12.04 has this in their repos)
* Add an entry in udev for the uc3a3 board so you don't need to run sudo. Restart udev

Sample Dev Environment Layout
-----------------------------
Directory names have been truncated for sanity's sake.

    ~/atmel
    ~/atmel/asf-3.17.0 (Atmel's "drivers" here)
    ~/atmel/atmel-headers
    ~/atmel/avr32-gnu-toolchain/
    Symlink ~/atmel/avr32-gnu-toolchain/avr32/include/avr32 to ~/atmel/atmel-headers/avr32

Sample Project Layout
---------------------
**NOTE:** Put or symlink your projects in asf/avr32/applications

    project/
    project/board (If you spin your own board)
    project/board/gcc (Run "make dfu" here)

Programming the Board
---------------------
    cd led-blink/xplained/gcc
    # (Here, jump reset to ground while holding SW0 down.)
    make -j8 dfu

FAQ
---
**Q:** I'm getting this error from make:

    No rule to make target `avr32/applications/led-blink/main.o', needed by `led-blink.elf'.

**A:** Don't forget to symlink led-blink into avr32/applications. It's Atmel's annoying directory structure.
