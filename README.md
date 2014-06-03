uc3a3-xplained-templates
========================

Wasted **way** too much time getting Atmel's stuff up and running. There's an SDRAM chip on the board, an old port of FreeRTOS, and **no** mention of how to get everything working. Hopefully this will help you get going a little faster.

Everything here assumes your IDE is a plain ol' text editor, and you do your building with Make/GCC. I can't help you with IAR.

Dev Environment Setup
---------------------
* Get the board [here](http://www.digikey.com/product-detail/en/AT32UC3A3-XPLD/AT32UC3A3-XPLD-ND/2522717) for about $32.
* Make an account with atmel so you can download their super secret files
* Download the avr32 toolchain and header files for linux [here](http://www.atmel.com/tools/atmelavrtoolchainforlinux.aspx)
* Download the ASF [here](http://www.atmel.com/tools/avrsoftwareframework.aspx)
* Extract all three downloads to ~/atmel or /opt
* Symlink or move the headers into the toolchain
* Add the avr32 toolchain to your path
* Install dfu-programmer (Ubuntu 12.04 has this in their repos)
* Add an entry in udev for the uc3a3 board, so you don't need to run sudo

Dev Environment Layout
----------------------
Directory names have been truncated for sanity's sake.
    ~/atmel
    ~/atmel/asf-3.17.0 (Atmel's "drivers" here)
    ~/atmel/atmel-headers
    ~/atmel/avr32-gnu-toolchain/
    Symlink ~/atmel/avr32-gnu-toolchain/avr32/include/avr32 to ~/atmel/atmel-headers/avr32

Project Layout
--------------
Put / symlink your projects in asf/avr32/applications
    project/
    project/board (If you spin your own board)
    project/board/gcc (Run "make dfu" here)
