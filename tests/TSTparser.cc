/* 
  TSTparser.cc
  Description: DOTparser unit test cases
  Started on  <Tue Jul  2 10:59:51 2019>
  ----------------------------------------------------------------------------- 
  Made by Carlos Linares López
  Login   <carlos.linares@uc3m.es>
*/

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

#include "gtest/gtest.h"
#include "TSTdefs.h"
#include "TSThelperfunctions.h"

#include "../dot.h"

// Checks that default datetimes are initialized with null values
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_FileNotFound)
{

  // create a file which is guaranteed not to exist (with high likelihood)
  string filename = randString (10);

  // create a parser for parsing this file create a dot parser
  dot::parser parser {filename};

  // and now check that an exception is raised
  EXPECT_THROW (parser.parse (), invalid_argument);
}

// Checks that the first example (simple graph) shown in:
//
// https://graphs.grevian.org/example
//
// is correctly parsed
TEST (Parser, DISABLED_GrevianExample1)
{
  
  // create a parser and parse the contnets of this file
  dot::parser parser ("examples/example-1.dot");

  // avoid any messages on the output console by making the verbose level to be
  // false
  parser.set_verbose (false);
  
  // verify that the file is correctly parsed
  ASSERT_TRUE (parser.parse ());
}

// Checks that the second example (K6) shown in:
//
// https://graphs.grevian.org/example
//
// is correctly parsed
TEST (Parser, DISABLED_GrevianExample2)
{
  
  // create a parser and parse the contnets of this file
  dot::parser parser ("examples/example-2.dot");

  // avoid any messages on the output console by making the verbose level to be
  // false
  parser.set_verbose (false);
  
  // verify that the file is correctly parsed
  ASSERT_TRUE (parser.parse ());
}

// Checks that the third example (simple digraph) shown in:
//
// https://graphs.grevian.org/example
//
// is correctly parsed
TEST (Parser, DISABLED_GrevianExample3)
{
  
  // create a parser and parse the contnets of this file
  dot::parser parser ("examples/example-3.dot");

  // avoid any messages on the output console by making the verbose level to be
  // false
  parser.set_verbose (false);
  
  // verify that the file is correctly parsed
  ASSERT_TRUE (parser.parse ());
}

// Checks that the fourth example (full digraph) shown in:
//
// https://graphs.grevian.org/example
//
// is correctly parsed
TEST (Parser, DISABLED_GrevianExample4)
{
  
  // create a parser and parse the contnets of this file
  dot::parser parser ("examples/example-4.dot");

  // avoid any messages on the output console by making the verbose level to be
  // false
  parser.set_verbose (false);
  
  // verify that the file is correctly parsed
  ASSERT_TRUE (parser.parse ());
}

// Checks that the first variant of the fifth example (showing a path) shown in:
//
// https://graphs.grevian.org/example
//
// is correctly parsed
TEST (Parser, DISABLED_GrevianExample5a)
{
  
  // create a parser and parse the contnets of this file
  dot::parser parser ("examples/example-5a.dot");

  // avoid any messages on the output console by making the verbose level to be
  // false
  parser.set_verbose (false);
  
  // verify that the file is correctly parsed
  ASSERT_TRUE (parser.parse ());
}

// Checks that the second variant of the fifth example (showing a path) shown in:
//
// https://graphs.grevian.org/example
//
// is correctly parsed
TEST (Parser, DISABLED_GrevianExample5b)
{
  
  // create a parser and parse the contnets of this file
  dot::parser parser ("examples/example-5b.dot");

  // avoid any messages on the output console by making the verbose level to be
  // false
  parser.set_verbose (false);
  
  // verify that the file is correctly parsed
  ASSERT_TRUE (parser.parse ());
}

// Checks that the seventh example (large graph) shown in:
//
// https://graphs.grevian.org/example
//
// is correctly parsed
TEST (Parser, DISABLED_GrevianExample7)
{
  
  // create a parser and parse the contnets of this file
  dot::parser parser ("examples/example-7.dot");

  // avoid any messages on the output console by making the verbose level to be
  // false
  parser.set_verbose (false);
  
  // verify that the file is correctly parsed
  ASSERT_TRUE (parser.parse ());
}

// Checks that the type of an anonymous graph (either directed or undirected) is
// correctly retrieved
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetTypeAnonymousGraph)
{

  vector<string> vertices;
  map<string, vector<string>> edges;
  map<string, string> labels;
  map<string, map<string, string>> vertexattrs;
  map<string, map<string, map<string, string>>> edgeattrs;
  
  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // -- undirected graphs
    
    // create an undirected anonymous graph randomly
    string dotgraph {randGraph (0, 0, 0, 10, 0, 1, 0, 0, "", UNDIRECTED_GRAPH, UNDIRECTED_EDGE, 
				vertices, edges, labels, vertexattrs, edgeattrs)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the graph is acknowledged as an undirected graph
    ASSERT_EQ ("graph", parser.get_type ()) << dotgraph << endl;

    // -- directed graphs
    
    // create a directed anonymous graph randomly
    dotgraph = randGraph (0, 0, 0, 10, 0, 1, 0, 0, "", DIRECTED_GRAPH, DIRECTED_EDGE,
			  vertices, edges, labels, vertexattrs, edgeattrs);

    // parse the graph
    parser.parse_string (dotgraph);

    // check the graph is acknowledged as a directed graph
    ASSERT_EQ ("digraph", parser.get_type ()) << dotgraph << endl;
  }
}

// Checks that the type of a named graph (either directed or undirected) is
// correctly retrieved
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetTypeNamedGraph)
{

  vector<string> vertices;
  map<string, vector<string>> edges;
  map<string, string> labels;
  map<string, map<string, string>> vertexattrs;
  map<string, map<string, map<string, string>>> edgeattrs;

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // randomly choose a name for this graph
    string graphname = randString (10);

    // -- undirected graphs
    
    // create an undirected graph randomly with the given name
    string dotgraph {randGraph (0, 0, 0, 10, 0, 1, 0, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE, 
				vertices, edges, labels, vertexattrs, edgeattrs)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the graph is acknowledged as an undirected graph
    ASSERT_EQ ("graph", parser.get_type ()) << dotgraph << endl;

    // -- directed graphs
    
    // create a directed graph randomly with the given name
    dotgraph = randGraph (0, 0, 0, 10, 0, 1, 0, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE, 
			  vertices, edges, labels, vertexattrs, edgeattrs);

    // parse the graph
    parser.parse_string (dotgraph);

    // check the graph is acknowledged as a directed graph
    ASSERT_EQ ("digraph", parser.get_type ()) << dotgraph << endl;
  }
}

// Checks that the name of an anonymous graph (either directed or undirected) is
// correctly retrieved
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetNameAnonymousGraph)
{

  vector<string> vertices;
  map<string, vector<string>> edges;
  map<string, string> labels;
  map<string, map<string, string>> vertexattrs;
  map<string, map<string, map<string, string>>> edgeattrs;

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // -- undirected graphs
    
    // create an anonymous undirected graph randomly
    string dotgraph {randGraph (0, 0, 0, 10, 0, 1, 0, 0, "", UNDIRECTED_GRAPH, UNDIRECTED_EDGE, 
				vertices, edges, labels, vertexattrs, edgeattrs)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the name retrieved equals the empty string
    ASSERT_EQ ("", parser.get_name ()) << dotgraph << endl;

    // -- directed graphs
    
    // create an anonymous directed graph randomly
    dotgraph = randGraph (0, 0, 0, 10, 0, 1, 0, 0, "", DIRECTED_GRAPH, DIRECTED_EDGE,
			  vertices, edges, labels, vertexattrs, edgeattrs);

    // parse the graph
    parser.parse_string (dotgraph);

    // check the name retrieved equals the empty string
    ASSERT_EQ ("", parser.get_name ()) << dotgraph << endl;
  }
}

// Checks that the name of a named graph (either directed or undirected) is
// correctly retrieved
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetNameNamedGraph)
{

  vector<string> vertices;
  map<string, vector<string>> edges;
  map<string, string> labels;
  map<string, map<string, string>> vertexattrs;
  map<string, map<string, map<string, string>>> edgeattrs;

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // randomly choose a name for this graph
    string graphname = randString (10);

    // -- undirected graphs
    
    // create an undirected graph randomly with the given name
    string dotgraph {randGraph (0, 0, 0, 10, 0, 1, 0, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				vertices, edges, labels, vertexattrs, edgeattrs)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the name retrieved equals the name chosen
    ASSERT_EQ (graphname, parser.get_name ()) << dotgraph << endl;

    // -- directed graphs
    
    // create a directed graph randomly with the given name
    dotgraph = randGraph (0, 0, 0, 10, 0, 1, 0, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE, 
			  vertices, edges, labels, vertexattrs, edgeattrs);

    // parse the graph
    parser.parse_string (dotgraph);

    // check the name retrieved equals the name chosen
    ASSERT_EQ (graphname, parser.get_name ()) << dotgraph << endl;
  }
}

// Checks that the list of source vertices of a plain named graph (either
// directed or undirected) is correctly retrieved. A graph specification is said
// to be plain if and only if it does not contain any vertex/edge attributes
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetVerticesPlainNamedGraph)
{

  vector<string> vertices;
  map<string, vector<string>> edges;
  map<string, string> labels;
  map<string, map<string, string>> vertexattrs;
  map<string, map<string, map<string, string>>> edgeattrs;

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // randomly choose a name for this graph
    string graphname = randString (10);

    // -- undirected graphs
    
    // create an undirected graph randomly with the given name
    string dotgraph {randGraph (0, 0, 0, 10, 0, 1, 0, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE, 
				vertices, edges, labels, vertexattrs, edgeattrs)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the list of source vertices retrieved from the parser is equal to
    // the list of vertices randomly generated
    vector<string> dotvertices = parser.get_vertices ();

    ASSERT_TRUE (equalVectors<string> (vertices, dotvertices)) << dotgraph << endl;

    // -- directed graphs
    
    // create a directed graph randomly with the given name
    dotgraph = randGraph (0, 0, 0, 10, 0, 1, 0, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
    			  vertices, edges, labels, vertexattrs, edgeattrs);

    // parse the graph
    dot::parser diparser;
    diparser.parse_string (dotgraph);

    // check the list of source vertices retrieved from the parser is equal to
    // the list of vertices randomly generated
    dotvertices = diparser.get_vertices ();
    ASSERT_TRUE (equalVectors<string> (vertices, dotvertices)) << dotgraph << endl;
  }
}

// Checks that the edges of a plain named graph (either directed or undirected)
// are correctly retrieved. A graph specification is said to be plain if and only
// if it does not contain any vertex/edge attributes
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetEdgesPlainNamedGraph)
{

  vector<string> vertices;
  map<string, vector<string>> edges;
  map<string, string> labels;
  map<string, map<string, string>> vertexattrs;
  map<string, map<string, map<string, string>>> edgeattrs;

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // randomly choose a name for this graph
    string graphname = randString (10);

    // -- undirected graphs
    
    // create an undirected graph randomly with the given name
    string dotgraph {randGraph (0, 0, 0, 10, 0, 1, 0, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				vertices, edges, labels, vertexattrs, edgeattrs)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the list of edges retrieved from the parser is equal to the list
    // of edges randomly generated
    map<string, vector<string>> dotedges = parser.get_graph ();
    ASSERT_TRUE (equalMaps<string> (edges, dotedges)) << dotgraph << endl;

    // -- directed graphs
    
    // create a directed graph randomly with the given name
    dotgraph = randGraph (0, 0, 0, 10, 0, 1, 0, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE, 
			  vertices, edges, labels, vertexattrs, edgeattrs);

    // parse the graph
    dot::parser diparser;
    diparser.parse_string (dotgraph);

    // check the list of edges retrieved from the parser is equal to the list
    // of edges randomly generated
    dotedges = diparser.get_graph ();
    ASSERT_TRUE (equalMaps<string> (edges, dotedges)) << dotgraph << endl;
  }
}

// Checks that the neighbours of every vertex can be successfully retrieved both
// in directed and undirected edges. To make the unit test more meaningful, the
// random graph also contains node statements.
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetNeighbours)
{

  map<string, map<string, string>> vertexattrs;
  map<string, map<string, map<string, string>>> edgeattrs;

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    vector<string> vertices;
    map<string, vector<string>> edges;
    map<string, string> labels;

    // -- undirected graphs
    
    // generate a random graph
    string dotgraph = randGraph (10, 0, 0, 10, 0, 1, 0, 0, randString (10), UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				 vertices, edges, labels, vertexattrs, edgeattrs);

    // create a dot parser and parse the dot graph
    dot::parser parser;
    parser.parse_string (dotgraph);

    // now, go over all vertices of this graph
    for (auto& vertex : vertices) {

      // get all neighbours of this vertex
      vector<string> dotneighbours = parser.get_neighbours (vertex);

      // and verify that they are the same
      ASSERT_TRUE (equalVectors<string> (edges[vertex], dotneighbours)) << dotgraph << endl;
    }

    // -- directed graphs
    
    // generate a random graph
    dotgraph = randGraph (10, 0, 0, 10, 0, 1, 0, 0, randString (10), DIRECTED_GRAPH, DIRECTED_EDGE,
			  vertices, edges, labels, vertexattrs, edgeattrs);

    // create a dot parser and parse the dot graph
    dot::parser diparser;
    diparser.parse_string (dotgraph);

    // now, go over all vertices of this graph
    for (auto& vertex : vertices) {

      // get all neighbours of this vertex
      vector<string> dotneighbours = diparser.get_neighbours (vertex);

      // and verify that they are the same
      ASSERT_TRUE (equalVectors<string> (edges[vertex], dotneighbours)) << dotgraph << endl;
    }
  }
}

// Checks that labels (integer, floating-point, identifiers and quoted strings)
// are properly parsed in graphs with both directed and undirected edges. In
// passing, it also verifies that the list of vertices and edges are properly
// processed.
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetLabels)
{

  map<string, map<string, string>> vertexattrs;
  map<string, map<string, map<string, string>>> edgeattrs;

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    vector<string> vertices;
    map<string, vector<string>> edges;
    map<string, string> labels;

    // -- undirected graphs
    
    // generate a random graph
    string dotgraph = randGraph (0, 0, 0, 10, 10, 1, 0, 0, randString (10), DIRECTED_GRAPH, MIX_EDGE,
				 vertices, edges, labels, vertexattrs, edgeattrs);

    // create a dot parser and parse the dot graph
    dot::parser parser;
    parser.parse_string (dotgraph);

    // get all defined labels from the parser
    vector<string> dotlabels = parser.get_labels ();
    
    // now, browse all the labels randomly generated and ensure they have been
    // correctly retrieved by the parser
    for (auto label : labels) {

      // make sure this label has been recognized by the parser
      ASSERT_TRUE (find (dotlabels.begin (), dotlabels.end (), label.first) != dotlabels.end ()) << dotgraph << endl;

      // ensure also that both have the same value for this label
      ASSERT_EQ (parser.get_label_value (label.first), removeDoubleQuotes (label.second)) << dotgraph << endl;
    }

    // In passing, verify also that the list of vertices is properly parsed
    vector<string> dotvertices = parser.get_vertices ();
    ASSERT_TRUE (equalVectors<string> (vertices, dotvertices)) << dotgraph << endl;

    // and also the list of edges
    map<string, vector<string>> dotedges = parser.get_graph ();
    ASSERT_TRUE (equalMaps<string> (edges, dotedges)) << dotgraph << endl;    
  }
}

// Checks that vertex attributes are properly processed both in directed and
// undirected graphs by querying all of them simultaneously. The test considers
// a maximum number of attributes per vertex in the interval [0, 4]
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetAllVertexAttributes)
{
  
  vector<string> vertices;
  map<string, vector<string>> edges;
  map<string, string> labels;
  map<string, map<string, string>> vertexattrs;
  map<string, map<string, map<string, string>>> edgeattrs;

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for a different number of attributes per vertex
    for (auto j = 0 ; j < 5 ; j++) {

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);

      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 0, 0, 10, 0, 1, j, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};

      // parse the graph
      parser.parse_string (dotgraph);

      // check that the map with all attributes for all vertices is properly
      // returned
      map<string, map<string, string>> dotvertexattrs = parser.get_all_vertex_attributes ();

      // first, verify that both maps have precisely the same size
      ASSERT_EQ (vertexattrs.size (), dotvertexattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // vertices in the random graph
      for (auto& vertex : vertices) {

	// if this vertex is specified in either map, then assert that both maps
	// have precisely the same information
	if (vertexattrs.find (vertex) != vertexattrs.end () ||
	    dotvertexattrs.find (vertex) != dotvertexattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (vertexattrs[vertex]), dotvertexattrs[vertex]) << dotgraph << endl;
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 0, 0, 10, 0, 1, j, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);

      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);

      // check that the map with all attributes for all vertices is properly
      // returned
      dotvertexattrs = diparser.get_all_vertex_attributes ();

      // first, verify that both maps have precisely the same size
      ASSERT_EQ (vertexattrs.size (), dotvertexattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // vertices in the random graph
      for (auto& vertex : vertices) {

	// if this vertex is specified in either map, then assert that both maps
	// have precisely the same information
	if (vertexattrs.find (vertex) != vertexattrs.end () ||
	    dotvertexattrs.find (vertex) != dotvertexattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (vertexattrs[vertex]), dotvertexattrs[vertex]) << dotgraph << endl;
      }
    }
  }
}

// Checks that vertex attributes are properly processed by name both in directed
// and undirected graphs. The test considers a maximum number of attributes per
// vertex in the interval [0, 4]
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetVertexAttributesByName)
{
  
  vector<string> vertices;
  map<string, vector<string>> edges;
  map<string, string> labels;
  map<string, map<string, string>> vertexattrs;
  map<string, map<string, map<string, string>>> edgeattrs;

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for a different number of attributes per vertex
    for (auto j = 0 ; j < 5 ; j++) {

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);

      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 0, 0, 10, 0, 1, j, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};

      // parse the graph
      parser.parse_string (dotgraph);

      // check that the map with all attributes for each vertex are properly
      // processed
      for (auto& vertex : vertices) {
	
	map<string, string> dotvertexattrs = parser.get_vertex_attributes (vertex);

	// first, verify that both maps are precisely the same
	ASSERT_EQ (dotvertexattrs, removeDoubleQuotes (vertexattrs[vertex])) << dotgraph << endl;
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 0, 0, 10, 0, 1, j, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);

      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);

      // check that the map with all attributes for each vertex are properly
      // processed
      for (auto& vertex : vertices) {
	
	map<string, string> dotvertexattrs = diparser.get_vertex_attributes (vertex);

	// first, verify that both maps are precisely the same
	ASSERT_EQ (dotvertexattrs, removeDoubleQuotes (vertexattrs[vertex])) << dotgraph << endl;
      }
    }
  }
}

// Checks that single vertex attributes are properly processed by name both in
// directed and undirected graphs. The test considers a maximum number of
// attributes per vertex in the interval [0, 4]
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetSingleVertexAttributeByName)
{
  
  vector<string> vertices;
  map<string, vector<string>> edges;
  map<string, string> labels;
  map<string, map<string, string>> vertexattrs;
  map<string, map<string, map<string, string>>> edgeattrs;

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for a different number of attributes per vertex
    for (auto j = 0 ; j < 5 ; j++) {

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);

      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 0, 0, 10, 0, 1, j, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};

      // parse the graph
      parser.parse_string (dotgraph);

      // check that every single attribute of each vertex has been properly
      // parsed
      for (auto& vertex : vertices) {
	
	// and now, for each vertex name in this map
	for (auto& attr : vertexattrs[vertex]) 

	  // verify that the dot parser returns precisely the same value
	  ASSERT_EQ (parser.get_vertex_attribute (vertex, attr.first),
		     removeDoubleQuotes (attr.second)) << dotgraph << endl;
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 0, 0, 10, 0, 1, j, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);

      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);

      // check that every single attribute of each vertex has been properly
      // parsed
      for (auto& vertex : vertices) {
	
	// and now, for each vertex name in this map
	for (auto& attr : vertexattrs[vertex]) 

	  // verify that the dot parser returns precisely the same value
	  ASSERT_EQ (diparser.get_vertex_attribute (vertex, attr.first),
		     removeDoubleQuotes (attr.second)) << dotgraph << endl;
      }
    }
  }
}

// Checks that node statements, i.e., statements with a single node and
// optionally a list of node attributes are correctly processed in graphs with
// both directed and undirected edges. The test considers a maximum number of
// attributes per vertex in the interval [0, 4]
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetNodeStatements)
{
  
  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for a different number of attributes per vertex
    for (auto j = 0 ; j < 5 ; j++) {

      vector<string> vertices;
      map<string, vector<string>> edges;
      map<string, string> labels;
      map<string, map<string, string>> vertexattrs;
      map<string, map<string, map<string, string>>> edgeattrs;

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);

      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (4, 0, 0, 10, 0, 1, j, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};

      // parse the graph
      parser.parse_string (dotgraph);

      // check first that all vertices (including node statements) have been
      // properly parsed
      vector<string> dotvertices = parser.get_vertices ();
      ASSERT_TRUE (equalVectors<string> (vertices, dotvertices)) << dotgraph << endl;
      
      // check also that the map with all attributes for all vertices is properly
      // returned
      map<string, map<string, string>> dotvertexattrs = parser.get_all_vertex_attributes ();

      // first, verify that both maps have precisely the same size
      ASSERT_EQ (vertexattrs.size (), dotvertexattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // vertices in the random graph
      for (auto& vertex : vertices) {

	// if this vertex is specified in either map, then assert that both maps
	// have precisely the same information
	if (vertexattrs.find (vertex) != vertexattrs.end () ||
	    dotvertexattrs.find (vertex) != dotvertexattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (vertexattrs[vertex]), dotvertexattrs[vertex]) << dotgraph << endl;
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (4, 0, 0, 10, 0, 1, j, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);

      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);

      // check first that all vertices (including node statements) have been
      // properly parsed
      dotvertices = diparser.get_vertices ();
      ASSERT_TRUE (equalVectors<string> (vertices, dotvertices)) << dotgraph << endl;
      
      // check also that the map with all attributes for all vertices is properly
      // returned
      dotvertexattrs = diparser.get_all_vertex_attributes ();

      // first, verify that both maps have precisely the same size
      ASSERT_EQ (vertexattrs.size (), dotvertexattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // vertices in the random graph
      for (auto& vertex : vertices) {

	// if this vertex is specified in either map, then assert that both maps
	// have precisely the same information
	if (vertexattrs.find (vertex) != vertexattrs.end () ||
	    dotvertexattrs.find (vertex) != dotvertexattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (vertexattrs[vertex]), dotvertexattrs[vertex]) << dotgraph << endl;
      }      
    }
  }
}  

// Checks that edge attributes are properly processed both in directed and
// undirected graphs by querying all of them simultaneously. The test considers
// a maximum number of attributes per edge in the interval [0, 4].
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetAllEdgeAttributes)
{

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for a different number of attributes per edge
    for (auto j = 0 ; j < 5 ; j++) {
    
      vector<string> vertices;
      map<string, vector<string>> edges;
      map<string, string> labels;
      map<string, map<string, string>> vertexattrs;
      map<string, map<string, map<string, string>>> edgeattrs;

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);
    
      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 0, 0, 10, 0, 1, 0, j, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};
    
      // parse the graph
      parser.parse_string (dotgraph);
    
      // check first that all edges have been properly processed
      map<string, vector<string>> dotedges = parser.get_graph ();
      ASSERT_TRUE (equalMaps<string> (edges, dotedges)) << dotgraph << endl;
    
      // check also that the map with all attributes for all edges is properly
      // returned
      map<string, map<string, map<string, string>>> dotedgeattrs = parser.get_all_edge_attributes ();
    
      // first, verify that both maps have precisely the same size
      ASSERT_EQ (edgeattrs.size (), dotedgeattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // edges in the random graph
      for (auto& edge : edges) {
      
	// if this edge is specified in either map, then assert that both maps
	// have precisely the same information
	if (edgeattrs.find (edge.first) != edgeattrs.end () ||
	    dotedgeattrs.find (edge.first) != dotedgeattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (edgeattrs[edge.first]), dotedgeattrs[edge.first]) << dotgraph << endl;
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 0, 0, 10, 0, 1, 0, j, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);
    
      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);
    
      // check first that all edges have been properly processed
      dotedges = diparser.get_graph ();
      ASSERT_TRUE (equalMaps<string> (edges, dotedges)) << dotgraph << endl;
    
      // check also that the map with all attributes for all edges is properly
      // returned
      dotedgeattrs = diparser.get_all_edge_attributes ();
    
      // first, verify that both maps have precisely the same size
      ASSERT_EQ (edgeattrs.size (), dotedgeattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // edges in the random graph
      for (auto& edge : edges) {
      
	// if this edge is specified in either map, then assert that both maps
	// have precisely the same information
	if (edgeattrs.find (edge.first) != edgeattrs.end () ||
	    dotedgeattrs.find (edge.first) != dotedgeattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (edgeattrs[edge.first]), dotedgeattrs[edge.first]) << dotgraph << endl;
      }
    }
  }
}

// Checks that edge attributes are properly processed by edge, identified with
// the pair source-target, both in directed and undirected graphs. The test
// considers a maximum number of attributes per edge in the interval [0, 4].
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetEdgeAttributesByName)
{

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for a different number of attributes per edge
    for (auto j = 0 ; j < 5 ; j++) {
    
      vector<string> vertices;
      map<string, vector<string>> edges;
      map<string, string> labels;
      map<string, map<string, string>> vertexattrs;
      map<string, map<string, map<string, string>>> edgeattrs;

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);
    
      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 0, 0, 10, 0, 1, 0, j, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};
    
      // parse the graph
      parser.parse_string (dotgraph);
    
      // now, go over all edges of this graph
      for (auto& edge : edges) {

	for (auto& target : edge.second) {
      
	  // retrieve all the attributes of this edge
	  map<string, string> dotedgeattrs = parser.get_edge_attributes (edge.first, target);
	  
	  // now verify that the attributes of this edge are properly processed
	  ASSERT_EQ (dotedgeattrs, removeDoubleQuotes (edgeattrs[edge.first][target])) << dotgraph << endl;
	}
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 0, 0, 10, 0, 1, 0, j, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);
    
      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);
    
      // now, go over all edges of this graph
      for (auto& edge : edges) {

	for (auto& target : edge.second) {
      
	  // retrieve all the attributes of this edge
	  map<string, string> dotedgeattrs = diparser.get_edge_attributes (edge.first, target);
	  
	  // now verify that the attributes of this edge are properly processed
	  ASSERT_EQ (dotedgeattrs, removeDoubleQuotes (edgeattrs[edge.first][target])) << dotgraph << endl;
	}
      }
    }
  }
}

// Checks that single edge attributes are properly processed by edge, identified
// with the pair source-target, both in directed and undirected graphs. The test
// considers a maximum number of attributes per vertex in the interval [0, 4]
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetSingleEdgeAttributeByName)
{

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for a different number of attributes per edge
    for (auto j = 0 ; j < 5 ; j++) {
    
      vector<string> vertices;
      map<string, vector<string>> edges;
      map<string, string> labels;
      map<string, map<string, string>> vertexattrs;
      map<string, map<string, map<string, string>>> edgeattrs;

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);
    
      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 0, 0, 10, 0, 1, 0, j, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};
    
      // parse the graph
      parser.parse_string (dotgraph);
    
      // now, go over all edges of this graph
      for (auto& edge : edges) {

	for (auto& target : edge.second) {

	  // and now over all attributes of this edge
	  for (auto& attr : edgeattrs[edge.first][target]) {
	  
	    // retrieve all the attributes of this edge
	    string dotedgeattr = parser.get_edge_attribute (edge.first, target, attr.first);
	  
	    // now verify that the value of this attribute of this edge has been
	    // properly processed
	    ASSERT_EQ (dotedgeattr, removeDoubleQuotes (attr.second)) << dotgraph << endl;
	  }
	}
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 0, 0, 10, 0, 1, 0, j, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);
    
      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);
    
      // now, go over all edges of this graph
      for (auto& edge : edges) {

	for (auto& target : edge.second) {

	  // and now over all attributes of this edge
	  for (auto& attr : edgeattrs[edge.first][target]) {
	  
	    // retrieve all the attributes of this edge
	    string dotedgeattr = diparser.get_edge_attribute (edge.first, target, attr.first);
	  
	    // now verify that the value of this attribute of this edge has been
	    // properly processed
	    ASSERT_EQ (dotedgeattr, removeDoubleQuotes (attr.second)) << dotgraph << endl;
	  }
	}
      }
    }
  }
}

// Checks that vertex attributes are properly processed both in directed and
// undirected graphs by querying all of them simultaneously in the presence of
// paths. It also verifies that the set of vertices has been correctly
// parsed. The test considers 4 attributes per vertex and path length in the
// range [1, 5].
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetAllVertexAttributesPath)
{

  vector<string> vertices;
  map<string, vector<string>> edges;
  map<string, string> labels;
  map<string, map<string, string>> vertexattrs;
  map<string, map<string, map<string, string>>> edgeattrs;

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for paths of length randomly chosen in the range [1, j]
    for (auto j = 0 ; j < 5 ; j++ ) {
    
      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);

      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 0, 0, 10, 0, j, 4, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE, 
				  vertices, edges, labels, vertexattrs, edgeattrs)};


      // parse the graph
      parser.parse_string (dotgraph);

      // firstly, verify that the set of paths has been properly parsed
      vector<string> dotvertices = parser.get_vertices ();
      ASSERT_TRUE (equalVectors<string>(vertices, dotvertices)) << dotgraph << endl;
      
      // check that the map with all attributes for all vertices is properly
      // returned
      map<string, map<string, string>> dotvertexattrs = parser.get_all_vertex_attributes ();
    
      // first, verify that both maps have precisely the same size
      ASSERT_EQ (vertexattrs.size (), dotvertexattrs.size ()) << dotgraph << endl;
    
      // now, ensure also that both maps have the same information for all
      // vertices in the random graph
      for (auto& vertex : vertices) {
      
	// if this vertex is specified in either map, then assert that both maps
	// have precisely the same information
	if (vertexattrs.find (vertex) != vertexattrs.end () ||
	    dotvertexattrs.find (vertex) != dotvertexattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (vertexattrs[vertex]), dotvertexattrs[vertex]) << dotgraph << endl;
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 0, 0, 10, 0, j, 4, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE, 
			    vertices, edges, labels, vertexattrs, edgeattrs);

      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);

      // firstly, verify that the set of paths has been properly parsed
      dotvertices = diparser.get_vertices ();
      ASSERT_TRUE (equalVectors<string>(vertices, dotvertices)) << dotgraph << endl;
      
      // check that the map with all attributes for all vertices is properly
      // returned
      dotvertexattrs = diparser.get_all_vertex_attributes ();
    
      // first, verify that both maps have precisely the same size
      ASSERT_EQ (vertexattrs.size (), dotvertexattrs.size ()) << dotgraph << endl;
    
      // now, ensure also that both maps have the same information for all
      // vertices in the random graph
      for (auto& vertex : vertices) {
      
	// if this vertex is specified in either map, then assert that both maps
	// have precisely the same information
	if (vertexattrs.find (vertex) != vertexattrs.end () ||
	    dotvertexattrs.find (vertex) != dotvertexattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (vertexattrs[vertex]), dotvertexattrs[vertex]) << dotgraph << endl;
      }
    }
  }
}

// Checks that vertex attributes are properly processed by name both in directed
// and undirected graphs in the presence of paths. It also verifies that the set
// of vertices has been correctly parsed. The test considers 4 attributes per
// vertex and path length in the range [1, 5].
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetVertexAttributesByNamePath)
{

  vector<string> vertices;
  map<string, vector<string>> edges;
  map<string, string> labels;
  map<string, map<string, string>> vertexattrs;
  map<string, map<string, map<string, string>>> edgeattrs;

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for paths of length randomly chosen in the range [1, j]
    for (auto j = 0 ; j < 5 ; j++ ) {
    
      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);

      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 0, 0, 10, 0, j, 4, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE, 
				  vertices, edges, labels, vertexattrs, edgeattrs)};


      // parse the graph
      parser.parse_string (dotgraph);

      // firstly, verify that the set of paths has been properly parsed
      vector<string> dotvertices = parser.get_vertices ();
      ASSERT_TRUE (equalVectors<string>(vertices, dotvertices)) << dotgraph << endl;
      
      // check that the map with all attributes for each vertex are properly
      // processed
      for (auto& vertex : vertices) {
	
	map<string, string> dotvertexattrs = parser.get_vertex_attributes (vertex);

	// first, verify that both maps are precisely the same
	ASSERT_EQ (dotvertexattrs, removeDoubleQuotes (vertexattrs[vertex])) << dotgraph << endl;
      }


      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 0, 0, 10, 0, j, 4, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE, 
			    vertices, edges, labels, vertexattrs, edgeattrs);

      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);

      // firstly, verify that the set of paths has been properly parsed
      dotvertices = diparser.get_vertices ();
      ASSERT_TRUE (equalVectors<string>(vertices, dotvertices)) << dotgraph << endl;
      
      // check that the map with all attributes for each vertex are properly
      // processed
      for (auto& vertex : vertices) {
	
	map<string, string> dotvertexattrs = diparser.get_vertex_attributes (vertex);

	// first, verify that both maps are precisely the same
	ASSERT_EQ (dotvertexattrs, removeDoubleQuotes (vertexattrs[vertex])) << dotgraph << endl;
      }
    }
  }
}

// Checks that single vertex attributes are properly processed by name both in
// directed and undirected graphs in the presence of paths. It also verifies
// that the set of vertices has been correctly parsed. The test considers 4
// attributes per vertex and path length in the range [1, 5].
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetSingleVertexAttributeByNamePath)
{

  vector<string> vertices;
  map<string, vector<string>> edges;
  map<string, string> labels;
  map<string, map<string, string>> vertexattrs;
  map<string, map<string, map<string, string>>> edgeattrs;

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for paths of length randomly chosen in the range [1, j]
    for (auto j = 0 ; j < 5 ; j++ ) {
    
      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);

      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 0, 0, 10, 0, j, 4, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE, 
				  vertices, edges, labels, vertexattrs, edgeattrs)};


      // parse the graph
      parser.parse_string (dotgraph);

      // firstly, verify that the set of paths has been properly parsed
      vector<string> dotvertices = parser.get_vertices ();
      ASSERT_TRUE (equalVectors<string>(vertices, dotvertices)) << dotgraph << endl;
      
      // check that every single attribute of each vertex has been properly
      // parsed
      for (auto& vertex : vertices) {
	
	// and now, for each vertex name in this map
	for (auto& attr : vertexattrs[vertex]) 

	  // verify that the dot parser returns precisely the same value
	  ASSERT_EQ (parser.get_vertex_attribute (vertex, attr.first),
		     removeDoubleQuotes (attr.second)) << dotgraph << endl;
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 0, 0, 10, 0, j, 4, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE, 
			    vertices, edges, labels, vertexattrs, edgeattrs);

      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);

      // firstly, verify that the set of paths has been properly parsed
      dotvertices = diparser.get_vertices ();
      ASSERT_TRUE (equalVectors<string>(vertices, dotvertices)) << dotgraph << endl;
      
      // check that every single attribute of each vertex has been properly
      // parsed
      for (auto& vertex : vertices) {
	
	// and now, for each vertex name in this map
	for (auto& attr : vertexattrs[vertex]) 

	  // verify that the dot parser returns precisely the same value
	  ASSERT_EQ (diparser.get_vertex_attribute (vertex, attr.first),
		     removeDoubleQuotes (attr.second)) << dotgraph << endl;
      }
    }
  }
}

// Checks that edge attributes are properly processed both in directed and
// undirected graphs by querying all of them simultaneously in the presence of
// paths. The test considers 4 attributes per edge and path length in the
// range [1, 5].
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetAllEdgeAttributesPath)
{

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for paths of length randomly chosen in the range [1, j]
    for (auto j = 1 ; j < 5 ; j++) {
    
      vector<string> vertices;
      map<string, vector<string>> edges;
      map<string, string> labels;
      map<string, map<string, string>> vertexattrs;
      map<string, map<string, map<string, string>>> edgeattrs;

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);
    
      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 0, 0, 10, 0, j, 0, 4, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};
    
      // parse the graph
      parser.parse_string (dotgraph);
    
      // check first that all edges have been properly processed
      map<string, vector<string>> dotedges = parser.get_graph ();

      ASSERT_TRUE (equalMaps<string> (edges, dotedges)) << dotgraph << endl;
    
      // check also that the map with all attributes for all edges is properly
      // returned
      map<string, map<string, map<string, string>>> dotedgeattrs = parser.get_all_edge_attributes ();
    
      // first, verify that both maps have precisely the same size
      ASSERT_EQ (edgeattrs.size (), dotedgeattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // edges in the random graph
      for (auto& edge : edges) {
      
	// if this edge is specified in either map, then assert that both maps
	// have precisely the same information
	if (edgeattrs.find (edge.first) != edgeattrs.end () ||
	    dotedgeattrs.find (edge.first) != dotedgeattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (edgeattrs[edge.first]), dotedgeattrs[edge.first]) << dotgraph << endl;
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 0, 0, 10, 0, j, 0, 4, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);
    
      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);
    
      // check first that all edges have been properly processed
      dotedges = diparser.get_graph ();
      ASSERT_TRUE (equalMaps<string> (edges, dotedges)) << dotgraph << endl;
    
      // check also that the map with all attributes for all edges is properly
      // returned
      dotedgeattrs = diparser.get_all_edge_attributes ();
    
      // first, verify that both maps have precisely the same size
      ASSERT_EQ (edgeattrs.size (), dotedgeattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // edges in the random graph
      for (auto& edge : edges) {
      
	// if this edge is specified in either map, then assert that both maps
	// have precisely the same information
	if (edgeattrs.find (edge.first) != edgeattrs.end () ||
	    dotedgeattrs.find (edge.first) != dotedgeattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (edgeattrs[edge.first]), dotedgeattrs[edge.first]) << dotgraph << endl;
      }
    }
  }
}

// Checks that edge attributes are properly processed by edge, identified with
// the pair source-target, both in directed and undirected graphs in the
// presence of paths. The test considers 4 attributes per edge and path length
// in the range [1, 5].
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetEdgeAttributesByNamePath)
{

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for paths of length randomly chosen in the range [1, j]
    for (auto j = 0 ; j < 5 ; j++) {
    
      vector<string> vertices;
      map<string, vector<string>> edges;
      map<string, string> labels;
      map<string, map<string, string>> vertexattrs;
      map<string, map<string, map<string, string>>> edgeattrs;

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);
    
      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 0, 0, 10, 0, j, 0, 4, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};
    
      // parse the graph
      parser.parse_string (dotgraph);
    
      // now, go over all edges of this graph
      for (auto& edge : edges) {

	for (auto& target : edge.second) {
      
	  // retrieve all the attributes of this edge
	  map<string, string> dotedgeattrs = parser.get_edge_attributes (edge.first, target);
	  
	  // now verify that the attributes of this edge are properly processed
	  ASSERT_EQ (dotedgeattrs, removeDoubleQuotes (edgeattrs[edge.first][target])) << dotgraph << endl;
	}
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 0, 0, 10, 0, j, 0, 4, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);
    
      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);
    
      // now, go over all edges of this graph
      for (auto& edge : edges) {

	for (auto& target : edge.second) {
      
	  // retrieve all the attributes of this edge
	  map<string, string> dotedgeattrs = diparser.get_edge_attributes (edge.first, target);
	  
	  // now verify that the attributes of this edge are properly processed
	  ASSERT_EQ (dotedgeattrs, removeDoubleQuotes (edgeattrs[edge.first][target])) << dotgraph << endl;
	}
      }
    }
  }
}

// Checks that single edge attributes are properly processed by edge, identified
// with the pair source-target, both in directed and undirected graphs in the
// presence of paths. The test considers 4 attributes per edge and path length
// in the range [1, 5].
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetSingleEdgeAttributeByNamePath)
{

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for paths of length randomly chosen in the range [1, j]
    for (auto j = 0 ; j < 5 ; j++) {
    
      vector<string> vertices;
      map<string, vector<string>> edges;
      map<string, string> labels;
      map<string, map<string, string>> vertexattrs;
      map<string, map<string, map<string, string>>> edgeattrs;

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);
    
      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 0, 0, 10, 0, j, 0, 4, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};
    
      // parse the graph
      parser.parse_string (dotgraph);
    
      // now, go over all edges of this graph
      for (auto& edge : edges) {

	for (auto& target : edge.second) {

	  // and now over all attributes of this edge
	  for (auto& attr : edgeattrs[edge.first][target]) {
	  
	    // retrieve all the attributes of this edge
	    string dotedgeattr = parser.get_edge_attribute (edge.first, target, attr.first);
	  
	    // now verify that the value of this attribute of this edge has been
	    // properly processed
	    ASSERT_EQ (dotedgeattr, removeDoubleQuotes (attr.second)) << dotgraph << endl;
	  }
	}
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 0, 0, 10, 0, j, 0, 4, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);
    
      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);
    
      // now, go over all edges of this graph
      for (auto& edge : edges) {

	for (auto& target : edge.second) {

	  // and now over all attributes of this edge
	  for (auto& attr : edgeattrs[edge.first][target]) {
	  
	    // retrieve all the attributes of this edge
	    string dotedgeattr = diparser.get_edge_attribute (edge.first, target, attr.first);
	  
	    // now verify that the value of this attribute of this edge has been
	    // properly processed
	    ASSERT_EQ (dotedgeattr, removeDoubleQuotes (attr.second)) << dotgraph << endl;
	  }
	}
      }
    }
  }
}

// Checks that the list of vertices and their attributes are correctly processed
// both in directed and undirected graphs with edges that terminate with a block
// declaring multiple vertices. The test considers 4 attributes per vertex and a
// number of vertices in the block in the range [1, 5].
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetVerticesBlockMultipleVertices)
{

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for a number of vertices in each block up to j
    for (auto j = 1 ; j <= 5 ; j++ ) {
    
      vector<string> vertices;
      map<string, vector<string>> edges;
      map<string, string> labels;
      map<string, map<string, string>> vertexattrs;
      map<string, map<string, map<string, string>>> edgeattrs;

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);
    
      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 100, j, 10, 0, 1, 4, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};

      // parse the graph
      parser.parse_string (dotgraph);

      // verify that all vertices have been properly parsed
      vector<string> dotvertices = parser.get_vertices ();
      ASSERT_TRUE (equalVectors<string>(vertices, dotvertices)) << dotgraph << endl;

      // check also that the map with all attributes for all vertices is
      // properly returned
      map<string, map<string, string>> dotvertexattrs = parser.get_all_vertex_attributes ();

      // first, verify that both maps have precisely the same size
      ASSERT_EQ (vertexattrs.size (), dotvertexattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // vertices in the random graph
      for (auto& vertex : vertices) {

	// if this vertex is specified in either map, then assert that both maps
	// have precisely the same information
	if (vertexattrs.find (vertex) != vertexattrs.end () ||
	    dotvertexattrs.find (vertex) != dotvertexattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (vertexattrs[vertex]), dotvertexattrs[vertex]) << dotgraph << endl;
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 100, j, 10, 0, 1, 4, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);

      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);

      // verify that all vertices have been properly parsed
      dotvertices = diparser.get_vertices ();
      ASSERT_TRUE (equalVectors<string>(vertices, dotvertices)) << dotgraph << endl;

      // check also that the map with all attributes for all vertices is
      // properly returned
      dotvertexattrs = diparser.get_all_vertex_attributes ();

      // first, verify that both maps have precisely the same size
      ASSERT_EQ (vertexattrs.size (), dotvertexattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // vertices in the random graph
      for (auto& vertex : vertices) {

	// if this vertex is specified in either map, then assert that both maps
	// have precisely the same information
	if (vertexattrs.find (vertex) != vertexattrs.end () ||
	    dotvertexattrs.find (vertex) != dotvertexattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (vertexattrs[vertex]), dotvertexattrs[vertex]) << dotgraph << endl;
      }
    }
  }
}

// Checks that the list of vertices and their attributes are correctly processed
// both in directed and undirected graphs with paths that terminate with a block
// declaring multiple vertices. The test considers 4 attributes per vertex,
// blocks with up to 5 vertices and paths with a length randomly chosen in the
// range [1, 5].
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetVerticesBlockMultipleVerticesPath)
{

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for paths of length randomly chosen in the range [1, j]
    for (auto j = 1 ; j <= 5 ; j++ ) {
    
      vector<string> vertices;
      map<string, vector<string>> edges;
      map<string, string> labels;
      map<string, map<string, string>> vertexattrs;
      map<string, map<string, map<string, string>>> edgeattrs;

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);
    
      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 100, 5, 10, 0, j, 4, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};

      // parse the graph
      parser.parse_string (dotgraph);

      // verify that all vertices have been properly parsed
      vector<string> dotvertices = parser.get_vertices ();
      ASSERT_TRUE (equalVectors<string>(vertices, dotvertices)) << dotgraph << endl;

      // check also that the map with all attributes for all vertices is
      // properly returned
      map<string, map<string, string>> dotvertexattrs = parser.get_all_vertex_attributes ();

      // first, verify that both maps have precisely the same size
      ASSERT_EQ (vertexattrs.size (), dotvertexattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // vertices in the random graph
      for (auto& vertex : vertices) {

	// if this vertex is specified in either map, then assert that both maps
	// have precisely the same information
	if (vertexattrs.find (vertex) != vertexattrs.end () ||
	    dotvertexattrs.find (vertex) != dotvertexattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (vertexattrs[vertex]), dotvertexattrs[vertex]) << dotgraph << endl;
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 100, 5, 10, 0, j, 4, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);

      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);

      // verify that all vertices have been properly parsed
      dotvertices = diparser.get_vertices ();
      ASSERT_TRUE (equalVectors<string>(vertices, dotvertices)) << dotgraph << endl;

      // check also that the map with all attributes for all vertices is
      // properly returned
      dotvertexattrs = diparser.get_all_vertex_attributes ();

      // first, verify that both maps have precisely the same size
      ASSERT_EQ (vertexattrs.size (), dotvertexattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // vertices in the random graph
      for (auto& vertex : vertices) {

	// if this vertex is specified in either map, then assert that both maps
	// have precisely the same information
	if (vertexattrs.find (vertex) != vertexattrs.end () ||
	    dotvertexattrs.find (vertex) != dotvertexattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (vertexattrs[vertex]), dotvertexattrs[vertex]) << dotgraph << endl;
      }
    }
  }
}

// Checks that the list of edges and their attributes are correctly processed
// both in directed and undirected graphs with edges that terminate with a block
// declaring multiple vertices. The test considers 4 attributes per edge and a
// number of vertices in the block in the range [1, 5].
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetEdgesBlockMultipleVertices)
{

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for a number of vertices in each block up to j
    for (auto j = 1 ; j <= 5 ; j++ ) {
    
      vector<string> vertices;
      map<string, vector<string>> edges;
      map<string, string> labels;
      map<string, map<string, string>> vertexattrs;
      map<string, map<string, map<string, string>>> edgeattrs;

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);
    
      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 100, j, 10, 0, 1, 0, 4, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};

      // parse the graph
      parser.parse_string (dotgraph);

      // verify that all edges have been properly parsed
      map<string, vector<string>> dotedges = parser.get_graph ();
      ASSERT_TRUE (equalMaps<string>(edges, dotedges)) << dotgraph << endl;

      // check also that the map with all attributes for all edges is properly
      // returned
      map<string, map<string, map<string, string>>> dotedgeattrs = parser.get_all_edge_attributes ();
    
      // first, verify that both maps have precisely the same size
      ASSERT_EQ (edgeattrs.size (), dotedgeattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // edges in the random graph
      for (auto& edge : edges) {
      
	// if this edge is specified in either map, then assert that both maps
	// have precisely the same information
	if (edgeattrs.find (edge.first) != edgeattrs.end () ||
	    dotedgeattrs.find (edge.first) != dotedgeattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (edgeattrs[edge.first]), dotedgeattrs[edge.first]) << dotgraph << endl;
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 100, j, 10, 0, 1, 0, 4, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);

      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);

      // verify that all edges have been properly parsed
      dotedges = diparser.get_graph ();
      ASSERT_TRUE (equalMaps<string>(edges, dotedges)) << dotgraph << endl;

      // check also that the map with all attributes for all edges is properly
      // returned
      dotedgeattrs = diparser.get_all_edge_attributes ();
    
      // first, verify that both maps have precisely the same size
      ASSERT_EQ (edgeattrs.size (), dotedgeattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // edges in the random graph
      for (auto& edge : edges) {
      
	// if this edge is specified in either map, then assert that both maps
	// have precisely the same information
	if (edgeattrs.find (edge.first) != edgeattrs.end () ||
	    dotedgeattrs.find (edge.first) != dotedgeattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (edgeattrs[edge.first]), dotedgeattrs[edge.first]) << dotgraph << endl;
      }
    }
  }
}

// Checks that the list of edges and their attributes are correctly processed
// both in directed and undirected graphs with path that terminate with a block
// declaring multiple vertices. The test considers 4 attributes per edge, blocks
// with up to 5 vertices and paths with a length randomly chosen in the range
// [1, 5].
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetEdgesBlockMultipleVerticesPath)
{

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for paths of length randomly chosen in the range [1, j]
    for (auto j = 1 ; j <= 5 ; j++ ) {
    
      vector<string> vertices;
      map<string, vector<string>> edges;
      map<string, string> labels;
      map<string, map<string, string>> vertexattrs;
      map<string, map<string, map<string, string>>> edgeattrs;

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);
    
      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (0, 100, 5, 10, 0, j, 0, 4, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};

      // parse the graph
      parser.parse_string (dotgraph);

      // verify that all edges have been properly parsed
      map<string, vector<string>> dotedges = parser.get_graph ();
      ASSERT_TRUE (equalMaps<string>(edges, dotedges)) << dotgraph << endl;

      // check also that the map with all attributes for all edges is properly
      // returned
      map<string, map<string, map<string, string>>> dotedgeattrs = parser.get_all_edge_attributes ();
    
      // first, verify that both maps have precisely the same size
      ASSERT_EQ (edgeattrs.size (), dotedgeattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // edges in the random graph
      for (auto& edge : edges) {
      
	// if this edge is specified in either map, then assert that both maps
	// have precisely the same information
	if (edgeattrs.find (edge.first) != edgeattrs.end () ||
	    dotedgeattrs.find (edge.first) != dotedgeattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (edgeattrs[edge.first]), dotedgeattrs[edge.first]) << dotgraph << endl;
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (0, 100, 5, 10, 0, j, 0, 4, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);

      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);

      // verify that all edges have been properly parsed
      dotedges = diparser.get_graph ();
      ASSERT_TRUE (equalMaps<string>(edges, dotedges)) << dotgraph << endl;

      // check also that the map with all attributes for all edges is properly
      // returned
      dotedgeattrs = diparser.get_all_edge_attributes ();
    
      // first, verify that both maps have precisely the same size
      ASSERT_EQ (edgeattrs.size (), dotedgeattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // edges in the random graph
      for (auto& edge : edges) {
      
	// if this edge is specified in either map, then assert that both maps
	// have precisely the same information
	if (edgeattrs.find (edge.first) != edgeattrs.end () ||
	    dotedgeattrs.find (edge.first) != dotedgeattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (edgeattrs[edge.first]), dotedgeattrs[edge.first]) << dotgraph << endl;
      }
    }
  }
}

// Checks that the list of vertices and their attributes are correctly processed
// both in directed and undirected full graphs. The test considers 4 attributes
// per vertex and edge, 10 node statements and 10 label assignments, blocks with
// up to 5 vertices which appear with a probability equal to 0.5 and paths with
// a length randomly chosen in the range [1, 5].
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetVerticesFullGraph)
{

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for paths of length randomly chosen in the range [1, j]
    for (auto j = 1 ; j <= 5 ; j++ ) {
    
      vector<string> vertices;
      map<string, vector<string>> edges;
      map<string, string> labels;
      map<string, map<string, string>> vertexattrs;
      map<string, map<string, map<string, string>>> edgeattrs;

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);
    
      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (10, 50, 5, 10, 10, j, 4, 4, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};

      // parse the graph
      parser.parse_string (dotgraph);

      // verify that all vertices have been properly parsed
      vector<string> dotvertices = parser.get_vertices ();
      ASSERT_TRUE (equalVectors<string>(vertices, dotvertices)) << dotgraph << endl;

      // check also that the map with all attributes for all vertices is
      // properly returned
      map<string, map<string, string>> dotvertexattrs = parser.get_all_vertex_attributes ();

      // first, verify that both maps have precisely the same size
      ASSERT_EQ (vertexattrs.size (), dotvertexattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // vertices in the random graph
      for (auto& vertex : vertices) {

	// if this vertex is specified in either map, then assert that both maps
	// have precisely the same information
	if (vertexattrs.find (vertex) != vertexattrs.end () ||
	    dotvertexattrs.find (vertex) != dotvertexattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (vertexattrs[vertex]), dotvertexattrs[vertex]) << dotgraph << endl;
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (10, 50, 5, 10, 10, j, 4, 4, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);

      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);

      // verify that all vertices have been properly parsed
      dotvertices = diparser.get_vertices ();
      ASSERT_TRUE (equalVectors<string>(vertices, dotvertices)) << dotgraph << endl;

      // check also that the map with all attributes for all vertices is
      // properly returned
      dotvertexattrs = diparser.get_all_vertex_attributes ();

      // first, verify that both maps have precisely the same size
      ASSERT_EQ (vertexattrs.size (), dotvertexattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // vertices in the random graph
      for (auto& vertex : vertices) {

	// if this vertex is specified in either map, then assert that both maps
	// have precisely the same information
	if (vertexattrs.find (vertex) != vertexattrs.end () ||
	    dotvertexattrs.find (vertex) != dotvertexattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (vertexattrs[vertex]), dotvertexattrs[vertex]) << dotgraph << endl;
      }
    }
  }
}

// Checks that the list of edges and their attributes are correctly processed
// both in directed and undirected full graphs. The test considers 4 attributes
// per vertex and edge, 10 node statements and 10 label assignments, blocks with
// up to 5 vertices which appear with a probability equal to 0.5 and paths with
// a length randomly chosen in the range [1, 5].
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetEdgesFullGraph)
{

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    // for paths of length randomly chosen in the range [1, j]
    for (auto j = 1 ; j <= 5 ; j++ ) {
    
      vector<string> vertices;
      map<string, vector<string>> edges;
      map<string, string> labels;
      map<string, map<string, string>> vertexattrs;
      map<string, map<string, map<string, string>>> edgeattrs;

      // create a dot parser
      dot::parser parser;
    
      // randomly choose a name for this graph
      string graphname = randString (10);
    
      // -- undirected graphs
    
      // create an undirected graph randomly with the given name
      string dotgraph {randGraph (10, 50, 5, 10, 10, j, 4, 4, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				  vertices, edges, labels, vertexattrs, edgeattrs)};

      // parse the graph
      parser.parse_string (dotgraph);

      // verify that all edges have been properly parsed
      map<string, vector<string>> dotedges = parser.get_graph ();
      ASSERT_TRUE (equalMaps<string>(edges, dotedges)) << dotgraph << endl;

      // check also that the map with all attributes for all edges is properly
      // returned
      map<string, map<string, map<string, string>>> dotedgeattrs = parser.get_all_edge_attributes ();
    
      // first, verify that both maps have precisely the same size
      ASSERT_EQ (edgeattrs.size (), dotedgeattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // edges in the random graph
      for (auto& edge : edges) {
      
	// if this edge is specified in either map, then assert that both maps
	// have precisely the same information
	if (edgeattrs.find (edge.first) != edgeattrs.end () ||
	    dotedgeattrs.find (edge.first) != dotedgeattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (edgeattrs[edge.first]), dotedgeattrs[edge.first]) << dotgraph << endl;
      }

      // -- directed graphs
    
      // create a directed graph randomly with the given name
      dotgraph = randGraph (10, 50, 5, 10, 10, j, 4, 4, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			    vertices, edges, labels, vertexattrs, edgeattrs);

      // parse the graph
      dot::parser diparser;
      diparser.parse_string (dotgraph);

      // verify that all edges have been properly parsed
      dotedges = diparser.get_graph ();

      ASSERT_TRUE (equalMaps<string>(edges, dotedges)) << dotgraph << endl;

      // check also that the map with all attributes for all edges is properly
      // returned
      dotedgeattrs = diparser.get_all_edge_attributes ();
    
      // first, verify that both maps have precisely the same size
      ASSERT_EQ (edgeattrs.size (), dotedgeattrs.size ()) << dotgraph << endl;

      // now, ensure also that both maps have the same information for all
      // edges in the random graph
      for (auto& edge : edges) {
      
	// if this edge is specified in either map, then assert that both maps
	// have precisely the same information
	if (edgeattrs.find (edge.first) != edgeattrs.end () ||
	    dotedgeattrs.find (edge.first) != dotedgeattrs.end ())
	  ASSERT_EQ (removeDoubleQuotes (edgeattrs[edge.first]), dotedgeattrs[edge.first]) << dotgraph << endl;
      }
    }
  }
}


/* Local Variables: */
/* mode:c++ */
/* fill-column:80 */
/* End: */
