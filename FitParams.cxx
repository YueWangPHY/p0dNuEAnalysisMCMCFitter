#include <vector> 

#include "FitParams.h"


const double FitParams::EM_SCALE_SHOWER_ECAL = 0.1701;
const double FitParams::EM_SCALE_SHOWER_WTWATERIN = 0.1667;
const double FitParams::EM_SCALE_SHOWER_WTWATEROUT = 0.1158;
const double FitParams::EM_SCALE_TRACK_ECAL = 0.1845;
const double FitParams::EM_SCALE_TRACK_WTWATERIN = 0.1847;
const double FitParams::EM_SCALE_TRACK_WTWATEROUT = 0.1340;


FitParams::FitParams() {
	sigwt_params = true;
	xsec_params = true;
	flux_params = true;
	det_params = true;//false;//true;
	samplecon_params = false;//true;//for now
	det_params_nc1pi0 = true;

	nParams = 0;
	// to save time when searching 
//	nSigWtParams = 0;
//	nXsecParams = 0;
//	nFluxParams = 0;
//	nDetParams = 0;
//	nSampleConParams = 0;

	covariance = NULL;
	covarianceI = NULL;
	correlation = NULL;
	correlationI = NULL;

	NMAXPARS = 500;

	fluxbins_nd_numode_numu  = new TAxis();
	fluxbins_nd_numode_numub   = new TAxis();
	fluxbins_nd_numode_nue = new TAxis();
	fluxbins_nd_numode_nueb  = new TAxis();


	FillFitParams();
}

FitParams::~FitParams(){

	if(covariance != NULL) covariance->Delete();
	if(covarianceI != NULL) covarianceI->Delete();
	if(correlation != NULL) correlation->Delete();
	if(correlationI != NULL) correlationI->Delete();
}

void FitParams::FillFitParams(){
	covariance = new TMatrixDSym(NMAXPARS);
	correlation = new TMatrixDSym(NMAXPARS);//Yue add on Mar 3

	//sequqence of params in the vector. So the sequqence is important. Keep consistent
	if(sigwt_params) FillFitParams(kSigWt);
	if(xsec_params) FillFitParams(kXsec);
	if(flux_params) FillFitParams(kFlux);
	if(det_params) FillFitParams(kDet);
	if(samplecon_params) FillFitParams(kSampleCon);

	if (covariance != NULL){
		SetCovarianceI();
		SetCorrelation();
		SetCorrelationI();
	}

	if(nParams!=ParamNames.size()){
		std::cout << "in FitParam: nParams!=ParamNames.size()" << std:: endl;
		exit(0);
	}
	for(int i=0; i<(int)ParamNames.size(); i++)
		ParamNamesMap.insert({ParamNames[i], i});
}

void FitParams::FillFitParams(Int_t param_type){
	TFile *inFile;
	TTree *inT;

	if (param_type == kSigWt){
		inFile = new TFile("Inputs/sigwtparam_input.root", "open");
		if(!inFile) std::cerr << "Cannot find sig wt params file in Inputs/" << std::endl;
		inT = (TTree*)inFile->Get("sigWtParams");
	}
	else if (param_type == kXsec) {
		inFile = new TFile("Inputs/Xsecparam_input.root", "open");
		if(!inFile) std::cerr << "Cannot find params file in Inputs/" << std::endl;
		inT = (TTree*)inFile->Get("XsecParams");
	}
	else if (param_type == kFlux) {
		inFile = new TFile("Inputs/Fluxparam_input.root", "open");
		if(!inFile) std::cerr << "Cannot find params file in Inputs/" << std::endl;
		inT = (TTree*)inFile->Get("FluxParams");
	}
	else if (param_type == kDet){
		inFile = new TFile("Inputs/detparam_input.root", "open");
		if(!inFile) std::cerr << "Cannot find detector params file in Inputs/" << std::endl;
		inT = (TTree*)inFile->Get("detParams");
	}
	else if (param_type == kSampleCon){
		inFile = new TFile("Inputs/sampleconparam_input.root", "open");
		if(!inFile) std::cerr << "Cannot find sample constraint params file in Inputs/" << std::endl;
		inT = (TTree*)inFile->Get("sampleConParams");
	}
	else{
		std::cerr << "Incorrect Parameter Type Specified!" << std::endl;
		exit(0);
	}

	Int_t nParamsT =0;
	std::vector<std::string> *ParamNamesT=0;
	std::vector<double> *nominalValuesT=0;
	std::vector<double> *priorValuesT=0;
	std::vector<double> *sigmaValuesT=0;
	std::vector<double> *lBoundValuesT=0;
	std::vector<double> *uBoundValuesT=0;
	TMatrixDSym *covarianceT = NULL;

	inT->SetBranchAddress("nParams",&nParamsT);
	inT->SetBranchAddress("param_name",&ParamNamesT);
	inT->SetBranchAddress("nominal",&nominalValuesT);
	inT->SetBranchAddress("prior",&priorValuesT);
	inT->SetBranchAddress("sigma",&sigmaValuesT);
	inT->SetBranchAddress("lb",&lBoundValuesT);
	inT->SetBranchAddress("ub",&uBoundValuesT);
	inT->SetBranchAddress("covariance",&covarianceT);

	if (param_type == kFlux) {
		inT->SetBranchAddress("fluxbins_nu_numu",  &fluxbins_nd_numode_numu);
		inT->SetBranchAddress("fluxbins_nu_numub", &fluxbins_nd_numode_numub);
		inT->SetBranchAddress("fluxbins_nu_nue",   &fluxbins_nd_numode_nue);
		inT->SetBranchAddress("fluxbins_nu_anue",  &fluxbins_nd_numode_nueb);

//		inT->SetBranchAddress("nd5_numode_numu_bins",  &fluxbins_nd_numode_numu);
//		inT->SetBranchAddress("nd5_numode_numub_bins", &fluxbins_nd_numode_numub);
//		inT->SetBranchAddress("nd5_numode_nue_bins",   &fluxbins_nd_numode_nue);
//		inT->SetBranchAddress("nd5_numode_nueb_bins",  &fluxbins_nd_numode_nueb);
//
		//just considered FHC for now, so anumumode not include for now
//		inT->SetBranchAddress("nd5_anumode_numu_bins",  &fluxbins_nd_anumode_numu);
//		inT->SetBranchAddress("nd5_anumode_numub_bins", &fluxbins_nd_anumode_numub);
//		inT->SetBranchAddress("nd5_anumode_nue_bins",   &fluxbins_nd_anumode_nue);
//		inT->SetBranchAddress("nd5_anumode_nueb_bins",  &fluxbins_nd_anumode_nueb);
	}

	inT->GetEntry(0);//only one entry. This structure uses the one for nc1pi0 package. Use it for now, May change later to try to merge with xsLLhFitter. at least after I get some fitted results
	int marker = nParams;
	nParams += nParamsT;

//	if (param_type == kSigWt)
//		nSigWtParams = nParamsT;
//	else if (param_type == kXsec) 
//		nXsecParams = nParamsT;
//	else if (param_type == kFlux)
//		nFluxParams = nParamsT;
//	else if (param_type == kDet)
//		nDetParams = nParamsT;
//	else if(param_type==kSampleCon)
//		nSampleConParams = nParamsT;
//	else
//		std::cout<<"some other type not defined"<<std::endl;

	for(int i =0; i< nParamsT; i++){
		ParamNames.push_back(ParamNamesT->at(i));
		nominalValues.push_back(nominalValuesT->at(i));
		priorValues.push_back(priorValuesT->at(i));
		sigmaValues.push_back(sigmaValuesT->at(i));
		lBoundValues.push_back(lBoundValuesT->at(i));
		uBoundValues.push_back(uBoundValuesT->at(i));
	}

	covariance->ResizeTo(nParams,nParams);
	for(int iRow =0; iRow < nParamsT; iRow++)
	{
		for(int iCol =0; iCol < nParamsT; iCol++)
		{
		  int i = marker + iRow;
		  int j = marker + iCol;
		  (*covariance)(i,j) = (*covarianceT)(iRow,iCol);
		}
	}

  delete inFile;
}

void FitParams::SetCovarianceI()
{
	Double_t det = covariance->Determinant();
	std::cout << " original det is : " << det << std::endl;

	int count = 0;
	TMatrixDSym* temp = (TMatrixDSym*)covariance->Clone("temp");
	if (det < 1e-20)
	{
		do
		{
			count++;
			(*temp) = (*covariance);
			double det = temp->Determinant();
			if (det > 0)
			{
				(*covariance) = (*temp);
				break;
			}
			for (int i = 0 ; i < nParams; ++i){
				(*covariance)(i,i) = 0.000001 + (*covariance)(i,i);
  			}
		}while(true);
	}

	det = covariance->Determinant();
	std::cout << "after iteration # : " << count << " new det is : " << det << std::endl;
	if(det < 0){
		std::cout << "Warning, cov matrix is non invertible. Det is: " << det << std:: endl;
		exit(1);
	}

	covarianceI = (TMatrixDSym*)covariance->Clone("invCov");
	covarianceI->Invert();
}

void FitParams::SetCorrelation()
{
//	double* sqrtDiag = new double[nParams];
	std::vector<double> sqrtDiag(nParams);
	correlation->ResizeTo(nParams,nParams);//Yue add on Mar 3

	for(int i = 0; i < nParams; i++){
		sqrtDiag[i] = TMath::Sqrt((*covariance)(i,i));
	}

	for (Int_t i = 0; i< nParams; i++){
		for (Int_t j = 0; j< nParams; j++){
//			std::cout<<sqrtDiag[i]<<" "<<sqrtDiag[j]<<std::endl;
  			(*correlation)(i,j) = (*covariance)(i,j)/(sqrtDiag[i]*sqrtDiag[j]);
		}
	}
}

void FitParams::SetCorrelationI()
{
	Double_t det = correlation->Determinant();
  	if(det < 0){
    	std::cout << "Warning, correlation matrix is non invertible. Det is: " << det << std:: endl;
    	exit(1);
  	}
    correlationI = (TMatrixDSym*)correlation->Clone("invCorr");
    correlationI->Invert();
}


void FitParams::GetParamNames(std::vector<std::string> &params) const {
	params = ParamNames;
}

void FitParams::GetInitFitParams(std::vector<double> &params) const {
	params = nominalValues;
}

void FitParams::GetPriorFitParams(std::vector<double> &params) const {
	params = priorValues;
}

void FitParams::GetSigmaFitParams(std::vector<double> &params) const {
	params = sigmaValues;
}

void FitParams::GetLowerBoundParams(std::vector<double> &params) const {
	params = lBoundValues;
}

void FitParams::GetUpperBoundParams(std::vector<double> &params) const {
	params = uBoundValues;
}

int FitParams::GetNeutrinoEnergyBinIndex(int numode, int nupdg, double Enu) const{

	if(numode==1){//FHC
		if(nupdg==14)
			return fluxbins_nd_numode_numu->FindBin(Enu);
		else if(nupdg==-14)
			return fluxbins_nd_numode_numub->FindBin(Enu);
		else if(nupdg==12)
			return fluxbins_nd_numode_nue->FindBin(Enu);
		else if(nupdg==-12)
			return fluxbins_nd_numode_nueb->FindBin(Enu);
		else
			return -1;
	}
	else if(numode==0){
		if(nupdg==14)
			return fluxbins_nd_anumode_numu->FindBin(Enu);
		else if(nupdg==-14)
			return fluxbins_nd_anumode_numub->FindBin(Enu);
		else if(nupdg==12)
			return fluxbins_nd_anumode_nue->FindBin(Enu);
		else if(nupdg==-12)
			return fluxbins_nd_anumode_nueb->FindBin(Enu);
		else
			return -1;
	}
	else
		return -1;

}

int FitParams::GetParamIndexFromExactName(std::string name) const {

	auto it = ParamNamesMap.find(name);
	if(it!=ParamNamesMap.end())
		return it->second;
	else{
       std::cout<<"Parameter, "<<name<<", NOT FOUND"<<std::endl;
       exit(0);
    }
	return -1;
//	int index = -1;
//	for(int i=0; i<nParams; i++)//later when names form are regulated, then can use nSigWtParams etc to search just a range to save some time
//	{
//		if(name = ParamNames[i])
//		{
//			index = i;
//			break;
//		}
//	}
//	if(index<0){
//		std::cout<<"Parameter, "<<name<<", NOT FOUND"<<std::endl;
//		exit(0);
//	}
//	return index;
}

std::vector<int> FitParams::GetParamIndicesFromName(std::string partname) const {

	std::vector<int> indices;
	for(int i=0; i<nParams; i++){
		if(ParamNames[i].find(partname)!=std::string::npos)
			indices.push_back(i);
	}	
	if(indices.size()==0){
		std::cout<<"NO related parameters FOUND for "<<partname<<std::endl;
		exit(0);
	}
	return indices;
}
