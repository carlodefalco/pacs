#include "robust.hpp"

namespace RootFinding
{
  template <class real>
  Robust<real>::Robust (real tol, int maxit,
                        typename IterativeMethod<real>::checkT check,
                        real cfratio)
    :
    IterativeMethod<real> (tol, maxit, check),
    M_cfratio (cfratio),
    M_coarse (M_cfratio * tol, maxit, check),
    M_fine (tol, maxit) {}

  template <class real>
  real
  Robust<real>::apply (real a, real b,
                      typename IterativeMethod<real>::fctptr f,
                      typename IterativeMethod<real>::fctptr df)
  {
    return M_fine.apply  (M_coarse.apply(a, b, f), f, df );
  }

  template<class real>
  std::ostream&
  operator<<(std::ostream& ostr, Robust<real>& r)
  {
    ostr << "* Robust Method *" << std::endl
    << "Tolerance           :" << '\t' << r.M_tol
    << std::endl
    << "Max # of iterations :" << '\t' << r.M_maxit
    << std::endl
    << "# of iterations (C) :" << '\t' << r.nitcoarse()
    << std::endl
    << "# of iterations (F) :" << '\t' << r.nitfine()
    << std::endl
    << "C-to-F tol ratio    :" << '\t' << r.M_cfratio
    << std::flush;

    return ostr;
 }
}
