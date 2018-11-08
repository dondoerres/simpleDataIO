# simpleDataIO
This set of code allows communications between a PC connected to a master and a slave connected to a software serial port.

There are two programs.

forward.ino is really the Master

samplepixelcode is really the slave which controls a sensor and responds to a few simple, single letter commands.
UPPER or lower case letters may be used

b  -  deactivate actuator (Block view)
c  -  Return state of actuator
d  -  acquire and return a set of 64 ir readings
i  -  Take Arduino temperature (commented out, but with a link to code to set this up)
p  -  One second delay
t  -  Take baseplate temperature
v  -  activate actuator (View)
