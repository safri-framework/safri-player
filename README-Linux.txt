The instructions in this file should help you to build and install the
Safri-Player from source on your system.

Dependencies
============

Before you start, make sure you have installed following libraries with it's developing packages:

  > Qt 4.7.* (maybe an older version of Qt4 works too)
  > Taglib


Compiling
============

You can compile the Safri-Player with the following commands:

  qmake
  make

To 'install' the binary run:

  make install

This will copy the application binary to the prepared bin folder where you can start Safri-Player
from. A 'real installation' to system folders isn't implemented yet. But feel free to put the bin folder to your system wherever you want it. ;)