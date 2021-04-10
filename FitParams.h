#ifndef FITPARAMS_H
#define FITPARAMS_H

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <string>
#include <unordered_map>

#include "TROOT.h"
#include "TFile.h"
#include "TBranch.h"
#include "TLine.h"
#include "TString.h"
#include "TMath.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2D.h"
#include "TMatrixD.h"
#include "TMatrixDSym.h"
#include "TVector3.h"
#include "TVectorD.h"
#include "TCanvas.h"
#include "TColor.h"

//#include "DataTypes.h"
//#include "DataTypes.cxx"

class FitParams{

public:
	FitParams();
	~FitParams();

	enum{
		kSigWt,
		kXsec,
		kFlux,
		kDet,
		kSampleCon,
		kLast
	};

	bool sigwt_params;
	bool xsec_params;
	bool flux_params;
	bool det_params;
	bool samplecon_params;

	Int_t nParams;
	std::vector<std::string> ParamNames;
	std::unordered_map<std::string, int> ParamNamesMap;
	std::vector<double> nominalValues;
	std::vector<double> priorValues;
	std::vector<double> sigmaValues;
	std::vector<double> lBoundValues;
	std::vector<double> uBoundValues;

	Int_t nSigWtParams;
	Int_t nXsecParams;
	Int_t nFluxParams;
	Int_t nDetParams;// to save time when searching 

	int NMAXPARS;

	TMatrixDSym* covariance;
	TMatrixDSym* covarianceI;
	TMatrixDSym* correlation;
	TMatrixDSym* correlationI;

	TAxis* fluxbins_nd_numode_numu;
	TAxis* fluxbins_nd_numode_numub;
	TAxis* fluxbins_nd_numode_nue;
	TAxis* fluxbins_nd_numode_nueb;

	TAxis* fluxbins_nd_anumode_numu;
	TAxis* fluxbins_nd_anumode_numub;
	TAxis* fluxbins_nd_anumode_nue;
	TAxis* fluxbins_nd_anumode_nueb;

	void FillFitParams();
	void FillFitParams(Int_t param_type);
	void SetCovarianceI();//inverse
	void SetCorrelation();
	void SetCorrelationI();

	Int_t GetDim() const {return nParams;}
	void GetParamNames(std::vector<std::string> &params)const;
	void GetInitFitParams(std::vector<double> &params)const;
	void GetPriorFitParams(std::vector<double> &params)const;
	void GetSigmaFitParams(std::vector<double> &params)const;
	void GetLowerBoundParams(std::vector<double> &params)const;
	void GetUpperBoundParams(std::vector<double> &params)const;
	void GetCovariance(TMatrixDSym *Cov)const{*Cov = *covariance;}//why don't return the pointer covariance directly instead of doing copy here
	void GetCovarianceI(TMatrixDSym *iCov)const{*iCov = *covarianceI;}
	void GetCorrelation(TMatrixDSym *Corr)const{*Corr = *correlation;}
	void GetCorrelationI(TMatrixDSym *iCorr)const{*iCorr = *correlationI;}

	int GetNeutrinoEnergyBinIndex(int numode, int nupdg, double Enu) const; //numode: 1FHC, 0RHC
	int GetParamIndexFromExactName(std::string name) const; 

	std::vector<int> GetParamIndicesFromName(std::string partname) const;// return indices of parameters whose name contain the argument partname here

	std::vector<int> GetEMShowerMedianWidthScaleIndices() const;// return scale indices in all config and in other program to decide which config to choose based on the event 
	std::vector<int> GetHadronShowerMedianWidthScaleIndices() const;

	static const double EM_SCALE_SHOWER_ECAL;
	static const double EM_SCALE_SHOWER_WTWATERIN;
	static const double EM_SCALE_SHOWER_WTWATEROUT;

	static const double EM_SCALE_TRACK_ECAL;
	static const double EM_SCALE_TRACK_WTWATERIN;
	static const double EM_SCALE_TRACK_WTWATEROUT;

};




#endif
