//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
//
//  Rollcall header for module DarkBit
//
//  Compile-time registration of available obser-
//  vables and likelihoods, as well as their
//  dependencies.
//
//  Add to this if you want to add an observable
//  or likelihood to this module.
//
//  *********************************************
//
//  Authors
//  =======
//
//  (add name and date if you modify)
//
//  Torsten Bringmann (torsten.bringmann@desy.de)
//  [cloned from TinyDarkBit]
//  2013 Jun
//
//  Christoph Weniger <c.weniger@uva.nl>
//  July 2013
//
//  *********************************************

#ifndef __DarkBit_rollcall_hpp__
#define __DarkBit_rollcall_hpp__


#define MODULE DarkBit
START_MODULE

// Init functions:
// - are required as default dependence of all module functions on the
//   capability MODULE_PointInit
// - should not have module-function dependencies
// - can have backend dependencies
// - must have return type void
// - must be created with INIT_FUNCTION as second argument in START_FUNCTION
// - do not itself depend on the initialization function

  #define CAPABILITY DarkBit_PointInit
  START_CAPABILITY
    #define FUNCTION DarkBit_PointInit_Default
      START_FUNCTION(void, INIT_FUNCTION)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY RD_spectrum
  START_CAPABILITY 
    #define FUNCTION RD_spectrum_SUSY
      START_FUNCTION(RDspectype)
      // DEPENDENCY(dssusy, int) 
      // CW: Is this some placeholder initialization?
      #define BACKEND_REQ mspctm
        START_BACKEND_REQ(DS_MSPCTM, VAR)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
      #define BACKEND_REQ widths
        START_BACKEND_REQ(DS_WIDTHS, VAR)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
      #define BACKEND_REQ intdof
        START_BACKEND_REQ(DS_INTDOF, VAR)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
      #define BACKEND_REQ pacodes
        START_BACKEND_REQ(DS_PACODES, VAR)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
    #undef FUNCTION
  #undef CAPABILITY


  #define CAPABILITY RD_thresholds_resonances
  START_CAPABILITY 
    #define FUNCTION RD_thresholds_resonances_ordered
      START_FUNCTION(RDrestype)
      DEPENDENCY(RD_spectrum, RDspectype)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY RD_eff_annrate
  START_CAPABILITY 
    #define FUNCTION RD_eff_annrate_SUSY
      START_FUNCTION(fptr_dd)
      DEPENDENCY(RD_spectrum, RDspectype)
      #define BACKEND_REQ rdmgev
        START_BACKEND_REQ(DS_RDMGEV, VAR)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY RD_oh2
  START_CAPABILITY 
    #define FUNCTION RD_oh2_general
      START_FUNCTION(double)
      DEPENDENCY(RD_thresholds_resonances, RDrestype)
      DEPENDENCY(RD_eff_annrate, fptr_dd)
      #define BACKEND_REQ dsrdset
        START_BACKEND_REQ(void)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
      #define BACKEND_REQ dsrdinit
        START_BACKEND_REQ(void)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
      #define BACKEND_REQ dsrdthlim
        START_BACKEND_REQ(void)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
      #define BACKEND_REQ dsrdtab
        START_BACKEND_REQ(void)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
     #define BACKEND_REQ dsrdeqn
       START_BACKEND_REQ(void)
       BACKEND_OPTION(DarkSUSY, 0.1)
     #undef BACKEND_REQ
     #define BACKEND_REQ dsrdwintp
       START_BACKEND_REQ(double)
       BACKEND_OPTION(DarkSUSY, 0.1)
     #undef BACKEND_REQ
      #define BACKEND_REQ rdmgev
        START_BACKEND_REQ(DS_RDMGEV, VAR)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
      #define BACKEND_REQ rdpth
        START_BACKEND_REQ(DS_RDPTH, VAR)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
      #define BACKEND_REQ rdpars
        START_BACKEND_REQ(DS_RDPARS, VAR)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
      #define BACKEND_REQ rdswitch
        START_BACKEND_REQ(DS_RDSWITCH, VAR)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
      #define BACKEND_REQ rdlun
        START_BACKEND_REQ(DS_RDLUN, VAR)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
      #define BACKEND_REQ rdpadd
        START_BACKEND_REQ(DS_RDPADD, VAR)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
      #define BACKEND_REQ rddof
        START_BACKEND_REQ(DS_RDDOF, VAR)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
      #define BACKEND_REQ dsanwx
        START_BACKEND_REQ(double)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
    #undef FUNCTION
    #define FUNCTION RD_oh2_SingletDM
      START_FUNCTION(double)
      ALLOW_MODELS(SingletDM)
      DEPENDENCY(GA_BRs, Gambit::DarkBit::BRs)
    #undef FUNCTION
  #undef CAPABILITY


  #define CAPABILITY RD_test
  START_CAPABILITY 
    #define FUNCTION RD_test_out
      START_FUNCTION(double)
      DEPENDENCY(RD_thresholds_resonances, RDrestype)
    #undef FUNCTION
  #undef CAPABILITY



  #define CAPABILITY GA_dNdE
  START_CAPABILITY
    #define FUNCTION GA_dNdE_from_BRs
      START_FUNCTION(Gambit::DarkBit::dNdE)
      ALLOW_MODELS(SingletDM)
      DEPENDENCY(GA_BRs, Gambit::DarkBit::BRs)
      #define BACKEND_REQ dshayield
        START_BACKEND_REQ(double)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
      #define BACKEND_REQ dsinit
        START_BACKEND_REQ(void)
        BACKEND_OPTION(DarkSUSY, 0.1)
      #undef BACKEND_REQ
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY GA_BRs
  START_CAPABILITY
    #define FUNCTION GA_BRs_SingletDM
      START_FUNCTION(Gambit::DarkBit::BRs)
      ALLOW_MODELS(SingletDM)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_FermiLATdwarfs
  START_CAPABILITY
    #define FUNCTION lnL_FermiLATdwarfsSimple
      START_FUNCTION(double)
      DEPENDENCY(GA_dNdE, Gambit::DarkBit::dNdE)
      DEPENDENCY(GA_BRs, Gambit::DarkBit::BRs)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_oh2
  START_CAPABILITY
    #define FUNCTION lnL_oh2_Simple
      START_FUNCTION(double)
      DEPENDENCY(RD_oh2, double)
    #undef FUNCTION
  #undef CAPABILITY

#undef MODULE

#endif /* defined(__DarkBit_rollcall_hpp__) */

