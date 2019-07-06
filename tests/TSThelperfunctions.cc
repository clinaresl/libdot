/* 
  TSThelperfunctions.cc
  Description: Generic helpers for the Unit Test Cases only
  Started on  <Tue Mar 26 10:58:04 2019>
  ----------------------------------------------------------------------------- 
  Made by Carlos Linares López
  Login   <carlos.linares@uc3m.es>
*/

#include <vector>

#include "TSTdefs.h"
#include "TSThelperfunctions.h"

// ----------------------------------------------------------------------------
// INTEGERS
// ----------------------------------------------------------------------------

// Generate a random number in the interval [-bound, +bound)
int randInt (int bound)
{

  return rand () % (2*bound) - bound;
}

// ----------------------------------------------------------------------------
// STRINGS
// ----------------------------------------------------------------------------

// Generate a random string with characters in the sequence ASCII(45) -
// ASCII(122) which do not appear in the string exclude. Note that by default
// exclude makes the random string to contain only alphanum characters and the
// underscore
string randString (int length, string exclude)
{

  // just randomly sample a character from the set until the string gets the
  // requested length
  char randchr;
  std::string randstr = "";
  for (int i = 0 ; i < length ; i++) {
    do {
      randchr = (char) (rand () % (122 - 48 + 1) + 48);
    } while (exclude.find (randchr) != std::string::npos);
    randstr += randchr;
  }

  return randstr;
}

// Generate a random quoted string with characters in the sequence ASCII (32) -
// ASCII (126) which do not appear in the string exclude. Note that by default
// exclude avoids the quoted string to be prematurely ended
string randQuotedString (int length, std::string exclude)
{

  // just randomly sample a character from the set until the string gets the
  // requested length
  char randchr;
  std::string randstr = "";
  for (int i = 0 ; i < length ; i++) {
    do {
      randchr = (char) (rand () % (126 - 32 + 1) + 32);
    } while (exclude.find (randchr) != std::string::npos);
    randstr += randchr;
  }

  return randstr;
}

// ----------------------------------------------------------------------------
// GRAPHS
// ----------------------------------------------------------------------------

// Generate a string with a dot specification of precisely n either undirected
// (edge_spec=UNDIRECTED_EDGE), directed (edge_spec=DIRECTED_EDGE) or
// undirected/directed (edge_spec=MIX_EDGE) edges with neither attributes nor
// labels defined over n/2 vertices.
//
// It returns the textual definition of the edges in the DOT language. The
// collection of random sources vertices and edges are returned in dedicated
// vars.
string randEdges (int n, int edge_spec,
		  vector<string>& vertices, map<string, vector<string>>& edges)
{
  string output = "";
  set<string> used_vertices;                     // set of used source vertices

  // clear the collection of vertices and edges to ensure that the resulting
  // variables are consistent with the textual description
  vertices.clear ();
  edges.clear ();

  // now, create exactly n/2 different vertices. Bear in mind however that maybe
  // not all of them are used since they are randomly chosen
  for (auto i = 0; i < n/2 ; i++)
    vertices.push_back (randString (10));

  // and now create the edges
  for (auto i = 0 ; i < n ; i++) {

    // choose a source vertex and add it to the set of used vertices
    int vertexid = rand () % (n/2);
    used_vertices.insert (vertices[vertexid]);
    
    string source = vertices [vertexid];
    output += "\t" + source + " ";

    // edge
    int edge_type;
    switch (edge_spec) {

    case UNDIRECTED_EDGE:
      edge_type = UNDIRECTED_EDGE;
      output += "--";
      break;

    case DIRECTED_EDGE:
      edge_type = DIRECTED_EDGE;
      output += "->";
      break;

    case MIX_EDGE:
      if (rand () % 2) {
	edge_type = DIRECTED_EDGE;
	output += "->";
      }
      else {
	edge_type = UNDIRECTED_EDGE;
	output += "--";
      }
    }

    // target vertex
    string target = vertices [rand () % (n/2)];
    output += " " + target + ";\n";

    // update the collection of edges
    edges[source].push_back (target);
    if (edge_type == UNDIRECTED_EDGE) {
      edges[target].push_back (source);

      // in addition, the target vertex is used also as a source vertex, so
      // annotate it
      used_vertices.insert (target);
    }
  }

  // now, update the vector of source vertices actually considered
  vertices.clear ();
  vertices.assign (used_vertices.begin (), used_vertices.end ());
  
  // and return the dot specification computed so far
  return output;
}

// Generate a random graph with precisely n edges defined over n/2 vertices and
// no attributes at all named after graph_name. It returns the textual
// definition of the graph in the DOT language. The collection of vertices and
// edges are returned in dedicated output vars.
//
// The type of the graph is determined by the keyword graph_spec. It is
// undirected if graph_spec=UNDIRECTED_GRAPH and directed if
// graph_spec=DIRECTED_GRAPH. The type of edges is determined by edge_spec: they
// are all undirected if edge_spec=UNDIRECTED_EDGE, directed if
// edge_spec=DIRECTED_EDGE and a mixture if edge_spec=MIX_EDGE.
string randGraph (int n, int graph_spec, int edge_spec, const string graph_name,
		  vector<string>& vertices, map<string, vector<string>>& edges)
{

  // first line with the name of the graph
  string output = (graph_spec == UNDIRECTED_GRAPH)
    ? "graph"
    : "digraph";
  output += " ";

  // write now the name of the graph
  output += graph_name + " ";

  // and now write the graph specification
  output += "{\n";
  output += randEdges (n, edge_spec, vertices, edges);
  output += "}\n";

  // and return the graph specification
  return output;
}



/* Local Variables: */
/* mode:c++ */
/* fill-column:80 */
/* End: */
