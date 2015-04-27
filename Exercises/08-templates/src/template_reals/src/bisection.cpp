#include "bisection.hpp"
#include <assert.h>

#ifndef BISECTION_CPP
#define BISECTION_CPP 1

namespace RootFinding
{
  
  template<class real>
  Bisection<real>::Bisection (real tol, int maxit,
                              typename IterativeMethod<real>::checkT check)
    : IterativeMethod<real>(tol, maxit, check) {}

  template<class real>
  real
  Bisection<real>::apply (real a, real b,
                          typename IterativeMethod<real>::fctptr f)
  {
    real u = f(a);	// Evaluate f on boundary a
    real l = b - a;     // Interval length
    real r;             // Residual
    real c = a + l;     // Mid-point

    this->M_nit = 0;
    r = f(c);

    assert (u * f (b) < 0.0);

    while (! (this->converged (fabs (l), fabs (r)))
           && (this->M_nit <= this->M_maxit))
      {
        (u * r < 0.) ? (b = c) : (a = c, u = r);
        l *= 0.5;
        c = a + l;
        r = f(c);
        ++ (this->M_nit);
    }
    return c;
  }
}

#endif
