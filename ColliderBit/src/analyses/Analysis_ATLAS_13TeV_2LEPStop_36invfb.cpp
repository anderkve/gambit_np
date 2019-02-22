#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

using namespace std;

/* The ATLAS 2 lepton direct stop analysis (36.1fb^-1) - `heavy stop'.

   Based on: arXiv:1708.03247
   Author: Yang Zhang

   Known errors:
        1. Jet overlap removal with muon is not done becasue miss trac imformation
        2. Applied specific efficiencies on muon for validation

*/

namespace Gambit {
  namespace ColliderBit {


    bool sortByPT_j(HEPUtils::Jet* jet1, HEPUtils::Jet* jet2) { return (jet1->pT() > jet2->pT()); }
    bool sortByPT_l(HEPUtils::Particle* lep1, HEPUtils::Particle* lep2) { return (lep1->pT() > lep2->pT()); }

    class Analysis_ATLAS_13TeV_2LEPStop_36invfb : public Analysis {
    private:

        // Numbers passing cuts
        int _SRASF120, _SRADF120, _SRASF140, _SRADF140, _SRASF160, _SRADF160, _SRASF180, _SRADF180;
        int _SRBSF120, _SRBDF120, _SRBSF140, _SRBDF140;
        int _SRCSF110, _SRCDF110;
        //int _SR3BodyTSF, _SR3BodyTDF, _SR3BodyWSF, _SR3BodyWDF;
        int _SR4b;

        // Cut Flow
        vector<int> cutFlowVector;
        vector<string> cutFlowVector_str;
        int NCUTS;

        // // debug
        // ofstream Savelep1;
        // ofstream Savelep2;

        // Jet overlap removal
        void JetLeptonOverlapRemoval(vector<HEPUtils::Jet*> &jetvec, vector<HEPUtils::Particle*> &lepvec, double DeltaRMax) {
            //Routine to do jet-lepton check
            //Discards jets if they are within DeltaRMax of a lepton

            vector<HEPUtils::Jet*> Survivors;

            for(unsigned int itjet = 0; itjet < jetvec.size(); itjet++) {
                bool overlap = false;
                HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
                for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
                    HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
                    double dR;

                    dR=jetmom.deltaR_eta(lepmom);

                    if(fabs(dR) <= DeltaRMax) overlap=true;
                }
                if(overlap) continue;
                Survivors.push_back(jetvec.at(itjet));
            }
            jetvec=Survivors;

            return;
        }

        // Lepton overlap removal
        void LeptonJetOverlapRemoval(vector<HEPUtils::Particle*> &lepvec, vector<HEPUtils::Jet*> &jetvec, double DeltaRMax) {
            //Routine to do lepton-jet check
            //Discards leptons if they are within DeltaRMax of a jet

            vector<HEPUtils::Particle*> Survivors;

            for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
                bool overlap = false;
                HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
                for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++) {
                    HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
                    double dR;

                    dR=jetmom.deltaR_eta(lepmom);

                    if(fabs(dR) <= DeltaRMax) overlap=true;
                }
                if(overlap) continue;
                Survivors.push_back(lepvec.at(itlep));
            }
            lepvec=Survivors;

            return;
        }


    public:

        // Required detector sim
        static constexpr const char* detector = "ATLAS";

        Analysis_ATLAS_13TeV_2LEPStop_36invfb() {

            set_analysis_name("ATLAS_13TeV_2LEPStop_36invfb");
            set_luminosity(36.1);

            _SRASF120=0; _SRADF120=0; _SRASF140=0; _SRADF140=0;
            _SRASF160=0; _SRADF160=0; _SRASF180=0; _SRADF180=0;
            _SRBSF120=0; _SRBDF120=0; _SRBSF140=0; _SRBDF140=0;
            _SRCSF110=0; _SRCDF110=0;
            //_SR3BodyTSF=0; _SR3BodyTDF=0; _SR3BodyWSF=0; _SR3BodyWDF=0;
            _SR4b=0;

            NCUTS= 66;

            // //debug
            // Savelep1.open("lep1.txt");
            // Savelep2.open("lep2.txt");

            for(int i=0;i<NCUTS;i++){
                cutFlowVector.push_back(0);
                cutFlowVector_str.push_back("");
            }

        }

        void analyze(const HEPUtils::Event* event) {
            Analysis::analyze(event);

            // Missing energy
            double met = event->met();
            HEPUtils::P4 ptot = event->missingmom();

            // Baseline lepton objects
            vector<HEPUtils::Particle*> blElectrons, blMuons;              // Used for SR-2body and SR-3body
            vector<HEPUtils::Particle*> baselineElectrons, baselineMuons;  // Used for SR-4body
            for (HEPUtils::Particle* electron : event->electrons()) {
            // Same with the code snippet, not the experimental report
                if (electron->pT() > 10. && electron->abseta() < 2.47) blElectrons.push_back(electron);
                if (electron->pT() > 7. && electron->abseta() < 2.47) baselineElectrons.push_back(electron);
            }

            // Apply electron efficiency
            ATLAS::applyElectronEff(blElectrons);
            ATLAS::applyElectronEff(baselineElectrons);

            // Apply loose electron selection
            ATLAS::applyLooseIDElectronSelectionR2(blElectrons);
            ATLAS::applyLooseIDElectronSelectionR2(baselineElectrons);

            const std::vector<double>  a = {0,10.};
            const std::vector<double>  b = {0,10000.};
            const vector<double> cMu={0.89};
            HEPUtils::BinnedFn2D<double> _eff2dMu(a,b,cMu);
            for (HEPUtils::Particle* muon : event->muons()) {
                bool hasTrig=has_tag(_eff2dMu, muon->eta(), muon->pT());
            // Same with the code snippet, not the experimental report
                if (muon->pT() > 10. && muon->abseta() < 2.5 && hasTrig) blMuons.push_back(muon);
                if (muon->pT() > 7. && muon->abseta() < 2.5 && hasTrig) baselineMuons.push_back(muon);
            }

            // Apply muon efficiency
            ATLAS::applyMuonEff(blMuons);
            ATLAS::applyMuonEff(baselineMuons);

            // Jets
            vector<HEPUtils::Jet*> blJets;          // Used for SR-2body and SR-3body
            vector<HEPUtils::Jet*> baselineJets;    // Used for SR-4body
            for (HEPUtils::Jet* jet : event->jets()) {
                if (jet->pT() > 20. && fabs(jet->eta()) < 2.8) blJets.push_back(jet);
                if (jet->pT() > 20. && fabs(jet->eta()) < 2.8) baselineJets.push_back(jet);
            }

            // Overlap removal
            JetLeptonOverlapRemoval(blJets,blElectrons,0.2);
            LeptonJetOverlapRemoval(blElectrons,blJets,0.4);
            LeptonJetOverlapRemoval(blMuons,blJets,0.4);
            JetLeptonOverlapRemoval(baselineJets,baselineElectrons,0.2);
            LeptonJetOverlapRemoval(baselineElectrons,baselineJets,0.4);
            LeptonJetOverlapRemoval(baselineMuons,baselineJets,0.4);

            //Signal Jet
            vector<HEPUtils::Jet*> sgJets;                  // Used for SR-2body and SR-3body
            vector<HEPUtils::Jet*> signalJets;              // Used for SR-4body
            for (HEPUtils::Jet* jet : blJets) {
                if (jet->pT() > 20. && fabs(jet->eta()) < 2.5) {
                    sgJets.push_back(jet);
                }
            }
            for (HEPUtils::Jet* jet : baselineJets) {
                if (jet->pT() > 25. && fabs(jet->eta()) < 2.5) {
                    signalJets.push_back(jet);
                }
            }


            //Signal Leptons
            vector<HEPUtils::Particle*> sgElectrons, sgLeptons;          // Used for SR-2body and SR-3body
            vector<HEPUtils::Particle*> signalLeptons;  // Used for SR-4body
            for (HEPUtils::Particle* electron : blElectrons) {
                if (electron->pT() > 10. && fabs(electron->eta()) < 2.47){
                    sgElectrons.push_back(electron);
                }
            }
            ATLAS::applyMediumIDElectronSelectionR2(sgElectrons);
            for (HEPUtils::Particle* electron : sgElectrons) {
                sgLeptons.push_back(electron);
            }
            for (HEPUtils::Particle* muon : blMuons) {
                if (muon->pT() > 10. && fabs(muon->eta()) < 2.4){
                    sgLeptons.push_back(muon);
                }
            }
            ATLAS::applyMediumIDElectronSelectionR2(baselineElectrons);
            for (HEPUtils::Particle* electron : baselineElectrons) {
                signalLeptons.push_back(electron);
            }
            for (HEPUtils::Particle* muon : baselineMuons) {
                signalLeptons.push_back(muon);
            }


            //Put signal jets／leptons in pT order
            std::sort(signalJets.begin(), signalJets.end(), sortByPT_j);
            std::sort(signalLeptons.begin(), signalLeptons.end(), sortByPT_l);
            std::sort(sgJets.begin(), sgJets.end(), sortByPT_j);
            std::sort(sgLeptons.begin(), sgLeptons.end(), sortByPT_l);

            // Function used to get b jets
            vector<HEPUtils::Jet*> sgbJets;                  // Used for SR-2body and SR-3body
            vector<HEPUtils::Jet*> sgJetsGt25;               // Used for SR-2body
            //const std::vector<double>  a = {0,10.};
            //const std::vector<double>  b = {0,10000.};
            const std::vector<double> c = {0.77};
            HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);
            for (HEPUtils::Jet* jet :sgJets) {
                if (jet->pT() > 25.) {
                    sgJetsGt25.push_back(jet);
                    bool hasTag=has_tag(_eff2d, jet->eta(), jet->pT());
                    if(jet->btag() && hasTag && jet->pT() > 25.) sgbJets.push_back(jet);
                }
            }
            int nbjet = sgbJets.size();     // Used for SR-2body and SR-3body
            int njet25= sgJetsGt25.size();  // Used for SR-2body
            int njet = sgJets.size();  // Used for SR-2body

            // We now have the signal electrons, muons, jets and b jets- move on to the analysis
            /*********************************************************/
            /*                                                       */
            /* SIGNAL REGIONS SR-2body                               */
            /*                                                       */
            /*********************************************************/
            // Flags for SR-2body
            bool cABC_TriggerOS =false;
            bool cABC_SF        =false;
            // For SRA
            bool cA_mllGt111    =false;
            bool cA_nobjet      =false;
            bool CA_R2l2j       =false;
            bool cA_deltaX      =false;
            bool cA_MT2120      =false;
            bool cA_MT2140      =false;
            bool cA_MT2160      =false;
            bool cA_MT2180      =false;
            // For SRB
            bool cBC_mllExMz    =false;
            bool cBC_nbnj       =false;
            bool cB_DelBoost    =false;
            bool cB_MT2120      =false;
            bool cB_MT2140      =false;
            // For SRC
            bool cC_njGt2       =false;
            bool cC_R2lGt1o2    =false;
            bool cC_METGt200    =false;
            bool cC_MT2110      =false;

	    //Lepton Num
            if(sgLeptons.size() == 2){

                // Opposite sign leptons, pT(l1,l2)>25,20GeV, mll>20GeV
                HEPUtils::P4 lepton0=sgLeptons.at(0)->mom();
                HEPUtils::P4 lepton1=sgLeptons.at(1)->mom();
                double Mll= (lepton0+lepton1).m();

                // Savelep1 << sgLeptons[0]->pT() << endl;
                // Savelep2 << sgLeptons[1]->pT() << endl;

                if (sgLeptons[0]->pid()*sgLeptons[1]->pid()<0. && sgLeptons[0]->pT() > 25. && sgLeptons[1]->pT() > 20. && Mll>20.){
                    cABC_TriggerOS              = true;
                    if (sgLeptons[0]->pid()+sgLeptons[1]->pid()==0) cABC_SF = true;
                    /********* SRA-2body *********/
                    if (Mll>111.2) cA_mllGt111  = true;
                    if (nbjet==0)  cA_nobjet    = true;

                    double ptJet1=0.; if ( njet >= 1) ptJet1 = sgJets.at(0)->pT();
                    double ptJet2=0.; if ( njet >= 2) ptJet2 = sgJets.at(1)->pT();
                    double R2l2j=met / (met + lepton0.pT() + lepton1.pT() + ptJet1 + ptJet2);
                    if (R2l2j>0.3) CA_R2l2j     = true;

                    double DX = fabs((2 * (lepton0.pz() + lepton1.pz())) / 13000.);
                    if (DX<0.07)   cA_deltaX    = true;

                    //Calculate MT2
                    double mt2ll=0;
                    double pa_a[3] = { 0, sgLeptons[0]->mom().px(), sgLeptons[0]->mom().py() };
                    double pb_a[3] = { 0, sgLeptons[1]->mom().px(), sgLeptons[1]->mom().py() };
                    double pmiss_a[3] = { 0, ptot.px(), ptot.py() };
                    double mn_a = 0.;

                    mt2_bisect::mt2 mt2_event_a;
                    mt2_event_a.set_momenta(pa_a,pb_a,pmiss_a);
                    mt2_event_a.set_mn(mn_a);
                    mt2ll = mt2_event_a.get_mt2();

                    if(mt2ll>120 && mt2ll<140)  cA_MT2120   = true;
                    if(mt2ll>140 && mt2ll<160)  cA_MT2140   = true;
                    if(mt2ll>160 && mt2ll<180)  cA_MT2160   = true;
                    if(mt2ll>180)               cA_MT2180   = true;

                    /********* SRB-2body *********/
                    if (Mll>111.2 || Mll<71.2)  cBC_mllExMz = true;
                    if (nbjet>0 && njet25>1)    cBC_nbnj    = true;
                    //Calculate Delta phi_boost
                    HEPUtils::P4 pbll_TLV = lepton0 + lepton1 + ptot;
                    double dPhiEtmisspbll = fabs(pbll_TLV.deltaPhi(ptot));
                    if (dPhiEtmisspbll<1.5)     cB_DelBoost = true;
                    if(mt2ll>120 && mt2ll<140)  cB_MT2120   = true;
                    if(mt2ll>140 )              cB_MT2140   = true;

                    /********* SRC-2body *********/
                    if (njet25>2)               cC_njGt2    = true;
                    double R2L=met / (lepton0.pT() + lepton1.pT());
                    if (R2L>1.2)                cC_R2lGt1o2 = true;
                    if (met>200)                cC_METGt200 = true;
                    if (mt2ll>110)              cC_MT2110   = true;
                }
            }

            /*********************************************************/
            /*                                                       */
            /* SIGNAL REGIONS SR-4body                               */
            /*                                                       */
            /*********************************************************/
            // Flags
            bool c4_METOSlepton =false;
            bool c4_mllGt10     =false;
            bool c4_SoftLepton  =false;
            bool c4_njetGt2     =false;
            bool c4_Jet1PtGt150 =false;
            bool c4_Jet3PtMET   =false;
            bool c4_R2l4j       =false;
            bool c4_R2l         =false;
            bool c4_2bjetveto   =false;

            //MET trigger and Lepton Num
            if(signalLeptons.size() == 2 && met>200 ){

                // Opposite sign leptons
                if (signalLeptons[0]->pid()*signalLeptons[1]->pid()<0) c4_METOSlepton=true;

                // mll
                HEPUtils::P4 lep0=signalLeptons.at(0)->mom();
                HEPUtils::P4 lep1=signalLeptons.at(1)->mom();
                double mll= (lep0+lep1).m();
                if(mll>10) c4_mllGt10=true;
                //Soft lepton
                if(lep0.pT()<80 && lep1.pT()<35) c4_SoftLepton=true;

                //Number of jet
                int nJets = signalJets.size();
                if(nJets>=2){

                    c4_njetGt2=true;
                    double ptJet1=signalJets.at(0)->pT();
                    double ptJet2=signalJets.at(1)->pT();
                    double ptJet3=0.;
                    if ( nJets >= 3) ptJet3 = signalJets.at(2)->pT();
                    double ptJet4=0.;
                    if ( nJets >= 4) ptJet4 = signalJets.at(3)->pT();

                    //PT(j1)>150GeV
                    if (ptJet1>150) c4_Jet1PtGt150 =true;
                    //PT(j3)/MET<0.14
                    if (nJets>=3 && ptJet3/met < 0.14) c4_Jet3PtMET=true;
                    if (nJets<3) c4_Jet3PtMET=true;

                    //R_{2l4j}>0.35
                    double R2l4j=met / (met + lep0.pT() + lep1.pT() + ptJet1 + ptJet2 + ptJet3 + ptJet4);
                    if (R2l4j>0.35) c4_R2l4j=true;
                    //R_{2l}>12
                    double R2l=met / (lep0.pT() + lep1.pT());
                    if (R2l>12.) c4_R2l=true;

                    //veto b-jet on j1 and j2
                    // Function used to get b jets
                    /*const std::vector<double>  a = {0,10.};
                    const std::vector<double>  b = {0,10000.};
                    const std::vector<double> c = {0.7};
                    HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);*/
                    bool j1Tag=has_tag(_eff2d, signalJets.at(0)->eta(), signalJets.at(0)->pT());
                    bool j2Tag=has_tag(_eff2d, signalJets.at(1)->eta(), signalJets.at(1)->pT());
                    if (!(signalJets.at(0)->btag()&&j1Tag&&signalJets.at(1)->btag()&&j2Tag)) c4_2bjetveto=true;
                }
            }

            /*********************************************************/
            /*                                                       */
            /* Cut Flow                                              */
            /*                                                       */
            /*********************************************************/
            cutFlowVector_str[0] = "Total ";
            /*---------------------------------------*/
            cutFlowVector_str[1] = "SR2A--trigger && 2 OS lepton";
            cutFlowVector_str[2] = "SR2ASF--Same flavour";
            cutFlowVector_str[3] = "SR2ASF--mll>111GeV";
            cutFlowVector_str[4] = "SR2ASF--n_{b-jets}=0";
            cutFlowVector_str[5] = "SR2ASF--R_{2l2j}>0.3";
            cutFlowVector_str[6] = "SR2ASF--Delta x<0.07";
            cutFlowVector_str[7] = "SR2ASF--120<MT2<140";
            cutFlowVector_str[8] = "SR2ASF--140<MT2<160";
            cutFlowVector_str[9] = "SR2ASF--160<MT2<180";
            cutFlowVector_str[10] = "SR2ASF--180<MT2";

            cutFlowVector_str[11] = "SR2ADF--Different falvour";
            cutFlowVector_str[12] = "SR2ADF--mll>111GeV(only SF)";
            cutFlowVector_str[13] = "SR2ADF--n_{b-jets}=0";
            cutFlowVector_str[14] = "SR2ADF--R_{2l2j}>0.3(only SF)";
            cutFlowVector_str[15] = "SR2ADF--Delta x<0.07";
            cutFlowVector_str[16] = "SR2ADF--120<MT2<140";
            cutFlowVector_str[17] = "SR2ADF--140<MT2<160";
            cutFlowVector_str[18] = "SR2ADF--160<MT2<180";
            cutFlowVector_str[19] = "SR2ADF--180<MT2";
            /*---------------------------------------*/
            cutFlowVector_str[20] = "SR2BC--trigger && 2 OS lepton";
            cutFlowVector_str[21] = "SR2BSF--Same flavour";
            cutFlowVector_str[22] = "SR2BSF--mll>111GeV or mll<71GeV";
            cutFlowVector_str[23] = "SR2BSF--n_{b-jets}>0 && n_{jets}>1";
            cutFlowVector_str[24] = "SR2BSF--Delta phi_{boost}<1.5";
            cutFlowVector_str[25] = "SR2BSF--120<MT2<140";
            cutFlowVector_str[26] = "SR2BSF--140<MT2";

            cutFlowVector_str[27] = "SR2BDF--Different flavour";
            cutFlowVector_str[28] = "SR2BDF--mll>111GeV or mll<71GeV(only SF)";
            cutFlowVector_str[29] = "SR2BDF--n_{b-jets}>0 && n_{jets}>1";
            cutFlowVector_str[30] = "SR2BDF--Delta phi_{boost}<1.5";
            cutFlowVector_str[31] = "SR2BDF--120<MT2<140";
            cutFlowVector_str[32] = "SR2BDF--140<MT2";

            cutFlowVector_str[33] = "SR2CSF--n_{b-jets}>0 && n_{jets}>1";
            cutFlowVector_str[34] = "SR2CSF--n_{jets}>2";
            cutFlowVector_str[35] = "SR2CSF--R_{2l}>1.2";
            cutFlowVector_str[36] = "SR2CSF--E_T^{miss}>200GeV";
            cutFlowVector_str[37] = "SR2CSF--110<MT2";

            cutFlowVector_str[38] = "SR2CDF--n_{b-jets}>0 && n_{jets}>1";
            cutFlowVector_str[39] = "SR2CDF--n_{jets}>2";
            cutFlowVector_str[40] = "SR2CDF--R_{2l}>1.2";
            cutFlowVector_str[41] = "SR2CDF--E_T^{miss}>200GeV";
            cutFlowVector_str[42] = "SR2CDF--110<MT2";

            /*---------------------------------------*/
            cutFlowVector_str[57] = "SR4b--MET trigger && 2 OS Leptons ";
            cutFlowVector_str[58] = "SR4b--m_{ll}>10GeV ";
            cutFlowVector_str[59] = "SR4b--PT(l1)<80GeV && PT(l1)<35GeV ";
            cutFlowVector_str[60] = "SR4b--n_{jets}>2 ";
            cutFlowVector_str[61] = "SR4b--PT(j1)>150GeV ";
            cutFlowVector_str[62] = "SR4b--PT(j3)/MET<0.14 ";
            cutFlowVector_str[63] = "SR4b--R_{2l4j}>0.35 ";
            cutFlowVector_str[64] = "SR4b--R_{2l}>12 ";
            cutFlowVector_str[65] = "SR4b--veto on j1 and j2 ";

            for(int j=0;j<NCUTS;j++){
                if(
                   (j==0) ||
                   /********* SRA-2body *********/
                   (j==1  && cABC_TriggerOS) ||
                   //Same Flavour
                   (j==2  && cABC_SF) ||
                   (j==3  && cABC_SF && cA_mllGt111) ||
                   (j==4  && cABC_SF && cA_mllGt111 && cA_nobjet) ||
                   (j==5  && cABC_SF && cA_mllGt111 && cA_nobjet && CA_R2l2j) ||
                   (j==6  && cABC_SF && cA_mllGt111 && cA_nobjet && CA_R2l2j && cA_deltaX) ||
                   (j==7  && cABC_SF && cA_mllGt111 && cA_nobjet && CA_R2l2j && cA_deltaX && cA_MT2120) ||
                   (j==8  && cABC_SF && cA_mllGt111 && cA_nobjet && CA_R2l2j && cA_deltaX && cA_MT2140) ||
                   (j==9  && cABC_SF && cA_mllGt111 && cA_nobjet && CA_R2l2j && cA_deltaX && cA_MT2160) ||
                   (j==10  && cABC_SF && cA_mllGt111 && cA_nobjet && CA_R2l2j && cA_deltaX && cA_MT2180) ||
                   //different Flavour
                   (j==11 && cABC_TriggerOS && (!cABC_SF)) ||
                   (j==12 && cABC_TriggerOS && (!cABC_SF)) ||
                   (j==13 && (!cABC_SF) && cA_nobjet) ||
                   (j==14 && (!cABC_SF) && cA_nobjet) ||
                   (j==15 && (!cABC_SF) && cA_nobjet && cA_deltaX) ||
                   (j==16 && (!cABC_SF) && cA_nobjet && cA_deltaX && cA_MT2120) ||
                   (j==17 && (!cABC_SF) && cA_nobjet && cA_deltaX && cA_MT2140) ||
                   (j==18 && (!cABC_SF) && cA_nobjet && cA_deltaX && cA_MT2160) ||
                   (j==19 && (!cABC_SF) && cA_nobjet && cA_deltaX && cA_MT2180) ||
                   /********* SRB-2body *********/
                   (j==20  && cABC_TriggerOS) ||
                   //Same Flavour
                   (j==21  && cABC_SF) ||
                   (j==22  && cABC_SF && cBC_mllExMz) ||
                   (j==23  && cABC_SF && cBC_mllExMz && cBC_nbnj) ||
                   (j==24  && cABC_SF && cBC_mllExMz && cBC_nbnj && cB_DelBoost) ||
                   (j==25  && cABC_SF && cBC_mllExMz && cBC_nbnj && cB_DelBoost && cB_MT2120) ||
                   (j==26  && cABC_SF && cBC_mllExMz && cBC_nbnj && cB_DelBoost && cB_MT2140) ||
                   //different Flavour
                   (j==27  && cABC_TriggerOS && (!cABC_SF)) ||
                   (j==28  && cABC_TriggerOS && (!cABC_SF)) ||
                   (j==29  && (!cABC_SF) && cBC_nbnj) ||
                   (j==30  && (!cABC_SF) && cBC_nbnj && cB_DelBoost) ||
                   (j==31  && (!cABC_SF) && cBC_nbnj && cB_DelBoost && cB_MT2120) ||
                   (j==32  && (!cABC_SF) && cBC_nbnj && cB_DelBoost && cB_MT2140) ||
                   /********* SRC-2body *********/
                   //Same Flavour
                   (j==33  && cABC_SF && cBC_mllExMz && cBC_nbnj) ||
                   (j==34  && cABC_SF && cBC_mllExMz && cBC_nbnj && cC_njGt2) ||
                   (j==35  && cABC_SF && cBC_mllExMz && cBC_nbnj && cC_njGt2 && cC_R2lGt1o2) ||
                   (j==36  && cABC_SF && cBC_mllExMz && cBC_nbnj && cC_njGt2 && cC_R2lGt1o2 && cC_METGt200) ||
                   (j==37  && cABC_SF && cBC_mllExMz && cBC_nbnj && cC_njGt2 && cC_R2lGt1o2 && cC_METGt200 && cC_MT2110) ||
                   //different Flavour
                   (j==38  && (!cABC_SF) && cBC_nbnj) ||
                   (j==39  && (!cABC_SF) && cBC_nbnj && cC_njGt2) ||
                   (j==40  && (!cABC_SF) && cBC_nbnj && cC_njGt2 && cC_R2lGt1o2) ||
                   (j==41  && (!cABC_SF) && cBC_nbnj && cC_njGt2 && cC_R2lGt1o2 && cC_METGt200) ||
                   (j==42  && (!cABC_SF) && cBC_nbnj && cC_njGt2 && cC_R2lGt1o2 && cC_METGt200 && cC_MT2110) ||
                   /********* SR-4body *********/
                   (j==57 && c4_METOSlepton ) ||
                   (j==58 && c4_METOSlepton && c4_mllGt10) ||
                   (j==59 && c4_METOSlepton && c4_mllGt10 && c4_SoftLepton) ||
                   (j==60 && c4_METOSlepton && c4_mllGt10 && c4_SoftLepton && c4_njetGt2) ||
                   (j==61 && c4_METOSlepton && c4_mllGt10 && c4_SoftLepton && c4_Jet1PtGt150) ||
                   (j==62 && c4_METOSlepton && c4_mllGt10 && c4_SoftLepton && c4_Jet1PtGt150 && c4_Jet3PtMET) ||
                   (j==63 && c4_METOSlepton && c4_mllGt10 && c4_SoftLepton && c4_Jet1PtGt150 && c4_Jet3PtMET && c4_R2l4j) ||
                   (j==64 && c4_METOSlepton && c4_mllGt10 && c4_SoftLepton && c4_Jet1PtGt150 && c4_Jet3PtMET && c4_R2l4j && c4_R2l) ||
                   (j==65 && c4_METOSlepton && c4_mllGt10 && c4_SoftLepton && c4_Jet1PtGt150 && c4_Jet3PtMET && c4_R2l4j && c4_R2l && c4_2bjetveto)
                   )cutFlowVector[j]++;

            }
            // signal region

            if (   cABC_SF  && cA_mllGt111 && cA_nobjet && CA_R2l2j && cA_deltaX && cA_MT2120 ) _SRASF120++;
            if ( (!cABC_SF)                && cA_nobjet             && cA_deltaX && cA_MT2120 ) _SRADF120++;
            if (   cABC_SF  && cA_mllGt111 && cA_nobjet && CA_R2l2j && cA_deltaX && cA_MT2140 ) _SRASF140++;
            if ( (!cABC_SF)                && cA_nobjet             && cA_deltaX && cA_MT2140 ) _SRADF140++;
            if (   cABC_SF  && cA_mllGt111 && cA_nobjet && CA_R2l2j && cA_deltaX && cA_MT2160 ) _SRASF160++;
            if ( (!cABC_SF)                && cA_nobjet             && cA_deltaX && cA_MT2160 ) _SRADF160++;
            if (   cABC_SF  && cA_mllGt111 && cA_nobjet && CA_R2l2j && cA_deltaX && cA_MT2180 ) _SRASF180++;
            if ( (!cABC_SF)                && cA_nobjet             && cA_deltaX && cA_MT2180 ) _SRADF180++;

            if (   cABC_SF  && cBC_mllExMz && cBC_nbnj && cB_DelBoost && cB_MT2120 ) _SRBSF120++;
            if ( (!cABC_SF)                && cBC_nbnj && cB_DelBoost && cB_MT2120 ) _SRBDF120++;
            if (   cABC_SF  && cBC_mllExMz && cBC_nbnj && cB_DelBoost && cB_MT2140 ) _SRBSF140++;
            if ( (!cABC_SF)                && cBC_nbnj && cB_DelBoost && cB_MT2140 ) _SRBDF140++;

            if (   cABC_SF  && cBC_mllExMz && cBC_nbnj && cC_njGt2 && cC_R2lGt1o2 && cC_METGt200 && cC_MT2110 ) _SRCSF110++;
            if ( (!cABC_SF) &&                cBC_nbnj && cC_njGt2 && cC_R2lGt1o2 && cC_METGt200 && cC_MT2110 ) _SRCDF110++;


            if (c4_METOSlepton && c4_mllGt10 && c4_SoftLepton && c4_Jet1PtGt150 && c4_Jet3PtMET && c4_R2l4j && c4_R2l && c4_2bjetveto) _SR4b++;
        return;

        }


        void add(Analysis* other) {
            // The base class add function handles the signal region vector and total # events.
            Analysis::add(other);

            Analysis_ATLAS_13TeV_2LEPStop_36invfb* specificOther
                = dynamic_cast<Analysis_ATLAS_13TeV_2LEPStop_36invfb*>(other);

            // Here we will add the subclass member variables:
            if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
            for (int j=0; j<NCUTS; j++) {
                cutFlowVector[j] += specificOther->cutFlowVector[j];
                cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
            }

	    _SRASF120 += specificOther->_SRASF120;
	    _SRASF140 += specificOther->_SRASF140;
	    _SRADF140 += specificOther->_SRADF140;
	    _SRASF160 += specificOther->_SRASF160;
	    _SRADF160 += specificOther->_SRADF160;
	    _SRASF180 += specificOther->_SRASF180;
	    _SRADF180 += specificOther->_SRADF180;
	    _SRBSF120 += specificOther->_SRBSF120;
	    _SRBDF120 += specificOther->_SRBDF120;
	    _SRBSF140 += specificOther->_SRBSF140;
	    _SRBDF140 += specificOther->_SRBDF140;
	    _SRCSF110 += specificOther->_SRCSF110;
	    _SRCDF110 += specificOther->_SRCDF110;
	    _SR4b += specificOther->_SR4b;
        }


        void collect_results() {

            // double scale_by=1.;
            // cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;
            // cout << "CUT FLOW: ATLAS 13 TeV 2 lep stop paper "<<endl;
            // cout << "------------------------------------------------------------------------------------------------------------------------------"<<endl;
            // cout<< right << setw(40) << "CUT" <<  "," << setw(20) << "RAW" <<  "," << setw(20) << "SCALED"
            // <<  "," << setw(20) << "%" <<  "," << setw(20) << "clean adj RAW"<<  "," << setw(20) << "clean adj %" << endl;
            // for (int j=0; j<NCUTS; j++) {
            //     cout << right <<  setw(40) << cutFlowVector_str[j].c_str() <<  "," << setw(20)
            //     << cutFlowVector[j] <<  "," << setw(20) << cutFlowVector[j]*scale_by <<  "," << setw(20)
            //     << 100.*cutFlowVector[j]/cutFlowVector[0] << "%" <<  "," << setw(20)
            //     << cutFlowVector[j]*scale_by <<  "," << setw(20) << 100.*cutFlowVector[j]/cutFlowVector[0]<< "%" << endl;
            // }
            // cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;

            // signal regin 2-body A
            SignalRegionData results_SRASF120;
            results_SRASF120.sr_label = "SRASF120";
            results_SRASF120.n_observed = 22.;
            results_SRASF120.n_background = 20.0;
            results_SRASF120.background_sys = 4.6;
            results_SRASF120.signal_sys = 0.;
            results_SRASF120.n_signal = _SRASF120;
            add_result(results_SRASF120);

            SignalRegionData results_SRADF120;
            results_SRADF120.sr_label = "SRADF120";
            results_SRADF120.n_observed = 27.;
            results_SRADF120.n_background = 23.8;
            results_SRADF120.background_sys = 4.2;
            results_SRADF120.signal_sys = 0.;
            results_SRADF120.n_signal = _SRADF120;
            add_result(results_SRADF120);

            SignalRegionData results_SRASF140;
            results_SRASF140.sr_label = "SRASF140";
            results_SRASF140.n_observed = 6.;
            results_SRASF140.n_background = 11.0;
            results_SRASF140.background_sys = 2.5;
            results_SRASF140.signal_sys = 0.;
            results_SRASF140.n_signal = _SRASF140;
            add_result(results_SRASF140);

            SignalRegionData results_SRADF140;
            results_SRADF140.sr_label = "SRADF140";
            results_SRADF140.n_observed = 6.;
            results_SRADF140.n_background = 10.8;
            results_SRADF140.background_sys = 2.1;
            results_SRADF140.signal_sys = 0.;
            results_SRADF140.n_signal = _SRADF140;
            add_result(results_SRADF140);

            SignalRegionData results_SRASF160;
            results_SRASF160.sr_label = "SRASF160";
            results_SRASF160.n_observed = 10.;
            results_SRASF160.n_background = 5.6;
            results_SRASF160.background_sys = 1.8;
            results_SRASF160.signal_sys = 0.;
            results_SRASF160.n_signal = _SRASF160;
            add_result(results_SRASF160);

            SignalRegionData results_SRADF160;
            results_SRADF160.sr_label = "SRADF160";
            results_SRADF160.n_observed = 7.;
            results_SRADF160.n_background = 6.4;
            results_SRADF160.background_sys = 1.3;
            results_SRADF160.signal_sys = 0.;
            results_SRADF160.n_signal = _SRADF160;
            add_result(results_SRADF160);

            SignalRegionData results_SRASF180;
            results_SRASF180.sr_label = "SRASF180";
            results_SRASF180.n_observed = 16.;
            results_SRASF180.n_background = 12.3;
            results_SRASF180.background_sys = 2.6;
            results_SRASF180.signal_sys = 0.;
            results_SRASF180.n_signal = _SRASF180;
            add_result(results_SRASF180);

            SignalRegionData results_SRADF180;
            results_SRADF180.sr_label = "SRADF180";
            results_SRADF180.n_observed = 8.;
            results_SRADF180.n_background = 5.4;
            results_SRADF180.background_sys = 1.7;
            results_SRADF180.signal_sys = 0.;
            results_SRADF180.n_signal = _SRADF180;
            add_result(results_SRADF180);

            // signal regin 2-body B
            SignalRegionData results_SRBSF120;
            results_SRBSF120.sr_label = "SRBSF120";
            results_SRBSF120.n_observed = 17.;
            results_SRBSF120.n_background = 16.3;
            results_SRBSF120.background_sys = 6.2;
            results_SRBSF120.signal_sys = 0.;
            results_SRBSF120.n_signal = _SRBSF120;
            add_result(results_SRBSF120);

            SignalRegionData results_SRBDF120;
            results_SRBDF120.sr_label = "SRBDF120";
            results_SRBDF120.n_observed = 13.;
            results_SRBDF120.n_background = 16.1;
            results_SRBDF120.background_sys = 5.3;
            results_SRBDF120.signal_sys = 0.;
            results_SRBDF120.n_signal = _SRBDF120;
            add_result(results_SRBDF120);

            SignalRegionData results_SRBSF140;
            results_SRBSF140.sr_label = "SRBSF140";
            results_SRBSF140.n_observed = 9.;
            results_SRBSF140.n_background = 7.4;
            results_SRBSF140.background_sys = 1.1;
            results_SRBSF140.signal_sys = 0.;
            results_SRBSF140.n_signal = _SRBSF140;
            add_result(results_SRBSF140);

            SignalRegionData results_SRBDF140;
            results_SRBDF140.sr_label = "SRBDF140";
            results_SRBDF140.n_observed = 7.;
            results_SRBDF140.n_background = 4.8;
            results_SRBDF140.background_sys = 1.0;
            results_SRBDF140.signal_sys = 0.;
            results_SRBDF140.n_signal = _SRBDF140;
            add_result(results_SRBDF140);

            // signal regin 2-body C
            SignalRegionData results_SRCSF110;
            results_SRCSF110.sr_label = "SRCSF110";
            results_SRCSF110.n_observed = 11.;
            results_SRCSF110.n_background = 5.3;
            results_SRCSF110.background_sys = 1.8;
            results_SRCSF110.signal_sys = 0.;
            results_SRCSF110.n_signal = _SRCSF110;
            add_result(results_SRCSF110);

            SignalRegionData results_SRCDF110;
            results_SRCDF110.sr_label = "SRCDF110";
            results_SRCDF110.n_observed = 7.;
            results_SRCDF110.n_background = 3.8;
            results_SRCDF110.background_sys = 1.5;
            results_SRCDF110.signal_sys = 0.;
            results_SRCDF110.n_signal = _SRCDF110;
            add_result(results_SRCDF110);


            // signal regin 4-body
            SignalRegionData results_SR4b;
            results_SR4b.sr_label = "SR4b";
            results_SR4b.n_observed = 30.;
            results_SR4b.n_background = 28.;
            results_SR4b.background_sys = 6.;
            results_SR4b.signal_sys = 0.;
            results_SR4b.n_signal = _SR4b;
            add_result(results_SR4b);
            return;
        }

    protected:
      void clear() {
	_SRASF120=0; _SRADF120=0; _SRASF140=0; _SRADF140=0;
	_SRASF160=0; _SRADF160=0; _SRASF180=0; _SRADF180=0;
	_SRBSF120=0; _SRBDF120=0; _SRBSF140=0; _SRBDF140=0;
	_SRCSF110=0; _SRCDF110=0;
	//_SR3BodyTSF=0; _SR3BodyTDF=0; _SR3BodyWSF=0; _SR3BodyWDF=0;
	_SR4b=0;

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }



    };



    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2LEPStop_36invfb)


  }
}
