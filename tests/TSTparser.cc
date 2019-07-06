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

// Checks that the type of an anonymous graph (either directed or undirected) is
// correctly retrieved
// ----------------------------------------------------------------------------
TEST (Parser, DISABLED_GetTypeAnonymousGraph)
{

  vector<string> vertices;
  map<string, vector<string>> edges;
  
  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // -- undirected graphs
    
    // create an undirected anonymous graph randomly
    string dotgraph {randGraph (10, UNDIRECTED_GRAPH, UNDIRECTED_EDGE, "",
				vertices, edges)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the graph is acknowledged as an undirected graph
    ASSERT_EQ ("graph", parser.get_type ()) << dotgraph << endl;

    // -- directed graphs
    
    // create an undirected anonymous graph randomly
    dotgraph = randGraph (10, DIRECTED_GRAPH, DIRECTED_EDGE, "",
			  vertices, edges);

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
  
  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // randomly choose a name for this graph
    string graphname = randString (10);

    // -- undirected graphs
    
    // create an undirected graph randomly with the given name
    string dotgraph {randGraph (10, UNDIRECTED_GRAPH, UNDIRECTED_EDGE, graphname,
				vertices, edges)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the graph is acknowledged as an undirected graph
    ASSERT_EQ ("graph", parser.get_type ()) << dotgraph << endl;

    // -- directed graphs
    
    // create a directed graph randomly with the given name
    dotgraph = randGraph (10, DIRECTED_GRAPH, DIRECTED_EDGE, graphname,
			  vertices, edges);

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
  
  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // -- undirected graphs
    
    // create an anonymous undirected graph randomly
    string dotgraph {randGraph (10, UNDIRECTED_GRAPH, UNDIRECTED_EDGE, "",
				vertices, edges)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the name retrieved equals the empty string
    ASSERT_EQ ("", parser.get_name ()) << dotgraph << endl;

    // -- directed graphs
    
    // create an anonymous directed graph randomly
    dotgraph = randGraph (10, DIRECTED_GRAPH, DIRECTED_EDGE, "",
			  vertices, edges);

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
  
  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // randomly choose a name for this graph
    string graphname = randString (10);

    // -- undirected graphs
    
    // create an undirected graph randomly with the given name
    string dotgraph {randGraph (10, UNDIRECTED_GRAPH, UNDIRECTED_EDGE, graphname,
				vertices, edges)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the name retrieved equals the name chosen
    ASSERT_EQ (graphname, parser.get_name ()) << dotgraph << endl;

    // -- directed graphs
    
    // create a directed graph randomly with the given name
    dotgraph = randGraph (10, DIRECTED_GRAPH, DIRECTED_EDGE, graphname,
			  vertices, edges);

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
  
  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // randomly choose a name for this graph
    string graphname = randString (10);

    // -- undirected graphs
    
    // create an undirected graph randomly with the given name
    string dotgraph {randGraph (10, UNDIRECTED_GRAPH, UNDIRECTED_EDGE, graphname,
				vertices, edges)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the list of source vertices retrieved from the parser is equal to
    // the list of vertices randomly generated
    vector<string> dotvertices = parser.get_vertices ();
    ASSERT_TRUE (equalVectors<string> (vertices, dotvertices)) << dotgraph << endl;

    // -- directed graphs
    
    // create an undirected graph randomly with the given name
    dotgraph = randGraph (10, DIRECTED_GRAPH, DIRECTED_EDGE, graphname,
			  vertices, edges);

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
  
  srand(time(nullptr));  

  for (auto i = 0 ; i < NB_TESTS ; i++) {
  
    // create a dot parser
    dot::parser parser;
    
    // randomly choose a name for this graph
    string graphname = randString (10);

    // -- undirected graphs
    
    // create an undirected graph randomly with the given name
    string dotgraph {randGraph (10, UNDIRECTED_GRAPH, UNDIRECTED_EDGE, graphname,
				vertices, edges)};

    // parse the graph
    parser.parse_string (dotgraph);

    // check the list of vertices retrieved from the parser is equal to the list
    // of vertices randomly generated
    map<string, vector<string>> dotedges = parser.get_graph ();
    ASSERT_TRUE (equalMaps<string> (edges, dotedges)) << dotgraph << endl;

    // -- directed graphs
    
    // create an undirected graph randomly with the given name
    dotgraph = randGraph (10, DIRECTED_GRAPH, DIRECTED_EDGE, graphname,
			  vertices, edges);

    // parse the graph
    dot::parser diparser;
    diparser.parse_string (dotgraph);

    // check the list of vertices retrieved from the parser is equal to the list
    // of vertices randomly generated
    dotedges = diparser.get_graph ();
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
