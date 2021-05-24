#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "TMath.h"
#include "TFile.h"
#include "TMatrixDSym.h"
#include "TObjArray.h"
#include "TAxis.h"
#include "TVectorD.h"
#include "TTree.h"

void CreateFluxInput(){
  
	//use the flux binning used in banff
	//later if I need to change the binning and regenerate cov of flux, then move to replica one which has more finer bining than this one
	TFile *inF = new TFile("../flux/flux_covariance_banff_13av4_run1-9d_v2.root");

	TMatrixDSym* inMat_in = (TMatrixDSym*)inF->Get("total_flux_cov");
	TMatrixDSym inMat = *inMat_in;
	//FHC  
	TAxis* nu_numu  = (TAxis*)inF->Get("nd5_numode_numu_bins");
	TAxis* nu_nue   = (TAxis*)inF->Get("nd5_numode_nue_bins");
	TAxis* nu_numub = (TAxis*)inF->Get("nd5_numode_numub_bins");
	TAxis* nu_anue  = (TAxis*)inF->Get("nd5_numode_nueb_bins");
	//RHC
	TAxis* anu_numu  = (TAxis*)inF->Get("nd5_anumode_numu_bins");
	TAxis* anu_nue   = (TAxis*)inF->Get("nd5_anumode_nue_bins");
	TAxis* anu_numub = (TAxis*)inF->Get("nd5_anumode_numub_bins");
	TAxis* anu_anue  = (TAxis*)inF->Get("nd5_anumode_nueb_bins");
  
	Int_t nParams=0;
	std::vector<std::string> param_name;   
	std::vector<double> prior; 
	std::vector<double> sigma;
	std::vector<double> nominal;
	std::vector<double> lb;
	std::vector<double> ub;

	Int_t nnu_numuBins = nu_numu->GetNbins();
	Int_t nnu_nueBins = nu_nue->GetNbins();
	Int_t nnu_numubBins = nu_numub->GetNbins();
	Int_t nnu_nuebBins = nu_anue->GetNbins();

	Int_t nanu_numuBins = anu_numu->GetNbins();
	Int_t nanu_nueBins = anu_nue->GetNbins();
	Int_t nanu_numubBins = anu_numub->GetNbins();
	Int_t nanu_nuebBins = anu_anue->GetNbins();
	nParams = nnu_numuBins + nnu_numubBins + nnu_nueBins + nnu_nuebBins ;//+ 8 ; //+8 for under and overflow bin
//			+nanu_numuBins + nanu_numubBins + nanu_nueBins + nanu_nuebBins; //just consider FHC for now

	std::cout << "Total # of pars : " << nParams << std::endl;

	param_name.resize(nParams);
	sigma.resize(nParams);
	nominal.resize(nParams);
	prior.resize(nParams);
	lb.resize(nParams);
	ub.resize(nParams);
	//  TMatrixD cov(nParams,nParams);
	TMatrixDSym cov(nParams);

	for(Int_t i=0; i<nParams ;i++){
		for(Int_t j=0; j<nParams ;j++){
	  		cov(i,j) = inMat(i,j);
		}
		sigma[i] = TMath::Sqrt(cov(i,i));
		nominal[i] = 1.0;
		prior[i] = 1.0;
		lb[i] = 0.0;
		ub[i] = 10.0;
	}

	//Fill the param names
	std::string name; 
	int nnuBins = nnu_numuBins+nnu_numubBins+nnu_nueBins+nnu_nuebBins;
	std::cout<<nnu_numuBins<<" "<<nnu_numubBins<<" "<<nnu_nueBins<<" "<<nnu_nuebBins<<std::endl;
	for(Int_t i = 0; i < nParams ; i++){
		if(i<nnu_numuBins){
			name = "nd5_numode_numu_bin"+std::to_string(i+1);
		}
		else if(i<nnu_numuBins+nnu_numubBins){
			name = "nd5_numode_numub_bin"+std::to_string(i-nnu_numuBins+1);
		}
		else if(i<nnu_numuBins+nnu_numubBins+nnu_nueBins){
			name = "nd5_numode_nue_bin"+std::to_string(i-nnu_numuBins-nnu_numubBins+1);
		}
		else if(i<nnu_numuBins+nnu_numubBins+nnu_nueBins+nnu_nuebBins){
			name = "nd5_numode_nueb_bin"+std::to_string(i-nnu_numuBins-nnu_numubBins-nnu_nueBins+1);;
		}
//		else if(i<nnuBins+nanu_numuBins)
//			name = "nd5_anumode_numu_bin"+std::to_string(i-nnuBins+1);
//		else if(i<nnuBins+nanu_numuBins+nanu_numubBins)
//			name = "nd5_anumode_numub_bin"+std::to_string(i-nnuBins-nanu_numuBins+1);
//		else if(i<nnuBins+nanu_numuBins+nanu_numubBins+nanu_nueBins)
//			name = "nd5_anumode_nue_bin"+std::to_string(i-nnuBins-nanu_numuBins-nanu_numubBins+1);
//		else 
//			name = "nd5_anumode_nueb_bin"+std::to_string(i-nnuBins-nanu_numuBins-nanu_numubBins-nanu_nueBins+1);
		param_name[i] = name;
		std::cout<<param_name[i]<<std::endl;
	}
//	param_name[nParams-8] = "nd5_numode_numu_bin0";
//	param_name[nParams-7] = "nd5_numode_numu_bin"+ std::to_string(nnu_numuBins+1);
//	param_name[nParams-6] = "nd5_numode_numub_bin0";
//	param_name[nParams-5] = "nd5_numode_numub_bin"+ std::to_string(nnu_numubBins+1);
//	param_name[nParams-4] = "nd5_numode_nue_bin0";
//	param_name[nParams-3] = "nd5_numode_nue_bin" + std::to_string(nnu_nueBins+1);
//	param_name[nParams-2] = "nd5_numode_nueb_bin0";
//	param_name[nParams-1] = "nd5_numode_nueb_bin" + std::to_string(nnu_nuebBins+1);

  cov.Print();

  for (Int_t i = 0; i < nParams; i++){
    std::cout << i << " " << param_name[i] << " nom :  " << nominal[i] << " prior : " << prior[i] << " sigma : " << sigma[i] << " lb: " << lb[i] << " ub: " << ub[i] << std::endl;
  }
  
  delete inF;

  TFile *outF = new TFile("Fluxparam_input.root","recreate");
  cov.Write("covariance");
  TTree *outT = new TTree("FluxParams","flux parameters");

  outT->Branch("nParams",&nParams,"nParams/I");
  outT->Branch("param_name",&param_name);
  outT->Branch("nominal",&nominal);
  outT->Branch("prior",&prior);
  outT->Branch("sigma",&sigma);
  outT->Branch("lb",&lb);
  outT->Branch("ub",&ub);
  outT->Branch("covariance","TMatrixDSym",&cov);
  outT->Branch("fluxbins_nu_numu", &nu_numu);
  outT->Branch("fluxbins_nu_nue", &nu_nue);
  outT->Branch("fluxbins_nu_numub", &nu_numub);
  outT->Branch("fluxbins_nu_anue", &nu_anue);
  outT->Fill();
  
  outF->Write();
  delete outF;

}
