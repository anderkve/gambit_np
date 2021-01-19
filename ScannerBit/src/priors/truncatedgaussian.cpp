//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Prior function made up of two log priors
///  (positive and negative branch) joined across
///  zero by a flat region.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Fabio Zeiser
///          (fabio.zeiser@fys.uio.no)
///  \date 2021 Jan
///
///  *********************************************

#include "gambit/ScannerBit/priors/truncatedgaussian.hpp"

#include <cmath>
#include <boost/math/special_functions/erf.hpp>

namespace Gambit
{
   namespace Priors
   {

      /// Constructor
      TruncatedGaussian::TruncatedGaussian(const std::vector<std::string>& param, const Options& options)
        : BasePrior(param, 1)
        , myparameter(param_names[0])
        , mu(0.0)
        , sigma(1.0)
        , lower_cut(-INFINITY)
        , upper_cut(INFINITY)
      {
         // Only valid for 1D parameter transformation
         if (param.size()!=1)
         {
             scan_err << "Invalid input to TruncatedGaussian prior (in constructor): " << endl
                      << "Input parameters must be a vector of size 1! (has size=" << param.size() << ")" << scan_end;
         }

         // Read the entries we need from the options
         mu = get_option("mu", options);
         sigma = get_option("sigma", options);

         if (options.hasKey("lower_cut"))
         {
            lower_cut=options.getValue<double>("lower_cut");
         }

         if (options.hasKey("upper_cut"))
         {
            upper_cut=options.getValue<double>("upper_cut");
         }


         // Make sure ordering of constraints makes sense
         if(lower_cut > upper_cut)
         {
             scan_err << "Inconsistent values of options for TruncatedGaussian prior detected! " << endl
                      << "The required ordering is: lower_cut < upper_cut."<< endl
                      << "Values received were: lower_cut: "<<lower_cut<<
                         ", upper_cut: "<<upper_cut << "." << endl << scan_end;
         }

         // Useful quantities:
         // calculate at initialization to save computation time
         double alpha = (lower_cut - mu) / sigma;
         double beta = (upper_cut - mu) / sigma;
         a = 0.5*(1 + erf(alpha/M_SQRT2)); // cdf(lower_cut)
         b = 0.5*(1 + erf(beta/M_SQRT2)); // cdf(upper_cut)
      }


      /// Try to get options for Truncated Gaussian
      double TruncatedGaussian::get_option(const str& name, const Options& options)
      {
       if (options.hasKey(name))
       {
         return options.getValue<double>(name);
       }
       else
       {
         scan_err << "Missing option " << name <<" for TruncatedGaussian prior. Must specify " << endl
                  << "'mu', 'sigma'." << scan_end;
       }
       return 0;
      }


      /// Transformation from unit interval to Truncated Gaussian
      void TruncatedGaussian::transform(const std::vector <double> &unitpars, std::unordered_map <std::string, double> &output) const
      {
         // Only valid for 1D parameter transformation
         if (unitpars.size()!=1)
         {
             scan_err << "Invalid input to TruncatedGaussian prior (in 'transform'): Input parameters must be a vector of size 1! (has size=" << unitpars.size() << ")" << scan_end;
         }

         double r = unitpars[0]; // input unit cube parameter

         // Transformation:
         double x = M_SQRT2*boost::math::erf_inv(2*(r*(b-a) + a) - 1); // output (result)
         x = x * sigma + mu;

         output[myparameter] = x;
      }

      // double TruncatedGaussian::operator()(const std::vector<double> &vec) const
      // {
      //    double r = 0;
      //    double x = vec[0];
      //    double x0 = lower_cut;
      //    double x1 = mu;
      //    double x2 = sigma;
      //    double x3 = upper_cut;
      //    if( x <= x0 ) {
      //      r = 0.;
      //    }
      //    else if( (x > x0) and (x <= x1) ) {
      //      r =  1./x * x1 * C;
      //    }
      //    else if( (x > x1) and (x <= x2) ) {
      //      r =  C;
      //    }
      //    else if( (x > x2) and (x <= x3) ) {
      //      r =  1./x * x2 * C;
      //    }
      //    else if (x > x3) {
      //      r = 0;
      //    }
      //    else {
      //        scan_err << "Problem computing prior density for TruncatedGaussian (received x="<<x<<")!" << scan_end;
      //    }

      //    return r;
      // }

   }
}
