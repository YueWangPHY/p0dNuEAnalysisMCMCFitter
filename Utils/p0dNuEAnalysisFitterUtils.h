#ifndef P0DNUEANALYSISFITTERUTILS_H
#define P0DNUEANALYSISFITTERUTILS_H

#include <iostream>
#include <unordered_set>
#include <unordered_map>

namespace p0dNuEMCMCFitterUtils
{

	template <typename T>
	void copyarray(T newarray[], T copyarray[], const int length=100)
	{
		for(int i=0; i<length; i++)
			newarray[i]=copyarray[i];
	}

	template <typename T>
	void copy2Darray(T newarray[][100], T copyarray[][100], const int lengthx=100)//, const int lengthy=20)
	{
	//	const int lengthx=100;
		const int lengthy=100;
		for(int i=0; i<lengthx; i++){
			for(int j=0; j<lengthy; j++){
				newarray[i][j]=copyarray[i][j];
			}
		}
	}

	template <typename T>
	void copy2Darray(T newarray[][20], T copyarray[][20], const int lengthx=100)//, const int lengthy=20)
	{
	//	const int lengthx=100;
		const int lengthy=20;
		for(int i=0; i<lengthx; i++){
			for(int j=0; j<lengthy; j++){
				newarray[i][j]=copyarray[i][j];
			}
		}
	}

	template <typename T>
	void copy2Darray(T newarray[][4], T copyarray[][4], const int lengthx=100)//, const int lengthy=20)
	{
	//	const int lengthx=100;
		const int lengthy=4;
		for(int i=0; i<lengthx; i++){
			for(int j=0; j<lengthy; j++){
				newarray[i][j]=copyarray[i][j];
			}
		}
	}

	template <typename T>
	void copy2Darray(T newarray[][3], T copyarray[][3], const int lengthx=100)//, const int lengthy=20)
	{
	//	const int lengthx=100;
		const int lengthy=3;
		for(int i=0; i<lengthx; i++){
			for(int j=0; j<lengthy; j++){
				newarray[i][j]=copyarray[i][j];
			}
		}
	}

	bool isInFVRange(float posi, int coord)//coor=0X, 1Y , 2Z
	{
		Float_t p0dFV[3][2];//xyz, minmax

		p0dFV[0][0]= -836;//    Float_t p0dXmin
		p0dFV[0][1] = 764; //   Float_t p0dXmax
		p0dFV[1][0] = -871;//   Float_t p0dYmin
		p0dFV[1][1] = 869; //   Float_t p0dYmax
		p0dFV[2][0] = -2969;//  Float_t p0dZmin
		p0dFV[2][1] = -1536;//-1264;//  Float_t p0dZmax
		if(coord<0||coord>2)
		{
			std::cerr<<"wrong coordinate"<<std::endl;
			return false;
		}
		return (posi>p0dFV[coord][0]&&posi<p0dFV[coord][1]);
	}
	bool isInOrigFVRange(float posi, int coord)//coor=0X, 1Y , 2Z
	{
		Float_t p0dFV[3][2];//xyz, minmax

		p0dFV[0][0]= -836;//    Float_t p0dXmin
		p0dFV[0][1] = 764; //   Float_t p0dXmax
		p0dFV[1][0] = -871;//   Float_t p0dYmin
		p0dFV[1][1] = 869; //   Float_t p0dYmax
		p0dFV[2][0] = -2969;//  Float_t p0dZmin
		p0dFV[2][1] = -1264;//  Float_t p0dZmax
		if(coord<0||coord>2)
		{
			std::cerr<<"wrong coordinate"<<std::endl;
			return false;
		}
		return (posi>p0dFV[coord][0]&&posi<p0dFV[coord][1]);
	}
/*
	void SettotTrueConParKin(MCEvent &mcEvent)//this method to get totkin doesn't look the same as what in binstudy. need to check whether they give the same result
	{
		double totkin = 0;
		std::unordered_set<int> primaryidused;
		std::unordered_map<int, int> paridvsidx;
		for(int i=0; i<(int)mcEvent.true_ParticleID.size(); i++)
			paridvsidx.insert({mcEvent.true_ParticleID[i], i});	
		for(int i=0; i<(int)mcEvent. true_ParticlePrimaryID.size(); i++)
		{
			if(primaryidused.find(true_ParticlePrimaryID[i])!=primaryidused.end())
				continue;
			primaryidused.insert(true_ParticlePrimaryID[i]);
			int idx = paridvsidx[true_ParticlePrimaryID[i]];
			totkin += GetKineticEnergy(true_ParticleMom[idx], true_ParticlePDG[idx]);
		}
		mcEvent.totTrueParKin = totkin;
	}

	double GetKineticEnergy(double momentum, int pdg)
	{
		std::unordered_map<int, double> pdgvsmass{{11, 0.511}, {13, 105.65}, {22, 0}, {111, 134.976}, {211, 139.57}, {2212, 938.271}};
		if(pdgvsmass.find(pdg)==pdgvsmass.end())
			return 0;
		return TMath::Sqrt(TMath::Power(momentum,2)+TMath::Power(pdgvsmass[pdg],2))-pdgvsmass[pdg];
	}
*/
}



#endif
