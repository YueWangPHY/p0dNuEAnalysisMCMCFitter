#include "p0dNuEAnalysisLikelihood.h"
#include "Utils/pi0RelatedQuanCal.h"



p0dNuEAnalysisLikelihood::p0dNuEAnalysisLikelihood()
{
/*
	_SMWCut_Waterin_FHC  = 24;//probably read them from a parameter file
	_SMWCut_Waterin_RHC  = 29;
	_SMWCut_Waterout_FHC = 24; 
	_SMWCut_Waterout_RHC = 29;
	_SCFCut_Waterin_FHC  = 0.9;
	_SCFCut_Waterin_RHC  = 0.9;
	_SCFCut_Waterout_FHC = 0.9;
	_SCFCut_Waterout_RHC = 0.9;
*/
	_curNConfigs = 2;
//	_NConfigs = 4;//may set as parameter to read from .dat later
	_SMWCut[0]=30; _SMWCut[1]=32; _SMWCut[2]=24; _SMWCut[3]=29;
//	_SMWCut[0]=24; _SMWCut[1]=29; _SMWCut[2]=24; _SMWCut[3]=29; //try with above
	_SCFCut[0]=0.9; _SCFCut[1]=0.9; _SCFCut[2]=0.9; _SCFCut[3]=0.9;
	//added on 05/23/2021
	_LayerCut[0] = 22; _LayerCut[1] = 24; _LayerCut[3] = 18; _LayerCut[4] = 18;	

//	for(int i=0; i<_NConfigs; i++)
	for(int i=0; i<_curNConfigs; i++)
	{
		Data_SS_ReconShowerVisibleEnergy[i] = 0;
		Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[i] = 0;
		Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[i] = 0;

//		MCSamples_allConfigs[i].clear();
		MCSamples_allConfigs[i] = 0;

		MC_SS_ReconShowerVisibleEnergy[i] = 0;
		MC_SS_Signal_ReconShowerVisibleEnergy[i] = 0;
		MC_SS_Background_ReconShowerVisibleEnergy[i] = 0;

		MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[i] = 0;
		MC_NCResonantPi0Sideband_Signal_ReconShowerVisibleEnergy[i] = 0;
		MC_NCResonantPi0Sideband_Background_ReconShowerVisibleEnergy[i] = 0;

		MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[i] = 0;
		MC_numuCCDISMultiPionSideband_Signal_ReconShowerVisibleEnergy[i] = 0;
		MC_numuCCDISMultiPionSideband_Background_ReconShowerVisibleEnergy[i] = 0;

//		MC_SS_TrueTotKinEnergy[i] = 0;
//		MC_SS_Signal_TrueTotKinEnergy[i] = 0;
//		MC_SS_Background_TrueTotKinEnergy[i] = 0;
//
//		MC_NCResonantPi0Sideband_TrueTotKinEnergy[i] = 0;
//		MC_NCResonantPi0Sideband_Signal_TrueTotKinEnergy[i] = 0;
//		MC_NCResonantPi0Sideband_Background_TrueTotKinEnergy[i] = 0;
//
//		MC_numuCCDISMultiPionSideband_TrueTotKinEnergy[i] = 0;
//		MC_numuCCDISMultiPionSideband_Signal_TrueTotKinEnergy[i] = 0;
//		MC_numuCCDISMultiPionSideband_Background_TrueTotKinEnergy[i] = 0;
	}	

    fParamNames.clear();
    fInitParams.clear();
    fPriorParams.clear();
    fSigmaParams.clear();
    fLowerBound.clear();
    fUpperBound.clear();
}


double p0dNuEAnalysisLikelihood::operator()(const std::vector<double>& fCurrParams)
{
    ResetMCHistograms();
    if(!FillMCHistograms(fCurrParams))//if there are negative weights
		return -2e+38;

    double logLikelihood = 0.0;

	//statistical
	//sumoverbins(N_data-N_mc+N_data*log(N_mc/N_data))
//    for(int ic=0; ic<_NConfig; ic++)
    for(int ic=0; ic<_curNConfigs; ic++)
	{
		int nbins = Data_SS_ReconShowerVisibleEnergy[ic]->GetNbinsX();
		if(nbins!= MC_SS_ReconShowerVisibleEnergy[ic]->GetNbinsX())//small check, not complete
		{
			std::cout<<"in cal likelihood, nbins of Data_SS_ReconShowerVisibleEnergy and MC_SS_ReconShowerVisibleEnergy are different"<<std::endl;
			exit(0);
		}
		
		
		for(int ibin=1; ibin<nbins+1; ibin++)//there should be not underflow/overflow events
		{
			double ndata = Data_SS_ReconShowerVisibleEnergy[ic]->GetBinContent(ibin);
			double nmc = MC_SS_ReconShowerVisibleEnergy[ic]->GetBinContent(ibin);

			if(ndata>0&&nmc>0)
				logLikelihood+= (ndata*1.0-nmc*1.0+ndata*std::log(nmc/ndata));
			else if(nmc>0&&ndata==0)
			{
//				nmc = 0.001;
				logLikelihood+= (ndata*1.0-nmc*1.0);//+ndata*std::log(nmc/ndata));
			}
//			else if(ndata==0&&nmc>0)//how to deal with...
//			{
//				ndata = 0.001;
//				logLikelihood+=(
//			}
			else //if(nmc<=0||ndata<0)//shouldn't happen //should ndata==0 happen???
			{
				logLikelihood = -2e+38;//a number randomly choose...
				std::cout<<"ic="<<ic<<" bin"<<ibin<<" has contents: "<<" ndate="<<ndata<<" and nmc="<<nmc<<std::endl;
				break;
			}
			
			
//			logLikelihood+=ndata-nmc;
//			if(ndata>0&&nmc>0)//here it's diff from what in ncpi0, it set nmc=0.001 if nmc<0.001. need further check to decide what to write when ndata or nmc is 0 or very close to 0.
//				logLikelihood+=ndata*std::log(nmc/ndata);
				
//			logLikelihood+=(ndata-nmc)*(nmc-ndata);
//			if(ndata>0&&nmc>0)//here it's diff from what in ncpi0, it set nmc=0.001 if nmc<0.001. need further check to decide what to write when ndata or nmc is 0 or very close to 0.
//				logLikelihood+=0;//ndata*std::log(nmc/ndata);
		}
		
		if(Data_SS_ReconShowerVisibleEnergy[ic]->GetBinContent(0)>0)
			std::cout<<"Data_SS_ReconShowerVisibleEnergy ic="<<ic<<" had contents at bin"<<0<<" ="<<Data_SS_ReconShowerVisibleEnergy[ic]->GetBinContent(0)<<std::endl;
		if(Data_SS_ReconShowerVisibleEnergy[ic]->GetBinContent(nbins+1)>0)
			std::cout<<"Data_SS_ReconShowerVisibleEnergy ic="<<ic<<" had contents at bin"<<nbins+1<<" ="<<Data_SS_ReconShowerVisibleEnergy[ic]->GetBinContent(nbins+1)<<std::endl;
		if(MC_SS_ReconShowerVisibleEnergy[ic]->GetBinContent(0)>0)
			std::cout<<"MC_SS_ReconShowerVisibleEnergy ic="<<ic<<" had contents at bin"<<0<<" ="<<MC_SS_ReconShowerVisibleEnergy[ic]->GetBinContent(0)<<std::endl;
		if(MC_SS_ReconShowerVisibleEnergy[ic]->GetBinContent(nbins+1)>0)
			std::cout<<"MC_SS_ReconShowerVisibleEnergy ic="<<ic<<" had contents at bin"<<nbins+1<<" ="<<MC_SS_ReconShowerVisibleEnergy[ic]->GetBinContent(nbins+1)<<std::endl;
		if(logLikelihood < -2e+38+0.001)
			break;
		
		
		//ncbkcs
		if(Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[ic]!=NULL&&Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[ic]->GetEntries()>0)
		{
			int nbins_ncbkcs = Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[ic]->GetNbinsX();
			if(nbins_ncbkcs!= MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[ic]->GetNbinsX())//small check, not complete
			{
				std::cout<<"in cal likelihood, nbins of Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy and MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy are different"<<std::endl;
				exit(0);
			}
			for(int ibin=0; ibin<nbins_ncbkcs+2; ibin++)//consider underflow/overflow events
			{
				double ndata = Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[ic]->GetBinContent(ibin);
				double nmc = MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[ic]->GetBinContent(ibin);
				
				if(ndata>0&&nmc>0)
					logLikelihood+= (ndata*1.0-nmc*1.0+ndata*std::log(nmc/ndata));
				else if(nmc>=0&&ndata==0)//add=0 comparing with above, mainly for over/under flow
				{
					logLikelihood+= (ndata*1.0-nmc*1.0);//+ndata*std::log(nmc/ndata));
				}
				else //if(nmc<=0||ndata<0)//shouldn't happen //should ndata==0 happen???
				{
					logLikelihood = -2e+38;//a number randomly choose...
					std::cout<<"ic="<<ic<<" bin"<<ibin<<" has contents: "<<" ndate="<<ndata<<" and nmc="<<nmc<<std::endl;
					break;
				}
			}
		}
		if(logLikelihood < -2e+38+0.001)
			break;
		
		//numuccbkcs
		if(Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[ic]!=NULL&&Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[ic]->GetEntries()>0)
		{
			int nbins_numuccbkcs = Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[ic]->GetNbinsX();
			if(nbins_numuccbkcs!= MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[ic]->GetNbinsX())//small check, not complete
			{
				std::cout<<"in cal likelihood, nbins of Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy and MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy are different"<<std::endl;
				exit(0);
			}
			for(int ibin=0; ibin<nbins_numuccbkcs+2; ibin++)//consider underflow/overflow events
			{
				double ndata = Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[ic]->GetBinContent(ibin);
				double nmc = MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[ic]->GetBinContent(ibin);
				
				if(ndata>0&&nmc>0)
					logLikelihood+= (ndata*1.0-nmc*1.0+ndata*std::log(nmc/ndata));
				else if(nmc>=0&&ndata==0)//add=0 comparing with above, mainly for over/under flow
				{
					logLikelihood+= (ndata*1.0-nmc*1.0);//+ndata*std::log(nmc/ndata));
				}
				else //if(nmc<=0||ndata<0)//shouldn't happen //should ndata==0 happen???
				{
					logLikelihood = -2e+38;//a number randomly choose...
					std::cout<<"ic="<<ic<<" bin"<<ibin<<" has contents: "<<" ndate="<<ndata<<" and nmc="<<nmc<<std::endl;
					break;
				}
			}
		}
		if(logLikelihood < -2e+38+0.001)
			break;
	}
	
	//systematic
    //where CovarianceI is a large cov mat of all pars!
    double llh_syst = 0;
    for(int i=0; i<covarianceI->GetNrows(); i++)
    {
		if(fParamNames[i].find("ksigwt")!=std::string::npos) //no sigwt prior
			continue; //
		for(int j=0; j<covarianceI->GetNrows(); j++)
	  	{
			if(fParamNames[j].find("ksigwt")!=std::string::npos)
				continue;
	    	llh_syst += (fCurrParams[i]-fPriorParams[i])*(fCurrParams[j]-fPriorParams[j])*(*covarianceI)(i,j);
//			llh_syst += (fCurrParams[i]-fInitParams[i])*(fCurrParams[j]-fInitParams[j])*(*covarianceI)(i,j);	    
//			if((*covarianceI)(i,j) != 0){
//				std::cout << " Prop[i] " <<  fCurrParams[i] << " Prior [i] " << fPriorParams[i] << " diff : " << -fCurrParams[i] + fPriorParams[i] << std::endl;
//				std::cout << " Prop[j] " << fCurrParams[j] << " Prior [j] " << fPriorParams[j] << " diff : " << -fCurrParams[j] + fPriorParams[j] << std::endl;
//				std::cout << " cov : " << (*covarianceI)(i,j) << std::endl; 
//				std::cout << "llh_syst at each (i,j) : " << i << ", " << j << " : " << llh_syst << std::endl;
//			}
	
	  	}
	}
	logLikelihood+=(-0.5*llh_syst);
	
	//other reg terms if have
	//logLikelihood+=...
	/* //what below wants to do should be done by if(!FillMCHistograms) return -2e+38; above
	//penalty on weights lower than 0 but apply in such a way. need to refine when dealing with other params
    for(Int_t i = 0; i < fCurrParams.size(); i++){
      if(fCurrParams[i] < fLowerBound[i] || fCurrParams[i] > fUpperBound[i]){
	//	std::cout << i << "th parameter has the current value " << fCurrParams[i] << " its lower bound is : " << fLowerBound[i] << " and the upper bound is : " << fUpperBound[i] << std::endl; 
			logLikelihood = -2e+38;
			break;
      }
    }
	*/
	return logLikelihood;
}


void p0dNuEAnalysisLikelihood::Init(int nconfigs, std::vector<std::string>& mcWaterinFHC, std::vector<std::string>& mcSplineWaterinFHC, double mcPOTWaterin, std::vector<std::string>& mcWateroutFHC, std::vector<std::string>& mcSplineWateroutFHC, double mcPOTWaterout, std::vector<std::string>& dataWaterinFHC, double dataPOTWaterin, std::vector<std::string>& dataWateroutFHC, double dataPOTWaterout)
//void p0dNuEAnalysisLikelihood::Init(int nconfigs, std::string mcWaterinFHC, double mcWaterinFHCPOT, std::string mcWateroutFHC, double mcWateroutFHCPOT, std::string mcWaterinRHC, double mcWaterinRHCPOT, std::string mcWateroutRHC, double mcWateroutRHCPOT, std::string dataWaterinFHC, double dataWaterinFHCPOT,  std::string dataWateroutFHC, double dataWateroutFHCPOT,  std::string dataWaterinRHC, double dataWaterinRHCPOT, std::string dataWateroutRHC, double dataWateroutRHCPOT,  std::string splineWaterinFHC, std::string splineWateroutFHC, std::string splineWaterinRHC, std::string splineWateroutRHC)
{
	std::cout<<"In p0dNuEAnalysisLikelihood::Init"<<std::endl;
	//init data and MC
//	std::string datainputnames[_NConfigs] = {"dataWaterinFHC", "dataWateroutFHC", "dataWaterinRHC", "dataWateroutRHC"};
//	std::string mcinputnames[_NConfigs] = {"mcWaterinFHC", "mcWateroutFHC", "mcWaterinRHC", "mcWateroutRHC"};
//	std::string mcsplinenames[_NConfigs] = {"splineWaterinFHC", "splineWateroutFHC", "splineWaterinRHC", "splineWateroutRHC"};
//	std::vector<std::string> datainputnames, mcinputnames, mcsplinenames;
	if(nconfigs!=_curNConfigs)
		throw std::runtime_error("in p0dNuEAnalysisLikelihood.cxx Init, nconfigs!=_curNConfigs");
	
	if(nconfigs==2)
	{
//		datainputnames.push_back(dataWaterinFHC); datainputnames.push_back(dataWateroutFHC);
//		mcinputnames.push_back(mcWaterinFHC); mcinputnames.push_back(mcWateroutFHC);
//		mcsplinenames.push_back(splineWaterinFHC); mcsplinenames.push_back(splineWateroutFHC);
		dataPOT[0] = dataPOTWaterin; dataPOT[1] = dataPOTWaterout;
		MCPOT[0] = mcPOTWaterin;  MCPOT[1] = mcPOTWaterout;//mcWateroutFHCPOT;
	}
	else if(nconfigs=4)
	{
		std::cout<<"nconfig=4 is NOT fully valid now"<<std::endl;
		exit(0);
//		datainputnames.push_back(dataWaterinFHC); datainputnames.push_back(dataWateroutFHC); datainputnames.push_back(dataWaterinRHC); datainputnames.push_back(dataWateroutRHC);
//		mcinputnames.push_back(mcWaterinFHC); mcinputnames.push_back(mcWateroutFHC); mcinputnames.push_back(mcWaterinRHC); mcinputnames.push_back(mcWateroutRHC);
//		mcsplinenames.push_back(splineWaterinFHC); mcsplinenames.push_back(splineWateroutFHC); mcsplinenames.push_back(splineWaterinRHC); mcsplinenames.push_back(splineWateroutRHC);
//		dataPOT[0] = dataWaterinFHCPOT; dataPOT[1] = dataWateroutFHCPOT; dataPOT[2] = dataWaterinRHCPOT; dataPOT[3] = dataWateroutRHCPOT;
//		MCPOT[0] = mcWaterinFHCPOT; MCPOT[1] = mcWateroutFHCPOT; MCPOT[2] = mcWaterinRHCPOT; MCPOT[3] = mcWateroutRHCPOT;
	}
	
//	MCSimulation* emptyMCSim = new MCSimulation();
	MCSimUnit* emptyMCSim = new MCSimUnit();
	TH1D* templatehist = emptyMCSim->GetTemplateHistogram();
	TH1D* templatehist_ncbkcs = emptyMCSim->GetNCBKCSTemplateHistogram();
	TH1D* templatehist_numubkcs = emptyMCSim->GetNumuCCBKCSTemplateHistogram();

	std::string basename = "";
//	for(int i=0; i<_NConfigs; i++)
	std::cout<<"start to read data"<<std::endl;
	for(int i=0; i<_curNConfigs; i++)
	{
		std::vector<std::string> datafiles = i==0 ?  dataWaterinFHC : dataWateroutFHC;
		DataSets* DataSample = new DataSets(datafiles[0], datafiles[1], datafiles[2]);//new DataSets(datainputnames[i]);//have to use pointer. if you object iteself, then the object disappear out of scoop then all pointer will point to the address in the last object in the loop
		DataSample->FillHistograms();

//		dataPOT[i] = DataSample->GetPOT();

		basename = DataSample->GetSignalEnrichedHistogram()->GetName();
		Data_SS_ReconShowerVisibleEnergy[i] = (TH1D*) DataSample->GetSignalEnrichedHistogram()->Clone(("data_"+basename).c_str());
		MC_SS_ReconShowerVisibleEnergy[i] = (TH1D*) templatehist->Clone(("MC_"+basename).c_str());
		MC_SS_Signal_ReconShowerVisibleEnergy[i] = (TH1D*) templatehist->Clone(("MC_"+basename+"_Signal").c_str());
		MC_SS_Background_ReconShowerVisibleEnergy[i] = (TH1D*) templatehist->Clone(("MC_"+basename+"_Background").c_str());
		MC_SS_ReconShowerVisibleEnergy[i]->Sumw2();//set the Sum of squares of weights structure
		MC_SS_Signal_ReconShowerVisibleEnergy[i]->Sumw2();
		MC_SS_Background_ReconShowerVisibleEnergy[i]->Sumw2();


		basename = DataSample->GetNCResonantPi0SidebandHistogram()->GetName();
		Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[i] = (TH1D*) DataSample->GetNCResonantPi0SidebandHistogram()->Clone(("data_"+basename).c_str());
		MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[i] = (TH1D*) templatehist_ncbkcs->Clone(("MC_"+basename).c_str());
		MC_NCResonantPi0Sideband_Signal_ReconShowerVisibleEnergy[i] = (TH1D*) templatehist_ncbkcs->Clone(("MC_"+basename+"_Signal").c_str());
		MC_NCResonantPi0Sideband_Background_ReconShowerVisibleEnergy[i] = (TH1D*) templatehist_ncbkcs->Clone(("MC_"+basename+"_Background").c_str());
		MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[i]->Sumw2();
		MC_NCResonantPi0Sideband_Signal_ReconShowerVisibleEnergy[i]->Sumw2();
		MC_NCResonantPi0Sideband_Background_ReconShowerVisibleEnergy[i]->Sumw2();

		basename = DataSample->GetnumuCCDISMultiPionSidebandHistogram()->GetName();
		Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[i] = (TH1D*) DataSample->GetnumuCCDISMultiPionSidebandHistogram()->Clone(("data_"+basename).c_str());
		MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[i] = (TH1D*) templatehist_numubkcs->Clone(("MC_"+basename).c_str());
		MC_numuCCDISMultiPionSideband_Signal_ReconShowerVisibleEnergy[i] = (TH1D*) templatehist_numubkcs->Clone(("MC_"+basename+"_Signal").c_str());
		MC_numuCCDISMultiPionSideband_Background_ReconShowerVisibleEnergy[i] = (TH1D*) templatehist_numubkcs->Clone(("MC_"+basename+"_Background").c_str());
		MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[i]->Sumw2();
		MC_numuCCDISMultiPionSideband_Signal_ReconShowerVisibleEnergy[i]->Sumw2();
		MC_numuCCDISMultiPionSideband_Background_ReconShowerVisibleEnergy[i]->Sumw2();


//		basename = "SS_TrueTotKinEnergy";
//		basename += (DataSample->GetWaterConfig() ? "_waterin":"_waterout");
//		basename += (DataSample->GetBeamMode() ? "_FHC":"_RHC"); 
//		MC_SS_TrueTotKinEnergy[i] = (TH1D*) templatehist->Clone(("MC_"+basename)c_str());
//		MC_SS_Signal_TrueTotKinEnergy[i] = (TH1D*) templatehist->Clone(("MC_"+basename+"_Signal")c_str());
//		MC_SS_Background_TrueTotKinEnergy[i] = (TH1D*) templatehist->Clone(("MC_"+basename+"_Background")c_str()); 
//
//		basename = "NCResonantPi0Sideband_TrueTotKinEnergy";
//		basename += (DataSample->GetWaterConfig() ? "_waterin":"_waterout");
//		basename += (DataSample->GetBeamMode() ? "_FHC":"_RHC"); 
//		MC_NCResonantPi0Sideband_TrueTotKinEnergy[i] = (TH1D*) templatehist->Clone(("MC_"+basename)c_str());
//		MC_NCResonantPi0Sideband_Signal_TrueTotKinEnergy[i] = (TH1D*) templatehist->Clone(("MC_"+basename+"_Signal")c_str());
//		MC_NCResonantPi0Sideband_Background_TrueTotKinEnergy[i] = (TH1D*) templatehist->Clone(("MC_"+basename+"_Background")c_str()); 
//
//		basename = "numuCCDISMultiPionSideband_TrueTotKinEnergy";
//		basename += (DataSample->GetWaterConfig() ? "_waterin":"_waterout");
//		basename += (DataSample->GetBeamMode() ? "_FHC":"_RHC"); 
//		MC_numuCCDISMultiPionSideband_TrueTotKinEnergy[i] = (TH1D*) templatehist->Clone(("MC_"+basename)c_str());
//		MC_numuCCDISMultiPionSideband_Signal_TrueTotKinEnergy[i] = (TH1D*) templatehist->Clone(("MC_"+basename+"_Signal")c_str());
//		MC_numuCCDISMultiPionSideband_Background_TrueTotKinEnergy[i] = (TH1D*) templatehist->Clone(("MC_"+basename+"_Background")c_str()); 


		std::vector<std::string> mcfiles = i==0 ?  mcWaterinFHC : mcWateroutFHC;
		std::vector<std::string> mcsplinefiles = i==0 ?  mcSplineWaterinFHC : mcSplineWateroutFHC;
		MCSamples_allConfigs[i] = new MCSimulation(mcfiles[0], mcsplinefiles[0], mcfiles[1], mcsplinefiles[1], mcfiles[2], mcsplinefiles[2]); //new MCSimulation(mcinputnames[i], mcsplinenames[i]);
		MCSamples_allConfigs[i]->GetAllSamples();
//		MCPOT[i] = MCSamples_allConfigs[i]->GetPOT(); //need to put here???
	}

	std::cout<<"end data reading"<<std::endl;
	std::cout<<"start parameter init"<<std::endl;
	//Read the Fit Parameters and Initialize them
	FitParams fitParams;
	

	fParamNames.resize(fitParams.GetDim());
	fitParams.GetParamNames(fParamNames);
	std::cout<<"# of parameters: "<<fitParams.GetDim()<<std::endl;
	for(int i=0; i<fitParams.GetDim(); i++)
		std::cout<<" "<<fParamNames[i]<<std::endl;

    fInitParams.resize(fitParams.GetDim());
    fitParams.GetInitFitParams(fInitParams);//nominal
	fPriorParams.resize(fitParams.GetDim());
    fitParams.GetPriorFitParams(fPriorParams);
    fSigmaParams.resize(fitParams.GetDim());
    fitParams.GetSigmaFitParams(fSigmaParams);
    fLowerBound.resize(fitParams.GetDim());
    fitParams.GetLowerBoundParams(fLowerBound);
    fUpperBound.resize(fitParams.GetDim());
    fitParams.GetUpperBoundParams(fUpperBound);
    correlation = new TMatrixDSym(fitParams.GetDim());
    fitParams.GetCorrelation(correlation);
    covariance = new TMatrixDSym(fitParams.GetDim());
    fitParams.GetCovariance(covariance);
    covarianceI = new TMatrixDSym(fitParams.GetDim());
    fitParams.GetCovarianceI(covarianceI);

	std::cout<<"end parameter init"<<std::endl;

	std::cout<<"start MC init"<<std::endl;
    ResetMCHistograms();
    FillMCHistograms(fInitParams);
	std::cout<<"end MC init"<<std::endl;


	delete emptyMCSim;
	delete templatehist;
	delete templatehist_ncbkcs;
	delete templatehist_numubkcs;
}

void p0dNuEAnalysisLikelihood::ResetMCHistograms()
{
//	for(int i=0; i<_NConfigs; i++)
	for(int i=0; i<_curNConfigs; i++)
	{
		MC_SS_ReconShowerVisibleEnergy[i]->Reset();
		MC_SS_Signal_ReconShowerVisibleEnergy[i]->Reset();
		MC_SS_Background_ReconShowerVisibleEnergy[i]->Reset();

		MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[i]->Reset();
		MC_NCResonantPi0Sideband_Signal_ReconShowerVisibleEnergy[i]->Reset();
		MC_NCResonantPi0Sideband_Background_ReconShowerVisibleEnergy[i]->Reset();

		MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[i]->Reset();
		MC_numuCCDISMultiPionSideband_Signal_ReconShowerVisibleEnergy[i]->Reset();
		MC_numuCCDISMultiPionSideband_Background_ReconShowerVisibleEnergy[i]->Reset();

//		MC_SS_TrueTotKinEnergy[i]->Reset();
//		MC_SS_Signal_TrueTotKinEnergy[i]->Reset();
//		MC_SS_Background_TrueTotKinEnergy[i]->Reset();
//
//		MC_NCResonantPi0Sideband_TrueTotKinEnergy[i]->Reset();
//		MC_NCResonantPi0Sideband_Signal_TrueTotKinEnergy[i]->Reset();
//		MC_NCResonantPi0Sideband_Background_TrueTotKinEnergy[i]->Reset();
//
//		MC_numuCCDISMultiPionSideband_TrueTotKinEnergy[i]->Reset();
//		MC_numuCCDISMultiPionSideband_Signal_TrueTotKinEnergy[i]->Reset();
//		MC_numuCCDISMultiPionSideband_Background_TrueTotKinEnergy[i]->Reset();
	}

}

/*
void  p0dNuEAnalysisLikelihood::FillNominalMCHistograms()//const std::vector<double>& params)
{
	ResetMCHistograms();
	
	for(int ic=0; ic<_curNConfigs; ic++)
	{
		//change it to const function so that I don't need to define a object but use SystematicCorrection::ReweightEvent(xxx)
		for(int i=0; i<MCSamples_allConfigs[ic]->_signalsample.size(); i++)
		{
			MCEvent nominalevt = MCSamples_allConfigs[ic]->_signalsample[i];
			if(nominalevt.ShowerMedianWidth<_SMWCut[ic]&&nominalevt.ShowerEDepFraction>_SCFCut[ic])
			{
				MC_SS_ReconShowerVisibleEnergy[ic]->Fill(nominalevt.ReconShowerEnergy);
//				MC_SS_TrueTotKinEnergy[ic]->Fill(nominalevt.totTrueParKin, weight);
				if(nominalevt.isSignal==1)
					MC_SS_Signal_ReconShowerVisibleEnergy[ic]->Fill(nominalevt.ReconShowerEnergy);
				else if(nominalevt.isSignal==0) 
					MC_SS_Background_ReconShowerVisibleEnergy[ic]->Fill(nominalevt.ReconShowerEnergy);
			}

		}
		for(int i=0; i<MCSamples_allConfigs[ic]->_ncbksample.size(); i++)
		{
			MCEvent nominalevt = MCSamples_allConfigs[ic]->_ncbksample[i];
			if(nominalevt.ShowerEDepFraction<_SCFCut[ic])
			{
				double Max_Dir[3] = {nominalevt.parDirection[nominalevt.maxEDepShowerIndex][0], nominalevt.parDirection[nominalevt.maxEDepShowerIndex][1], nominalevt.parDirection[nominalevt.maxEDepShowerIndex][2]};
				double SecondMax_Dir[3] = {nominalevt.parDirection[nominalevt.secondmaxEDepShowerIndex][0], nominalevt.parDirection[nominalevt.secondmaxEDepShowerIndex][1], nominalevt.parDirection[nominalevt.secondmaxEDepShowerIndex][2]};
				double invarinatmass = pi0ShowerUtils::CalInvariantMass(nominalevt.parScaledMom[nominalevt.maxEDepShowerIndex], Max_Dir, nominalevt.parScaledMom[nominalevt.secondmaxEDepShowerIndex],SecondMax_Dir); // use nueutil mom
//					double cospi0thetaz = (Max_pi0Mom*Max_Dir[2]+SecondMax_pi0Mom*SecondMax_Dir[2])/TMath::Sqrt(TMath::Power(Max_pi0Mom*Max_Dir[0]+SecondMax_pi0Mom*SecondMax_Dir[0], 2)+TMath::Power(Max_pi0Mom*Max_Dir[1]+SecondMax_pi0Mom*SecondMax_Dir[1], 2)+TMath::Power(Max_pi0Mom*Max_Dir[2]+SecondMax_pi0Mom*SecondMax_Dir[2], 2));
				double cospi0thetaz = (nominalevt.parScaledMom[nominalevt.maxEDepShowerIndex]*Max_Dir[2]+nominalevt.parScaledMom[nominalevt.secondmaxEDepShowerIndex]*SecondMax_Dir[2])/TMath::Sqrt(TMath::Power(nominalevt.parScaledMom[nominalevt.maxEDepShowerIndex]*Max_Dir[0]+nominalevt.parScaledMom[nominalevt.secondmaxEDepShowerIndex]*SecondMax_Dir[0], 2)+TMath::Power(nominalevt.parScaledMom[nominalevt.maxEDepShowerIndex]*Max_Dir[1]+nominalevt.parScaledMom[nominalevt.secondmaxEDepShowerIndex]*SecondMax_Dir[1], 2)+TMath::Power(nominalevt.parScaledMom[nominalevt.maxEDepShowerIndex]*Max_Dir[2]+nominalevt.parScaledMom[nominalevt.secondmaxEDepShowerIndex]*SecondMax_Dir[2], 2));
				if(TMath::ACos(cospi0thetaz)<1.04&&invarinatmass>60&&invarinatmass<200)
				{
					MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[ic]->Fill(nominalevt.ReconShowerEnergy);
					if(nominalevt.isSignal==1)
						MC_NCResonantPi0Sideband_Signal_ReconShowerVisibleEnergy[ic]->Fill(nominalevt.ReconShowerEnergy);
					if(nominalevt.isSignal==0)
						MC_NCResonantPi0Sideband_Background_ReconShowerVisibleEnergy[ic]->Fill(nominalevt.ReconShowerEnergy);
				}
			}

		}
		for(int i=0; i<MCSamples_allConfigs[ic]->_numuccbksample.size(); i++)
		{
			MCEvent nominalevt = MCSamples_allConfigs[ic]->_numuccbksample[i];
			MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[ic]->Fill(nominalevt.ReconShowerEnergy);
			if(nominalevt.isSignal==1)
				MC_numuCCDISMultiPionSideband_Signal_ReconShowerVisibleEnergy[ic]->Fill(nominalevt.ReconShowerEnergy);
			if(nominalevt.isSignal==0)
				MC_numuCCDISMultiPionSideband_Background_ReconShowerVisibleEnergy[ic]->Fill(nominalevt.ReconShowerEnergy);
		}
		
//		MC_SS_ReconShowerVisibleEnergy[ic]->Sumw2();
		MC_SS_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
//		MC_SS_Signal_ReconShowerVisibleEnergy[ic]->Sumw2();
		MC_SS_Signal_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
//		MC_SS_Background_ReconShowerVisibleEnergy[ic]->Sumw2();
		MC_SS_Background_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
//		MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[ic]->Sumw2();
		MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
//		MC_NCResonantPi0Sideband_Signal_ReconShowerVisibleEnergy[ic]->Sumw2();
		MC_NCResonantPi0Sideband_Signal_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
//		MC_NCResonantPi0Sideband_Background_ReconShowerVisibleEnergy[ic]->Sumw2();
		MC_NCResonantPi0Sideband_Background_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
//		MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[ic]->Sumw2();
		MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
//		MC_numuCCDISMultiPionSideband_Signal_ReconShowerVisibleEnergy[ic]->Sumw2();
		MC_numuCCDISMultiPionSideband_Signal_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
//		MC_numuCCDISMultiPionSideband_Background_ReconShowerVisibleEnergy[ic]->Sumw2();
		MC_numuCCDISMultiPionSideband_Background_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
	}
}
*/

void  p0dNuEAnalysisLikelihood::FillNominalMCHistograms()
{

	ResetMCHistograms();
	
	for(int ic=0; ic<_curNConfigs; ic++)
	{
		if(!MCSamples_allConfigs[ic]->_signalSample)
			throw std::runtime_error("_signalSample is a NULL poiner");
		for(int i=0; i<MCSamples_allConfigs[ic]->_signalSample->_sample.size(); i++)
		{
			MCEvent reweightevt = MCSamples_allConfigs[ic]->_signalSample->_sample[i];
//				std::cout<<"reweightevt.isWaterConfig = "<<reweightevt.isWaterConfig<<" and nominal : "<<MCSamples_allConfigs[ic]->_signalsample[i].isWaterConfig<<std::endl;
//				reweightevt.ReconShowerEnergy = Correction.CalReconShowerEnergyWithSyst(nominalevt, params); //four lines below are added on 03/14/2021. need to check
			if(reweightevt.ShowerMedianWidth<_SMWCut[ic]&&reweightevt.ShowerEDepFraction>_SCFCut[ic]&&reweightevt.HSMTrackLayers>_LayerCut[ic])
			{
				MC_SS_ReconShowerVisibleEnergy[ic]->Fill(reweightevt.ReconShowerEnergy);//, weight);
//				MC_SS_TrueTotKinEnergy[ic]->Fill(reweightevt.totTrueParKin, weight);
				if(reweightevt.isSignal==1)
					MC_SS_Signal_ReconShowerVisibleEnergy[ic]->Fill(reweightevt.ReconShowerEnergy);//, weight);
				if(reweightevt.isSignal==0) 
					MC_SS_Background_ReconShowerVisibleEnergy[ic]->Fill(reweightevt.ReconShowerEnergy);//, weight);
			}

		
		}
		if(MCSamples_allConfigs[ic]->_ncbkSample)
		{
			for(int i=0; i<MCSamples_allConfigs[ic]->_ncbkSample->_sample.size(); i++)
			{
				MCEvent reweightevt = MCSamples_allConfigs[ic]->_ncbkSample->_sample[i];
				if(reweightevt.ShowerEDepFraction<_SCFCut[ic]&&reweightevt.twoshowerEDepfrac>0.85&&reweightevt.invariantmass>60&&reweightevt.invariantmass<200)
				{
					MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[ic]->Fill(reweightevt.invariantmass);//ReconShowerEnergy);//, weight);
					if(reweightevt.isSignal==1)
						MC_NCResonantPi0Sideband_Signal_ReconShowerVisibleEnergy[ic]->Fill(reweightevt.invariantmass);//ReconShowerEnergy);//, weight);
					if(reweightevt.isSignal==0)
						MC_NCResonantPi0Sideband_Background_ReconShowerVisibleEnergy[ic]->Fill(reweightevt.invariantmass);//ReconShowerEnergy);//, weight);
				}

			}
		}	
		if(MCSamples_allConfigs[ic]->_numccbkSample)
		{
			for(int i=0; i<MCSamples_allConfigs[ic]->_numccbkSample->_sample.size(); i++)
			{
				MCEvent reweightevt = MCSamples_allConfigs[ic]->_numccbkSample->_sample[i];
				if(reweightevt.LongestTrackLayers_atTrackReconStage>23)
				{
					MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[ic]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage));//, weight);
					if(reweightevt.isSignal==1)
						MC_numuCCDISMultiPionSideband_Signal_ReconShowerVisibleEnergy[ic]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage));
					if(reweightevt.isSignal==0)
						MC_numuCCDISMultiPionSideband_Background_ReconShowerVisibleEnergy[ic]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage));
				}
			}
		}
		
		MC_SS_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_SS_Signal_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_SS_Background_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_NCResonantPi0Sideband_Signal_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_NCResonantPi0Sideband_Background_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_numuCCDISMultiPionSideband_Signal_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_numuCCDISMultiPionSideband_Background_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
	}

}
//void p0dNuEAnalysisLikelihood::FillMCHistograms(const std::vector<double>& params)
bool p0dNuEAnalysisLikelihood::FillMCHistograms(const std::vector<double>& params)
{
	ResetMCHistograms();
//	bool hasneg = false;
//	bool allposi = true;
	
//	SystematicCorrection Correction;
//	for(int ic=0; ic<_NConfig; ic++)
	for(int ic=0; ic<_curNConfigs; ic++)
	{
		//change it to const function so that I don't need to define a object but use SystematicCorrection::ReweightEvent(xxx)
		if(!MCSamples_allConfigs[ic]->_signalSample)
			throw std::runtime_error("_signalSample is a NULL poiner");
		for(int i=0; i<MCSamples_allConfigs[ic]->_signalSample->_sample.size(); i++)
		{
			MCEvent reweightevt = MCSamples_allConfigs[ic]->_signalSample->_sample[i];
//				std::cout<<"reweightevt.isWaterConfig = "<<reweightevt.isWaterConfig<<" and nominal : "<<MCSamples_allConfigs[ic]->_signalsample[i].isWaterConfig<<std::endl;
//				reweightevt.ReconShowerEnergy = Correction.CalReconShowerEnergyWithSyst(nominalevt, params); //four lines below are added on 03/14/2021. need to check
//				reweightevt.ShowerMedianWidth = Correction.CalShowerMedianWidthWithSyst(nominalevt, params);
//				reweightevt.ShowerEDepFraction = Correction.CalShowerEDepFractionWithSyst(nominalevt, params);
			double weight = Correction.ReweightEvent(reweightevt, MCSamples_allConfigs[ic]->_signalSample->_sample[i], params);					
//			if(allposi&&weight<0)
//				allposi = false;
//			if(!hasneg&&weight<0)
//				hasneg = true;
		/*	
			if(weight!=1)
			{
				std::cout<<"weight = "<<weight<<" Event "<<reweightevt.EventID<<std::endl;
//				if(fParamNames.size()!=params.size())
//					std::cout<<"fParamNames.size = "<<fParamNames.size()<<" != params.size = "<<params.size()<<std::endl;
//				for(int itmp=0; itmp<params.size(); itmp++)
//				{
//					std::cout<<fParamNames[itmp]<<" "<<params[itmp]<<std::endl;
//				}
			}
		*/	
			if(reweightevt.ShowerMedianWidth<_SMWCut[ic]&&reweightevt.ShowerEDepFraction>_SCFCut[ic]&&reweightevt.HSMTrackLayers>_LayerCut[ic])
			{
				if(weight<0)
				{
					//std::cout<<"In Signal Sample, Event "<<reweightevt.EventID<<" is reweighted in a negative weight = "<<weight<<std::endl;
					return false;
				}
				MC_SS_ReconShowerVisibleEnergy[ic]->Fill(reweightevt.ReconShowerEnergy, weight);
//				MC_SS_TrueTotKinEnergy[ic]->Fill(reweightevt.totTrueParKin, weight);
				if(reweightevt.isSignal==1)
					MC_SS_Signal_ReconShowerVisibleEnergy[ic]->Fill(reweightevt.ReconShowerEnergy, weight);
				if(reweightevt.isSignal==0) 
					MC_SS_Background_ReconShowerVisibleEnergy[ic]->Fill(reweightevt.ReconShowerEnergy, weight);
			}

		
		}
		if(MCSamples_allConfigs[ic]->_ncbkSample)
		{
			for(int i=0; i<MCSamples_allConfigs[ic]->_ncbkSample->_sample.size(); i++)
			{
				MCEvent reweightevt = MCSamples_allConfigs[ic]->_ncbkSample->_sample[i];
//				double weight = Correction.ReweightEvent(reweightevt, MCSamples_allConfigs[ic]->_ncbkSample->_sample[i], params);					
				double weight = Correction.ReweightNC1pi0CSEvent(reweightevt, MCSamples_allConfigs[ic]->_ncbkSample->_sample[i], params);					
				if(reweightevt.ShowerEDepFraction<_SCFCut[ic]&&reweightevt.twoshowerEDepfrac>0.85&&reweightevt.invariantmass>60&&reweightevt.invariantmass<200)
				{
					if(weight<0)
					{
						//std::cout<<"In NCBKCS, Event "<<reweightevt.EventID<<" is reweighted in a negative weight = "<<weight<<std::endl;
						return false;
					}
					MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[ic]->Fill(reweightevt.invariantmass, weight);//ReconShowerEnergy, weight);
					if(reweightevt.isSignal==1)
						MC_NCResonantPi0Sideband_Signal_ReconShowerVisibleEnergy[ic]->Fill(reweightevt.invariantmass, weight);//ReconShowerEnergy, weight);
					if(reweightevt.isSignal==0)
						MC_NCResonantPi0Sideband_Background_ReconShowerVisibleEnergy[ic]->Fill(reweightevt.invariantmass, weight);//ReconShowerEnergy, weight);
				}

			}
		}	
		if(MCSamples_allConfigs[ic]->_numccbkSample)
		{
			for(int i=0; i<MCSamples_allConfigs[ic]->_numccbkSample->_sample.size(); i++)
			{
				MCEvent reweightevt = MCSamples_allConfigs[ic]->_numccbkSample->_sample[i];
				double weight = Correction.ReweightEvent(reweightevt, MCSamples_allConfigs[ic]->_numccbkSample->_sample[i], params, 2);;//for now
				if(reweightevt.LongestTrackLayers_atTrackReconStage>23)
				{
					if(weight<0)
					{
						//std::cout<<"In numuCCBKCS Sample, Event "<<reweightevt.EventID<<" is reweighted in a negative weight = "<<weight<<std::endl;
						return false;
					}
					MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[ic]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage), weight);
					if(reweightevt.isSignal==1)
						MC_numuCCDISMultiPionSideband_Signal_ReconShowerVisibleEnergy[ic]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage), weight);
					if(reweightevt.isSignal==0)
						MC_numuCCDISMultiPionSideband_Background_ReconShowerVisibleEnergy[ic]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage), weight);
				}
			}
		}
		
		MC_SS_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_SS_Signal_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_SS_Background_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_NCResonantPi0Sideband_Signal_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_NCResonantPi0Sideband_Background_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_numuCCDISMultiPionSideband_Signal_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
		MC_numuCCDISMultiPionSideband_Background_ReconShowerVisibleEnergy[ic]->Scale(dataPOT[ic]/MCPOT[ic]);
	}

	return true;//!hasneg;
}

//void p0dNuEAnalysisLikelihood::DrawSignalSampleStack(int ic)//configid)
THStack* p0dNuEAnalysisLikelihood::GetSignalSampleStack(int ic, std::string differentiator)//int configid)
{
	if(ic>=_curNConfigs||ic<0)
	{
		std::cout<<"No such configid (="<<ic<<")"<<std::endl;
		return NULL;
	}
    const int NUEREAC = 13;
    std::string NueReaction_types[NUEREAC] = { "#nu_{e} CCQE",   "#nu_{e} CCRES",  "#nu_{e} CC_MEC",  "#nu_{e} CC_COH",   "#nu_{e} CC_DIS", "#nu_{e} CC_LowWMultiPions",  "#nu_{e} CCOthers",  "#bar{#nu}_{e} CC",   "#nu_{#mu}/#bar{#nu}_{#mu} CC",    "NC" ,   "OOP0DFV", "Unknown", "#nu_{e} CC-NOTSigByBDT"};
//	int NueReaction_codes[NUEREAC] = {              0,                 1,                  2,                    3,                 4,                       5,				      6,                       12,                   7,                       8,                  9,         10,       11};
	int NueReaction_colors[NUEREAC]= {              2,                 3,               kOrange,                 5,                12,                       9,                  30,                       46,                      20,                 6,        kPink-7,     kBlack,          7 };

	THStack* hs_reconshowerenergy_NueReaction = new THStack("hs_reconshowerenergy_NueReaction", "hs_reconshowerenergy_NueReaction");
    TH1D* th1d_reconshowerenergy_NueReaction[NUEREAC];
	MCSimUnit* emptyMCSim = new MCSimUnit();
	TH1D* templatehist = emptyMCSim->GetTemplateHistogram();
	for(int i=NUEREAC-2; i>=0; i--)//as "#nu_{e} CC-NOTSigByBDT" is added as the last by accident, so to make sure the plot looks in a good order , adding in such a way
	{
		th1d_reconshowerenergy_NueReaction[i] = (TH1D*) templatehist->Clone(NueReaction_types[i].c_str());
	 	th1d_reconshowerenergy_NueReaction[i]->SetFillColor(NueReaction_colors[i]);
		hs_reconshowerenergy_NueReaction->Add(th1d_reconshowerenergy_NueReaction[i]);
		if(i==7)//add last one
		{
			th1d_reconshowerenergy_NueReaction[12] = (TH1D*) templatehist->Clone(NueReaction_types[12].c_str());
			th1d_reconshowerenergy_NueReaction[12]->SetFillColor(NueReaction_colors[12]);
			hs_reconshowerenergy_NueReaction->Add(th1d_reconshowerenergy_NueReaction[12]);
		}
	}

	//tmp
	TH1D* onwatersig = (TH1D*) templatehist->Clone("onwatersig");
	TH1D* notwatersig = (TH1D*) templatehist->Clone("notwatersig");
	std::unordered_map<int, int> nupdgid{{14, 0}, {-14, 1}, {12, 2}, {-12, 3}};
	TH1D* truenuE[4];
	double numubins[12] = {0, 0.4, 0.5, 0.6, 0.7, 1, 1.5, 2.5, 3.5, 5, 7, 30};
	double numubbins[6] = {0, 0.7, 1, 1.5, 2.5, 30};
	double nuebins[8] = {0, 0.5, 0.7, 0.8, 1.5, 2.5, 4, 30};
	double nuebbins[3] = {0, 2.5, 30};
	truenuE[0] = new TH1D("numu", "numu", 11, numubins );
	truenuE[1] = new TH1D("numub", "numub", 5, numubbins);
	truenuE[2] = new TH1D("nue", "nue", 7, nuebins);
	truenuE[3] = new TH1D("nueb", "nueb", 2, nuebbins);
	////

	for(int i=0; i<MCSamples_allConfigs[ic]->_signalSample->_sample.size(); i++)
	{
		
		if(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ShowerMedianWidth>=_SMWCut[ic]||MCSamples_allConfigs[ic]->_signalSample->_sample[i].ShowerEDepFraction<=_SCFCut[ic]||MCSamples_allConfigs[ic]->_signalSample->_sample[i].HSMTrackLayers<=_LayerCut[ic])
			continue;
		int reaccode =  MCSamples_allConfigs[ic]->_signalSample->_sample[i].reactionCode;
		int nupdg = MCSamples_allConfigs[ic]->_signalSample->_sample[i].NeutrinoPDG;
		int isinFV = MCSamples_allConfigs[ic]->_signalSample->_sample[i].isinFV;
		int isSigBDT = MCSamples_allConfigs[ic]->_signalSample->_sample[i].isSignal;
		///
		int isOnWater = MCSamples_allConfigs[ic]->_signalSample->_sample[i].isOnWater;
		if(nupdgid.find(nupdg)==nupdgid.end())
			std::cout<<"Event "<<MCSamples_allConfigs[ic]->_signalSample->_sample[i].EventID<<"with nupdg = "<<nupdg<<std::endl;
		else
			truenuE[nupdgid[nupdg]]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].TrueNeutrinoEnergy/1000.0);
		///
		//MCEvent reweightevt = MCSamples_allConfigs[ic]->_signalSample->_sample[i];
		if(isinFV==1)
		{
			if(nupdg==12)
			{
				if(std::abs(reaccode)>30)
					th1d_reconshowerenergy_NueReaction[9]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
				else if(isSigBDT==1)
				{
					if(std::abs(reaccode)==1)//ccqe	
						th1d_reconshowerenergy_NueReaction[0]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
					else if((std::abs(reaccode)>10&&std::abs(reaccode)<14)||std::abs(reaccode)==22||std::abs(reaccode)==23||(std::abs(reaccode)>=17&&std::abs(reaccode)<=20))
						th1d_reconshowerenergy_NueReaction[1]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
					else if(std::abs(reaccode)==2)
						th1d_reconshowerenergy_NueReaction[2]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
					else if(std::abs(reaccode)==16)
						 th1d_reconshowerenergy_NueReaction[3]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
					else if(std::abs(reaccode)==26)
						th1d_reconshowerenergy_NueReaction[4]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
					else if(std::abs(reaccode)==21)
						th1d_reconshowerenergy_NueReaction[5]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
					else //should not occur
						th1d_reconshowerenergy_NueReaction[6]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);

					///
					if(isOnWater==1)
						onwatersig->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
					else if(isOnWater==0)
						notwatersig->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
					///
				}
				else
					th1d_reconshowerenergy_NueReaction[12]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
			}
			else if(nupdg==-12)
			{
				if(std::abs(reaccode)>30)//nc
					th1d_reconshowerenergy_NueReaction[9]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
				else//nuebarCC
					th1d_reconshowerenergy_NueReaction[7]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
			}
			else if(std::abs(nupdg)==14)//numu
			{
				if(std::abs(reaccode)>30)//nc
					th1d_reconshowerenergy_NueReaction[9]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
				else//numu numubar CC
					th1d_reconshowerenergy_NueReaction[8]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
			}
			else //unknown
				th1d_reconshowerenergy_NueReaction[11]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);

		}
		else if(isinFV==0)
			th1d_reconshowerenergy_NueReaction[10]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
		else
			th1d_reconshowerenergy_NueReaction[11]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy);
	}

	TCanvas* c1 = new TCanvas("c1", "c1");
	c1->cd();
	int nbins = templatehist->GetNbinsX();
	std::vector<double> totcnts(nbins, 0);
//	for(int i=0; i<NUEREAC; i++)
//	{
//		for(int ib=1; ib<nbins+1; ib++)
//			totcnts[ib-1] += th1d_reconshowerenergy_NueReaction[i]->GetBinContent(ib);
//
//		std::string name = differentiator+th1d_reconshowerenergy_NueReaction[i]->GetName()+"_waterconfig"+std::to_string(ic)+".pdf";
//		th1d_reconshowerenergy_NueReaction[i]->Draw("HIST");
//		c1->SaveAs(name.c_str());
//	}
	//print
	std::cout<<"Print cnt in waterconfig "<<ic<<" where differentiator = "<<differentiator<<std::endl;
	std::cout<<"	onwatersigcnts: ";
	for(int ib=1; ib<nbins+1; ib++)
		std::cout<<" "<<onwatersig->GetBinContent(ib);
	std::cout<<std::endl;
	std::string name1 = differentiator + onwatersig->GetName() + "_waterconfig"+std::to_string(ic)+".pdf";
	onwatersig->Draw("HIST TEXT");
	c1->SaveAs(name1.c_str());

	std::cout<<"	notwatersigcnts: ";
	for(int ib=1; ib<nbins+1; ib++)
		std::cout<<" "<<notwatersig->GetBinContent(ib);
	std::cout<<std::endl;
	name1 = differentiator + notwatersig->GetName() + "_waterconfig"+std::to_string(ic)+".pdf";
	notwatersig->Draw("HIST TEXT");
	c1->SaveAs(name1.c_str());

	std::cout<<"	totwatersigcnts: ";
	for(int ib=1; ib<nbins+1; ib++)
		std::cout<<" "<<totcnts[ib-1];
	std::cout<<std::endl;
//	for(int i=0; i<4; i++)
//	{
//		int tmpnbins = truenuE[i]->GetNbinsX();
//		std::cout<<"	flux "<< truenuE[i]->GetName()<<": ";
//		for(int ib=1; ib<tmpnbins+1; ib++)
//			std::cout<<" "<<truenuE[i]->GetBinContent(ib);
//		std::cout<<std::endl;
//
//		std::string name = differentiator + truenuE[i]->GetName() + "_waterconfig"+std::to_string(ic)+".pdf";
//		truenuE[i]->Draw("HIST TEXT");
//		c1->SaveAs(name.c_str());
//	}

//	hs_reconshowerenergy_NueReaction->Draw();
//	hs_reconshowerenergy_NueReaction->GetXaxis()->SetTitle("ReconShowerEnergy(MeV)");
//	c1->Modified();
//	c1->BuildLegend(0.6,0.6,0.9,0.9,"");
//	c1->SaveAs("ReconShowerEnergy_signalsample.pdf");
//
//	for(int i=0; i<NUEREAC; i++)
//		delete th1d_reconshowerenergy_NueReaction[i];
//	delete hs_reconshowerenergy_NueReaction;
//	delete templatehist;
	delete c1;
	delete emptyMCSim;
	delete templatehist;
	for(int i=0; i<4; i++)
		delete truenuE[i];
	return hs_reconshowerenergy_NueReaction;
}

THStack* p0dNuEAnalysisLikelihood::GetSignalSampleStack(int ic, const std::vector<double>& params, std::string differentiator)//int configid)
{
	if(ic>=_curNConfigs||ic<0)
	{
		std::cout<<"No such configid (="<<ic<<")"<<std::endl;
		return NULL;
	}

	if(params.size()!=fInitParams.size())
	{
		std::cout<<"Input params size doesn't match"<<std::endl;
		exit(0);
	}
    const int NUEREAC = 13;
    std::string NueReaction_types[NUEREAC] = { "#nu_{e} CCQE",   "#nu_{e} CCRES",  "#nu_{e} CC_MEC",  "#nu_{e} CC_COH",   "#nu_{e} CC_DIS", "#nu_{e} CC_LowWMultiPions",  "#nu_{e} CCOthers",  "#bar{#nu}_{e} CC",   "#nu_{#mu}/#bar{#nu}_{#mu} CC",    "NC" ,   "OOP0DFV", "Unknown", "#nu_{e} CC-NOTSigByBDT"};
//	int NueReaction_codes[NUEREAC] = {              0,                 1,                  2,                    3,                 4,                       5,				      6,                       12,                   7,                       8,                  9,         10,       11};
	int NueReaction_colors[NUEREAC]= {              2,                 3,               kOrange,                 5,                12,                       9,                  30,                       46,                      20,                 6,        kPink-7,     kBlack,          7 };

	THStack* hs_reconshowerenergy_NueReaction = new THStack(("hs_reconshowerenergy_NueReaction"+differentiator).c_str(), ("hs_reconshowerenergy_NueReaction"+differentiator).c_str());
    TH1D* th1d_reconshowerenergy_NueReaction[NUEREAC];
	MCSimUnit* emptyMCSim = new MCSimUnit();
	TH1D* templatehist = emptyMCSim->GetTemplateHistogram();
	for(int i=NUEREAC-2; i>=0; i--)//as "#nu_{e} CC-NOTSigByBDT" is added as the last by accident, so to make sure the plot looks in a good order , adding in such a way
	{
		th1d_reconshowerenergy_NueReaction[i] = (TH1D*) templatehist->Clone((NueReaction_types[i]+differentiator).c_str());
	 	th1d_reconshowerenergy_NueReaction[i]->SetFillColor(NueReaction_colors[i]);
		hs_reconshowerenergy_NueReaction->Add(th1d_reconshowerenergy_NueReaction[i]);
		if(i==7)//add last one
		{
			th1d_reconshowerenergy_NueReaction[12] = (TH1D*) templatehist->Clone(NueReaction_types[12].c_str());
			th1d_reconshowerenergy_NueReaction[12]->SetFillColor(NueReaction_colors[12]);
			hs_reconshowerenergy_NueReaction->Add(th1d_reconshowerenergy_NueReaction[12]);
		}
	}

	//tmp
	TH1D* onwatersig = (TH1D*) templatehist->Clone("onwatersig");
	TH1D* notwatersig = (TH1D*) templatehist->Clone("notwatersig");
	std::unordered_map<int, int> nupdgid{{14, 0}, {-14, 1}, {12, 2}, {-12, 3}};
	TH1D* truenuE[4];
	double numubins[12] = {0, 0.4, 0.5, 0.6, 0.7, 1, 1.5, 2.5, 3.5, 5, 7, 30};
	double numubbins[6] = {0, 0.7, 1, 1.5, 2.5, 30};
	double nuebins[8] = {0, 0.5, 0.7, 0.8, 1.5, 2.5, 4, 30};
	double nuebbins[3] = {0, 2.5, 30};
	truenuE[0] = new TH1D("numu", "numu", 11, numubins );
	truenuE[1] = new TH1D("numub", "numub", 5, numubbins);
	truenuE[2] = new TH1D("nue", "nue", 7, nuebins);
	truenuE[3] = new TH1D("nueb", "nueb", 2, nuebbins);
	////

	for(int i=0; i<MCSamples_allConfigs[ic]->_signalSample->_sample.size(); i++)
	{
		MCEvent reweightevt = MCSamples_allConfigs[ic]->_signalSample->_sample[i];
		double weight = Correction.ReweightEvent(reweightevt, MCSamples_allConfigs[ic]->_signalSample->_sample[i], params);					
		
		if(reweightevt.ShowerMedianWidth>=_SMWCut[ic]||reweightevt.ShowerEDepFraction<=_SCFCut[ic]||reweightevt.HSMTrackLayers<=_LayerCut[ic])
			continue;
		int reaccode =  reweightevt.reactionCode;
		int nupdg = reweightevt.NeutrinoPDG;
		int isinFV =  reweightevt.isinFV;
		int isSigBDT = reweightevt.isSignal;
		///
		int isOnWater = MCSamples_allConfigs[ic]->_signalSample->_sample[i].isOnWater;
		if(nupdgid.find(nupdg)==nupdgid.end())
			std::cout<<"Event "<<MCSamples_allConfigs[ic]->_signalSample->_sample[i].EventID<<"with nupdg = "<<nupdg<<std::endl;
		else
			truenuE[nupdgid[nupdg]]->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].TrueNeutrinoEnergy/1000.0, weight);
		///
		//MCEvent reweightevt = MCSamples_allConfigs[ic]->_signalSample->_sample[i];
		if(isinFV==1)
		{
			if(nupdg==12)
			{
				if(std::abs(reaccode)>30)
					th1d_reconshowerenergy_NueReaction[9]->Fill(reweightevt.ReconShowerEnergy, weight);
				else if(isSigBDT==1)
				{
					if(std::abs(reaccode)==1)//ccqe	
						th1d_reconshowerenergy_NueReaction[0]->Fill(reweightevt.ReconShowerEnergy, weight);
					else if((std::abs(reaccode)>10&&std::abs(reaccode)<14)||std::abs(reaccode)==22||std::abs(reaccode)==23||(std::abs(reaccode)>=17&&std::abs(reaccode)<=20))
						th1d_reconshowerenergy_NueReaction[1]->Fill(reweightevt.ReconShowerEnergy, weight);
					else if(std::abs(reaccode)==2)
						th1d_reconshowerenergy_NueReaction[2]->Fill(reweightevt.ReconShowerEnergy, weight);
					else if(std::abs(reaccode)==16)
						 th1d_reconshowerenergy_NueReaction[3]->Fill(reweightevt.ReconShowerEnergy, weight);
					else if(std::abs(reaccode)==26)
						th1d_reconshowerenergy_NueReaction[4]->Fill(reweightevt.ReconShowerEnergy, weight);
					else if(std::abs(reaccode)==21)
						th1d_reconshowerenergy_NueReaction[5]->Fill(reweightevt.ReconShowerEnergy, weight);
					else //should not occur
						th1d_reconshowerenergy_NueReaction[6]->Fill(reweightevt.ReconShowerEnergy, weight);

					///
					if(isOnWater==1)
						onwatersig->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy, weight);
					else if(isOnWater==0)
						notwatersig->Fill(MCSamples_allConfigs[ic]->_signalSample->_sample[i].ReconShowerEnergy, weight);
					///
				}
				else
					th1d_reconshowerenergy_NueReaction[12]->Fill(reweightevt.ReconShowerEnergy, weight);
			}
			else if(nupdg==-12)
			{
				if(std::abs(reaccode)>30)//nc
					th1d_reconshowerenergy_NueReaction[9]->Fill(reweightevt.ReconShowerEnergy, weight);
				else//nuebarCC
					th1d_reconshowerenergy_NueReaction[7]->Fill(reweightevt.ReconShowerEnergy, weight);
			}
			else if(std::abs(nupdg)==14)//numu
			{
				if(std::abs(reaccode)>30)//nc
					th1d_reconshowerenergy_NueReaction[9]->Fill(reweightevt.ReconShowerEnergy, weight);
				else//numu numubar CC
					th1d_reconshowerenergy_NueReaction[8]->Fill(reweightevt.ReconShowerEnergy, weight);
			}
			else //unknown
				th1d_reconshowerenergy_NueReaction[11]->Fill(reweightevt.ReconShowerEnergy, weight);

		}
		else if(isinFV==0)
			th1d_reconshowerenergy_NueReaction[10]->Fill(reweightevt.ReconShowerEnergy, weight);
		else
			th1d_reconshowerenergy_NueReaction[11]->Fill(reweightevt.ReconShowerEnergy, weight);
	}

	///
	TCanvas* c1 = new TCanvas("c1", "c1");
	c1->cd();
	int nbins = templatehist->GetNbinsX();
	std::vector<double> totcnts(nbins, 0);
//	for(int i=0; i<NUEREAC; i++)
//	{
//		for(int ib=1; ib<nbins+1; ib++)
//			totcnts[ib-1] += th1d_reconshowerenergy_NueReaction[i]->GetBinContent(ib);
//
//		std::string name = differentiator+th1d_reconshowerenergy_NueReaction[i]->GetName()+"_waterconfig"+std::to_string(ic)+".pdf";
//		th1d_reconshowerenergy_NueReaction[i]->Draw("HIST");
//		c1->SaveAs(name.c_str());
//	}
	//print
	std::cout<<"Print cnt in waterconfig "<<ic<<" where differentiator = "<<differentiator<<std::endl;
	std::cout<<"	onwatersigcnts: ";
	for(int ib=1; ib<nbins+1; ib++)
		std::cout<<" "<<onwatersig->GetBinContent(ib);
	std::cout<<std::endl;
	std::string name1 = differentiator + onwatersig->GetName() + "_waterconfig"+std::to_string(ic)+".pdf";
	onwatersig->Draw("HIST TEXT");
	c1->SaveAs(name1.c_str());

	std::cout<<"	notwatersigcnts: ";
	for(int ib=1; ib<nbins+1; ib++)
		std::cout<<" "<<notwatersig->GetBinContent(ib);
	std::cout<<std::endl;
	name1 = differentiator + notwatersig->GetName() + "_waterconfig"+std::to_string(ic)+".pdf";
	notwatersig->Draw("HIST TEXT");
	c1->SaveAs(name1.c_str());

	std::cout<<"	totwatersigcnts: ";
	for(int ib=1; ib<nbins+1; ib++)
		std::cout<<" "<<totcnts[ib-1];
	std::cout<<std::endl;

	std::cout<<"Print signal sample in topology:"<<std::endl;
	for(int i=0; i<NUEREAC; i++)
	{
		std::cout<<NueReaction_types[i]<<" "<<th1d_reconshowerenergy_NueReaction[i]->GetEntries()<<std::endl;;
	}

//	for(int i=0; i<4; i++)
//	{
//		int tmpnbins = truenuE[i]->GetNbinsX();
//		std::cout<<"	flux "<< truenuE[i]->GetName()<<": ";
//		for(int ib=1; ib<tmpnbins+1; ib++)
//			std::cout<<" "<<truenuE[i]->GetBinContent(ib);
//		std::cout<<std::endl;
//
//		std::string name = differentiator + truenuE[i]->GetName() + "_waterconfig"+std::to_string(ic)+".pdf";
//		truenuE[i]->Draw("HIST TEXT");
//		c1->SaveAs(name.c_str());
//	}
	///
//	hs_reconshowerenergy_NueReaction->Draw();
//	hs_reconshowerenergy_NueReaction->GetXaxis()->SetTitle("ReconShowerEnergy(MeV)");
//	c1->Modified();
//	c1->BuildLegend(0.6,0.6,0.9,0.9,"");
//	c1->SaveAs("ReconShowerEnergy_signalsample.pdf");
//
//	for(int i=0; i<NUEREAC; i++)
//		delete th1d_reconshowerenergy_NueReaction[i];
//	delete hs_reconshowerenergy_NueReaction;
//	delete templatehist;
	delete c1;
	delete emptyMCSim;
	delete templatehist;
	///
	for(int i=0; i<4; i++)
		delete truenuE[i];
	///
	return hs_reconshowerenergy_NueReaction;
}

THStack* p0dNuEAnalysisLikelihood::GetNCBKControlSampleStack(int ic, const std::vector<double>& params, std::string differentiator)
{
	if(ic>=_curNConfigs||ic<0)
	{
		std::cout<<"No such configid (="<<ic<<")"<<std::endl;
		return NULL;
	}
	const int NTOPOLOGY = 10;
	std::string Topology_types[NTOPOLOGY] = {"NC1#pi^{0}",  "NC >1#pi^{0}", "NC >=1#pi^{#pm}", "NC Oth", "CC 1#pi^{0}",  "CC >1#pi^{0}", "CC >=1#pi^{#pm}", "CC Oth", "OOFV", "Unknow"};
	int Topology_colors[NTOPOLOGY] = {          3,         		kOrange,         kPink-7,   		5,        38,       		30,            46 ,     		2, 	  kViolet+1,     7};

	THStack* hs_reconinvariantmass = new THStack(("hs_reconinvariantmass_ncbkcs"+differentiator).c_str(), ("hs_reconinvariantmass_ncbk"+differentiator).c_str());
    TH1D* th1d_reconinvariantmass[NTOPOLOGY];
	MCSimUnit* emptyMCSim = new MCSimUnit();
	TH1D* templatehist = emptyMCSim->GetNCBKCSTemplateHistogram();
	for(int i=NTOPOLOGY-1; i>=0; i--)
	{
		th1d_reconinvariantmass[i]=(TH1D*) templatehist->Clone((Topology_types[i]+differentiator).c_str());
	 	th1d_reconinvariantmass[i]->SetFillColor(Topology_colors[i]);
		hs_reconinvariantmass->Add(th1d_reconinvariantmass[i]);
	}
	for(int i=0; i<MCSamples_allConfigs[ic]->_ncbkSample->_sample.size(); i++) //later may change what _ncbkSample contains so may modify some selections below
	{
		int reaccode =  MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].reactionCode;
		int nupdg = MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].NeutrinoPDG;
		int isinFV = MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].isinFV;

		MCEvent reweightevt = MCSamples_allConfigs[ic]->_ncbkSample->_sample[i];
//		double weight = Correction.ReweightEvent(reweightevt, MCSamples_allConfigs[ic]->_ncbkSample->_sample[i], params);
		double weight = Correction.ReweightNC1pi0CSEvent(reweightevt, MCSamples_allConfigs[ic]->_ncbkSample->_sample[i], params);
//		std::cout<<"reweightevt.ShowerEDepFraction = "<<reweightevt.ShowerEDepFraction<<std::endl;
		if(!(reweightevt.ShowerEDepFraction<_SCFCut[ic]&&reweightevt.twoshowerEDepfrac>0.85&&reweightevt.invariantmass>60&&reweightevt.invariantmass<200))
			continue;
//		std::cout<<"reweightevt.invariantmass, weight = "<<reweightevt.invariantmass<<" "<<weight<<std::endl;
		if(isinFV==1)
		{
			if(std::abs(reaccode)>30)
			{
				if(reweightevt.NtruePi0==1)
					th1d_reconinvariantmass[0]->Fill(reweightevt.invariantmass, weight);
				else if(reweightevt.NtruePi0>1)
					th1d_reconinvariantmass[1]->Fill(reweightevt.invariantmass, weight);
				else if(reweightevt.NtruePiCharge>0)
					th1d_reconinvariantmass[2]->Fill(reweightevt.invariantmass, weight);
				else
					th1d_reconinvariantmass[3]->Fill(reweightevt.invariantmass, weight);
			}
			else if(std::abs(nupdg)==12||std::abs(nupdg)==14)
			{
				if(reweightevt.NtruePi0==1)
					th1d_reconinvariantmass[4]->Fill(reweightevt.invariantmass, weight);
				else if(reweightevt.NtruePi0>1)
					th1d_reconinvariantmass[5]->Fill(reweightevt.invariantmass, weight);
				else if(reweightevt.NtruePiCharge>0)
					th1d_reconinvariantmass[6]->Fill(reweightevt.invariantmass, weight);
				else
					th1d_reconinvariantmass[7]->Fill(reweightevt.invariantmass, weight);
			}
			else
				th1d_reconinvariantmass[9]->Fill(reweightevt.invariantmass, weight);
		}
		else if(isinFV==0)
			th1d_reconinvariantmass[8]->Fill(reweightevt.invariantmass, weight);
		else
			th1d_reconinvariantmass[9]->Fill(reweightevt.invariantmass, weight);
	}
	std::cout<<"Print NCBKCS in topology:"<<std::endl;
	for(int i=0; i<NTOPOLOGY; i++)
	{
		std::cout<<Topology_types[i]<<" "<<th1d_reconinvariantmass[i]->GetEntries()<<std::endl;
	}

    delete emptyMCSim;
	delete templatehist;

	return hs_reconinvariantmass;
}
/*
THStack* p0dNuEAnalysisLikelihood::GetNCBKControlSampleStack(int ic, const std::vector<double>& params, std::string differentiator)
{
	//need to fill with param later
	if(ic>=_curNConfigs||ic<0)
	{
		std::cout<<"No such configid (="<<ic<<")"<<std::endl;
		return NULL;
	}
    const int NREAC = 11;
    std::string Reaction_types[NREAC] = {"NC Resonant #pi^{0}",  "NC Resonant #pi^{#pm}",  "NC Resonant #gamma", "NC Resonant Others", "NC Coherent #pi^{0}", "NC DIS", "NC LowWMultiPion", "{#nu}_{e}/#bar{#nu}_{e} CC", "#nu_{#mu}/#bar{#nu_{#mu}} CC",       "OOP0DFV",   "Unknow"};
	
	int Reaction_codes[NREAC] = {              0,               		  1,              			    2,                    3,          	       4,                5,	     	     6,                       7,                          8,                            9,          10};
	int Reaction_colors[NREAC]= {              2,                       3,                         kOrange,                 5,                   12,               9,              30,                     46,                         20,                          6,            7};

	THStack* hs_reconshowerenergy = new THStack(("hs_reconshowerenergy_ncbk"+differentiator).c_str(), ("hs_reconshowerenergy_ncbk"+differentiator).c_str());
    TH1D* th1d_reconshowerenergy[NREAC];
	MCSimUnit* emptyMCSim = new MCSimUnit();
	TH1D* templatehist = emptyMCSim->GetNCBKCSTemplateHistogram();
	for(int i=NREAC-1; i>=0; i--)
	{
		th1d_reconshowerenergy[i]=(TH1D*) templatehist->Clone(Reaction_types[i].c_str());
	 	th1d_reconshowerenergy[i]->SetFillColor(Reaction_colors[i]);
		hs_reconshowerenergy->Add(th1d_reconshowerenergy[i]);
	}

	for(int i=0; i<MCSamples_allConfigs[ic]->_ncbkSample->_sample.size(); i++)
	{
		int reaccode =  MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].reactionCode;
		int nupdg = MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].NeutrinoPDG;
		int isinFV = MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].isinFV;
		if(MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].ShowerEDepFraction>=_SCFCut[ic])
			continue;
		if(isinFV==1)
		{
			if(std::abs(reaccode)<30)
			{
				if(std::abs(nupdg)==12)
					th1d_reconshowerenergy[7]-> Fill(MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].invariantmass);
				else if(std::abs(nupdg)==14)
					th1d_reconshowerenergy[8]-> Fill(MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].invariantmass);
				else
					th1d_reconshowerenergy[10]->Fill(MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].invariantmass);
			}
			else if(std::abs(reaccode)==31||std::abs(reaccode)==32)
				th1d_reconshowerenergy[0]->Fill(MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].invariantmass);
			else if(std::abs(reaccode)==33||std::abs(reaccode)==34)
				th1d_reconshowerenergy[1]->Fill(MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].invariantmass);
			else if(std::abs(reaccode)==38||std::abs(reaccode)==39)
				th1d_reconshowerenergy[2]->Fill(MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].invariantmass);
			else if(std::abs(reaccode)>=42&&std::abs(reaccode)<=45)
				th1d_reconshowerenergy[3]->Fill(MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].invariantmass);
			else if(std::abs(reaccode)==36)
				th1d_reconshowerenergy[4]->Fill(MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].invariantmass);
			else if(std::abs(reaccode)==46)
				th1d_reconshowerenergy[5]->Fill(MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].invariantmass);
			else if(std::abs(reaccode)==41)
				th1d_reconshowerenergy[6]->Fill(MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].invariantmass);
			else
				th1d_reconshowerenergy[10]->Fill(MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].invariantmass);
		}
		else if(isinFV==0)
			th1d_reconshowerenergy[9]-> Fill(MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].invariantmass);
		else
			th1d_reconshowerenergy[10]->Fill(MCSamples_allConfigs[ic]->_ncbkSample->_sample[i].invariantmass);
	}

//	TCanvas* c1 = new TCanvas("c1", "c1");
//	c1->cd();
//	hs_reconshowerenergy->Draw();
//	hs_reconshowerenergy->GetXaxis()->SetTitle("ReconShowerEnergy(MeV)");
//	c1->Modified();
//	c1->BuildLegend(0.6,0.6,0.9,0.9,"");
//	c1->SaveAs("ReconShowerEnergy_ncbkcs.pdf");
//
//	for(int i=0; i<NUEREAC; i++)
//		delete th1d_reconshowerenergy[i];
//	delete hs_reconshowerenergy;
//	delete templatehist;
//	delete c1;

	delete emptyMCSim;
	delete templatehist;

	return hs_reconshowerenergy;
}
*/


THStack* p0dNuEAnalysisLikelihood::GetNumuControlSampleStack(int ic, const std::vector<double>& params, std::string differentiator)
{
	if(ic>=_curNConfigs||ic<0)
	{
		std::cout<<"No such configid (="<<ic<<")"<<std::endl;
		return NULL;
	}
    const int NREAC = 10;//#nu_{mu} here include both #{nu}_{mu} and #bar{nu}_{mu}
    std::string Reaction_types[NREAC] = {
    "#nu_{#mu} #bar{#nu_{#mu}} CCQE",   "#nu_{#mu} #bar{#nu_{#mu}}  CCRES",     "#nu_{#mu} #bar{#nu_{#mu}}  CC_COH",   "#nu_{#mu} #bar{#nu_{#mu}}  CC_DIS", "#nu_{#mu} #bar{#nu_{#mu}}  CCLowWMultiPi","#nu_{#mu} #bar{#nu_{#mu}} CCOthers", 
	"#nu_{e} #bar{#nu_{e}} CC",            "NC",                                  "OOP0DFV", 									"Unknown"};
    int Reaction_colors[NREAC]= { 2,               3,     kOrange,        5,         38,        30,              46,             20,      6, 7};

	THStack* hs_recontrackangle = new THStack(("hs_recontrackangle"+differentiator).c_str(), ("hs_recontrackangle"+differentiator).c_str());
    TH1D* th1d_recontrackangle[NREAC];
	MCSimUnit* emptyMCSim = new MCSimUnit();
	TH1D* templatehist = emptyMCSim->GetNumuCCBKCSTemplateHistogram();
	for(int i=NREAC-1; i>=0; i--)
	{
		th1d_recontrackangle[i] = (TH1D*) templatehist->Clone((Reaction_types[i]+differentiator).c_str());
	 	th1d_recontrackangle[i]->SetFillColor(Reaction_colors[i]);
		hs_recontrackangle->Add(th1d_recontrackangle[i]);
	}

	for(int i=0; i<MCSamples_allConfigs[ic]->_numccbkSample->_sample.size(); i++)
	{
		int reaccode =  MCSamples_allConfigs[ic]->_numccbkSample->_sample[i].reactionCode;
		int nupdg = MCSamples_allConfigs[ic]->_numccbkSample->_sample[i].NeutrinoPDG;
		int isinFV = MCSamples_allConfigs[ic]->_numccbkSample->_sample[i].isinFV;

		MCEvent reweightevt = MCSamples_allConfigs[ic]->_numccbkSample->_sample[i];
		double weight = Correction.ReweightEvent(reweightevt, MCSamples_allConfigs[ic]->_numccbkSample->_sample[i], params, 2);
//		std::cout<<"Event"<<i<<" reweightevt.LongestTrackLayers_atTrackReconStage="<<reweightevt.LongestTrackLayers_atTrackReconStage<<std::endl;
		if(reweightevt.LongestTrackLayers_atTrackReconStage<=23)
			continue;
		if(isinFV==1)
		{
			if(std::abs(reaccode)>30)
				th1d_recontrackangle[7]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage), weight);
			else if(std::abs(nupdg)==12)
				th1d_recontrackangle[6]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage), weight);
			else if(std::abs(nupdg)==14)
			{
				if(std::abs(reaccode)==1)
					th1d_recontrackangle[0]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage), weight);
				else if((std::abs(reaccode)>10&&std::abs(reaccode)<14)||(std::abs(reaccode)==22)||std::abs(reaccode)==23||(std::abs(reaccode)>=17&&std::abs(reaccode)<=20))
					th1d_recontrackangle[1]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage), weight);
				else if(std::abs(reaccode)==16)
					th1d_recontrackangle[2]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage), weight);
				else if(std::abs(reaccode)==26)
					th1d_recontrackangle[3]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage), weight);
				else if(std::abs(reaccode)==21)
					th1d_recontrackangle[4]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage), weight);
				else
					th1d_recontrackangle[5]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage), weight);
			}
			else
				th1d_recontrackangle[9]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage), weight);
		}
		else if(isinFV==0)
		{
			th1d_recontrackangle[8]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage), weight);
		}
		else
			th1d_recontrackangle[9]->Fill(TMath::ACos(reweightevt.LongestTrackCostheta_atTrackReconStage), weight);


	}

	std::cout<<"Print numuCCCS in topology:"<<std::endl;
	for(int i=0; i<NREAC; i++)
	{
		std::cout<<Reaction_types[i]<<" "<<th1d_recontrackangle[i]->GetEntries()<<std::endl;;
	}

    delete emptyMCSim;
	delete templatehist;

	return hs_recontrackangle;
}




