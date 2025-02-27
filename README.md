# Introduction #

This library implements a DOT language parser using regular expressions.

The formal specification of the language can be found at http://www.graphviz.org/doc/info/lang.html but this library only implements a subset of these rules. See the documentation for further
details.

Remarkably:

There are a number of good diferences with the official DOT language which are:

* The keyword `strict` is not recognized. Moreover, the parser does not check whether the graph is truly directed or undirected, e.g., it is possible to declare a `digraph` and then to use the `edge_op` `--`

* *Label statements* consist of a single assignment to an ID, i.e., they can not be continued with other expressions as in the official DOT language.

* There are not *subgraphs*. The DOT language implemented in this library only allows to define edges between vertices as in the usual mathematical formulation of a graph.

* There are not *ports* and, indeed, the subset implemented here is not selected for any specific purpose, but for the intention of defining graphs in a general sense.

On the other hand, the language parsed by this library allows edges to be qualified with attributes as much as vertices with an `attr_list`, so that whereas the official DOT language complains with statements such as `a -> [ color = red ] b;`, this library actually parses them correctly.
  
The language parsed by this library allows the definition of paths, as in `a -> b -> c;` or blocks with multiple vertices, such as in `a -> { b c d };`. As in the official DOT language, a block with multiple vertices ends an edge statement, so that expressions such as `{ a b c } -- { d e f };` actually raise a syntax error. Of course, both forms can be mixed in a single statement such as in `a -> b -- c -- { d e f};`.

Another relevant difference is the definition of IDs. For the purpose of this library, IDs are defined as a collection of alphanumeric characters and the underscore `_`, so that `81_` is a valid ID. IDs are used for naming graphs (which is entirely optional) or for declaring attributes. Attributes give a VALUE to an ID which are defined as:

* Either an integer number with or without sign, e.g., `12`, `+12` or `-12`; or

* A floating-point number which can be in scientific notation or not. Examples are: `12.13`, `.019e-12` and `1003.`; or

* A string which can be either an alphanumeric sequence which does not start with a number, such as `red`, or a double quoted string which can then contain any characters, such as `"I'm a double quoted string"`.


# Dependencies #

`Libdot` uses [Google Test](https://github.com/google/googletest) for defining *Test cases* and running *Unit tests*. Thus, it should be installed in the target system.

In addition, `Libdot` uses [Sphinx](www.sphinx-doc.org) for automatically generating the documentation in PDF and HTML formats. If it is required to generate the documentation in PDF then `pdflatex` should be also available in the target system.

Finally, `Libdot` uses c++17.


# Install #

To compile the `Libdot` library you can use the following command:

```bash
   $ ./configure; make
```

The first command, `./configure`, will go through a number of tests and, if it does not find any error, it will create the `Makefile` that is executed with the second command.

To install the library just type:

```bash
   $ make install
```    

By default, the library is installed in `/usr/local/lib` and the header files are installed in `/usr/local/include/libdot-MAJOR.MINOR` (where *MAJOR* and *MINOR* are substituted by the version numbers of this library) To change the include and lib dirs use `--prefix` with `./configure`:

```bash
   $ ./configure --prefix=/home/myuser/local; make
```

It will automatically create a `Makefile` which is specifically instructed to copy all the binaries and headers in `/home/myuser/local`

To uninstall the binaries and headers of the `Libdot` library just execute:

```bash
   $ make uninstall
```    

Be aware that it might be necessary to prepend both `make install` and `make uninstall` with `sudo` in case you are installing in su-protected directories such as `/usr/local`.

Finally, to entirely remove the intermediate files from the installation directory type:

```bash
   $ make distclean
```   


# Tests #

The unit tests have been defined using Google Test. To compile all test cases and run the tests, type:

```bash
   $ make check
```    

from the root directory where the library has been installed. In case all tests are enabled, a failure might be reported for all those unit tests that require accessing files below the directory `tests`. To make sure the tests are performed correctly it is strongly adviced to execute the following commands:

```bash
   $ cd tests
   $ ./gtest --gtest_also_run_disabled_tests
```    

# Documentation #

All the documentation has been generated with Sphinx. To regenerate the documentation type:

```bash
   $ make html
```    

from the `doc/` directory to generate the documentation in HTML format. The main HTML page can be found at `_build/html/index.html`; and type:

```bash
   $ make latexpdf
```    
from the `doc/` directory to generate the same documentation as a PDF. Note that this requires `pdflatex` to be installed in your system.

Finally, to entirely remove the intermediate files from the `doc/` directory type:

```bash
   $ make clean
```   


# License #

`Libdot` is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

`Libdot` is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with `Libdot`.  If not, see <http://www.gnu.org/licenses/>.


# Author #

Carlos Linares Lopez <carlos.linares@uc3m.es>


