//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  GAMBIT models for nuclear level density
///  functions
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          anders.kvellestad@fys.uio.no
///  \date 2020 Mar
///
///  *********************************************


#ifndef __nldmodels_hpp__
#define __nldmodels_hpp__

#define MODEL NLDModelCT_and_discretes
  START_MODEL
  DEFINEPARS(nld_T, nld_Eshift, nld_Ecrit)
#undef MODEL

#define MODEL NLDModelBSFG_and_discretes
  START_MODEL
  DEFINEPARS(nld_NLDa, nld_Eshift, nld_Ecrit)
#undef MODEL

#endif /* defined(__nldmodels_hpp__) */














