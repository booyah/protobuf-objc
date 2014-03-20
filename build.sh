#!/bin/sh
make clean;
./autogen.sh;
./configure;
make && make install;
