# simpleDataIO
This set of code allows communications between a PC connected to a master and a slave connected to a software serial port.

There are two programs.

forward.ino is really the Master

samplepixelcode.ino is really the slave which controls a sensor and responds to a few simple, single letter commands.
UPPER or lower case letters may be used

b  -  Deactivate actuator (Block view)

c  -  Return state (Condition) of actuator

d  -  Acquire and return a set of 64 ir Data readings

i  -  Take Arduino temperature (commented out, but with a link to code to set this up)

p  -  One second delay (a Pause)

t  -  Take baseplate Temperature

v  -  Activate actuator (View)
