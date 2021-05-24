#ifndef P0DNUEANALYSISLIKELIHOOD_H
#define P0DNUEANALYSISLIKELIHOOD_H
#include <iostream>
#include <string> 

#include <THStack.h>

#include "DataTypes.h"
#include "DataTypes.cxx"
#include "FitParams.h"
#include "FitParams.cxx"
#include "SystematicUncertaintyCorr.h"
#include "SystematicUncertaintyCorr.cxx"

class p0dNuEAnalysisLikelihood
{
private:
/*
	const double _SMWCut_Waterin_FHC ;
	const double _SMWCut_Waterin_RHC ;
	const double _SMWCut_Waterout_FHC;
	const double _SMWCut_Waterout_RHC;
	const double _SCFCut_Waterin_FHC ;//should I just define one variable SCFCut for all as the cut value in the four config is the same
	const double _SCFCut_Waterin_RHC ;
	const double _SCFCut_Waterout_FHC;
	const double _SCFCut_Waterout_RHC;
*/
	static const int _NConfigs = 4;
	int _curNConfigs;

	double _SMWCut[_NConfigs];
	double _SCFCut[_NConfigs];
	int _LayerCut[_NConfigs]; //added on 05/23/2021

	double MCPOT[_NConfigs];
	double dataPOT[_NConfigs];

	//below two added on 03/17/2021 for SaveNSignal
	FitParams fitparam;
	Binning binobject;

public:
	//***********Constructor***********//
	p0dNuEAnalysisLikelihood();
	double operator()(const std::vector<double>& fCurrParams);
	
	void Init(int nconfigs, std::vector<std::string>& mcWaterinFHC, std::vector<std::string>& mcSplineWaterinFHC, double mcPOTWaterin, std::vector<std::string>& mcWaterOutFHC, std::vector<std::string>& mcSplineWaterOutFHC, double mcPOTWaterout, std::vector<std::string>& dataWaterinFHC, double dataPOTWaterin, std::vector<std::string>& dataWaterOutFHC, double dataPOTWaterout);
//	void Init(int nconfigs, std::string mcWaterinFHC, double mcWaterinFHCPOT, std::string mcWateroutFHC, double mcWateroutFHCPOT, std::string mcWaterinRHC, double mcWaterinRHCPOT, std::string mcWateroutRHC, double mcWateroutRHCPOT, std::string dataWaterinFHC, double dataWaterinFHCPOT,  std::string dataWateroutFHC, double dataWateroutFHCPOT,  std::string dataWaterinRHC, double dataWaterinRHCPOT, std::string dataWateroutRHC, double dataWateroutRHCPOT,  std::string splineWaterinFHC, std::string splineWateroutFHC, std::string splineWaterinRHC, std::string splineWateroutRHC);
  
	void ResetMCHistograms();
	bool FillMCHistograms(const std::vector<double>& params);//return false if there're evts whose weights are <0, considering both signal enriched sample and sidebands
//	void FillMCHistograms(const std::vector<double>& params);
	void FillNominalMCHistograms();//const std::vector<double>& params);

	void DrawSignalSampleStack(int configid);
	void DrawNCBKControlSampleStack(int configid);
	void DrawNumuControlSampleStack(int configid);
	THStack* GetSignalSampleStack(int configid, std::string differentiator="");
	THStack* GetSignalSampleStack(int configid, const std::vector<double>& params, std::string differentiator="");
	THStack* GetNCBKControlSampleStack(int configid, const std::vector<double>& params, std::string differentiator="");
	THStack* GetNumuControlSampleStack(int configid, const std::vector<double>& params, std::string differentiator="");

	//added 03/17/2021, save the sigwt of onwater and not water
	void SaveNSignal(const std::vector<double>& params, std::vector<double>& sigwtonwater, std::vector<double>& sigwtnotwater)
	{
		if(!fitparam.sigwt_params)
			return ;
		float signal_on_water = 0;
		float signal_not_water = 0;
		int N = binobject.GetNBins();
		if(sigwtonwater.size()!=N)
			sigwtonwater.resize(N, 0);
		if(sigwtnotwater.size()!=N)
			sigwtnotwater.resize(N, 0);
		for(int i=1; i<N+1; i++)
		{
			std::string nameonwater = "ksigwt_nueCC_onwater_bin"+std::to_string(i);//+"_waterin_FHC";
			sigwtonwater[i-1] = params[fitparam.GetParamIndexFromExactName(nameonwater)];
			std::string namenotwater = "ksigwt_nueCC_notwater_bin"+std::to_string(i);//+"_waterin_FHC";
			sigwtnotwater[i-1] = params[fitparam.GetParamIndexFromExactName(namenotwater)];
		}

	}
//	//added 04/14/2021, save all params
//	void SaveNSignal(const std::vector<double>& params, std::vector<double>& sigwtonwater, std::vector<double>& sigwtnotwater)
//	{
//		if(!fitparam.sigwt_params)
//			return ;
//		float signal_on_water = 0;
//		float signal_not_water = 0;
//		int N = binobject.GetNBins();
//		if(sigwtonwater.size()!=N)
//			sigwtonwater.resize(N, 0);
//		if(sigwtnotwater.size()!=N)
//			sigwtnotwater.resize(N, 0);
//		for(int i=1; i<N+1; i++)
//		{
//			std::string nameonwater = "ksigwt_nueCC_onwater_bin"+std::to_string(i);//+"_waterin_FHC";
//			sigwtonwater[i-1] = params[fitparam.GetParamIndexFromExactName(nameonwater)];
//			std::string namenotwater = "ksigwt_nueCC_notwater_bin"+std::to_string(i);//+"_waterin_FHC";
//			sigwtnotwater[i-1] = params[fitparam.GetParamIndexFromExactName(namenotwater)];
//		}
//
//	}
	// ******** Data ********//
//	DataSets* DataSample;
	//following the sequence of waterinFHC, wateroutFHC, waterinRHC and wateroutRHC	
	TH1D* Data_SS_ReconShowerVisibleEnergy[_NConfigs];
	TH1D* Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[_NConfigs];
	TH1D* Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[_NConfigs];

	// ******** MC ********//
	//following the sequence of waterinFHC, wateroutFHC, waterinRHC and wateroutRHC	
//	MCSimulation::MCEventsVect MCSamples_allConfigs[_NConfigs];
	MCSimulation* MCSamples_allConfigs[_NConfigs];

	TH1D* MC_SS_ReconShowerVisibleEnergy[_NConfigs];
	TH1D* MC_SS_Signal_ReconShowerVisibleEnergy[_NConfigs];
	TH1D* MC_SS_Background_ReconShowerVisibleEnergy[_NConfigs];

	TH1D* MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[_NConfigs];
	TH1D* MC_NCResonantPi0Sideband_Signal_ReconShowerVisibleEnergy[_NConfigs];
	TH1D* MC_NCResonantPi0Sideband_Background_ReconShowerVisibleEnergy[_NConfigs];

	TH1D* MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[_NConfigs];
	TH1D* MC_numuCCDISMultiPionSideband_Signal_ReconShowerVisibleEnergy[_NConfigs];
	TH1D* MC_numuCCDISMultiPionSideband_Background_ReconShowerVisibleEnergy[_NConfigs];

//	TH1D* MC_SS_TrueTotKinEnergy[_NConfigs];
//	TH1D* MC_SS_Signal_TrueTotKinEnergy[_NConfigs];
//	TH1D* MC_SS_Background_TrueTotKinEnergy[_NConfigs];
//
//	TH1D* MC_NCResonantPi0Sideband_TrueTotKinEnergy[_NConfigs];
//	TH1D* MC_NCResonantPi0Sideband_Signal_TrueTotKinEnergy[_NConfigs];
//	TH1D* MC_NCResonantPi0Sideband_Background_TrueTotKinEnergy[_NConfigs];
//
//	TH1D* MC_numuCCDISMultiPionSideband_TrueTotKinEnergy[_NConfigs];
//	TH1D* MC_numuCCDISMultiPionSideband_Signal_TrueTotKinEnergy[_NConfigs];
//	TH1D* MC_numuCCDISMultiPionSideband_Background_TrueTotKinEnergy[_NConfigs];

	// ******** Parameters ********//
//	FitParams fitParams;
	std::vector<std::string> fParamNames;
	std::vector<double> fInitParams;
	std::vector<double> fPriorParams;
	std::vector<double> fSigmaParams;
	std::vector<double> fLowerBound;
	std::vector<double> fUpperBound;
	TMatrixDSym *correlation;
	TMatrixDSym *covariance;
	TMatrixDSym *covarianceI;//inverted covariance matrix

	// ******** corrections applied to each event ********//
	SystematicUncertaintyCorr Correction;

	double GetSMWCutValue(int iconfig) const {return _SMWCut[iconfig];}
	double GetSCFCutValue(int iconfig) const {return _SCFCut[iconfig];}
	
};


#endif
