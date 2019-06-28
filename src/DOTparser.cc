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

// return in contents all the contents of the dot file stored in _file. It
// returns true if the operation was successfully performed. Otherwise, it
// raises an exception
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

  // if it was not possible to open the input stream, then throw an error
  throw invalid_argument (" It was not possible to read the contents of the dot file: " + _filename);
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

// parse the given contents looking for the graph type. It returns true if
// it could find the type and false otherwise. In case the graph type is
// successfully determined, it is returned in type.
bool dot::parser::_parse_graph_type (string& contents, string& type) const
{
  _parse_comments (contents);
  if (_parse_string (contents, GRAPH_TYPE, type))
    show_value ("TYPE", type, _verbose);
  else {
    cerr << " Syntax error: GRAPH type could not be parsed!" << endl;
    if (!_verbose)
      cerr << " try --verbose to obtain additional information" << endl;
    return false;
  }
  return true;
}

// parse the given contents looking for the graph name. It returns true if
// it could find the graph name and false otherwise.  In case the graph name
// is successfully determined, it is returned in name.
bool dot::parser::_parse_graph_name (string& contents, string& name) const
{
  _parse_comments (contents);
  if (_parse_string (contents, GRAPH_NAME, name))
    show_value ("NAME", name, _verbose);
  else {
    cerr << " Syntax error: NAME could not be parsed!" << endl;
    if (!_verbose)
      cerr << " try --verbose to obtain additional information" << endl;
    return false;
  }
  return true;
}

// parse the given contents looking for the beginning of a block. It returns
// true if it is found and false otherwise.
bool dot::parser::_parse_block_begin (string& contents) const
{
  _parse_comments (contents);
  if (_parse_void (contents, BLOCK_BEGIN))
    _show_void ("--- Block begin found ---", _verbose);
  else {
    cerr << " Syntax error: BEGIN OF BLOCK missing" << endl;
    if (!_verbose)
      cerr << " try --verbose to obtain additional information" << endl;
    return false;
  }
  return true;
}

// parse the given contents looking for the name of a vertex. It returns
// true if it is found and false otherwise.  In case the vertex name is
// successfully determined, it is returned in name.
bool dot::parser::_parse_vertex_name (string& contents, string& name) const
{
  _parse_comments (contents);
  if (_parse_string (contents, VERTEX_NAME, name))
    show_value ("VERTEX NAME", name, _verbose);
  else {
    cerr << " Syntax error: VERTEX_NAME could not be parsed" << endl;
    if (!_verbose)
      cerr << " try --verbose to obtain additional information" << endl;
    return false;
  }
  return true;
}

// parse the given contents looking for the type of an edge.  It returns
// true if it is found and false otherwise.  In case the edge type is
// successfully determined, it is returned in edge_type.
bool dot::parser::_parse_edge_type (string& contents, string& edge_type) const
{
  _parse_comments (contents);
  if (_parse_string (contents, EDGE_TYPE, edge_type))
    show_value ("EDGE TYPE", edge_type, _verbose);
  else {
    cerr << " Syntax error: EDGE_TYPE could not be parsed" << endl;
    if (!_verbose)
      cerr << " try --verbose to obtain additional information" << endl;
    return false;
  }
  return true;
}

// parse the given contents looking for the name of a target vertex. It then
// uses the name of the origin vertex and the type of the edge type (that should
// have been previously processed) to update the adjacency map describing the
// graph. It returns true if a target could be successfully processed, and false
// otherwise.
bool dot::parser::_parse_target_name (string& contents, string& name,
				      string orig_name, string edge_type)
{
  _parse_comments (contents);
  if (_parse_string (contents, VERTEX_NAME, name)) {
    show_value ("TARGET NAME", name, _verbose);
    _graph[orig_name].push_back (name);
    if (edge_type!="->")
      _graph[name].push_back (orig_name);
    return true;
  }
  return false;
}

// parse an attributes section. The attributes read are return as a map that
// stores for every attribute its value as a string. It returns true if any
// attributes were found and false otherwise.
bool dot::parser::_parse_attributes (string& contents, map<string, string>& dict) const
{
  // check if the current contents start with an attributes section
  if (_parse_void (contents, ATTRIBUTE_BEGIN)) {

    bool eoattr = false;
    while (!eoattr) {
	
      string attrname, attrvalue;
	
      // yeah, an attributes section is started, so process it. Start getting
      // the name of the next attribute
      if (_parse_string (contents, ATTRIBUTE_NAME, attrname)) {
	show_value ("\tATTRIBUTE", attrname, _verbose);
      }

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
      else {
	cerr << " Syntax error: ATTRIBUTE section is neither ended nor continued" << endl;
	if (!_verbose)
	  cerr << " try --verbose to obtain additional information" << endl;
	return false;
      }

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

// show a void line
void dot::parser::_show_void (const string& line, bool verbose) const
{
  if (verbose)
    cout << " [" << line << "]" << endl;
}

// Public services
// ----------------------------------------------------------------------------

// get all vertices of the graph
std::vector<std::string> dot::parser::get_vertices () const
{
  vector<string> vertices;

  // now, go over the adjacency map retrieving the names of all vertices
  if (_graph.size ())
    for (auto& ivertex : _graph)
      vertices.push_back (ivertex.first);

  return vertices;
}

// get all nodes that are reachable from a given node. In case no node is
    // found with the given node an exception is raised.
std::vector<std::string> dot::parser::get_neighbours (const string& name)
{

  // verify that the specified name actually exists
  if (_graph.find (name) == _graph.end ())
    throw invalid_argument (" No node with the name '" + name + "' has been found");

  // otherwise return a vector with all neighbours of this node
  return _graph[name];
}

// get all the attributes of the specified vertex. In case no node is found with
// the given node an exception is raised.
std::vector<std::string> dot::parser::get_vertex_attributes (const string& name)
{
  vector<string> attrs;
  
  // verify that the specified name actually exists
  if (_graph.find (name) == _graph.end ())
    throw invalid_argument (" No node with the name '" + name + "' has been found");

  // now, go over the attributes of this specific vertex, and retrieve the
  // attribute names defined for it
  for (auto iattr: _vertex[name])
    attrs.push_back (iattr.first);
  
  return attrs;
}

// return the value of an attribute defined for a specific vertex. In case no
// node is found with the given node, or no attribute with the given name is
// found for the specified node, an exception is raised.
std::string dot::parser::get_vertex_attribute (const string& name, const string& attrname)
{

  // verify that the specified name actually exists
  if (_graph.find (name) == _graph.end ())
    throw invalid_argument (" No node with the name '" + name + "' has been found");

  // verify there is an attribute with the given name
  if (_vertex[name].find (attrname) == _vertex[name].end ())
    throw invalid_argument (" The node '" + name + "' has no attribute with the name '" + attrname + "'");

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
    throw invalid_argument (" No node with the name '" + origin + "' has been found");

  // verify now that the target is reachable from the origin. I know linear time
  // but the list of vertices should not be expected to be too large ... I
  // guess! ;)
  if (find (_graph[origin].begin (), _graph[origin].end (), target) == _graph[origin].end ())
    throw invalid_argument (" The node '" + origin + "' has no neighbour with the name '" + target + "'");

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
    throw invalid_argument (" No node with the name '" + origin + "' has been found");

  // verify now that the target is reachable from the origin. I know linear time
  // but the list of vertices should not be expected to be too large ... I
  // guess! ;)
  if (find (_graph[origin].begin (), _graph[origin].end (), target) == _graph[origin].end ())
    throw invalid_argument (" The node '" + origin + "' has no neighbour with the name '" + target + "'");

  // now, verify that the pair (origin,target) exists in the map of edge
  // attributes
  typename map<string,map<string,map<string,string>>>::iterator iattrs = _edge.find (origin);
  if (iattrs!=_edge.end ()) {
    typename map<string,map<string,string>>::iterator jattrs = iattrs->second.find (target);
    if (jattrs != iattrs->second.end ()) {

      // in case there is no attribute with the specified name, raise an
      // exception
      if (jattrs->second.find (attr) == jattrs->second.end ())
	throw invalid_argument (" The edge joining vertices '" + origin + "' and '" + target + "' has no attribute named '" + attr + "'");
    }
  }

  // at this point, both the origin and the target are known to exist. Besides,
  // an attribute with the specified name is known to exist for the edge joining
  // those vertices, so just retrieve it
  return _edge[origin][target][attr];
}

// parse the file given in the construction of this instance. It returns true if
// the file could be successfully parse and false otherwise.
bool dot::parser::parse ()
{
  bool eob = false;                                             // end of block
  
  // -- read the file
  string contents;
  if (!_read_file (contents))
    return false;

  // -- parse the file

  // get the graph type and its ID (which is optional)
  // REMARK - "strict" is not acknowledged!
  if (!_parse_graph_type (contents, _type))
    return false;
  
  // get the graph name
  // REMARK - the graph name is entirely optional
  if (!_parse_graph_name (contents, _name))
    return false;
  
  // block start
  if (!_parse_block_begin (contents))
    return false;
  
  // now, process all edges of the graph
  while (!eob) {

    // unless we are closing the block at this point
    _parse_comments (contents);
    if (!(eob=_parse_void (contents, BLOCK_END))) {

      // get the next vertex name
      string orig_name;
      if (!_parse_vertex_name (contents, orig_name))
	return false;

      // and process also its attributes
      map<string, string> origdict;
      if (_parse_attributes (contents, origdict))
	_vertex [orig_name] = origdict;

      // now, get the edge type, either directed or undirected
      string edge_type;
      if (!_parse_edge_type (contents, edge_type))
	return false;

      // and process its attributes
      map<string, string> arcdict;
      _parse_attributes (contents, arcdict);

      // the target can be specified in two different forms: either single or
      // multiple. A single target consists uniquely of a single vertex
      string target_name;
      if (!_parse_target_name (contents, target_name, orig_name, edge_type)) {
	
	// if a single target was not recognized, then multiple targets are
	// tried. They consist of an arbitrarily large list of vertices between
	// curly brackets
	if (_parse_void (contents, BLOCK_BEGIN)) {
	  _show_void (" --- Beginning multiple target specification ---", _verbose);
	  bool eomts = false;           // end of multiple target specification
	  while (!eomts) {

	    // unless the multiple target specification is over
	    _parse_comments (contents);
	    if (!(eomts=_parse_void (contents, BLOCK_END))) {

	      // get the next vertex name
	      if (!_parse_target_name (contents, target_name, orig_name, edge_type)) {
		cerr << " Syntax error: TARGET_NAME could not be parsed" << endl;
		if (!_verbose)
		  cerr << " try --verbose to obtain additional information" << endl;
		return false;
	      }
	      else {

		// first, process the edge attributes: if and only if any edge
		// attributes were given
		if (arcdict.size ()) {

		  // Syntax: [orig][target][attr name] = attr value
		  _edge[orig_name][target_name] = arcdict;

		  // also, in case this is an edge of the form "--" then
		  // annotate the same attribute to the reversed direction
		  if (edge_type == "--")
		    _edge[target_name][orig_name] = arcdict;
		}
		
		// and process also this vertex attributes, if given
		map<string, string> targetdict;
		if (_parse_attributes (contents, targetdict))
		  _vertex [target_name] = targetdict;
	      }
	    }
	  }
	  _show_void (" --- Ending multiple target specification ---", _verbose);
	}
	else {
	  cerr << " Syntax error: TARGET_NAME could not be parsed" << endl;
	  if (!_verbose)
	    cerr << " try --verbose to obtain additional information" << endl;
	  return false;
	}
      }

      // if the target was given in single form, then process the attributes of
      // the edge from its origin, if given
      else 
	
	// if and only if any edge attributes were given
	if (arcdict.size ()) {

	  // Syntax: [orig][target][attr name] = attr value
	  _edge[orig_name][target_name] = arcdict;

	  // also, in case this is an edge of the form "--" then
	  // annotate the same attribute to the reversed direction
	  if (edge_type == "--")
	    _edge[target_name][orig_name] = arcdict;
	}

      // process now the attributes of the target vertex, if given
      map<string, string> targetdict;
      if (_parse_attributes (contents, targetdict))
	_vertex [target_name] = targetdict;

      // this completes the processing of a single statement, consume the
      // semicolon in case it has been given
      _parse_comments (contents);
      _parse_void (contents, END_OF_STATEMENT);
    }
  }

  _show_void (" --- Block end found ---", _verbose);
  
  return true;                                                 // nicely return
}



/* Local Variables: */
/* mode:c++ */
/* fill-column:80 */
/* End: */
