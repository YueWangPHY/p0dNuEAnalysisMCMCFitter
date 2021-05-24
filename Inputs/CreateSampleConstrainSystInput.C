#include <iostream>
#include <vector>
#include <string>

#include "TFile.h"
#include "TMatrixD.h"
#include "TMatrixDSym.h"
#include "TTree.h"

void CreateSampleConstrainSystInput(){

  bool _debug = true;
  
  TFile *outF = new TFile("sampleconparam_input.root","recreate");
  TTree *outT = new TTree("sampleConParams","sample constrain syst parameters");

  Int_t nParams = 0;
  std::vector<std::string> param_name;
  std::vector<double> nominal;
  std::vector<double> prior;
  std::vector<double> sigma;
  std::vector<double> lb;
  std::vector<double> ub;

  //Fake Muon Decay Probability
  // MC - Data
  param_name.push_back("kSamp_FakeMuDkProb_WaterIn");
  nominal.push_back(0);
  prior.push_back(0.01065);
  sigma.push_back(0.005);
  lb.push_back(-1);
  ub.push_back(1);
  nParams++;

  //Muon Decay Efficiency
  //Prior is (eff_mc - eff_data)/100
  param_name.push_back("kSamp_MuDkEff_WaterIn");
  nominal.push_back(0);
  prior.push_back(0.015);
  sigma.push_back(0.007);
  lb.push_back(-1);
  ub.push_back(1);
  nParams++;

  //Fake Muon Decay Probability
  param_name.push_back("kSamp_FakeMuDkProb_WaterOut");
  nominal.push_back(0);
  prior.push_back(-0.0124);
  sigma.push_back(0.007);
  lb.push_back(-1); //-1 implies difference is 100%
  ub.push_back(1);
  nParams++;

  //Muon Decay Efficiency
  param_name.push_back("kSamp_MuDkEff_WaterOut");
  nominal.push_back(0);
  prior.push_back(-0.023);
  sigma.push_back(0.0085);
  lb.push_back(-1);
  ub.push_back(1);
  nParams++;
  
  //The Covariance Matrix
  //  TMatrixD cov(nParams, nParams);
  TMatrixDSym cov(nParams);

  for(Int_t i=0; i<nParams ;i++){
      for(Int_t j=0; j<nParams ;j++){
	if(i==j)
	  cov(i,j) = sigma[i]*sigma[i];
	else
	    cov(i,j) = 0;
      }
  }

  if (_debug){
    std::cout << "nParams : " << nParams << std::endl;
    for(int i = 0; i< nParams; i++){
      std::cout << i << " " << param_name[i] << " " << nominal[i] << " " << prior[i] << " " << sigma[i] << " " << lb[i] << " " << ub[i] << std::endl;
    }
    
    cov.Print();
  }

  
  outT->Branch("nParams",&nParams,"nParams/I");
  outT->Branch("param_name",&param_name);
  outT->Branch("nominal",&nominal);
  outT->Branch("prior",&prior);
  outT->Branch("sigma",&sigma);
  outT->Branch("lb",&lb);
  outT->Branch("ub",&ub);
  outT->Branch("covariance","TMatrixDSym",&cov);
  outT->Fill();
  
  outF->Write();
  delete outF;
  
}
