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
  
  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // -- undirected graphs
    
    // create an undirected anonymous graph randomly
    string dotgraph {randGraph (10, 0, "", UNDIRECTED_GRAPH, UNDIRECTED_EDGE, 
				vertices, edges, labels)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the graph is acknowledged as an undirected graph
    ASSERT_EQ ("graph", parser.get_type ()) << dotgraph << endl;

    // -- directed graphs
    
    // create an undirected anonymous graph randomly
    dotgraph = randGraph (10, 0, "", DIRECTED_GRAPH, DIRECTED_EDGE,
			  vertices, edges, labels);

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
  
  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // randomly choose a name for this graph
    string graphname = randString (10);

    // -- undirected graphs
    
    // create an undirected graph randomly with the given name
    string dotgraph {randGraph (10, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE, 
				vertices, edges, labels)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the graph is acknowledged as an undirected graph
    ASSERT_EQ ("graph", parser.get_type ()) << dotgraph << endl;

    // -- directed graphs
    
    // create a directed graph randomly with the given name
    dotgraph = randGraph (10, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE, 
			  vertices, edges, labels);

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
  
  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // -- undirected graphs
    
    // create an anonymous undirected graph randomly
    string dotgraph {randGraph (10, 0, "", UNDIRECTED_GRAPH, UNDIRECTED_EDGE, 
				vertices, edges, labels)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the name retrieved equals the empty string
    ASSERT_EQ ("", parser.get_name ()) << dotgraph << endl;

    // -- directed graphs
    
    // create an anonymous directed graph randomly
    dotgraph = randGraph (10, 0, "", DIRECTED_GRAPH, DIRECTED_EDGE,
			  vertices, edges, labels);

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

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // randomly choose a name for this graph
    string graphname = randString (10);

    // -- undirected graphs
    
    // create an undirected graph randomly with the given name
    string dotgraph {randGraph (10, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				vertices, edges, labels)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the name retrieved equals the name chosen
    ASSERT_EQ (graphname, parser.get_name ()) << dotgraph << endl;

    // -- directed graphs
    
    // create a directed graph randomly with the given name
    dotgraph = randGraph (10, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE, 
			  vertices, edges, labels);

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
  
  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // randomly choose a name for this graph
    string graphname = randString (10);

    // -- undirected graphs
    
    // create an undirected graph randomly with the given name
    string dotgraph {randGraph (10, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE, 
				vertices, edges, labels)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the list of source vertices retrieved from the parser is equal to
    // the list of vertices randomly generated
    vector<string> dotvertices = parser.get_vertices ();
    ASSERT_TRUE (equalVectors<string> (vertices, dotvertices)) << dotgraph << endl;

    // -- directed graphs
    
    // create an undirected graph randomly with the given name
    dotgraph = randGraph (10, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE,
			  vertices, edges, labels);

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
  
  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // randomly choose a name for this graph
    string graphname = randString (10);

    // -- undirected graphs
    
    // create an undirected graph randomly with the given name
    string dotgraph {randGraph (10, 0, graphname, UNDIRECTED_GRAPH, UNDIRECTED_EDGE,
				vertices, edges, labels)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the list of vertices retrieved from the parser is equal to the list
    // of vertices randomly generated
    map<string, vector<string>> dotedges = parser.get_graph ();
    ASSERT_TRUE (equalMaps<string> (edges, dotedges)) << dotgraph << endl;

    // -- directed graphs
    
    // create an undirected graph randomly with the given name
    dotgraph = randGraph (10, 0, graphname, DIRECTED_GRAPH, DIRECTED_EDGE, 
			  vertices, edges, labels);

    // parse the graph
    dot::parser diparser;
    diparser.parse_string (dotgraph);

    // check the list of vertices retrieved from the parser is equal to the list
    // of vertices randomly generated
    dotedges = diparser.get_graph ();
    ASSERT_TRUE (equalMaps<string> (edges, dotedges)) << dotgraph << endl;
  }
}

// Checks that labels (integer, floating-point, identifiers and quoted strings)
// are properly parsed in graphs with both directed and undirected edges. In
// passing, it also verifies that the list of vertices and edges are properly
// processed.
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetLabels)
{

  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {

    vector<string> vertices;
    map<string, vector<string>> edges;
    map<string, string> labels;

    // -- undirected graphs
    
    // generate a random graph
    string dotgraph = randGraph (10, 10, randString (10), DIRECTED_GRAPH, MIX_EDGE,
				 vertices, edges, labels);

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
      ASSERT_EQ (parser.get_label_value (label.first), label.second) << dotgraph << endl;
    }

    // In passing, verify also that the list of vertices is properly parsed
    vector<string> dotvertices = parser.get_vertices ();
    ASSERT_TRUE (equalVectors<string> (vertices, dotvertices)) << dotgraph << endl;

    // and also the list of edges
    map<string, vector<string>> dotedges = parser.get_graph ();
    ASSERT_TRUE (equalMaps<string> (edges, dotedges)) << dotgraph << endl;    
  }
}


// // Checks that 
// // ----------------------------------------------------------------------------
// TEST (Parser, )
// {

// }



/* Local Variables: */
/* mode:c++ */
/* fill-column:80 */
/* End: */
