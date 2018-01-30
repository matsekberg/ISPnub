ISPnub
======

Firmware for stand-alone AVR programmer module.

ISPnub is a stand-alone AVR programming module. The programming instructions
are defined within scripts. These scripts are converted with an additional
tool (ISPnubCreator) into a binary format and are stored in the flash of
ISPnub's ATmega1284P. This firmware interprets the binary programming
instructions and executes it on the connected target controller.
 
The firmware hex file is packed into the JAR file of ISPnubCreator which
merges the firmware hex data with programming instructions from scripts.
 
New in matsekberg-fork, matsekberg-usart branch:
The ISPnub firmware emits status on a serial port, USART0. Two letters representing the script command, a colon and then a 0 or 1 depending on the failure or success of the script command.
