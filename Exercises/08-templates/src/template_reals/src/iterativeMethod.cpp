#ifndef ITERATIVEMETHOD_CPP
#define ITERATIVEMETHOD_CPP 1

#include "iterativeMethod.hpp"

namespace RootFinding {

  template<class real>
  IterativeMethod<real>::IterativeMethod (real tol, int maxit, checkT check)
    : M_tol(tol), M_maxit(maxit), M_check(check) {}

  template<class real>
  bool
  IterativeMethod<real>::converged(real increment, real residual) {
    return (M_check == INCREMENT && increment < M_tol) ||
      (M_check == RESIDUAL && residual < M_tol);
  }
}

#endif
