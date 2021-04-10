#ifndef SCALEDCONST_H
#define SCALEDCONST_H

//nue
const double EM_SCALE_SHOWER_AIR = 0.1158; // MeV/PEU
const double EM_SCALE_SHOWER_WATER = 0.1667; // MeV/PEU
const double EM_SCALE_SHOWER_ECAL = 0.1701; // MeV/PEU
double EM_SHOWER_SCALE = 0; // MeV/PEU

const double EM_SCALE_TRACK_AIR = 0.1340; // MeV/PEU
const double EM_SCALE_TRACK_WATER = 0.1847; // MeV/PEU
const double EM_SCALE_TRACK_ECAL = 0.1845; // MeV/PEU
double EM_TRACK_SCALE = 0; // MeV/PEU


//pi0
const double EM_SLOPE_AIR   = 0.121; // MeV/PEU
const double EM_YINT_AIR    = -1.3 ; // MeV
const double EM_SLOPE_WATER = 0.197; // MeV/PEU
const double EM_YINT_WATER  = -14.1; // MeV

double EM_SLOPE_P0D= 0;
double EM_YINT_P0D = 0;

const double EM_SLOPE_ECAL  = 0.262; // MeV/PEU
const double EM_YINT_ECAL   = -29.6; // MeV

#endif
