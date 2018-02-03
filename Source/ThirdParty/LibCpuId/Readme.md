libcpuid
========

libcpuid provides CPU identification for the x86 (and x86_64).
For details about the programming API, you might want to 
take a look at the project's website on sourceforge
(http://libcpuid.sourceforge.net/). There you'd find a short
[tutorial](http://libcpuid.sf.net/documentation.html), as well
as the full [API reference](http://libcpuid.sf.net/doxy).

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

Testing
-------

After any change to the detection routines or match tables, it's always
a good idea to run `make test`. If some test fails, and you're confident
that the test is wrong and needs fixing, run `make fix-tests`.

You can also add a new test (which is basically a file containing
the raw CPUID data and the expected decoded items) by using 
`tests/create_test.py`. The workflow there is as follows:

1. Run "cpuid_tool" with no arguments. It will tell you that it
   has written a pair of files, raw.txt and report.txt. Ensure
   that report.txt contains meaningful data.
2. Run "tests/create_test.py raw.txt report.txt > «my-cpu».test"
3. Use a proper descriptive name for the test (look into tests/amd
   and tests/intel to get an idea) and copy your test file to an
   appropriate place within the tests directory hierarchy.

For non-developers, who still want to contribute tests for the project,
use [this page](http://libcpuid.sourceforge.net/bugreport.php) to report
misdetections or new CPUs that libcpuid doesn't handle well yet.

Users
-----

So far, I'm aware of the following projects which utilize libcpuid:

* CPU-X (https://github.com/X0rg/CPU-X)
* fre:ac (https://www.freac.org/)
* ucbench (http://anrieff.net/ucbench)
* Multiprecision Computing Toolbox for MATLAB (https://www.advanpix.com/)

We'd love to hear from you if you are also using libcpuid and want your project listed above.
