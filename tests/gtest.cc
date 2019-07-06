/* 
  gtest.cc
  Description: Google Test Cases
  Started on  <Mon Mar 25 14:15:54 2019>
  ----------------------------------------------------------------------------- 
  Made by Carlos Linares López
  Login   <carlos.linares@uc3m.es>
*/

#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}


/* Local Variables: */
/* mode:c++ */
/* fill-column:80 */
/* End: */
