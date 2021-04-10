#include <sstream> 
#include "SystematicUncertaintyCorr.h"


double SystematicUncertaintyCorr::ReweightEvent(MCEvent& reweightedevt, const MCEvent& nominalevt, const std::vector<double>& param) const
{
	double weight = 1.0;

	if(fitparam.det_params)
	{
		reweightedevt.ShowerMedianWidth = CalShowerMedianWidthWithSyst(nominalevt, param);
		if(_debugweight&&reweightedevt.ShowerMedianWidth!=nominalevt.ShowerMedianWidth)
			std::cout<<nominalevt.EventID<<"reweightedevt.ShowerMedianWidth = "<<reweightedevt.ShowerMedianWidth<<" !=nominalevt.ShowerMedianWidth = "<<nominalevt.ShowerMedianWidth<<std::endl;
		reweightedevt.ShowerEDepFraction = CalShowerEDepFractionWithSyst(nominalevt, param);
		if(_debugweight&&reweightedevt.ShowerEDepFraction!=nominalevt.ShowerEDepFraction)
			std::cout<<nominalevt.EventID<<"reweightedevt.ShowerEDepFraction = "<<reweightedevt.ShowerEDepFraction<<" !=nominalevt.ShowerEDepFraction = "<<nominalevt.ShowerEDepFraction<<std::endl;
		reweightedevt.ReconShowerEnergy = CalReconShowerEnergyWithSyst(nominalevt, param);
		if(_debugweight&&reweightedevt.ReconShowerEnergy!=nominalevt.ReconShowerEnergy)
			std::cout<<nominalevt.EventID<<"reweightedevt.ReconShowerEnergy = "<<reweightedevt.ReconShowerEnergy<<" !=nominalevt.ReconShowerEnergy = "<<nominalevt.ReconShowerEnergy<<std::endl;
	}
		
	if(fitparam.sigwt_params)
	{
		weight*=CalcSignalEventWeight(nominalevt, param);
		if(_debugweight&&weight!=1)
			std::cout<<nominalevt.EventID<<" weight after CalcSignalEventWeight = "<<weight<<std::endl;
	}
	
	if(fitparam.det_params)
	{
		weight*=CalPIDSystWeight(nominalevt, param);
		if(_debugweight&&weight!=1)
			std::cout<<nominalevt.EventID<<" weight after CalcPIDSystWeight = "<<weight<<std::endl;
		weight*=CalcMassSystWeight(nominalevt, param);
		if(_debugweight&&weight!=1)
			std::cout<<nominalevt.EventID<<" weight after CalcMassSystWeight = "<<weight<<std::endl;
		weight*=CalOOFVPi0WeightSyst(nominalevt, param);
		if(_debugweight&&weight!=1)
			std::cout<<nominalevt.EventID<<" weight after CalOOFVPi0WeightSyst = "<<weight<<std::endl;
	}	

	if(fitparam.xsec_params)
	{
		weight*=CalcXSecFSISystWeightFromT2KReweight(nominalevt, param);
		if(_debugweight&&weight!=1)
			std::cout<<nominalevt.EventID<<" weight after CalcXSecFSISystWeightFromT2KReweight = "<<weight<<std::endl;
		weight*=CalcXSecNormSystWeight(nominalevt, param);
		if(_debugweight&&weight!=1)
			std::cout<<nominalevt.EventID<<" weight after CalcXSecNormSystWeight = "<<weight<<std::endl;
	}
	
	if(fitparam.flux_params)
	{
		weight*=CalcFluxSystWeight(nominalevt, param);
		if(_debugweight&&weight!=1)
			std::cout<<nominalevt.EventID<<" weight after CalcFluxSystWeight = "<<weight<<std::endl;
	}
	
	return weight;
}

double SystematicUncertaintyCorr::ReweightEvent(MCEvent& reweightedevt, const MCEvent& nominalevt, const std::vector<double>& param, int sampleid ) const//sampleid, whether ncbk or numubk 
{
	//rough for now. need more in the future
	double weight = 1.0;
//	weight*=CalcMassSystWeight(nominalevt, param);
//	weight*=CalOOFVPi0WeightSyst(nominalevt, param);
	weight*=CalcXSecFSISystWeightFromT2KReweight(nominalevt, param);
	weight*=CalcXSecNormSystWeight(nominalevt, param);
	weight*=CalcFluxSystWeight(nominalevt, param);

	return weight;
}
double SystematicUncertaintyCorr::CalReconShowerEnergyWithSyst(const MCEvent& nominalevt, const std::vector<double>& param) const
{
	int ecalparaindex = fitparam.GetParamIndexFromExactName("kDet_ShowerEnergyScaleECal");
	std::string wtparaname = (nominalevt.isWaterConfig ? "kDet_ShowerEnergyScaleWTWaterIn":"kDet_ShowerEnergyScaleWTWaterOut");
	int wtparaindex = fitparam.GetParamIndexFromExactName(wtparaname);
	double scale = 1;
	if(nominalevt.isWaterConfig)
		scale=nominalevt.WTCharges/(nominalevt.WTCharges+nominalevt.ECalCharges)*FitParams::EM_SCALE_SHOWER_WTWATERIN*param[wtparaindex]+nominalevt.ECalCharges/(nominalevt.WTCharges+nominalevt.ECalCharges)*FitParams::EM_SCALE_SHOWER_ECAL*param[ecalparaindex];
	else
		scale = nominalevt.WTCharges/(nominalevt.WTCharges+nominalevt.ECalCharges)*FitParams::EM_SCALE_SHOWER_WTWATEROUT*param[wtparaindex]+nominalevt.ECalCharges/(nominalevt.WTCharges+nominalevt.ECalCharges)*FitParams::EM_SCALE_SHOWER_ECAL*param[ecalparaindex];
	
	return scale*nominalevt.EDeposit;
}

double SystematicUncertaintyCorr::CalShowerMedianWidthWithSyst(const MCEvent& nominalevt, const std::vector<double>& param) const
{
	std::string paramname = "";
//	int showertype = 0;// 1: EM, 2 Hadron
	if(std::abs(nominalevt.MostProbableTrueParticlePDG)==11||nominalevt.MostProbableTrueParticlePDG==22)
		paramname += "kDet_EMShowerMedianWidthScale";
//		showertype = 1;
	else// if(std::abs(nominalevt.MostProbableTrueParticlePDG)==2212||std::abs(nominalevt.MostProbableTrueParticlePDG)==211)	
		paramname += "kDet_HadronShowerMedianWidthScale";
//		showertype = 2;
	if(nominalevt.isWaterConfig<0||nominalevt.numode<0){
		std::cerr<<"Event in not in any available configuration: "<<nominalevt.isWaterConfig<<" "<<nominalevt.numode<<" Please Check!"<<std::endl;
		exit(0);
	}

	if(_debugweight&&paramname=="")
	{
		std::cout<<"Shower is caused by neither EM or Hadron!!!"<<" MostProbableTrueParticlePDG = "<<nominalevt.MostProbableTrueParticlePDG<<std::endl;
		return 1.0;
	}
	paramname+= (nominalevt.isWaterConfig ? "WaterIn":"WaterOut");
	paramname+= (nominalevt.numode ? "FHC":"RHC");

	if(_debug) 
		std::cout<<"paramname = "<<paramname<<std::endl;

	int paramindex = fitparam.GetParamIndexFromExactName(paramname);//validation of the parameter has been checked inside the function
	//added on 03/18/2021 for now. should return back to exit(0) in fitparam.GetParamIndexFromExactName
	if(paramindex==-1)
		return  nominalevt.ShowerMedianWidth;
	return nominalevt.ShowerMedianWidth*param[paramindex];//return the new SMW value
}

double SystematicUncertaintyCorr::CalShowerEDepFractionWithSyst(const MCEvent& nominalevt, const std::vector<double>& param) const
{
	std::string paramname = "kDet_ShowerEDepFractionScale";
	paramname+= (nominalevt.isWaterConfig ? "WaterIn":"WaterOut");
	paramname+= (nominalevt.numode ? "FHC":"RHC");

	if(_debug) 
		std::cout<<"paramname = "<<paramname<<std::endl;

	int paramindex = fitparam.GetParamIndexFromExactName(paramname);//validation of the parameter has been checked inside the function
	return nominalevt.ShowerEDepFraction*param[paramindex];//return the new SCF value
}

double SystematicUncertaintyCorr::CalcMassSystWeight(const MCEvent& nominalevt, const std::vector<double>& param) const{

	double weight = 1.0;
	std::string paramname = "kDet_Mass";
	if(nominalevt.isOnWater==1)
		paramname+="OnWater";
	else{
		if(nominalevt.RunID==1)
			paramname+="NotWater1";
		else
			paramname+="NotWater2";
	}
	int paramindex =  fitparam.GetParamIndexFromExactName(paramname);
	weight*=param[paramindex];
	if(_debugweight&&weight!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<paramname<<" weight = "<< weight<<std::endl;
	
	return weight;
}

double SystematicUncertaintyCorr::CalPIDSystWeight(const MCEvent& nominalevt, const std::vector<double>& param) const
{
	double weight = 1.0;
	std::string paramname = "kDet_PIDSyst";
	paramname+= (nominalevt.isWaterConfig ? "WaterIn":"WaterOut");
	paramname+= (nominalevt.numode ? "FHC":"RHC");
	int paramindex =  fitparam.GetParamIndexFromExactName(paramname);
	weight*=param[paramindex];
	if(_debugweight&&weight!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<paramname<<" weight = "<< weight<<std::endl;
	
	return weight;

}

double SystematicUncertaintyCorr::CalOOFVPi0WeightSyst(const MCEvent& nominalevt, const std::vector<double>& param) const
{
	if(nominalevt.isinFV)
		return 1.0;
	else if(std::abs(nominalevt.reactionCode)>30&&nominalevt.NPrimaryPi0s>0)//ncpi0 oofv
	{
		double weight = param[fitparam.GetParamIndexFromExactName("kDet_OOFVPi0Events")];
		if(_debugweight&&weight!=1)
			std::cout<<"Event"<<nominalevt.EventID<<" "<<"kDet_OOFVPi0Events"<<" weight = "<< weight<<std::endl;
		return param[fitparam.GetParamIndexFromExactName("kDet_OOFVPi0Events")];
	}
	else
		return 1.0;
}

double SystematicUncertaintyCorr::CalcXSecFSISystWeightFromT2KReweight(const MCEvent& nominalevt, const std::vector<double>& param) const{
	
	if(nominalevt.isSignal==1)//skip signal
		return 1.0;

	double weight = 1.0;
	int paramindex = -1;

	if(!nominalevt.spline_MaCCQE)
	{
		std::cerr<<"spline_MaCCQE of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
		exit(0);
	}
	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_MaCCQE->GetName());
	weight*= nominalevt.spline_MaCCQE->Eval(param[paramindex]);
	if(_debugweight&&nominalevt.spline_MaCCQE->Eval(param[paramindex])!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<"CCQE"<<" weight = "<< weight<<std::endl;

	if(!nominalevt.spline_MaRES)
	{
		std::cerr<<"spline_maRES of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
		exit(0);
	}
	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_MaRES->GetName());
	weight*= nominalevt.spline_MaRES->Eval(param[paramindex]);
	if(_debugweight&&nominalevt.spline_MaRES->Eval(param[paramindex])!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<"MaRES"<<" weight = "<<nominalevt.spline_MaRES->Eval(param[paramindex])<<std::endl;
/*
 *comment for now 04/03 because graph of CA5 looks a bit strange
	if(!nominalevt.spline_CA5) 	                   
	{
		std::cerr<<"spline_CA5 of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
		exit(0);
	}
	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_CA5->GetName());
	weight*= nominalevt.spline_CA5->Eval(param[paramindex]);
	if(_debugweight&&nominalevt.spline_CA5->Eval(param[paramindex])!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<"CA5"<<" weight = "<< nominalevt.spline_CA5->Eval(param[paramindex])<<" "<<param[paramindex]<<std::endl;
*/
	if(!nominalevt.spline_ISO_BKG)                 
	{
		std::cerr<<"spline_ISO_BKG of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
		exit(0);
	}
	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_ISO_BKG->GetName());
	weight*= nominalevt.spline_ISO_BKG->Eval(param[paramindex]);
	if(_debugweight&&nominalevt.spline_ISO_BKG->Eval(param[paramindex])!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<"nominalevt.spline_ISO_BKG-"<<" weight = "<< weight<<std::endl;

	if(!nominalevt.spline_FSI_PI_ABS)              
	{
		std::cerr<<"spline_FSI_PI_ABS of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
		exit(0);
	}
	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_FSI_PI_ABS->GetName());
	weight*= nominalevt.spline_FSI_PI_ABS->Eval(param[paramindex]);
	if(_debugweight&&nominalevt.spline_FSI_PI_ABS->Eval(param[paramindex])!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<"nominalevt.spline_FSI_PI_ABS"<<" weight = "<< weight<<std::endl;

	if(!nominalevt.spline_FSI_CEX_LO)              
	{
		std::cerr<<"spline_FSI_CEX_LO of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
		exit(0);
	}
	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_FSI_CEX_LO->GetName());
	weight*= nominalevt.spline_FSI_CEX_LO->Eval(param[paramindex]);
	if(_debugweight&&nominalevt.spline_FSI_CEX_LO->Eval(param[paramindex])!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<"nominalevt.spline_FSI_CEX_LO"<<" weight = "<< weight<<std::endl;

	if(!nominalevt.spline_FSI_INEL_LO)             
	{
		std::cerr<<"spline_FSI_INEL_LO of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
		exit(0);
	}
	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_FSI_INEL_LO->GetName());
	weight*= nominalevt.spline_FSI_INEL_LO->Eval(param[paramindex]);
	if(_debugweight&&nominalevt.spline_FSI_INEL_LO->Eval(param[paramindex])!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<"nominalevt.spline_FSI_INEL_LO"<<" weight = "<< weight<<std::endl;
//	if(!nominalevt.spline_FSI_CEX_HI)              
//	{
//		std::cerr<<"spline_FSI_CEX_HI of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
//		exit(0);
//	}
//	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_FSI_CEX_HI->GetName());
//	weight*= nominalevt.spline_FSI_CEX_HI->Eval(param[paramindex]);
	if(!nominalevt.spline_FSI_INEL_HI)             
	{
		std::cerr<<"spline_FSI_INEL_HI of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
		exit(0);
	}
	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_FSI_INEL_HI->GetName());
	weight*= nominalevt.spline_FSI_INEL_HI->Eval(param[paramindex]);
	if(_debugweight&&nominalevt.spline_FSI_INEL_HI->Eval(param[paramindex])!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<"nominalevt.spline_FSI_INEL_HI"<<" weight = "<< weight<<std::endl;

	if(!nominalevt.spline_FSI_PI_PROD)              
	{
		std::cerr<<"spline_FSI_PI_PROD of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
		exit(0);
	}
	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_FSI_PI_PROD->GetName());
	weight*= nominalevt.spline_FSI_PI_PROD->Eval(param[paramindex]);
	if(_debugweight && nominalevt.spline_FSI_PI_PROD->Eval(param[paramindex])!=1)
	{
		if(nominalevt.EventID==1804522)
		{
			TCanvas* c1 = new TCanvas("c1", "c1");
			c1->cd();
			nominalevt.spline_FSI_PI_PROD->Draw();
			std::string name = std::to_string(nominalevt.EventID)+nominalevt.spline_FSI_PI_PROD->GetName()+".pdf";
			c1->SaveAs(name.c_str());
			std::cout<<"Event"<<nominalevt.EventID<<" "<<"nominalevt.spline_FSI_PI_PROD"<<" weight = "<< weight<<" "<<param[paramindex]<<std::endl;
		}
	}

	if(!nominalevt.spline_NIWG_DIS_BY)             
	{
		std::cerr<<"spline_NIWG_DIS_BY of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
		exit(0);
	}
	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_NIWG_DIS_BY->GetName());
	weight*= nominalevt.spline_NIWG_DIS_BY->Eval(param[paramindex]);
	if(_debugweight&&nominalevt.spline_NIWG_DIS_BY->Eval(param[paramindex])!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<"nominalevt.spline_NIWG_DIS_BY-"<<" weight = "<< weight<<std::endl;

	if(!nominalevt.spline_NIWG_MultiPi_BY)         
	{
		std::cerr<<"spline_NIWG_MultiPi_BY of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
		exit(0);
	}
	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_NIWG_MultiPi_BY->GetName());
	weight*= nominalevt.spline_NIWG_MultiPi_BY->Eval(param[paramindex]);
	if(_debugweight&&nominalevt.spline_NIWG_MultiPi_BY->Eval(param[paramindex])!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<"nominalevt.spline_NIWG_MultiPi_BY"<<" weight = "<< weight<<std::endl;

	if(!nominalevt.spline_NIWG_MultiPi_Xsec_AGKY)  
	{
		std::cerr<<"spline_NIWG_MultiPi_Xsec_AGKY of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
		exit(0);
	}
	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_NIWG_MultiPi_Xsec_AGKY->GetName());
	weight*= nominalevt.spline_NIWG_MultiPi_Xsec_AGKY->Eval(param[paramindex]);
	if(_debugweight&&nominalevt.spline_NIWG_MultiPi_Xsec_AGKY->Eval(param[paramindex])!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<"nominalevt.spline_NIWG_MultiPi_Xsec_AGKY"<<" weight = "<< weight<<std::endl;
//	if(!nominalevt.spline_NIWG2012a_nc1piE0)       
//	{
//		std::cerr<<"spline_NIWG2012a_nc1piE0 of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
//		exit(0);
//	}
//	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_NIWG2012a_nc1piE0->GetName());
//	weight*= nominalevt.spline_NIWG2012a_nc1piE0->Eval(param[paramindex]);
	if(!nominalevt.spline_NIWG2012a_nccohE0)       
	{
		std::cerr<<"spline_NIWG2012a_nccohE0 of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
		exit(0);
	}
	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_NIWG2012a_nccohE0->GetName());
	weight*= nominalevt.spline_NIWG2012a_nccohE0->Eval(param[paramindex]);
	if(_debugweight&&nominalevt.spline_NIWG2012a_nccohE0->Eval(param[paramindex])!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<"nominalevt.spline_NIWG2012a_nccohE0"<<" weight = "<< weight<<std::endl;

	if(!nominalevt.spline_NIWG2012a_ncotherE0)     
	{
		std::cerr<<"spline_NIWG2012a_ncotherE0 of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
		exit(0);
	}
	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_NIWG2012a_ncotherE0->GetName());
	weight*= nominalevt.spline_NIWG2012a_ncotherE0->Eval(param[paramindex]);
	if(_debugweight&&nominalevt.spline_NIWG2012a_ncotherE0->Eval(param[paramindex])!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<"nominalevt.spline_NIWG2012a_ncotherE0"<<" weight = "<< weight<<std::endl;
	if(!nominalevt.spline_NIWG2012a_nc1pi0E0)      
	{
		std::cerr<<"spline_NIWG2012a_nc1pi0E0 of evt "<<nominalevt.EventID<<" is NULL"<<std::endl;
		exit(0);
	}
	paramindex = fitparam.GetParamIndexFromExactName(nominalevt.spline_NIWG2012a_nc1pi0E0->GetName());
	weight*= nominalevt.spline_NIWG2012a_nc1pi0E0->Eval(param[paramindex]);
	if(_debugweight&&nominalevt.spline_NIWG2012a_nc1pi0E0->Eval(param[paramindex])!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<"nominalevt.spline_NIWG2012a_nc1pi0E0"<<" weight = "<< weight<<std::endl;




	// add all xsec and fsi param used in t2k-reweight for this analysis

	return weight;
}

double SystematicUncertaintyCorr::CalcXSecNormSystWeight(const MCEvent& nominalevt, const std::vector<double>& param) const{

	double weight = 1.0;
	// to add parameters here
	
	return weight;
}


double SystematicUncertaintyCorr::CalcFluxSystWeight(const MCEvent& nominalevt, const std::vector<double>& param) const{

	double weight = 1.0;

//	int bin = fitparam.GetNeutrinoEnergyBinIndex(nominalevt.numode, nominalevt.NeutrinoPDG, nominalevt.TrueNeutrinoEnergy);
	std::string paramname = "nd5_";
	if(nominalevt.numode==1)//FHC
		paramname+="numode_";	
	else if(nominalevt.numode==0)//RHC
		paramname+="anumode_";
	else{ //something is wrong
		std::cerr<<"In CalcFluxSystWeight, this event is in neither FHC nor RHC. Something is wrong"<<std::endl;
		exit(0);
	}
	if(nominalevt.NeutrinoPDG==14)
		paramname+="numu_";
	else if(nominalevt.NeutrinoPDG==-14)
		paramname+="numub_";
	else if(nominalevt.NeutrinoPDG==12)
		paramname+="nue_";
	else if(nominalevt.NeutrinoPDG==-12)
		paramname+="nueb_";
	else{
//		std::cerr<<"In CalcFluxSystWeight, this neutrino is not numu, numub, nue or nueb: "<<nominalevt.NeutrinoPDG<<". The EventID is "<<nominalevt.EventID<<" ReconShowerEnergy = "<<nominalevt.ReconShowerEnergy<<std::endl;
		return 1;//this line is added on 03/16/2021
	}
	//gcc4.8 doesn't have std::to_string. to make sure this program can be compile in both gcc4.8 and gcc6, use stringstream below
	std::stringstream sstmp;
	sstmp << fitparam.GetNeutrinoEnergyBinIndex(nominalevt.numode, nominalevt.NeutrinoPDG, nominalevt.TrueNeutrinoEnergy);
	paramname+=("bin"+sstmp.str());

	int idx = fitparam.GetParamIndexFromExactName(paramname);
	if(idx==-1) //overflow or underflow, so doesn;t count for now...
	{
		std::cout<<"Event "<<nominalevt.EventID<<" paramname = "<<paramname<<" idx = -1"<<std::endl;
		return 0;
	}
	weight*=param[idx];
	if(_debugweight&&weight!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<paramname<<" weight = "<< weight<<std::endl;
	return weight;
}

double SystematicUncertaintyCorr::CalcSignalEventWeight(const MCEvent& nominalevt, const std::vector<double>& param) const
{
	double weight = 1.0;
	std::string paramname = "ksigwt";
	if(nominalevt.isSignal!=1)//==0)
		return weight;
	int binindex = binobj.GetBinIndex(nominalevt.totTrueParKin);
	std::stringstream sstmp;
	sstmp<<binindex;
	if(nominalevt.isSignal==1&&nominalevt.NeutrinoPDG==12)//nue 
		paramname += "_nueCC";
//	else if(nominalevt.isSignal==1&&nominalevt.NeutrinoPDG==-12)//for antinue in RHC. in FHC, isSignal would be 0
//		paramname += "_nuebarCC";
	else{
		std::cout<<"In CalcSignalEventWeight, found a event whose isSignal but not from nue"<<std::endl;//"from neither nue nor nuebar"<<std::endl;
//		return 0;
		exit(0);
	}

	paramname += ((nominalevt.isOnWater==1) ? "_onwater" : "_notwater");
	paramname += ("_bin"+sstmp.str());
//	paramname += ((nominalevt.isWaterConfig==1) ? "_waterin":"_waterout" );
//	paramname += ((nominalevt.numode==1) ? "_FHC":"_RHC");
	weight*=param[fitparam.GetParamIndexFromExactName(paramname)];	
	if(_debugweight&&weight!=1)
		std::cout<<"Event"<<nominalevt.EventID<<" "<<paramname<<" weight = "<< weight<<std::endl;
	return weight;
}



