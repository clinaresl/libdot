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

// Generates a vector of nblabels strings, each one with the declaration of a
// label that might be either an integer, a floating-point number, an unquoted
// string or a quoted string
//
// It returns the values of all labels in a map whose index is the label name
// and the value is the label value
vector<string> randLabels (int nblabels, map<string, string>& labels)
{

  vector<string> result;

  // loop over n
  for (auto i = 0 ; i < nblabels ; i++) {

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

// given a map of attributes (key=value) return a specification of attributes in
// the DOT language. The attributes actually included are returned in the map
// used_attrs
string generateDotAttrs (map<string, string>& attrs,
			 map<string, string>& used_attrs)
{

  string result;

  // start by making sure that the collection of used attributes is initially
  // empty
  used_attrs.clear ();
  
  // if and only if this vertex has attributes
  if (attrs.size ()) {

    // serialize all the attributes names to make it easier to pick up them
    // later
    vector<string> keys;
    for (auto& attr : attrs)
      keys.push_back (attr.first);
    
    // now, randomly decide how many attributes to include in the vertex
    // specification
    int nbattrs = rand () % attrs.size ();

    // and only in case that any attributes have been generated
    if (nbattrs) {
    
      // open the square brackets after a random number of blanks
      for (auto k = 0 ; k < rand () % 5 ; result+= " ", k++);
      result += "[";
    
      // and now, just pick up attributes randomly and add them to the vertex
      // specification. Be aware that there might be repeated keys but this is
      // desired indeed.
      for (auto i = 0 ; i < nbattrs ; i++) {

	// randomly choose an attribute name
	int attridx = rand () % keys.size ();
      
	// write the attribute along with its value always separating all fields
	// by a random number of blanks
	for (auto k = 0 ; k < rand () % 5 ; result+= " ", k++);
	result += keys[attridx];
	for (auto k = 0 ; k < rand () % 5 ; result+= " ", k++);
	result += "=";
	for (auto k = 0 ; k < rand () % 5 ; result+= " ", k++);
	result += attrs[keys[attridx]];
	for (auto k = 0 ; k < rand () % 5 ; result+= " ", k++);
	result += ",";

	// also make sure to annotate that this attribute was indeed used
	used_attrs [keys[attridx]] = attrs[keys[attridx]];
      }

      // and substitute the last comma by a closing square bracket
      result [result.size ()-1] =']';
    }
  }

  return result;
}

// given a map of attributes (key=value), return a dot specification of a node
// named after name with a random selection of attributes ---which could be
// repeated or not. The attributes actually included are returned in the map
// used_attrs
string generateDotVertex (const string& name, map<string, string>& attrs,
			  map<string, string>& used_attrs)
{

  // start with the specification of the vertex name
  string result {name};

  // make sure that the used attributes are all removed
  used_attrs.clear ();

  // and add the attributes to the vertex
  result += generateDotAttrs (attrs, used_attrs);

  // and return the dot specification
  return result;
}

// given a map of attributes (key=value), return a dot specification of an edge
// according to the given edge_spec which can be either undirected
// (edge_spec=UNDIRECTED_EDGE), directed (edge_spec=DIRECTED_EDGE) or random
// (edge_spec=MIX_EDGE). The attributes actually included are returned in the
// map used_attrs
string generateDotEdge (const int edge_spec, map<string, string>& attrs,
			map<string, string>& used_attrs)
{

  string result;
  
  // make sure that the used attributes are all removed
  used_attrs.clear ();

  // start with the type of edge to return according to the given specification
  int edge_type;
  switch (edge_spec) {

  case UNDIRECTED_EDGE:
    edge_type = UNDIRECTED_EDGE;
    result = "--";
    break;

  case DIRECTED_EDGE:
    edge_type = DIRECTED_EDGE;
    result = "->";
    break;

  case MIX_EDGE:
    if (rand () % 2) {
      edge_type = DIRECTED_EDGE;
      result = "->";
    }
    else {
      edge_type = UNDIRECTED_EDGE;
      result = "--";
    }
  }

  // and now add the attributes to the edge
  result += generateDotAttrs (attrs, used_attrs);

  // and return the edge specification
  return result;
}

// generate precisely nbvertices vertices each with a random number of
// attributes in the range [0, nbattrs] which are returned in the map
// attributes. The name of the vertices randomly generated are returned in
// vertices.
//
// note that this function does not return a dot specification. Indeed, the
// method generateDotVertex should be used instead to do the job
void randVertices (int nbvertices, int nbattrs,
		   vector<string>& vertices,
		   map<string, map<string, string>>& attributes)
{

  // make sure that both the collection of vertices and their attributes are
  // initially empty
  vertices.clear ();
  attributes.clear ();
  
  // create precisely nbvertices random vertices
  for (auto i = 0 ; i < nbvertices ; i++) {

    string vertex;
    
    // randomly create a new vertex name and add it to the collection of
    // vertices
    vertex = randString (10);
    vertices.push_back (vertex);

    // generate precisely nbattrs labels
    map<string, string> labels;
    vector<string> vertexattrs = randLabels (nbattrs, labels);

    // and now add these attributes to this vertex
    attributes[vertex] = labels;
  }
}

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
			  map<string, map<string, map<string, string>>>& edgeattrs)
{
  vector<string> result;
  set<string> used_vertices;

  // a specific map is needed to record the vertex attributes selected in the
  // random generation of vertices
  map<string, map<string, string>> vertexselectedattrs;

  // clear the collection of vertices and edges to ensure that the resulting
  // variables are consistent with the textual description
  vertices.clear ();
  edges.clear ();

  // and also clear the collection of vertex and edge attributes
  vertexattrs.clear ();
  edgeattrs.clear ();

  // now, create exactly n/2 different vertices. Bear in mind however that maybe
  // not all of them are used since they are randomly chosen. Note that the
  // vertices randomly created are returned in vertices and randEdges should
  // return in the same vector those that are actually used. For this we use a
  // set, used_vertices
  randVertices (nbedges/2, nbvertexattrs, vertices, vertexselectedattrs);

  // choose also a collection of random attributes for qualifying the edges
  map<string, string> edgeselectedattrs;
  randLabels (nbedgeattrs, edgeselectedattrs);
  
  // create the node statements
  for (auto i = 0 ; i < nbnodestmts ; i++) {

    string output;
    map<string, string> vertexusedattrs;  // attrs randomly chosen for a vertex
    
    // choose a source vertex and add it to the collection of used vertices
    // unless it has been already inserted
    int sourceid = rand () % (vertices.size ());
    used_vertices.insert (vertices[sourceid]);

    // start the declaration of the edge with the source vertex
    string source = generateDotVertex (vertices[sourceid], vertexselectedattrs[vertices[sourceid]],
				       vertexusedattrs);
    output += "\t" + source + ";";

    // now, add the collection of vertex attributes effectively chosen to the
    // collection of vertex attributes to return
    if (vertexusedattrs.size ())
      vertexattrs[vertices[sourceid]].merge (vertexusedattrs);

    // and add it to the vector of edges in dot format
    result.push_back (output);
  }
  
  // and now create the edges
  for (auto i = 0 ; i < nbedges ; i++) {

    string output;
    map<string, string> vertexusedattrs;  // attrs randomly chosen for a vertex
    map<string, string> edgeusedattrs;    // attrs randomly chosen for a vertex
    
    // choose a source vertex and add it to the collection of used vertices
    // unless it has been already inserted
    int sourceid = rand () % (vertices.size ());
    used_vertices.insert (vertices[sourceid]);

    // start the declaration of the edge with the source vertex
    string source = generateDotVertex (vertices[sourceid], vertexselectedattrs[vertices[sourceid]],
				       vertexusedattrs);
    output += "\t" + source + " ";

    // now, add the collection of vertex attributes effectively chosen to the
    // collection of vertex attributes to return
    if (vertexusedattrs.size ())
      vertexattrs[vertices[sourceid]].merge (vertexusedattrs);

    // add the edge. First, decide the type of edge
    int edge_type;
    if (edge_spec == MIX_EDGE) {
      if (rand ()%2)
	edge_type = DIRECTED_EDGE;
      else
	edge_type = UNDIRECTED_EDGE;
    }
    else
      edge_type = edge_spec;

    // and then add it along with its attributes if any has been requested
    output += generateDotEdge (edge_type, edgeselectedattrs, edgeusedattrs);

    // target vertex
    int targetid = rand () % vertices.size ();
    string target = generateDotVertex (vertices [targetid], vertexselectedattrs [vertices [targetid]],
				       vertexusedattrs);
    output += " " + target + ";";

    // and add the vertex attributes effectively chosen
    if (vertexusedattrs.size ())
      vertexattrs [vertices[targetid]].merge (vertexusedattrs);

    // and add also the edge attributes to the edge ---in both directions if
    // required
    if (edgeusedattrs.size ()) {
      map<string, string> edgemergedattrs {edgeusedattrs};
      edgeattrs [vertices[sourceid]][vertices[targetid]].merge (edgeusedattrs);

      edgeusedattrs = edgemergedattrs;
      if (edge_type == UNDIRECTED_EDGE)
	edgeattrs [vertices[targetid]][vertices[sourceid]].merge (edgeusedattrs);
    }
    
    // and add it to the vector of edges in dot format
    result.push_back (output);

    // update the collection of edges. Note that it is possible that the same
    // edge is repeated in the graph so that we verify first that the new edge
    // has not been recorded before.
    if (find (edges[vertices[sourceid]].begin (), edges[vertices[sourceid]].end (),
	      vertices[targetid]) == edges[vertices[sourceid]].end ())
      edges[vertices[sourceid]].push_back (vertices[targetid]);

    // if this is an undirected edge then the same operation should be performed
    // in the opposite direction
    if (edge_type == UNDIRECTED_EDGE) {

      if (find (edges[vertices[targetid]].begin (), edges[vertices[targetid]].end (),
		vertices[sourceid]) == edges[vertices[targetid]].end ())
	edges[vertices[targetid]].push_back (vertices[sourceid]);

      // in addition, the target vertex is used also as a source vertex, so
      // annotate it unless it has been already inserted
      used_vertices.insert (vertices[targetid]);
    }
  }

  // now, update the collection of vertices effectively used
  vertices.clear ();
  vertices.assign (used_vertices.begin (), used_vertices.end ());

  // and return the dot specification computed so far
  return result;
}

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
		  map<string, map<string, map<string, string>>>& edgeattrs)
{

  // before starting, make sure that all containers returning information about
  // the graph randomly generated are initially cleared
  vertices.clear ();
  edges.clear ();
  labels.clear ();
  vertexattrs.clear ();
  edgeattrs.clear ();
  
  // first line with the name of the graph
  string output = (graph_spec == UNDIRECTED_GRAPH)
    ? "graph"
    : "digraph";
  output += " ";

  // write now the name of the graph
  output += graph_name + " ";

  // generate the edges and add them all to the body
  vector<string> body = randEdges (nbnodestmts, nbedges,
				   nbvertexattrs, nbedgeattrs, edge_spec,
				   vertices, edges,
				   vertexattrs, edgeattrs);

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
