Simple dot parser implemented using regular expressions -- July, 2016


# Introduction #

This library implements a dot language parser using regular
expressions.

The formal specification of the language can be found at
http://www.graphviz.org/doc/info/lang.html but this library only
implements a subset of these rules.

Remarkably:

1. It does not recognize HTML strings.
2. Escape quotes (\") cannot be used to name IDs.
3. The kewyord `strict` is not recognized yet
4. Likewise, it is not possible to define subgraphs with the keyword `subgraph`.

Note that both edges and nodes can be given an `attr_list` which
consists of a comma separated list of assignments given between square
brackets.


# Install #

To compile the libdot library you can use the following command:

    $ ./configure; make

The first command, `./configure`, will go through a number of tests
and, if it does not find any error, it will create the `Makefile` that
is executed with the second command.

To install the library just type:

    $ make install

By default, the library is installed in `/usr/local/lib` and the
header files are installed in `/usr/local/include/libdot-MAJOR.MINOR`
(where *MAJOR* and *MINOR* are substituted by the version numbers of
this library) To change the include and lib dirs use `--prefix` with
`./configure`:

    $ ./configure --prefix=/home/myuser/local; make

It will automatically create a `Makefile` which is specifically
instructed to copy all the binaries and headers in
`/home/myuser/local`

To uninstall the binaries and headers of the libdot library just
execute:

    $ make uninstall

Finally, be aware that it might be necessary to prepend both `make
install` and `make uninstall` with `sudo` in case you are installing
in su-protected directories such as `/usr/local`


# License #

libdot is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

libdot is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with libdot.  If not, see <http://www.gnu.org/licenses/>.


# Author #

Carlos Linares Lopez <carlos.linares@uc3m.es>

