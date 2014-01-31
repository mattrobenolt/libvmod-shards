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

                set beresp.backend = "s" + shards.id(req.url, 16);

INSTALLATION
============

The source tree is based on autotools to configure the building, and
does also have the necessary bits in place to do functional unit tests
using the varnishtest tool.

Usage::

 ./configure VARNISHSRC=DIR [VMODDIR=DIR]

`VARNISHSRC` is the directory of the Varnish source tree for which to
compile your vmod. Both the `VARNISHSRC` and `VARNISHSRC/include`
will be added to the include search paths for your module.

Optionally you can also set the vmod install directory by adding
`VMODDIR=DIR` (defaults to the pkg-config discovered directory from your
Varnish installation).

Make targets:

* make - builds the vmod
* make install - installs your vmod in `VMODDIR`
* make check - runs the unit tests in ``src/tests/*.vtc``

In your VCL you could then use this vmod along the following lines::

        import shards;

        sub vcl_fetch {
                # Set which backend shard to actually store the data in
                set beresp.backend = "s" + shards.id(req.url, 16);
        }

HISTORY
=======

This manual page was released as part of the libvmod-shards package.

COPYRIGHT
=========

This document is licensed under the same license as the
libvmod-shards project. See LICENSE for details.

* Copyright (c) 2014 Matt Robenolt
