#ifndef SYSMATICUNCERTAINTYCORRECTION_H
#define SYSMATICUNCERTAINTYCORRECTION_H

#include "DataTypes.h"
#include "FitParams.h"

class SystematicUncertaintyCorr{

public:
	SystematicUncertaintyCorr(){
		_debug = 0;//1;
		_debugweight = 0;//1;
	}
	~SystematicUncertaintyCorr(){}

	double ReweightEvent(MCEvent& corrected, const MCEvent& nominalevt, const std::vector<double>& param) const;
	double ReweightEvent(MCEvent& corrected, const MCEvent& nominalevt, const std::vector<double>& param, int sampleid) const;
	double ReweightNC1pi0CSEvent(MCEvent& corrected, const MCEvent& nominalevt, const std::vector<double>& param) const;
	double ReweightNumuCCCSEvent(MCEvent& corrected, const MCEvent& nominalevt, const std::vector<double>& param) const;

	double CalReconShowerEnergyWithSyst(const MCEvent& nominalevt, const std::vector<double>& param) const;
	double CalShowerMedianWidthWithSyst(const MCEvent& nominalevt, const std::vector<double>& param) const;
	double CalShowerEDepFractionWithSyst(const MCEvent& nominalevt, const std::vector<double>& param) const;
	double CalPIDSystWeight(const MCEvent& nominalevt, const std::vector<double>& param) const;
	double CalOOFVPi0WeightSyst(const MCEvent& nominalevt, const std::vector<double>& param) const;
	double CalcMassSystWeight(const MCEvent& nominalevt, const std::vector<double>& param) const;
	//write as template later
	double CalcXSecFSISystWeightFromT2KReweight(const MCEvent& nominalevt, const std::vector<double>& param) const;
	double CalcXSecFSISystWeightFromT2KReweight(const TruthEvent& nominalevt, const std::vector<double>& param) const;

	double CalcFluxSystWeight(const MCEvent& nominalevt, const std::vector<double>& param) const;
	double CalcFluxSystWeight(const TruthEvent& nominalevt, const std::vector<double>& param) const;
	////
	double CalcXSecNormSystWeight(const MCEvent& nominalevt, const std::vector<double>& param) const;//calculate weight from xsec param which are not through t2k-reweight

	double CalcSignalEventWeight(const MCEvent& nominalevt, const std::vector<double>& param) const;
/*
 *         weight *= CalcXSecSystWeightFromResponseFunction(evt,param);//done
 *             weight *= CalcXSecNormSystWeight(evt,param);
 *                 weight *= CalcFSISystWeightFromResponseFunction(evt,param);//done
 *                     weight *= CalcFluxSystWeight(evt, param);
 *                         weight *= CalcSignalEventWeight(evt, param);
 *other det sys other than SMW and SCF
 */                 
	//NC1pi0 CS alone
	double CalInvariantMassWithSyst(const MCEvent& nominalevt, const std::vector<double>& param) const;
	double CalTwoShowerChargeRatioWithSyst(const MCEvent& nominalevt, const std::vector<double>& param) const;
	double CalcMuDecayEffCorrectionWeight(const MCEvent& nominalevt, const std::vector<double>& param, const int AllCCEvt, const int CCEvtNoMdk, const int CCEvtMdk) const;
	double CalcMuDecayFakeRateCorrectionWeight(const MCEvent& nominalevt, const std::vector<double>& param, const int AllNCEvt, const int NCEvtNoMdk, const int NCEvtMdk) const;

	FitParams fitparam;

private:
	Binning binobj;
	bool _debug;
	bool _debugweight;

};


#endif
