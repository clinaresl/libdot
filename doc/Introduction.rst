****************
Introduction
****************

The DOT language is used for defining either directed or undirected
graphs which can be qualified with *atributes* and *labels*. It
serves, for example, to define those graphs that can be drawn using
:program:`graphviz`. Indeed, the official DOT language seems to be
highly tuned for graphical applications, whereas the subset
implemented in this library has been implemented for the generic
purpose of defining graphs in a general sense. 

This library implements a light parser (based on *regexps*) of a
subset of the DOT language. Even if the intention of the parser is to
actually parse only legal statements in the DOT language, a few
(natural) extensions have been added for the sake of completeness.

This manual documents the library and its usage. At the end, a list of
all the unit tests is given also for reference.


