//Make sure the values are consistent w/ CreateT2KReweightInput.C used to create splines for shape parameters
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <unordered_map>

#include "TMath.h"
#include "TFile.h"
#include "TMatrixDSym.h"
#include "TObjArray.h"
#include "TAxis.h"
#include "TVectorD.h"
#include "TTree.h"

void CreateXsecInputUsingBANFFPrefit();

void CreateXsecInput(){

	//pre-process, read BANFF prefit
	TFile *inF = new TFile("xsec_covariance_2020a_v6.root","open"); //2017oaPreBANFFValues

	TObjArray* param_names_in = (TObjArray*)inF->Get("xsec_param_names");
	TObjArray param_names = *param_names_in;

	TVectorD* nominal_vals = (TVectorD*)inF->Get("xsec_param_nom");
	TVectorD* nominal_unnorm_vals = (TVectorD*)inF->Get("xsec_param_nom_unnorm");
	TVectorD* prior_vals = (TVectorD*)inF->Get("xsec_param_prior");
	TVectorD* prior_unnorm_vals = (TVectorD*)inF->Get("xsec_param_prior_unnorm");
	TVectorD* lb_vals = (TVectorD*)inF->Get("xsec_param_lb");
	TVectorD* ub_vals = (TVectorD*)inF->Get("xsec_param_ub");
	TMatrixDSym* inMat_in = (TMatrixDSym*)inF->Get("xsec_cov");
	TMatrixDSym inMat = *inMat_in;

	std::unordered_map<std::string, int> preparamtersidx;

	int npreParams = nominal_vals->GetNrows();
	for(int i=0; i<npreParams; i++){
		std::string name = param_names.At(i)->GetName();
		preparamtersidx[name] = i;
	}
	///////

	std::vector<std::string> xsecparams{"MAQE", "MARES", "CA5", "ISO_BKG", "CC_BY_DIS", "CC_BY_MPi", "CC_AGKY_Mult",  "NC_Coh", "NC_other_near", "NC_1gamma", "FEFABS", "FEFCX", "FEFQE", "FEFQEH", "FEFCXH", "FEFINEL"}; //>=c++11 needed 

	Int_t nParams=0; //# of parameters, including fst para
	Int_t nFSIParam = 6;
	std::vector<std::string> param_name; 
	std::vector<double> prior; 
	std::vector<double> sigma;
	std::vector<double> nominal;//unnorm
	std::vector<double> lb; 
	std::vector<double> ub;

	for(int i=0; i<xsecparams.size(); i++)
	{
		if(preparamtersidx.find(xsecparams[i])==preparamtersidx.end())
		{
			std::cout<<"A XSEC Parameter "<<xsecparams[i]<<" is NOT from Input ROOT. Please check and make sure it's considered"<<std::endl;
			continue;
		}
		int idx = preparamtersidx[xsecparams[i]];
		param_name.push_back(xsecparams[i]);
		nominal.push_back((*nominal_unnorm_vals)(idx));
		prior.push_back((*prior_unnorm_vals)(idx));
		sigma.push_back(TMath::Sqrt(inMat(idx,idx)));
		lb.push_back((*lb_vals)(idx));
		ub.push_back((*ub_vals)(idx));
		nParams++;
	}

	TMatrixDSym cov(nParams);
	for(int i=0; i<nParams; i++)
	{
		int prei = preparamtersidx[param_name[i]];
		for(int j=i; j<nParams; j++)
		{
			int prej = preparamtersidx[param_name[j]];
			cov(i,j) = inMat(prei, prej);
		}
	}

	cov.Print();
  
	for (std::size_t i = 0; i < prior.size();i++){
		std::cout  << std::setw(2) << left <<  i << "  " << std::setw(20) << param_name[i] << " nom : " << std::setw(10) <<  nominal[i] << " prior : " << std::setw(10) 
		<<  prior[i] << " sigma : " << std::setw(10) <<  sigma[i] << " lb: " << std::setw(10) << lb[i] << " ub: " << std::setw(10) <<  ub[i] << std::endl;
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

	std::unordered_map<std::string, int> paramtersidx;


	for(int i=0; i<nParams; i++){
		param_name[i] = param_names.At(i)->GetName();
		paramtersidx[param_name[i]] = i;
		nominal[i] = (*nominal_vals)(i);
		prior[i] = (*prior_vals)(i);
		lb[i] = (*lb_vals)(i);
		ub[i] = (*ub_vals)(i);
	}

	TMatrixDSym cov(nParams);

	for(Int_t i=0; i<nParams ;i++){
		for(Int_t j=0; j<nParams ;j++)
		  cov(i,j) = inMat(i,j);
		
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
