#ifndef BISECTION_HPP
#define BISECTION_HPP 1

#include "iterativeMethod.hpp"

namespace RootFinding

{
  /*!
    \class Bisection
    \brief Find the root of a non-linear equation using the bisection method

    This class provides an implementation of the Bisection method for
    rootfinding.
    \author Daniele A. Di Pietro
    \author Paolo G. Ferrandi
    \date 8-26-2005
  */

  template<class real>
  class Bisection : public IterativeMethod<real>
  {
  public:
    /** @name Constructors
     */
    //@{

    //! Constructor   
    Bisection (real tol, int maxit,
               typename IterativeMethod<real>::checkT check);

    //@}

    /** @name Methods
     */
    //@{

    //! Apply the method
    real
    apply(real, real,
          typename IterativeMethod<real>::fctptr);

    //@}


    // notice that the template parameter
    // for the friend function may differ
    // from real, so we must give it a different
    // name
    template<class _real>
    friend std::ostream&
    operator<<(std::ostream& ostr,
               Bisection<_real>& r)
    {
      ostr << "* Bisection Method *" << std::endl
           << "Tolerance           :" << '\t' << r.M_tol
           << std::endl
           << "Max # of iterations :" << '\t' << r.M_maxit
           << std::endl
           << "# of iterations :" << '\t' << r.nit ()
           << std::endl
           << std::flush;
      return ostr;

    };

  };
}

#endif
