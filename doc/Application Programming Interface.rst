************************************
Application Programming Interface
************************************

The library has been developed in C++ and it is intended to be used in
C++ programs as well. The *main* program using this library should
include its header with:

.. code-block:: c++

   #include <dot.h>

The library defines a *namespace* ``dot``. Hence, in the following the
namespace will be included as well though this can be avoided in C++
programs adding the following statement at the beginning:

.. code-block:: c++

   using namespace dot;
   
This section describes the various services provided by the API.

==============================
Creating a parser
==============================

The library provides both an *implicit* and an *explicit* constructor
shown below:

.. code-block:: c++

   dot::parser ();
   dot::parser (const string& filename);

The second form is used to directly specify a DOT file that should be
parsed.

.. index::
   single: implicit constructor
   single: explicit constructor
   pair: constructor; implicit
   pair: constructor; explicit


==============================
Parsing
==============================

.. index::
   single: parsing

There are two different services for parsing:

.. code-block:: c++

   bool dot::parse ();
   bool dot::parse (string contents);

If an explicit constructor has been used, then the first service
automatically parses the contents of the specified file in the
constructor. Otherwise, the string with the DOT statements has to be
explicitly given to the second service

It is possible to request the library to show additional information
as it is parsing the DOT statements. The method:

.. code-block:: c++

   void dot::set_verbose (bool value = true);

actually orders the library to do so, only if ``value`` is true ---so
that ``set_verbose (false)`` ensures that the library will silently
parse the DOT statements.


==============================
Accessing the graph
==============================

Finally, there is a third block of function members for actually
retrieving information from the graph once parsing is completed:

* .. code-block:: c++
		
     string dot::get_type () const

  Returns the type of the graph which should be either ``graph`` or ``digraph``
      
* .. code-block:: c++
		
     string dot::get_name () const

  Returns the name of the graph. If none was given it returns the empty string.

* .. code-block:: c++

     vector<string> dot::get_labels () const;

  Returns all label IDs defined in the graph. If none was declared, it
  returns an empty vector.

     
* .. code-block:: C++

     string dot::get_label_value (const string& name);

  It returns the value of a label ID identified by its *name*. Note it
  is always returned as a string in spite of its type. If no label was
  given with the specified *name* it raises an exception.
     
* .. code-block:: C++

     vector<string> dot::get_vertices () const;

  It returns a vector with the names of all vertices declared in the
  graph, even if they are not part of an edge or if they have no
  neighbours. If no vertices are declared in the graph, it then
  returns an empty vector.
     
* .. code-block:: c++

     map<string, vector<string>> dot::get_graph () const;

  It returns a map of vertex names to a vector of vertex names which
  are immediately adjacent to it. If a vertex is declared in the DOT
  language but it has no neighbours, then it is not included in the
  map.
     
* .. code-block:: c++

     vector<string> dot::get_neighbours (const string& name);

  It returns a vector with all vertices which are immediately
  accessible from the vertex identified by its *name*. An exception is
  raised if no vertex exists with the given *name*.
     
* .. code-block:: c++

     map<string, map<string, string>> dot::get_all_vertex_attributes () const;

  It returns a map indexed by vertex names to a map of attributes,
  where the primary key is the attribute name and its value is the
  attribute value. If no vertex attributes were declared in the DOT
  statements, it then returns an empty map.
     
* .. code-block:: c++

     map<string, string> dot::get_vertex_attributes (const string& name);

  It returns the map of attributes of the vertex identified by its
  *name*. The map is indexed by the attribute name and its value is
  the attribute value. An exception is raised if no vertex exists with
  the given *name*.
     
* .. code-block:: c++

     string dot::get_vertex_attribute (const string& name, const string& attrname);

  It returns the value of the attribute identified by *attrname* of
  the vertex *name*. An exception is raised if either no vertex exists
  with the given *name* or if it contains no attribute named
  *attrname*.
     
* .. code-block:: c++

     map<string, map<string, map<string, string>>> dot::get_all_edge_attributes ();

  It returns a map of origin vertices to a map of target vertices
  which hold a map of attributes indexed by the attribute name.
     
     
* .. code-block:: c++

     map<string, string> dot::get_edge_attributes (const string& origin, const string& target);

  It returns the map of attributes of the edge qualified by its
  *origin* and *target* vertices. An exception is raised if either the
  *origin* was not found in the DOT specification or if it has no
  neighbour named after *target*.
     
* .. code-block:: c++

     string dot::get_edge_attribute (const string& origin, const string& target, const string& attrname);

  It returns the value of the attribute named *attrname* of the edge
  qualified by its *origin* and *target* vertices. An exception is
  raised if either the *origin* vertex does not exist, the *target*
  vertex is not a neighbour of it, or no attribute named *attrname*
  was defined in that edge.


==============================
Exceptions
==============================

If something goes wrong, the library immediately raises an
exception. There are two types of exceptions implemented:

* .. code-block:: c++

     std::invalid_argument

  It is raised when the library is instructed to parse a file which
  does not exist or is not accessible.

* .. code-block:: c++

     dot::syntax_error

  It is raised by the library both for syntax errors or when accessing
  the services provided in the API with incorrect arguments.

==============================
Sample application
==============================

A typical snippet using this library looks like:

.. code-block:: c++

  // create a dot parser
  dot::parser parser {filename};

  // set the verbose flag
  parser.set_verbose (want_verbose);

  // and parse the contents
  try {
    
    parser.parse ();
  } catch (const std::exception& error) {

    cerr << " Fatal error: " << error.what () << endl;
    exit (EXIT_FAILURE);
  }  

where ``filename`` is a string with the path to the DOT file to parse,
and ``want_verbose`` is a boolean flag that is used to instruct the
library whether to show additional information or not. Because the
library raises an exception if something goes wrong, the ``parse``
method is included withing a *try-catch* block.

A full program using this library can be found in the `bitbucket
repository <https://bitbucket.org/clinares/dot-parser/>`_.
