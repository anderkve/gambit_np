//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Fronted header for the CaptnGeneral backend
///
///  Compile-time registration of available
///  functions and variables from this backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///  Aaron the Vincent
///  \date 2017 Sep
///  *********************************************

#define BACKENDNAME CaptnGeneral
#define VERSION 1.0
#define SAFE_VERSION 1_0

// Load the library
LOAD_LIBRARY

BE_ALLOW_MODELS(Halo_Einasto_rho0,Halo_gNFW_rho0)
// Variables
//BE_VARIABLE(solarmodel,std::string,"solarmodel","solarmodel");
//solarmodel = backendDir+"solarmodels/model_gs98_nohead.dat";

// Functions
BE_FUNCTION(captn_init,void,(const char&,const double&,const double&,const double&,const double&),"captn_init_","captn_init")
BE_FUNCTION(captn_general, void, (const double&,const double&,int&,int&,int&,double&), "captn_general_", "cap_Sun_vnqn_isoscalar")
BE_FUNCTION(captn_specific, void, (const double&,const double&,const double&,double&,double&), "captn_specific_", "cap_Sun_v0q0_isoscalar")
BE_FUNCTION(captn_maxcap, void, (const double&), "captn_maxcap_", "cap_sun_saturation")
// Still should add: DM fraction (rho_0);

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
