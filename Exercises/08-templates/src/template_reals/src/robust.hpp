#ifndef ROBUST_HPP
#define ROBUST_HPP 1

#include "iterativeMethod.cpp"
#include "bisection.cpp"
#include "newton.cpp"

namespace RootFinding
{

  /*!
    \class Robust
    \brief Find the root of a non-linear equation using a robust method 
    \author Daniele A. Di Pietro
    \date 8-26-2005
  */

  template<class real>
  class Robust
    : public IterativeMethod<real>
  {
  public:

    //! Coarse method type
    typedef Bisection<real> coarseT;

    //! Fine method type
    typedef Newton<real> fineT;
    
    /** @name Constructors
     */
    //@{
    //! Constructor

    Robust (real, int,
            typename IterativeMethod<real>::checkT =
            IterativeMethod<real>::INCREMENT, real = 5e4);
    
    //@}
    /** @name Accessors
     */
    //@{
    
    //! Return the number of iterations of the coarse method
    int
    nitcoarse () { return this->M_coarse.nit (); }

    //! Return the number to iterations of the fine method
    int
    nitfine () { return this->M_fine.nit (); }
    
    //@}
    /** @name Methods
     */
    //@{
    //! Apply the method
    real
    apply (real, real,
           typename IterativeMethod<real>::fctptr,
           typename IterativeMethod<real>::fctptr);
    //@}


    //! Display the results
    // notice that the template parameter
    // for the friend function may differ
    // from real, so we must give it a different
    // name
    template<class _real>
    friend std::ostream&
    operator<<(std::ostream& ostr,
               Robust<_real>& r);


  private:

    //! The ratio between coarse and fine method tolerance
    real M_cfratio;

    //! The coarse method
    coarseT M_coarse;

    //! The fine method
    fineT M_fine;
  };
}

#endif
