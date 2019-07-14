****************
Unit tests
****************

This section provides a detailed view of all the *Unit tests*
implemented in the directory :file:`tests`. Each test might consider
(or not) different components such as *labels*, *node statements*,
*vertex attributes* and *edge attributes*, or combinations of
them. Unless stated otherwise, each unit test considers only those
components mentioned in its name and discussed in the documentation
string.

To run the tests, type:

.. code-block:: shell

   $ make check

from the root directory where the library has been installed. In case
all tests are enabled, a failure might be reported for all those unit
tests that require accessing files below the directory
:file:`tests`. To make sure the tests are performed correctly it is
strongly adviced to execute the following commands:

.. code-block:: shell

   $ cd tests
   $ ./gtest --gtest_also_run_disabled_tests

==============================
Testing DOT files
==============================

.. index::
   single: ``FileNotFound``
   single: ``invalid_argument``
   single: non-existing dot files
   pair: dot file; non-existing
   single: ``GrevianExample1``
   single: ``GrevianExample2``
   single: ``GrevianExample3``
   single: ``GrevianExample4``
   single: ``GrevianExample5a``
   single: ``GrevianExample5b``
   single: ``GrevianExample7``
   single: simple graph
   single: K6
   single: simple digraph
   single: full digraph
   single: showing a path
   pair: path; showing
   single: large graph
   pair: graph; simple
   pair: graph; large
   pair: digraph; simple
   pair: digraph; full

The unit tests implemented for verifying the existence of dot files
are the following:

* ``FileNotFound``: it verifies that attempting at parsing the
  contents of a non-existing file raises an ``invalid_argument``
  exception.

* ``GrevianExample1``: Checks that the first example (*simple graph*)
  given in the `GraphViz Pocket Reference
  <http://graphs.grevian.org/example>`_ is correctly parsed.

* ``GrevianExample2``: Checks that the second example (*K6*) given in
  the `GraphViz Pocket Reference <http://graphs.grevian.org/example>`_
  is correctly parsed.

* ``GrevianExample3``: Checks that the third example (*simple
  digraph*) given in the `GraphViz Pocket Reference
  <http://graphs.grevian.org/example>`_ is correctly parsed.

* ``GrevianExample4``: Checks that the fourth example (*full digraph*)
  given in the `GraphViz Pocket Reference
  <http://graphs.grevian.org/example>`_ is correctly parsed.

* ``GrevianExample5a``: Checks that the first variant of the fifth
  example (*showing a path*) given in the `GraphViz Pocket Reference
  <http://graphs.grevian.org/example>`_ is correctly parsed.

* ``GrevianExample5b``: Checks that the second variant of the fifth
  example (*showing a path*) given in the `GraphViz Pocket Reference
  <http://graphs.grevian.org/example>`_ is correctly parsed.

* ``GrevianExample7``: Checks that the seventh example (*large graph*)
  given in the `GraphViz Pocket Reference
  <http://graphs.grevian.org/example>`_ is correctly parsed.



==============================
Testing DOT graphs
==============================

The unit tests implemented for testing the contents of DOT graphs are
shown below:

.. index::
   single: directed graph
   single: undirected graph
   pair: graph; directed
   pair: graph; undirected
   single: ``GetTypeAnonymousGraph``
   single: ``GetTypeNamedGraph``
   single: graph type
   pair: dot graph; graph type
   single: ``GetNameAnonymousGraph``
   single: ``GetNameNamedGraph``
   single: graph name
   pair: dot graph; graph name
   single: ``GetVerticesPlainNamedGraph``
   single: vertices
   pair: dot graph; vertices
   single: ``GetEdgesPlainNamedGraph``
   single: edges
   pair: dot graph; edges
   single: ``GetNeighbours``
   single: neighbours
   single: ``GetLabels``
   single: labels
   pair: labels; integer
   pair: labels; floating-point
   pair: labels; id
   pair: labels; quoted strings
   single: ``GetAllVertexAttributes``
   single: vertex attributes
   pair: vertex; attributes
   pair: attributes; vertex
   single: ``GetVertexAttributesByName``
   single: ``GetSingleVertexAttributeByName``
   single: ``GetNodeStatements``
   single: Node statements
   single: ``GetAllEdgeAttributes``
   single: edge attributes
   pair: edge; attributes
   pair: attributes; edge
   single: ``GetEdgeAttributesByName``
   single: ``GetSingleEdgeAttributeByName``
   single: ``GetAllVertexAttributesPath``
   single: path
   single: ``GetVertexAttributesByNamePath``
   single: ``GetSingleVertexAttributeByNamePath``
   single: ``GetAllEdgeAttributesPath``
   single: ``GetEdgeAttributesByNamePath``
   single: ``GetSingleEdgeAttributeByNamePath``
   single: ``GetVerticesBlockMultipleVertices``
   single: multiple vertices
   pair: vertices; multiple
   single: ``GetVerticesBlockMultipleVerticesPath``
   single: ``GetEdgesBlockMultipleVertices``
   single: ``GetVerticesFullGraph``
   single: ``GetEdgesFullGraph``
   
* ``GetTypeAnonymousGraph``: Checks that the type of an anonymous
  graph (either directed or undirected) is correctly retrieved.

* ``GetTypeNamedGraph``: Checks that the type of a named graph (either
  directed or undirected) is correctly retrieved.
   
* ``GetNameAnonymousGraph``: it verifies that the name of an anonymous
  graph (i.e., the empty string) is correctly parsed with either
  directed or undirected graphs.

* ``GetNameNamedGraph``: it verifies that the name of a named graph
  (i.e., a non-null string) is correctly parsed with either directed
  or undirected graphs.

* ``GetVerticesPlainNamedGraph``: Checks that the list of source
  vertices of a plain named graph (either directed or undirected) is
  correctly retrieved. A graph specification is said to be plain if
  and only if it does not contain any vertex/edge attributes.

* ``GetEdgesPlainNamedGraph``: Checks that the edges of a plain named
  graph (either directed or undireted) are correctly retrieved. A
  graph specification is said to be plain if and only if it does not
  contain any vertex/edge attributes.

* ``GetNeighbours``: Checks that the neighbours of every vertex can be
  successfully retrieved both in directed and undirected edges. To
  make the unit test more meaningful, the random graph also contains
  node statements.
  
* ``GetLabels``: Checks that labels (integer, floating-point,
  identifiers and quoted strings) are properly parsed in graphs with
  both directed and undirected edges. In passing, it also verifies
  that the list of vertices and edges are properly processed.

* ``GetAllVertexAttributes``: Checks that vertex attributes are
  properly processed both in directed and undirected graphs by
  querying all of them simultaneously. The test considers a maximum
  number of attributes per vertex in the interval [0, 4].

* ``GetVertexAttributesByName``: Checks that vertex attributes are
  properly processed by name both in directed and undirected
  graphs. The test considers a maximum number of attributes per vertex
  in the interval [0, 4].

* ``GetSingleVertexAttributeByName``: Checks that single vertex
  attributes are properly processed by name both in directed and
  undirected graphs. The test considers a maximum number of attributes
  per vertex in the interval [0, 4].

* ``GetNodeStatements``: Checks that node statements, i.e., statements
  with a single node and optionally a list of node attributes are
  correctly processed in graphs with both directed and undirected
  edges. The test considers a maximum number of attributes per vertex
  in the interval [0, 4].

* ``GetAllEdgeAttributes``: Checks that edge attributes are properly
  processed both in directed and undirected graphs by querying all of
  them simultaneously. The test considers a maximum number of
  attributes per edge in the interval [0, 4].

* ``GetEdgeAttributesByName``: Checks that edge attributes are
  properly processed by edge, identified with the pair source-target,
  both in directed and undirected graphs. The test considers a maximum
  number of attributes per edge in the interval [0, 4].

* ``GetSingleEdgeAttributeByName``: Checks that single edge attributes
  are properly processed by edge, identified with the pair
  source-target, both in directed and undirected graphs. The test
  considers a maximum number of attributes per vertex in the interval
  [0, 4].

* ``GetAllVertexAttributesPath``: Checks that vertex attributes are
  properly processed both in directed and undirected graphs by
  querying all of them simultaneously in the presence of paths. It
  also verifies that the set of vertices has been correctly
  parsed. The test considers 4 attributes per vertex and path length
  in the range [1, 5].

* ``GetVertexAttributesByNamePath``: Checks that vertex attributes are
  properly processed by name both in directed and undirected graphs in
  the presence of paths. It also verifies that the set of vertices has
  been correctly parsed. The test considers 4 attributes per vertex
  and path length in the range [1, 5].

* ``GetSingleVertexAttributeByNamePath``: Checks that single vertex
  attributes are properly processed by name both in directed and
  undirected graphs in the presence of paths. It also verifies that
  the set of vertices has been correctly parsed. The test considers 4
  attributes per vertex and path length in the range [1, 5].

* ``GetAllEdgeAttributesPath``: Checks that edge attributes are
  properly processed both in directed and undirected graphs by
  querying all of them simultaneously in the presence of paths. The
  test considers 4 attributes per edge and path length in the range
  [1, 5].

* ``GetEdgeAttributesByNamePath``: Checks that edge attributes are
  properly processed by edge, identified with the pair source-target,
  both in directed and undirected graphs in the presence of paths. The
  test considers 4 attributes per edge and path length in the range
  [1, 5].

* ``GetSingleEdgeAttributeByNamePath``: Checks that single edge
  attributes are properly processed by edge, identified with the pair
  source-target, both in directed and undirected graphs in the
  presence of paths. The test considers 4 attributes per edge and path
  length in the range [1, 5].

* ``GetVerticesBlockMultipleVertices``: Checks that the list of
  vertices and their attributes are correctly processed both in
  directed and undirected graphs with edges that terminate with a
  block declaring multiple vertices. The test considers 4 attributes
  per vertex and a number of vertices in the block in the range [1,
  5].

* ``GetVerticesBlockMultipleVerticesPath``: Checks that the list of
  vertices and their attributes are correctly processed both in
  directed and undirected graphs with paths that terminate with a
  block declaring multiple vertices. The test considers 4 attributes
  per vertex, blocks with up to 5 vertices and paths with a length
  randomly chosen in the range [1, 5].

* ``GetEdgesBlockMultipleVertices``: Checks that the list of edges and
  their attributes are correctly processed both in directed and
  undirected graphs with edges that terminate with a block declaring
  multiple vertices. The test considers 4 attributes per edge and a
  number of vertices in the block in the range [1, 5].

* ``GetEdgesBlockMultipleVerticesPath``: Checks that the list of edges
  and their attributes are correctly processed both in directed and
  undirected graphs with path that terminate with a block declaring
  multiple vertices. The test considers 4 attributes per edge, blocks
  with up to 5 vertices and paths with a length randomly chosen in the
  range [1, 5].

* ``GetVerticesFullGraph``: Checks that the list of vertices and their
  attributes are correctly processed both in directed and undirected
  full graphs. The test considers 4 attributes per vertex and edge, 10
  node statements and 10 label assignments, blocks with up to 5
  vertices which appear with a probability equal to 0.5 and paths with
  a length randomly chosen in the range [1, 5].

* ``GetEdgesFullGraph``: Checks that the list of edges and their
  attributes are correctly processed both in directed and undirected
  full graphs. The test considers 4 attributes per vertex and edge, 10
  node statements and 10 label assignments, blocks with up to 5
  vertices which appear with a probability equal to 0.5 and paths with
  a length randomly chosen in the range [1, 5].
  
Note that in all cases the random generation of graphs might include
repeated vertices and/or edges. The previous unit test cases therefore
also verify these cases. The same comment applies to the random
generation of labels and vertex/edge attributes.
