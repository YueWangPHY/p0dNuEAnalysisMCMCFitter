#ifndef PI0RELATEDQUANCAL_H
#define PI0RELATEDQUANCAL_H

#include <iostream>
#include <utility>
#include <TMath.h>

#include "SCALECONSTS.h"

namespace pi0ShowerUtils{

	double CalPi0UtilsMom(const double nueMom, const float EDep, const int isWaterConfig)
	{
		double chargeratioinWT = 0;
		double pi0utilMom = -1;
		if(isWaterConfig == 1)
		{
			chargeratioinWT = (nueMom/EDep-EM_SCALE_SHOWER_ECAL)/(EM_SCALE_SHOWER_WATER-EM_SCALE_SHOWER_ECAL);
			double pi0_EMSLOP = EM_SLOPE_WATER*chargeratioinWT + EM_SLOPE_ECAL*(1.0-chargeratioinWT);
			double pi0_EMYINT = EM_YINT_WATER*chargeratioinWT + EM_YINT_ECAL*(1.0-chargeratioinWT);
			pi0utilMom = pi0_EMSLOP*EDep+pi0_EMYINT;
		}
		else if(isWaterConfig==0)
		{
			chargeratioinWT = (nueMom/EDep-EM_SCALE_SHOWER_ECAL)/(EM_SCALE_SHOWER_AIR-EM_SCALE_SHOWER_ECAL);
			double pi0_EMSLOP = EM_SLOPE_AIR*chargeratioinWT + EM_SLOPE_ECAL*(1.0-chargeratioinWT);
			double pi0_EMYINT = EM_YINT_AIR*chargeratioinWT + EM_YINT_ECAL*(1.0-chargeratioinWT);
			pi0utilMom = pi0_EMSLOP*EDep+pi0_EMYINT;
		}
		else
			std::cout<<"Warning!!! neither water-in nor water-out"<<std::endl;
		return pi0utilMom;
	}


	double CalPi0UtilsMom_withWeightedScale(const double nueMom, const float EDep, const int isWaterConfig, const double wtslopew, const double wtintw, const double ecalslopew, const double ecalintw)
	{
		double chargeratioinWT = 0;
		double pi0utilMom = -1;
		if(isWaterConfig==1)
		{
			chargeratioinWT = (nueMom/EDep-EM_SCALE_SHOWER_ECAL)/(EM_SCALE_SHOWER_WATER-EM_SCALE_SHOWER_ECAL);
			double pi0_EMSLOP = wtslopew*EM_SLOPE_WATER*chargeratioinWT + ecalslopew*EM_SLOPE_ECAL*(1.0-chargeratioinWT);
			double pi0_EMYINT = wtintw*EM_YINT_WATER*chargeratioinWT + ecalintw*EM_YINT_ECAL*(1.0-chargeratioinWT);
			pi0utilMom = pi0_EMSLOP*EDep+pi0_EMYINT;
		}
		else if (isWaterConfig==0)
		{
			chargeratioinWT = (nueMom/EDep-EM_SCALE_SHOWER_ECAL)/(EM_SCALE_SHOWER_AIR-EM_SCALE_SHOWER_ECAL);
			double pi0_EMSLOP = wtslopew*EM_SLOPE_AIR*chargeratioinWT + ecalslopew*EM_SLOPE_ECAL*(1.0-chargeratioinWT);
			double pi0_EMYINT = wtintw*EM_YINT_AIR*chargeratioinWT + ecalintw*EM_YINT_ECAL*(1.0-chargeratioinWT);
			pi0utilMom = pi0_EMSLOP*EDep+pi0_EMYINT;
		}
		else
			std::cout<<"Warning!!! neither water-in nor water-out"<<std::endl;
		return pi0utilMom;
	}

	double CalPi0UtilsMom_withWeightedScale(const double nueMom, const double EDep, const int isWaterConfig, const double wtslopew, const double wtintw, const double ecalslopew, const double ecalintw)
	{
		double chargeratioinWT = 0;
		double pi0utilMom = -1;
		if(isWaterConfig==1)
		{
			chargeratioinWT = (nueMom/EDep-EM_SCALE_SHOWER_ECAL)/(EM_SCALE_SHOWER_WATER-EM_SCALE_SHOWER_ECAL);
			double pi0_EMSLOP = wtslopew*EM_SLOPE_WATER*chargeratioinWT + ecalslopew*EM_SLOPE_ECAL*(1.0-chargeratioinWT);
			double pi0_EMYINT = wtintw*EM_YINT_WATER*chargeratioinWT + ecalintw*EM_YINT_ECAL*(1.0-chargeratioinWT);
			pi0utilMom = pi0_EMSLOP*EDep+pi0_EMYINT;
		}
		else if(isWaterConfig==0)
		{
			chargeratioinWT = (nueMom/EDep-EM_SCALE_SHOWER_ECAL)/(EM_SCALE_SHOWER_AIR-EM_SCALE_SHOWER_ECAL);
			double pi0_EMSLOP = wtslopew*EM_SLOPE_AIR*chargeratioinWT + ecalslopew*EM_SLOPE_ECAL*(1.0-chargeratioinWT);
			double pi0_EMYINT = wtintw*EM_YINT_AIR*chargeratioinWT + ecalintw*EM_YINT_ECAL*(1.0-chargeratioinWT);
			pi0utilMom = pi0_EMSLOP*EDep+pi0_EMYINT;
		}
		else
			std::cout<<"Warning!!! neither water-in nor water-out"<<std::endl;
		return pi0utilMom;
	}
		
	double CalInvariantMass(const double mom1, const float dir1[3], const double mom2, const float dir2[3])
	{
		double totE = mom1+mom2;
		double totP[3];
		for(int i=0; i<3; i++)
			totP[i] = mom1*dir1[i]+mom2*dir2[i];
		return TMath::Sqrt(std::abs(totE*totE-totP[0]*totP[0]-totP[1]*totP[1]-totP[2]*totP[2]));
	}
	double CalInvariantMass(const double mom1, const double dir1[3], const double mom2, const double dir2[3])
	{
		double totE = mom1+mom2;
		double totP[3];
		for(int i=0; i<3; i++)
			totP[i] = mom1*dir1[i]+mom2*dir2[i];
		return TMath::Sqrt(std::abs(totE*totE-totP[0]*totP[0]-totP[1]*totP[1]-totP[2]*totP[2]));
	}


	double CalPosiDiff(float posi1X, float posi1Y, float posi1Z,float posi2X, float posi2Y, float posi2Z)
	{
		float diffsquare = TMath::Power(posi1X-posi2X, 2)+TMath::Power(posi1Y-posi2Y, 2)+TMath::Power(posi1Z-posi2Z, 2);
		return TMath::Sqrt(diffsquare);
	}

	std::pair<int, int> FindMaxTwoShower(int dim[], double ScaledMom[], int startindex, int endindex)
	{
		int MaxIndex = -1; 
		double MaxValue = 0;
		int SecondMaxIndex =-1;
		double SecondMaxValue=0;
		for(int i=startindex; i<=endindex; i++)
		{
			if(dim[i]!=7)
				continue;
			if(ScaledMom[i]>SecondMaxValue)	{
				SecondMaxValue = ScaledMom[i];
				SecondMaxIndex = i;
			}
			if(ScaledMom[i]>MaxValue)
			{
				SecondMaxValue = MaxValue;
				SecondMaxIndex = MaxIndex;
				MaxValue = ScaledMom[i];
				MaxIndex = i;
			}
		}
		std::pair<int, int> maxindices = std::make_pair(MaxIndex, SecondMaxIndex);
		return maxindices;
	}

	std::pair<int, int> FindMaxTwoShower(int dim[], float ScaledMom[], float parMom[], float  parEDep[], int startindex, int endindex)
	{
		int MaxIndex = -1; 
		float MaxValue = 0;
//		double MaxValue = 0;
		int SecondMaxIndex =-1;
		float SecondMaxValue=0;
//		double SecondMaxValue=0;
		for(int i=startindex; i<=endindex; i++)
		{
			if(dim[i]!=7)
				continue;
			if(parMom[i]==0&&parEDep[i]==-999)
				continue;
			if(ScaledMom[i]>SecondMaxValue)	{
				SecondMaxValue = ScaledMom[i];
				SecondMaxIndex = i;
			}
			if(ScaledMom[i]>MaxValue)
			{
				SecondMaxValue = MaxValue;
				SecondMaxIndex = MaxIndex;
				MaxValue = ScaledMom[i];
				MaxIndex = i;
			}
		}
		std::pair<int, int> maxindices = std::make_pair(MaxIndex, SecondMaxIndex);
		return maxindices;
	}

	std::pair<int, int> FindMaxTwoShower(int dim[], double ScaledMom[], float parMom[], float  parEDep[], int startindex, int endindex)
	{
		int MaxIndex = -1; 
		double MaxValue = 0;
		int SecondMaxIndex =-1;
		double SecondMaxValue=0;
		for(int i=startindex; i<=endindex; i++)
		{
			if(dim[i]!=7)
				continue;
			if(parMom[i]==0&&parEDep[i]==-999)
				continue;

			if(ScaledMom[i]>MaxValue)
			{
				SecondMaxValue = MaxValue;
				SecondMaxIndex = MaxIndex;
				MaxValue = ScaledMom[i];
				MaxIndex = i;
			}
			else if(ScaledMom[i]>SecondMaxValue)
			{
				SecondMaxValue = ScaledMom[i];
				SecondMaxIndex = i;
			}
			/*
			if(ScaledMom[i]>SecondMaxValue)	{
				SecondMaxValue = ScaledMom[i];
				SecondMaxIndex = i;
			}
			if(ScaledMom[i]>MaxValue)
			{
				SecondMaxValue = MaxValue;
				SecondMaxIndex = MaxIndex;
				MaxValue = ScaledMom[i];
				MaxIndex = i;
			}
			*/
		}
		std::pair<int, int> maxindices = std::make_pair(MaxIndex, SecondMaxIndex);
		return maxindices;
	}
}



#endif
