
class MCSimUnit: public Binning
{
public:
	MCSimUnit(){
		_inputMCfilename = "";
		_inputXsecFSIRWfilename = "";
	}
	MCSimUnit(std::string inputMCfile, std::string inputXsecFSIRWfile, int type){

		_type = type;
        _inputMCfilename = inputMCfile;
//        if(_inputMCfilename.find(".list")!=std::string::npos||_inputMCfilename.find(".root")!=std::string::npos){
        if(_inputMCfilename.find(".list")==std::string::npos&&_inputMCfilename.find(".root")==std::string::npos){
            std::cerr<<"the input format is invalid"<<std::endl;
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
//	std::vector<MCEvent> _signalsample;
//	std::vector<MCEvent> _ncbksample;
//	std::vector<MCEvent> _numuccbksample;
	std::vector<MCEvent> _sample;

protected:
	// ************ tmp *************** //
	double GettotTrueConParKin()//this method to get totkin doesn't look the same as what in binstudy. need to check whether they give the same result
	{
		double totkin = 0;
		std::unordered_set<int> primaryidused;
		std::unordered_map<int, int> paridvsidx;
		for(int i=0; i<100; i++)//(int)true_ParticleID.size(); i++)
			paridvsidx.insert({true_ParticleID[i], i});	
		for(int i=0; i<100; i++)//(int)true_ParticlePrimaryID.size(); i++)
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
		if(pdgvsmass.find(pdg)==pdgvsmass.end())
			return 0;
		return TMath::Sqrt(TMath::Power(momentum,2)+TMath::Power(pdgvsmass[pdg],2))-pdgvsmass[pdg];
	}
	// ************ end tmp *************** //

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
		_defaultTree->SetBranchAddress("iIncrementPar", &iIncrementPar);
		_defaultTree->SetBranchAddress("particleDim", &particleDim);
		_defaultTree->SetBranchAddress("parMom", &parMom);
		_defaultTree->SetBranchAddress("parEDep", &parEDep);
		_defaultTree->SetBranchAddress("parTotCharge", &parTotCharge);
		_defaultTree->SetBranchAddress("parScaledMom", &parScaledMom);
		_defaultTree->SetBranchAddress("parDirection", &parDirection);
		_defaultTree->SetBranchAddress("parPosition", &parPosition);
//		_defaultTree->SetBranchAddress("parLayers", &parLayers);
//		_defaultTree->SetBranchAddress("parMW", &parMW);
//		_defaultTree->SetBranchAddress("parPID", &parPID);
//		_defaultTree->SetBranchAddress("parPIDWeight", &parPIDWeight);
		_defaultTree->SetBranchAddress("iIncrementTruePars", &iIncrementTruePars);
		_defaultTree->SetBranchAddress("true_ParticleMom", &true_ParticleMom);
		_defaultTree->SetBranchAddress("true_ParticlePDG", &true_ParticlePDG);
		_defaultTree->SetBranchAddress("true_ParticleID", &true_ParticleID);
		_defaultTree->SetBranchAddress("true_ParticlePrimaryID", &true_ParticlePrimaryID);
		_defaultTree->SetBranchAddress("true_ParticleDir", &true_ParticleDir);
		_defaultTree->SetBranchAddress("true_ParStartPosi", &true_ParStartPosi);
	}

	bool isSignalEvent(int defid = 0)
	{
		if(defid==0)//by default
			return isSignalwBDTdef();
		return 0;
	}

	bool isSignalwBDTdef();
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
	double TrueNeutrinoEnergy;
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

//    //not directly from setbranchadress
//    int maxEDepShowerIndex;
//    int secondmaxEDepShowerIndex;

	//reco pars
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
	//... add more xxec parameters later
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

