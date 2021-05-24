#include <iostream>
#include <vector>
#include <string>

#include "TFile.h"
#include "TMatrixD.h"
#include "TMatrixDSym.h"
#include "TTree.h"

void CreateDetSystInput(){

	bool _debug = true;

	TFile *outF = new TFile("detparam_input.root","recreate");
	TTree *outT = new TTree("detParams","det syst parameters");

	Int_t nParams = 0;
	std::vector<std::string> param_name;
	std::vector<double> nominal;
	std::vector<double> prior;
	std::vector<double> sigma;
	std::vector<double> lb;
	std::vector<double> ub;

	//Create an enum of all detector systematics

	enum{

		kDet_MassOnWater,
		kDet_MassNotWater1,//run1
		kDet_MassNotWater2,//run2 and later

		kDet_ShowerEnergyScaleECal,
		kDet_ShowerEnergyScaleWTWaterIn,
		kDet_ShowerEnergyScaleWTWaterOut,

//		kDet_VertexResolutionWaterInFHC, //negligible
//		kDet_VertexResolutionWaterOutFHC,
//		kDet_VertexResolutionWaterInRHC, // should be same with (very close to) kDet_VertexResolutionWaterInFHC
//		kDet_VertexResolutionWaterOutRHC,// should be same with (very close to) kDet_VertexResolutionWaterInFHC
		kDet_OOFVPi0Events,

		kDet_EMShowerMedianWidthScaleWaterInFHC,
		kDet_EMShowerMedianWidthScaleWaterOutFHC,
		kDet_EMShowerMedianWidthScaleWaterInRHC,
		kDet_EMShowerMedianWidthScaleWaterOutRHC,

		kDet_HadronShowerMedianWidthScaleWaterInFHC,
		kDet_HadronShowerMedianWidthScaleWaterOutFHC,
		kDet_HadronShowerMedianWidthScaleWaterInRHC,
		kDet_HadronShowerMedianWidthScaleWaterOutRHC,

		kDet_ShowerEDepFractionScaleWaterInFHC,
		kDet_ShowerEDepFractionScaleWaterOutFHC,
		kDet_ShowerEDepFractionScaleWaterInRHC,
		kDet_ShowerEDepFractionScaleWaterOutRHC,
//		kDet_ShowerChargeFractionScaleWaterInFHC,
//		kDet_ShowerChargeFractionScaleWaterOutFHC,
//		kDet_ShowerChargeFractionScaleWaterInRHC,
//		kDet_ShowerChargeFractionScaleWaterOutRHC,

		KDet_PIDSystWaterInFHC,
		KDet_PIDSystWaterOutFHC,
		KDet_PIDSystWaterInRHC,
		KDet_PIDSystWaterOutRHC,

		//for nc1pi0 CS only
		kDet_PhotonEnergyScaleECal_SLOPE,
		kDet_PhotonEnergyScaleWTWaterIn_SLOPE,
		kDet_PhotonEnergyScaleWTWaterOut_SLOPE,
		kDet_PhotonEnergyScaleECal_INT,
		kDet_PhotonEnergyScaleWTWaterIn_INT,
		kDet_PhotonEnergyScaleWTWaterOut_INT,

		kDet_ChargeRatioScaleNC1pi0WaterIn,
		kDet_ChargeRatioScaleOthWaterIn,
		kDet_ChargeRatioScaleNC1pi0WaterOut,
		kDet_ChargeRatioScaleOthWaterOut,

		//end of nc1pi0 CS only

		kDet_p0dNuEDetSystEnd,
	};

	//Mass on Water
	param_name.push_back("kDet_MassOnWater");
	nominal.push_back(1);
	prior.push_back(0.989);
	sigma.push_back(0.008);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;

	//Mass NOT Water Run1
	param_name.push_back("kDet_MassNotWater1");
	nominal.push_back(1);
	prior.push_back(1.026);
	sigma.push_back(0.01);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;

	//Mass NOT Water Run2+
	param_name.push_back("kDet_MassNotWater2");
	nominal.push_back(1);
	prior.push_back(1.031);
	sigma.push_back(0.01);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;

	//Energy Scale
	param_name.push_back("kDet_ShowerEnergyScaleECal");//scaled to nominal 1
	nominal.push_back(1);
	prior.push_back(1);
	sigma.push_back(0.07);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;

	param_name.push_back("kDet_ShowerEnergyScaleWTWaterIn");
	nominal.push_back(1);
	prior.push_back(1);
	sigma.push_back(0.038);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;

	param_name.push_back("kDet_ShowerEnergyScaleWTWaterOut");
	nominal.push_back(1);
	prior.push_back(1.0);
	sigma.push_back(0.11);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;
/*
	param_name.push_back("kDet_VertexResolutionWaterInFHC");
	nominal.push_back();
	prior.push_back();
	sigma.push_back();
	lb.push_back();
	ub.push_back();
	nParams++;
*/
	param_name.push_back("kDet_OOFVPi0Events");
	nominal.push_back(1);
	prior.push_back(1);
	sigma.push_back(1);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;

	// ****************************** //
	param_name.push_back("kDet_EMShowerMedianWidthScaleWaterInFHC");
	nominal.push_back(1);
	prior.push_back(0.96);
	sigma.push_back(0.06);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;

	//values need to be changed
	param_name.push_back("kDet_EMShowerMedianWidthScaleWaterOutFHC");
	nominal.push_back(1);
	prior.push_back(0.96);
	sigma.push_back(0.06);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;
/*
	param_name.push_back("kDet_EMShowerMedianWidthScaleWaterInRHC");
	nominal.push_back(1);
	prior.push_back(0.96);
	sigma.push_back(0.06);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;

	param_name.push_back("kDet_EMShowerMedianWidthScaleWaterOutRHC");
	nominal.push_back(1);
	prior.push_back(0.96);
	sigma.push_back(0.06);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;
*/
	// ****************************** //

	param_name.push_back("kDet_HadronShowerMedianWidthScaleWaterInFHC");
	nominal.push_back(1);
	prior.push_back(1.06);
	sigma.push_back(0.03);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;

	param_name.push_back("kDet_HadronShowerMedianWidthScaleWaterOutFHC");
	nominal.push_back(1);
	prior.push_back(1.06);
	sigma.push_back(0.03);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;
/*
	param_name.push_back("kDet_HadronShowerMedianWidthScaleWaterInRHC");
	nominal.push_back(1);
	prior.push_back(1.06);
	sigma.push_back(0.03);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;

	param_name.push_back("kDet_HadronShowerMedianWidthScaleWaterOutRHC");
	nominal.push_back(1);
	prior.push_back(1.06);
	sigma.push_back(0.03);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;
*/
	// ****************************** //

	param_name.push_back("kDet_ShowerEDepFractionScaleWaterInFHC");
//	param_name.push_back("kDet_ShowerChargeFractionScaleWaterInFHC");
	nominal.push_back(1);
	prior.push_back(1.006);
	sigma.push_back(0.01);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;

	param_name.push_back("kDet_ShowerEDepFractionScaleWaterOutFHC");
	nominal.push_back(1);
	prior.push_back(1.006);
	sigma.push_back(0.01);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;
/*
	param_name.push_back("kDet_ShowerEDepFractionScaleWaterInRHC");
	nominal.push_back(1);
	prior.push_back(1.006);
	sigma.push_back(0.01);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;

	param_name.push_back("kDet_ShowerEDepFractionScaleWaterOutRHC");
	nominal.push_back(1);
	prior.push_back(1.006);
	sigma.push_back(0.01);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;
*/

	// ****************************** //

	param_name.push_back("kDet_PIDSystWaterInFHC");
	nominal.push_back(1);
	prior.push_back(1);
	sigma.push_back(0.01);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;

	param_name.push_back("kDet_PIDSystWaterOutFHC");
	nominal.push_back(1);
	prior.push_back(1);
	sigma.push_back(0.018);
	lb.push_back(0);
	ub.push_back(10);
	nParams++;

	//below for nc1pi0 cs, are from nc1pi0 analysis
	param_name.push_back("kDet_PhotonEnergyScaleECal_SLOPE");//scaled to nominal 1
	nominal.push_back(1);
	prior.push_back(1);
	sigma.push_back(0.095); //0.025/0.262
	lb.push_back(-10);
	ub.push_back(10);
	nParams++;

	param_name.push_back("kDet_PhotonEnergyScaleECal_INT");//scaled to nominal 1
	nominal.push_back(1);
	prior.push_back(1);
	sigma.push_back(0.54); //16.0/29.6
	lb.push_back(-10);
	ub.push_back(10);
	nParams++;

	param_name.push_back("kDet_PhotonEnergyScaleWTWaterIn_SLOPE");//scaled to nominal 1
	nominal.push_back(1);
	prior.push_back(1);
	sigma.push_back(0.097); // 0.019/0.197
	lb.push_back(-10);
	ub.push_back(10);
	nParams++;

	param_name.push_back("kDet_PhotonEnergyScaleWTWaterIn_INT");//scaled to nominal 1
	nominal.push_back(1);
	prior.push_back(1);
	sigma.push_back(1); // 14.2/14.1
	lb.push_back(-10);
	ub.push_back(10);
	nParams++;

	param_name.push_back("kDet_PhotonEnergyScaleWTWaterOut_SLOPE");//scaled to nominal 1
	nominal.push_back(1);
	prior.push_back(1);
	sigma.push_back(0.09); // 0.011/0.121
	lb.push_back(-10);
	ub.push_back(10);
	nParams++;

	param_name.push_back("kDet_PhotonEnergyScaleWTWaterOut_INT");//scaled to nominal 1
	nominal.push_back(1);
	prior.push_back(1);
	sigma.push_back(10); // 13.0/1.3.. = 10
	lb.push_back(-100); //this number is given without solid reason
	ub.push_back(100);
	nParams++;

	param_name.push_back("kDet_ChargeRatioScaleNC1pi0WaterIn");
	nominal.push_back(0);
	prior.push_back(0.022);
	sigma.push_back(0.015);
	lb.push_back(-1);
	ub.push_back(1);
	nParams++;

	//Charge Ratio Scale Bkg (CR' = CR*(1-scale))
	param_name.push_back("kDet_ChargeRatioScaleOthWaterIn");
	nominal.push_back(0);
	prior.push_back(0.005);
	sigma.push_back(0.005);
	lb.push_back(-1);
	ub.push_back(1);
	nParams++;

	//Charge Ratio Scale Signal (CR' = CR*(1-scale))
	param_name.push_back("kDet_ChargeRatioScaleNC1pi0WaterOut");
	nominal.push_back(0);
	prior.push_back(0.032);
	sigma.push_back(0.015);
	lb.push_back(-1);
	ub.push_back(1);
	nParams++;

	//Charge Ratio Scale Bkg (CR' = CR*(1-scale))
	param_name.push_back("kDet_ChargeRatioScaleOthWaterOut");
	nominal.push_back(0);
	prior.push_back(0.005);
	sigma.push_back(0.0047);
	lb.push_back(-1);
	ub.push_back(1);
	nParams++;
	// ****************************** //
/*
	param_name.push_back();
	nominal.push_back();
	prior.push_back();
	sigma.push_back();
	lb.push_back();
	ub.push_back();
	nParams++;
		kDet_VertexResolutionWaterInFHC,
		kDet_VertexResolutionWaterOutFHC,
		kDet_VertexResolutionWaterInRHC, // should be same with (very close to) kDet_VertexResolutionWaterInFHC
		kDet_VertexResolutionWaterOutRHC,// should be same with (very close to) kDet_VertexResolutionWaterInFHC
		kDet_OOFVPi0Events,

*/

  //The Covariance Matrix
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
}
