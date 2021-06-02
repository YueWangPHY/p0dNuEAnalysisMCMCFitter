#ifndef DATATYPES_H
#define DATATYPES_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <stdexcept>
#include <memory>
#include <utility>

#include <TH1D.h>
#include "TFile.h"
//#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <TChain.h>
#include <TMath.h>

#include "Utils/p0dNuEAnalysisFitterUtils.h"

//just to put mention that because in the micro tree, this is no var called numode at this momemnt and we are just runing FHC result, so set +numode or numode to be 1 directly here by far.

class Binning
{
public:
	Binning(){
		//default binning
		DefineBinning();
	}
	virtual ~Binning(){
//		delete _binsdis;//needed?
	}

	virtual void DefineBinning(){
		_NBins = 5;
		_binsdis.resize(_NBins+1);// = new double(_NBins+1);
		_binsdis[0] = 0;
		_binsdis[1] = 600;
		_binsdis[2] = 1500;
		_binsdis[3] = 2300;
		_binsdis[4] = 3400;
		_binsdis[5] = 30000;
	
		//ncbkcs
		_NNCBKCSBins = 7;
		_ncbkcsbinsdis.resize(_NNCBKCSBins+1);
		for(int i=0; i<_NNCBKCSBins+1; i++)
			_ncbkcsbinsdis[i] = 60.0+20.0*i;

		//to add numucc =bkcs binning
		//int _NNUMUCCBKCSBins; 
		//std::vector<double> _numuccbkcsbinsdis;
		_NNUMUCCBKCSBins = 7;//8;
		_numuccbkcsbinsdis.resize(_NNUMUCCBKCSBins+1);
		_numuccbkcsbinsdis = {0, 0.2, 0.3, 0.4, 0.5, 0.6, 0.785, 1.57};//1.2, 1.5};
	}

	virtual void DefineBinning(const int nbins, const std::vector<double>& bindis){
		_NBins = nbins;
		for(int i=0; i<_NBins+1; i++)
			_binsdis[i]=bindis[i];	
	}
		
	virtual int GetNBins() const {return _NBins;}
	
	virtual int GetBinIndex(double val) const{
		if(val<_binsdis[0])	return 0; //underflow
		if(val>=_binsdis[_NBins]) return _NBins+1; //overflow
		for(int i=0; i<_NBins; i++){
			if(val>=_binsdis[i]&&val<_binsdis[i+1])
				return i+1;
		}
		return -2;//should not happen
	}

	virtual int GetNCBKCSBinIndex(double val) const{
		if(val<_ncbkcsbinsdis[0])	return 0; //underflow
		if(val>=_ncbkcsbinsdis[_NNCBKCSBins]) return _NNCBKCSBins+1; //overflow
		for(int i=0; i<_NNCBKCSBins; i++){
			if(val>=_ncbkcsbinsdis[i]&&val<_ncbkcsbinsdis[i+1])
				return i+1;
		}
		return -2;//should not happen
	}

	virtual int GetNumuCCBKCSBinIndex(double val) const{
		if(val<_numuccbkcsbinsdis[0])	return 0; //underflow
		if(val>=_numuccbkcsbinsdis[_NNUMUCCBKCSBins]) return _NNUMUCCBKCSBins+1; //overflow
		for(int i=0; i<_NNUMUCCBKCSBins; i++){
			if(val>=_numuccbkcsbinsdis[i]&&val<_numuccbkcsbinsdis[i+1])
				return i+1;
		}
		return -2;//should not happen
	}

	virtual TH1D* GetTemplateHistogram()
	{
		const int N = _NBins+1;
		double dis[N];
		for(int i=0; i<_binsdis.size(); i++)
			dis[i] = _binsdis[i];
		TH1D* templatehist = new TH1D("templatehist", "", _NBins, dis);
		return templatehist;
	}

	virtual TH1D* GetNCBKCSTemplateHistogram()
	{
		const int N = _NNCBKCSBins+1;
		double dis[N];
		for(int i=0; i<_ncbkcsbinsdis.size(); i++)
			dis[i] = _ncbkcsbinsdis[i];
		TH1D* templatehist = new TH1D("ncbkcstemplatehist", "", _NNCBKCSBins, dis);
		return templatehist;
	}

	virtual TH1D* GetNumuCCBKCSTemplateHistogram()
	{
		const int N = _NNUMUCCBKCSBins+1;
		double dis[N];
		for(int i=0; i<_numuccbkcsbinsdis.size(); i++)
			dis[i] = _numuccbkcsbinsdis[i];
		TH1D* templatehist = new TH1D("numuccbkcstemplatehist", "", _NNUMUCCBKCSBins, dis);
		return templatehist;
	}

private:
	//singal 
	int _NBins;//not definted as const intentionally 
	std::vector<double> _binsdis;
//	double* _binsdis;//[NBins+1];
	
	int _NNCBKCSBins; 
	std::vector<double> _ncbkcsbinsdis;
	
	int _NNUMUCCBKCSBins; 
	std::vector<double> _numuccbkcsbinsdis;

};

class DataSets: public Binning
{
public:
	DataSets(std::string inputfilesig, std::string inputfilecs1="", std::string inputfilecs2=""){//, int sampletype=0){
		std::cout<<"Int DataSet construction and reading "<<std::endl;
		_inputsigfilename = inputfilesig;
		_inputncbkcsfilename = inputfilecs1;
		_inputnumuccbkcsfilename = inputfilecs2;
		if(_inputsigfilename.find(".list")==std::string::npos&&_inputsigfilename.find(".root")==std::string::npos)
		{
			std::cout<<_inputsigfilename<<std::endl;
			std::cerr<<"DataSet: the input format is invalid"<<std::endl;
			exit(1);
		}

		std::string file1;// = _inputfilename;
		if(_inputsigfilename.find(".list")!=std::string::npos)
		{
			std::ifstream in(_inputsigfilename.c_str());
			if(in.is_open())
				getline(in, file1);
		}
		else
			file1 = _inputsigfilename;
		if(file1.find(".root")==std::string::npos)
		{
			std::cout<<file1<<std::endl;
			std::cerr<<"the form of first Data file is NOT .root"<<std::endl;
			exit(1);
		}
		std::cout<<"file1 is "<<file1<<std::endl;
		TFile* tfile1 = new TFile(file1.c_str(), "READ");
		std::cout<<"read file"<<std::endl;
		TTree* defaulttree = (TTree*) tfile1->Get("default");
		std::cout<<"set default tree"<<std::endl;
		int isWaterConfig;
		int numode = 1;
		defaulttree->SetBranchAddress("isWaterConfig", &isWaterConfig);
//		defaulttree->SetBranchAddress("numode", &numode);
		defaulttree->GetEntry(0);
		_isWaterConfig = isWaterConfig;
		_numode = numode;
//		_sampletype = sampletype;
//		delete tfile1;
//		delete defaulttree;
	}

	virtual ~DataSets(){}	

//	void InitHistograms();
	void FillHistograms();

	void InitSigHistograms();
	void InitNumuCCBKCSHistograms();
	void InitNCBKCSHistograms();
	void FillSignalHistograms();
	void FillNumuCCBKCSHistograms();
	void FillNCBKCSHistograms();

//	virtual double GetPOT();//need to add in .cxx
	TH1D* GetSignalEnrichedHistogram() const {return SS_ReconShowerVisibleEnergy;}
	TH1D* GetNCResonantPi0SidebandHistogram() const {return NCResonantPi0Sideband_ReconShowerVisibleEnergy;}
	TH1D* GetnumuCCDISMultiPionSidebandHistogram() const {return numuCCDISMultiPionSideband_ReconShowerVisibleEnergy;}

	int GetWaterConfig() const {return _isWaterConfig;}
	int GetBeamMode() const {return _numode;}

private:
	std::string _inputsigfilename;
	std::string _inputnumuccbkcsfilename;
	std::string _inputncbkcsfilename;
	int _isWaterConfig; 
	int _numode;
//	int _sampletype; //signal enriched sample, NCResonantPi0Sideband, numuCCDISMultiPionSideband samples are going to be put in one input file and select with different cut. thus, here, samplettype is p0donly sample and external sample which are samples that can't be put in the same inputfiles with signal samples. =0 signal sample, =1 external sample (not external sample so far) 
	TH1D* SS_ReconShowerVisibleEnergy;//private member isW and numode will determine the config
	TH1D* NCResonantPi0Sideband_ReconShowerVisibleEnergy;
	TH1D* numuCCDISMultiPionSideband_ReconShowerVisibleEnergy;
};

class TruthEvent
{
public:
	TruthEvent(){
		//init all variables
		numode = 1;
		isSignal = -1;
		isOnWater = -1;
//		isinFV = -1;
//		InteractionTarget = -1;
		reactionCode=0;
		NeutrinoPDG=0;
		TrueVPositionZ=-9999.0;
		TrueNeutrinoEnergy = -1;
		totTrueParKin = -1;

		RunID = -1;
		EventID = -1;

		spline_MaCCQE = new TGraph();
		spline_MaRES = new TGraph();
		spline_CA5 = new TGraph();
		spline_ISO_BKG               = new TGraph();  
		spline_FSI_PI_ABS            = new TGraph();    
		spline_FSI_CEX_LO            = new TGraph();       
		spline_FSI_INEL_LO           = new TGraph();       
		spline_FSI_CEX_HI            = new TGraph();         
		spline_FSI_INEL_HI           = new TGraph();       
		spline_FSI_PI_PROD           = new TGraph();
		spline_NIWG_DIS_BY           = new TGraph();      
		spline_NIWG_MultiPi_BY       = new TGraph();    
		spline_NIWG_MultiPi_Xsec_AGKY= new TGraph();   
		spline_NIWG2012a_nc1piE0     = new TGraph(); 
		spline_NIWG2012a_nccohE0     = new TGraph();
		spline_NIWG2012a_ncotherE0   = new TGraph(); 
		spline_NIWG2012a_nc1pi0E0    = new TGraph();   
	}

	~TruthEvent()
	{
//		if(spline_MaCCQE)                       delete spline_MaCCQE;
//		if(spline_MaRES)                        delete spline_MaRES;
//		if(spline_CA5) 	                        delete spline_CA5;
//		if(spline_ISO_BKG)                      delete  spline_ISO_BKG;
//		if(spline_FSI_PI_ABS)                   delete  spline_FSI_PI_ABS;
//		if(spline_FSI_CEX_LO)                   delete  spline_FSI_CEX_LO;
//		if(spline_FSI_INEL_LO)                  delete  spline_FSI_INEL_LO;
//		if(spline_FSI_CEX_HI)                   delete  spline_FSI_CEX_HI;
//		if(spline_FSI_INEL_HI)                  delete  spline_FSI_INEL_HI;
//		if(spline_FSI_PI_PROD)                  delete spline_FSI_PI_PROD;
//		if(spline_NIWG_DIS_BY)                  delete  spline_NIWG_DIS_BY;
//		if(spline_NIWG_MultiPi_BY)              delete  spline_NIWG_MultiPi_BY;
//		if(spline_NIWG_MultiPi_Xsec_AGKY)       delete  spline_NIWG_MultiPi_Xsec_AGKY;
//		if(spline_NIWG2012a_nc1piE0)            delete  spline_NIWG2012a_nc1piE0;
//		if(spline_NIWG2012a_nccohE0)            delete  spline_NIWG2012a_nccohE0;
//		if(spline_NIWG2012a_ncotherE0)          delete  spline_NIWG2012a_ncotherE0;
//		if(spline_NIWG2012a_nc1pi0E0)           delete  spline_NIWG2012a_nc1pi0E0;

	}

	int numode ;//manully= 1;
	int isSignal;//this variable is not define in microtree but later in local code based on our desire
	int isOnWater; //1 yes, 0 no
	int isinFV;
//	int InteractionTarget;
	int reactionCode;
	int NeutrinoPDG;
	float TrueVPositionZ;
	float TrueNeutrinoEnergy;
	double totTrueParKin;
	//config
	int RunID; //from run1 to run10
	int EventID;

	//xsec para
	TGraph* spline_MaCCQE;
	TGraph* spline_MaRES;
	TGraph* spline_CA5;
	
	TGraph* spline_ISO_BKG;
	TGraph* spline_FSI_PI_ABS;
	TGraph* spline_FSI_CEX_LO;
	TGraph* spline_FSI_INEL_LO;
	TGraph* spline_FSI_CEX_HI;
	TGraph* spline_FSI_INEL_HI;
	TGraph* spline_FSI_PI_PROD;
	TGraph* spline_NIWG_DIS_BY;
	TGraph* spline_NIWG_MultiPi_BY;
	TGraph* spline_NIWG_MultiPi_Xsec_AGKY;
	TGraph* spline_NIWG2012a_nc1piE0;
	TGraph* spline_NIWG2012a_nccohE0;
	TGraph* spline_NIWG2012a_ncotherE0;
	TGraph* spline_NIWG2012a_nc1pi0E0;

	//... add more xxec parameters later if needed
	//... add more fsi parameters later if needed
	
};


class MCEvent
{
public:
	MCEvent(){
		//init all variables
		isSignal = -1;
		isOnWater = -1;
		isinFV = -1;
		InteractionTarget = -1;
		reactionCode=0;
		NPrimaryPi0s=0;
		NeutrinoPDG=0;
		MostProbableTrueParticlePDG = 0;
		TrueVPositionX=-9999.0;
		TrueVPositionY=-9999.0;
		TrueVPositionZ=-9999.0;
		TrueNeutrinoEnergy = -1;
		totTrueParKin = -1;

		NtruePi0 = -1;
		NtruePiCharge = -1;
		
		RunID = -1;
		EventID = -1;
		isWaterConfig = -1;//bool

		numode = 1;//-1;
		accum_level = -1;
		NValidParticles = -1;
		NValidTracks = -1;
		HSMTrackLayers = -1;
		HSMShowerLayers = -1;
		WTCharges = -1;
		ECalCharges = -1;
		EDeposit = -1;
		ReconShowerEnergy = -1;
		ShowerMedianWidth = -1;
		ShowerEDepFraction = -1;
		AllParTotEDepInEvent = -1;

		LongestTrackLayers_atTrackReconStage = -1;
		LongestTrackCostheta_atTrackReconStage = -9999.0;

		invariantmass = -9999.0;
		twoshowerEDepfrac = -9999.0;
		cospi0thetaz = -9999.0;
		maxEDepShower_ScaledMom = -9999.0; //should == ReconShowerEnergy
		maxEDepShower_EDep = -999.0; 
		maxEDepShower_Dir[0] = maxEDepShower_Dir[1] = maxEDepShower_Dir[2] = -999.0; 
		second_maxEDepShower_ScaledMom = -9999.0;
		second_maxEDepShower_EDep = -999.0; 
		second_maxEDepShower_Dir[0] = second_maxEDepShower_Dir[1] = second_maxEDepShower_Dir[2] = -999.0; 

		spline_MaCCQE = new TGraph();
		spline_MaRES = new TGraph();
		spline_CA5 = new TGraph();
		spline_ISO_BKG               = new TGraph();  
		spline_FSI_PI_ABS            = new TGraph();    
		spline_FSI_CEX_LO            = new TGraph();       
		spline_FSI_INEL_LO           = new TGraph();       
		spline_FSI_CEX_HI            = new TGraph();         
		spline_FSI_INEL_HI           = new TGraph();       
		spline_FSI_PI_PROD           = new TGraph();
		spline_NIWG_DIS_BY           = new TGraph();      
		spline_NIWG_MultiPi_BY       = new TGraph();    
		spline_NIWG_MultiPi_Xsec_AGKY= new TGraph();   
		spline_NIWG2012a_nc1piE0     = new TGraph(); 
		spline_NIWG2012a_nccohE0     = new TGraph();
		spline_NIWG2012a_ncotherE0   = new TGraph(); 
		spline_NIWG2012a_nc1pi0E0    = new TGraph();   
	}

	~MCEvent()
	{
//		if(spline_MaCCQE)                       delete spline_MaCCQE;
//		if(spline_MaRES)                        delete spline_MaRES;
//		if(spline_CA5) 	                        delete spline_CA5;
//		if(spline_ISO_BKG)                      delete  spline_ISO_BKG;
//		if(spline_FSI_PI_ABS)                   delete  spline_FSI_PI_ABS;
//		if(spline_FSI_CEX_LO)                   delete  spline_FSI_CEX_LO;
//		if(spline_FSI_INEL_LO)                  delete  spline_FSI_INEL_LO;
//		if(spline_FSI_CEX_HI)                   delete  spline_FSI_CEX_HI;
//		if(spline_FSI_INEL_HI)                  delete  spline_FSI_INEL_HI;
//		if(spline_FSI_PI_PROD)                  delete spline_FSI_PI_PROD;
//		if(spline_NIWG_DIS_BY)                  delete  spline_NIWG_DIS_BY;
//		if(spline_NIWG_MultiPi_BY)              delete  spline_NIWG_MultiPi_BY;
//		if(spline_NIWG_MultiPi_Xsec_AGKY)       delete  spline_NIWG_MultiPi_Xsec_AGKY;
//		if(spline_NIWG2012a_nc1piE0)            delete  spline_NIWG2012a_nc1piE0;
//		if(spline_NIWG2012a_nccohE0)            delete  spline_NIWG2012a_nccohE0;
//		if(spline_NIWG2012a_ncotherE0)          delete  spline_NIWG2012a_ncotherE0;
//		if(spline_NIWG2012a_nc1pi0E0)           delete  spline_NIWG2012a_nc1pi0E0;

	}

	//true
	int isSignal;//this variable is not define in microtree but later in local code based on our desire
	int isOnWater; //1 yes, 0 no
	int isinFV;
	int InteractionTarget;
	int reactionCode;
	int NPrimaryPi0s;
	int NeutrinoPDG;
	int MostProbableTrueParticlePDG;//pdg of the true par which contributes most energy in the selected reco candidate shower
	float TrueVPositionX;
	float TrueVPositionY;
	float TrueVPositionZ;
	float TrueNeutrinoEnergy;

	//not directly from setbranchadress
	double totTrueParKin;
	int NtruePi0;
	int NtruePiCharge;
	//reco
	double invariantmass;
	double twoshowerEDepfrac;
	double cospi0thetaz;
	double maxEDepShower_ScaledMom; //should == ReconShowerEnergy
	float maxEDepShower_EDep; 
	float maxEDepShower_Dir[3]; 
	double second_maxEDepShower_ScaledMom; 
	float  second_maxEDepShower_EDep; 
	float  second_maxEDepShower_Dir[3]; 
	//end of not directly from setbranchaddress
	//
	//config
	int RunID; //from run1 to run10
	int EventID;
	int isWaterConfig;//1 water-in, 0 water-out

	//reco
	int numode;// 1 FHC, 0 RHC
	int accum_level;
//	int cut0, cut1, cut2, cut3, cut4, cut5, cut6, cut7, cut8, cut9, cut10, cut11; // add more later
	int NValidParticles;
	int NValidTracks;
//	int NValidShowers;
	int HSMTrackLayers;
	int HSMShowerLayers;
//	int HSMShowerContainID;
	int nMuonDecayClusters;
	double WTCharges;
	double ECalCharges;
	double EDeposit; //=p0dparticle->momentum in oa for showers
	double ReconShowerEnergy;
	double ShowerMedianWidth;
	float ShowerEDepFraction;
	double AllParTotEDepInEvent;

	//
	int LongestTrackLayers_atTrackReconStage;
	double LongestTrackCostheta_atTrackReconStage;
	
	//xsec para
	TGraph* spline_MaCCQE;
	TGraph* spline_MaRES;
	TGraph* spline_CA5;
	
	TGraph* spline_ISO_BKG;
	TGraph* spline_FSI_PI_ABS;
	TGraph* spline_FSI_CEX_LO;
	TGraph* spline_FSI_INEL_LO;
	TGraph* spline_FSI_CEX_HI;
	TGraph* spline_FSI_INEL_HI;
	TGraph* spline_FSI_PI_PROD;
	TGraph* spline_NIWG_DIS_BY;
	TGraph* spline_NIWG_MultiPi_BY;
	TGraph* spline_NIWG_MultiPi_Xsec_AGKY;
	TGraph* spline_NIWG2012a_nc1piE0;
	TGraph* spline_NIWG2012a_nccohE0;
	TGraph* spline_NIWG2012a_ncotherE0;
	TGraph* spline_NIWG2012a_nc1pi0E0;

	//... add more xxec parameters later if needed
	//... add more fsi parameters later if needed
	
//	bool isSignalEvent(int defid = 0)
//	{
//		if(defid==0)//by default
//			return isSignalwBDTdef();
//		return 0;
//	}
//
//	bool isSignalwBDTdef();

	void operator=(MCEvent &mcEvent);//const MCEvent &mcEvent); //when issues when filling arrays in mcEvent when using const
};

class MCTruthUnit: public Binning
{
public:
	MCTruthUnit(){
	}
	MCTruthUnit(std::string inputMCfile, std::string inputXsecFSIRWfile)
	{
		std::cout<<"In Construction of MCTruthUnit using "<<inputMCfile<<" and "<<inputXsecFSIRWfile<<std::endl;
		_inputMCfilename = inputMCfile;
        if(_inputMCfilename.find(".list")==std::string::npos&&_inputMCfilename.find(".root")==std::string::npos){
            std::cerr<<"the MC input format is invalid"<<std::endl;
			exit(0);
		}
		_inputXsecFSIRWfilename = inputXsecFSIRWfile;
		if(_inputXsecFSIRWfilename.find(".root")==std::string::npos){
			std::cerr<<"the form of input XsecRW file is invalid"<<std::endl;
			exit(0);
		}
		SettruthTree(); //technically. the truth tree shouldn't be affect by selections, so we can use the same file. but just to make it faster, use the preporocessed truth
		SetXsecFSITree();
		SettruthTreeBranchAddress();
		SetXsecFSITreeBranchAddress();
		_NMCEntries = _truthTree->GetEntries();
		_NEntries_xsectree = _xsecfsiparaTree->GetEntries();
		std::cout<<"_NMCETruthntries = "<<_NMCEntries<<std::endl;
		std::cout<<"_NEntries_xsectree = "<<_NEntries_xsectree<<std::endl;
		FillXsecFSITreeEventIDvsEntry();
	}

	virtual ~MCTruthUnit(){}

	int FindEventIndexInXsecFSITreeFromDefaultIndex(int eventid);
	void GetAllSamples();

	std::vector<TruthEvent> _sigonwatersample;
//	std::vector<TruthEvent> _signotwatersample;
//	std::vector<TruthEvent> _notsigonwatersample;
//	std::vector<TruthEvent> _notsignotwatersample;

protected:
	virtual void SettruthTree()
	{
		std::cout<<"MC SettruthTree"<<std::endl;
		if(_inputMCfilename==""){
			std::cerr<<"No input truth file!!!"<<std::endl;
			exit(0);
		}
		_truthTree = new TChain("truth");
		std::string fileName;
		if(_inputMCfilename.find(".list")!=std::string::npos)
		{
			std::ifstream in(_inputMCfilename.c_str());
			while(in>>fileName)
			{
			  if(in.fail()) break;
			  _truthTree->AddFile(fileName.c_str());
			}
		}
		else
			_truthTree->AddFile(_inputMCfilename.c_str());
	}
	virtual void SetXsecFSITree()
	{
		std::cout<<"In MCTruthUnit, Set MC SetXsecFSITree"<<std::endl;
		if(_inputXsecFSIRWfilename==""){
			std::cerr<<"In MCTruthUnit, No input Xsec/FSI spline file!!!"<<std::endl;
			exit(0);
		}
		TFile* fXsecRW = new TFile(_inputXsecFSIRWfilename.c_str(), "READ");
		if(!fXsecRW){	
			std::cerr<<"Cannot open XsecRW file"<<std::endl;
			exit(0);
		}
		_xsecfsiparaTree = (TTree*) fXsecRW->Get("eventsReWeightsTree");
		if(!_xsecfsiparaTree)
			std::cerr<<"Cannot find T2K eventsReWeightsTree"<<std::endl;
	}
	virtual void SetXsecFSITreeBranchAddress()
	{
		std::cout<<"MC SetXsecFSITreeBranchAddress"<<std::endl;
		spline_MaCCQE = new TGraph();
		spline_MaRES = new TGraph();
		spline_CA5 = new TGraph();
		spline_ISO_BKG               = new TGraph();  
		spline_FSI_PI_ABS            = new TGraph();    
		spline_FSI_CEX_LO            = new TGraph();       
		spline_FSI_INEL_LO           = new TGraph();       
		spline_FSI_CEX_HI            = new TGraph();         
		spline_FSI_INEL_HI           = new TGraph();       
		spline_FSI_PI_PROD           = new TGraph();
		spline_NIWG_DIS_BY           = new TGraph();      
		spline_NIWG_MultiPi_BY       = new TGraph();    
		spline_NIWG_MultiPi_Xsec_AGKY= new TGraph();   
		spline_NIWG2012a_nc1piE0     = new TGraph(); 
		spline_NIWG2012a_nccohE0     = new TGraph();
		spline_NIWG2012a_ncotherE0   = new TGraph(); 
		spline_NIWG2012a_nc1pi0E0    = new TGraph();   
		//      spline_fsiinelLow_pi = new TGraph();

		_xsecfsiparaTree->SetBranchAddress("MaCCQEGraph", &spline_MaCCQE);
		_xsecfsiparaTree->SetBranchAddress("MaRESGraph",  &spline_MaRES);
		_xsecfsiparaTree->SetBranchAddress("CA5Graph",    &spline_CA5);
		_xsecfsiparaTree->SetBranchAddress("ISO_BKGGraph", &spline_ISO_BKG); 
		_xsecfsiparaTree->SetBranchAddress("FSI_PI_ABSGraph", &spline_FSI_PI_ABS);
		_xsecfsiparaTree->SetBranchAddress("FSI_CEX_LOGraph", &spline_FSI_CEX_LO             );
		_xsecfsiparaTree->SetBranchAddress("FSI_INEL_LOGraph", &spline_FSI_INEL_LO            );
		_xsecfsiparaTree->SetBranchAddress("FSI_CEX_HIGraph", &spline_FSI_CEX_HI             );
		_xsecfsiparaTree->SetBranchAddress("FSI_INEL_HIGraph", &spline_FSI_INEL_HI            );
		_xsecfsiparaTree->SetBranchAddress("FSI_PI_PRODGraph", &spline_FSI_PI_PROD            );
		_xsecfsiparaTree->SetBranchAddress("NIWG_DIS_BYGraph", &spline_NIWG_DIS_BY            );
		_xsecfsiparaTree->SetBranchAddress("NIWG_MultiPi_BYGraph", &spline_NIWG_MultiPi_BY        );
		_xsecfsiparaTree->SetBranchAddress("NIWG_MultiPi_Xsec_AGKYGraph", &spline_NIWG_MultiPi_Xsec_AGKY );
		_xsecfsiparaTree->SetBranchAddress("NIWG2012a_nc1piE0Graph", &spline_NIWG2012a_nc1piE0      );
		_xsecfsiparaTree->SetBranchAddress("NIWG2012a_nccohE0Graph", &spline_NIWG2012a_nccohE0      );
		_xsecfsiparaTree->SetBranchAddress("NIWG2012a_ncotherE0Graph", &spline_NIWG2012a_ncotherE0    );
		_xsecfsiparaTree->SetBranchAddress("NIWG2012a_nc1pi0E0Graph", &spline_NIWG2012a_nc1pi0E0     );
	}
	virtual void FillXsecFSITreeEventIDvsEntry()
	{
		std::cout<<"In FillXsecFSITreeEventIDvsEntry"<<std::endl;
		int eventID = -1;
		int nentries = _xsecfsiparaTree->GetEntries();
		_xsecfsiparaTree->SetBranchAddress("EventID", &eventID);
		for(int ientry = 0; ientry<nentries; ientry++)
		{
			_xsecfsiparaTree->GetEntry(ientry);	
			_EventIDvsEntry.insert({eventID, ientry});
		}
	}
	virtual void SettruthTreeBranchAddress()
	{
		std::cout<<"In MCTruthUnit, SetdefaultTreeBranchAddress"<<std::endl;
		_truthTree->SetBranchAddress("isTrueOnWater", &isOnWater);
		_truthTree->SetBranchAddress("isSigbyBDT", &isSignal);//isSigwBDT);
//		_truthTree->SetBranchAddress("targetpdg", &InteractionTarget);
		_truthTree->SetBranchAddress("nu_truereac", &reactionCode);
		_truthTree->SetBranchAddress("nu_pdg", &NeutrinoPDG);//nu_pdg is filled in baseAnalysis, there are some trueNeutrinoPDG for (proabably in numuCC/NC bacs) are not filled. similar for below
		_truthTree->SetBranchAddress("nu_trueE", &TrueNeutrinoEnergy);
		_truthTree->SetBranchAddress("truevtx_posZ", &TrueVPositionZ);
		_truthTree->SetBranchAddress("totTrueParKin", &totTrueParKin);
		_truthTree->SetBranchAddress("run", &RunID);
		_truthTree->SetBranchAddress("EventID", &EventID);
	}

private: 
    std::string _inputMCfilename;
	std::string _inputXsecFSIRWfilename;

	TChain* _truthTree;
	TTree* _xsecfsiparaTree;

	std::unordered_map<int, int> _EventIDvsEntry;

	int _NMCEntries;
	int _NEntries_xsectree;

	int isSignal;//this variable is not define in microtree but later in local code based on our desire
	int isOnWater; //1 yes, 0 no
	int isinFV;
//	int InteractionTarget;
	int reactionCode;
	int NeutrinoPDG;
	float TrueVPositionZ;
	float TrueNeutrinoEnergy;
	double totTrueParKin;
	//config
	int RunID; //from run1 to run10
	int EventID;

	//xsec para
	TGraph* spline_MaCCQE;
	TGraph* spline_MaRES;
	TGraph* spline_CA5;
	
	TGraph* spline_ISO_BKG;
	TGraph* spline_FSI_PI_ABS;
	TGraph* spline_FSI_CEX_LO;
	TGraph* spline_FSI_INEL_LO;
	TGraph* spline_FSI_CEX_HI;
	TGraph* spline_FSI_INEL_HI;
	TGraph* spline_FSI_PI_PROD;
	TGraph* spline_NIWG_DIS_BY;
	TGraph* spline_NIWG_MultiPi_BY;
	TGraph* spline_NIWG_MultiPi_Xsec_AGKY;
	TGraph* spline_NIWG2012a_nc1piE0;
	TGraph* spline_NIWG2012a_nccohE0;
	TGraph* spline_NIWG2012a_ncotherE0;
	TGraph* spline_NIWG2012a_nc1pi0E0;


};

class MCSimUnit: public Binning
{
public:
	MCSimUnit(){
		_inputMCfilename = "";
		_inputXsecFSIRWfilename = "";
	}
	MCSimUnit(std::string inputMCfile, std::string inputXsecFSIRWfile, int type){
		std::cout<<"In Construction of MCSimUnit using "<<inputMCfile<<" and "<<inputXsecFSIRWfile<<std::endl;
		_type = type;
        _inputMCfilename = inputMCfile;
//        if(_inputMCfilename.find(".list")!=std::string::npos||_inputMCfilename.find(".root")!=std::string::npos){
        if(_inputMCfilename.find(".list")==std::string::npos&&_inputMCfilename.find(".root")==std::string::npos){
            std::cerr<<"the MC input format is invalid"<<std::endl;
			exit(0);
		}
		_inputXsecFSIRWfilename = inputXsecFSIRWfile;
		if(_inputXsecFSIRWfilename.find(".root")==std::string::npos){
			std::cerr<<"the form of input XsecRW file is invalid"<<std::endl;
			exit(0);
		}
		SetdefaultTree();
		SetXsecFSITree();
		SetdefaultTreeBranchAddress();
		SetXsecFSITreeBranchAddress();
		_NMCEntries = _defaultTree->GetEntries();
		_NEntries_xsectree = _xsecfsiparaTree->GetEntries();
		std::cout<<"_NMCEntries = "<<_NMCEntries<<std::endl;
		std::cout<<"_NEntries_xsectree = "<<_NEntries_xsectree<<std::endl;
		FillXsecFSITreeEventIDvsEntry();
	}
	virtual ~MCSimUnit(){};

//	virtual double GetPOT();//need to add in .cxx

	std::string GetInputMCfileName(){return _inputMCfilename;}
	std::string GetInputXsecFSISplinefileName(){return _inputXsecFSIRWfilename;}
	int GetNMCinputEntries(){return _NMCEntries;}
//	void GetMCEvent(MCEvent &mcEvent, int ientry, int cutsid=1);
	bool GetMCEvent(MCEvent &mcEvent, int ientry);//, int cutsid=1);//return false if doesn't pass needed cuts. may change it in HL to make sure every events in the micro-tree has passed certain cuts we need. 
//	virtual void GetMCEventwoSMWSCF(MCEvent &mcEvent, int ientry);
//	virtual void GetMCEventwallCuts(MCEvent &mcEvent, int ientry);
	typedef std::vector<MCEvent> MCEventsVect;
	void GetMCEventsVect(MCEventsVect& mcEvents, int startindex=0, int endindex=0, int cutsid=1);//[startindex, endindex), default setting is to read all events//fill mcEvents as the reference of argument so that size of this class is small

	void GetAllSamples();

	int FindEventIndexInXsecFSITreeFromDefaultIndex(int defaulttreeindex);

	//write them as public for now to test current reading idea. will need to move  them into private and write a interface later if this way is decided to be used
	std::vector<MCEvent> _sample;

protected:
	// ************ tmp *************** //
	double GettotTrueConParKin()//this method to get totkin doesn't look the same as what in binstudy. need to check whether they give the same result
	{
		double totkin = 0;
		std::unordered_set<int> primaryidused;
		std::unordered_map<int, int> paridvsidx;
		for(int i=0; i<iIncrementTruePars; i++)//100; i++)//(int)true_ParticleID.size(); i++)
			paridvsidx.insert({true_ParticleID[i], i});	
		for(int i=0; i<iIncrementTruePars; i++)//100; i++)//(int)true_ParticlePrimaryID.size(); i++)
		{
			if(primaryidused.find(true_ParticlePrimaryID[i])!=primaryidused.end())
				continue;
			primaryidused.insert(true_ParticlePrimaryID[i]);
			int idx = paridvsidx[true_ParticlePrimaryID[i]];
			totkin += GetKineticEnergy(true_ParticleMom[idx], true_ParticlePDG[idx]);
		}
		return totkin;
	}

	double GetKineticEnergy(double momentum, int pdg)
	{
		std::unordered_map<int, double> pdgvsmass{{11, 0.511}, {13, 105.65}, {22, 0}, {111, 134.976}, {211, 139.57}, {2212, 938.271}};
		if(pdgvsmass.find(std::abs(pdg))==pdgvsmass.end())
			return 0;
		pdg = std::abs(pdg); //added on 05/11/2021
		return TMath::Sqrt(TMath::Power(momentum,2)+TMath::Power(pdgvsmass[pdg],2))-pdgvsmass[pdg];
	}

	std::pair<int, int> GetNTruePions()
	{
		int ntruepi0 = 0;
		int ntruepicharge = 0;

		for(int it=0; it<iIncrementTruePars; it++)
		{
			if(true_ParticleID[it]!=true_ParticlePrimaryID[it])
				continue;//skip non-primary particles
			if(true_ParticlePDG[it]==111)
				ntruepi0++;
			else if(true_ParticlePDG[it]==211||true_ParticlePDG[it]==-211)
				ntruepicharge++;
		}
		return std::make_pair(ntruepi0, ntruepicharge);
	}
	// ************ end tmp *************** //

	bool isSignalEvent(int defid = 0)
	{
		if(defid==0)//by default
			return isSignalwBDTdef();
		return 0;
	}

	bool isSignalwBDTdef();
	virtual void SetdefaultTree()
	{
		std::cout<<"MC SetdefaultTree"<<std::endl;
		if(_inputMCfilename==""){
			std::cerr<<"No input MC file!!!"<<std::endl;
			exit(0);
		}
		_defaultTree = new TChain("default");
		std::string fileName;
		if(_inputMCfilename.find(".list")!=std::string::npos)
		{
			std::ifstream in(_inputMCfilename.c_str());
			while(in>>fileName)
			{
			  if(in.fail()) break;
			  _defaultTree->AddFile(fileName.c_str());
			}
		}
		else
			_defaultTree->AddFile(_inputMCfilename.c_str());
	}
	virtual void SetXsecFSITree()
	{
		std::cout<<"MC SetXsecFSITree"<<std::endl;
		if(_inputXsecFSIRWfilename==""){
			std::cerr<<"No input Xsec/FSI spline file!!!"<<std::endl;
			exit(0);
		}
		TFile* fXsecRW = new TFile(_inputXsecFSIRWfilename.c_str(), "READ");
		if(!fXsecRW){	
			std::cerr<<"Cannot open XsecRW file"<<std::endl;
			exit(0);
		}
		_xsecfsiparaTree = (TTree*) fXsecRW->Get("eventsReWeightsTree");
		if(!_xsecfsiparaTree)
			std::cerr<<"Cannot find T2K eventsReWeightsTree"<<std::endl;
	}
	virtual void SetXsecFSITreeBranchAddress()
	{
		std::cout<<"MC SetXsecFSITreeBranchAddress"<<std::endl;
		spline_MaCCQE = new TGraph();
		spline_MaRES = new TGraph();
		spline_CA5 = new TGraph();
		spline_ISO_BKG               = new TGraph();  
		spline_FSI_PI_ABS            = new TGraph();    
		spline_FSI_CEX_LO            = new TGraph();       
		spline_FSI_INEL_LO           = new TGraph();       
		spline_FSI_CEX_HI            = new TGraph();         
		spline_FSI_INEL_HI           = new TGraph();       
		spline_FSI_PI_PROD           = new TGraph();
		spline_NIWG_DIS_BY           = new TGraph();      
		spline_NIWG_MultiPi_BY       = new TGraph();    
		spline_NIWG_MultiPi_Xsec_AGKY= new TGraph();   
		spline_NIWG2012a_nc1piE0     = new TGraph(); 
		spline_NIWG2012a_nccohE0     = new TGraph();
		spline_NIWG2012a_ncotherE0   = new TGraph(); 
		spline_NIWG2012a_nc1pi0E0    = new TGraph();   
		//      spline_fsiinelLow_pi = new TGraph();

		_xsecfsiparaTree->SetBranchAddress("MaCCQEGraph", &spline_MaCCQE);
		_xsecfsiparaTree->SetBranchAddress("MaRESGraph",  &spline_MaRES);
		_xsecfsiparaTree->SetBranchAddress("CA5Graph",    &spline_CA5);
		_xsecfsiparaTree->SetBranchAddress("ISO_BKGGraph", &spline_ISO_BKG); 
		_xsecfsiparaTree->SetBranchAddress("FSI_PI_ABSGraph", &spline_FSI_PI_ABS);
		_xsecfsiparaTree->SetBranchAddress("FSI_CEX_LOGraph", &spline_FSI_CEX_LO             );
		_xsecfsiparaTree->SetBranchAddress("FSI_INEL_LOGraph", &spline_FSI_INEL_LO            );
		_xsecfsiparaTree->SetBranchAddress("FSI_CEX_HIGraph", &spline_FSI_CEX_HI             );
		_xsecfsiparaTree->SetBranchAddress("FSI_INEL_HIGraph", &spline_FSI_INEL_HI            );
		_xsecfsiparaTree->SetBranchAddress("FSI_PI_PRODGraph", &spline_FSI_PI_PROD            );
		_xsecfsiparaTree->SetBranchAddress("NIWG_DIS_BYGraph", &spline_NIWG_DIS_BY            );
		_xsecfsiparaTree->SetBranchAddress("NIWG_MultiPi_BYGraph", &spline_NIWG_MultiPi_BY        );
		_xsecfsiparaTree->SetBranchAddress("NIWG_MultiPi_Xsec_AGKYGraph", &spline_NIWG_MultiPi_Xsec_AGKY );
		_xsecfsiparaTree->SetBranchAddress("NIWG2012a_nc1piE0Graph", &spline_NIWG2012a_nc1piE0      );
		_xsecfsiparaTree->SetBranchAddress("NIWG2012a_nccohE0Graph", &spline_NIWG2012a_nccohE0      );
		_xsecfsiparaTree->SetBranchAddress("NIWG2012a_ncotherE0Graph", &spline_NIWG2012a_ncotherE0    );
		_xsecfsiparaTree->SetBranchAddress("NIWG2012a_nc1pi0E0Graph", &spline_NIWG2012a_nc1pi0E0     );
	}
	virtual void FillXsecFSITreeEventIDvsEntry()
	{
		std::cout<<"In FillXsecFSITreeEventIDvsEntry"<<std::endl;
		int eventID = -1;
		int nentries = _xsecfsiparaTree->GetEntries();
		_xsecfsiparaTree->SetBranchAddress("evt", &eventID);
		for(int ientry = 0; ientry<nentries; ientry++)
		{
			_xsecfsiparaTree->GetEntry(ientry);	
			_EventIDvsEntry.insert({eventID, ientry});
		}
	}
	virtual void SetdefaultTreeBranchAddress()
	{
		std::cout<<"MC SetdefaultTreeBranchAddress"<<std::endl;
		_defaultTree->SetBranchAddress("isTrueOnWater", &isOnWater);
		_defaultTree->SetBranchAddress("isSigwBDT", &isSignal);//isSigwBDT);
//		_defaultTree->SetBranchAddress("isinFV", &isinFV);
		_defaultTree->SetBranchAddress("targetpdg", &InteractionTarget);
		_defaultTree->SetBranchAddress("nu_truereac", &reactionCode);
//		_defaultTree->SetBranchAddress("reactionCode", &reactionCode);
		_defaultTree->SetBranchAddress("true_numPrimaryPi0", &NPrimaryPi0s);
		_defaultTree->SetBranchAddress("nu_pdg", &NeutrinoPDG);//nu_pdg is filled in baseAnalysis, there are some trueNeutrinoPDG for (proabably in numuCC/NC bacs) are not filled. similar for below
//		_defaultTree->SetBranchAddress("trueNeutrinoPDG", &NeutrinoPDG);
		_defaultTree->SetBranchAddress("nu_trueE", &TrueNeutrinoEnergy);
//		_defaultTree->SetBranchAddress("trueNeutrinoEnergy", &TrueNeutrinoEnergy);
		_defaultTree->SetBranchAddress("TrueHSMPDG", &MostProbableTrueParticlePDG);
		_defaultTree->SetBranchAddress("TrueVPositionX", &TrueVPositionX);
		_defaultTree->SetBranchAddress("TrueVPositionY", &TrueVPositionY);
		_defaultTree->SetBranchAddress("TrueVPositionZ", &TrueVPositionZ);
//		_defaultTree->SetBranchAddress("totTrueParKin", &totTrueParKin);
		_defaultTree->SetBranchAddress("run", &RunID);
		_defaultTree->SetBranchAddress("evt", &EventID);
//		_defaultTree->SetBranchAddress("numode", &numode);
		_defaultTree->SetBranchAddress("isWaterConfig", &isWaterConfig);
		_defaultTree->SetBranchAddress("accum_level", &accum_level);
		_defaultTree->SetBranchAddress("cut0", &cut0);
		_defaultTree->SetBranchAddress("cut1", &cut1);
		_defaultTree->SetBranchAddress("cut2", &cut2);
		_defaultTree->SetBranchAddress("cut3", &cut3);
		_defaultTree->SetBranchAddress("cut4", &cut4);
		_defaultTree->SetBranchAddress("cut5", &cut5);
		_defaultTree->SetBranchAddress("cut6", &cut6);
		_defaultTree->SetBranchAddress("cut7", &cut7);
		_defaultTree->SetBranchAddress("cut8", &cut8);
		_defaultTree->SetBranchAddress("cut9", &cut9);
		_defaultTree->SetBranchAddress("cut10", &cut10);
		_defaultTree->SetBranchAddress("cut11", &cut11);
		_defaultTree->SetBranchAddress("NValidParticles", &NValidParticles);
		_defaultTree->SetBranchAddress("NValidTracks", &NValidTracks);
		_defaultTree->SetBranchAddress("NValidShowers", &NValidShowers);
		_defaultTree->SetBranchAddress("HSMTrackLayers", &HSMTrackLayers);
		_defaultTree->SetBranchAddress("HSMShowerLayers", &HSMShowerLayers);
		_defaultTree->SetBranchAddress("HSMShowerContainID", &HSMShowerContainID);
		_defaultTree->SetBranchAddress("nMuonDecayClusters", &nMuonDecayClusters);
		_defaultTree->SetBranchAddress("HSMShowerChargesWT", &WTCharges);
		_defaultTree->SetBranchAddress("HSMShowerChargesEC", &ECalCharges);
		_defaultTree->SetBranchAddress("ParticleEDep", &EDeposit);
		_defaultTree->SetBranchAddress("ReconShowerEnergy", &ReconShowerEnergy);
		_defaultTree->SetBranchAddress("ShowerMedianWidth", &ShowerMedianWidth);
		_defaultTree->SetBranchAddress("ShowerEDepFraction", &ShowerEDepFraction);
		_defaultTree->SetBranchAddress("AllParTotEDepInEvent", &AllParTotEDepInEvent);
		_defaultTree->SetBranchAddress("pi0Utils_HSMShowerMom", &pi0Utils_HSMShowerMom);
		_defaultTree->SetBranchAddress("iIncrementPar", &iIncrementPar);
		_defaultTree->SetBranchAddress("particleDim", &particleDim);
		_defaultTree->SetBranchAddress("parMom", &parMom);
		_defaultTree->SetBranchAddress("parEDep", &parEDep);
		_defaultTree->SetBranchAddress("parTotCharge", &parTotCharge);
		_defaultTree->SetBranchAddress("parScaledMom", &parScaledMom);
		_defaultTree->SetBranchAddress("parDirection", &parDirection);
		_defaultTree->SetBranchAddress("parPosition", &parPosition);
		_defaultTree->SetBranchAddress("iIncrementTruePars", &iIncrementTruePars);
		_defaultTree->SetBranchAddress("true_ParticleMom", &true_ParticleMom);
		_defaultTree->SetBranchAddress("true_ParticlePDG", &true_ParticlePDG);
		_defaultTree->SetBranchAddress("true_ParticleID", &true_ParticleID);
		_defaultTree->SetBranchAddress("true_ParticlePrimaryID", &true_ParticlePrimaryID);
		_defaultTree->SetBranchAddress("true_ParticleDir", &true_ParticleDir);
		_defaultTree->SetBranchAddress("true_ParStartPosi", &true_ParStartPosi);

		if(_type==2)
		{
			_defaultTree->SetBranchAddress("LongestTrackLayers_atTrackReconStage", &LongestTrackLayers_atTrackReconStage);
			_defaultTree->SetBranchAddress("LongestTrackCostheta_atTrackReconStage", &LongestTrackCostheta_atTrackReconStage);
		}
	}

private:
    std::string _inputMCfilename;
	std::string _inputXsecFSIRWfilename;
	int _type;

//	TFile* _tinputMCfile;
//	TFile* _tinputXsecFSIRWfile;
	TChain* _defaultTree;
	TTree* _xsecfsiparaTree;
//	TTree* _xsecparaTree;
//	TTree* _fsiparaTree;

	std::unordered_map<int, int> _EventIDvsEntry;

	int _NMCEntries;
	int _NEntries_xsectree;
	int _NEntries_fsitree;

	int _NSignalSample; //number of selected signal events when passing all cuts but SMW and SCF
	int _NNCBKSample;
	int _NnumuCCSample;

	//true
	int isSignal;//this variable is not define in microtree but later in local code based on our desire
//	int isSigwBDT;
	int isOnWater; //1 yes, 0 no
	int isinFV;
	int InteractionTarget;
	int reactionCode;
	int NPrimaryPi0s;
	int NeutrinoPDG;
	int MostProbableTrueParticlePDG;//pdg of the true par which contributes most energy in the selected reco candidate shower //on 03/12/2021, at this moment, I am not sure whether it should be its pdg or its primary pdg
	float TrueVPositionX;
	float TrueVPositionY;
	float TrueVPositionZ;
	float TrueNeutrinoEnergy;
	double totTrueParKin; //total kinetic energy of all primary charged particles and primary photons
//	double trueQ2;
		
	//config
	int RunID; //from run1 to run10
	int EventID;
	int isWaterConfig;//1 water-in, 0 water-out

	//reco
//	int numode;// 1 FHC, 0 RHC
	int accum_level;
	int cut0, cut1, cut2, cut3, cut4, cut5, cut6, cut7, cut8, cut9, cut10, cut11; // add more later
	int NValidParticles;
	int NValidTracks;
	int NValidShowers;
	int HSMTrackLayers;
	int HSMShowerLayers;
	int HSMShowerContainID;
	int nMuonDecayClusters;
	double WTCharges;
	double ECalCharges;
	double EDeposit;
	double ReconShowerEnergy;
	double ShowerMedianWidth;
	float ShowerEDepFraction;
	double AllParTotEDepInEvent;

	//
	int LongestTrackLayers_atTrackReconStage;
	double LongestTrackCostheta_atTrackReconStage;

	//reco pars
	double pi0Utils_HSMShowerMom;
	int iIncrementPar;
    int particleDim[100];
//	int parLayers[100];
	float parMom[100];
	float parEDep[100];
    double parScaledMom[100];
//    float parScaledMom[100];
	float parTotCharge[100];
//	double parMW[100];
//	int parPID[100][20];
	float parPosition[100][4];
	float parDirection[100][3];
//	float parPIDWeight[100][20];

	//true pars
    int iIncrementTruePars;
    int true_ParticlePDG[100];
    int true_ParticleID[100];
    int true_ParticlePrimaryID[100];
    float true_ParticleMom[100];
    float true_ParticleDir[100][3];
    float true_ParStartPosi[100][4];
	
	//xsec para
    TGraph *spline_MaCCQE;//add other paras later
    TGraph* spline_MaRES; 
	TGraph* spline_CA5;
	TGraph* spline_ISO_BKG;
	TGraph* spline_FSI_PI_ABS;
	TGraph* spline_FSI_CEX_LO;
	TGraph* spline_FSI_INEL_LO;
	TGraph* spline_FSI_CEX_HI;
	TGraph* spline_FSI_INEL_HI;
	TGraph* spline_FSI_PI_PROD;
	TGraph* spline_NIWG_DIS_BY;
	TGraph* spline_NIWG_MultiPi_BY;
	TGraph* spline_NIWG_MultiPi_Xsec_AGKY;
	TGraph* spline_NIWG2012a_nc1piE0;
	TGraph* spline_NIWG2012a_nccohE0;
	TGraph* spline_NIWG2012a_ncotherE0;
	TGraph* spline_NIWG2012a_nc1pi0E0;
	//... add more xsec ans fsi parameters later if needed
};
class MCSimulation
{
public:
	MCSimulation(){
//		_inputMCfilename = "";
//		_inputXsecFSIRWfilename = "";
	}
	MCSimulation(std::string inputfilesig, std::string inputsplinesig, std::string inputfilenccs="", std::string inputsplinenccs="", std::string inputfilenumucs="", std::string inputfsplinenumucs="")//, std::string inputMCfile, std::string inputXsecFSIRWfile){
	{
		_inputsigMCfilename = inputfilesig;
		_inputsigXsecFSIRWfilename = inputsplinesig;
		_inputncbkcsMCfilename = inputfilenccs;
		_inputncbkcsXsecFSIRWfilename = inputsplinenccs;
		_inputnumuccbkcsMCfilename = inputfilenumucs;
		_inputnumuccbkcsXsecFSIRWfilename = inputfsplinenumucs;
		_signalSample = NULL;
		_ncbkSample = NULL;
		_numccbkSample= NULL;
	}

	void GetAllSamples()
	{
		if(_inputnumuccbkcsMCfilename!=""&&_inputnumuccbkcsXsecFSIRWfilename!="")
			GeNumuControlSample();
		GetSignalEnrichedSample();
		if(_inputncbkcsMCfilename!=""&&_inputncbkcsXsecFSIRWfilename!="")
			GetNCBKControlSample();
	}

	void GetSignalEnrichedSample()
	{
		_signalSample = new MCSimUnit(_inputsigMCfilename, _inputsigXsecFSIRWfilename, 0);
		_signalSample->GetAllSamples();
	}

	void GetNCBKControlSample()
	{
		_ncbkSample = new MCSimUnit(_inputncbkcsMCfilename, _inputncbkcsXsecFSIRWfilename, 1);
		_ncbkSample->GetAllSamples();
	}

	void GeNumuControlSample()
	{
		_numccbkSample = new MCSimUnit(_inputnumuccbkcsMCfilename, _inputnumuccbkcsXsecFSIRWfilename, 2);
		_numccbkSample->GetAllSamples();
	}

	MCSimUnit* _signalSample;
	MCSimUnit* _ncbkSample;
	MCSimUnit* _numccbkSample;	

private:
	std::string _inputsigMCfilename;
	std::string _inputsigXsecFSIRWfilename;
	std::string _inputnumuccbkcsMCfilename;
	std::string _inputnumuccbkcsXsecFSIRWfilename;
	std::string _inputncbkcsMCfilename;
	std::string _inputncbkcsXsecFSIRWfilename;
};



#endif
