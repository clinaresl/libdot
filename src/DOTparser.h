/* 
  DOTparser.h
  Description: Simple dot language parser implemented using regular
  expressions
  ----------------------------------------------------------------------------- 

  Started on  <Fri Jul  1 09:08:22 2016 Carlos Linares Lopez>
  Last update <jueves, 21 julio 2016 10:30:14 Carlos Linares Lopez (clinares)>
  -----------------------------------------------------------------------------

  $Id::                                                                      $
  $Date::                                                                    $
  $Revision::                                                                $
  -----------------------------------------------------------------------------

  Made by Carlos Linares Lopez
  Login   <clinares@atlas>
*/

#ifndef   	PARSER_H_
# define   	PARSER_H_

#include "DOTdefs.h"

#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <utility>
#include <vector>

namespace dot {

  using namespace std;

  class parser {

  private:

    // INVARIANTS: every dot parser consists of a filename which is stored in a
    // private data member. The parser is responsible to process the contents of
    // this file sequentially discanding those parts that are successfully
    // processed
    string _filename;           // filename with the dot specification to parse

    // INVARIANTS: each graph has a type (either directed or undirected) and a
    // name (which can be the empty string). They are stored in dedicated data
    // members
    string _type;                  // graph type, either directed or undirected
    string _name;              // graph name which can be also the empty string

    // graphs are represented like adjacency maps which are indexed by the
    // vertex name given in the dot file. Each entry of the map consists then of
    // a vector of adjacent vertices
    map<string, vector<string>> _graph;

    // graphs can contain an arbitrary collection of labels which must be given
    // a value. These are stored in the following data member
    map<string, string> _label;
    
    // each graph is made of vertices and edges which can be characterized with
    // attributes. These are stored in a couple of maps:
    //
    //    _vertex stores for every vertex name a map of attributes of the form
    //    "name"->"value"
    //    _edge stores for every vertex name a map which is indexed with the
    //    target vertex name and a map of attribute names and values.
    //
    // In both cases, though values can be casted into different types, they are
    // internally stored as strings.
    map<string,map<string,string>> _vertex;
    map<string,map<string,map<string, string>>> _edge;

    // Additionally, the user can explicitly request verbose output while
    // parsing the dot specification file. It is disabled by default
    bool _verbose;                     // whether the user wants verbose output
    
  private:

    // return in contents all the contents of the dot file stored in _file. It
    // returns true if the operation was successfully performed. Otherwise, it
    // returns false
    bool _read_file (string& contents) const;
    
    // the following methods parse different types according to the given
    // regexp. The second and third methods return in value the matching of the
    // given regexp.

    // just simply parse a regular expression. It return true if the given
    // string was parsed and false otherwise.
    bool _parse_void (string& content, const string& regexp) const;

    // parse a string and return its value in 'value' It return true if the
    // given string was parsed and false otherwise.
    bool _parse_string (string& content, const string& regexp, string& value) const;

    // parse an unsigned int and return its value in 'value' It return true if
    // the given string was parsed and false otherwise.
    bool _parse_unsigned_int (string& content, const string& regexp, 
			      unsigned int& value) const;

    // skips the section of contents if it contains comments. It returns the
    // contents that result after stripping the leading comments. It honors both
    // C and C++ comments (as specified in the dot language)
    void _parse_comments (string& contents) const;

    // parse the given contents and if the specified regexp matches then its value
    // is returned. Additionally, it is shown prefixed by a label on the standard
    // output if and only if verbose is enabled
    bool _read_string (string& contents, const string& regexp, string& value, const string& label) const;

    // parse the given contents and return true if the given regexp
    // matches. Additionally, it shows the given label if and only if verbose is
    // enabled
    bool _read_void (string& contents, const string& regexp, const string& label) const;
    
    // parse an attributes section. The attributes read are return as a map that
    // stores for every attribute its value as a string. It returns true if any
    // attributes were found and raises an exception otherwise
    bool _process_attributes (string& contents, map<string, string>& dict) const;

    // process the value of a label named labelid. This method should be invoked
    // only when a label identifier has been found in contents which should then
    // start with the value of the label. It returns true if it could
    // successfully determine the label value and raises an exception otherwise
    bool _process_label_value (string& contents, const string& labelid);

    // process the attributes of an edge joining two single vertices, orig_name
    // and target_name, of the specified type edge_type, given in arcdict. It
    // also processes the attributes of the target vertex if any are given in
    // contents. It returns true upon successful completion and false otherwise
    bool _process_single_vertex (string& contents,
				 const string& orig_name, const string& edge_type,
				 const string& target_name, map<string, string>& arcdict);
  
    // process a multiple declaration of target vertices which should appear
    // right at the beginning of the specified contents. The original vertex,
    // type of edge and any edge attributes specified previously should be given
    // now in orig_name, edge_type and arcdict. It returns true if and only if
    // the block could be successfully parsed and raises an exception otherwise
    bool _process_multiple_vertices (string& contents, const string& orig_name,
				     const string& edge_type, map<string, string>& arcdict);

    // process a trajectory or path defined over single definitions of vertices
    // from the origin vertex specified. It returns true upon successful
    // completion of the trajectory and raises an exception otherwise
    bool _process_trajectory (string& contents, string& orig_name);
    
  public:

    // Default constructor are forbidden
    parser () = delete;
    
    // Explicit constructor
    parser (const string& filename)
      : _filename {filename}
    { }

    // get/set accessors
    string get_type () const
    { return _type; }
    string get_name () const
    { return _name; }

    // get all labels of this graph
    vector<string> get_labels () const;

    // get the value of the label with the specified name
    string get_label_value (const string& name);
    
    // get all vertices of the graph
    vector<string> get_vertices () const;
    
    // get all nodes that are reachable from a given node. In case no node is
    // found with the given node an exception is raised.
    vector<string> get_neighbours (const string& name);
    
    // get all the attributes of the specified vertex. In case no node is found
    // with the given node an exception is raised.
    vector<string> get_vertex_attributes (const string& name);
  
    // return the value of an attribute defined for a specific vertex. In case
    // no node is found with the given node, or no attribute with the given name
    // is found for the specified node, an exception is raised.
    string get_vertex_attribute (const string& name, const string& attrname);

    // get all the attributes of a specific edge qualified by its
    // (origin,target) names. If either the origin does not exist, or the target
    // is not found to be a neighbour of the origin, an exception is raised.
    vector<string> get_edge_attributes (const string& origin, const string& target);

    // return the value of the given attribute defined for the vertex qualified
    // by (origin,target) names. If either the origin does not exist, or the
    // target is not found to be a neighbour of the origin, or no attribute is
    // found in the edge joining those two vertices, an exception is raised.
    string get_edge_attribute (const string& origin, const string& target, const string& attr);

    // set the filename to parse
    void set_filename (string filename)
    { _filename = filename; }
    
    // Sets the verbose level to true by default
    void set_verbose (bool value = true)
    { _verbose = value; }
    
    // parse the file given in the construction of this instance. It returns
    // true if the file could be successfully parse. Otherwise, it raises an
    // exception with an error message
    bool parse ();    
    
  };  // class parser
  
} // namespace dot

#endif 	    /* !PARSER_H_ */


/* Local Variables: */
/* mode:c++ */
/* fill-column:80 */
/* End: */
