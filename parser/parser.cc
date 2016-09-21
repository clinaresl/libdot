/* 
   parser - DOT parser built with the DOT parser library

   Copyright (C) 2016 Carlos Linares Lopez

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  

*/

#include <src/DOTparser.h>

#include <iostream>
#include <string>

#include <stdio.h>
#include <sys/types.h>
#include <getopt.h>
#include "system.h"

using namespace std;

#define EXIT_NICE 0
#define EXIT_FAILURE 1

extern "C" {
char *xstrdup (char *p);
}

// *** Globals
char *program_name;

// *** Option flags and variables
static struct option const long_options[] =
{
  {"file", required_argument, 0, 'f'},
  {"show-attributes", no_argument, 0, 's'},
  {"verbose", no_argument, 0, 'v'},
  {"help", no_argument, 0, 'h'},
  {"version", no_argument, 0, 'V'},
  {NULL, 0, NULL, 0}
};

// ** Prototypes

// Set all the option flags according to the switches specified.  Return the
// index of the first non-option argument.
static int decode_switches (int argc, char **argv, string& file, bool& show_attributes,
			      bool& want_verbose);

static void usage (int status);

int
main (int argc, char **argv)
{
  
  string file;              // file with the dot specification of this instance
  bool show_attributes;                // are attributes requested to be shown?
  bool want_verbose;        // whether verbose output has been requested or not

  string name;                                                    // graph name
  string type;                                                    // graph type
  
  program_name = argv[0];
  decode_switches (argc, argv, file, show_attributes, want_verbose);

  // *** parameter checking
  if (!file.size ()) {

    cerr << "\n Please, provide the file with the dot specification with --file" << endl;
    cerr << " See " << program_name << " --help for more details" << endl << endl;
    exit(EXIT_FAILURE);
  }
  
  // *** do the work

  // create an objet of a dot parser
  dot::parser parser (file);

  // set the verbosity level
  parser.set_verbose (want_verbose);

  // and parse its contents
  if (want_verbose)
    cout << endl;
  if (!parser.parse ())
    return EXIT_FAILURE;

  // show admin info of the graph
  cout << endl;
  cout << " Type: " << parser.get_type () << endl;
  cout << " Name: " << parser.get_name () << endl << endl;

  // in case the attributes have been required
  if (show_attributes) {

    // *** vertex attributes

    // get all vertices of the graph
    vector<string> vertices = parser.get_vertices ();
    if (vertices.size ()) {
      for (auto ivertex = vertices.begin () ; ivertex != vertices.end () ; ++ivertex) {

	// now, get all attributes for this specific vertex
	vector<string> attrs = parser.get_vertex_attributes (*ivertex);
	if (attrs.size ()) {
	  cout << " Vertex " << *ivertex << ":" << endl;
	  for (auto iattr = attrs.begin () ; iattr != attrs.end () ; ++iattr)

	    cout << "\t " << *iattr << ": " << parser.get_vertex_attribute (*ivertex, *iattr) << endl;
	  cout << endl;
	}
      }
    }
    
    // *** edge attributes

    // for every pair of vertices which are connected through an edge
    for (auto ivertex = vertices.begin () ;  ivertex != vertices.end () ; ++ivertex) {

      // get all nodes that are immediately reachable from this one
      vector<string> neighbours = parser.get_neighbours (*ivertex);
      for (auto jvertex = neighbours.begin () ; jvertex != neighbours.end () ; ++jvertex ) {

	// get all attributes of this edge
	vector<string> attrs = parser.get_edge_attributes (*ivertex, *jvertex);
	if (attrs.size ()) {

	  cout << " Edge " << *ivertex << " -> " << *jvertex << ":" << endl;

	  // and show all attributes of this edge
	  for (auto iattr = attrs.begin () ; iattr != attrs.end () ; ++iattr ) {
	    cout << "\t " << *iattr << ": " << parser.get_edge_attribute (*ivertex, *jvertex, *iattr) << endl;
	  }
	  cout << endl;
	}
      }
    }
  }

  // and exit
  return EXIT_NICE;
}

// Set all the option flags according to the switches specified.  Return the
// index of the first non-option argument.
static int
decode_switches (int argc, char **argv, string& file, bool& show_attributes,
		 bool& want_verbose)
{
  int c;

  // default values
  file = "";
  show_attributes = false;
  want_verbose = false;
  
  while ((c = getopt_long (argc, argv, 
			   "f"  /* file */
			   "s"  /* show-attributes */
			   "v"	/* verbose */
			   "h"	/* help */
			   "V",	/* version */
			   long_options, (int *) 0)) != EOF) {
    switch (c) {
    case 'f':		/* --file */
      file = optarg;
      break;
    case 's':		/* --show-attributes */
      show_attributes = 1;
      break;
    case 'v':		/* --verbose */
      want_verbose = 1;
      break;
    case 'V':
      printf ("DOT parser %s\n", VERSION);
      exit (0);
      
    case 'h':
      usage (0);
      
    default:
      usage (EXIT_FAILURE);
    }
  }
  
  return optind;
}

static void
usage (int status)
{
  cout << endl << " " << program_name << " parses dot files" << endl << endl;
  cout << " Usage: " << program_name << " [OPTION]" << endl << endl;
  cout << "\
 Options:\n\
      -f, --file                 file with the dot specification of the graph\n\
                                 see the README.md with information on the subset\n\
                                 of the dot language used\n\
      -s, --show-attributes      if given, all vertex and edge attributes are printed\n\
                                 on the console\n\
\n\
      --verbose                  print verbose information\n\
      -h, --help                 display this help and exit\n\
      -V, --version              output version information and exit\n\
\n";
  exit (status);
}

/* Local Variables: */
/* mode:c++ */
/* fill-column:80 */
/* End: */
