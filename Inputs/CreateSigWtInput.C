#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "TFile.h"
#include "TMatrixD.h"
#include "TMatrixDSym.h"
#include "TObjArray.h"
#include "TTree.h"
#include "TBranch.h"

void CreateSigWtInput(){ //structure of input param tree may be changed later. Use this form for now to make the fitter run as soon as possible

	bool _debug = true;

	const int NConfig = 4;//waterin_FHC, water-out_FHC, waterin_RHC, waterout_RHC
	const int NBins = 5;  // # of bins in true total kin space in each config
	const int nParams_perbin = 2;//in each bin, nue-onwater, nue_notwater, nuebar_onwater, nuebar_notwater
	int nParams = NBins*nParams_perbin;//*NConfig; 

	std::vector<std::string> param_name;
	std::vector<double> nominal;
	std::vector<double> prior;
	std::vector<double> sigma;
	std::vector<double> lb;
	std::vector<double> ub;

//	param_name.resize(nParams);
//	sigma.resize(nParams);
//	nominal.resize(nParams);
//	prior.resize(nParams);
//	lb.resize(nParams);
//	ub.resize(nParams);
	TMatrixDSym cov(nParams);

	std::string basenames[nParams_perbin] = {"ksigwt_nueCC_onwater", "ksigwt_nueCC_notwater"};//, "ksigwt_nuebarCC_onwater", "ksigwt_nuebarCC_notwater"};
//	std::string configname[NConfig] = {"waterin_FHC", "waterout_FHC", "waterin_RHC", "waterout_RHC"};

	//fill config by config
//	for(int ic=0; ic<NConfig; ic++)
//	{
		for(int ib=0; ib<NBins; ib++)
		{
			for(int ip=0; ip<nParams_perbin; ip++)
			{
				std::string name = basenames[ip]+"_bin"+std::to_string(ib+1);//+"_"+configname[ic];
				param_name.push_back(name);
				nominal.push_back(1);
				prior.push_back(1);
				sigma.push_back(1);
				lb.push_back(0);
				ub.push_back(10);
			}
		}
//	}	

	//the covariance matrix
	for(int i=0; i<nParams; i++){
		for(int j=0; j<nParams; j++){
			if(i==j)
				cov(i,j) = sigma[i]*sigma[i];
		else
			cov(i,j) = 0;
	  	}
	}

	if (_debug){
		std::cout << "nParams : " << nParams << std::endl;
		for(int i = 0; i< nParams; i++){
			std::cout << i << " " << param_name[i] << " " << nominal[i] << " " << prior[i] << " " << lb[i] << " " << ub[i] << std::endl;
		}
		cov.Print();
	}


	TFile *outF = new TFile("sigwtparam_input.root","recreate");
	TTree *outT = new TTree("sigWtParams","sig wt parameters");

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
