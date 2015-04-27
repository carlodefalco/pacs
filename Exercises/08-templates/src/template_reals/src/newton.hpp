#ifndef NEWTON_HPP
#define NEWTON_HPP 1

#include "iterativeMethod.cpp"

namespace RootFinding
{
  /*!
    \class Newton
    \brief Find the root of a non-linear equation using the Newton method    
    \author Daniele A. Di Pietro
    \author Paolo G. Ferrandi
    \date 8-26-2005
  */

  template <class real>
  class Newton
    : public IterativeMethod<real>
  {

  public:

    // the type defined in the base class would
    // would need to be used with full specification,
    // including value of the template parameter
    // we use a typedef here for more convenient
    // naming. Notice the use of "typename" to let
    // the compiler know that IterativeMethod<real>::fctptr
    // is a type.
    typedef typename IterativeMethod<real>::fctptr fctptr;
    
    /** @name Constructors
     */
    //@{
    //! Constructor taking the tolerance and the maximum number of 
    //! iterations

    Newton (real, int);
    //@}
    /** @name Methods
     */
    //@{

    //! Apply the method
    real
    apply (real, fctptr, fctptr);


    // notice that the template parameter
    // for the friend function may differ
    // from real, so we must give it a different
    // name
    template<class _real>
    friend std::ostream&
    operator<<(std::ostream& ostr,
               Newton<_real>& r);

    //@}
  };
}

#endif
