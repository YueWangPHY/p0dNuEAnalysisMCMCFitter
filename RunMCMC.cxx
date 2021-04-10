/*************************************************
To run:
 g++ `root-config --cflags` -g -o RunMCMC RunMCMC.C -I`root-config --incdir` -I./ `root-config --glibs --libs`
./RunMCMC -m NominalMCWater.root -p MCPOTWater -n NominalMCAir.root -q MCPOTAir -d DataWater.root -t DataPOTWater -e DataAir.root -u DataPOTAir -r SplinesWater.root -s SplinesAir.root -o Output.root
************************************************/

#include "./root-simple-mcmc-master/TSimpleMCMC.H"
#include "p0dNuEAnalysisLikelihood.h"
#include "p0dNuEAnalysisLikelihood.cxx"

#include "TH1D.h"
#include "TVector.h"
#include "TVectorD.h"
#include "TPad.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TString.h"
#include "TStopwatch.h"

#include <string>
#include <sstream>
#include <iomanip>

const int gBurninCycles = 1; 
const int gBurninLength = 20000;

const int gChainCycles = 1;
const int gChainLength = 40000;//50000; 

void DrawHistos(p0dNuEAnalysisLikelihood& like)
{
	TH1D* Data_SS_ReconShowerVisibleEnergy_waterin_norm = (TH1D*) like.Data_SS_ReconShowerVisibleEnergy[0]->Clone("Data_SS_ReconShowerVisibleEnergy_waterin_norm");
//	Data_SS_ReconShowerVisibleEnergy_waterin_norm->Sumw2();
//	Data_SS_ReconShowerVisibleEnergy_waterin_norm->Scale(1.0/Data_SS_ReconShowerVisibleEnergy_waterin_norm->Integral());
	TH1D* Data_SS_ReconShowerVisibleEnergy_waterout_norm = (TH1D*) like.Data_SS_ReconShowerVisibleEnergy[1]->Clone("Data_SS_ReconShowerVisibleEnergy_waterout_norm");
//	Data_SS_ReconShowerVisibleEnergy_waterout_norm->Sumw2();
//	Data_SS_ReconShowerVisibleEnergy_waterout_norm->Scale(1.0/Data_SS_ReconShowerVisibleEnergy_waterout_norm->Integral());
		
	TH1D* Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm = (TH1D*) like.Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[0]->Clone("Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm");
//	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm->Sumw2();
//	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm->Scale(1.0/Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm->Integral());
	TH1D* Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm = (TH1D*) like.Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[1]->Clone("Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm");
//	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm->Sumw2();
//	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm->Scale(1.0/Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm->Integral());

	TH1D* Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm = (TH1D*) like.Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[0]->Clone("Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm");
//	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm->Sumw2();
//	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm->Scale(1.0/Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm->Integral());
	TH1D* Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm = (TH1D*) like.Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[1]->Clone("Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm");
//	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm->Sumw2();
//	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm->Scale(1.0/Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm->Integral());

	TH1D* MC_SS_ReconShowerVisibleEnergy_waterin_norm = (TH1D*) like.MC_SS_ReconShowerVisibleEnergy[0]->Clone("MC_SS_ReconShowerVisibleEnergy_waterin_norm");
//	MC_SS_ReconShowerVisibleEnergy_waterin_norm->Sumw2();
//	MC_SS_ReconShowerVisibleEnergy_waterin_norm->Scale(1.0/MC_SS_ReconShowerVisibleEnergy_waterin_norm->Integral());
	TH1D* MC_SS_ReconShowerVisibleEnergy_waterout_norm = (TH1D*) like.MC_SS_ReconShowerVisibleEnergy[1]->Clone("MC_SS_ReconShowerVisibleEnergy_waterout_norm");
//	MC_SS_ReconShowerVisibleEnergy_waterout_norm->Sumw2();
//	MC_SS_ReconShowerVisibleEnergy_waterout_norm->Scale(1.0/MC_SS_ReconShowerVisibleEnergy_waterout_norm->Integral());
		
	TH1D* MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm = (TH1D*) like.MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[0]->Clone("MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm");
//	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm->Sumw2();
//	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm->Scale(1.0/MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm->Integral());
	TH1D* MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm = (TH1D*) like.MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[1]->Clone("MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm");
//	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm->Sumw2();
//	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm->Scale(1.0/MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm->Integral());

	TH1D* MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm = (TH1D*) like.MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[0]->Clone("MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm");
//	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm->Sumw2();
//	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm->Scale(1.0/MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm->Integral());
	TH1D* MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm = (TH1D*) like.MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[1]->Clone("MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm");
//	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm->Sumw2();
//	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm->Scale(1.0/MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm->Integral());

	
//	MC_SS_ReconShowerVisibleEnergy_waterin_norm->Draw("hist");
	like.GetSignalSampleStack(0)->Draw();
	gPad->BuildLegend(0.6,0.6,0.9,0.9,"");
	Data_SS_ReconShowerVisibleEnergy_waterin_norm->Draw("same ep");
  	gPad->Print("nominal-MC-Data-ReconShowerVisibleEnergy-waterin-withoutsys.png");
//	MC_SS_ReconShowerVisibleEnergy_waterout_norm->Draw("hist");
	like.GetSignalSampleStack(1)->Draw();
	gPad->BuildLegend(0.6,0.6,0.9,0.9,"");
	Data_SS_ReconShowerVisibleEnergy_waterout_norm->Draw("same ep");
  	gPad->Print("nominal-MC-Data-ReconShowerVisibleEnergy-waterout-withoutsys.png");
	/*
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm->Draw("hist");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm->Draw("same ep");
    gPad->Print("nominal-MC-Data-NCResonantPi0Sideband_ReconShowerVisibleEnergy-waterin-withoutsys.png");
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm->Draw("hist");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm->Draw("same ep");
    gPad->Print("nominal-MC-Data-NCResonantPi0Sideband_ReconShowerVisibleEnergy-waterout-withoutsys.png");

	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm->Draw("hist");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm->Draw("same ep");
	gPad->Print("nominal-MC-Data-numuCCDISMultiPionSideband_ReconShowerVisibleEnergy-waterin-withoutsys.png");
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm->Draw("hist");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm->Draw("same ep");
	gPad->Print("nominal-MC-Data-numuCCDISMultiPionSideband_ReconShowerVisibleEnergy-waterout-withoutsys.png");
	*/

	TH1D* Data_SS_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.Data_SS_ReconShowerVisibleEnergy[0]);
	TH1D* Data_SS_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.Data_SS_ReconShowerVisibleEnergy[1]);
	TH1D* MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[0]);
	TH1D* MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[1]);
	TH1D* MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[0]);
	TH1D* MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[1]);
	TH1D* Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[0]);
	TH1D* Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[1]);
	TH1D* Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[0]);
	TH1D* Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[1]);
	TH1D* MC_SS_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.MC_SS_ReconShowerVisibleEnergy[0]);
	TH1D* MC_SS_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.MC_SS_ReconShowerVisibleEnergy[1]);
	MC_SS_ReconShowerVisibleEnergy_waterin_norm2->Draw("hist");
	Data_SS_ReconShowerVisibleEnergy_waterin_norm2->Draw("same ep");
  	gPad->Print("nominal-MC-Data-ReconShowerVisibleEnergy-waterin-2-withoutsys.png");
	MC_SS_ReconShowerVisibleEnergy_waterout_norm2->Draw("hist");
	Data_SS_ReconShowerVisibleEnergy_waterout_norm2->Draw("same ep");
  	gPad->Print("nominal-MC-Data-ReconShowerVisibleEnergy-waterout-2-withoutsys.png");

	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm2->Draw("hist");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm2->Draw("same ep");
    gPad->Print("nominal-MC-Data-NCResonantPi0Sideband_ReconShowerVisibleEnergy-waterin-2-withoutsys.png");
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm2->Draw("hist");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm2->Draw("same ep");
    gPad->Print("nominal-MC-Data-NCResonantPi0Sideband_ReconShowerVisibleEnergy-waterout-2-withoutsys.png");

	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm2->Draw("hist");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm2->Draw("same ep");
	gPad->Print("nominal-MC-Data-numuCCDISMultiPionSideband_ReconShowerVisibleEnergy-waterin-2-withoutsys.png");
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm2->Draw("hist");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm2->Draw("same ep");
	gPad->Print("nominal-MC-Data-numuCCDISMultiPionSideband_ReconShowerVisibleEnergy-waterout-2-withoutsys.png");

}

void RunMCMC(std::vector<std::string>& mcWaterinFHC, std::vector<std::string>& mcSplineWaterinFHC, double mcPOTWaterin, std::vector<std::string>& mcWaterOutFHC, std::vector<std::string>& mcSplineWaterOutFHC, double mcPOTWaterout, std::vector<std::string>& dataWaterinFHC, double dataPOTWaterin, std::vector<std::string>& dataWaterOutFHC, double dataPOTWaterout, std::string outFile);
//void RunMCMC(std::string mcFile1, double mcPOTWater, std::string mcFile2, double mcPOTAir, std::string dataFile1, double dataPOTWater, std::string dataFile2, double dataPOTAir, std::string splinesFile1, std::string splinesFile2, std::string outFile);
TH1D* NormalizeHistogram(TH1D* hist);

int main(int argc, char **argv) {
//    if (argc != 23) {
//    std::cerr << "./RunMCMC -m NominalMCWater.root -p MCPOTWater -n NominalMCAir.root -q MCPOTAir -d DataWater.root -t DataPOTWater -e DataAir.root -u DataPOTAir -r SplinesWater.root -s SplinesAir.root -o Output.root" << std::endl;
//    exit(-1);
//  }
	std::string nominalMCSigWaterin;
	std::string nominalMCNCWaterin;
	std::string nominalMCNumuWaterin;
	std::string nominalsplineSigWaterin;
	std::string nominalsplineNCWaterin;
	std::string nominalsplineNumuWaterin;

	std::string nominalMCSigWaterout;
	std::string nominalMCNCWaterout;
	std::string nominalMCNumuWaterout;
	std::string nominalsplineSigWaterout;
	std::string nominalsplineNCWaterout;
	std::string nominalsplineNumuWaterout;

	std::string DataSigWaterin;
	std::string DataNCWaterin;
	std::string DataNumuWaterin;
	std::string DataSigWaterout;
	std::string DataNCWaterout;
	std::string DataNumuWaterout;

	double mcPOTWaterin;
	double mcPOTWaterout;
	double dataPOTWaterin;
	double dataPOTWaterout;

	std::string outputfile;

	char cc;
	while((cc = getopt(argc, argv, "a:b:c:d:e:f:g:h:i:j:k:l:m:n:o:p:q:r:s:t:u:v:w:x")) != -1)
	{
		switch(cc)
		{
			case 'a':
				nominalMCSigWaterin = optarg;
				break;
			case 'b':
				nominalsplineSigWaterin = optarg;
				break;
			case 'c':
				nominalMCNCWaterin = optarg;
				break;
			case 'd': 
				nominalsplineNCWaterin = optarg;
				break;
			case 'e':
				nominalMCNumuWaterin = optarg;
				break;
			case 'f': 
				nominalsplineNumuWaterin = optarg;
				break;
			case 'g':
				nominalMCSigWaterout = optarg;
				break;
			case 'h' :
				nominalsplineSigWaterout = optarg;
				break;
			case 'i':
				nominalMCNCWaterout = optarg;
				break;
			case 'j':
				nominalsplineNCWaterout = optarg;	
				break;
			case 'k':
				nominalMCNumuWaterout = optarg;
				break;
			case 'l':
				nominalsplineNumuWaterout = optarg;
				break;
			case 'm':
				DataSigWaterin = optarg;
				break;
			case 'n':
				DataNCWaterin = optarg;
				break;
			case 'o':
				DataNumuWaterin = optarg;
				break;
			case 'p':
				DataSigWaterout = optarg;
				break;
			case 'q':
				DataNCWaterout = optarg;
				break;
			case 'r':
				DataNumuWaterout = optarg;	
				break;
			case 's':
				mcPOTWaterin = atof(optarg);;
				break;
			case 't':
				mcPOTWaterout = atof(optarg);;
				break;
			case 'u':
				dataPOTWaterin = atof(optarg);;
				break;
			case 'v':
				dataPOTWaterout = atof(optarg);;			
				break;
			case 'w': 
				outputfile = optarg;
				break;
		  	case 'x'://help
				std::cout << "USAGE: refer to the code"<<std::endl;
			  	return 0;
			default:
			  return 1;
		}
			
	}
	std::vector<std::string> mcWaterinFHC{nominalMCSigWaterin, nominalMCNCWaterin, nominalMCNumuWaterin};
	std::vector<std::string> mcSplineWaterinFHC{nominalsplineSigWaterin, nominalsplineNCWaterin, nominalsplineNumuWaterin};
	std::vector<std::string> mcWaterOutFHC{nominalMCSigWaterout, nominalMCNCWaterout, nominalMCNumuWaterout};
	std::vector<std::string> mcSplineWaterOutFHC{nominalsplineSigWaterout, nominalsplineNCWaterout, nominalsplineNumuWaterout};
	std::vector<std::string> dataWaterinFHC{DataSigWaterin, DataNCWaterin, DataNumuWaterin};
	std::vector<std::string> dataWaterOutFHC{DataSigWaterout, DataNCWaterout, DataNumuWaterout};
//	std::cout<<DataSigWaterin<<" "<<DataNCWaterin<<" "<<DataNumuWaterin<<std::endl;
	std::cout<<dataWaterinFHC[0]<<" "<<dataWaterinFHC[1]<<" "<<dataWaterinFHC[2]<<std::endl;
	std::cout<<dataPOTWaterout<<std::endl;
	RunMCMC(mcWaterinFHC, mcSplineWaterinFHC, mcPOTWaterin, mcWaterOutFHC, mcSplineWaterOutFHC, mcPOTWaterout, dataWaterinFHC, dataPOTWaterin, dataWaterOutFHC, dataPOTWaterout, outputfile);
	
}

void RunMCMC(std::vector<std::string>& mcWaterinFHC, std::vector<std::string>& mcSplineWaterinFHC, double mcPOTWaterin, std::vector<std::string>& mcWaterOutFHC, std::vector<std::string>& mcSplineWaterOutFHC, double mcPOTWaterout, std::vector<std::string>& dataWaterinFHC, double dataPOTWaterin, std::vector<std::string>& dataWaterOutFHC, double dataPOTWaterout, std::string outFile)
//void RunMCMC(std::string mcFile1, double mcPOTWater, std::string mcFile2, double mcPOTAir, std::string dataFile1, double dataPOTWater, std::string dataFile2, double dataPOTAir, std::string splinesFile1, std::string splinesFile2, std::string outFile) 
{

  std::cout << "Likelihood MCMC Loaded" << std::endl;
  gRandom->SetSeed(0);
  TStopwatch clock;

  TFile *outputFile = new TFile(outFile.c_str(),"recreate");
  TTree *tree = new TTree("MCMC","Tree of accepted points");
  TTree *pi0Tree = new TTree("SigWtTree", "Tree of accepted pi0 events");

  TSimpleMCMC<p0dNuEAnalysisLikelihood> mcmc(tree);
  p0dNuEAnalysisLikelihood& like = mcmc.GetLogLikelihood();
  TProposeAdaptiveStep& proposal = mcmc.GetProposeStep();

	Binning tmpobj;
	int NBins = tmpobj.GetNBins();
  std::vector<double> NSignalOnWater(NBins, 0);
  std::vector<double> NSignalNotWater(NBins, 0);

	double nsigonwaterbin1 = NSignalOnWater[0];
	double nsigonwaterbin2 = NSignalOnWater[1];
	double nsigonwaterbin3 = NSignalOnWater[2];
	double nsigonwaterbin4 = NSignalOnWater[3];
	double nsigonwaterbin5 = NSignalOnWater[4];

	double nsignotwaterbin1 = NSignalNotWater[0];
	double nsignotwaterbin2 = NSignalNotWater[1];
	double nsignotwaterbin3 = NSignalNotWater[2];
	double nsignotwaterbin4 = NSignalNotWater[3];
	double nsignotwaterbin5 = NSignalNotWater[4];
	pi0Tree->Branch("nsigonwaterbin1", &nsigonwaterbin1);
	pi0Tree->Branch("nsigonwaterbin2", &nsigonwaterbin2);
	pi0Tree->Branch("nsigonwaterbin3", &nsigonwaterbin3);
	pi0Tree->Branch("nsigonwaterbin4", &nsigonwaterbin4);
	pi0Tree->Branch("nsigonwaterbin5", &nsigonwaterbin5);
	pi0Tree->Branch("nsignotwaterbin1", &nsignotwaterbin1);
	pi0Tree->Branch("nsignotwaterbin2", &nsignotwaterbin2);
	pi0Tree->Branch("nsignotwaterbin3", &nsignotwaterbin3);
	pi0Tree->Branch("nsignotwaterbin4", &nsignotwaterbin4);
	pi0Tree->Branch("nsignotwaterbin5", &nsignotwaterbin5);

  // Initialize the likelihood with data and MC values
	std::cout<<"Init the likelihood with data and MC"<<std::endl;
//  like.Init(2, mcFile1, mcPOTWater,  mcFile2, mcPOTAir, "", 1, "", 1, dataFile1, dataPOTWater, dataFile2, dataPOTAir, "",1, "",1, splinesFile1, splinesFile2, "", "");
	like.Init(2, mcWaterinFHC, mcSplineWaterinFHC, mcPOTWaterin, mcWaterOutFHC, mcSplineWaterOutFHC, mcPOTWaterout, dataWaterinFHC, dataPOTWaterin, dataWaterOutFHC, dataPOTWaterout);
		
//	like.FillNominalMCHistograms();

//  TObjString *mcWaterstr = new TObjString(mcFile1.c_str());
//  TObjString *mcAirstr = new TObjString(mcFile2.c_str());
//  TObjString *dataWaterstr = new TObjString(dataFile1.c_str());
//  TObjString *dataAirstr = new TObjString(dataFile2.c_str());
//  TObjString *splinesWaterstr = new TObjString(splinesFile1.c_str());
//  TObjString *splinesAirstr = new TObjString(splinesFile2.c_str());
//  mcWaterstr->Write("mcWaterFile");
//  mcAirstr->Write("mcAirFile");
//  dataWaterstr->Write("dataWaterFile");
//  dataAirstr->Write("dataAirFile");
//  splinesWaterstr->Write("splinesWaterFile");
//  splinesAirstr->Write("splinesAirFile");
  TVector *mcPOT = new TVector(2);;
  TVector *dataPOT = new TVector(2);;
  TVector *burnAcc = new TVector(2);;
  (*mcPOT)[0] = mcPOTWaterin;
  (*mcPOT)[1] = mcPOTWaterout;
  (*dataPOT)[0] = dataPOTWaterin;
  (*dataPOT)[1] = dataPOTWaterout;

  outputFile->cd();
  mcPOT->Write("mcPOT");
  dataPOT->Write("dataPOT");
  like.correlation->Write("correlation");
  like.covariance->Write("covariance");
  like.covarianceI->Write("covarianceI");

  Int_t nPar = like.fInitParams.size();
  TVectorD* NominalParams = new TVectorD(nPar);
  TVectorD* PriorParams = new TVectorD(nPar);
  TVectorD* SigmaParams = new TVectorD(nPar);
  TVectorD* LowerBound = new TVectorD(nPar);
  TVectorD* UpperBound = new TVectorD(nPar);
  TObjArray* ParamNames = new TObjArray(nPar);

  for(Int_t i = 0; i < nPar; i++){
    TObjString *str = new TObjString(like.fParamNames[i].c_str());
    ParamNames->Add(str);
    (*NominalParams)[i] = like.fInitParams[i];
    (*PriorParams)[i] = like.fPriorParams[i];
    (*SigmaParams)[i] = like.fSigmaParams[i];
    (*LowerBound)[i] = like.fLowerBound[i];
    (*UpperBound)[i] = like.fUpperBound[i];
  }

  ParamNames->Write("ParamNames", TObject::kSingleKey);
  NominalParams->Write("NominalParams");
  PriorParams->Write("PriorParams");
  SigmaParams->Write("SigmaParams");
  LowerBound->Write("LowerBound");
  UpperBound->Write("UpperBound");

  like.Data_SS_ReconShowerVisibleEnergy[0]->Write();
  like.Data_SS_ReconShowerVisibleEnergy[1]->Write();
  like.Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[0]->Write();
  like.Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[1]->Write();
  like.Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[0]->Write();
  like.Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[1]->Write();

  like.MC_SS_ReconShowerVisibleEnergy[0]->Write();
  like.MC_SS_ReconShowerVisibleEnergy[1]->Write();
  like.MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[0]->Write();
  like.MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[1]->Write();
  like.MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[0]->Write();
  like.MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[1]->Write();

	DrawHistos();

 // Set the number of dimensions for the proposal.
  proposal.SetDim(like.fPriorParams.size());

  Int_t dim = like.fPriorParams.size();
  Float_t scale = 0.07;

  // What should be the scale for the first proposal
  
  for(Int_t i = 0; i < dim; i++){
    proposal.SetGaussian(i, scale*like.fSigmaParams[i]);
  }
  
  std::vector<double> p;
  p.resize(like.fPriorParams.size());

  // Set the starting point.
  // Starting point should be prior + random number b/w -1 and 1 * sigma
  // Check if 1 sigma error are larger or smaller that lb or ub in which case get a new value
	std::cout<<"randomize p"<<std::endl;
  for (std::size_t i=0; i<p.size(); ++i) {
//    //Set the signal weight priors to their burned -in value
//    if (i==0) p[i] = 1.5;
//    else if (i==1) p[i] = 1.0;
//    else if (i==2) p[i] = 0.8;
//    else if (i==3) p[i] = 0.8;
//    else if (i==4) p[i] = 0.8;
//    else if (i==5) p[i] = 1.0;
//    else if (i==6) p[i] = 1.0;
//    else if (i==7) p[i] = 1.2;
//    else if (i==8) p[i] = 1.2;
//    else if (i==9) p[i] = 1.2;
//    else if (i==10) p[i] = 1.2;
//    else if (i==11) p[i] = 0.8;
//    else if (i==12) p[i] = 0.9;
//    else if (i==13) p[i] = 1.0;
//    else if (i==14) p[i] = 1.1;
//    else if (i==15) p[i] = 1.2;
//    else if (i==16) p[i] = 1.2;
//    else if (i==17) p[i] = 1.2;
//    else p[i] = like.fPriorParams[i];// + (gRandom->Uniform(-1,1)*like.fSigmaParams[i]);
//	
//    
//    while(p[i] < like.fLowerBound[i] || p[i] > like.fUpperBound[i]){
//      p[i] = like.fPriorParams[i] + (gRandom->Uniform(-1,1)*like.fSigmaParams[i]);      
//    }
//    
    p[i] = like.fInitParams[i];//like.fPriorParams[i] + (gRandom->Uniform(-1,1)*like.fSigmaParams[i]);
//	p[i] = like.fPriorParams[i] + (gRandom->Uniform(-1,1)*like.fSigmaParams[i]);
	std::cout<<like.fParamNames[i]<<" "<<like.fPriorParams[i]<<" "<<p[i]<<" "<<like.fLowerBound[i]<<" "<<like.fUpperBound[i]<<std::endl;
    while(p[i] < like.fLowerBound[i] || p[i] > like.fUpperBound[i]){
      p[i] = like.fPriorParams[i] + (gRandom->Uniform(-1,1)*like.fSigmaParams[i]);
     }
  }

	std::cout<<"Start mcmc"<<std::endl;
  mcmc.Start(p,true); 
  
  outputFile->cd();
  like.FillMCHistograms(p);//not sure to have it or not...
//  like.WriteSimulation(p,"initial");
  // First burnin of the chain (don't save the output).  This is looking for
  // the best fit point.
  int total_burnin = 0;
  for (int burnin = 0; burnin<gBurninCycles; ++burnin) {
    std::cout << " burnin # : " << burnin << std::endl;
    proposal.ResetProposal();
    
    std::stringstream burninName;
    burninName << "burnin" << burnin+1;
    int length = gBurninLength*(burnin+1)/gBurninCycles;
    std::cout << "Start new burnin phase ("<< length
	      << " steps)" << std::endl;
    for (int i=0; i<length; ++i){
      mcmc.Step(true); // Saving the burn-in steps too
      like.SaveNSignal(mcmc.GetAccepted(), NSignalOnWater, NSignalNotWater);

		////// need to make it tidy
		nsigonwaterbin1 = NSignalOnWater[0];
		nsigonwaterbin2 = NSignalOnWater[1];
		nsigonwaterbin3 = NSignalOnWater[2];
		nsigonwaterbin4 = NSignalOnWater[3];
		nsigonwaterbin5 = NSignalOnWater[4];

		nsignotwaterbin1 = NSignalNotWater[0];
		nsignotwaterbin2 = NSignalNotWater[1];
		nsignotwaterbin3 = NSignalNotWater[2];
		nsignotwaterbin4 = NSignalNotWater[3];
		nsignotwaterbin5 = NSignalNotWater[4];
		///////////
      pi0Tree->Fill();
      if(length > 100 && !(i%(length/100))){
      	std::cout << "On step: " << i+1 << "/" << length << " " << i*100./length << "%" << std::endl;
      }
      
      ++total_burnin;
    }
    outputFile->cd();
	//doing the fillhosto in WriteSim below
	like.FillMCHistograms(proposal.GetEstimatedCenter());
    //    like.WriteSimulation(proposal.GetEstimatedCenter(),
    //			 burninName.str().c_str());

	TH1D* Data_SS_ReconShowerVisibleEnergy_waterin_afterburn_norm = (TH1D*) like.Data_SS_ReconShowerVisibleEnergy[0]->Clone("Data_SS_ReconShowerVisibleEnergy_waterin_afterburn_norm");
	Data_SS_ReconShowerVisibleEnergy_waterin_afterburn_norm->Sumw2();
	Data_SS_ReconShowerVisibleEnergy_waterin_afterburn_norm->Scale(1.0/Data_SS_ReconShowerVisibleEnergy_waterin_afterburn_norm->Integral());
	TH1D* Data_SS_ReconShowerVisibleEnergy_waterout_afterburn_norm = (TH1D*) like.Data_SS_ReconShowerVisibleEnergy[1]->Clone("Data_SS_ReconShowerVisibleEnergy_waterout_afterburn_norm");
	Data_SS_ReconShowerVisibleEnergy_waterout_afterburn_norm->Sumw2();
	Data_SS_ReconShowerVisibleEnergy_waterout_afterburn_norm->Scale(1.0/Data_SS_ReconShowerVisibleEnergy_waterout_afterburn_norm->Integral());
		
	TH1D* Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_afterburn_norm = (TH1D*) like.Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[0]->Clone("Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_afterburn_norm");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Sumw2();
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Scale(1.0/Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Integral());
	TH1D* Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_afterburn_norm = (TH1D*) like.Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[1]->Clone("Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_afterburn_norm");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Sumw2();
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Scale(1.0/Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Integral());

	TH1D* Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_afterburn_norm = (TH1D*) like.Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[0]->Clone("Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_afterburn_norm");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Sumw2();
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Scale(1.0/Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Integral());
	TH1D* Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_afterburn_norm = (TH1D*) like.Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[1]->Clone("Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_afterburn_norm");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Sumw2();
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Scale(1.0/Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Integral());

	TH1D* MC_SS_ReconShowerVisibleEnergy_waterin_afterburn_norm = (TH1D*) like.MC_SS_ReconShowerVisibleEnergy[0]->Clone("MC_SS_ReconShowerVisibleEnergy_waterin_afterburn_norm");
	MC_SS_ReconShowerVisibleEnergy_waterin_afterburn_norm->Sumw2();
	MC_SS_ReconShowerVisibleEnergy_waterin_afterburn_norm->Scale(1.0/MC_SS_ReconShowerVisibleEnergy_waterin_afterburn_norm->Integral());
	TH1D* MC_SS_ReconShowerVisibleEnergy_waterout_afterburn_norm = (TH1D*) like.MC_SS_ReconShowerVisibleEnergy[1]->Clone("MC_SS_ReconShowerVisibleEnergy_waterout_afterburn_norm");
	MC_SS_ReconShowerVisibleEnergy_waterout_afterburn_norm->Sumw2();
	MC_SS_ReconShowerVisibleEnergy_waterout_afterburn_norm->Scale(1.0/MC_SS_ReconShowerVisibleEnergy_waterout_afterburn_norm->Integral());
		
	TH1D* MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_afterburn_norm = (TH1D*) like.MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[0]->Clone("MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_afterburn_norm");
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Sumw2();
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Scale(1.0/MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Integral());
	TH1D* MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_afterburn_norm = (TH1D*) like.MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[1]->Clone("MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_afterburn_norm");
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Sumw2();
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Scale(1.0/MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Integral());

	TH1D* MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_afterburn_norm = (TH1D*) like.MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[0]->Clone("MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_afterburn_norm");
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Sumw2();
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Scale(1.0/MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Integral());
	TH1D* MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_afterburn_norm = (TH1D*) like.MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[1]->Clone("MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_afterburn_norm");
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Sumw2();
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Scale(1.0/MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Integral());

	MC_SS_ReconShowerVisibleEnergy_waterin_afterburn_norm->Draw("hist");
	Data_SS_ReconShowerVisibleEnergy_waterin_afterburn_norm->Draw("same ep");
  	gPad->Print("AfterBurn-MC-Data-ReconShowerVisibleEnergy-waterin-withoutsys.png");
	MC_SS_ReconShowerVisibleEnergy_waterout_afterburn_norm->Draw("hist");
	Data_SS_ReconShowerVisibleEnergy_waterout_afterburn_norm->Draw("same ep");
  	gPad->Print("AfterBurn-MC-Data-ReconShowerVisibleEnergy-waterout-withoutsys.png");

	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Draw("hist");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Draw("same ep");
    gPad->Print("AfterBurn-MC-Data-NCResonantPi0Sideband_ReconShowerVisibleEnergy-waterin-withoutsys.png");
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Draw("hist");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Draw("same ep");
    gPad->Print("AfterBurn-MC-Data-NCResonantPi0Sideband_ReconShowerVisibleEnergy-waterout-withoutsys.png");

	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Draw("hist");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_afterburn_norm->Draw("same ep");
	gPad->Print("AfterBurn-MC-Data-numuCCDISMultiPionSideband_ReconShowerVisibleEnergy-waterin-withoutsys.png");
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Draw("hist");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_afterburn_norm->Draw("same ep");
	gPad->Print("AfterBurn-MC-Data-numuCCDISMultiPionSideband_ReconShowerVisibleEnergy-waterout-withoutsys.png");

	Data_SS_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.Data_SS_ReconShowerVisibleEnergy[0]);
	Data_SS_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.Data_SS_ReconShowerVisibleEnergy[1]);
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[0]);
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[1]);
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[0]);
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[1]);
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[0]);
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[1]);
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[0]);
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[1]);
	MC_SS_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.MC_SS_ReconShowerVisibleEnergy[0]);
	MC_SS_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.MC_SS_ReconShowerVisibleEnergy[1]);
	MC_SS_ReconShowerVisibleEnergy_waterin_norm2->Draw("hist");
	Data_SS_ReconShowerVisibleEnergy_waterin_norm2->Draw("same ep");
  	gPad->Print("AfterBurn-MC-Data-ReconShowerVisibleEnergy-waterin-2-withoutsys.png");
	MC_SS_ReconShowerVisibleEnergy_waterout_norm2->Draw("hist");
	Data_SS_ReconShowerVisibleEnergy_waterout_norm2->Draw("same ep");
  	gPad->Print("AfterBurn-MC-Data-ReconShowerVisibleEnergy-waterout-2-withoutsys.png");

	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm2->Draw("hist");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm2->Draw("same ep");
    gPad->Print("AfterBurn-MC-Data-NCResonantPi0Sideband_ReconShowerVisibleEnergy-waterin-2-withoutsys.png");
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm2->Draw("hist");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm2->Draw("same ep");
    gPad->Print("AfterBurn-MC-Data-NCResonantPi0Sideband_ReconShowerVisibleEnergy-waterout-2-withoutsys.png");

	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm2->Draw("hist");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm2->Draw("same ep");
	gPad->Print("AfterBurn-MC-Data-numuCCDISMultiPionSideband_ReconShowerVisibleEnergy-waterin-2-withoutsys.png");
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm2->Draw("hist");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm2->Draw("same ep");
	gPad->Print("AfterBurn-MC-Data-numuCCDISMultiPionSideband_ReconShowerVisibleEnergy-waterout-2-withoutsys.png");
  }

  std::cout << "total number of burnin steps : " << total_burnin << std::endl;
  for (int chain = 0; chain < gChainCycles; ++chain) {
    proposal.UpdateProposal();
    clock.Start();
    // Run the chain.
    std::cout << "Start chain " << chain << std::endl;
    int nAcc = 0;
    for (int i=0; i<gChainLength; ++i)
	{
		 bool accepted =  mcmc.Step();
		 if(accepted){
		   ++nAcc;
		 }
		 like.SaveNSignal(mcmc.GetAccepted(), NSignalOnWater, NSignalNotWater);
		////// need to make it tidy
		nsigonwaterbin1 = NSignalOnWater[0];
		nsigonwaterbin2 = NSignalOnWater[1];
		nsigonwaterbin3 = NSignalOnWater[2];
		nsigonwaterbin4 = NSignalOnWater[3];
		nsigonwaterbin5 = NSignalOnWater[4];

		nsignotwaterbin1 = NSignalNotWater[0];
		nsignotwaterbin2 = NSignalNotWater[1];
		nsignotwaterbin3 = NSignalNotWater[2];
		nsignotwaterbin4 = NSignalNotWater[3];
		nsignotwaterbin5 = NSignalNotWater[4];
		///////////
		 pi0Tree->Fill();

		 if(gChainLength > 100 && !(i%(gChainLength/100))){
		   std::cout << "On step: " << i+1 << "/" << gChainLength << " " << i*100./gChainLength << "%" << std::endl;
		 }
    }
    std::cout << nAcc <<  " steps were accepted out of " << gChainLength << std::endl;
    (*burnAcc)[0] = total_burnin;
    (*burnAcc)[1] = nAcc;
    outputFile->cd();
    burnAcc->Write("BurnNAccpted");
	std::string tmpname = "correlation-chain"+std::to_string(chain);
	like.correlation->Write(tmpname.c_str());//"correlation");
	tmpname = "covariance-chain"+std::to_string(chain);
	like.covariance->Write(tmpname.c_str());
	tmpname = "covarianceI-chain"+std::to_string(chain);
	like.covarianceI->Write(tmpname.c_str());
//	tmpname = "paravalue"+"-chain"+std::to_string(chain);
//	like.
	like.FillMCHistograms(proposal.GetEstimatedCenter());
    //    like.WriteSimulation(proposal.GetEstimatedCenter(),"midway");
	TH1D* Data_SS_ReconShowerVisibleEnergy_waterin_MCMC_norm = (TH1D*) like.Data_SS_ReconShowerVisibleEnergy[0]->Clone("Data_SS_ReconShowerVisibleEnergy_waterin_MCMC_norm");
	Data_SS_ReconShowerVisibleEnergy_waterin_MCMC_norm->Sumw2();
	Data_SS_ReconShowerVisibleEnergy_waterin_MCMC_norm->Scale(1.0/Data_SS_ReconShowerVisibleEnergy_waterin_MCMC_norm->Integral());
	TH1D* Data_SS_ReconShowerVisibleEnergy_waterout_MCMC_norm = (TH1D*) like.Data_SS_ReconShowerVisibleEnergy[1]->Clone("Data_SS_ReconShowerVisibleEnergy_waterout_MCMC_norm");
	Data_SS_ReconShowerVisibleEnergy_waterout_MCMC_norm->Sumw2();
	Data_SS_ReconShowerVisibleEnergy_waterout_MCMC_norm->Scale(1.0/Data_SS_ReconShowerVisibleEnergy_waterout_MCMC_norm->Integral());
		
	TH1D* Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_MCMC_norm = (TH1D*) like.Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[0]->Clone("Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_MCMC_norm");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Sumw2();
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Scale(1.0/Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Integral());
	TH1D* Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_MCMC_norm = (TH1D*) like.Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[1]->Clone("Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_MCMC_norm");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Sumw2();
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Scale(1.0/Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Integral());

	TH1D* Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_MCMC_norm = (TH1D*) like.Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[0]->Clone("Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_MCMC_norm");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Sumw2();
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Scale(1.0/Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Integral());
	TH1D* Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_MCMC_norm = (TH1D*) like.Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[1]->Clone("Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_MCMC_norm");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Sumw2();
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Scale(1.0/Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Integral());

	TH1D* MC_SS_ReconShowerVisibleEnergy_waterin_MCMC_norm = (TH1D*) like.MC_SS_ReconShowerVisibleEnergy[0]->Clone("MC_SS_ReconShowerVisibleEnergy_waterin_MCMC_norm");
	MC_SS_ReconShowerVisibleEnergy_waterin_MCMC_norm->Sumw2();
	MC_SS_ReconShowerVisibleEnergy_waterin_MCMC_norm->Scale(1.0/MC_SS_ReconShowerVisibleEnergy_waterin_MCMC_norm->Integral());
	TH1D* MC_SS_ReconShowerVisibleEnergy_waterout_MCMC_norm = (TH1D*) like.MC_SS_ReconShowerVisibleEnergy[1]->Clone("MC_SS_ReconShowerVisibleEnergy_waterout_MCMC_norm");
	MC_SS_ReconShowerVisibleEnergy_waterout_MCMC_norm->Sumw2();
	MC_SS_ReconShowerVisibleEnergy_waterout_MCMC_norm->Scale(1.0/MC_SS_ReconShowerVisibleEnergy_waterout_MCMC_norm->Integral());
		
	TH1D* MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_MCMC_norm = (TH1D*) like.MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[0]->Clone("MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_MCMC_norm");
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Sumw2();
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Scale(1.0/MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Integral());
	TH1D* MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_MCMC_norm = (TH1D*) like.MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[1]->Clone("MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_MCMC_norm");
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Sumw2();
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Scale(1.0/MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Integral());

	TH1D* MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_MCMC_norm = (TH1D*) like.MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[0]->Clone("MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_MCMC_norm");
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Sumw2();
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Scale(1.0/MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Integral());
	TH1D* MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_MCMC_norm = (TH1D*) like.MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[1]->Clone("MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_MCMC_norm");
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Sumw2();
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Scale(1.0/MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Integral());

	MC_SS_ReconShowerVisibleEnergy_waterin_MCMC_norm->Draw("hist");
	Data_SS_ReconShowerVisibleEnergy_waterin_MCMC_norm->Draw("same ep");
	std::string name = "Chain"+std::to_string(chain)+"-MC-Data-ReconShowerVisibleEnergy-waterin-withoutsys.png";
  	gPad->Print(name.c_str());
	MC_SS_ReconShowerVisibleEnergy_waterout_MCMC_norm->Draw("hist");
	Data_SS_ReconShowerVisibleEnergy_waterout_MCMC_norm->Draw("same ep");
	name = "Chain"+std::to_string(chain)+"-MC-Data-ReconShowerVisibleEnergy-waterout-withoutsys.png";
  	gPad->Print(name.c_str());

	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Draw("hist");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Draw("same ep");
	name = "Chain"+std::to_string(chain)+"-MC-Data-NCResonantPi0Sideband_ReconShowerVisibleEnergy-waterin-withoutsys.png";
  	gPad->Print(name.c_str());
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Draw("hist");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Draw("same ep");
	name = "Chain"+std::to_string(chain)+"-MC-Data-NCResonantPi0Sideband_ReconShowerVisibleEnergy-waterout-withoutsys.png";
  	gPad->Print(name.c_str());

	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Draw("hist");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_MCMC_norm->Draw("same ep");
	name = "Chain"+std::to_string(chain)+"-MC-Data-numuCCDISMultiPionSideband_ReconShowerVisibleEnergy-waterin-withoutsys.png";
  	gPad->Print(name.c_str());
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Draw("hist");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_MCMC_norm->Draw("same ep");
	name = "Chain"+std::to_string(chain)+"-MC-Data-numuCCDISMultiPionSideband_ReconShowerVisibleEnergy-waterout-withoutsys.png";
  	gPad->Print(name.c_str());


	Data_SS_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.Data_SS_ReconShowerVisibleEnergy[0]);
	Data_SS_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.Data_SS_ReconShowerVisibleEnergy[1]);
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[0]);
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy[1]);
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[0]);
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[1]);
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[0]);
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy[1]);
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[0]);
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy[1]);
	MC_SS_ReconShowerVisibleEnergy_waterin_norm2 = NormalizeHistogram(like.MC_SS_ReconShowerVisibleEnergy[0]);
	MC_SS_ReconShowerVisibleEnergy_waterout_norm2 = NormalizeHistogram(like.MC_SS_ReconShowerVisibleEnergy[1]);
	MC_SS_ReconShowerVisibleEnergy_waterin_norm2->Draw("hist");
	Data_SS_ReconShowerVisibleEnergy_waterin_norm2->Draw("same ep");
	name = "Chain"+std::to_string(chain)+"-MC-Data-SS_ReconShowerVisibleEnergy-waterin-2-withoutsys.png";
  	gPad->Print(name.c_str());
	MC_SS_ReconShowerVisibleEnergy_waterout_norm2->Draw("hist");
	Data_SS_ReconShowerVisibleEnergy_waterout_norm2->Draw("same ep");
	name = "Chain"+std::to_string(chain)+"-MC-Data-SS_ReconShowerVisibleEnergy-waterout-2-withoutsys.png";
  	gPad->Print(name.c_str());

	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm2->Draw("hist");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterin_norm2->Draw("same ep");
	name = "Chain"+std::to_string(chain)+"-MC-Data-NCResonantPi0Sideband_ReconShowerVisibleEnergy-waterin-2-withoutsys.png";
  	gPad->Print(name.c_str());
	MC_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm2->Draw("hist");
	Data_NCResonantPi0Sideband_ReconShowerVisibleEnergy_waterout_norm2->Draw("same ep");
	name = "Chain"+std::to_string(chain)+"-MC-Data-NCResonantPi0Sideband_ReconShowerVisibleEnergy-waterout-2-withoutsys.png";
  	gPad->Print(name.c_str());

	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm2->Draw("hist");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterin_norm2->Draw("same ep");
	name = "Chain"+std::to_string(chain)+"-MC-Data-numuCCDISMultiPionSideband_ReconShowerVisibleEnergy-waterin-2-withoutsys.png";
  	gPad->Print(name.c_str());
	MC_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm2->Draw("hist");
	Data_numuCCDISMultiPionSideband_ReconShowerVisibleEnergy_waterout_norm2->Draw("same ep");
	name = "Chain"+std::to_string(chain)+"-MC-Data-numuCCDISMultiPionSideband_ReconShowerVisibleEnergy-waterout-2-withoutsys.png";
  	gPad->Print(name.c_str());
  }

  outputFile->cd();
  if(pi0Tree) pi0Tree->Write();
  if (tree) tree->Write();
  clock.Stop();
  std::cout << " MCMC took " << clock.RealTime() << " seconds to complete.(" << clock.RealTime() / gChainLength << "s / step)." << std::endl;
  std::cout << "I finished writing to the " << outFile.c_str()  << std::endl;
  if (outputFile) delete outputFile;
  
 return ;
}


TH1D* NormalizeHistogram(TH1D* hist){
  
  TH1D* norm_hist = (TH1D*)hist->Clone();
  
  Double_t min_width = 999.0;
  Int_t nbins = hist->GetNbinsX(); 
  
  for (Int_t i=0;i<nbins;i++){
    Double_t binwidth = hist->GetBinWidth(i+1);
    if(binwidth < min_width) min_width = binwidth;
  }
  
  for (Int_t i=0;i<nbins;i++){
    Double_t binwidth = hist->GetBinWidth(i+1);
    Double_t bincontent = hist->GetBinContent(i+1);
    norm_hist->SetBinContent(i+1,bincontent*(min_width/binwidth));
  }  
  
  return norm_hist;
}
