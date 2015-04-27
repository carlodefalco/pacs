#include "newton.hpp"

#ifndef NEWTON_CPP
#define NEWTON_CPP 1

namespace RootFinding {

  template<class real>
  Newton<real>::Newton (real tol, int maxit) 
    : IterativeMethod<real>(tol,
                            maxit,
                            IterativeMethod<real>::INCREMENT) {}

  template<class real>
  real
  Newton<real>::apply (real xp, fctptr f, fctptr df)
  {
    real v = f(xp);
    real xv;
    real derv;
    
    this->M_nit = 0;
	
    do
      {
        xv = xp;
        derv = df(xv);
        if (! derv)
          {
            std::cerr << "ERROR: Division by 0 occurred "
              "in Newton::apply()" << std::endl;
            exit (1);
          }
      	xp = xv - v / derv;
      	v = f (xp);
      	++ this->M_nit;
      }
    while (! (this->converged (fabs(xp - xv), fabs(v)))
           && (this->M_nit <= this->M_maxit) );
    return xp;
  }

  template<class real>
  std::ostream&
  operator<<(std::ostream& ostr,
             Newton<real>& r)
  {
    ostr << "* Newton Method *" << std::endl
         << "Tolerance           :" << '\t' << r.M_tol
         << std::endl
         << "Max # of iterations :" << '\t' << r.M_maxit
         << std::endl
         << "# of iterations :" << '\t' << r.nit ()
         << std::endl
         << std::flush;
    return ostr;
  }


}

#endif
