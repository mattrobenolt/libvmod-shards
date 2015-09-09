#!/bin/sh
set -x

git submodule update --init
./autogen.sh && ./configure && make
dpkg-buildpackage -uc -us -b
