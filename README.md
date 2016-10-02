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
3. C comments (`/* ... */`) are not handled yet. Instead, only C++
comments (`//`) are acknowledged.
4. The kewyord `strict` is not recognized yet
5. Likewise, it is not possible to define subgraphs with the keyword
`subgraph`.

6. According to the official definitions of dot: *Edges can be
specified as `->` in directed graphs and `--` in undirected
graphs*. However, this parser acknowledges its usage in both cases
with the obvious syntax. This actually makes that the graph type is
not relevant at all.

Note that both edges and nodes can be given an `attr_list` which
consists of a comma separated list of assignments given between square
brackets.

It also includes the code to create an executable (called `parser`)
which effectively parses the contents of any dot file.


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

Be aware that it might be necessary to prepend both `make
install` and `make uninstall` with `sudo` in case you are installing
in su-protected directories such as `/usr/local`

To compile the `parser`, go to the directory `parser/` and use the
following command:

    $ ./configure; make

The same instructions given above for customizing the configuration of
the library can be used here to customize the creation of the
makefile. To remove ancillary files use the command:

    $ make distclean


# Examples #

The directory `parser/examples` contains various dot files that
represent simple graphs. Some come with no attributes, while others
use attributes to qualify nodes and edges.

To parse a dot file (e.g., `parser/examples/graph1.dot`) go to the
directory `parser/` and compile it following the instructions given
above. Then execute:

    $ ./parser --file examples/graph1.dot

     Type: graph
     Name: prueba

As shown above, the parser will respond with the type of graph
(`graph` which is an undirected graph) and its name, which is
optional, *prueba*. It is also possible to see how the parser
processes separately each block:

    $ ./parser --file examples/graph1.dot --verbose

     [TYPE <graph>]
     [NAME <prueba>]
     [--- Block begin found ---]
     [VERTEX NAME <s>]
     [EDGE TYPE <-->]
     [ --- Beginning multiple target specification ---]
     [TARGET NAME <A>]
     [TARGET NAME <B>]
     [TARGET NAME <C>]
     [ --- Ending multiple target specification ---]
     [VERTEX NAME <A>]
     [EDGE TYPE <-->]
     [ --- Beginning multiple target specification ---]
     [TARGET NAME <B>]
     [TARGET NAME <t>]
     [ --- Ending multiple target specification ---]
     [VERTEX NAME <B>]
     [EDGE TYPE <-->]
     [TARGET NAME <t>]
     [VERTEX NAME <C>]
     [EDGE TYPE <-->]
     [ --- Beginning multiple target specification ---]
     [TARGET NAME <B>]
     [TARGET NAME <t>]
     [ --- Ending multiple target specification ---]
     [ --- Block end found ---]

     Type: graph
     Name: prueba
    
The parser precedes then the name and type of the graph with
information of each block as it was processed on the fly.

In case a graph contains attributes for nodes and/or edges, then use
`--show-attributes` to inspect them (in this case
`examples/graph2.dot` is used instead as the first graph contains no
attributes):

    $ ./parser --file examples/graph2.dot --show-attributes

     Type: graph
     Name: prueba
    
     Vertex A:
    	 h_cff: 10.10

     Vertex B:
	 h_cff: 1
	 h_pdb: 1.41
	 name: "(0,0)"

     Vertex C:
	 h_cff: 3.14159
	 h_ff: 1.0
	 h_pdb: 10.0

     Edge A -> s:
	 k: 1

     Edge A -> B:
	 k: 1

     Edge B -> t:
	 k: 1
	 name: "Optimal"

     Edge B -> C:
	 k: 1

     Edge t -> C:
	 k: 1

The output has been shorten to make it easy to read.

Finally, `parser` acknowledges two additional directives:

* `--help` provides additional information on the available commands
* `--version` provides the version of the implementation.


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

