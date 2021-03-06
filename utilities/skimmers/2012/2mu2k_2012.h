//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 12 03:59:55 2018 by ROOT version 6.12/07
// from TTree X_data/X(4140) Data
// found on file: runD_split_01.root
//////////////////////////////////////////////////////////

#ifndef TwoMuTwoK_2012_h
#define TwoMuTwoK_2012_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

#include <TSystem.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TBranch.h>
//#include <TCint.h>
#include <TRandom.h>
#include <TMath.h>
#include <TDirectory.h>
#include "TEnv.h"
#include <TString.h>
#include <TSelector.h>
#include <TProof.h>
#include <TProofOutputFile.h>

#include "TPoint.h"
#include <TH1.h>
#include <TH2.h>
#include <TH2F.h>
#include <TF1.h>
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <map>



class TwoMuTwoK_2012 : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   TTree *outTree;
   // Readers to access the data (delete the ones you do not need).
   TTreeReaderArray<unsigned int> TrigRes = {fReader, "TrigRes"};
   TTreeReaderArray<string> TrigNames = {fReader, "TrigNames"};
   TTreeReaderArray<string> MatchTriggerNames = {fReader, "MatchTriggerNames"};
   TTreeReaderArray<unsigned int> L1TrigRes = {fReader, "L1TrigRes"};
   TTreeReaderValue<UInt_t> evtNum = {fReader, "evtNum"};
   TTreeReaderValue<UInt_t> runNum = {fReader, "runNum"};
   TTreeReaderValue<UInt_t> lumiNum = {fReader, "lumiNum"};
   TTreeReaderValue<UInt_t> priVtx_n = {fReader, "priVtx_n"};
   TTreeReaderValue<Float_t> priVtx_X = {fReader, "priVtx_X"};
   TTreeReaderValue<Float_t> priVtx_Y = {fReader, "priVtx_Y"};
   TTreeReaderValue<Float_t> priVtx_Z = {fReader, "priVtx_Z"};
   TTreeReaderValue<Float_t> priVtx_XE = {fReader, "priVtx_XE"};
   TTreeReaderValue<Float_t> priVtx_YE = {fReader, "priVtx_YE"};
   TTreeReaderValue<Float_t> priVtx_ZE = {fReader, "priVtx_ZE"};
   TTreeReaderValue<Float_t> priVtx_NormChi2 = {fReader, "priVtx_NormChi2"};
   TTreeReaderValue<Float_t> priVtx_Chi2 = {fReader, "priVtx_Chi2"};
   TTreeReaderValue<Float_t> priVtx_CL = {fReader, "priVtx_CL"};
   TTreeReaderValue<UInt_t> priVtx_tracks = {fReader, "priVtx_tracks"};
   TTreeReaderValue<Float_t> priVtx_tracksPtSq = {fReader, "priVtx_tracksPtSq"};
   TTreeReaderArray<float> trNotRef = {fReader, "trNotRef"};
   TTreeReaderArray<float> trRef = {fReader, "trRef"};
   TTreeReaderArray<float> trackPx = {fReader, "trackPx"};
   TTreeReaderArray<float> trackPy = {fReader, "trackPy"};
   TTreeReaderArray<float> trackPz = {fReader, "trackPz"};
   TTreeReaderArray<float> trackEnergy = {fReader, "trackEnergy"};
   TTreeReaderArray<int> trackNDF = {fReader, "trackNDF"};
   TTreeReaderArray<int> trackPhits = {fReader, "trackPhits"};
   TTreeReaderArray<int> trackShits = {fReader, "trackShits"};
   TTreeReaderArray<float> trackChi2 = {fReader, "trackChi2"};
   TTreeReaderArray<float> trackD0 = {fReader, "trackD0"};
   TTreeReaderArray<float> trackD0Err = {fReader, "trackD0Err"};
   TTreeReaderArray<float> trackCharge = {fReader, "trackCharge"};
   TTreeReaderArray<int> TrackHighPurity = {fReader, "TrackHighPurity"};
   TTreeReaderArray<int> TrackTight = {fReader, "TrackTight"};
   TTreeReaderArray<float> trackfHits = {fReader, "trackfHits"};
   TTreeReaderValue<vector<bool>> trackFirstBarrel = {fReader, "trackFirstBarrel"};
   TTreeReaderValue<vector<bool>> trackFirstEndCap = {fReader, "trackFirstEndCap"};
   TTreeReaderArray<float> trackDzVtx = {fReader, "trackDzVtx"};
   TTreeReaderArray<float> trackDxyVtx = {fReader, "trackDxyVtx"};
   TTreeReaderArray<double> tr_nsigdedx = {fReader, "tr_nsigdedx"};
   TTreeReaderArray<float> tr_dedx = {fReader, "tr_dedx"};
   TTreeReaderArray<float> tr_dedxMass = {fReader, "tr_dedxMass"};
   TTreeReaderArray<float> tr_theo = {fReader, "tr_theo"};
   TTreeReaderArray<float> tr_sigma = {fReader, "tr_sigma"};
   TTreeReaderArray<float> tr_dedx_byHits = {fReader, "tr_dedx_byHits"};
   TTreeReaderArray<float> tr_dedxErr_byHits = {fReader, "tr_dedxErr_byHits"};
   TTreeReaderArray<int> tr_saturMeas_byHits = {fReader, "tr_saturMeas_byHits"};
   TTreeReaderArray<int> tr_Meas_byHits = {fReader, "tr_Meas_byHits"};

   TTreeReaderValue<UInt_t> nMu = {fReader, "nMu"};
   TTreeReaderArray<float> muPx = {fReader, "muPx"};
   TTreeReaderArray<float> muPy = {fReader, "muPy"};
   TTreeReaderArray<float> muPz = {fReader, "muPz"};
   TTreeReaderArray<float> muCharge = {fReader, "muCharge"};
   TTreeReaderArray<float> muD0 = {fReader, "muD0"};
   TTreeReaderArray<float> muDz = {fReader, "muDz"};
   TTreeReaderArray<float> muChi2 = {fReader, "muChi2"};
   TTreeReaderArray<int> muNDF = {fReader, "muNDF"};
   TTreeReaderArray<int> muPhits = {fReader, "muPhits"};
   TTreeReaderArray<int> muShits = {fReader, "muShits"};
   TTreeReaderArray<int> muLayersTr = {fReader, "muLayersTr"};
   TTreeReaderArray<int> muLayersPix = {fReader, "muLayersPix"};
   TTreeReaderArray<float> muD0E = {fReader, "muD0E"};
   TTreeReaderArray<float> muDzVtxErr = {fReader, "muDzVtxErr"};
   TTreeReaderArray<unsigned int> muKey = {fReader, "muKey"};
   TTreeReaderValue<vector<bool>> muIsGlobal = {fReader, "muIsGlobal"};
   TTreeReaderValue<vector<bool>> muIsPF = {fReader, "muIsPF"};
   TTreeReaderArray<int> muGlMuHits = {fReader, "muGlMuHits"};
   TTreeReaderArray<float> muGlChi2 = {fReader, "muGlChi2"};
   TTreeReaderArray<int> muGlNDF = {fReader, "muGlNDF"};
   TTreeReaderArray<int> muGlMatchedStation = {fReader, "muGlMatchedStation"};
   TTreeReaderArray<float> muGlDzVtx = {fReader, "muGlDzVtx"};
   TTreeReaderArray<float> muGlDxyVtx = {fReader, "muGlDxyVtx"};
   TTreeReaderArray<int> nMatchedStations = {fReader, "nMatchedStations"};
   TTreeReaderArray<int> muType = {fReader, "muType"};
   TTreeReaderArray<int> muQual = {fReader, "muQual"};
   TTreeReaderArray<int> muTrack = {fReader, "muTrack"};
   TTreeReaderArray<int> muNOverlap = {fReader, "muNOverlap"};
   TTreeReaderArray<int> muNSharingSegWith = {fReader, "muNSharingSegWith"};
   TTreeReaderArray<float> mufHits = {fReader, "mufHits"};
   TTreeReaderValue<vector<bool>> muFirstBarrel = {fReader, "muFirstBarrel"};
   TTreeReaderValue<vector<bool>> muFirstEndCap = {fReader, "muFirstEndCap"};
   TTreeReaderArray<float> muDzVtx = {fReader, "muDzVtx"};
   TTreeReaderArray<float> muDxyVtx = {fReader, "muDxyVtx"};

   TTreeReaderValue<UInt_t> nMuMu = {fReader, "nMuMu"};
   TTreeReaderArray<float> MuMuMass = {fReader, "MuMuMass"};
   TTreeReaderArray<float> MuMuPx = {fReader, "MuMuPx"};
   TTreeReaderArray<float> MuMuPy = {fReader, "MuMuPy"};
   TTreeReaderArray<float> MuMuPz = {fReader, "MuMuPz"};
   TTreeReaderArray<float> MuMuVtx_CL = {fReader, "MuMuVtx_CL"};
   TTreeReaderArray<float> MuMuVtx_Chi2 = {fReader, "MuMuVtx_Chi2"};
   TTreeReaderArray<float> MuMuDecayVtx_X = {fReader, "MuMuDecayVtx_X"};
   TTreeReaderArray<float> MuMuDecayVtx_Y = {fReader, "MuMuDecayVtx_Y"};
   TTreeReaderArray<float> MuMuDecayVtx_Z = {fReader, "MuMuDecayVtx_Z"};
   TTreeReaderArray<float> MuMuDecayVtx_XE = {fReader, "MuMuDecayVtx_XE"};
   TTreeReaderArray<float> MuMuDecayVtx_YE = {fReader, "MuMuDecayVtx_YE"};
   TTreeReaderArray<float> MuMuDecayVtx_ZE = {fReader, "MuMuDecayVtx_ZE"};
   TTreeReaderArray<int> mu1Idx = {fReader, "mu1Idx"};
   TTreeReaderArray<int> mu2Idx = {fReader, "mu2Idx"};
   TTreeReaderArray<float> mu1Px_MuMu = {fReader, "mu1Px_MuMu"};
   TTreeReaderArray<float> mu1Py_MuMu = {fReader, "mu1Py_MuMu"};
   TTreeReaderArray<float> mu1Pz_MuMu = {fReader, "mu1Pz_MuMu"};
   TTreeReaderArray<float> mu1Chi2_MuMu = {fReader, "mu1Chi2_MuMu"};
   TTreeReaderArray<int> mu1NDF_MuMu = {fReader, "mu1NDF_MuMu"};
   TTreeReaderArray<float> mu2Px_MuMu = {fReader, "mu2Px_MuMu"};
   TTreeReaderArray<float> mu2Py_MuMu = {fReader, "mu2Py_MuMu"};
   TTreeReaderArray<float> mu2Pz_MuMu = {fReader, "mu2Pz_MuMu"};
   TTreeReaderArray<float> mu2Chi2_MuMu = {fReader, "mu2Chi2_MuMu"};
   TTreeReaderArray<int> mu2NDF_MuMu = {fReader, "mu2NDF_MuMu"};
   TTreeReaderArray<int> MuMuType = {fReader, "MuMuType"};
   TTreeReaderValue<vector<bool>> MuMuMuonTrigMatch = {fReader, "MuMuMuonTrigMatch"};
   TTreeReaderArray<int> PriVtxMuMuCorr_n = {fReader, "PriVtxMuMuCorr_n"};
   TTreeReaderArray<float> PriVtxMuMuCorr_X = {fReader, "PriVtxMuMuCorr_X"};
   TTreeReaderArray<float> PriVtxMuMuCorr_Y = {fReader, "PriVtxMuMuCorr_Y"};
   TTreeReaderArray<float> PriVtxMuMuCorr_Z = {fReader, "PriVtxMuMuCorr_Z"};
   TTreeReaderArray<double> PriVtxMuMuCorr_EX = {fReader, "PriVtxMuMuCorr_EX"};
   TTreeReaderArray<double> PriVtxMuMuCorr_EY = {fReader, "PriVtxMuMuCorr_EY"};
   TTreeReaderArray<double> PriVtxMuMuCorr_EZ = {fReader, "PriVtxMuMuCorr_EZ"};
   TTreeReaderArray<float> PriVtxMuMuCorr_Chi2 = {fReader, "PriVtxMuMuCorr_Chi2"};
   TTreeReaderArray<float> PriVtxMuMuCorr_CL = {fReader, "PriVtxMuMuCorr_CL"};
   TTreeReaderArray<int> PriVtxMuMuCorr_tracks = {fReader, "PriVtxMuMuCorr_tracks"};
   TTreeReaderArray<int> nTrk_afterMuMu = {fReader, "nTrk_afterMuMu"};
   TTreeReaderValue<UInt_t> nKK = {fReader, "nKK"};
   TTreeReaderArray<float> KKMass = {fReader, "KKMass"};
   TTreeReaderArray<float> KKPx = {fReader, "KKPx"};
   TTreeReaderArray<float> KKPy = {fReader, "KKPy"};
   TTreeReaderArray<float> KKPz = {fReader, "KKPz"};
   TTreeReaderArray<float> KKVtx_CL = {fReader, "KKVtx_CL"};
   TTreeReaderArray<float> KKVtx_Chi2 = {fReader, "KKVtx_Chi2"};
   TTreeReaderArray<float> KKDecayVtx_X = {fReader, "KKDecayVtx_X"};
   TTreeReaderArray<float> KKDecayVtx_Y = {fReader, "KKDecayVtx_Y"};
   TTreeReaderArray<float> KKDecayVtx_Z = {fReader, "KKDecayVtx_Z"};
   TTreeReaderArray<float> KKDecayVtx_XE = {fReader, "KKDecayVtx_XE"};
   TTreeReaderArray<float> KKDecayVtx_YE = {fReader, "KKDecayVtx_YE"};
   TTreeReaderArray<float> KKDecayVtx_ZE = {fReader, "KKDecayVtx_ZE"};

   TTreeReaderArray<int> ka1Idx = {fReader, "ka1Idx"};
   TTreeReaderArray<int> ka2Idx = {fReader, "ka2Idx"};
   TTreeReaderArray<float> ka1Px_KK = {fReader, "ka1Px_KK"};
   TTreeReaderArray<float> ka1Py_KK = {fReader, "ka1Py_KK"};
   TTreeReaderArray<float> ka1Pz_KK = {fReader, "ka1Pz_KK"};
   TTreeReaderArray<float> ka1Chi2_KK = {fReader, "ka1Chi2_KK"};
   TTreeReaderArray<int> ka1NDF_KK = {fReader, "ka1NDF_KK"};
   TTreeReaderArray<float> ka2Px_KK = {fReader, "ka2Px_KK"};
   TTreeReaderArray<float> ka2Py_KK = {fReader, "ka2Py_KK"};
   TTreeReaderArray<float> ka2Pz_KK = {fReader, "ka2Pz_KK"};
   TTreeReaderArray<float> ka2Chi2_KK = {fReader, "ka2Chi2_KK"};
   TTreeReaderArray<int> ka2NDF_KK = {fReader, "ka2NDF_KK"};
   TTreeReaderArray<float> DR_MuMu_K1 = {fReader, "DR_MuMu_K1"};
   TTreeReaderArray<float> DR_MuMu_K2 = {fReader, "DR_MuMu_K2"};
   TTreeReaderArray<float> DR_MuMuKK_K1 = {fReader, "DR_MuMuKK_K1"};
   TTreeReaderArray<float> DR_MuMuKK_K2 = {fReader, "DR_MuMuKK_K2"};
   TTreeReaderValue<UInt_t> nX = {fReader, "nX"};
   TTreeReaderValue<UInt_t> nX_pre0 = {fReader, "nX_pre0"};
   TTreeReaderValue<UInt_t> nX_pre1 = {fReader, "nX_pre1"};
   TTreeReaderValue<UInt_t> nX_pre2 = {fReader, "nX_pre2"};
   TTreeReaderValue<UInt_t> nX_pre3 = {fReader, "nX_pre3"};
   TTreeReaderValue<UInt_t> nX_pre4 = {fReader, "nX_pre4"};
   TTreeReaderValue<UInt_t> nX_pre5 = {fReader, "nX_pre5"};
   TTreeReaderValue<UInt_t> nX_pre6 = {fReader, "nX_pre6"};
   TTreeReaderValue<UInt_t> nX_pre7 = {fReader, "nX_pre7"};
   TTreeReaderValue<UInt_t> nX_pre8 = {fReader, "nX_pre8"};
   TTreeReaderValue<UInt_t> nX_pre9 = {fReader, "nX_pre9"};
   TTreeReaderValue<UInt_t> nX_pre10 = {fReader, "nX_pre10"};
   TTreeReaderValue<UInt_t> nX_pre11 = {fReader, "nX_pre11"};
   TTreeReaderValue<UInt_t> nX_pre12 = {fReader, "nX_pre12"};
   TTreeReaderValue<UInt_t> nX_pre13 = {fReader, "nX_pre13"};
   TTreeReaderValue<UInt_t> nX_pre14 = {fReader, "nX_pre14"};
   TTreeReaderValue<UInt_t> nX_pre15 = {fReader, "nX_pre15"};

   TTreeReaderArray<float> XMass = {fReader, "XMass"};
   TTreeReaderArray<float> XPx = {fReader, "XPx"};
   TTreeReaderArray<float> XPy = {fReader, "XPy"};
   TTreeReaderArray<float> XPz = {fReader, "XPz"};
   TTreeReaderArray<double> XPxE = {fReader, "XPxE"};
   TTreeReaderArray<double> XPyE = {fReader, "XPyE"};
   TTreeReaderArray<double> XPzE = {fReader, "XPzE"};
   TTreeReaderArray<float> XVtx_CL = {fReader, "XVtx_CL"};
   TTreeReaderArray<float> XVtx_Chi2 = {fReader, "XVtx_Chi2"};
   TTreeReaderArray<float> XDecayVtx_X = {fReader, "XDecayVtx_X"};
   TTreeReaderArray<float> XDecayVtx_Y = {fReader, "XDecayVtx_Y"};
   TTreeReaderArray<float> XDecayVtx_Z = {fReader, "XDecayVtx_Z"};
   TTreeReaderArray<double> XDecayVtx_XE = {fReader, "XDecayVtx_XE"};
   TTreeReaderArray<double> XDecayVtx_YE = {fReader, "XDecayVtx_YE"};
   TTreeReaderArray<double> XDecayVtx_ZE = {fReader, "XDecayVtx_ZE"};
   TTreeReaderArray<double> XCosAlphaBS = {fReader, "XCosAlphaBS"};
   TTreeReaderArray<double> XCosAlpha3DBS = {fReader, "XCosAlpha3DBS"};
   TTreeReaderArray<double> XCTauBS = {fReader, "XCTauBS"};
   TTreeReaderArray<double> XCTauBSE = {fReader, "XCTauBSE"};
   TTreeReaderArray<double> XLxyBS = {fReader, "XLxyBS"};
   TTreeReaderArray<double> XLxyBSE = {fReader, "XLxyBSE"};
   TTreeReaderArray<double> XLxyzBS = {fReader, "XLxyzBS"};
   TTreeReaderArray<double> XLxyzBSE = {fReader, "XLxyzBSE"};
   TTreeReaderArray<double> XCosAlphaPV = {fReader, "XCosAlphaPV"};
   TTreeReaderArray<double> XCosAlpha3DPV = {fReader, "XCosAlpha3DPV"};
   TTreeReaderArray<double> XCTauPV = {fReader, "XCTauPV"};
   TTreeReaderArray<double> XCTauPVE = {fReader, "XCTauPVE"};
   TTreeReaderArray<double> XLxyPV = {fReader, "XLxyPV"};
   TTreeReaderArray<double> XLxyPVE = {fReader, "XLxyPVE"};
   TTreeReaderArray<double> XLxyzPV = {fReader, "XLxyzPV"};
   TTreeReaderArray<double> XLxyzPVE = {fReader, "XLxyzPVE"};
   TTreeReaderArray<int> PriVtx_XCosAlpha_n = {fReader, "PriVtx_XCosAlpha_n"};
   TTreeReaderArray<float> PriVtx_XCosAlpha_X = {fReader, "PriVtx_XCosAlpha_X"};
   TTreeReaderArray<float> PriVtx_XCosAlpha_Y = {fReader, "PriVtx_XCosAlpha_Y"};
   TTreeReaderArray<float> PriVtx_XCosAlpha_Z = {fReader, "PriVtx_XCosAlpha_Z"};
   TTreeReaderArray<double> PriVtx_XCosAlpha_EX = {fReader, "PriVtx_XCosAlpha_EX"};
   TTreeReaderArray<double> PriVtx_XCosAlpha_EY = {fReader, "PriVtx_XCosAlpha_EY"};
   TTreeReaderArray<double> PriVtx_XCosAlpha_EZ = {fReader, "PriVtx_XCosAlpha_EZ"};
   TTreeReaderArray<float> PriVtx_XCosAlpha_Chi2 = {fReader, "PriVtx_XCosAlpha_Chi2"};
   TTreeReaderArray<float> PriVtx_XCosAlpha_CL = {fReader, "PriVtx_XCosAlpha_CL"};
   TTreeReaderArray<int> PriVtx_XCosAlpha_tracks = {fReader, "PriVtx_XCosAlpha_tracks"};
   TTreeReaderArray<double> XCosAlphaPVCosAlpha = {fReader, "XCosAlphaPVCosAlpha"};
   TTreeReaderArray<double> XCosAlpha3DPVCosAlpha = {fReader, "XCosAlpha3DPVCosAlpha"};
   TTreeReaderArray<double> XCTauPVCosAlpha = {fReader, "XCTauPVCosAlpha"};
   TTreeReaderArray<double> XCTauPVCosAlphaE = {fReader, "XCTauPVCosAlphaE"};
   TTreeReaderArray<double> XLxyPVCosAlpha = {fReader, "XLxyPVCosAlpha"};
   TTreeReaderArray<double> XLxyPVCosAlphaE = {fReader, "XLxyPVCosAlphaE"};
   TTreeReaderArray<double> XLxyzPVCosAlpha = {fReader, "XLxyzPVCosAlpha"};
   TTreeReaderArray<double> XLxyzPVCosAlphaE = {fReader, "XLxyzPVCosAlphaE"};
   TTreeReaderArray<int> PriVtx_XCosAlpha3D_n = {fReader, "PriVtx_XCosAlpha3D_n"};
   TTreeReaderArray<float> PriVtx_XCosAlpha3D_X = {fReader, "PriVtx_XCosAlpha3D_X"};
   TTreeReaderArray<float> PriVtx_XCosAlpha3D_Y = {fReader, "PriVtx_XCosAlpha3D_Y"};
   TTreeReaderArray<float> PriVtx_XCosAlpha3D_Z = {fReader, "PriVtx_XCosAlpha3D_Z"};
   TTreeReaderArray<double> PriVtx_XCosAlpha3D_EX = {fReader, "PriVtx_XCosAlpha3D_EX"};
   TTreeReaderArray<double> PriVtx_XCosAlpha3D_EY = {fReader, "PriVtx_XCosAlpha3D_EY"};
   TTreeReaderArray<double> PriVtx_XCosAlpha3D_EZ = {fReader, "PriVtx_XCosAlpha3D_EZ"};
   TTreeReaderArray<float> PriVtx_XCosAlpha3D_Chi2 = {fReader, "PriVtx_XCosAlpha3D_Chi2"};
   TTreeReaderArray<float> PriVtx_XCosAlpha3D_CL = {fReader, "PriVtx_XCosAlpha3D_CL"};
   TTreeReaderArray<int> PriVtx_XCosAlpha3D_tracks = {fReader, "PriVtx_XCosAlpha3D_tracks"};
   TTreeReaderArray<double> XCosAlphaPVCosAlpha3D = {fReader, "XCosAlphaPVCosAlpha3D"};
   TTreeReaderArray<double> XCosAlpha3DPVCosAlpha3D = {fReader, "XCosAlpha3DPVCosAlpha3D"};
   TTreeReaderArray<double> XCTauPVCosAlpha3D = {fReader, "XCTauPVCosAlpha3D"};
   TTreeReaderArray<double> XCTauPVCosAlpha3DE = {fReader, "XCTauPVCosAlpha3DE"};
   TTreeReaderArray<double> XLxyPVCosAlpha3D = {fReader, "XLxyPVCosAlpha3D"};
   TTreeReaderArray<double> XLxyPVCosAlpha3DE = {fReader, "XLxyPVCosAlpha3DE"};
   TTreeReaderArray<double> XLxyzPVCosAlpha3D = {fReader, "XLxyzPVCosAlpha3D"};
   TTreeReaderArray<double> XLxyzPVCosAlpha3DE = {fReader, "XLxyzPVCosAlpha3DE"};
   TTreeReaderArray<float> XLessPV_tracksPtSq = {fReader, "XLessPV_tracksPtSq"};
   TTreeReaderArray<float> XLessPV_4tracksPtSq = {fReader, "XLessPV_4tracksPtSq"};
   TTreeReaderArray<int> PriVtxXLess_n = {fReader, "PriVtxXLess_n"};
   TTreeReaderArray<float> PriVtxXLess_X = {fReader, "PriVtxXLess_X"};
   TTreeReaderArray<float> PriVtxXLess_Y = {fReader, "PriVtxXLess_Y"};
   TTreeReaderArray<float> PriVtxXLess_Z = {fReader, "PriVtxXLess_Z"};
   TTreeReaderArray<double> PriVtxXLess_EX = {fReader, "PriVtxXLess_EX"};
   TTreeReaderArray<double> PriVtxXLess_EY = {fReader, "PriVtxXLess_EY"};
   TTreeReaderArray<double> PriVtxXLess_EZ = {fReader, "PriVtxXLess_EZ"};
   TTreeReaderArray<float> PriVtxXLess_Chi2 = {fReader, "PriVtxXLess_Chi2"};
   TTreeReaderArray<float> PriVtxXLess_CL = {fReader, "PriVtxXLess_CL"};
   TTreeReaderArray<int> PriVtxXLess_tracks = {fReader, "PriVtxXLess_tracks"};
   TTreeReaderArray<double> XCosAlphaXLessPV = {fReader, "XCosAlphaXLessPV"};
   TTreeReaderArray<double> XCosAlpha3DXLessPV = {fReader, "XCosAlpha3DXLessPV"};
   TTreeReaderArray<double> XCTauXLessPV = {fReader, "XCTauXLessPV"};
   TTreeReaderArray<double> XCTauXLessPVE = {fReader, "XCTauXLessPVE"};
   TTreeReaderArray<double> XLxyXLessPV = {fReader, "XLxyXLessPV"};
   TTreeReaderArray<double> XLxyXLessPVE = {fReader, "XLxyXLessPVE"};
   TTreeReaderArray<double> XLxyzXLessPV = {fReader, "XLxyzXLessPV"};
   TTreeReaderArray<double> XLxyzXLessPVE = {fReader, "XLxyzXLessPVE"};
   TTreeReaderArray<int> PriVtxXLess_XCosAlpha_n = {fReader, "PriVtxXLess_XCosAlpha_n"};
   TTreeReaderArray<float> PriVtxXLess_XCosAlpha_X = {fReader, "PriVtxXLess_XCosAlpha_X"};
   TTreeReaderArray<float> PriVtxXLess_XCosAlpha_Y = {fReader, "PriVtxXLess_XCosAlpha_Y"};
   TTreeReaderArray<float> PriVtxXLess_XCosAlpha_Z = {fReader, "PriVtxXLess_XCosAlpha_Z"};
   TTreeReaderArray<double> PriVtxXLess_XCosAlpha_EX = {fReader, "PriVtxXLess_XCosAlpha_EX"};
   TTreeReaderArray<double> PriVtxXLess_XCosAlpha_EY = {fReader, "PriVtxXLess_XCosAlpha_EY"};
   TTreeReaderArray<double> PriVtxXLess_XCosAlpha_EZ = {fReader, "PriVtxXLess_XCosAlpha_EZ"};
   TTreeReaderArray<float> PriVtxXLess_XCosAlpha_Chi2 = {fReader, "PriVtxXLess_XCosAlpha_Chi2"};
   TTreeReaderArray<float> PriVtxXLess_XCosAlpha_CL = {fReader, "PriVtxXLess_XCosAlpha_CL"};
   TTreeReaderArray<int> PriVtxXLess_XCosAlpha_tracks = {fReader, "PriVtxXLess_XCosAlpha_tracks"};
   TTreeReaderArray<double> XCosAlphaXLessPVCosAlpha = {fReader, "XCosAlphaXLessPVCosAlpha"};
   TTreeReaderArray<double> XCosAlpha3DXLessPVCosAlpha = {fReader, "XCosAlpha3DXLessPVCosAlpha"};
   TTreeReaderArray<double> XCTauXLessPVCosAlpha = {fReader, "XCTauXLessPVCosAlpha"};
   TTreeReaderArray<double> XCTauXLessPVCosAlphaE = {fReader, "XCTauXLessPVCosAlphaE"};
   TTreeReaderArray<double> XLxyXLessPVCosAlpha = {fReader, "XLxyXLessPVCosAlpha"};
   TTreeReaderArray<double> XLxyXLessPVCosAlphaE = {fReader, "XLxyXLessPVCosAlphaE"};
   TTreeReaderArray<double> XLxyzXLessPVCosAlpha = {fReader, "XLxyzXLessPVCosAlpha"};
   TTreeReaderArray<double> XLxyzXLessPVCosAlphaE = {fReader, "XLxyzXLessPVCosAlphaE"};
   TTreeReaderArray<int> PriVtxXLess_XCosAlpha3D_n = {fReader, "PriVtxXLess_XCosAlpha3D_n"};
   TTreeReaderArray<float> PriVtxXLess_XCosAlpha3D_X = {fReader, "PriVtxXLess_XCosAlpha3D_X"};
   TTreeReaderArray<float> PriVtxXLess_XCosAlpha3D_Y = {fReader, "PriVtxXLess_XCosAlpha3D_Y"};
   TTreeReaderArray<float> PriVtxXLess_XCosAlpha3D_Z = {fReader, "PriVtxXLess_XCosAlpha3D_Z"};
   TTreeReaderArray<double> PriVtxXLess_XCosAlpha3D_EX = {fReader, "PriVtxXLess_XCosAlpha3D_EX"};
   TTreeReaderArray<double> PriVtxXLess_XCosAlpha3D_EY = {fReader, "PriVtxXLess_XCosAlpha3D_EY"};
   TTreeReaderArray<double> PriVtxXLess_XCosAlpha3D_EZ = {fReader, "PriVtxXLess_XCosAlpha3D_EZ"};
   TTreeReaderArray<float> PriVtxXLess_XCosAlpha3D_Chi2 = {fReader, "PriVtxXLess_XCosAlpha3D_Chi2"};
   TTreeReaderArray<float> PriVtxXLess_XCosAlpha3D_CL = {fReader, "PriVtxXLess_XCosAlpha3D_CL"};
   TTreeReaderArray<int> PriVtxXLess_XCosAlpha3D_tracks = {fReader, "PriVtxXLess_XCosAlpha3D_tracks"};
   TTreeReaderArray<double> XCosAlphaXLessPVCosAlpha3D = {fReader, "XCosAlphaXLessPVCosAlpha3D"};
   TTreeReaderArray<double> XCosAlpha3DXLessPVCosAlpha3D = {fReader, "XCosAlpha3DXLessPVCosAlpha3D"};
   TTreeReaderArray<double> XCTauXLessPVCosAlpha3D = {fReader, "XCTauXLessPVCosAlpha3D"};
   TTreeReaderArray<double> XCTauXLessPVCosAlpha3DE = {fReader, "XCTauXLessPVCosAlpha3DE"};
   TTreeReaderArray<double> XLxyXLessPVCosAlpha3D = {fReader, "XLxyXLessPVCosAlpha3D"};
   TTreeReaderArray<double> XLxyXLessPVCosAlpha3DE = {fReader, "XLxyXLessPVCosAlpha3DE"};
   TTreeReaderArray<double> XLxyzXLessPVCosAlpha3D = {fReader, "XLxyzXLessPVCosAlpha3D"};
   TTreeReaderArray<double> XLxyzXLessPVCosAlpha3DE = {fReader, "XLxyzXLessPVCosAlpha3DE"};
   TTreeReaderArray<int> PriVtxXCorr_n = {fReader, "PriVtxXCorr_n"};
   TTreeReaderArray<float> PriVtxXCorr_X = {fReader, "PriVtxXCorr_X"};
   TTreeReaderArray<float> PriVtxXCorr_Y = {fReader, "PriVtxXCorr_Y"};
   TTreeReaderArray<float> PriVtxXCorr_Z = {fReader, "PriVtxXCorr_Z"};
   TTreeReaderArray<double> PriVtxXCorr_EX = {fReader, "PriVtxXCorr_EX"};
   TTreeReaderArray<double> PriVtxXCorr_EY = {fReader, "PriVtxXCorr_EY"};
   TTreeReaderArray<double> PriVtxXCorr_EZ = {fReader, "PriVtxXCorr_EZ"};
   TTreeReaderArray<float> PriVtxXCorr_Chi2 = {fReader, "PriVtxXCorr_Chi2"};
   TTreeReaderArray<float> PriVtxXCorr_CL = {fReader, "PriVtxXCorr_CL"};
   TTreeReaderArray<int> PriVtxXCorr_tracks = {fReader, "PriVtxXCorr_tracks"};
   TTreeReaderArray<double> XCosAlphaPVX = {fReader, "XCosAlphaPVX"};
   TTreeReaderArray<double> XCTauPVX = {fReader, "XCTauPVX"};
   TTreeReaderArray<double> XCTauPVXE = {fReader, "XCTauPVXE"};
   TTreeReaderArray<double> XLxyPVX = {fReader, "XLxyPVX"};
   TTreeReaderArray<double> XLxyzPVX = {fReader, "XLxyzPVX"};
   TTreeReaderArray<float> XCTauPVX_3D = {fReader, "XCTauPVX_3D"};
   TTreeReaderArray<float> XCTauPVX_3D_err = {fReader, "XCTauPVX_3D_err"};
   TTreeReaderArray<float> kaon1_dxy_PV = {fReader, "kaon1_dxy_PV"};
   TTreeReaderArray<float> kaon1_dz_PV = {fReader, "kaon1_dz_PV"};
   TTreeReaderArray<float> kaon2_dxy_PV = {fReader, "kaon2_dxy_PV"};
   TTreeReaderArray<float> kaon2_dz_PV = {fReader, "kaon2_dz_PV"};
   TTreeReaderArray<float> kaon1_dxy_BS = {fReader, "kaon1_dxy_BS"};
   TTreeReaderArray<float> kaon1_dz_BS = {fReader, "kaon1_dz_BS"};
   TTreeReaderArray<float> kaon2_dxy_BS = {fReader, "kaon2_dxy_BS"};
   TTreeReaderArray<float> kaon2_dz_BS = {fReader, "kaon2_dz_BS"};
   TTreeReaderArray<float> kaon1_dxy_XLessPV = {fReader, "kaon1_dxy_XLessPV"};
   TTreeReaderArray<float> kaon1_dz_XLessPV = {fReader, "kaon1_dz_XLessPV"};
   TTreeReaderArray<float> kaon2_dxy_XLessPV = {fReader, "kaon2_dxy_XLessPV"};
   TTreeReaderArray<float> kaon2_dz_XLessPV = {fReader, "kaon2_dz_XLessPV"};
   TTreeReaderArray<float> kaon1_dxyE = {fReader, "kaon1_dxyE"};
   TTreeReaderArray<float> kaon1_dzE = {fReader, "kaon1_dzE"};
   TTreeReaderArray<float> kaon2_dxyE = {fReader, "kaon2_dxyE"};
   TTreeReaderArray<float> kaon2_dzE = {fReader, "kaon2_dzE"};
   TTreeReaderArray<int> XMuMuIdx = {fReader, "XMuMuIdx"};
   TTreeReaderArray<int> XKaon1Idx = {fReader, "XKaon1Idx"};
   TTreeReaderArray<int> XKaon2Idx = {fReader, "XKaon2Idx"};
   TTreeReaderValue<vector<bool>> Kaon1FromPV = {fReader, "Kaon1FromPV"};
   TTreeReaderValue<vector<bool>> Kaon2FromPV = {fReader, "Kaon2FromPV"};
   TTreeReaderArray<float> Muon1Px_MuMuKK = {fReader, "Muon1Px_MuMuKK"};
   TTreeReaderArray<float> Muon1Py_MuMuKK = {fReader, "Muon1Py_MuMuKK"};
   TTreeReaderArray<float> Muon1Pz_MuMuKK = {fReader, "Muon1Pz_MuMuKK"};
   TTreeReaderArray<float> Muon1E_MuMuKK = {fReader, "Muon1E_MuMuKK"};
   TTreeReaderArray<float> Muon2Px_MuMuKK = {fReader, "Muon2Px_MuMuKK"};
   TTreeReaderArray<float> Muon2Py_MuMuKK = {fReader, "Muon2Py_MuMuKK"};
   TTreeReaderArray<float> Muon2Pz_MuMuKK = {fReader, "Muon2Pz_MuMuKK"};
   TTreeReaderArray<float> Muon2E_MuMuKK = {fReader, "Muon2E_MuMuKK"};
   TTreeReaderArray<float> Kaon1Px_MuMuKK = {fReader, "Kaon1Px_MuMuKK"};
   TTreeReaderArray<float> Kaon1Py_MuMuKK = {fReader, "Kaon1Py_MuMuKK"};
   TTreeReaderArray<float> Kaon1Pz_MuMuKK = {fReader, "Kaon1Pz_MuMuKK"};
   TTreeReaderArray<float> Kaon1E_MuMuKK = {fReader, "Kaon1E_MuMuKK"};
   TTreeReaderArray<double> kaon1_nsigdedx = {fReader, "kaon1_nsigdedx"};
   TTreeReaderArray<float> kaon1_dedx = {fReader, "kaon1_dedx"};
   TTreeReaderArray<float> kaon1_dedxMass = {fReader, "kaon1_dedxMass"};
   TTreeReaderArray<float> kaon1_theo = {fReader, "kaon1_theo"};
   TTreeReaderArray<float> kaon1_sigma = {fReader, "kaon1_sigma"};
   TTreeReaderArray<float> kaon1_dedx_byHits = {fReader, "kaon1_dedx_byHits"};
   TTreeReaderArray<float> kaon1_dedxErr_byHits = {fReader, "kaon1_dedxErr_byHits"};
   TTreeReaderArray<int> kaon1_saturMeas_byHits = {fReader, "kaon1_saturMeas_byHits"};
   TTreeReaderArray<int> kaon1_Meas_byHits = {fReader, "kaon1_Meas_byHits"};
   TTreeReaderArray<float> Kaon2Px_MuMuKK = {fReader, "Kaon2Px_MuMuKK"};
   TTreeReaderArray<float> Kaon2Py_MuMuKK = {fReader, "Kaon2Py_MuMuKK"};
   TTreeReaderArray<float> Kaon2Pz_MuMuKK = {fReader, "Kaon2Pz_MuMuKK"};
   TTreeReaderArray<float> Kaon2E_MuMuKK = {fReader, "Kaon2E_MuMuKK"};
   TTreeReaderArray<double> kaon2_nsigdedx = {fReader, "kaon2_nsigdedx"};
   TTreeReaderArray<float> kaon2_dedx = {fReader, "kaon2_dedx"};
   TTreeReaderArray<float> kaon2_dedxMass = {fReader, "kaon2_dedxMass"};
   TTreeReaderArray<float> kaon2_theo = {fReader, "kaon2_theo"};
   TTreeReaderArray<float> kaon2_sigma = {fReader, "kaon2_sigma"};
   TTreeReaderArray<float> kaon2_dedx_byHits = {fReader, "kaon2_dedx_byHits"};
   TTreeReaderArray<float> kaon2_dedxErr_byHits = {fReader, "kaon2_dedxErr_byHits"};
   TTreeReaderArray<int> kaon2_saturMeas_byHits = {fReader, "kaon2_saturMeas_byHits"};
   TTreeReaderArray<int> kaon2_Meas_byHits = {fReader, "kaon2_Meas_byHits"};



   Float_t out_TrigRes, out_TrigNames, out_MatchTriggerNames, out_L1TrigRes, out_evtNum;
Float_t out_runNum, out_lumiNum, out_priVtx_n, out_priVtx_X, out_priVtx_Y;
Float_t out_priVtx_Z, out_priVtx_XE, out_priVtx_YE, out_priVtx_ZE, out_priVtx_NormChi2;
Float_t out_priVtx_Chi2, out_priVtx_CL, out_priVtx_tracks, out_priVtx_tracksPtSq, out_trNotRef;
Float_t out_trRef, out_trackPx, out_trackPy, out_trackPz, out_trackEnergy;
Float_t out_trackNDF, out_trackPhits, out_trackShits, out_trackChi2, out_trackD0;
Float_t out_trackD0Err, out_trackCharge, out_TrackHighPurity, out_TrackTight, out_trackfHits;
Float_t out_trackFirstBarrel, out_trackFirstEndCap, out_trackDzVtx, out_trackDxyVtx, out_tr_nsigdedx;
Float_t out_tr_dedx, out_tr_dedxMass, out_tr_theo, out_tr_sigma, out_tr_dedx_byHits;
Float_t out_tr_dedxErr_byHits, out_tr_saturMeas_byHits, out_tr_Meas_byHits, out_nMu, out_muPx;
Float_t out_muPy, out_muPz, out_muCharge, out_muD0, out_muDz;
Float_t out_muChi2, out_muNDF, out_muPhits, out_muShits, out_muLayersTr;
Float_t out_muLayersPix, out_muD0E, out_muDzVtxErr, out_muKey, out_muIsGlobal;
Float_t out_muIsPF, out_muGlMuHits, out_muGlChi2, out_muGlNDF, out_muGlMatchedStation;
Float_t out_muGlDzVtx, out_muGlDxyVtx, out_nMatchedStations, out_muType, out_muQual;
Float_t out_muTrack, out_muNOverlap, out_muNSharingSegWith, out_mufHits, out_muFirstBarrel;
Float_t out_muFirstEndCap, out_muDzVtx, out_muDxyVtx, out_nMuMu, out_MuMuMass;
Float_t out_MuMuPx, out_MuMuPy, out_MuMuPz, out_MuMuVtx_CL, out_MuMuVtx_Chi2;
Float_t out_MuMuDecayVtx_X, out_MuMuDecayVtx_Y, out_MuMuDecayVtx_Z, out_MuMuDecayVtx_XE, out_MuMuDecayVtx_YE;
Float_t out_MuMuDecayVtx_ZE, out_mu1Idx, out_mu2Idx, out_mu1Px_MuMu, out_mu1Py_MuMu;
Float_t out_mu1Pz_MuMu, out_mu1Chi2_MuMu, out_mu1NDF_MuMu, out_mu2Px_MuMu, out_mu2Py_MuMu;
Float_t out_mu2Pz_MuMu, out_mu2Chi2_MuMu, out_mu2NDF_MuMu, out_MuMuType, out_MuMuMuonTrigMatch;
Float_t out_PriVtxMuMuCorr_n, out_PriVtxMuMuCorr_X, out_PriVtxMuMuCorr_Y, out_PriVtxMuMuCorr_Z, out_PriVtxMuMuCorr_EX;
Float_t out_PriVtxMuMuCorr_EY, out_PriVtxMuMuCorr_EZ, out_PriVtxMuMuCorr_Chi2, out_PriVtxMuMuCorr_CL, out_PriVtxMuMuCorr_tracks;
Float_t out_nTrk_afterMuMu, out_nKK, out_KKMass, out_KKPx, out_KKPy;
Float_t out_KKPz, out_KKVtx_CL, out_KKVtx_Chi2, out_KKDecayVtx_X, out_KKDecayVtx_Y;
Float_t out_KKDecayVtx_Z, out_KKDecayVtx_XE, out_KKDecayVtx_YE, out_KKDecayVtx_ZE, out_ka1Idx;
Float_t out_ka2Idx, out_ka1Px_KK, out_ka1Py_KK, out_ka1Pz_KK, out_ka1Chi2_KK;
Float_t out_ka1NDF_KK, out_ka2Px_KK, out_ka2Py_KK, out_ka2Pz_KK, out_ka2Chi2_KK;
Float_t out_ka2NDF_KK, out_DR_MuMu_K1, out_DR_MuMu_K2, out_DR_MuMuKK_K1, out_DR_MuMuKK_K2;
Float_t out_nX, out_nX_pre0, out_nX_pre1, out_nX_pre2, out_nX_pre3;
Float_t out_nX_pre4, out_nX_pre5, out_nX_pre6, out_nX_pre7, out_nX_pre8;
Float_t out_nX_pre9, out_nX_pre10, out_nX_pre11, out_nX_pre12, out_nX_pre13;
Float_t out_nX_pre14, out_nX_pre15;
Float_t out_XMass, out_XPx, out_XPy;
Float_t out_XPz, out_XPxE, out_XPyE, out_XPzE, out_XVtx_CL;
Float_t out_XVtx_Chi2, out_XDecayVtx_X, out_XDecayVtx_Y, out_XDecayVtx_Z, out_XDecayVtx_XE;
Float_t out_XDecayVtx_YE, out_XDecayVtx_ZE, out_XCosAlphaBS, out_XCosAlpha3DBS, out_XCTauBS;
Float_t out_XCTauBSE, out_XLxyBS, out_XLxyBSE, out_XLxyzBS, out_XLxyzBSE;
Float_t out_XCosAlphaPV, out_XCosAlpha3DPV, out_XCTauPV, out_XCTauPVE, out_XLxyPV;
Float_t out_XLxyPVE, out_XLxyzPV, out_XLxyzPVE, out_PriVtx_XCosAlpha_n, out_PriVtx_XCosAlpha_X;
Float_t out_PriVtx_XCosAlpha_Y, out_PriVtx_XCosAlpha_Z, out_PriVtx_XCosAlpha_EX, out_PriVtx_XCosAlpha_EY, out_PriVtx_XCosAlpha_EZ;
Float_t out_PriVtx_XCosAlpha_Chi2, out_PriVtx_XCosAlpha_CL, out_PriVtx_XCosAlpha_tracks, out_XCosAlphaPVCosAlpha, out_XCosAlpha3DPVCosAlpha;
Float_t out_XCTauPVCosAlpha, out_XCTauPVCosAlphaE, out_XLxyPVCosAlpha, out_XLxyPVCosAlphaE, out_XLxyzPVCosAlpha;
Float_t out_XLxyzPVCosAlphaE, out_PriVtx_XCosAlpha3D_n, out_PriVtx_XCosAlpha3D_X, out_PriVtx_XCosAlpha3D_Y, out_PriVtx_XCosAlpha3D_Z;
Float_t out_PriVtx_XCosAlpha3D_EX, out_PriVtx_XCosAlpha3D_EY, out_PriVtx_XCosAlpha3D_EZ, out_PriVtx_XCosAlpha3D_Chi2, out_PriVtx_XCosAlpha3D_CL;
Float_t out_PriVtx_XCosAlpha3D_tracks, out_XCosAlphaPVCosAlpha3D, out_XCosAlpha3DPVCosAlpha3D, out_XCTauPVCosAlpha3D, out_XCTauPVCosAlpha3DE;
Float_t out_XLxyPVCosAlpha3D, out_XLxyPVCosAlpha3DE, out_XLxyzPVCosAlpha3D, out_XLxyzPVCosAlpha3DE, out_XLessPV_tracksPtSq;
Float_t out_XLessPV_4tracksPtSq, out_PriVtxXLess_n, out_PriVtxXLess_X, out_PriVtxXLess_Y, out_PriVtxXLess_Z;
Float_t out_PriVtxXLess_EX, out_PriVtxXLess_EY, out_PriVtxXLess_EZ, out_PriVtxXLess_Chi2, out_PriVtxXLess_CL;
Float_t out_PriVtxXLess_tracks, out_XCosAlphaXLessPV, out_XCosAlpha3DXLessPV, out_XCTauXLessPV, out_XCTauXLessPVE;
Float_t out_XLxyXLessPV, out_XLxyXLessPVE, out_XLxyzXLessPV, out_XLxyzXLessPVE, out_PriVtxXLess_XCosAlpha_n;
Float_t out_PriVtxXLess_XCosAlpha_X, out_PriVtxXLess_XCosAlpha_Y, out_PriVtxXLess_XCosAlpha_Z, out_PriVtxXLess_XCosAlpha_EX, out_PriVtxXLess_XCosAlpha_EY;
Float_t out_PriVtxXLess_XCosAlpha_EZ, out_PriVtxXLess_XCosAlpha_Chi2, out_PriVtxXLess_XCosAlpha_CL, out_PriVtxXLess_XCosAlpha_tracks, out_XCosAlphaXLessPVCosAlpha;
Float_t out_XCosAlpha3DXLessPVCosAlpha, out_XCTauXLessPVCosAlpha, out_XCTauXLessPVCosAlphaE, out_XLxyXLessPVCosAlpha, out_XLxyXLessPVCosAlphaE;
Float_t out_XLxyzXLessPVCosAlpha, out_XLxyzXLessPVCosAlphaE, out_PriVtxXLess_XCosAlpha3D_n, out_PriVtxXLess_XCosAlpha3D_X, out_PriVtxXLess_XCosAlpha3D_Y;
Float_t out_PriVtxXLess_XCosAlpha3D_Z, out_PriVtxXLess_XCosAlpha3D_EX, out_PriVtxXLess_XCosAlpha3D_EY, out_PriVtxXLess_XCosAlpha3D_EZ, out_PriVtxXLess_XCosAlpha3D_Chi2;
Float_t out_PriVtxXLess_XCosAlpha3D_CL, out_PriVtxXLess_XCosAlpha3D_tracks, out_XCosAlphaXLessPVCosAlpha3D, out_XCosAlpha3DXLessPVCosAlpha3D, out_XCTauXLessPVCosAlpha3D;
Float_t out_XCTauXLessPVCosAlpha3DE, out_XLxyXLessPVCosAlpha3D, out_XLxyXLessPVCosAlpha3DE, out_XLxyzXLessPVCosAlpha3D, out_XLxyzXLessPVCosAlpha3DE;
Float_t out_PriVtxXCorr_n, out_PriVtxXCorr_X, out_PriVtxXCorr_Y, out_PriVtxXCorr_Z, out_PriVtxXCorr_EX;
Float_t out_PriVtxXCorr_EY, out_PriVtxXCorr_EZ, out_PriVtxXCorr_Chi2, out_PriVtxXCorr_CL, out_PriVtxXCorr_tracks;
Float_t out_XCosAlphaPVX, out_XCTauPVX, out_XCTauPVXE, out_XLxyPVX, out_XLxyzPVX;
Float_t out_XCTauPVX_3D, out_XCTauPVX_3D_err, out_kaon1_dxy_PV, out_kaon1_dz_PV, out_kaon2_dxy_PV;
Float_t out_kaon2_dz_PV, out_kaon1_dxy_BS, out_kaon1_dz_BS, out_kaon2_dxy_BS, out_kaon2_dz_BS;
Float_t out_kaon1_dxy_XLessPV, out_kaon1_dz_XLessPV, out_kaon2_dxy_XLessPV, out_kaon2_dz_XLessPV, out_kaon1_dxyE;
Float_t out_kaon1_dzE, out_kaon2_dxyE, out_kaon2_dzE, out_XMuMuIdx, out_XKaon1Idx;
Float_t out_XKaon2Idx, out_Kaon1FromPV, out_Kaon2FromPV, out_Muon1Px_MuMuKK, out_Muon1Py_MuMuKK;
Float_t out_Muon1Pz_MuMuKK, out_Muon1E_MuMuKK, out_Muon2Px_MuMuKK, out_Muon2Py_MuMuKK, out_Muon2Pz_MuMuKK;
Float_t out_Muon2E_MuMuKK, out_Kaon1Px_MuMuKK, out_Kaon1Py_MuMuKK, out_Kaon1Pz_MuMuKK, out_Kaon1E_MuMuKK;
Float_t out_kaon1_nsigdedx, out_kaon1_dedx, out_kaon1_dedxMass, out_kaon1_theo, out_kaon1_sigma;
Float_t out_kaon1_dedx_byHits, out_kaon1_dedxErr_byHits, out_kaon1_saturMeas_byHits, out_kaon1_Meas_byHits, out_Kaon2Px_MuMuKK;
Float_t out_Kaon2Py_MuMuKK, out_Kaon2Pz_MuMuKK, out_Kaon2E_MuMuKK, out_kaon2_nsigdedx, out_kaon2_dedx;
Float_t out_kaon2_dedxMass, out_kaon2_theo, out_kaon2_sigma, out_kaon2_dedx_byHits, out_kaon2_dedxErr_byHits;
Float_t out_kaon2_saturMeas_byHits, out_kaon2_Meas_byHits;
Float_ out_JpsiMass, out_JpsiMass_ref, out_PhiMass;


   TwoMuTwoK_2012(TTree * /*tree*/ =0) { }
   virtual ~TwoMuTwoK_2012() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   TProofOutputFile *OutFile;
   TFile            *fOut;

   ClassDef(TwoMuTwoK_2012,0);

};

#endif

#ifdef TwoMuTwoK_2012_cxx
void TwoMuTwoK_2012::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t TwoMuTwoK_2012::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef TwoMuTwoK_2012_cxx
