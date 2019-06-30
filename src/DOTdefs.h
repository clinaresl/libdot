/* 
  DOTdefs.h
  Description: basic definitions
  ----------------------------------------------------------------------------- 

  Started on  <Fri Jul  1 09:11:32 2016 Carlos Linares Lopez>
  Last update <jueves, 21 julio 2016 10:27:21 Carlos Linares Lopez (clinares)>
  -----------------------------------------------------------------------------

  $Id::                                                                      $
  $Date::                                                                    $
  $Revision::                                                                $
  -----------------------------------------------------------------------------

  Made by Carlos Linares Lopez
  Login   <clinares@atlas>
*/

#ifndef   	DEFS_H_
# define   	DEFS_H_

// regexps used to parse the input files using a subset of the dot specification
// language. For a full description of the dot language, see:
//
//    http://www.graphviz.org/doc/info/lang.html

#include <iostream>
#include <string>

// Specification part
#define GRAPH_TYPE R"((digraph|graph))"
#define GRAPH_NAME R"(^[[:space:]]*([\-0-9a-zA-Z_]*))"
#define BLOCK_BEGIN R"(^[[:space:]]*\{)"
#define BLOCK_END R"(^[[:space:]]*})"
#define LABEL_ASSIGNMENT R"(^[[:space:]]*(([[:alnum:]])+)[[:space:]]*=)"
#define LABEL_VALUE R"(^[[:space:]]*((([+-]?(\.[[:digit:]]|[[:digit:]]+(\.[[:digit:]]*)?))|([[:alnum:]])+|(\".*\")+))[[:space:]]*)"
#define VERTEX_NAME R"(^[[:space:]]*([[:alnum:]]+))"
#define EDGE_TYPE R"(^[[:space:]]*(--|->))"
#define END_OF_STATEMENT R"(^[[:space:]]*;)"
#define CPP_COMMENT R"(^[[:space:]]*//.*\n)"

#define ATTRIBUTE_BEGIN R"(^[[:space:]]*\[)"
#define ATTRIBUTE_NAME R"(^[[:space:]]*(([[:alnum:]])+)[[:space:]]*=)"
#define ATTRIBUTE_VALUE_NEXT R"(^[[:space:]]*((([+-]?(\.[[:digit:]]|[[:digit:]]+(\.[[:digit:]]*)?))|([[:alnum:]])+|(\".*\")+))[[:space:]]*,)"
#define ATTRIBUTE_VALUE_END R"(^[[:space:]]*((([+-]?(\.[[:digit:]]|[[:digit:]]+(\.[[:digit:]]*)?))|([[:alnum:]]+)|(\"[^\"]*\")+))[[:space:]]*\])"
#define ATTRIBUTE_END R"(^[[:space:]]*\])"

namespace dot {
  
  using namespace std;

  // show a void line if and only if verbose is true
  void show_void (const string& line, bool verbose)
  {
    if (verbose)
      cout << " [" << line << "]" << endl;
  }

  // the following is a shortcut for writing data on cout if and only if verbose is true
  template<class T> void show_value (const string& line, const T& value, bool verbose)
  {
    if (verbose)
      cout << " [" << line << " " << value << "]" << endl;
  }
} // namespace dot

#endif 	    /* !DEFS_H_ */




/* Local Variables: */
/* mode:c++ */
/* fill-column:80 */
/* End: */
