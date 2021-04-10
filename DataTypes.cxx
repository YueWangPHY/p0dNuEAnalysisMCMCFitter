#include <fstream>

#include "DataTypes.h"
#include "Utils/pi0RelatedQuanCal.h"
#include "Utils/BDTClassifier.h"
#include "Utils/electronproton_4features_v2_class.h"
#include "Utils/electronpiplus_4features_v2_class.h"

void DataSets::FillHistograms(){
	FillSignalHistograms();
	FillNCBKCSHistograms();
	FillNumuCCBKCSHistograms();
}

void DataSets::InitSigHistograms()
{
//	std::shared_ptr<TH1D> templatehist = std::make_shared<TH1D>(GetTemplateHistogram());
    TH1D* templatehist = GetTemplateHistogram();

	std::string histoname = "SS_ReconShowerVisibleEnergy";
	histoname += (_isWaterConfig ? "_waterin":"_waterout");
	histoname += (_numode ? "_FHC":"_RHC");
	SS_ReconShowerVisibleEnergy = (TH1D*) templatehist->Clone(histoname.c_str());
	delete templatehist;
}
void DataSets::FillSignalHistograms(){
	
	InitSigHistograms();

	std::cout<<"In DataSet FillSignalHistograms and reading "<<_inputsigfilename<<std::endl;
//	std::shared_ptr<TChain> _defaultTree = std::make_shared<TChain>(new TChain("default"));
	TChain* _defaultTree = new TChain("default");
	std::string fileName;
	if(_inputsigfilename.find(".list")!=std::string::npos)
	{
		std::ifstream in(_inputsigfilename.c_str());
		while(in>>fileName)
		{
		  if(in.fail()) break;
		  _defaultTree->AddFile(fileName.c_str());
		}
	}
	else if(_inputsigfilename.find(".root")!=std::string::npos)
		_defaultTree->AddFile(_inputsigfilename.c_str());
	else
	{
		std::cout<<"DataSet: Invalid format of _inputsignalfile"<<std::endl;
		exit(0);
	}

	int EventID;
	int isWaterConfig;//bool
//	int numode;
	int accum_level;
	int HSMTrackLayers;
	double ShowerMedianWidth;
	float ShowerEDepFraction;
	double ReconShowerEnergy;

	_defaultTree->SetBranchAddress("evt", &EventID);
	_defaultTree->SetBranchAddress("isWaterConfig", &isWaterConfig);
//	_defaultTree->SetBranchAddress("numode", &numode);
	_defaultTree->SetBranchAddress("accum_level", &accum_level);
	_defaultTree->SetBranchAddress("HSMTrackLayers", &HSMTrackLayers);
	_defaultTree->SetBranchAddress("ReconShowerEnergy", &ReconShowerEnergy);
	_defaultTree->SetBranchAddress("ShowerMedianWidth", &ShowerMedianWidth);
	_defaultTree->SetBranchAddress("ShowerEDepFraction", &ShowerEDepFraction);

	long int NEntries = _defaultTree->GetEntries();
	for(long int ievt=0; ievt<NEntries; ievt++)
	{
		if(ievt%1000==0)
			std::cout<<"In Data GetEntry "<<ievt<<std::endl;
		_defaultTree->GetEntry(ievt);
		if(accum_level>9&&HSMTrackLayers>13&&ShowerEDepFraction>0.9)
		{
			if((isWaterConfig==1&&ShowerMedianWidth<24)||(isWaterConfig==0&&ShowerMedianWidth<29))
				SS_ReconShowerVisibleEnergy->Fill(ReconShowerEnergy);
		}
	}

	delete _defaultTree;
}

void DataSets::InitNCBKCSHistograms()
{
//	std::shared_ptr<TH1D> templatehist = std::make_shared<TH1D>(GetTemplateHistogram());
    TH1D* templatehist = GetTemplateHistogram();

	std::string histoname = "NCResonantPi0Sideband_ReconShowerVisibleEnergy";
	histoname += (_isWaterConfig ? "_waterin":"_waterout");
	histoname += (_numode ? "_FHC":"_RHC");
	NCResonantPi0Sideband_ReconShowerVisibleEnergy = (TH1D*) templatehist->Clone(histoname.c_str());

	delete templatehist;
}
void DataSets::FillNCBKCSHistograms(){
	
	InitNCBKCSHistograms();

	std::cout<<"In DataSet FillNCBKCSHistograms and reading "<<_inputncbkcsfilename<<std::endl;
	if(_inputncbkcsfilename=="")
	{
		std::cout<<"NO NC Control Sample in Current Configuration"<<std::endl;
		return ;
	}
//	std::shared_ptr<TChain> _defaultTree = std::make_shared<TChain>(new TChain("default"));
	TChain* _defaultTree = new TChain("default");
	std::string fileName;
	if(_inputncbkcsfilename.find(".list")!=std::string::npos)
	{
		std::ifstream in(_inputncbkcsfilename.c_str());
		while(in>>fileName)
		{
		  if(in.fail()) break;
		  _defaultTree->AddFile(fileName.c_str());
		}
	}
	else if(_inputncbkcsfilename.find(".root")!=std::string::npos)
		_defaultTree->AddFile(_inputncbkcsfilename.c_str());
	else
	{
		std::cout<<"DataSet: Invalid format of _inputncbkcsfile"<<std::endl;
		exit(0);
	}

	int EventID;
	int isWaterConfig;//bool
//	int numode;
	int accum_level;
	int HSMTrackLayers;
	double ShowerMedianWidth;
	float ShowerEDepFraction;
	double ReconShowerEnergy;
	double AllParTotEDepInEvent;
//	int cut0, cut1, cut2, cut3, cut4, cut5, cut6, cut7, cut8, cut9, cut10, cut11; // add more later
	//reco pars
	int iIncrementPar;
    int particleDim[100];
	float parMom[100];
	float parEDep[100];
    double parScaledMom[100];
	float parDirection[100][3];

	_defaultTree->SetBranchAddress("evt", &EventID);
	_defaultTree->SetBranchAddress("isWaterConfig", &isWaterConfig);
//	_defaultTree->SetBranchAddress("numode", &numode);
	_defaultTree->SetBranchAddress("accum_level", &accum_level);
	_defaultTree->SetBranchAddress("HSMTrackLayers", &HSMTrackLayers);
	_defaultTree->SetBranchAddress("ReconShowerEnergy", &ReconShowerEnergy);
	_defaultTree->SetBranchAddress("ShowerMedianWidth", &ShowerMedianWidth);
	_defaultTree->SetBranchAddress("ShowerEDepFraction", &ShowerEDepFraction);
	_defaultTree->SetBranchAddress("AllParTotEDepInEvent", &AllParTotEDepInEvent);
//	_defaultTree->SetBranchAddress("cut0", &cut0);
	_defaultTree->SetBranchAddress("iIncrementPar", &iIncrementPar);
	_defaultTree->SetBranchAddress("particleDim", &particleDim);
	_defaultTree->SetBranchAddress("parMom", &parMom);
	_defaultTree->SetBranchAddress("parEDep", &parEDep);
	_defaultTree->SetBranchAddress("parScaledMom", &parScaledMom);
	_defaultTree->SetBranchAddress("parDirection", &parDirection);

	long int NEntries = _defaultTree->GetEntries();
	for(long int ievt=0; ievt<NEntries; ievt++)
	{
		_defaultTree->GetEntry(ievt);
		if(accum_level>6&&ShowerEDepFraction<0.9)//add cuts for selecting ncpi0 cs 
		{
			std::pair<int, int> maxtwo = pi0ShowerUtils::FindMaxTwoShower(particleDim, parScaledMom, parMom, parEDep, 0, iIncrementPar-1);
			int maxEDepShowerIndex = maxtwo.first;
			int secondmaxEDepShowerIndex = maxtwo.second;
			/*
			std::cout<<EventID<<" "<<maxEDepShowerIndex<<" "<<secondmaxEDepShowerIndex;//<<" "<<parEDep[maxEDepShowerIndex]<<" "<<parEDep[secondmaxEDepShowerIndex]<<std::endl;
			for(int i=0; i<iIncrementPar; i++)
			{
				if(parEDep[i]>-1)
					std::cout<<" "<<i<<"-"<<parEDep[i];
			}
			std::cout<<std::endl;
			*/
			if(maxEDepShowerIndex>=0&&secondmaxEDepShowerIndex>=0&&(parEDep[maxEDepShowerIndex]+parEDep[secondmaxEDepShowerIndex])/AllParTotEDepInEvent>0.85)
			{
				double Max_Dir[3] = { parDirection[ maxEDepShowerIndex][0],  parDirection[ maxEDepShowerIndex][1],  parDirection[ maxEDepShowerIndex][2]};
				double SecondMax_Dir[3] = { parDirection[ secondmaxEDepShowerIndex][0],  parDirection[ secondmaxEDepShowerIndex][1],  parDirection[ secondmaxEDepShowerIndex][2]};
				double invarinatmass = pi0ShowerUtils::CalInvariantMass( parScaledMom[ maxEDepShowerIndex], Max_Dir,  parScaledMom[ secondmaxEDepShowerIndex],SecondMax_Dir); // use nueutil mom
//					double cospi0thetaz = (Max_pi0Mom*Max_Dir[2]+SecondMax_pi0Mom*SecondMax_Dir[2])/TMath::Sqrt(TMath::Power(Max_pi0Mom*Max_Dir[0]+SecondMax_pi0Mom*SecondMax_Dir[0], 2)+TMath::Power(Max_pi0Mom*Max_Dir[1]+SecondMax_pi0Mom*SecondMax_Dir[1], 2)+TMath::Power(Max_pi0Mom*Max_Dir[2]+SecondMax_pi0Mom*SecondMax_Dir[2], 2));
				double cospi0thetaz = (parScaledMom[maxEDepShowerIndex]*Max_Dir[2]+ parScaledMom[secondmaxEDepShowerIndex]*SecondMax_Dir[2])/TMath::Sqrt(TMath::Power( parScaledMom[ maxEDepShowerIndex]*Max_Dir[0]+ parScaledMom[ secondmaxEDepShowerIndex]*SecondMax_Dir[0], 2)+TMath::Power( parScaledMom[ maxEDepShowerIndex]*Max_Dir[1]+ parScaledMom[ secondmaxEDepShowerIndex]*SecondMax_Dir[1], 2)+TMath::Power( parScaledMom[ maxEDepShowerIndex]*Max_Dir[2]+ parScaledMom[ secondmaxEDepShowerIndex]*SecondMax_Dir[2], 2));
				if(TMath::ACos(cospi0thetaz)<1.04&&invarinatmass>60&&invarinatmass<200)
					NCResonantPi0Sideband_ReconShowerVisibleEnergy->Fill(ReconShowerEnergy);
			}
		}
	}

	delete _defaultTree;
}

void DataSets::InitNumuCCBKCSHistograms()
{
//	std::shared_ptr<TH1D> templatehist = std::make_shared<TH1D>(GetTemplateHistogram());
    TH1D* templatehist = GetTemplateHistogram();
	std::string histoname = "numuCCDISMultiPionSideband_ReconShowerVisibleEnergy";
	histoname += (_isWaterConfig ? "_waterin":"_waterout");
	histoname += (_numode ? "_FHC":"_RHC");
	numuCCDISMultiPionSideband_ReconShowerVisibleEnergy = (TH1D*) templatehist->Clone(histoname.c_str());

	delete templatehist;
}

void DataSets::FillNumuCCBKCSHistograms(){
	
	std::cout<<"In DataSet FillNumuCCBKCSHistograms and reading "<<_inputnumuccbkcsfilename<<std::endl;
	InitNumuCCBKCSHistograms();

	if(_inputnumuccbkcsfilename=="")
	{
		std::cout<<"NO NC Control Sample in Current Configuration"<<std::endl;
		return ;
	}

//	std::shared_ptr<TChain> _defaultTree = std::make_shared<TChain>(new TChain("default"));
	TChain* _defaultTree = new TChain("default");
	std::string fileName;
	if(_inputnumuccbkcsfilename.find(".list")!=std::string::npos)
	{
		std::ifstream in(_inputnumuccbkcsfilename.c_str());
		while(in>>fileName)
		{
		  if(in.fail()) break;
		  _defaultTree->AddFile(fileName.c_str());
		}
	}
	else if(_inputnumuccbkcsfilename.find(".root")!=std::string::npos)
		_defaultTree->AddFile(_inputnumuccbkcsfilename.c_str());
	else
	{
		std::cout<<"DataSet: Invalid format of _inputnumuccbkcsfile"<<std::endl;
		exit(0);
	}

	int EventID;
	int isWaterConfig;//bool
//	int numode;
	int accum_level;
	double ReconShowerEnergy;
	_defaultTree->SetBranchAddress("evt", &EventID);
	_defaultTree->SetBranchAddress("isWaterConfig", &isWaterConfig);
//	_defaultTree->SetBranchAddress("numode", &numode);
	_defaultTree->SetBranchAddress("accum_level", &accum_level);
	_defaultTree->SetBranchAddress("ReconShowerEnergy", &ReconShowerEnergy);

	long int NEntries = _defaultTree->GetEntries();
	for(long int ievt=0; ievt<NEntries; ievt++)
	{
		 _defaultTree->GetEntry(ievt);
		if(accum_level>5)
			numuCCDISMultiPionSideband_ReconShowerVisibleEnergy->Fill(ReconShowerEnergy);
	}

	delete _defaultTree;
}

void MCEvent::operator=(MCEvent &mcEvent)
{

	isOnWater = mcEvent.isOnWater; 
	isinFV = mcEvent.isinFV;
	InteractionTarget = mcEvent.InteractionTarget;
	reactionCode = mcEvent.reactionCode;
	NPrimaryPi0s = mcEvent.NPrimaryPi0s;
	NeutrinoPDG = mcEvent.NeutrinoPDG;
	MostProbableTrueParticlePDG = mcEvent.MostProbableTrueParticlePDG;
	TrueVPositionX = mcEvent.TrueVPositionX;
	TrueVPositionY = mcEvent.TrueVPositionY;
	TrueVPositionZ = mcEvent.TrueVPositionZ;
	TrueNeutrinoEnergy = mcEvent.TrueNeutrinoEnergy;
	totTrueParKin = mcEvent.totTrueParKin;

	isSignal = mcEvent.isSignal;
	RunID = mcEvent.RunID; 
	EventID = mcEvent.EventID; 
	isWaterConfig = mcEvent.isWaterConfig;
//	mcEvent.numode = numode;
	accum_level = mcEvent.accum_level;
	HSMTrackLayers = mcEvent.HSMTrackLayers;
	HSMShowerLayers = mcEvent.HSMShowerLayers;
	WTCharges = mcEvent.WTCharges;
	ECalCharges = mcEvent.ECalCharges;
	EDeposit = mcEvent.EDeposit;
	ReconShowerEnergy = mcEvent.ReconShowerEnergy;
	ShowerMedianWidth = mcEvent.ShowerMedianWidth;
	ShowerEDepFraction = mcEvent.ShowerEDepFraction;
	AllParTotEDepInEvent = mcEvent.AllParTotEDepInEvent;
	invariantmass = mcEvent.invariantmass;
	twoshowerEDepfrac = mcEvent.twoshowerEDepfrac;
	cospi0thetaz = mcEvent.cospi0thetaz;

	//make sure the name here is the same with the name in FitParam
	spline_MaCCQE                 = (TGraph*)  mcEvent.spline_MaCCQE->Clone("MAQE");//"MaCCQE");
	spline_MaRES                  = (TGraph*)  mcEvent.spline_MaRES->Clone("MARES");//"MaRES");
	spline_CA5                    = (TGraph*)  mcEvent.spline_MaRES->Clone("CA5");
	spline_ISO_BKG                = (TGraph*)  mcEvent.spline_ISO_BKG               ->Clone("ISO_BKG");             
	spline_FSI_PI_ABS             = (TGraph*)  mcEvent.spline_FSI_PI_ABS            ->Clone("FEFABS");  
	spline_FSI_CEX_LO             = (TGraph*)  mcEvent.spline_FSI_CEX_LO            ->Clone("FEFCX");   
	spline_FSI_INEL_LO            = (TGraph*)  mcEvent.spline_FSI_INEL_LO           ->Clone("FEFQE");    
	spline_FSI_CEX_HI             = (TGraph*)  mcEvent.spline_FSI_CEX_HI            ->Clone("FEFCXH");    
	spline_FSI_INEL_HI            = (TGraph*)  mcEvent.spline_FSI_INEL_HI           ->Clone("FEFQEH");       
	spline_FSI_PI_PROD            = (TGraph*)  mcEvent.spline_FSI_PI_PROD           ->Clone("FEFINEL");
	spline_NIWG_DIS_BY            = (TGraph*)  mcEvent.spline_NIWG_DIS_BY           ->Clone("CC_BY_DIS");  
	spline_NIWG_MultiPi_BY        = (TGraph*)  mcEvent.spline_NIWG_MultiPi_BY       ->Clone("CC_BY_MPi"); 
	spline_NIWG_MultiPi_Xsec_AGKY = (TGraph*)  mcEvent.spline_NIWG_MultiPi_Xsec_AGKY->Clone("CC_AGKY_Mult"); 
	spline_NIWG2012a_nc1piE0      = (TGraph*)  mcEvent.spline_NIWG2012a_nc1piE0     ->Clone("NC1PI_MINE"); //not sure about the name
	spline_NIWG2012a_nccohE0      = (TGraph*)  mcEvent.spline_NIWG2012a_nccohE0     ->Clone("NC_Coh"); 
	spline_NIWG2012a_ncotherE0    = (TGraph*)  mcEvent.spline_NIWG2012a_ncotherE0   ->Clone("NC_other_near");  
	spline_NIWG2012a_nc1pi0E0     = (TGraph*)  mcEvent.spline_NIWG2012a_nc1pi0E0    ->Clone("NC_1gamma");//not sure about the name    
	//...add more later

}


int MCSimUnit::FindEventIndexInXsecFSITreeFromDefaultIndex(int eventid)
{
	if(_EventIDvsEntry.find(eventid)==_EventIDvsEntry.end())
		throw std::runtime_error("event not in XsecFSI Tree");
//		throw std::runtime_error("event %d not in XsecFSI Tree", eventid);
	return _EventIDvsEntry[eventid];
}


bool MCSimUnit::GetMCEvent(MCEvent &mcEvent, int ientry)//, int type)
{
	if(ientry<0||ientry>=_NMCEntries){
		std::cerr<<"entry "<<ientry<<" is out of the range"<<std::endl;
		return false;
	}
	
	_defaultTree->GetEntry(ientry);
//	std::cout<<"In GetMCEvent "<<isWaterConfig<<std::endl;
//	std::cout<<"GetEvent "<<ientry<<" "<<EventID<<std::endl;
	bool passcuts = 0;

	if(_type==0&&accum_level>9&&HSMTrackLayers>13)//cut0&&cut1&&cut2&&cut5)//tmp
		passcuts = 1;
	else if(_type==1&&accum_level>6)//nc
		passcuts = 1;
	else if(_type==2&&accum_level>5)//numucc
		passcuts = 1;
	if(passcuts)
	{
		if(std::abs(NeutrinoPDG)!=12&&std::abs(NeutrinoPDG)!=14)
			std::cout<<"Event "<<EventID<<" NeutrinoPDG = "<<NeutrinoPDG<<std::endl;
		if(isSignal==1&&NeutrinoPDG!=12)
			std::cout<<"Event "<<EventID<<" isSIgnal = 1 but NeutrinoPDG = "<<NeutrinoPDG<<std::endl;

//		std::cout<<"In GetMCEvent "<<isWaterConfig<<std::endl;
		int ievtinxsecfsi = FindEventIndexInXsecFSITreeFromDefaultIndex(EventID);// need to check based on the input data structure later whether their entries are one-to-one corresponding to the _defaultTree.
		_xsecfsiparaTree->GetEntry(ievtinxsecfsi);

		//should define the true info in trueth tree or left in default tree as what it is now?
		mcEvent.isOnWater = isOnWater; 
		mcEvent.isSignal = isSignal;
		mcEvent.isinFV = (p0dNuEMCMCFitterUtils::isInFVRange(TrueVPositionX,0)&&p0dNuEMCMCFitterUtils::isInFVRange(TrueVPositionY,1)&&p0dNuEMCMCFitterUtils::isInFVRange(TrueVPositionZ, 2)) ? 1 : 0;//isinFV;
		mcEvent.InteractionTarget = InteractionTarget;
		mcEvent.reactionCode = reactionCode;
		mcEvent.NPrimaryPi0s = NPrimaryPi0s;
		mcEvent.NeutrinoPDG = NeutrinoPDG;
		mcEvent.MostProbableTrueParticlePDG = MostProbableTrueParticlePDG;
		mcEvent.TrueVPositionX = TrueVPositionX;
		mcEvent.TrueVPositionY = TrueVPositionY;
		mcEvent.TrueVPositionZ = TrueVPositionZ;
		mcEvent.TrueNeutrinoEnergy = TrueNeutrinoEnergy;
//		mcEvent.totTrueParKin = totTrueParKin;

		mcEvent.RunID = RunID; 
		mcEvent.EventID = EventID; 
//		mcEvent.numode = numode;
		mcEvent.isWaterConfig = isWaterConfig;

		mcEvent.accum_level = accum_level;
		mcEvent.HSMTrackLayers = HSMTrackLayers;
		mcEvent.HSMShowerLayers = HSMShowerLayers;
//		mcEvent.HSMShowerContainID = HSMShowerContainID;
//		mcEvent.nMuonDecayClusters = nMuonDecayClusters;
		mcEvent.WTCharges = WTCharges;
		mcEvent.ECalCharges = ECalCharges;
		mcEvent.EDeposit = EDeposit;
		mcEvent.ReconShowerEnergy = ReconShowerEnergy;
		mcEvent.ShowerMedianWidth = ShowerMedianWidth;
		mcEvent.ShowerEDepFraction = ShowerEDepFraction;
		mcEvent.AllParTotEDepInEvent = AllParTotEDepInEvent;

		mcEvent.totTrueParKin = GettotTrueConParKin();
		//not directly from setbranchadress
		if(_type==1)//nc
		{
			if(NValidShowers<2)
				throw std::runtime_error("NValidShowers<2, not mathcing the cuts applied");
			std::pair<int, int> maxtwo = pi0ShowerUtils::FindMaxTwoShower(particleDim, parScaledMom, parMom, parEDep, 0, iIncrementPar-1);
//			mcEvent.maxEDepShowerIndex = maxtwo.first;
//			mcEvent.secondmaxEDepShowerIndex = maxtwo.second;
			if(maxtwo.first>=0&&maxtwo.second>=0)
			{
				mcEvent.twoshowerEDepfrac = (parEDep[maxtwo.first]+parEDep[maxtwo.second])/AllParTotEDepInEvent;
				double Max_Dir[3] = {parDirection[maxtwo.first][0], parDirection[maxtwo.first][1], parDirection[maxtwo.first][2]};
				double SecondMax_Dir[3] = {parDirection[maxtwo.second][0], parDirection[maxtwo.second][1], parDirection[maxtwo.second][2]};
				double invarinatmass = pi0ShowerUtils::CalInvariantMass(parScaledMom[maxtwo.first], Max_Dir, parScaledMom[maxtwo.second],SecondMax_Dir); // use nueutil mom
//					double cospi0thetaz = (Max_pi0Mom*Max_Dir[2]+SecondMax_pi0Mom*SecondMax_Dir[2])/TMath::Sqrt(TMath::Power(Max_pi0Mom*Max_Dir[0]+SecondMax_pi0Mom*SecondMax_Dir[0], 2)+TMath::Power(Max_pi0Mom*Max_Dir[1]+SecondMax_pi0Mom*SecondMax_Dir[1], 2)+TMath::Power(Max_pi0Mom*Max_Dir[2]+SecondMax_pi0Mom*SecondMax_Dir[2], 2));
				double cospi0thetaz = (parScaledMom[maxtwo.first]*Max_Dir[2]+parScaledMom[maxtwo.second]*SecondMax_Dir[2])/TMath::Sqrt(TMath::Power(parScaledMom[maxtwo.first]*Max_Dir[0]+parScaledMom[maxtwo.second]*SecondMax_Dir[0], 2)+TMath::Power(parScaledMom[maxtwo.first]*Max_Dir[1]+parScaledMom[maxtwo.second]*SecondMax_Dir[1], 2)+TMath::Power(parScaledMom[maxtwo.first]*Max_Dir[2]+parScaledMom[maxtwo.second]*SecondMax_Dir[2], 2));

				mcEvent.invariantmass = invarinatmass;
				mcEvent.cospi0thetaz = cospi0thetaz;
			}
		}

		//make sure the name here is the same with the name in FitParam
		mcEvent.spline_MaCCQE = (TGraph*) spline_MaCCQE->Clone("MAQE");//"MaCCQE");
		mcEvent.spline_MaRES = (TGraph*) spline_MaRES->Clone("MARES");//"MaRES");
		mcEvent.spline_CA5 = (TGraph*) spline_MaRES->Clone("CA5");
		mcEvent.spline_ISO_BKG                = (TGraph*)  spline_ISO_BKG               ->Clone("ISO_BKG");             
		mcEvent.spline_FSI_PI_ABS             = (TGraph*)  spline_FSI_PI_ABS            ->Clone("FEFABS");  
		mcEvent.spline_FSI_CEX_LO             = (TGraph*)  spline_FSI_CEX_LO            ->Clone("FEFCX");   
		mcEvent.spline_FSI_INEL_LO            = (TGraph*)  spline_FSI_INEL_LO           ->Clone("FEFQE");    
		mcEvent.spline_FSI_CEX_HI             = (TGraph*)  spline_FSI_CEX_HI            ->Clone("FEFCXH");    
		mcEvent.spline_FSI_INEL_HI            = (TGraph*)  spline_FSI_INEL_HI           ->Clone("FEFQEH");       
		mcEvent.spline_FSI_PI_PROD            = (TGraph*)  spline_FSI_PI_PROD           ->Clone("FEFINEL");
		mcEvent.spline_NIWG_DIS_BY            = (TGraph*)  spline_NIWG_DIS_BY           ->Clone("CC_BY_DIS");  
		mcEvent.spline_NIWG_MultiPi_BY        = (TGraph*)  spline_NIWG_MultiPi_BY       ->Clone("CC_BY_MPi"); 
		mcEvent.spline_NIWG_MultiPi_Xsec_AGKY = (TGraph*)  spline_NIWG_MultiPi_Xsec_AGKY->Clone("CC_AGKY_Mult"); 
		mcEvent.spline_NIWG2012a_nc1piE0      = (TGraph*)  spline_NIWG2012a_nc1piE0     ->Clone("NC1PI_MINE"); //not sure about the name
		mcEvent.spline_NIWG2012a_nccohE0      = (TGraph*)  spline_NIWG2012a_nccohE0     ->Clone("NC_Coh"); 
		mcEvent.spline_NIWG2012a_ncotherE0    = (TGraph*)  spline_NIWG2012a_ncotherE0   ->Clone("NC_other_near");  
		mcEvent.spline_NIWG2012a_nc1pi0E0     = (TGraph*)  spline_NIWG2012a_nc1pi0E0    ->Clone("NC_1gamma");//not sure about the name    
		//mcEvent.spline_fsiinelLow_pi = (TGraph*) spline_fsiinelLow_pi->Clone("FSI_INEL_LO");
		//...add more later


		/*
		bool infunc = isSignalEvent();
		if(infunc&&isSignal!=1)
		{
			std::cout<<" isSignal = "<<isSignal<<" and functions given true"<<" More info: "<<EventID<<" "<<mcEvent.isinFV<<" "<<accum_level<<" "<<NeutrinoPDG<<std::endl;
//			exit(0);
		}
		else if(!infunc&&isSignal==1) //-1
		{
			std::cout<<" isSignal = "<<isSignal<<" but functions given false"<<" More info: "<<EventID<<" "<<mcEvent.isinFV<<" "<<accum_level<<" "<<NeutrinoPDG<<std::endl;
//			exit(0);
		}
		*/
		return true;
	}
	else
		return false;
	
}

void MCSimUnit::GetMCEventsVect(MCEventsVect& mcEvents, int startindex, int endindex, int cutsid)
{
	if(endindex==0)
		endindex = _NMCEntries;
	if(startindex<0||startindex>=_NMCEntries||endindex<0||endindex>_NMCEntries||startindex>endindex){
		std::cerr<<"["<<startindex<<", "<<endindex<<")"<<"is not a valid range"<<std::endl;
		exit(0);
	}

	for(int i=startindex; i<endindex; i++)
	{
		MCEvent evt;
		if(GetMCEvent(evt, i))//, cutsid))
			mcEvents.push_back(evt);
	}
}

void MCSimUnit::GetAllSamples()
{
	std::cout<<"In GetAllSamples to Read MCSamples"<<std::endl;
	for(int ientry=0; ientry<_NMCEntries; ientry++)
	{
//		_defaultTree->GetEntry(ientry);
		MCEvent evt;
		if(!GetMCEvent(evt, ientry))
			continue;
		if(ientry%1000<10)//output first ten in the 1000 events 
			std::cout<<ientry<<" "<<evt.EventID<<std::endl;

		//some cuts are applied in GetMCEvent. If wanting to apply additional cuts, we can add here or in GetMCEvent
		if(_type==1&&!(evt.twoshowerEDepfrac>0.85&&TMath::ACos(evt.cospi0thetaz)<1.04&&evt.invariantmass>60&&evt.invariantmass<200))
			continue;
		_sample.push_back(evt); //signal need to tune SMw ans SCF, ncbk need to tune SCF
		/*
		if(_type==0)
		{
			if(evt.accum_level>9&&evt.HSMTrackLayers>13) 
			{
				if(evt.isSignal==-1)
					std::cout<<"Event "<<evt.EventID<<" isSignal = -1. "<<" it's accum_level is "<<evt.accum_level<<std::endl;
	//			std::cout<<"evt.isWaterConfig = "<<evt.isWaterConfig<<std::endl;
				_signalsample.push_back(evt);
			}
		}
		if(evt.cut0&&evt.cut1&&evt.cut2&&evt.cut5&&evt.cut6&&evt.NValidShowers>=2&&evt.nMuonDecayClusters==0&&evt.HSMShowerLayers>10&&evt.HSMShowerContainID==0)//&&ShowerEDepFraction<0.9-->need reweight later)//add cuts for selecting ncpi0 cs 
		{
			std::cout<<evt.EventID<<" "<<evt.maxEDepShowerIndex<<" "<<evt.secondmaxEDepShowerIndex;//<<" "<<evt.parEDep[evt.maxEDepShowerIndex]<<" "<<evt.parEDep[evt.secondmaxEDepShowerIndex]<<std::endl;
			for(int i=0; i<evt.iIncrementPar; i++)//100; i++)//
np			{
				if(evt.parEDep[i]>-1)
					std::cout<<" "<<i<<"-"<<evt.parEDep[i]<<"-"<<evt.particleDim[i]<<"-"<<evt.parScaledMom[i];
			}
			std::cout<<std::endl;
			if(evt.maxEDepShowerIndex>=0&&evt.secondmaxEDepShowerIndex>=0&&(evt.parEDep[evt.maxEDepShowerIndex]+evt.parEDep[evt.secondmaxEDepShowerIndex])/evt.AllParTotEDepInEvent>0.85)
				_ncbksample.push_back(evt);//GetCurrentEvent());
		}
		if(evt.cut0&&evt.cut1&&evt.cut2&&evt.cut5&&evt.cut6&&evt.NValidTracks>=2&&evt.NValidParticles>=3)//add cuts for selecting numuDIS cs
			 _numuccbksample.push_back(evt);//GetCurrentEvent());
		*/
	}

	std::cout<<"_sample size: "<<_sample.size()<<std::endl;
	
}

bool MCSimUnit::isSignalwBDTdef()
{
//	std::cout<<"Event "<<EventID<<" "<<"iIncrementTruePars = "<<iIncrementTruePars<<std::endl;
	if(!p0dNuEMCMCFitterUtils::isInOrigFVRange(TrueVPositionX,0)||!p0dNuEMCMCFitterUtils::isInOrigFVRange(TrueVPositionY,1)||!p0dNuEMCMCFitterUtils::isInOrigFVRange(TrueVPositionZ, 2)) //check whether in FV //or we can use isinFV, just need to change th sequence of code in getmcevetn 
		return 0;
		
	double electronmass = 0.511;
	double protonmass =  938.27;
	double pionmass = 139.57;
//	std::cout<<"Event "<<EventID<<" "<<"iIncrementTruePars = "<<iIncrementTruePars<<std::endl;
	float trueelecdir[3] = {0,0,0};
	bool foundelec = 0;
	double electronenergy = 0;
	for(int kp=0; kp<iIncrementTruePars; kp++){
		if(true_ParticleID[kp]==true_ParticlePrimaryID[kp]&&true_ParticlePDG[kp]==11){
			foundelec = 1;
			electronenergy = TMath::Sqrt(true_ParticleMom[kp]*true_ParticleMom[kp]-electronmass*electronmass)-electronmass;
			p0dNuEMCMCFitterUtils::copyarray(trueelecdir, true_ParticleDir[kp], 3);
			break;
		}
	}

	if(!foundelec)	return false;
//	if(NueReaction<0||NueReaction>6)
	if(NeutrinoPDG!=12||std::abs(reactionCode)>30)//nueCC
	{
		std::cout<<"NueReaction doesn't match 1e-."<<" NeutrinoPDG = "<<NeutrinoPDG<<", reactionCode = "<<reactionCode<<std::endl;
		return false;
	}

	BDTClassifier* protonclassifier = new electronproton_4features_v2_class();
	BDTClassifier* piplusclassifier = new electronpiplus_4features_v2_class();
	union BDTClassifier::BDTClassifierFeature features[4];//4, 8

	for(int kp=0; kp<iIncrementTruePars; kp++){
		if(true_ParticleID[kp]==true_ParticlePrimaryID[kp]&&true_ParticlePDG[kp]==2212){
			double cosangle = (trueelecdir[0]*true_ParticleDir[kp][0]+trueelecdir[1]*true_ParticleDir[kp][1]+trueelecdir[2]*true_ParticleDir[kp][2]);
			double kineticenergy  = TMath::Sqrt(true_ParticleMom[kp]*true_ParticleMom[kp]+protonmass*protonmass)-protonmass;
			
			features[0].fvalue = (float) kineticenergy;
			features[1].fvalue = (float) electronenergy/kineticenergy;
			features[2].fvalue = (float) TMath::ACos(cosangle);
			features[3].fvalue = (float) TMath::ACos(true_ParticleDir[kp][2]);
			
			if(protonclassifier->GetClassfication(features, 1))
				return 0;
		}
		else if(true_ParticleID[kp]==true_ParticlePrimaryID[kp]&&abs(true_ParticlePDG[kp])==211){
			double cosangle = (trueelecdir[0]*true_ParticleDir[kp][0]+trueelecdir[1]*true_ParticleDir[kp][1]+trueelecdir[2]*true_ParticleDir[kp][2]);
			double kineticenergy  = TMath::Sqrt(true_ParticleMom[kp]*true_ParticleMom[kp]+pionmass*pionmass)-pionmass;
			
			features[0].fvalue = (float) kineticenergy;
			features[1].fvalue = (float) electronenergy/kineticenergy;
			features[2].fvalue = (float) TMath::ACos(cosangle);
			features[3].fvalue = (float) TMath::ACos(true_ParticleDir[kp][2]);
			
			if(piplusclassifier->GetClassfication(features, 1))
				return 0;
		}
	}
	return 1;

}



