#include <cstdlib>
#include <stdlib.h>

#include <iostream>
#include <fstream>

#include "TClonesArray.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TGraph.h"

#include "T2KReWeight/WeightEngines/NEUT/T2KNEUTUtils.h"
#include "T2KReWeight/WeightEngines/T2KReWeightFactory.h"
#include "T2KReWeight/Utils/WeightsStorer.h"
#include "T2KReWeight/WeightEngines/T2KReWeightEvent.h"



// all values of the parameters are from xsec_covariance_2020a_v6.root
// nominal values are unnorm and so does the sigmas

int main(int argc, char *argv[]) {
  // write a function like ParseArgs later to read arguments from command line
  std::string inputfile = ""; // or define as char* directly
  std::string cardname = "";
  std::string outputfile = "";
  if (argc > 3) {
    inputfile = argv[1];
    cardname = argv[2];
    outputfile = argv[3];
  } else {
    std::cerr << "no input file to reweight" << std::endl;
    exit(1);
  }

  t2krew::WeightsStorer *storer =
      new t2krew::WeightsStorer("testweights.root"); // forweightstorer
  //	std::ofstream fout("storeweight2.txt");

  std::cout << "start to reweight events in file " << inputfile << std::endl;

  //	TFile* finput = new TFile(inputfile.c_str(), "OPEN");
  //	if(!finput)
  //		std::cerr<<"cannot open inputfile "<<inputfile<<std::endl;

  // read inputfile
  TChain *defaultTree = new TChain("default");
  TChain *NRooTrackerVtxTree = new TChain("NRooTrackerVtx");

  std::string fileName;
  if (inputfile.find(".list") != std::string::npos) {
    ifstream in(inputfile.c_str());
    while (in >> fileName) {
      if (in.fail())
        break;
      defaultTree->AddFile(fileName.c_str());
      NRooTrackerVtxTree->AddFile(fileName.c_str());
    }
  } else {
    defaultTree->AddFile(inputfile.c_str());
    NRooTrackerVtxTree->AddFile(inputfile.c_str());
  }

  Int_t EventID;
  Int_t accum_level;
  Int_t cut0, cut1, cut2, cut5;
  Int_t reacCode;
  //    Int_t cut0, cut1, cut2, cut3,cut4, cut5, cut6, cut7, cut8, cut9, cut10,
  //    cut11, cut12, cut13;
  Int_t HSMTrackLayers;
  Float_t TSHitFracOverShower;
  Int_t RooVtxEntry;
  Int_t TruthVertexID;
  Int_t isWaterConfig;
  Double_t ShowerMedianWidth;
  Double_t ShowerEDepFraction;

  defaultTree->SetBranchAddress("evt", &EventID);
  defaultTree->SetBranchAddress("cut0", &cut0);
  defaultTree->SetBranchAddress("cut1", &cut1);
  defaultTree->SetBranchAddress("cut2", &cut2);
  defaultTree->SetBranchAddress("cut5", &cut5);
  defaultTree->SetBranchAddress("reactionCode", &reacCode);
  defaultTree->SetBranchAddress("accum_level", &accum_level);
  defaultTree->SetBranchAddress("isWaterConfig", &isWaterConfig);
  defaultTree->SetBranchAddress("ShowerMedianWidth", &ShowerMedianWidth);
  defaultTree->SetBranchAddress("ShowerEDepFraction", &ShowerEDepFraction);
  defaultTree->SetBranchAddress("HSMTrackLayers", &HSMTrackLayers);
  defaultTree->SetBranchAddress("TSHitFracOverShower", &TSHitFracOverShower);
  defaultTree->SetBranchAddress("RooVtxEntry", &RooVtxEntry);
  defaultTree->SetBranchAddress("TruthVertexID", &TruthVertexID);

  int NVtx;
  TClonesArray *nRooVtxs = new TClonesArray("ND::NRooTrackerVtx", 100);
  NRooTrackerVtxTree->SetBranchAddress("NVtx", &NVtx);
  NRooTrackerVtxTree->SetBranchAddress("Vtx", &nRooVtxs);

  auto T2KRW = t2krew::MakeT2KReWeightInstance(t2krew::Event::kNRooTracker);
  t2krew::T2KNEUTUtils::SetCardFile(cardname);

  std::vector<t2krew::T2KSyst_t> SystParams;
  std::vector<std::string> paramnames;
  std::vector<Double_t> nominals;
  std::vector<Double_t> sigmas;
  std::vector<Double_t> lbs;
  std::vector<Double_t> ubs;
  std::vector<std::vector<Double_t>> tweakindices;
  std::vector<TGraph *> param_graphs;

  //	std::vector<Double_t> balanced = {-5.0, -4.0, -3.0, -2.5, -2.0, -1.5,
  //-1, -0.8, -0.6, -0.4 -0.2, -0.1, -0.05, 0.00, 0.05, 0.1, 0.2, 0.4, 0.6, 0.8,
  // 1, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0}; //c++11 of later supports such syntax but
  // c++98 doesn't. either change to c++11 or write in the below below...
  //	std::vector<Double_t> unbalanced1 = {-4.0, -3.0, -2.5, -2.0, -1.5, -1,
  //-0.8, -0.6, -0.4 -0.2, -0.1, -0.05, 0.00, 0.05, 0.1, 0.2, 0.4, 0.6, 0.8,
  // 1, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0};

  //	double arrs[27] = {-5.0, -4.0, -3.0, -2.5, -2.0, -1.5, -1, -0.8, -0.6,
  //-0.4, -0.2, -0.1, -0.05, 0.00, 0.05, 0.1, 0.2, 0.4, 0.6, 0.8,
  // 1, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0};
  std::vector<Double_t> balanced;
  for (int i = 0; i < 21; i++)
    balanced.push_back(-5.0 + 0.5 * i);
  //	for(int i=0; i<27; i++)
  //		balanced.push_back(arrs[i]);
  std::vector<Double_t> unbalanced1;
  for (int i = 0; i < 19; i++)
    unbalanced1.push_back(-4.0 + 0.5 * i);
  //	for(int i=1; i<27; i++)
  //        unbalanced1.push_back(arrs[i]);
  std::vector<Double_t> lb_minus2sig;
  for (int i = 0; i < 15; i++)
    lb_minus2sig.push_back(-2.0 + 0.5 * i);
  std::vector<Double_t> lb_minus1halfsig;
  for (int i = 0; i < 14; i++)
    lb_minus1halfsig.push_back(-1.5 + 0.5 * i);
  std::vector<Double_t> lb_minus1sig;
  for (int i = 0; i < 13; i++)
    lb_minus1sig.push_back(-1.0 + 0.5 * i);

  //	std::vector<Double_t> thistweakindices;
  //	thistweakindices = balanced;
  // CCQE
  SystParams.push_back(T2KRW->DialFromString("MaCCQE"));
  paramnames.push_back("MaCCQE");
  nominals.push_back(T2KRW->GetDial_From_Value(SystParams.back()));
  nominals.push_back(T2KRW->GetDial_OneSigma(SystParams.back(),1));
  lbs.push_back(0);
  ubs.push_back(9999);
  tweakindices.push_back(balanced);

  // Res1pi
  SystParams.push_back(T2KRW->DialFromString("MaRES"));
  paramnames.push_back("MaRES");
  nominals.push_back(T2KRW->GetDial_From_Value(SystParams.back()));
  nominals.push_back(T2KRW->GetDial_OneSigma(SystParams.back(),1));
  lbs.push_back(0);
  ubs.push_back(9999);
  tweakindices.push_back(balanced);

  SystParams.push_back(T2KRW->DialFromString("CA5RES"));
  paramnames.push_back("CA5");
  nominals.push_back(T2KRW->GetDial_From_Value(SystParams.back()));
  nominals.push_back(T2KRW->GetDial_OneSigma(SystParams.back(),1));
  lbs.push_back(0);
  ubs.push_back(9999);
  tweakindices.push_back(balanced);

  SystParams.push_back(T2KRW->DialFromString("BgSclRES"));
  paramnames.push_back("ISO_BKG"); // is it right?
  nominals.push_back(T2KRW->GetDial_From_Value(SystParams.back()));
  nominals.push_back(T2KRW->GetDial_OneSigma(SystParams.back(),1));
  lbs.push_back(0);
  ubs.push_back(9999);
  tweakindices.push_back(balanced);

  // FSI
  SystParams.push_back(T2KRW->DialFromString("PionFSI_AbsProb"));
  paramnames.push_back("FSI_PI_ABS"); // NEUT NAME: FEFABS
  nominals.push_back(T2KRW->GetDial_From_Value(SystParams.back()));
  nominals.push_back(T2KRW->GetDial_OneSigma(SystParams.back(),1));
  lbs.push_back(-9999);
  ubs.push_back(9999);
  tweakindices.push_back(lb_minus2sig);

  SystParams.push_back(T2KRW->DialFromString("PionFSI_CExLowMomProb"));
  paramnames.push_back("FSI_CEX_LO"); // NEUT NAME: FEFCX
  nominals.push_back(T2KRW->GetDial_From_Value(SystParams.back()));
  nominals.push_back(T2KRW->GetDial_OneSigma(SystParams.back(),1));
  lbs.push_back(-9999);
  ubs.push_back(9999);
  tweakindices.push_back(lb_minus1sig);

  SystParams.push_back(T2KRW->DialFromString("PionFSI_QELowMomProb"));
  paramnames.push_back("FSI_INEL_LO"); // NEUT NAME: FEFQE
  nominals.push_back(T2KRW->GetDial_From_Value(SystParams.back()));
  nominals.push_back(T2KRW->GetDial_OneSigma(SystParams.back(),1));
  lbs.push_back(-9999);
  ubs.push_back(9999);
  tweakindices.push_back(lb_minus2sig);

  SystParams.push_back(T2KRW->DialFromString("PionFSI_InelProb"));
  paramnames.push_back("FSI_PI_PROD"); // NEUT NAME: FEFINEL
  nominals.push_back(T2KRW->GetDial_From_Value(SystParams.back()));
  nominals.push_back(T2KRW->GetDial_OneSigma(SystParams.back(),1));
  lbs.push_back(-9999);
  ubs.push_back(9999);
  tweakindices.push_back(lb_minus1halfsig);

  SystParams.push_back(T2KRW->DialFromString("PionFSI_CExHighMomProb"));
  paramnames.push_back(
      "FSI_CEX_HI"); // NEUT NAME" FEFCXL, not found in
                     // _xsec_covariance_2020a_v6.root, so use the same info
                     // with of FEFCX for now //update on 05/02/2021, according
  nominals.push_back(T2KRW->GetDial_From_Value(SystParams.back()));
  nominals.push_back(T2KRW->GetDial_OneSigma(SystParams.back(),1));
  lbs.push_back(-9999);
  ubs.push_back(9999);
  tweakindices.push_back(balanced);

  SystParams.push_back(T2KRW->DialFromString("PionFSI_QEHighMomProb"));
  paramnames.push_back("FSI_INEL_HI"); // NEUT NAME" FEFQEH
  nominals.push_back(T2KRW->GetDial_From_Value(SystParams.back()));
  nominals.push_back(T2KRW->GetDial_OneSigma(SystParams.back(),1));
  lbs.push_back(-9999);
  ubs.push_back(9999);
  tweakindices.push_back(balanced);
  // end of FSI

  // DIS and LowWMultiPi. some norm parameters???
  // found names like t2krew::kNIWG_DIS_BY_corr in T2KSyst.h
  SystParams.push_back(T2KRW->DialFromString("DIS_BY_corr_on_off"));
  nominals.push_back(T2KRW->GetDial_From_Value(SystParams.back()));
  nominals.push_back(T2KRW->GetDial_OneSigma(SystParams.back(),1));
  lbs.push_back(-9999);
  ubs.push_back(9999);
  tweakindices.push_back(balanced);

  SystParams.push_back(T2KRW->DialFromString("MultiPi_BY_corr_on_off"));
  nominals.push_back(T2KRW->GetDial_From_Value(SystParams.back()));
  nominals.push_back(T2KRW->GetDial_OneSigma(SystParams.back(),1));
  lbs.push_back(-9999);
  ubs.push_back(9999);
  tweakindices.push_back(balanced);

  SystParams.push_back(T2KRW->DialFromString("MultiPi_Multiplicity_TotXSec"));
  nominals.push_back(T2KRW->GetDial_From_Value(SystParams.back()));
  nominals.push_back(T2KRW->GetDial_OneSigma(SystParams.back(),1));
  lbs.push_back(-9999);
  ubs.push_back(9999);
  tweakindices.push_back(balanced);
  // end od DIS and LowWMutiPi

  //Luke -- These dials have not been brought forward. If they are important
  // I will put them in the NIWGReWeight2021 it is minimal hassle.
  /*
  // NC, nominal and sigmas are guessed from xsec_covariance_2020a_v6 NC_Coh
  paramnames.push_back("NIWG2012a_nc1piE0");
  nominals.push_back(1);
  sigmas.push_back(0.3);
  lbs.push_back(0);
  ubs.push_back(9999);
  tweakindices.push_back(unbalanced1);

  paramnames.push_back("NIWG2012a_nc1pi0E0");
  nominals.push_back(1);
  sigmas.push_back(0.3);
  lbs.push_back(0);
  ubs.push_back(9999);
  tweakindices.push_back(unbalanced1);

  paramnames.push_back("NIWG2012a_nccohE0");
  nominals.push_back(1);
  sigmas.push_back(0.3);
  lbs.push_back(0);
  ubs.push_back(9999);
  tweakindices.push_back(unbalanced1);

  paramnames.push_back("NIWG2012a_ncotherE0");
  nominals.push_back(1);
  sigmas.push_back(0.3);
  lbs.push_back(0);
  ubs.push_back(9999);
  tweakindices.push_back(unbalanced1);
  */
  /*
   *????
    kNIWG2010a_nc,
      kNIWG2010a_nc1pi0,
            kNIWG2010a_nccoh,
              kNIWG2010a_ncoth,
    kNIWG2011a_NCRESSplineE0,
      kNIWG2011a_NCRESSplineE1,
            kNIWG2011a_NCRESSplineE2,
              kNIWG2011a_NCRESSplineE3,
                    kNIWG2011a_NCRESSplineE4,
                      kNIWG2011a_NCRESSplineE5,
                  */
  /*
          //2p2h
          rw.Systematics().Include(t2krew::kNIWGMEC_Norm_C12);//Norm para found
          SystParams.push_back(t2krew::);
          paramnames.push_back();
          nominals.push_back();
          sigmas.push_back();
          thistweakindices=;
          tweakindices.push_back(thistweakindices);

          rw.Systematics().Include(t2krew::kNIWGMEC_Norm_O16);
          SystParams.push_back(t2krew::);
          paramnames.push_back();
          nominals.push_back();
          sigmas.push_back();
          thistweakindices=;
          tweakindices.push_back(thistweakindices);
          rw.Systematics().Include(t2krew::kNIWGMEC_Norm_Other);
          rw.Systematics().Include(t2krew::kNIWGMEC_PDDWeight_C12);//2p2h_shape_C
          rw.Systematics().Include(t2krew::kNIWGMEC_PDDWeight_O16);//2p2h_shape_O
          //DIS&MutilPi
          rw.Systematics().Include(t2krew::kNIWG_DIS_BY_corr);
          rw.Systematics().Include(t2krew::kNIWG_MultiPi_BY_corr);
          rw.Systematics().Include(t2krew::kNIWG_MultiPi_Xsec_AGKY);
  //	rw.Systematics().Include(t2krew::);//some other parameters related to
  DIS. I didn't find the dial based on prameter names
          //Coherent
  //	rw.Systematics().Include(t2krew::);
  //	rw.Systematics().Include(t2krew::);
  //	rw.Systematics().Include(t2krew::);
          //	NC
  //	rw.Systematics().Include(t2krew::);
          //	etc
          //	fsi
  */

  for (int ipara = 0; ipara < (int)SystParams.size(); ipara++) {
    TGraph *graph = new TGraph();
    param_graphs.push_back(graph);
  }

  // set up output file
  TFile *foutput = new TFile(outputfile.c_str(), "RECREATE");
  TTree *weightsTree =
      new TTree("eventsReWeightsTree", "xsecfsireweights on each event");
  weightsTree->Branch("evt", &EventID, "EventID/I");
  weightsTree->Branch("isWaterConfig", &isWaterConfig, "isWaterConfig/I");
  //	weightsTree->Branch("ShowerMedianWidth", &ShowerMedianWidth,
  //"ShowerMedianWidth/D"); 	weightsTree->Branch("ShowerEDepFraction",
  //&ShowerEDepFraction, "ShowerEDepFraction/D");
  //weightsTree->Branch("cut12", &cut12, "cut12/I");
  //weightsTree->Branch("cut13", &cut13, "cut13/I");
  for (int igraph = 0; igraph < (int)param_graphs.size(); igraph++)
    weightsTree->Branch(Form("%sGraph", paramnames[igraph].c_str()), "TGraph",
                        &(param_graphs[igraph]), 256000, 0);

  Int_t Entries = defaultTree->GetEntries();
  std::cout << "NRooTrackerVtxTree->GetEntries() = " << Entries << std::endl;

  std::cout << "loop over events" << std::endl;
  for (int ievt = 0; ievt < Entries; ievt++)
  //		for(int ievt=0; ievt<2000; ievt++)
  {
    Double_t weight = 0.0;
    defaultTree->GetEntry(ievt);
    NRooTrackerVtxTree->GetEntry(RooVtxEntry);
    ND::NRooTrackerVtx *vtx = NULL;
    if (accum_level > 9 &&
        HSMTrackLayers >
            13) ///(cut0&&cut1&&cut2&&cut5)//accum_level>9)//cut0&&cut1&&cut2&&cut3&&cut4&&cut6&&cut7&&cut8&&cut9&&cut10&&cut11&&HSMTrackLayers>14)//&&cut12&&cut13&&HSMTrackLayers>13&&TSHitFracOverShower<0.999)
    {

      //			if((std::abs(reacCode)>10&&std::abs(reacCode)<14)||std::abs(reacCode)==1)
      //				fout<<"EventID: "<<EventID<<" reacCode:
      //"<<reacCode<<std::endl; 			fout<<"Event
      //"<<ievt<<std::endl; 			std::cout<<"Event "<<ievt<<std::endl;
      //			std::cout<<"NVtx = "<<NVtx<<std::endl;
      for (int j = 0; j < NVtx; j++) {
        vtx = (ND::NRooTrackerVtx *)nRooVtxs->At(j);
        if (vtx && vtx->TruthVertexID == TruthVertexID) {
          //					std::cout<<"foundvtx
          //"<<ievt<<std::endl; 					fout<<"  "<<"foundvtx
          //"<<std::endl;
          break; // stop when found
        }
        vtx = NULL;
      }
      if (vtx && vtx->TruthVertexID == TruthVertexID) {
        for (int ipara = 0; ipara < (int)SystParams.size(); ipara++) {
          // reset
          // for (int jp = 0; jp < (int)SystParams.size(); jp++)
          //   rw.Systematics().SetTwkDial(SystParams[jp], 0);
          T2KRW->Reset();
          //LP: This is awful and clunky but I really don't understand how the weight
          // storer works...
          std::map<std::string, double> pvals;
          for(auto &p : SystParams){
            pvals[T2KRW->DialAsString(p)] = T2KRW->GetDial_To_Value(p);
          }

          // end of reset
          t2krew::T2KSyst_t tweakParam = SystParams[ipara];
          for (int itweak = 0; itweak < (int)tweakindices[ipara].size();
               itweak++) {
            
            //LP: Set the dial value in number of sigma tweaks
            T2KRW->SetDial_NumberOfSigmas(tweakParam, tweakindices[ipara][itweak]);
            //LP: Reconfigure to calculate the parameter value internally
            T2KRW->Reconfigure();
            //LP: Get the parameter value to check that its sensible
            double param_val = T2KRW->GetDial_To_Value(tweakParam);

            //LP: If the parameter value is out of bounds, clamp it directly to the bound
            if (param_val < lbs[ipara]){
              T2KRW->SetDial_To_Value(tweakParam,lbs[ipara]);
              T2KRW->Reconfigure();
            }
            else if (param_val > ubs[ipara]){
              T2KRW->SetDial_To_Value(tweakParam,ubs[ipara]);
              T2KRW->Reconfigure();
            }

            param_val = T2KRW->GetDial_To_Value(tweakParam);
            pvals[T2KRW->DialAsString(tweakParam)] = param_val;


            storer->NewSystSet(pvals);
            weight = T2KRW->CalcWeight(t2krew::Event::Make(vtx)); //(basevtx);
            // if(std::abs(reacCode)>10&&std::abs(reacCode)<14)
            //						if((std::abs(reacCode)>10&&std::abs(reacCode)<14)||std::abs(reacCode)==1)
            //							fout<<" "<<paramnames[ipara]<<"
            //at
            //"<<tweakindices[ipara][itweak]*sigmas[ipara]+nominals[ipara]<<"(tweakval="<<tweakval<<")"<<"
            // with weight = "<<weight<<std::endl; 						fout<<"
            // weight:
            //"<<weight<<std::endl;
            storer->AddWeight(weight);
            param_graphs[ipara]->SetPoint(
                itweak,
                param_val,
                weight);
          }
        }
      }
      weightsTree->Fill();
    } // end of selection
  }   // end of loop over events

  foutput->Write();
  storer->SaveToFile();

  return 0;
}
