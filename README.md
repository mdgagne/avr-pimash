pimash
======

A Raspberry Pi/AVR based RIMS mash controller. This is currently a work-in-progress.


#### High-Level Overview

The pimash consists of three essential blocks that work together to operate a 120V Recirculated Mash System (RIMS) the user interacts with the control system in two way: 

1) Controls main power, heating element power, and pump power through a number of physical switches located on the RIMS controller. For safetly purposes power must be controlled through hard-wired switches/relays.

2) Controls and monitors the mash temperature set point (SP), mash temperature (PV), pump state, and mash schedule from a computer/handheld device (tablet, phone) and webpage hosted on a Raspberry Pi located in the controller.

