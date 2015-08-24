===========
vmod_shards
===========

--------------------------
Varnish Consistent Hashing
--------------------------

:Author: Matt Robenolt
:Date: 2014-01-30
:Version: 1.0
:Manual section: 3

SYNOPSIS
========

import shards;

DESCRIPTION
===========

Generate a consistent id for utilizing multiple file-backed storage backends.

FUNCTIONS
=========

shards
------

Prototype
        ::

                id(STRING key, INT shards)
Return value
	STRING
Description
	Returns a consistent shard id based on *key* using murmur3
Example
        ::

                set beresp.storage = "s" + shards.id(req.url, 16);

INSTALLATION
============

The source tree is based on autotools to configure the building, and
does also have the necessary bits in place to do functional unit tests
using the ``varnishtest`` tool.

Building requires the Varnish header files and uses pkg-config to find
the necessary paths.

Usage::

 ./autogen.sh
 ./configure

If you have installed Varnish to a non-standard directory, call
``autogen.sh`` and ``configure`` with ``PKG_CONFIG_PATH`` pointing to
the appropriate path. For shards, when varnishd configure was called
with ``--prefix=$PREFIX``, use

 PKG_CONFIG_PATH=${PREFIX}/lib/pkgconfig
 export PKG_CONFIG_PATH

Make targets:

* make - builds the vmod.
* make install - installs your vmod.
* make check - runs the unit tests in ``src/tests/*.vtc``
* make distcheck - run check and prepare a tarball of the vmod.

In your VCL you could then use this vmod along the following lines::

        import shards;

        sub vcl_fetch {
                # Set which storage shard to actually store the data in
                set beresp.storage = "s" + shards.id(req.url, 16);
        }

COMMON PROBLEMS
===============

* configure: error: Need varnish.m4 -- see README.rst

  Check if ``PKG_CONFIG_PATH`` has been set correctly before calling
  ``autogen.sh`` and ``configure``

COPYRIGHT
=========

This document is licensed under the same license as the
libvmod-shards project. See LICENSE for details.

* Copyright (c) 2014 Matt Robenolt
