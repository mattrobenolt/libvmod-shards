#!/bin/sh
set -x

export VARNISH_VERSION=${VARNISH_VERSION:="3.0.5"}
export VARNISHSRC=../varnish-${VARNISH_VERSION}
export DEBIAN_VARNISH_SRC=$VARNISHSRC
export VMODDIR=/usr/lib/varnish/vmods

git submodule update --init
./autogen.sh && ./configure && make
dpkg-buildpackage -uc -us -b
