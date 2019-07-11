/* 
  TSThelperfunctions.h
  Description: Generic helpers for the Unit Test Cases only
  Started on  <Tue Mar 26 10:56:22 2019>
  ----------------------------------------------------------------------------- 
  Made by Carlos Linares López
  Login   <carlos.linares@uc3m.es>
*/

#ifndef   	TSTHELPERFUNCTIONS_H_
# define   	TSTHELPERFUNCTIONS_H_

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream> 
#include <map>
#include <set>
#include <vector>

using namespace std; 

// ----------------------------------------------------------------------------
// TESTS
// ----------------------------------------------------------------------------

// Verify that two vectors contain precisely the same items
template<class T>
bool equalVectors (vector<T>& v1, vector<T>& v2)
{

  // if sizes differ then exit immediately
  if (v1.size () != v2.size ())
    return false;
  
  // otherwise, sort both vectors and return whether they are identical or not
  sort (v1.begin (), v1.end ());
  sort (v2.begin (), v2.end ());
  return (v1 == v2);
}

// verify that the maps given are equal. Note that the values are vectors and
// hence these have to be checked with equalVectors
template<class T>
bool equalMaps (map<T, vector<T>>& m1, map<T, vector<T>>& m2)
{

  // if sizes differ then exit immediately
  if (m1.size () != m2.size ())
    return false;

  // otherwise, verify that both maps contain precisely the same keys with
  // precisely the same values
  for (auto& key1 : m1) {

    // in case this key does not exist in the second map exit immediately with
    // failure
    if (m2.find (key1.first) == m2.end ())
      return false;

    // now, verify that the values for this key are the same in both maps
    if (!equalVectors<T>(key1.second, m2[key1.first]))
      return false;
  }

  // at this point, it can be certified that both maps are the same
  return true;
}

// ----------------------------------------------------------------------------
// INTEGERS
// ----------------------------------------------------------------------------

// Generate a random number in the interval [-bound, +bound). Note that the
// result is given as a string
string randInt (int bound);

// ----------------------------------------------------------------------------
// STRINGS
// ----------------------------------------------------------------------------

// Generate a random string with characters in the sequence ASCII(45) -
// ASCII(122) which do not appear in the string exclude. Note that by default
// exclude makes the random string to contain only alphanum characters and the
// underscore
string randString (int length, std::string exclude=":;<=>?@[\\]^`");

// Generate a random quoted string with characters in the sequence ASCII (32) -
// ASCII (126) which do not appear in the string exclude. Note that by default
// exclude avoids the quoted string to be prematurely ended
string randQuotedString (int length, std::string exclude="\"");

// ----------------------------------------------------------------------------
// GRAPHS
// ----------------------------------------------------------------------------

// Generates a vector of nblabels strings, each one with the declaration of a
// label that might be either an integer, a floating-point number, an unquoted
// string or a quoted string
//
// It returns the values of all labels in a map whose index is the label name
// and the value is the label value
vector<string> randLabels (int nblabels, map<string, string>& labels);

// given a map of attributes (key=value) return a specification of attributes in
// the DOT language. The attributes actually included are returned in the map
// used_attrs
string generateDotAttrs (map<string, string>& attrs,
			 map<string, string>& used_attrs);

// given a map of attributes (key=value), return a dot specification of a node
// named after name with a random selection of attributes ---which could be
// repeated or not. The attributes actually included are returned in the map
// used_attrs
string generateDotVertex (const string& name, map<string, string>& attrs,
			  map<string, string>& used_attrs);

// given a map of attributes (key=value), return a dot specification of an edge
// according to the given edge_spec which can be either undirected
// (edge_spec=UNDIRECTED_EDGE) or directed (edge_spec=DIRECTED_EDGE). The
// attributes actually included are returned in the map used_attrs
string generateDotEdge (const int edge_spec, map<string, string>& attrs,
			map<string, string>& used_attrs);

// generate precisely nbvertices vertices each with a random number of
// attributes in the range [0, nbattrs] which are returned in the map
// attributes. The name of the vertices randomly generated are returned in
// vertices.
//
// note that this function does not return a dot specification. Indeed, the
// method generateDotVertex should be used instead to do the job
void randVertices (int nbvertices, int nbattrs,
		   vector<string>& vertices,
		   map<string, map<string, string>>& attributes);

// Generate a vector of strings, each one with the declaration of an edge or a
// single node statement. It generates precisely nbnodestmts node statements and
// nbedges edges which are either undirected (edge_spec=UNDIRECTED_EDGE),
// directed (edge_spec=DIRECTED_EDGE) or undirected/directed
// (edge_spec=MIX_EDGE). Each vertex has a random number of attributes randomly
// chosen in the interval [0, nbvertexattrs]. Likewise, each edge has a random
// number of attributes randomly chosen in the interval [0, nbedgeattrs].
//
// The collection of random source vertices and edges are returned in dedicated
// vars. In addition, the vertex attributes of all vertices randomly chosen
// (either those appearing in edges or as node statements) and the edges
// attributes are also returned in a dedicated container.
vector<string> randEdges (int nbnodestmts, int nbedges,
			  int nbvertexattrs, int nbedgeattrs, int edge_spec,
			  vector<string>& vertices, map<string, vector<string>>& edges,
			  map<string, map<string, string>>& vertexattrs,
			  map<string, map<string, map<string, string>>>& edgeattrs);
  
// Generate a random graph with precisely nbnodestmts node statements, nbedges
// edges defined over nbedges/2 vertices, and nblabels labels named after
// graph_name. It returns the textual definition of the graph in the DOT
// language. Each vertex has a random number of attributes randomly chosen in
// the interval [0, nbvertexattrs]. Likewise, each edge has a random number of
// attributes randomly chosen in the interval [0, nbedgeattrs].
//
// The collection of random vertices, edges and labels are returned in dedicated
// output vars. Also, the attributes selected for all vertices and edges are
// returned also in dedicated variables.
//
// The type of the graph is determined by the keyword graph_spec. It is
// undirected if graph_spec=UNDIRECTED_GRAPH and directed if
// graph_spec=DIRECTED_GRAPH. The type of edges is determined by edge_spec: they
// are all undirected if edge_spec=UNDIRECTED_EDGE, directed if
// edge_spec=DIRECTED_EDGE and a mixture if edge_spec=MIX_EDGE.
string randGraph (int nbnodestmts, int nbedges, int nblabels,
		  int nbvertexattrs, int nbedgeattrs, 
		  const string graph_name,
		  int graph_spec, int edge_spec, 
		  vector<string>& vertices, map<string, vector<string>>& edges,
		  map<string, string>& labels,
		  map<string, map<string, string>>& vertexattrs,
		  map<string, map<string, map<string, string>>>& edgeattrs);

#endif 	    /* !TSTHELPERFUNCTIONS_H_ */


/* Local Variables: */
/* mode:c++ */
/* fill-column:80 */
/* End: */
