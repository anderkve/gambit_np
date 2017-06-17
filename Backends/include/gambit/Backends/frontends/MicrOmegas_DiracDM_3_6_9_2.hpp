//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for MicrOmegas DiracDM backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Ankit Beniwal
/// \date Oct 2016, Jun 2017
///
///  *********************************************

#define BACKENDNAME MicrOmegas_DiracDM
#define VERSION 3.6.9.2
#define SAFE_VERSION 3_6_9_2

LOAD_LIBRARY

BE_FUNCTION(assignVal, int, (char*,double),"assignVal","assignVal", (DiracDM))
BE_FUNCTION(vSigma, double, (double, double, int), "vSigma","vSigma", (DiracDM))
BE_FUNCTION(darkOmega, double, (double*, int, double), "darkOmega", "oh2", (DiracDM))
BE_FUNCTION(sortOddParticles, int, (char*), "sortOddParticles","mass_spectrum", (DiracDM))
BE_FUNCTION(cleanDecayTable, void, (), "cleanDecayTable", "cleanDecayTable", (DiracDM))
BE_FUNCTION(calcSpectrum, double, (int, double*, double*, double*, double*, double*, double*, int*), "calcSpectrum", "calcSpectrum", (DiracDM))
BE_FUNCTION(nucleonAmplitudes, int, (double(*)(double,double,double,double), double*, double*, double*, double*), "nucleonAmplitudes", "nucleonAmplitudes", (DiracDM))
BE_FUNCTION(FeScLoop, double, (double, double, double, double), "FeScLoop", "FeScLoop", (DiracDM))
BE_FUNCTION(calcScalarQuarkFF, void, (double, double, double, double), "calcScalarQuarkFF", "calcScalarQuarkFF", (DiracDM))

BE_FUNCTION(mInterp, int, (double,int,int,double*) , "mInterp", "mInterp")
BE_FUNCTION(zInterp, double, (double,double*) , "zInterp", "zInterp")
BE_FUNCTION(readSpectra, int, (), "readSpectra", "readSpectra")

BE_VARIABLE(mocommon_, MicrOmegas::MOcommonSTR, "mocommon_", "MOcommon", (DiracDM))
BE_VARIABLE(vSigmaCh, MicrOmegas::aChannel*, "vSigmaCh", "vSigmaCh", (DiracDM))
BE_VARIABLE(ForceUG, int, "ForceUG", "ForceUG", (DiracDM))
BE_VARIABLE(VZdecay, int, "VZdecay", "VZdecay", (DiracDM))
BE_VARIABLE(VWdecay, int, "VWdecay", "VWdecay", (DiracDM))

BE_CONV_FUNCTION(dNdE, double, (double,double,int,int), "dNdE")

BE_INI_DEPENDENCY(DiracDM_spectrum, Spectrum)
BE_INI_DEPENDENCY(decay_rates, DecayTable)

#include "gambit/Backends/backend_undefs.hpp"

