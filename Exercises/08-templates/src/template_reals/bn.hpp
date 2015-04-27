/*!
  \file bn.hpp
  \brief Header file for bn
  \author Daniele A. Di Pietro
  \date 8-26-2005
*/

#ifndef BN_HPP
#define BN_HPP

// include the .cpp file so that
// template methods are implemented
#include "src/bisection.cpp"
#include "src/newton.cpp"
#include "src/robust.cpp"

// replace the typedef/using
// with a template parameter
// using RootFinding::real;

template<class real>
real
f(real x)
{
  return pow(x, 2) - .5;
}

template<class real>
real
df (real x)
{
  return 2.0 * x;
}

#endif
