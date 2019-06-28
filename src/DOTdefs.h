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
#define GRAPH_TYPE R"(^[[:space:]]*([[:alnum:]]+))"
#define GRAPH_NAME R"(^[[:space:]]*([\-0-9a-zA-Z_]*))"
#define BLOCK_BEGIN "^[[:space:]]*\\{"
#define BLOCK_END "^[[:space:]]*}"
#define LABEL_ASSIGNMENT "^[[:space:]]*(([[:alnum:]])+)[[:space:]]*="
#define LABEL_VALUE "^[[:space:]]*((([+-]?(\\.[[:digit:]]|[[:digit:]]+(\\.[[:digit:]]*)?))|([[:alnum:]])+|(\".*\")+))[[:space:]]*"
#define VERTEX_NAME "^[[:space:]]*([[:alnum:]]+)"
#define EDGE_TYPE "^[[:space:]]*(--|->)"
#define END_OF_STATEMENT "^[[:space:]]*;"
#define CPP_COMMENT "^[[:space:]]*//.*\n"

#define ATTRIBUTE_BEGIN "^[[:space:]]*\\["
#define ATTRIBUTE_NAME "^[[:space:]]*(([[:alnum:]])+)[[:space:]]*="
#define ATTRIBUTE_VALUE_NEXT "^[[:space:]]*((([+-]?(\\.[[:digit:]]|[[:digit:]]+(\\.[[:digit:]]*)?))|([[:alnum:]])+|(\".*\")+))[[:space:]]*,"
#define ATTRIBUTE_VALUE_END "^[[:space:]]*((([+-]?(\\.[[:digit:]]|[[:digit:]]+(\\.[[:digit:]]*)?))|([[:alnum:]]+)|(\"[^\"]*\")+))[[:space:]]*\\]"
#define ATTRIBUTE_END "^[[:space:]]*\\]"

namespace dot {
  
  using namespace std;

  // the following is a shortcut for writing data on cout
  template<class T> void show_value (const string& line, const T& value, bool verbose)
  {
    if (verbose)
      cout << " [" << line << " <" << value << ">]" << endl;
  }
} // namespace dot

#endif 	    /* !DEFS_H_ */




/* Local Variables: */
/* mode:c++ */
/* fill-column:80 */
/* End: */
