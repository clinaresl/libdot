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
// FLOATING-POINT NUMBERS
// ----------------------------------------------------------------------------

// Generate a random floating-point number in scientific notation or not. If the
// scientific notation is not used, the number is selected in the bound [-bound,
// +bound]. If the scientific notation is randomly chosen, the number is added
// an exponent in the interval [-299, +299]. Note that the result is given as a
// string
string randFloat (int bound);

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

// returns the declaration of a vertex in the DOT language. The vertex is
// randomly chosen among those in vertices and its name is returned in name.
//
// The vertex might be decorated with attributes among those in
// vertexselectedattrs. Those effecitvely used are returned in vertexattrs.
string randVertex (vector<string>& vertices, string& name,
		   map<string, map<string, string>>& vertexselectedattrs,
		   map<string, map<string, string>>& vertexattrs);

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

// generate up to nbnodestmts node statements randomly chosen among the vector
// of vertices and returns the specification in the DOT language as a vector of
// strings, each one with the specification of a single node statement. Each
// vertex can be decorated with vertex attributes which are randomly chosen
// among those in vertexselectedattrs.
//
// The vertices selected are returned in used_vertices, and the vertex
// attributes randomly picked up are returned in vertexattrs. It also updates
// information about the adjacency of the graph by adding the vertices without
// any neighbours
vector<string> randNodeStatements (int nbnodestmts, vector<string>& vertices,
				   map<string, map<string, string>>& vertexselectedattrs,
				   set<string>& used_vertices,
				   map<string, map<string, string>>& vertexattrs,
				   map<string, vector<string>>& edges);

// return the declaration of a block with multiple vertices in the DOT
// language. The number of vertices included is drawn from a uniform
// distribution in the range [1, nbmultiplenodes] and they are randomly selected
// from the given collection of vertices. Each one is decorated with attributes
// randomly selected from vertexselectedattrs.
//
// The vertices effectively chosen are returned in targets, and are added to
// used_vertices; the attributes selected are returned in the map vertexattrs.
string randMultipleVertices (int nbmultiplenodes,
			     vector<string>& vertices,
			     map<string, map<string, string>>& vertexselectedattrs,
			     vector<string>& target, 
			     set<string>& used_vertices,
			     map<string, map<string, string>>& vertexattrs);

// generate a path of the given length in the DOT language, where the path
// length is measured as the number of edges and should be strictly greater or
// equal than one. The path is terminated with a block with multiple vertices
// with probability p/100 and it contains a number of nodes randomly chosen in
// the interval [1, nbmultiplenodes].
//
// The path generated starts with an edge of the specified type which can be
// either undirected (edge_spec=UNDIRECTED_EDGE), directed
// (edge_spec=DIRECTED_EDGE) or undirected/directed (edge_spec=MIX_EDGE).
//
// Each vertex is randomly chosen from the vector of vertices.
//
// Both vertices and edges can be decorated with attributes randomly chosen from
// vertexselectedattrs and edgeselectedattrs.
//
// This function updates the following information:
//
// edges: contains the edges randomly created in the final graph
// used_vertices: contains the vertices randomly selected in the final graph
// vertexattrs: vertex attributes finally chosen in the final graph
// edgeattrs: edge attributes finally chosen in the final graph
string randPath (int pathlength, int p, int nbmultiplenodes, int edge_spec,
		 vector<string>& vertices,
		 map<string, vector<string>>& edges,
		 map<string, map<string, string>>& vertexselectedattrs,
		 map<string, string>& edgeselectedattrs,
		 set<string>& used_vertices,
		 map<string, map<string, string>>& vertexattrs,
		 map<string, map<string, map<string, string>>>& edgeattrs);

// Generate a vector of strings, each one with the declaration of a path with a
// length randomly chosen in the interval [1, pathlength] or a single node
// statement. The path is terminated with a block with multiple vertices with
// probability p/100 and it contains a number of nodes randomly chosen in the
// interval [1, nbmultiplenodes]. In addition, it generates precisely
// nbnodestmts node statements.
//
// Each path contains precisely nbedges edges which are either undirected
// (edge_spec=UNDIRECTED_EDGE), directed (edge_spec=DIRECTED_EDGE) or
// undirected/directed (edge_spec=MIX_EDGE). Each vertex has a random number of
// attributes randomly chosen in the interval [0, nbvertexattrs]. Likewise, each
// edge has a random number of attributes randomly chosen in the interval [0,
// nbedgeattrs].
//
// The collection of random source vertices and edges are returned in dedicated
// vars. In addition, the vertex attributes of all vertices randomly chosen
// (either those appearing in edges or as node statements) and the edges
// attributes are also returned in a dedicated container.
vector<string> randStatements (int nbnodestmts, int nbedges, int pathlength,
			       int p, int nbmultiplenodes, 
			       int nbvertexattrs, int nbedgeattrs, int edge_spec,
			       vector<string>& vertices, map<string, vector<string>>& edges,
			       map<string, map<string, string>>& vertexattrs,
			       map<string, map<string, map<string, string>>>& edgeattrs);
  
// Generate a random graph with precisely nbnodestmts node statements, nbedges
// edge statements defined over nbedges/2 vertices, each one with a random
// length between 1 and pathlength, and nblabels labels named after
// graph_name. Each path is terminated with a block with multiple vertices with
// probability p/100 and it contains a number of nodes randomly chosen in the
// interval [1, nbmultiplenodes]. 
//
// It returns the textual definition of the graph in the DOT
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
string randGraph (int nbnodestmts, int p, int nbmultiplenodes, int nbedges, int nblabels, int pathlength,
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
