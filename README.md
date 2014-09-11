spherO
======

Dependencies
============

Built the dependencies with:

    autoconf
    ./configure
    make
    sudo make install

Then simply `make test`.

Base
----

    sudo apt-get install build-essential autoconf libgtkmm-2.4-dev

libunicap
---------

    sudo apt-get install libv4l-dev
    cd /usr/include/linux
    sudo ln -s ../libv4l1-videodev.h videodev.h

libunicapgtk
------------

    sudo apt-get install libgtk2.0-dev libxv-dev

libucil
-------

    sudo apt-get install intltool
