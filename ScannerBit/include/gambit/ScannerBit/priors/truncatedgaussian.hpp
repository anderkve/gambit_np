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

#ifndef PRIOR_TruncatedGaussian_HPP
#define PRIOR_TruncatedGaussian_HPP

#include "gambit/ScannerBit/priors.hpp"
#include "gambit/Utils/yaml_options.hpp"

#include <vector>

namespace Gambit
{
   namespace Priors
   {
      /// 1D truncated normal distribution
      /// Follows e.g. from https://en.wikipedia.org/wiki/Truncated_normal_distribution#Generating_values_from_the_truncated_normal_distribution
      /// but with some simplifications to save computation time
      /// Takes the arguments: mu, sigma, lower_cut, upper_cut
      /// Defaults to lower_cut = -infty, upper_cut = infty [no truncation]
      class TruncatedGaussian : public BasePrior
      {
      private:
         /// Name of the parameter that this prior is supposed to transform
         const std::string &myparameter;
         /// Variables controlling the prior range etc.
         /// @{
         double mu;
         double sigma;
         double lower_cut;
         double upper_cut;
         /// @}
         /// Useful quantities
         /// @{
         double a;
         double b;
         /// @}


         /// Try to get options for double log-flat joined prior
         double get_option(const str&, const Options&);

      public:
         /// Constructor defined in TruncatedGaussian.cpp
         TruncatedGaussian(const std::vector<std::string>& param, const Options&);

         /// Transformation from unit interval truncated normal (inverse prior transform)
         void transform(const std::vector <double> &unitpars, std::unordered_map <std::string, double> &output) const;

         // /// Probability density function
         // double operator()(const std::vector<double> &vec) const;
      };

      LOAD_PRIOR(truncated_gaussian, TruncatedGaussian)
   }
}

#endif
