******************
The DOT language
******************
.. index::
   single: DOT language

This section briefly summarizes the subset of the DOT language that is
parsed by this library. For a complete reference see the `DOT
language <https://www.graphviz.org/doc/info/lang.html>`_

==============================
BNF specification
==============================

The specification of the language parsed by this library is shown
below:

.. code-block:: bnf

    graph 	: 	(graph | digraph) [ ID ] '{' stmt_list '}'
    stmt_list 	: 	[ stmt [ ';' ] stmt_list ]
    stmt 	: 	node_stmt
    	              | edge_stmt
    	              | label_stmt
    node_stmt 	: 	node_id [ attr_list ]
    node_id 	: 	ID
    edge_stmt   :       node_stmt edge_list
    edge_list   :       edge_op [ attr_list ] node_stmt [ edge_list ]
                      | edge_op [ attr_list ] '{' node_list '}'
    edge_op     :       ('--' | '->')
    node_list   :       node_stmt [ node_list ]
    label_stmt  :       ID '=' VALUE
    attr_list 	: 	'[' [ a_list ] ']'
    a_list 	: 	ID '=' VALUE [ ',' a_list ]

.. index::
   single: BNF specification
   single: graph
   single: digraph
   single: ID
   single: VALUE
   single: node
   single: edge
   single: label
    
There are a number of good diferences with the official DOT language
which are:

* The keyword ``strict`` is not recognized. Moreover, the parser does
  not check whether the graph is truly directed or undirected, e.g.,
  it is possible to declare a ``digraph`` and then to use the
  ``edge_op`` ``--``

* *Label statements* consist of a single assignment to an ID, i.e.,
  they can not be continued with other expressions as in the official
  DOT language.

.. index::
   single: label statement
   pair: statement; label
  
* There are not *subgraphs*. The DOT language implemented in this
  library only allows to define edges between vertices as in the usual
  mathematical formulation of a graph.

.. index::
   single: subgraph
    
* There are not *ports* and, indeed, the subset implemented here is
  not selected for any specific purpose, but for the intention of
  defining graphs in a general sense.

.. index::
   single: port
  
On the other hand, the language parsed by this library allows edges to
be qualified with attributes as much as vertices with an
``attr_list``, so that whereas the official DOT language complains
with statements such as ``a -> [ color = red ] b;``, this library
actually parses them correctly.
  
As it can be seen in the BNF specification, the language parsed by
this library allows the definition of paths, as in ``a -> b -> c;`` or
blocks with multiple vertices, such as in ``a -> { b c d };``. As in
the official DOT language, a block with multiple vertices ends an edge
statement, so that expressions such as ``{ a b c } -- { d e f };``
actually raise a syntax error. Of course, both forms can be mixed in a
single statement such as in ``a -> b -- c -- { d e f };``.

.. index::
   single: path
   single: multiple vertices
   pair: vertices; multiple

Another relevant difference is the definition of IDs. For the purpose
of this library, IDs are defined as a collection of alphanumeric
characters and the underscore ``_``, so that ``81_`` is a
valid ID. IDs are used for naming graphs (which is entirely optional)
or for declaring attributes. Attributes give a VALUE to an ID which
are defined as:

.. index::
   single: ID
   single: VALUE   

* Either an integer number with or without sign, e.g., ``12``, ``+12``
  or ``-12``; or

.. index::
   single: integer number
   pair: number; integer

* A floating-point number which can be in scientific notation or
  not. Examples are: ``12.13``, ``.019e-12`` and ``1003.``; or

.. index::
   single: floating-point number
   pair: number; floating-point
  
* A string which can be either an alphanumeric sequence which does not
  start with a number, such as ``red``, or a double quoted string
  which can then contain any characters, such as ``"I'm a double
  quoted string"``.
