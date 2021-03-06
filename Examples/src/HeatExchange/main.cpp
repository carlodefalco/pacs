#include <iostream> // input output
#include <cmath> // (for sqrt)
#include <vector>
#include <tuple>
#include "readParameters.hpp"
#include "GetPot.hpp"
#include "gnuplot-iostream.hpp"// interface with gnuplot
/*!
  @file main.cpp
  @brief Temperature distribution in a 1D bar.

  @detail
    We solve  \f$ -T^{\prime\prime}(x)+act*(T(x)-T_e)=0, 0<x<L \f$ with 
    boundary conditions \f$ T(0)=To; T^\prime(L)=0\f$
    
    **************************************************
    Linear finite elements
    Iterative resolution by Gauss Siedel.
    **************************************************
    
    Example adapted by Luca Formaggia from  a code found in 
    "Simulation numerique an C++" di I. Danaila, F. Hecht e
    O. Pironneau.
*/
//! helper function
void printHelp()
{
  std::cout<<"USAGE: main [-h] [-v] -p parameterFile (default: parameters.pot)"<<std::endl;
  std::cout<<"-h this help"<<std::endl;
  std::cout<<"-v verbose output"<<std::endl;
}

//! main program
int main(int argc, char** argv)
{
  using namespace std; // avoid std::
  int status(0); // final program status
  GetPot   cl(argc, argv);
  if( cl.search(2, "-h", "--help") )
    {
      printHelp();
      return 0;
    }
  // check if we want verbosity
  bool verbose=cl.search(1,"-v");
  // Get file with parameter values
  string filename = cl.follow("parameters.pot","-p");
  cout<<"Reading parameters from "<<filename<<std::endl;
  // read parameters
  const parameters param=readParameters(filename,verbose);
  // Transfer parameters to local variables
  // I use references to save memory (not really an issue here, it is just
  // to show a possible  use of references)
  const int&    itermax= param.itermax;   //max number of iteration for Gauss-Siedel
  const double& toler=param.toler;   // Tolerance for stopping criterion
  const double& L= param.L;  // Bar length
  const double& a1=param.a1; // First longitudinal dimension
  const double& a2=param.a2; //  Second longitudinal dimension
  const double& To=param.To; // Dirichlet condition
  const double& Te=param.Te; // External temperature (Centigrades)
  const double& k=param.k;  // Thermal conductivity
  const double& hc=param.hc; // Convection coefficient
  const int&    M=param.M; // Number of grid elements
  
  //! Precomputed coefficient for adimensional form of equation
  const double act=2.*(a1+a2)*hc*L*L/(k*a1*a2);

  // mesh size
  const double h=1./M;
  
  // Solution vector
  vector<double> theta(M+1);
  
  // Gauss Siedel is initialised with a linear variation
  // of T
  
  theta[0]=(To-Te)/Te;       //Condition at x=0
  for(unsigned int m=1;m <= M;m++)
    theta[m]=(1.-m*h)*(To-Te)/Te;
  
  // Gauss-Seidel
  // epsilon=||x^{k+1}-x^{k}||
  // Stopping criteria epsilon<=toler
  
  int iter=0;
  double xnew, epsilon;
     do
       { epsilon=0.;

	 // first M-1 row of linear system
         for(int m=1;m < M;m++)
         {   
	   xnew  = (theta[m-1]+theta[m+1])/(2.+h*h*act);
	   epsilon += (xnew-theta[m])*(xnew-theta[m]);
	   theta[m] = xnew;
         }

	 //Last row
	 xnew = theta[M-1]; 
	 epsilon += (xnew-theta[M])*(xnew-theta[M]);
	 theta[M]=  xnew; 

	 iter=iter+1;     
       }while((sqrt(epsilon) > toler) && (iter < itermax) );

    if(iter<itermax)
      cout << "M="<<M<<"  Convergence in "<<iter<<" iterations"<<endl;
    else
      {
	cerr << "NOT CONVERGING in "<<itermax<<" iterations "<<
	  "||dx||="<<sqrt(epsilon)<<endl;
	status=1;
      }

 // Analitic solution

    vector<double> thetaa(M+1);
     for(int m=0;m <= M;m++)
       thetaa[m]=Te+(To-Te)*cosh(sqrt(act)*(1-m*h))/cosh(sqrt(act));

     // writing results with format
     // x_i u_h(x_i) u(x_i) and lauch gnuplot 

     Gnuplot gp;
     std::vector<double> coor(M+1);
     std::vector<double> sol(M+1);
     std::vector<double> exact(M+1);

     cout<<"Result file: result.dat"<<endl;
     ofstream f("result.dat");
     for(int m = 0; m<= M; m++)
       {
	 // \t writes a tab 
         f<<m*h*L<<"\t"<<Te*(1.+theta[m])<<"\t"<<thetaa[m]<<endl;
	 // An example of use of tie and tuples!
	 std::tie(coor[m],sol[m],exact[m])=
	   std::make_tuple(m*h*L,Te*(1.+theta[m]),thetaa[m]);
       }
     // Using temporary files (another nice use of tie)
     gp<<"plot"<<gp.file1d(std::tie(coor,sol))<<
       "w lp title 'uh',"<< gp.file1d(std::tie(coor,exact))<<
       "w l title 'uex'"<<std::endl;
     f.close();
     return status;
}
