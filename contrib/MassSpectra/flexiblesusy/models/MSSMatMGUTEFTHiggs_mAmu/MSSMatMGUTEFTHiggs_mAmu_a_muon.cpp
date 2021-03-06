// ====================================================================
// This file is part of FlexibleSUSY.
//
// FlexibleSUSY is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// FlexibleSUSY is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FlexibleSUSY.  If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

// File generated at Thu 10 May 2018 14:34:58

/**
 * @file MSSMatMGUTEFTHiggs_mAmu_a_muon.cpp
 *
 * This file was generated at Thu 10 May 2018 14:34:58 with FlexibleSUSY
 * 2.0.1 and SARAH 4.12.2 .
 */

#include "MSSMatMGUTEFTHiggs_mAmu_a_muon.hpp"
#include "MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates.hpp"

#include "MSSMatMGUTEFTHiggs_mAmu_cxx_diagrams.hpp"

#define INPUTPARAMETER(p) context.model.get_input().p
#define MODELPARAMETER(p) context.model.get_##p()
#define DERIVEDPARAMETER(p) context.model.p()
#define PHASE(p) context.model.get_##p()

using namespace flexiblesusy;
using namespace cxx_diagrams;

using Muon = Fe;

namespace {
static constexpr double oneOver16PiSquared = 0.0063325739776461107152;

double OneLoopFunctionF1C(double);
double OneLoopFunctionF2C(double);
double OneLoopFunctionF1N(double);
double OneLoopFunctionF2N(double);

double get_QED_2L(EvaluationContext&);

/**
 * @class AMuonVertexCorrectionSF
 * @brief A template that calculate contributions to the
 *        anomalous dipole moment of a given particle in
 *        a one loop diagram specified by a photon emitter
 *        and an exchange particle.
 * @tparam Args Specifies in order the field of which to
 *              calculate the electric dipole moment,
 *              the photon emitter and the exchange particle
 *              in a one-loop diagram where the photon emitter
 *              is a scalar and the exchange particle a fermion.
 *
 * This template evaluates the contribution to the electric
 * dipole moment of a one loop diagram with fields given by
 * \a Args.
 */
template<class PhotonEmitter, class ExchangeParticle>
struct AMuonVertexCorrectionSF {
   static double value(const typename field_indices<Muon>::type& indices,
                       const EvaluationContext& context);
};

/**
 * @class AMuonVertexCorrectionFS
 * @brief A template that calculate contributions to the
 *        anomalous dipole moment of a given particle in
 *        a one loop diagram specified by a photon emitter
 *        and an exchange particle.
 * @tparam Args Specifies in order the field of which to
 *              calculate the electric dipole moment,
 *              the photon emitter and the exchange particle
 *              in a one-loop diagram where the photon emitter
 *              is a fermion and the exchange particle a scalar.
 *
 * This template evaluates the contribution to the electric
 * dipole moment of a one loop diagram with fields given by
 * \a Args.
 */
template<class PhotonEmitter, class ExchangeParticle>
struct AMuonVertexCorrectionFS {
   static double value(const typename field_indices<Muon>::type& indices,
                       const EvaluationContext& context);
};

/**
* @defgroup LoopFunctions Loop functions
* @brief The loop functions necessary for \f$a_\mu\f$ one-loop calculations.
*
* These are OneLoopFunctionF1C(), OneLoopFunctionF2C(),
* OneLoopFunctionF1N() and OneLoopFunctionF2N()
* as specified in arXiv:1311.1775
*/

double OneLoopFunctionF1C(double x)
{
   if (is_zero(x))
      return 4.0;

   // error around x=1 is <= 10^-12 on an intel i7
   const double y = x - 1.0;

   if (std::abs(y) < 0.21) {
      return (1.0000000000000000000 -
              0.60000000000000000000  * y +
              0.40000000000000000000  * y * y -
              0.28571428571428571429  * y * y * y +
              0.21428571428571428571  * y * y * y * y -
              0.16666666666666666667  * y * y * y * y * y +
              0.13333333333333333333  * y * y * y * y * y * y -
              0.10909090909090909091  * y * y * y * y * y * y * y +
              0.090909090909090909091 * y * y * y * y * y * y * y * y -
              0.076923076923076923077 * y * y * y * y * y * y * y * y * y +
              0.065934065934065934066 * y * y * y * y * y * y * y * y * y * y -
              0.057142857142857142857 * y * y * y * y * y * y * y * y * y * y * y +
              0.050000000000000000000 * y * y * y * y * y * y * y * y * y * y * y * y -
              0.044117647058823529412 * y * y * y * y * y * y * y * y * y * y * y * y * y +
              0.039215686274509803922 * y * y * y * y * y * y * y * y * y * y * y * y * y * y -
              0.035087719298245614035 * y * y * y * y * y * y * y * y * y * y * y * y * y * y * y);
   }

   return 2.0 / (y * y * y * y) * (2.0 + 3.0 * x - 6.0 * x * x + x * x * x + 6.0 * x * std::log(x));
}

double OneLoopFunctionF2C(double x)
{
   // error around x=1 is <= 10^-13 on an intel i7
   const double y = x - 1.0;

   if (std::abs(y) < 0.155)
      return (1.0 - 0.75 * y + 0.6 * y * y -
              0.50000000000000000000 * y * y * y +
              0.4285714285714285714  * y * y * y * y -
              0.37500000000000000000 * y * y * y * y * y +
              0.33333333333333333333 * y * y * y * y * y * y -
              0.3000000000000000000  * y * y * y * y * y * y * y +
              0.2727272727272727273  * y * y * y * y * y * y * y * y -
              0.2500000000000000000  * y * y * y * y * y * y * y * y * y +
              0.23076923076923076923 * y * y * y * y * y * y * y * y * y * y -
              0.21428571428571428571 * y * y * y * y * y * y * y * y * y * y * y +
              0.2000000000000000000  * y * y * y * y * y * y * y * y * y * y * y * y -
              0.1875000000000000000  * y * y * y * y * y * y * y * y * y * y * y * y * y +
              0.1764705882352941176  * y * y * y * y * y * y * y * y * y * y * y * y * y * y -
              0.16666666666666666667 * y * y * y * y * y * y * y * y * y * y * y * y * y * y * y);

   return -3.0 / (2.0 * y * y * y) * (-3.0 + 4.0 * x - x * x - 2.0 * std::log(x));
}

double OneLoopFunctionF1N(double x)
{
   if (is_zero(x))
      return 2.0;

   // error around x=1 is <= 10^-12 on an intel i7
   const double y = x - 1.0;

   if (std::abs(y) < 0.23)
      return (1.0000000000000000000 -
              0.4000000000000000000  * y +
              0.2000000000000000000  * y * y -
              0.11428571428571428571 * y * y * y +
              0.07142857142857142857 * y * y * y * y -
              0.04761904761904761905 * y * y * y * y * y +
              0.03333333333333333333 * y * y * y * y * y * y -
              0.02424242424242424242 * y * y * y * y * y * y * y +
              0.0181818181818181818  * y * y * y * y * y * y * y * y -
              0.01398601398601398601 * y * y * y * y * y * y * y * y * y +
              0.01098901098901098901 * y * y * y * y * y * y * y * y * y * y -
              0.0087912087912087912  * y * y * y * y * y * y * y * y * y * y * y +
              0.00714285714285714286 * y * y * y * y * y * y * y * y * y * y * y * y -
              0.0058823529411764706  * y * y * y * y * y * y * y * y * y * y * y * y * y +
              0.0049019607843137255  * y * y * y * y * y * y * y * y * y * y * y * y * y * y -
              0.0041279669762641899  * y * y * y * y * y * y * y * y * y * y * y * y * y * y * y);

   return 2.0 / (y * y * y * y) * (1.0 - 6.0 * x + 3.0 * x * x + 2.0 * x * x * x - 6.0 * x * x * std::log(x));
}

double OneLoopFunctionF2N(double x)
{
   if (is_zero(x))
      return 3.0;

   // error around x=1 is <= 10^-13 on an intel i7
   const double y = x - 1.0;

   if (std::abs(y) < 0.185)
      return (1.0000000000000000000 -
              0.50000000000000000000 * y +
              0.30000000000000000000 * y * y -
              0.2000000000000000000  * y * y * y +
              0.14285714285714285714 * y * y * y * y -
              0.10714285714285714286 * y * y * y * y * y +
              0.08333333333333333333 * y * y * y * y * y * y -
              0.06666666666666666667 * y * y * y * y * y * y * y +
              0.05454545454545454545 * y * y * y * y * y * y * y * y -
              0.0454545454545454545  * y * y * y * y * y * y * y * y * y +
              0.0384615384615384615  * y * y * y * y * y * y * y * y * y * y -
              0.03296703296703296703 * y * y * y * y * y * y * y * y * y * y * y +
              0.0285714285714285714  * y * y * y * y * y * y * y * y * y * y * y * y -
              0.02500000000000000000 * y * y * y * y * y * y * y * y * y * y * y * y * y +
              0.0220588235294117647  * y * y * y * y * y * y * y * y * y * y * y * y * y * y -
              0.0196078431372549020  * y * y * y * y * y * y * y * y * y * y * y * y * y * y * y);

   return -3.0 / (y * y * y) * (1.0 - x * x + 2.0 * x * std::log(x));
}

double get_MSUSY(const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model)
{
   return Min(model.get_MSd().tail<6>().minCoeff(), model.get_MSu().tail<6>()
      .minCoeff(), model.get_MSe().tail<6>().minCoeff(), model.get_MHpm().tail<1>(
      ).minCoeff(), model.get_MCha().tail<2>().minCoeff());

}

void run_to_MSUSY(MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model)
{
   const double precision_goal = model.get_precision();
   const int Nmax = static_cast<int>(-log10(precision_goal) * 10);
   int it = 0;
   double precision = 0.;
   double MSUSY_old = 0., MSUSY_new = 0.;

   VERBOSE_MSG("MSSMatMGUTEFTHiggs_mAmu_a_muon: iterate to run to MSUSY ...");

   do {
      MSUSY_new = get_MSUSY(model);

      if (MSUSY_new <= 0.)
         return;

      VERBOSE_MSG("MSSMatMGUTEFTHiggs_mAmu_a_muon:    running to new MSUSY = " << MSUSY_new);

      model.run_to(MSUSY_new);
      model.calculate_DRbar_masses();

      precision = MaxRelDiff(MSUSY_old, MSUSY_new);
      MSUSY_old = MSUSY_new;
   } while (precision > precision_goal && ++it < Nmax);

   VERBOSE_MSG("MSSMatMGUTEFTHiggs_mAmu_a_muon: iteration finished. MSUSY = " << MSUSY_new);

   if (precision > precision_goal) {
      WARNING("MSSMatMGUTEFTHiggs_mAmu_a_muon: run_to_MSUSY(): "
              "Iteration did not converge after " << Nmax
              << " iterations (precision goal: " << precision_goal << ")");
   }
}

double calculate_a_muon_impl(MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model)
{
   VERBOSE_MSG("MSSMatMGUTEFTHiggs_mAmu_a_muon: calculating a_mu at Q = " << model.get_scale());

   EvaluationContext context{ model };
   double val = 0.0;

   std::array<int, 1> indices = { 1 };

   val += AMuonVertexCorrectionFS<Fe, Ah>::value(indices, context);
   val += AMuonVertexCorrectionSF<Se, Chi>::value(indices, context);
   val += AMuonVertexCorrectionSF<Hpm, Fv>::value(indices, context);
   val += AMuonVertexCorrectionFS<Fe, hh>::value(indices, context);
   val += AMuonVertexCorrectionFS<Cha, Sv>::value(indices, context);

   // add 2-loop QED logarithms
   val *= 1. + get_QED_2L(context);

   return val;
}

/// generates array with N scales from mean/factor to mean*factor
template <int N>
std::array<double,N> generate_scales(double mean, double factor)
{
   static_assert(N > 1, "N must be greater than 1!");

   const double start = mean / factor, stop = mean * factor;
   std::array<double,N> scales;

   scales[0] = start;

   for (int i = 1; i < (N-1); i++)
      scales[i] = std::exp(std::log(start) + (std::log(stop) - std::log(start))*i / N);

   scales[N-1] = stop;

   return scales;
}

/// returns minimum and maximum a_mu when scale is varied by a factor 2
std::pair<double,double> vary_scale(const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model)
{
   auto scales = generate_scales<7>(model.get_scale(), 2.);

   std::transform(scales.begin(), scales.end(), scales.begin(),
                  [&model] (double scale) {
                     double amu = 0.;
                     try {
                        auto m = model;
                        m.run_to(scale);
                        m.get_physical().clear();
                        m.calculate_DRbar_masses();
                        m.solve_ewsb();
                        m.calculate_MFe_pole();
                        amu = calculate_a_muon_impl(m);
                     }
                     catch(const Error& e) {
                        ERROR("MSSMatMGUTEFTHiggs_mAmu_a_muon: scale variation: " << e.what());
                     }
                     return amu;
                  });

   const auto minmax = std::minmax_element(scales.cbegin(), scales.cend());

   return std::make_pair(*(minmax.first), *(minmax.second));
}

double muonPhysicalMass(const EvaluationContext& context)
{
   return context.model.get_physical().MFe( 1 );
}

} // anonymous namespace

double MSSMatMGUTEFTHiggs_mAmu_a_muon::calculate_a_muon(const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_)
{
   MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates model(model_);

   VERBOSE_MSG("MSSMatMGUTEFTHiggs_mAmu_a_muon: starting calculation of a_mu ...");

   try {
      run_to_MSUSY(model);
      model.get_physical().clear();
   } catch (const Error& e) {
      ERROR("MSSMatMGUTEFTHiggs_mAmu_a_muon:" << e.what());
      return std::numeric_limits<double>::quiet_NaN();
   }

   double m_muon_pole = muonPhysicalMass(EvaluationContext{model});

   if (m_muon_pole == 0.0) {
      model.solve_ewsb();
      model.calculate_MFe_pole();
   }

   return calculate_a_muon_impl(model);
}

double MSSMatMGUTEFTHiggs_mAmu_a_muon::calculate_a_muon_uncertainty(const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_)
{
   MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates model(model_);

   VERBOSE_MSG("MSSMatMGUTEFTHiggs_mAmu_a_muon: starting calculation of a_mu uncertainty ...");

   try {
      run_to_MSUSY(model);
      model.get_physical().clear();
   } catch (const Error& e) {
      ERROR("MSSMatMGUTEFTHiggs_mAmu_a_muon uncertainty: " << e.what());
      return std::numeric_limits<double>::quiet_NaN();
   }

   const auto delta_amu_scale_minmax = vary_scale(model);
   const auto delta_amu_scale = std::abs(delta_amu_scale_minmax.second - delta_amu_scale_minmax.first);

   return delta_amu_scale;
}

namespace {
double get_QED_2L(EvaluationContext& context)
{
   const double MSUSY = Abs(get_MSUSY(context.model));
   const double m_muon = muonPhysicalMass(context);
   const double alpha_em = Sqr(Muon::electric_charge * unit_charge(context))/(4*Pi);
   const double qed_2L = alpha_em/(4*Pi) * 16 * FiniteLog(m_muon/MSUSY);

   return qed_2L;
}

template<class PhotonEmitter, class ExchangeField>
double AMuonVertexCorrectionFS<
PhotonEmitter, ExchangeField
>::value(const typename field_indices<Muon>::type& indices, const EvaluationContext& context)
{
   double res = 0.0;

   using MuonVertex = Vertex<
                      typename Muon::lorentz_conjugate,
                      ExchangeField,
                      PhotonEmitter
                      >;

   constexpr auto indexBounds = MuonVertex::index_bounds;

   for (const auto& index: indexBounds) {
      const auto muonIndices = MuonVertex::template fieldIndices<0>(index);

      if (muonIndices != indices)
         continue;

      const auto photonEmitterIndices = MuonVertex::template fieldIndices<2>(index);
      const auto exchangeFieldIndices = MuonVertex::template fieldIndices<1>(index);

      if (isSMField<PhotonEmitter>(photonEmitterIndices) &&
          isSMField<ExchangeField>(exchangeFieldIndices))
         continue;

      auto muonVertex = MuonVertex::evaluate(index, context);

      const auto photonEmitterMass = context.mass<PhotonEmitter>(photonEmitterIndices);
      const auto exchangeFieldMass = context.mass<ExchangeField>(exchangeFieldIndices);
      const auto muonMass = context.mass<Muon>(muonIndices);

      const double photonEmitterChargeCount =
         PhotonEmitter::electric_charge / Muon::electric_charge;

      const std::complex<double> zL = muonVertex.left();
      const std::complex<double> zR = muonVertex.right();

      const double coeffA = std::norm(zL) + std::norm(zR);
      const double coeffB = (zL * std::conj(zR) + zR * std::conj(zL)).real();

      const double massRatioSquared = Sqr(photonEmitterMass / exchangeFieldMass);

      const double part1 = muonMass / 12.0 * coeffA * OneLoopFunctionF1C(massRatioSquared);

      const double part2 =
         is_zero(massRatioSquared) ? 0. :
         photonEmitterMass / 3.0 * coeffB * OneLoopFunctionF2C(massRatioSquared);

      const double preFactor = oneOver16PiSqr * photonEmitterChargeCount
         * muonPhysicalMass(context) / (exchangeFieldMass * exchangeFieldMass);

      res += preFactor * (part1 + part2);
   }

   return res;
}

template<class PhotonEmitter, class ExchangeField>
double AMuonVertexCorrectionSF<
PhotonEmitter, ExchangeField
>::value(const typename field_indices<Muon>::type& indices, const EvaluationContext& context)
{
   double res = 0.0;

   using MuonVertex = Vertex<
                      typename Muon::lorentz_conjugate,
                      ExchangeField,
                      PhotonEmitter
                      >;

   constexpr auto indexBounds = MuonVertex::index_bounds;

   for (const auto& index: indexBounds) {
      const auto muonIndices = MuonVertex::template fieldIndices<0>(index);

      if (muonIndices != indices)
         continue;

      const auto photonEmitterIndices = MuonVertex::template fieldIndices<2>(index);
      const auto exchangeFieldIndices = MuonVertex::template fieldIndices<1>(index);

      if (isSMField<PhotonEmitter>(photonEmitterIndices) &&
          isSMField<ExchangeField>(exchangeFieldIndices))
         continue;

      const auto muonVertex = MuonVertex::evaluate(index, context);

      const auto photonEmitterMass = context.mass<PhotonEmitter>(photonEmitterIndices);
      const auto exchangeFieldMass = context.mass<ExchangeField>(exchangeFieldIndices);
      const auto muonMass = context.mass<Muon>(muonIndices);

      const double photonEmitterChargeCount =
         PhotonEmitter::electric_charge / Muon::electric_charge;

      const std::complex<double> zL = muonVertex.left();
      const std::complex<double> zR = muonVertex.right();

      const double coeffA = std::norm(zL) + std::norm(zR);
      const double coeffB = (zL * std::conj(zR) + zR * std::conj(zL)).real();

      const double massRatioSquared = Sqr(exchangeFieldMass / photonEmitterMass);

      const double part1 = 1.0 / 12.0 * coeffA * OneLoopFunctionF1N(massRatioSquared);
      const double part2 = exchangeFieldMass / (6.0 * muonMass) * coeffB * OneLoopFunctionF2N(massRatioSquared);

      const double preFactor = - oneOver16PiSqr * photonEmitterChargeCount
         * muonPhysicalMass(context) * muonMass / (photonEmitterMass * photonEmitterMass);

      res += preFactor * (part1 + part2);
   }

   return res;
}

} // anonymous namespace
