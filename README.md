Introduction:
-------------
This package provide C/C++ lib wrapper to linux user space spidev
This pacakage is based on work done by Stefan Mavrodiev 
for the pyA20 python library https://pypi.python.org/pypi/pyA20


Warning
-------
if you want other user than root have access to spidev device you may probably need to add a file with the following udev rules in your /etc/udev.d directory. 

KERNEL=="spidev*", SUBSYSTEM=="spidev", GROUP="spi", MODE="0660"

add a spi groups and add user to this groups

How to build
------------

First of all you need cmake installed on your system.
into main directory do the following: 

* mkdir build
* cd build
* cmake ../
* make 
* make install

This will create 2 statics libraries  libspidev-lib.a and libspidev-lib++.a
You can link thoses libraries against your own code.

The sample directory contain a sample usage for c and for c++
you can compile it from main directory in this way.

* g++ sample/spidev-testcpp.cc -lspidev-lib++ -o spidev-testcpp
* gcc sample/spidev-testc.c -lspidev-lib -o spidev-testc

if you have any question you can contact me at lemouchon at gmail dot com.
