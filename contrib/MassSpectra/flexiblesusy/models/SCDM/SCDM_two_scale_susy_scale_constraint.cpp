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

// File generated at Tue 29 Dec 2015 16:23:42

#include "SCDM_two_scale_susy_scale_constraint.hpp"
#include "SCDM_two_scale_model.hpp"
#include "wrappers.hpp"
#include "logger.hpp"
#include "ew_input.hpp"
#include "gsl_utils.hpp"
#include "minimizer.hpp"
#include "root_finder.hpp"
#include "threshold_loop_functions.hpp"

#include <cassert>
#include <cmath>

namespace flexiblesusy {

#define INPUTPARAMETER(p) model->get_input().p
#define MODELPARAMETER(p) model->get_##p()
#define PHASE(p) model->get_##p()
#define BETAPARAMETER(p) beta_functions.get_##p()
#define BETA(p) beta_##p
#define LowEnergyConstant(p) Electroweak_constants::p
#define MZPole Electroweak_constants::MZ
#define STANDARDDEVIATION(p) Electroweak_constants::Error_##p
#define Pole(p) model->get_physical().p
#define SCALE model->get_scale()
#define THRESHOLD static_cast<int>(model->get_thresholds())
#define MODEL model
#define MODELCLASSNAME SCDM<Two_scale>

SCDM_susy_scale_constraint<Two_scale>::SCDM_susy_scale_constraint()
   : Constraint<Two_scale>()
   , scale(0.)
   , initial_scale_guess(0.)
   , model(0)
{
}

SCDM_susy_scale_constraint<Two_scale>::SCDM_susy_scale_constraint(
   SCDM<Two_scale>* model_)
   : Constraint<Two_scale>()
   , model(model_)
{
   initialize();
}

SCDM_susy_scale_constraint<Two_scale>::~SCDM_susy_scale_constraint()
{
}

void SCDM_susy_scale_constraint<Two_scale>::apply()
{
   assert(model && "Error: SCDM_susy_scale_constraint::apply():"
          " model pointer must not be zero");

   model->calculate_DRbar_masses();
   update_scale();

   // apply user-defined susy scale constraints
   MODEL->solve_ewsb();

}

double SCDM_susy_scale_constraint<Two_scale>::get_scale() const
{
   return scale;
}

double SCDM_susy_scale_constraint<Two_scale>::get_initial_scale_guess() const
{
   return initial_scale_guess;
}

const SCDM_input_parameters& SCDM_susy_scale_constraint<Two_scale>::get_input_parameters() const
{
   assert(model && "Error: SCDM_susy_scale_constraint::"
          "get_input_parameters(): model pointer is zero.");

   return model->get_input();
}

SCDM<Two_scale>* SCDM_susy_scale_constraint<Two_scale>::get_model() const
{
   return model;
}

void SCDM_susy_scale_constraint<Two_scale>::set_model(Two_scale_model* model_)
{
   model = cast_model<SCDM<Two_scale>*>(model_);
}

void SCDM_susy_scale_constraint<Two_scale>::clear()
{
   scale = 0.;
   initial_scale_guess = 0.;
   model = NULL;
}

void SCDM_susy_scale_constraint<Two_scale>::initialize()
{
   assert(model && "SCDM_susy_scale_constraint<Two_scale>::"
          "initialize(): model pointer is zero.");

   const auto QEWSB = INPUTPARAMETER(QEWSB);

   initial_scale_guess = QEWSB;

   scale = initial_scale_guess;
}

void SCDM_susy_scale_constraint<Two_scale>::update_scale()
{
   assert(model && "SCDM_susy_scale_constraint<Two_scale>::"
          "update_scale(): model pointer is zero.");

   const auto QEWSB = INPUTPARAMETER(QEWSB);

   scale = QEWSB;


}

} // namespace flexiblesusy