//Make sure the values are consistent w/ CreateT2KReweightInput.C used to create splines for shape parameters
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "TMath.h"
#include "TFile.h"
#include "TMatrixDSym.h"
#include "TObjArray.h"
#include "TAxis.h"
#include "TVectorD.h"
#include "TTree.h"

void CreateXsecInputUsingBANFFPrefit();

void CreateXsecInput(){

  bool useBANFFPrefit = false;

  if(useBANFFPrefit){
    CreateXsecInputUsingBANFFPrefit();
    exit(0);
  }

  Int_t nParams=0;
  std::vector<std::string> param_name; 
  std::vector<double> prior; 
  std::vector<double> sigma;
  std::vector<double> nominal;
  std::vector<double> lb; 
  std::vector<double> ub;

  param_name.push_back("MaCCQE");
  nominal.push_back(1.0); // 1.2 unnorm
  prior.push_back(1.0); // 1.2
  sigma.push_back(0.34); // 0.41/1.2 overriding the default BANFF values
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;
  
  param_name.push_back("pF_C");
  nominal.push_back(1.0);  // 217
  prior.push_back(1.0); //217
  sigma.push_back(0.143); // 31/217 overriding the prefit BANFF values
  lb.push_back(0.92); //200/217
  ub.push_back(1.27); //275/217
  nParams++;
  
  param_name.push_back("pF_O");
  nominal.push_back(1.0); //225
  prior.push_back(1.0); //225
  sigma.push_back(0.138); // 31/225 overriding the prefit BANFF values
  lb.push_back(0.89); // 200/225
  ub.push_back(1.22); // 275/225
  nParams++;
  
  param_name.push_back("2p2h_norm_nu");
  nominal.push_back(1.0); 
  prior.push_back(1.0);
  sigma.push_back(1.0); 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;

  param_name.push_back("2p2h_norm_nubar");
  nominal.push_back(1.0); 
  prior.push_back(1.0);
  sigma.push_back(1.0); 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;

  param_name.push_back("2p2h_normCtoO");
  nominal.push_back(1.0); 
  prior.push_back(1.0);
  sigma.push_back(0.2); 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;

  param_name.push_back("2p2h_shape_C");
  nominal.push_back(0.0); 
  prior.push_back(0.0);
  sigma.push_back(3.0); 
  lb.push_back(-1.0);
  ub.push_back(1.0);
  nParams++;  

  param_name.push_back("2p2h_shape_O");
  nominal.push_back(0.0); 
  prior.push_back(0.0);
  sigma.push_back(3.0); 
  lb.push_back(-1.0);
  ub.push_back(1.0);
  nParams++;
  
  param_name.push_back("BeRPA_A");
  nominal.push_back(0.59); 
  prior.push_back(0.59);
  sigma.push_back(0.118); 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;

  param_name.push_back("BeRPA_B");
  nominal.push_back(1.05); 
  prior.push_back(1.05);
  sigma.push_back(0.21); 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;

  param_name.push_back("BeRPA_D");
  nominal.push_back(1.13); 
  prior.push_back(1.13);
  sigma.push_back(0.1695); 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;

  param_name.push_back("BeRPA_E");
  nominal.push_back(0.88); 
  prior.push_back(0.88);
  sigma.push_back(0.352); 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;
  
  param_name.push_back("CA5");
  nominal.push_back(1.0); //1.01
  prior.push_back(0.95); //0.96/1.01
  sigma.push_back(0.15); // 0.15/1.01 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;
  
  param_name.push_back("MaRES");
  nominal.push_back(1.0); //0.95
  prior.push_back(1.13); // 1.07/0.95
  sigma.push_back(0.16); // 0.15/0.95 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;
  
  param_name.push_back("ISO_BKG");
  nominal.push_back(1.0); // 1.30
  prior.push_back(0.74); //0.96/1.30
  sigma.push_back(0.31); // 0.4/1.30 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;

  param_name.push_back("nue_numu");
  nominal.push_back(1.0); 
  prior.push_back(1.0);
  sigma.push_back(0.028); 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;

  param_name.push_back("nuebar_numubar");
  nominal.push_back(1.0); 
  prior.push_back(1.0);
  sigma.push_back(0.028); 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;
  
  param_name.push_back("CC_DIS");
  nominal.push_back(0.0); 
  prior.push_back(0.0);
  sigma.push_back(0.40); 
  lb.push_back(-10.0);
  ub.push_back(10.0);
  nParams++;

  param_name.push_back("CC_Coh_C");
  nominal.push_back(1.0); 
  prior.push_back(1.0);
  sigma.push_back(0.3); 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;

  param_name.push_back("CC_Coh_O");
  nominal.push_back(1.0); 
  prior.push_back(1.0);
  sigma.push_back(0.3); 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;
  
  param_name.push_back("NC_1gamma");
  nominal.push_back(1.0); 
  prior.push_back(1.0);
  sigma.push_back(1.0); 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;

  param_name.push_back("NC_other_near");
  nominal.push_back(1.0); 
  prior.push_back(1.0);
  sigma.push_back(0.3); 
  lb.push_back(0.0);
  ub.push_back(10.0);
  nParams++;
  
  param_name.push_back("FSI_INEL_LO");
  nominal.push_back(0.0); 
  prior.push_back(0.0);
  sigma.push_back(0.41); 
  lb.push_back(-10.0);
  ub.push_back(10.0);
  nParams++;
  
  param_name.push_back("FSI_INEL_HI");
  nominal.push_back(0.0); 
  prior.push_back(0.0);
  sigma.push_back(0.34); 
  lb.push_back(-10.0);
  ub.push_back(10.0);
  nParams++;
  
  param_name.push_back("FSI_PI_PROD");
  nominal.push_back(0.0); 
  prior.push_back(0.0);
  sigma.push_back(0.50); 
  lb.push_back(-10.0);
  ub.push_back(10.0);
  nParams++;
    
  param_name.push_back("FSI_PI_ABS");
  nominal.push_back(0.0); 
  prior.push_back(0.0);
  sigma.push_back(0.41); 
  lb.push_back(-10.0);
  ub.push_back(10.0);
  nParams++;
  
  param_name.push_back("FSI_CEX_LO");
  nominal.push_back(0.0); 
  prior.push_back(0.0);
  sigma.push_back(0.57); 
  lb.push_back(-10.0);
  ub.push_back(10.0);
  nParams++;
  
  param_name.push_back("FSI_CEX_HI");
  nominal.push_back(0.0); 
  prior.push_back(0.0);
  sigma.push_back(0.28); 
  lb.push_back(-10.0);
  ub.push_back(10.0);
  nParams++;

  //Create the covariance matrix
  //  TMatrixD cov(nParams,nParams);
   TMatrixDSym cov(nParams);
  //Initialize diagonal terms with sigma^2 and off-diagonal with 0

  for(Int_t iRow = 0; iRow < nParams; iRow++){
    for(Int_t iCol = 0; iCol < nParams; iCol++){
      if(iRow == iCol){
	cov(iRow, iCol) = sigma[iRow] * sigma[iRow];
      }
      else
	cov(iRow, iCol) = 0.0;
    }
  }

  //Hardcode the correlations between other parameters

  //2p2h Shape Correlations = 30% (2.7/(3*3) = 0.3)
  cov(6 ,7) = cov (7, 6) = 2.7;

  //1pi Resonance Parameters Covariances
  cov(12,13) = cov(13,12) = -0.01946;
  cov(12,14) = cov(14,12) = -0.01417;
  cov(13,14) = cov(14,13) = -0.0004858;

  //Nue-Numu and Nuebar-Numubar - 2% anti-correlation
  cov(15,16) = cov(16,15) = -0.0004;
  //cov(15,16) = cov(16,15) = -0.000016;

  //CC Coherent on C and O (fully correlated)
  cov(18,19) = cov(19,18) = 0.08999 ;

  //According to BANFF
  //FSI Parameter Correlations :
  cov(22,23) = cov(23,22) = -0.002779;
  cov(22,24) = cov(24,22) = 0;
  cov(22,25) = cov(25,22) = 0.02251;
  cov(22,26) = cov(26,22) = 0.005;
  cov(22,27) = cov(27,22) = 0;
  cov(23,24) = cov(24,23) = -0.1677;
  cov(23,25) = cov(25,23) = -0.001265;
  cov(23,26) = cov(26,23) = -0.002108;
  cov(23,27) = cov(27,23) = -0.0939;
  cov(24,25) = cov(25,24) = 0;
  cov(24,26) = cov(26,24) = 0;
  cov(24,27) = cov(27,24) = 0.14;
  cov(25,26) = cov(26,25) = -0.002277;
  cov(25,27) = cov(27,25) = 0;
  cov(26,27) = cov(27,26) = 0;

  /* According to TN-315
  //FSI Parameter Covariance :
  cov(22,23) = cov(23,22) = 0; 
  cov(22,24) = cov(24,22) = -0.002779;
  cov(22,25) = cov(25,22) = 0.02251;
  cov(22,26) = cov(26,22) = 0.005;
  cov(22,27) = cov(27,22) = 0;
  cov(23,24) = cov(24,23) = -0.1677;
  cov(23,25) = cov(25,23) = 0;
  cov(23,26) = cov(26,23) = 0;
  cov(23,27) = cov(27,23) = 0.14;
  cov(24,25) = cov(25,24) = -0.001265;
  cov(24,26) = cov(26,24) = -0.002108;
  cov(24,27) = cov(27,24) = -0.0939;
  cov(25,26) = cov(26,25) = -0.002277;
  cov(25,27) = cov(27,25) = 0;
  cov(26,27) = cov(27,26) = 0;
  */
  cov.Print();
  
  for (std::size_t i = 0; i < prior.size();i++){
    std::cout  << std::setw(2) << left <<  i << "  " << std::setw(20) << param_name[i] << " nom : " << std::setw(10) <<  nominal[i] << " prior : " << std::setw(10) <<  prior[i] << " sigma : " << std::setw(10) <<  sigma[i] << " lb: " << std::setw(10) << lb[i] << " ub: " << std::setw(10) <<  ub[i] << std::endl;
  }

  TFile *outF = new TFile("Xsecparam_input.root","recreate");
  TTree *outT = new TTree("XsecParams","xsec parameters");

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

void CreateXsecInputUsingBANFFPrefit(){

  TFile *inF = new TFile("xsec_covariance_2017b_NOMINAL_v4.root","open"); //2017oaPreBANFFValues

  TMatrixDSym* inMat_in = (TMatrixDSym*)inF->Get("xsec_cov");
  TMatrixDSym inMat = *inMat_in;
  
  TObjArray* param_names_in = (TObjArray*)inF->Get("xsec_param_names");
  TObjArray param_names = *param_names_in;
  
  TVectorD* nominal_vals = (TVectorD*)inF->Get("xsec_param_nom");
  TVectorD* nominal_unnorm_vals = (TVectorD*)inF->Get("xsec_param_nom_unnorm");
  TVectorD* prior_vals = (TVectorD*)inF->Get("xsec_param_prior");
  TVectorD* prior_unnorm_vals = (TVectorD*)inF->Get("xsec_param_prior_unnorm");
  TVectorD* lb_vals = (TVectorD*)inF->Get("xsec_param_lb");
  TVectorD* ub_vals = (TVectorD*)inF->Get("xsec_param_ub");

  Int_t nParams=0;
  std::vector<std::string> param_name; 
  std::vector<double> prior; 
  std::vector<double> sigma;
  std::vector<double> nominal;
  std::vector<double> lb; 
  std::vector<double> ub;

  nParams = nominal_vals->GetNrows();
  param_name.resize(nParams);
  sigma.resize(nParams);
  nominal.resize(nParams);
  prior.resize(nParams);
  lb.resize(nParams);
  ub.resize(nParams);

	std::unordered_set<std::string> paramters{"MAQE", "MARES", };
	std::unordered_map<std::string, std::pair<int, int>> paramtersidx;


  for(int i=0; i<nParams; i++){
    param_name[i] = param_names.At(i)->GetName();
    nominal[i] = (*nominal_vals)(i);
    prior[i] = (*prior_vals)(i);
    lb[i] = (*lb_vals)(i);
    ub[i] = (*ub_vals)(i);
  }

  TMatrixDSym cov(nParams);
  
  for(Int_t i=0; i<nParams ;i++){
    for(Int_t j=0; j<nParams ;j++){
      cov(i,j) = inMat(i,j);
    }
  }
  
  cov.Print();
  for (Int_t i=0; i<nParams; i++){
    double diag = cov(i,i);
    if (diag != 0) sigma[i] = TMath::Sqrt(diag);
    else std::cerr << "WHY IS IT O ?? " << diag  << std::endl;
  }

  for (std::size_t i = 0; i < prior.size();i++){
    std::cout  << setw(2) <<  i << "  " << setw(20) << param_name[i] << " nom : " << setw(10) <<  nominal[i] << " prior : " << setw(10) <<  prior[i] << " sigma : " << setw(10) <<  sigma[i] << " lb: " << setw(10) << lb[i] << " ub: " << setw(10) <<  ub[i] << std::endl;
  }
    
  delete inF;

  TFile *outF = new TFile("Xsecparam_input.root","recreate");
  TTree *outT = new TTree("XsecParams","xsec parameters");

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
