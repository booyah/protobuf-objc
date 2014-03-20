#!/bin/sh
make clean;
./autogen;
./configure;
make && make install;
