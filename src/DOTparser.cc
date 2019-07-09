/* 
  DOTparser.cc
  Description: Simple dot language parser implemented using regular
  ----------------------------------------------------------------------------- 

  Started on  <Fri Jul  1 20:24:29 2016 Carlos Linares Lopez>
  Last update <jueves, 21 julio 2016 10:28:09 Carlos Linares Lopez (clinares)>
  -----------------------------------------------------------------------------

  $Id::                                                                      $
  $Date::                                                                    $
  $Revision::                                                                $
  -----------------------------------------------------------------------------

  Made by Carlos Linares Lopez
  Login   <clinares@atlas>
*/

#include "DOTparser.h"

// Private services
// ----------------------------------------------------------------------------

// return in contents all the contents of the dot file stored in _filename. It
// returns true if the operation was successfully performed. Otherwise, it
// returns false
//
// the following is deemed as the fastes C++ way for reading the entire contents
// of a file into a single string. Others might prefer buffer iterators but that
// is surprisingly slow.
//
// See: http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
bool dot::parser::_read_file(string& contents) const
{
  std::ifstream in(_filename, std::ios::in);
  if (in) {
    
    in.seekg (0, std::ios::end);
    contents.resize (in.tellg ());
    in.seekg (0, std::ios::beg);
    in.read (&contents[0], contents.size ());
    in.close ();
    return true;
  }

  // if it was not possible to open the input stream, then return false
  return false;
}

// the following methods parse different types according to the given
// regexp. The second and third methods return in value the matching of the
// given regexp.

// just simply parse a regular expression. It return true if the given string
// was parsed and false otherwise.
bool dot::parser::_parse_void (string& content, const string& regexp) const
{
  smatch matches;
  regex pattern {regexp};                                   // create the regex
  if (regex_search (content, matches, pattern)) {  // in case a match was found
    content = matches.suffix ();   // move to the suffix of the original string
    return true;                                     // and return with success
  }
  return false;                                  // otherwise exit with failure
}

// parse a string and return its value in 'value' It return true if the given
// string was parsed and false otherwise.
bool dot::parser::_parse_string (string& content, const string& regexp,
				 string& value) const
{
  smatch matches;
  regex pattern {regexp};                                   // create the regex
  if (regex_search (content, matches, pattern)) {  // in case a match was found
    value = matches [1];                                      // copy the value
    content = matches.suffix ();   // move to the suffix of the original string
    return true;                                     // and return with success
  }
  return false;                                  // otherwise exit with failure
}

// parse an unsigned int and return its value in 'value' It return true if the
// given string was parsed and false otherwise.
bool dot::parser::_parse_unsigned_int (string& content, const string& regexp, 
				       unsigned int& value) const
{
  smatch matches;
  regex pattern {regexp};                                   // create the regex
  if (regex_search (content, matches, pattern)) {  // in case a match was found
    value = (unsigned int) atoi (string (matches[1]).c_str ());
    return true;                                     // and return with success
  }
  return false;                                  // otherwise exit with failure
}

// skips the section of contents if it contains comments. It returns the
// contents that result after stripping the leading comments. It honors both C
// and C++ comments (as specified in the dot language)
void dot::parser::_parse_comments (string& contents) const
{

  // both types of comments are acknowledged using regexps. The key question is
  // that there might be an arbitrary number of comments one following the other
  // at the beginning of contents
  while (_parse_void (contents, CPP_COMMENT));
}

// parse the given contents and if the specified regexp matches then its value
// is returned. Additionally, it is shown prefixed by a label on the standard
// output if and only if verbose is enabled
bool dot::parser::_read_string (string& contents, const string& regexp, string& value, const string& label) const
{
  _parse_comments (contents);
  if (_parse_string (contents, regexp, value))
    show_value (label, value, _verbose);
  else 
    return false;
  return true;
}  

// parse the given contents and return true if the given regexp
// matches. Additionally, it shows the given label if and only if verbose is
// enabled
bool dot::parser::_read_void (string& contents, const string& regexp, const string& label) const
{
  _parse_comments (contents);
  if (_parse_void (contents, regexp))
    show_void (label, _verbose);
  else
    return false;
  return true;
}

// parse an attributes section. The attributes read are return as a map that
// stores for every attribute its value as a string. It returns true if any
// attributes were found and raises an exception otherwise
bool dot::parser::_process_attributes (string& contents, map<string, string>& dict) const
{
  // check if the current contents start with an attributes section
  if (_parse_void (contents, ATTRIBUTE_BEGIN)) {

    bool eoattr = false;
    while (!eoattr) {
	
      string attrname, attrvalue;
	
      // yeah, an attributes section is started, so process it. Start getting
      // the name of the next attribute
      if (_parse_string (contents, ATTRIBUTE_NAME, attrname)) 
	show_value ("\tATTRIBUTE", attrname, _verbose);
      else 
	throw dot::syntax_error ("an ATTRIBUTE_NAME could not be parsed");

      // try first to read the value of this attribute followed by and end
      // of attribute section (']')
      if ((eoattr = _parse_string (contents, ATTRIBUTE_VALUE_END, attrvalue))) {
	show_value ("\tVALUE (*)", attrvalue, _verbose);

	// store the last read pair in the map
	dict[attrname] = attrvalue;
      }

      // otherwise, read the next value followed by a comma
      else if (_parse_string (contents, ATTRIBUTE_VALUE_NEXT, attrvalue)) {
	show_value ("\tVALUE", attrvalue, _verbose);

	// store the last read pair in the map
	dict[attrname] = attrvalue;
      }

      // if neither the attribute section is finished nor it is continued with
      // other assignments, then an error should be raise
      else 
	throw dot::syntax_error ("an ATTRIBUTE_VALUE could not be parsed");

      // check anyway if the attributes section gets closed here (this is good,
      // e.g., for preventing empty attributes sections)
      eoattr = _parse_void (contents, ATTRIBUTE_END) || eoattr;
    }

    // and return that an attribute section was successfully processed
    return true;
  }

  // at this point, no attribute section was processed
  return false;
}

// process the value of a label named labelid. This method should be invoked
// only when a label identifier has been found in contents which should then
// start with the value of the label. It returns true if it could successfully
// determine the label value and raises an exception otherwise
bool dot::parser::_process_label_value (string& contents, const string& labelid)
{

  string label_value;
  if (!_read_string (contents, LABEL_VALUE, label_value, "LABEL VALUE"))
    throw dot::syntax_error ("it was not possible to read a LABEL_VALUE");
  
  // if a value could be successfully processed for this label, then store
  // it
  _label[labelid] = label_value;
  return true;
}

// process the attributes of an edge joining two single vertices, orig_name and
// target_name, of the specified type edge_type, given in arcdict. It also
// processes the attributes of the target vertex if any are given in
// contents. It returns true upon successful completion and false otherwise
bool dot::parser::_process_single_vertex (string& contents,
					  const string& orig_name, const string& edge_type,
					  const string& target_name, map<string, string>& arcdict)
{

  // first, process the edge attributes: if and only if any edge attributes were
  // given
  if (arcdict.size ()) {

    // Syntax: [orig][target][attr name] = attr value
    _edge[orig_name][target_name] = arcdict;

    // also, in case this is an edge of the form "--" then annotate the same
    // attribute to the reversed direction
    if (edge_type == "--")
      _edge[target_name][orig_name] = arcdict;
  }
		
  // and process also this vertex attributes, if given
  map<string, string> targetdict;
  if (_process_attributes (contents, targetdict))
    _vertex [target_name].merge (targetdict);

  return true;
}
    
// process a multiple declaration of target vertices which should appear right
// at the beginning of the specified contents. The original vertex, type of edge
// and any edge attributes specified previously should be given now in
// orig_name, edge_type and arcdict. It returns true if and only if the block
// could be successfully parsed and raises an exception otherwise
bool dot::parser::_process_multiple_vertices (string& contents, const string& orig_name,
					      const string& edge_type, map<string, string>& arcdict)
{

  string target_name;
  
  // Multiple targets consist of an arbitrarily large list of vertices between
  // curly brackets
  if (_parse_void (contents, BLOCK_BEGIN)) {
    show_void (" --- Beginning multiple target specification ---", _verbose);
    bool eomts = false;           // end of multiple target specification
    while (!eomts) {

      // unless the multiple target specification is over
      _parse_comments (contents);
      if (!(eomts=_parse_void (contents, BLOCK_END))) {

	// get the next vertex name
	if (!_read_string (contents, VERTEX_NAME, target_name, "TARGET VERTEX"))
	  throw dot::syntax_error ("TARGET_NAME could not be parsed");
	else {

	  // make sure this target vertex was not processed before
	  if (find (_graph[orig_name].begin (), _graph[orig_name].end (),
		    target_name) == _graph[orig_name].end ())
	    _graph[orig_name].push_back (target_name);
	  if (edge_type!="->")
	    if (find (_graph[target_name].begin (), _graph[target_name].end (),
		      orig_name) == _graph[target_name].end ())
	      _graph[target_name].push_back (orig_name);
    
	  // process now the edge attributes given to this vertex and, if given,
	  // the attributes of the target vertex as well
	  _process_single_vertex (contents, orig_name, edge_type, target_name, arcdict);
	}
      }
    }
    show_void (" --- Ending multiple target specification ---", _verbose);
  }
  else
    throw dot::syntax_error ("TARGET_NAME could not be parsed");

  return true;
}

// process a trajectory or path defined over single definitions of vertices
// from the origin vertex specified. It returns true upon successful
// completion of the trajectory and raises an exception otherwise
bool dot::parser::_process_trajectory (string& contents, string& orig_name)
{

  string edge_type;
  string target_name;
  
  // while an edge is found in contents
  while (_read_string (contents, EDGE_TYPE, edge_type, "EDGE TYPE")) {

    map<string, string> nestedarcdict;
	  
    // yeah! A path is listed, so make the target vertex the origin, and
    // parse the attributes of this edge if any were given
    orig_name = target_name;
    _process_attributes (contents, nestedarcdict);

    // get the target vertex of this specific edge
    if (!_read_string (contents, VERTEX_NAME, target_name, "TARGET VERTEX"))
      throw dot::syntax_error ("a VERTEX_NAME could not be found while parsing a path");
    else {

      // make sure this target vertex was not processed before
      if (find (_graph[orig_name].begin (), _graph[orig_name].end (),
		target_name) == _graph[orig_name].end ())
	_graph[orig_name].push_back (target_name);
      if (edge_type!="->")
	if (find (_graph[target_name].begin (), _graph[target_name].end (),
		  orig_name) == _graph[target_name].end ())
	  _graph[target_name].push_back (orig_name);
      
      // and update all the edge attributes of this edge and also the attributes
      // of the target vertex if any were given
      _process_single_vertex (contents, orig_name, edge_type, target_name, nestedarcdict);
    }
  }

  return true;
}

// Public services
// ----------------------------------------------------------------------------

// get all labels of this graph
std::vector<std::string> dot::parser::get_labels () const
{
  vector<string> labels;

  // now, go over the adjacency map retrieving the names of all vertices
  for (auto& ilabel : _label)
    labels.push_back (ilabel.first);

  return labels;
}

// get the value of the label with the specified name
std::string dot::parser::get_label_value (const string& name)
{

  // verify that the specified label actually exists
  if (_label.find (name) == _label.end ())
    throw dot::syntax_error (" No label with the name '" + name + "' has been found");

  // otherwise return the value of this label
  return _label[name];
}
    
// get all source vertices of the graph
std::vector<std::string> dot::parser::get_vertices () const
{
  vector<string> vertices;

  // now, go over the adjacency map retrieving the names of all vertices
  for (auto& ivertex : _graph)
    vertices.push_back (ivertex.first);

  return vertices;
}

// return the graph parsed as a map where the index is a source vertex and
// the value is a vector of target vertices.
std::map<std::string, std::vector<std::string>> dot::parser::get_graph () const
{
  return _graph;
}

// get all nodes that are reachable from a given node. In case no node is
    // found with the given node an exception is raised.
std::vector<std::string> dot::parser::get_neighbours (const string& name)
{

  // verify that the specified name actually exists
  if (_graph.find (name) == _graph.end ())
    throw dot::syntax_error (" No node with the name '" + name + "' has been found");

  // otherwise return a vector with all neighbours of this node
  return _graph[name];
}

// get all attributes of all vertices of the graph
std::map<std::string, std::map<std::string, std::string>> dot::parser::get_all_vertex_attributes () const
{
  return _vertex;
}

// get all the attributes of the specified vertex. In case no node is found with
// the given node an exception is raised.
std::map<std::string, std::string> dot::parser::get_vertex_attributes (const string& name)
{
  
  // verify that the specified name actually exists
  if (_graph.find (name) == _graph.end ())
    throw dot::syntax_error (" No node with the name '" + name + "' has been found");

  // now, in case there are no vertices defined for this vertex, return an empty
  // map
  if (_vertex.find (name) == _vertex.end ())
    return map<string, string>();

  // otherwise, return its attributes
  return _vertex[name];
}

// return the value of an attribute defined for a specific vertex. In case no
// node is found with the given node, or no attribute with the given name is
// found for the specified node, an exception is raised.
std::string dot::parser::get_vertex_attribute (const string& name, const string& attrname)
{

  // verify that the specified name actually exists
  if (_graph.find (name) == _graph.end ())
    throw dot::syntax_error (" No node with the name '" + name + "' has been found");

  // verify there is an attribute with the given name
  if (_vertex[name].find (attrname) == _vertex[name].end ())
    throw dot::syntax_error (" The node '" + name + "' has no attribute with the name '" + attrname + "'");

  // at this point, both the vertex and the attribute name are known to exist,
  // so that report it
  return _vertex[name][attrname];
}

// get all the attributes of a specific edge qualified by its (origin,target)
// names. If either the origin does not exist, or the target is not found to be
// a neighbour of the origin, an exception is raised.
std::vector<std::string> dot::parser::get_edge_attributes (const string& origin,
							   const string& target)
{
  vector<string> attrs;

  // verify that the specified origin actually exists
  if (_graph.find (origin) == _graph.end ())
    throw dot::syntax_error (" No node with the name '" + origin + "' has been found");

  // verify now that the target is reachable from the origin. I know linear time
  // but the list of vertices should not be expected to be too large ... I
  // guess! ;)
  if (find (_graph[origin].begin (), _graph[origin].end (), target) == _graph[origin].end ())
    throw dot::syntax_error (" The node '" + origin + "' has no neighbour with the name '" + target + "'");

  // now, verify that the pair (origin,target) exists in the map of edge
  // attributes
  typename map<string,map<string,map<string,string>>>::iterator iattrs = _edge.find (origin);
  if (iattrs!=_edge.end ()) {
    typename map<string,map<string,string>>::iterator jattrs = iattrs->second.find (target);
    if (jattrs != iattrs->second.end ()) {

      // now, return all the attributes in this map
      for (auto& kattr: jattrs->second)
	attrs.push_back (kattr.first);
    }
  }

  return attrs;
}

// return the value of the given attribute defined for the vertex qualified by
// (origin,target) names. If either the origin does not exist, or the target is
// not found to be a neighbour of the origin, or no attribute is found in the
// edge joining those two vertices, an exception is raised.
std::string dot::parser::get_edge_attribute (const string& origin,
					     const string& target,
					     const string& attr)
{

  // verify that the specified origin actually exists
  if (_graph.find (origin) == _graph.end ())
    throw dot::syntax_error (" No node with the name '" + origin + "' has been found");

  // verify now that the target is reachable from the origin. I know linear time
  // but the list of vertices should not be expected to be too large ... I
  // guess! ;)
  if (find (_graph[origin].begin (), _graph[origin].end (), target) == _graph[origin].end ())
    throw dot::syntax_error (" The node '" + origin + "' has no neighbour with the name '" + target + "'");

  // now, verify that the pair (origin,target) exists in the map of edge
  // attributes
  typename map<string,map<string,map<string,string>>>::iterator iattrs = _edge.find (origin);
  if (iattrs!=_edge.end ()) {
    typename map<string,map<string,string>>::iterator jattrs = iattrs->second.find (target);
    if (jattrs != iattrs->second.end ()) {

      // in case there is no attribute with the specified name, raise an
      // exception
      if (jattrs->second.find (attr) == jattrs->second.end ())
	throw dot::syntax_error (" The edge joining vertices '" + origin + "' and '" + target + "' has no attribute named '" + attr + "'");
    }
  }

  // at this point, both the origin and the target are known to exist. Besides,
  // an attribute with the specified name is known to exist for the edge joining
  // those vertices, so just retrieve it
  return _edge[origin][target][attr];
}

// parse the given string. It returns true if the string could be successfully
// parse. Otherwise, it raises an exception with an error message
bool dot::parser::parse_string (string contents)
{

  // get the graph type
  // REMARK - "strict" is not acknowledged!
  if (!_read_string (contents, GRAPH_TYPE, _type, "TYPE"))
    throw dot::syntax_error ("GRAPH type could not be parsed");
  
  // get the graph name
  // REMARK - the graph name is entirely optional
  if (!_read_string (contents, GRAPH_NAME, _name, "NAME"))
    throw dot::syntax_error ("NAME could not be parsed");
  
  // block start
  if (!_read_void (contents, BLOCK_BEGIN, "--- Block begin found ---"))
    throw dot::syntax_error ("BEGIN OF BLOCK missing");
  
  // now, process all edges of the graph
  bool eob = false;                                             // end of block
  while (!eob) {

    // unless we are closing the block at this point
    _parse_comments (contents);
    if (!(eob=_parse_void (contents, BLOCK_END))) {

      // at the beginning of each line we could have either a vertex name, or a
      // label. Try first, reading a label
      string orig_name;
      if (_read_string (contents, LABEL_ASSIGNMENT, orig_name, "LABEL ID")) {

	// if a label was found, then retrieve its value and store it in this
	// parser
	_process_label_value (contents, orig_name);

	// this completes the processing of a single statement, consume the
	// semicolon in case it has been given
	_parse_comments (contents);
	_parse_void (contents, END_OF_STATEMENT);
	continue;
      }
      else 
	if (!_read_string (contents, VERTEX_NAME, orig_name, "SOURCE_VERTEX"))
	  throw dot::syntax_error ("neither a VERTEX_NAME nor a LABEL_ID have been provided");

      // and process also its attributes
      map<string, string> origdict;
      if (_process_attributes (contents, origdict))
	_vertex [orig_name].merge (origdict);

      // at this point, the statement could be over if it is a "node statement",
      // i.e., a node along with its attributes. In this case, the statement
      // should be ended with a semicolon
      _parse_comments (contents);
      if (_parse_void (contents, END_OF_STATEMENT)) {

	// if so, just record this vertex with no neighbours unless it was
	// already inserted and proceed with the next line
	if (_graph.find (orig_name) == _graph.end ())
	  _graph [orig_name] = vector<string>();
	continue;
      }

      // now, get the edge type, either directed or undirected
      string edge_type;
      if (!_read_string (contents, EDGE_TYPE, edge_type, "EDGE TYPE"))
	throw dot::syntax_error ("no EDGE_TYPE has been provided");

      // and process its attributes. Note that at this point, the edge
      // attributes are only parsed and saved. They are written to the private
      // data members later when invoking either process_single_vertex or
      // process_multiple_vertices
      map<string, string> arcdict;
      _process_attributes (contents, arcdict);      

      // the target can be specified in two different forms: either single or
      // multiple. A single target consists uniquely of a single vertex
      string target_name;
      if (!_read_string (contents, VERTEX_NAME, target_name, "TARGET VERTEX"))
	_process_multiple_vertices (contents, orig_name, edge_type, arcdict);

      // if the target was given in single form, then process the attributes of
      // the edge from its origin, if given
      else {

	// make sure this target vertex was not already processed ---because it
	// is a repeated entry
	if (find (_graph[orig_name].begin (), _graph[orig_name].end (),
		  target_name) == _graph[orig_name].end ())
	  _graph[orig_name].push_back (target_name);
	if (edge_type!="->")
	  if (find (_graph[target_name].begin (), _graph[target_name].end (),
		    orig_name) == _graph[target_name].end ())
	    _graph[target_name].push_back (orig_name);
	
	// process now the edge attributes given to this vertex and, if given,
	// the attributes of the target vertex as well
	_process_single_vertex (contents, orig_name, edge_type, target_name, arcdict);

	// now, maybe a trajectory is listed ---which is only allowed with
	// single vertices. Note that the origin vertex of the trajectory is the
	// target vertex of the preceding edge.
	_process_trajectory (contents, target_name);
      }

      // this completes the processing of a single statement, consume the
      // semicolon in case it has been given
      _parse_comments (contents);
      _parse_void (contents, END_OF_STATEMENT);
    }
  }

  show_void (" --- Block end found ---", _verbose);
  
  return true;                                                 // nicely return
}

// parse the file given in the explicit constructor of this instance. It returns
// true if the file could be successfully parse. Otherwise, it raises an
// exception with an error message
bool dot::parser::parse ()
{
  
  // read the file
  string contents;
  if (!_read_file (contents))
    throw invalid_argument ("It was not possible to read the contents of the dot file: " + _filename);

  // and now parse its contents
  return parse_string (contents);
}




/* Local Variables: */
/* mode:c++ */
/* fill-column:80 */
/* End: */
