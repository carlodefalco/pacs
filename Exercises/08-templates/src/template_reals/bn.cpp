/*!
  \file bn.cpp
  \brief Compilable file for exercise 5, point 4
  \author Daniele A. Di Pietro
  \date 8-26-2005
*/

#include <iostream>
#include "bn.hpp"

using namespace RootFinding;
using namespace std;

int main ()
{

  Robust<double> r (1e-6, 100, IterativeMethod<double>::INCREMENT);

  cout << r.apply(0., 1., f<double>, df<double>) << endl;
  cout << r << endl;

  return 0;

}
