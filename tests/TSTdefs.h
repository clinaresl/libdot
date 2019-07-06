/* 
  TSTdefs.h
  Description: Generic definitions for all unit test cases
  Started on  <Tue Mar 26 20:03:34 2019>
  ----------------------------------------------------------------------------- 
  Made by Carlos Linares López
  Login   <carlos.linares@uc3m.es>
*/

#ifndef   	TSTDEFS_H_
# define   	TSTDEFS_H_

// number of times each test is repeated. This is particularly important when
// tests are run using random values
const int NB_TESTS = 100;

// definition of graph types
const int UNDIRECTED_GRAPH = 0;
const int DIRECTED_GRAPH   = 1;

// definition of edge types
const int UNDIRECTED_EDGE = 0;
const int DIRECTED_EDGE   = 1;
const int MIX_EDGE        = 2;

#endif 	    /* !TSTDEFS_H_ */




/* Local Variables: */
/* mode:c++ */
/* fill-column:80 */
/* End: */
