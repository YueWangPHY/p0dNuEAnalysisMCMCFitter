#ifndef SYSMATICUNCERTAINTYCORRECTION_H
#define SYSMATICUNCERTAINTYCORRECTION_H

#include "DataTypes.h"
#include "FitParams.h"

class SystematicUncertaintyCorr{

public:
	SystematicUncertaintyCorr(){
		_debug = 0;
		_debugweight = 0;//0;//1;
	}
	~SystematicUncertaintyCorr(){}

	double ReweightEvent(MCEvent& corrected, const MCEvent& nominalevt, const std::vector<double>& param) const;
	double ReweightEvent(MCEvent& corrected, const MCEvent& nominalevt, const std::vector<double>& param, int sampleid) const;

	double CalReconShowerEnergyWithSyst(const MCEvent& nominalevt, const std::vector<double>& param) const;
	double CalShowerMedianWidthWithSyst(const MCEvent& nominalevt, const std::vector<double>& param) const;
	double CalShowerEDepFractionWithSyst(const MCEvent& nominalevt, const std::vector<double>& param) const;
	double CalPIDSystWeight(const MCEvent& nominalevt, const std::vector<double>& param) const;
	double CalOOFVPi0WeightSyst(const MCEvent& nominalevt, const std::vector<double>& param) const;
	double CalcMassSystWeight(const MCEvent& nominalevt, const std::vector<double>& param) const;
	double CalcXSecFSISystWeightFromT2KReweight(const MCEvent& nominalevt, const std::vector<double>& param) const;

	double CalcXSecNormSystWeight(const MCEvent& nominalevt, const std::vector<double>& param) const;//calculate weight from xsec param which are not through t2k-reweight

	double CalcFluxSystWeight(const MCEvent& nominalevt, const std::vector<double>& param) const;

	double CalcSignalEventWeight(const MCEvent& nominalevt, const std::vector<double>& param) const;
/*
 *         weight *= CalcXSecSystWeightFromResponseFunction(evt,param);//done
 *             weight *= CalcXSecNormSystWeight(evt,param);
 *                 weight *= CalcFSISystWeightFromResponseFunction(evt,param);//done
 *                     weight *= CalcFluxSystWeight(evt, param);
 *                         weight *= CalcSignalEventWeight(evt, param);
 *other det sys other than SMW and SCF
 */                 

private:
	FitParams fitparam;
	Binning binobj;
	bool _debug;
	bool _debugweight;

};


#endif
