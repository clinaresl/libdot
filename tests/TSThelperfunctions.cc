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
string randInt (int bound)
{

  return to_string (rand () % (2*bound) - bound);
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

// Generates a vector of n strings, each one with the declaration of a label
// that might be either an integer, a floating-point number, an unquoted string
// or a quoted string
//
// It returns the values of all labels in a map whose index is the label name
// and the value is the label value
vector<string> randLabels (int n, map<string, string>& labels)
{

  vector<string> result;

  // loop over n
  for (auto i = 0 ; i < n ; i++) {

    string key;
    string value;

    // randomly create a label name
    key = randString (10);

    // and add it to the next string
    string label = key;

    // create a random number of blanks
    for (auto j = 0 ; j < rand () % 5 ; label+= " ", j++);

    // and add the equality sign
    label += "=";
    
    // add a value
    switch (rand () % 4) {
    case 0: /* integers */
      value = randInt (1000000);
      break;
    case 1: /* floating-point numbers */
      value = "3.14159";
      break;
    case 2: /* unquoted strings */

      // note that we make sure that the first character of the value is not a
      // digit
      value = randString (1, ":;<=>?@[\\]^`0123456789") + randString (9);
      break;
    case 3: /*quoted strings*/
      value+= "\"" + randQuotedString (10) + "\"";
      break;
    }

    // create a random number of blanks
    for (auto j = 0 ; j < rand () % 5 ; label+= " ", j++);

    // and add the value
    label += value;

    // and update the value of this label
    labels [key] = value;

    // and insert it in the vector of strings to return
    result.push_back (label);
  }

  // and return the vector of strings computed so far
  return result;
}

// Generate a vector of strings, each one with the declaration of an edge. The
// number of edges generated is precisely nbedges and they are either undirected
// (edge_spec=UNDIRECTED_EDGE), directed (edge_spec=DIRECTED_EDGE) or
// undirected/directed (edge_spec=MIX_EDGE) with neither attributes nor labels.
//
// The collection of random source vertices and edges are returned in dedicated
// vars.
vector<string> randEdges (int nbedges, int edge_spec,
			  vector<string>& vertices, map<string, vector<string>>& edges)
{
  vector<string> result;
  set<string> used_vertices;                     // set of used source vertices

  // clear the collection of vertices and edges to ensure that the resulting
  // variables are consistent with the textual description
  vertices.clear ();
  edges.clear ();

  // now, create exactly n/2 different vertices. Bear in mind however that maybe
  // not all of them are used since they are randomly chosen
  for (auto i = 0; i < nbedges/2 ; i++)
    vertices.push_back (randString (10));

  // and now create the edges
  for (auto i = 0 ; i < nbedges ; i++) {

    string output;
    
    // choose a source vertex and add it to the set of used vertices
    int vertexid = rand () % (nbedges/2);
    used_vertices.insert (vertices[vertexid]);

    // start the declaration of the edge with the source vertex
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
    string target = vertices [rand () % (nbedges/2)];
    output += " " + target + ";";

    // and add it to the vector of edges in dot format
    result.push_back (output);

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
  return result;
}

// Generate a random graph with precisely nbedges edges defined over nbedges/2
// vertices, and nblabels labels, and no attributes at all named after
// graph_name. It returns the textual definition of the graph in the DOT
// language. The collection of random vertices and edges are returned in
// dedicated output vars. In addition, the labels and their values are also
// returned in a dedicated map.
//
// The type of the graph is determined by the keyword graph_spec. It is
// undirected if graph_spec=UNDIRECTED_GRAPH and directed if
// graph_spec=DIRECTED_GRAPH. The type of edges is determined by edge_spec: they
// are all undirected if edge_spec=UNDIRECTED_EDGE, directed if
// edge_spec=DIRECTED_EDGE and a mixture if edge_spec=MIX_EDGE.
string randGraph (int nbedges, int nblabels,
		  const string graph_name,
		  int graph_spec, int edge_spec, 
		  vector<string>& vertices, map<string, vector<string>>& edges,
		  map<string, string>& labels)
{

  // first line with the name of the graph
  string output = (graph_spec == UNDIRECTED_GRAPH)
    ? "graph"
    : "digraph";
  output += " ";

  // write now the name of the graph
  output += graph_name + " ";

  // generate the edges and add them all to the body
  vector<string> body = randEdges (nbedges, edge_spec, vertices, edges);

  // generate also the labels and add them to the body as well
  vector<string> labellines = randLabels (nblabels, labels);

  // note that, by default, the labels are neither started nor terminated with
  // any characters, so that a tab and a semicolon must be added now
  for (auto& label : labellines)
    body.push_back ("\t" + label + ";");

  // and now shuffle the lines
  random_shuffle (body.begin (), body.end ());
  
  // and now write the graph specification
  output += "{\n";
  for (auto line : body)
    output += line + "\n";
  output += "}\n";

  // and return the graph specification
  return output;
}



/* Local Variables: */
/* mode:c++ */
/* fill-column:80 */
/* End: */
