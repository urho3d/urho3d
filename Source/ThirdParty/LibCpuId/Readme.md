libcpuid
========

libcpuid provides CPU identification for the x86 (and x86_64).
For details about the programming API, please see the docs
on the project's site (http://libcpuid.sourceforge.net/)

Configuring after checkout
--------------------------

Under linux, where you download the sources, there's no
configure script to run. This is because it isn't a good practice to keep
such scripts in a source control system. To create it, you need to run the
following commands once, after you checkout the libcpuid sources
from github:

        1. run "libtoolize"
        2. run "autoreconf --install"

You need to have `autoconf`, `automake` and `libtool` installed.

After that you can run `./configure` and `make` - this will build
the library.

`make dist` will create a tarball (with "configure" inside) with the
sources.

Users
-----

So far, I'm aware of the following projects which utilize libcpuid:

* CPU-X (https://github.com/X0rg/CPU-X)
* fre:ac (https://www.freac.org/)
* ucbench (http://anrieff.net/ucbench)

We'd love to hear from you if you are also using libcpuid and want your project listed above.
