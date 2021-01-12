//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  GAMBIT models for nuclear physics
///  gamma-ray strength functions
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


#ifndef __gsfmodels_hpp__
#define __gsfmodels_hpp__

#define MODEL GSFModel20
  START_MODEL
  DEFINEPARS(gsf_p1,gsf_p2,gsf_p3,gsf_p4,gsf_p5,gsf_p6,gsf_p7,gsf_p8,gsf_p9,gsf_p10,gsf_p11,gsf_p12,gsf_p13,gsf_p14,gsf_p15,gsf_p16,gsf_p17,gsf_p18,gsf_p19,gsf_T)
#undef MODEL

#define MODEL GSF_GLO_CT_Model20
  START_MODEL
  DEFINEPARS(gsf_p1,gsf_p2,gsf_p3,gsf_p4,gsf_p5,gsf_p6,gsf_p7,gsf_p8,gsf_p9,gsf_p10,gsf_p11,gsf_p12,gsf_p13,gsf_p14,gsf_p15,gsf_p16,gsf_p17,gsf_p18,gsf_p19,gsf_T)
#undef MODEL

#define MODEL GSF_EGLO_CT_Model20
  START_MODEL
  DEFINEPARS(gsf_p1,gsf_p2,gsf_p3,gsf_p4,gsf_p5,gsf_p6,gsf_p7,gsf_p8,gsf_p9,gsf_p10,gsf_p11,gsf_p12,gsf_p13,gsf_p14,gsf_p15,gsf_p16,gsf_p17,gsf_p18,gsf_p19,gsf_T,gsf_epsilon_0,gsf_k)
#undef MODEL

#define MODEL GSF_MGLO_CT_Model20
  START_MODEL
  DEFINEPARS(gsf_p1,gsf_p2,gsf_p3,gsf_p4,gsf_p5,gsf_p6,gsf_p7,gsf_p8,gsf_p9,gsf_p10,gsf_p11,gsf_p12,gsf_p13,gsf_p14,gsf_p15,gsf_p16,gsf_p17,gsf_p18,gsf_p19,gsf_T,gsf_epsilon_0,gsf_k)
#undef MODEL

#define MODEL GSF_GH_CT_Model20
  START_MODEL
  DEFINEPARS(gsf_p1,gsf_p2,gsf_p3,gsf_p4,gsf_p5,gsf_p6,gsf_p7,gsf_p8,gsf_p9,gsf_p10,gsf_p11,gsf_p12,gsf_p13,gsf_p14,gsf_p15,gsf_p16,gsf_p17,gsf_p18,gsf_p19,gsf_T,gsf_epsilon_0,gsf_k)
#undef MODEL

#define MODEL GSF_constantM1
  START_MODEL
  DEFINEPARS(gsf_constantM1)
#undef MODEL

#endif /* defined(__gsfmodels_hpp__) */














