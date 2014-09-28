#!/bin/sh
make clean;
./autogen.sh;
./configure;
make -j8 && make install;
