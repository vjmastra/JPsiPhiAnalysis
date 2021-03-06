//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Mar 23 16:50:33 2019 by ROOT version 6.12/07
// from TTree JPsiPhiTree/Tree of DiMuon and DiTrack
// found on file: rootuple-2018-dimuondiTrack_fivedataD2018_2_0_1.root
//////////////////////////////////////////////////////////

#ifndef FiveTracks_h
#define FiveTracks_h

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


// Headers needed by this particular selector
#include "TLorentzVector.h"



class FiveTracks : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   TTree *outTree;

   // Readers to access the data (delete the ones you do not need).
   // Readers to access the data (delete the ones you do not need).
TTreeReaderValue<Int_t> run = {fReader, "run"};
TTreeReaderValue<Int_t> event = {fReader, "event"};
TTreeReaderValue<Int_t> lumi = {fReader, "lumi"};
TTreeReaderValue<Int_t> numPrimaryVertices = {fReader, "numPrimaryVertices"};
TTreeReaderValue<Int_t> trigger = {fReader, "trigger"};
TTreeReaderValue<Int_t> noFiveCandidates = {fReader, "noFiveCandidates"};
TTreeReaderValue<Int_t> dimuonditrk_id = {fReader, "dimuonditrk_id"};
TTreeReaderValue<Int_t> dimuon_id = {fReader, "dimuon_id"};
TTreeReaderValue<Int_t> p_id = {fReader, "p_id"};
TTreeReaderValue<Int_t> m_id = {fReader, "m_id"};
TTreeReaderValue<Int_t> t_id = {fReader, "t_id"};
TTreeReaderValue<TLorentzVector> five_p4 = {fReader, "five_p4"};
TTreeReaderValue<TLorentzVector> dimuonditrk_p4 = {fReader, "dimuonditrk_p4"};
TTreeReaderValue<TLorentzVector> ditrack_p4 = {fReader, "ditrack_p4"};
TTreeReaderValue<TLorentzVector> dimuon_p4 = {fReader, "dimuon_p4"};
TTreeReaderValue<TLorentzVector> lowMuon_p4 = {fReader, "lowMuon_p4"};
TTreeReaderValue<TLorentzVector> highMuon_p4 = {fReader, "highMuon_p4"};
TTreeReaderValue<TLorentzVector> highKaon_p4 = {fReader, "highKaon_p4"};
TTreeReaderValue<TLorentzVector> lowKaon_p4 = {fReader, "lowKaon_p4"};
TTreeReaderValue<TLorentzVector> thirdKaon_p4 = {fReader, "thirdKaon_p4"};
TTreeReaderValue<TLorentzVector> highPion_p4 = {fReader, "highPion_p4"};
TTreeReaderValue<TLorentzVector> lowPion_p4 = {fReader, "lowPion_p4"};
TTreeReaderValue<TLorentzVector> thirdPion_p4 = {fReader, "thirdPion_p4"};
TTreeReaderValue<TLorentzVector> highProton_p4 = {fReader, "highProton_p4"};
TTreeReaderValue<TLorentzVector> lowProton_p4 = {fReader, "lowProton_p4"};
TTreeReaderValue<TLorentzVector> thirdProton_p4 = {fReader, "thirdProton_p4"};
TTreeReaderValue<Double_t> dimuonditrk_m = {fReader, "dimuonditrk_m"};
TTreeReaderValue<Double_t> dimuonditrk_pt = {fReader, "dimuonditrk_pt"};
TTreeReaderValue<Double_t> dimuonditrk_eta = {fReader, "dimuonditrk_eta"};
TTreeReaderValue<Double_t> dimuonditrk_phi = {fReader, "dimuonditrk_phi"};
TTreeReaderValue<Double_t> dimuonditrk_p = {fReader, "dimuonditrk_p"};
TTreeReaderValue<Double_t> dimuon_m = {fReader, "dimuon_m"};
TTreeReaderValue<Double_t> dimuon_pt = {fReader, "dimuon_pt"};
TTreeReaderValue<Double_t> dimuon_eta = {fReader, "dimuon_eta"};
TTreeReaderValue<Double_t> dimuon_phi = {fReader, "dimuon_phi"};
TTreeReaderValue<Double_t> dimuon_p = {fReader, "dimuon_p"};
TTreeReaderValue<Double_t> highTrackMatch = {fReader, "highTrackMatch"};
TTreeReaderValue<Double_t> lowTrackMatch = {fReader, "lowTrackMatch"};
TTreeReaderValue<Double_t> lowMuonMatch = {fReader, "lowMuonMatch"};
TTreeReaderValue<Double_t> thirdTrackMatch = {fReader, "thirdTrackMatch"};
TTreeReaderValue<Double_t> ditrack_m = {fReader, "ditrack_m"};
TTreeReaderValue<Double_t> ditrackOne_pt = {fReader, "ditrackOne_pt"};
TTreeReaderValue<Double_t> ditrackOne_eta = {fReader, "ditrackOne_eta"};
TTreeReaderValue<Double_t> ditrackOne_phi = {fReader, "ditrackOne_phi"};
TTreeReaderValue<Double_t> ditrackOne_p = {fReader, "ditrackOne_p"};
TTreeReaderValue<Double_t> ditrackTwo_pt = {fReader, "ditrackTwo_pt"};
TTreeReaderValue<Double_t> ditrackTwo_eta = {fReader, "ditrackTwo_eta"};
TTreeReaderValue<Double_t> ditrackTwo_phi = {fReader, "ditrackTwo_phi"};
TTreeReaderValue<Double_t> ditrackTwo_p = {fReader, "ditrackTwo_p"};
TTreeReaderValue<Double_t> ditrackThree_pt = {fReader, "ditrackThree_pt"};
TTreeReaderValue<Double_t> ditrackThree_eta = {fReader, "ditrackThree_eta"};
TTreeReaderValue<Double_t> ditrackThree_phi = {fReader, "ditrackThree_phi"};
TTreeReaderValue<Double_t> ditrackThree_p = {fReader, "ditrackThree_p"};
TTreeReaderValue<Double_t> highMuon_pt = {fReader, "highMuon_pt"};
TTreeReaderValue<Double_t> highMuon_eta = {fReader, "highMuon_eta"};
TTreeReaderValue<Double_t> highMuon_phi = {fReader, "highMuon_phi"};
TTreeReaderValue<Double_t> highMuon_charge = {fReader, "highMuon_charge"};
TTreeReaderValue<Double_t> highMuon_dz = {fReader, "highMuon_dz"};
TTreeReaderValue<Double_t> highMuon_dxy = {fReader, "highMuon_dxy"};
TTreeReaderValue<Double_t> lowMuon_pt = {fReader, "lowMuon_pt"};
TTreeReaderValue<Double_t> lowMuon_eta = {fReader, "lowMuon_eta"};
TTreeReaderValue<Double_t> lowMuon_phi = {fReader, "lowMuon_phi"};
TTreeReaderValue<Double_t> lowMuon_charge = {fReader, "lowMuon_charge"};
TTreeReaderValue<Double_t> lowMuon_dz = {fReader, "lowMuon_dz"};
TTreeReaderValue<Double_t> lowMuon_dxy = {fReader, "lowMuon_dxy"};
TTreeReaderValue<Double_t> highTrack_pt = {fReader, "highTrack_pt"};
TTreeReaderValue<Double_t> highTrack_eta = {fReader, "highTrack_eta"};
TTreeReaderValue<Double_t> highTrack_phi = {fReader, "highTrack_phi"};
TTreeReaderValue<Double_t> highTrack_charge = {fReader, "highTrack_charge"};
TTreeReaderValue<Double_t> highTrack_dz = {fReader, "highTrack_dz"};
TTreeReaderValue<Double_t> highTrack_dxy = {fReader, "highTrack_dxy"};
TTreeReaderValue<Double_t> lowTrack_pt = {fReader, "lowTrack_pt"};
TTreeReaderValue<Double_t> lowTrack_eta = {fReader, "lowTrack_eta"};
TTreeReaderValue<Double_t> lowTrack_phi = {fReader, "lowTrack_phi"};
TTreeReaderValue<Double_t> lowTrack_charge = {fReader, "lowTrack_charge"};
TTreeReaderValue<Double_t> lowTrack_dz = {fReader, "lowTrack_dz"};
TTreeReaderValue<Double_t> lowTrack_dxy = {fReader, "lowTrack_dxy"};
TTreeReaderValue<Double_t> thirdTrack_pt = {fReader, "thirdTrack_pt"};
TTreeReaderValue<Double_t> thirdTrack_eta = {fReader, "thirdTrack_eta"};
TTreeReaderValue<Double_t> thirdTrack_phi = {fReader, "thirdTrack_phi"};
TTreeReaderValue<Double_t> thirdTrack_charge = {fReader, "thirdTrack_charge"};
TTreeReaderValue<Double_t> thirdTrack_dz = {fReader, "thirdTrack_dz"};
TTreeReaderValue<Double_t> thirdTrack_dxy = {fReader, "thirdTrack_dxy"};
TTreeReaderValue<Double_t> dimuonDiTrkOne_pt = {fReader, "dimuonDiTrkOne_pt"};
TTreeReaderValue<Double_t> dimuonDiTrkOne_eta = {fReader, "dimuonDiTrkOne_eta"};
TTreeReaderValue<Double_t> dimuonDiTrkOne_phi = {fReader, "dimuonDiTrkOne_phi"};
TTreeReaderValue<Double_t> dimuonDiTrkOne_charge = {fReader, "dimuonDiTrkOne_charge"};
TTreeReaderValue<Double_t> dimuonDiTrkOne_p = {fReader, "dimuonDiTrkOne_p"};
TTreeReaderValue<Double_t> dimuonDiTrkTwo_pt = {fReader, "dimuonDiTrkTwo_pt"};
TTreeReaderValue<Double_t> dimuonDiTrkTwo_eta = {fReader, "dimuonDiTrkTwo_eta"};
TTreeReaderValue<Double_t> dimuonDiTrkTwo_phi = {fReader, "dimuonDiTrkTwo_phi"};
TTreeReaderValue<Double_t> dimuonDiTrkTwo_charge = {fReader, "dimuonDiTrkTwo_charge"};
TTreeReaderValue<Double_t> dimuonDiTrkTwo_p = {fReader, "dimuonDiTrkTwo_p"};
TTreeReaderValue<Double_t> dimuonDiTrkThree_pt = {fReader, "dimuonDiTrkThree_pt"};
TTreeReaderValue<Double_t> dimuonDiTrkThree_eta = {fReader, "dimuonDiTrkThree_eta"};
TTreeReaderValue<Double_t> dimuonDiTrkThree_phi = {fReader, "dimuonDiTrkThree_phi"};
TTreeReaderValue<Double_t> dimuonDiTrkThree_charge = {fReader, "dimuonDiTrkThree_charge"};
TTreeReaderValue<Double_t> dimuonDiTrkThree_p = {fReader, "dimuonDiTrkThree_p"};
TTreeReaderValue<Double_t> dimuon_vProb = {fReader, "dimuon_vProb"};
TTreeReaderValue<Double_t> dimuon_vChi2 = {fReader, "dimuon_vChi2"};
TTreeReaderValue<Double_t> dimuon_DCA = {fReader, "dimuon_DCA"};
TTreeReaderValue<Double_t> dimuon_ctauPV = {fReader, "dimuon_ctauPV"};
TTreeReaderValue<Double_t> dimuon_ctauErrPV = {fReader, "dimuon_ctauErrPV"};
TTreeReaderValue<Double_t> dimuon_cosAlpha = {fReader, "dimuon_cosAlpha"};
TTreeReaderValue<Double_t> triTrack_m = {fReader, "triTrack_m"};
TTreeReaderValue<Double_t> triTrack_pt = {fReader, "triTrack_pt"};
TTreeReaderValue<Double_t> triTrack_eta = {fReader, "triTrack_eta"};
TTreeReaderValue<Double_t> triTrack_phi = {fReader, "triTrack_phi"};
TTreeReaderValue<Double_t> triTrack_charge = {fReader, "triTrack_charge"};
TTreeReaderValue<Double_t> dimuonditrk_vProb = {fReader, "dimuonditrk_vProb"};
TTreeReaderValue<Double_t> dimuonditrk_vChi2 = {fReader, "dimuonditrk_vChi2"};
TTreeReaderValue<Double_t> dimuonditrk_nDof = {fReader, "dimuonditrk_nDof"};
TTreeReaderValue<Int_t> dimuonditrk_charge = {fReader, "dimuonditrk_charge"};
TTreeReaderValue<Double_t> dimuonditrk_cosAlpha = {fReader, "dimuonditrk_cosAlpha"};
TTreeReaderValue<Double_t> dimuonditrk_ctauPV = {fReader, "dimuonditrk_ctauPV"};
TTreeReaderValue<Double_t> dimuonditrk_ctauErrPV = {fReader, "dimuonditrk_ctauErrPV"};
TTreeReaderValue<Double_t> dimuonditrk_cosAlphaCA = {fReader, "dimuonditrk_cosAlphaCA"};
TTreeReaderValue<Double_t> dimuonditrk_ctauPVCA = {fReader, "dimuonditrk_ctauPVCA"};
TTreeReaderValue<Double_t> dimuonditrk_ctauErrPVCA = {fReader, "dimuonditrk_ctauErrPVCA"};
TTreeReaderValue<Double_t> dimuonditrk_cosAlphaDZ = {fReader, "dimuonditrk_cosAlphaDZ"};
TTreeReaderValue<Double_t> dimuonditrk_ctauPVDZ = {fReader, "dimuonditrk_ctauPVDZ"};
TTreeReaderValue<Double_t> dimuonditrk_ctauErrPVDZ = {fReader, "dimuonditrk_ctauErrPVDZ"};
TTreeReaderValue<Double_t> dimuonditrk_cosAlphaBS = {fReader, "dimuonditrk_cosAlphaBS"};
TTreeReaderValue<Double_t> dimuonditrk_ctauPVBS = {fReader, "dimuonditrk_ctauPVBS"};
TTreeReaderValue<Double_t> dimuonditrk_ctauErrPVBS = {fReader, "dimuonditrk_ctauErrPVBS"};
TTreeReaderValue<Double_t> dimuonditrk_vx = {fReader, "dimuonditrk_vx"};
TTreeReaderValue<Double_t> dimuonditrk_vy = {fReader, "dimuonditrk_vy"};
TTreeReaderValue<Double_t> dimuonditrk_vz = {fReader, "dimuonditrk_vz"};
TTreeReaderValue<Double_t> dca_m1m2 = {fReader, "dca_m1m2"};
TTreeReaderValue<Double_t> dca_m1t1 = {fReader, "dca_m1t1"};
TTreeReaderValue<Double_t> dca_m1t2 = {fReader, "dca_m1t2"};
TTreeReaderValue<Double_t> dca_m2t1 = {fReader, "dca_m2t1"};
TTreeReaderValue<Double_t> dca_m2t2 = {fReader, "dca_m2t2"};
TTreeReaderValue<Double_t> dca_t1t2 = {fReader, "dca_t1t2"};
TTreeReaderValue<Double_t> dca_m1t3 = {fReader, "dca_m1t3"};
TTreeReaderValue<Double_t> dca_m2t3 = {fReader, "dca_m2t3"};
TTreeReaderValue<Double_t> dca_t1t3 = {fReader, "dca_t1t3"};
TTreeReaderValue<Double_t> dca_t2t3 = {fReader, "dca_t2t3"};
TTreeReaderValue<Double_t> highTrackMuonDR = {fReader, "highTrackMuonDR"};
TTreeReaderValue<Double_t> highTrackMuonDP = {fReader, "highTrackMuonDP"};
TTreeReaderValue<Double_t> highTrackMuonDPt = {fReader, "highTrackMuonDPt"};
TTreeReaderValue<Double_t> lowTrackMuonDR = {fReader, "lowTrackMuonDR"};
TTreeReaderValue<Double_t> lowTrackMuonDP = {fReader, "lowTrackMuonDP"};
TTreeReaderValue<Double_t> lowTrackMuonDPt = {fReader, "lowTrackMuonDPt"};
TTreeReaderValue<Double_t> thirdTrackMuonDR = {fReader, "thirdTrackMuonDR"};
TTreeReaderValue<Double_t> thirdTrackMuonDP = {fReader, "thirdTrackMuonDP"};
TTreeReaderValue<Double_t> thirdTrackMuonDPt = {fReader, "thirdTrackMuonDPt"};
// TTreeReaderValue<Double_t> tPFromPV = {fReader, "tPFromPV"};
// TTreeReaderValue<Double_t> tMFromPV = {fReader, "tMFromPV"};
// TTreeReaderValue<Double_t> tTFromPV = {fReader, "tTFromPV"};
// TTreeReaderValue<Double_t> tPFromPVCA = {fReader, "tPFromPVCA"};
// TTreeReaderValue<Double_t> tMFromPVCA = {fReader, "tMFromPVCA"};
// TTreeReaderValue<Double_t> tMFTomPVCA = {fReader, "tTFromPVCA"};
// TTreeReaderValue<Double_t> tPFromPVDZ = {fReader, "tPFromPVDZ"};
// TTreeReaderValue<Double_t> tMFromPVDZ = {fReader, "tMFromPVDZ"};
// TTreeReaderValue<Double_t> tTFromPVDZ = {fReader, "tTFromPVDZ"};
TTreeReaderValue<Double_t> five_m = {fReader, "five_m"};
TTreeReaderValue<Double_t> five_m_ref = {fReader, "five_m_ref"};
TTreeReaderValue<Double_t> five_mass_ppk = {fReader, "five_mass_ppk"};
TTreeReaderValue<Double_t> five_mass_kpp = {fReader, "five_mass_kpp"};
TTreeReaderValue<Double_t> five_mass_pkp = {fReader, "five_mass_pkp"};
TTreeReaderValue<Double_t> five_mass_ppp = {fReader, "five_mass_ppp"};
TTreeReaderValue<Double_t> five_pt = {fReader, "five_pt"};
TTreeReaderValue<Double_t> five_eta = {fReader, "five_eta"};
TTreeReaderValue<Double_t> five_phi = {fReader, "five_phi"};
TTreeReaderValue<Double_t> five_p = {fReader, "five_p"};
TTreeReaderValue<Double_t> five_cosAlpha = {fReader, "five_cosAlpha"};
TTreeReaderValue<Double_t> five_ctauPV = {fReader, "five_ctauPV"};
TTreeReaderValue<Double_t> five_ctauErrPV = {fReader, "five_ctauErrPV"};
TTreeReaderValue<Double_t> five_cosAlphaCA = {fReader, "five_cosAlphaCA"};
TTreeReaderValue<Double_t> five_ctauPVCA = {fReader, "five_ctauPVCA"};
TTreeReaderValue<Double_t> five_ctauErrPVCA = {fReader, "five_ctauErrPVCA"};
TTreeReaderValue<Double_t> five_cosAlphaDZ = {fReader, "five_cosAlphaDZ"};
TTreeReaderValue<Double_t> five_ctauPVDZ = {fReader, "five_ctauPVDZ"};
TTreeReaderValue<Double_t> five_ctauErrPVDZ = {fReader, "five_ctauErrPVDZ"};
TTreeReaderValue<Double_t> five_cosAlphaBS = {fReader, "five_cosAlphaBS"};
TTreeReaderValue<Double_t> five_ctauPVBS = {fReader, "five_ctauPVBS"};
TTreeReaderValue<Double_t> five_ctauErrPVBS = {fReader, "five_ctauErrPVBS"};
TTreeReaderValue<Double_t> five_vProb = {fReader, "five_vProb"};
TTreeReaderValue<Double_t> five_nDof = {fReader, "five_nDof"};
TTreeReaderValue<Double_t> five_vChi2 = {fReader, "five_vChi2"};
TTreeReaderValue<Double_t> five_vx = {fReader, "five_vx"};
TTreeReaderValue<Double_t> five_vy = {fReader, "five_vy"};
TTreeReaderValue<Double_t> five_vz = {fReader, "five_vz"};
TTreeReaderValue<Double_t> bestPV_X = {fReader, "bestPV_X"};
TTreeReaderValue<Double_t> bestPV_Y = {fReader, "bestPV_Y"};
TTreeReaderValue<Double_t> bestPV_Z = {fReader, "bestPV_Z"};
TTreeReaderValue<Double_t> cosAlphaPV_X = {fReader, "cosAlphaPV_X"};
TTreeReaderValue<Double_t> cosAlphaPV_Y = {fReader, "cosAlphaPV_Y"};
TTreeReaderValue<Double_t> cosAlphaPV_Z = {fReader, "cosAlphaPV_Z"};
TTreeReaderValue<Double_t> bS_X = {fReader, "bS_X"};
TTreeReaderValue<Double_t> bS_Y = {fReader, "bS_Y"};
TTreeReaderValue<Double_t> bS_Z = {fReader, "bS_Z"};
TTreeReaderValue<Double_t> zPV_X = {fReader, "zPV_X"};
TTreeReaderValue<Double_t> zPV_Y = {fReader, "zPV_Y"};
TTreeReaderValue<Double_t> zPV_Z = {fReader, "zPV_Z"};
TTreeReaderValue<Int_t> five_charge = {fReader, "five_charge"};
TTreeReaderValue<Bool_t> lowMuon_isTight = {fReader, "lowMuon_isTight"};
TTreeReaderValue<Bool_t> lowMuon_isLoose = {fReader, "lowMuon_isLoose"};
TTreeReaderValue<Bool_t> lowMuon_isSoft = {fReader, "lowMuon_isSoft"};
TTreeReaderValue<Bool_t> lowMuon_isMedium = {fReader, "lowMuon_isMedium"};
TTreeReaderValue<Bool_t> lowMuon_isHighPt = {fReader, "lowMuon_isHighPt"};
TTreeReaderValue<Bool_t> lowMuon_isTracker = {fReader, "lowMuon_isTracker"};
TTreeReaderValue<Bool_t> lowMuon_isGlobal = {fReader, "lowMuon_isGlobal"};
TTreeReaderValue<Int_t> lowMuon_NPixelHits = {fReader, "lowMuon_NPixelHits"};
TTreeReaderValue<Int_t> lowMuon_NStripHits = {fReader, "lowMuon_NStripHits"};
TTreeReaderValue<Int_t> lowMuon_NTrackhits = {fReader, "lowMuon_NTrackhits"};
TTreeReaderValue<Int_t> lowMuon_NBPixHits = {fReader, "lowMuon_NBPixHits"};
TTreeReaderValue<Int_t> lowMuon_NPixLayers = {fReader, "lowMuon_NPixLayers"};
TTreeReaderValue<Int_t> lowMuon_NTraLayers = {fReader, "lowMuon_NTraLayers"};
TTreeReaderValue<Int_t> lowMuon_NStrLayers = {fReader, "lowMuon_NStrLayers"};
TTreeReaderValue<Int_t> lowMuon_NBPixLayers = {fReader, "lowMuon_NBPixLayers"};
TTreeReaderValue<Bool_t> highMuon_isTight = {fReader, "highMuon_isTight"};
TTreeReaderValue<Bool_t> highMuon_isLoose = {fReader, "highMuon_isLoose"};
TTreeReaderValue<Bool_t> highMuon_isSoft = {fReader, "highMuon_isSoft"};
TTreeReaderValue<Bool_t> highMuon_isMedium = {fReader, "highMuon_isMedium"};
TTreeReaderValue<Bool_t> highMuon_isHighPt = {fReader, "highMuon_isHighPt"};
TTreeReaderValue<Bool_t> highMuon_isTracker = {fReader, "highMuon_isTracker"};
TTreeReaderValue<Bool_t> highMuon_isGlobal = {fReader, "highMuon_isGlobal"};
TTreeReaderValue<Int_t> highMuon_NPixelHits = {fReader, "highMuon_NPixelHits"};
TTreeReaderValue<Int_t> highMuon_NStripHits = {fReader, "highMuon_NStripHits"};
TTreeReaderValue<Int_t> highMuon_NTrackhits = {fReader, "highMuon_NTrackhits"};
TTreeReaderValue<Int_t> highMuon_NBPixHits = {fReader, "highMuon_NBPixHits"};
TTreeReaderValue<Int_t> highMuon_NPixLayers = {fReader, "highMuon_NPixLayers"};
TTreeReaderValue<Int_t> highMuon_NTraLayers = {fReader, "highMuon_NTraLayers"};
TTreeReaderValue<Int_t> highMuon_NStrLayers = {fReader, "highMuon_NStrLayers"};
TTreeReaderValue<Int_t> highMuon_NBPixLayers = {fReader, "highMuon_NBPixLayers"};
TTreeReaderValue<UInt_t> lowMuon_type = {fReader, "lowMuon_type"};
TTreeReaderValue<UInt_t> highMuon_type = {fReader, "highMuon_type"};
TTreeReaderValue<Int_t> highTrack_NPixelHits = {fReader, "highTrack_NPixelHits"};
TTreeReaderValue<Int_t> highTrack_NStripHits = {fReader, "highTrack_NStripHits"};
TTreeReaderValue<Int_t> highTrack_NTrackhits = {fReader, "highTrack_NTrackhits"};
TTreeReaderValue<Int_t> highTrack_NBPixHits = {fReader, "highTrack_NBPixHits"};
TTreeReaderValue<Int_t> highTrack_NPixLayers = {fReader, "highTrack_NPixLayers"};
TTreeReaderValue<Int_t> highTrack_NTraLayers = {fReader, "highTrack_NTraLayers"};
TTreeReaderValue<Int_t> highTrack_NStrLayers = {fReader, "highTrack_NStrLayers"};
TTreeReaderValue<Int_t> highTrack_NBPixLayers = {fReader, "highTrack_NBPixLayers"};
TTreeReaderValue<Int_t> lowTrack_NPixelHits = {fReader, "lowTrack_NPixelHits"};
TTreeReaderValue<Int_t> lowTrack_NStripHits = {fReader, "lowTrack_NStripHits"};
TTreeReaderValue<Int_t> lowTrack_NTrackhits = {fReader, "lowTrack_NTrackhits"};
TTreeReaderValue<Int_t> lowTrack_NBPixHits = {fReader, "lowTrack_NBPixHits"};
TTreeReaderValue<Int_t> lowTrack_NPixLayers = {fReader, "lowTrack_NPixLayers"};
TTreeReaderValue<Int_t> lowTrack_NTraLayers = {fReader, "lowTrack_NTraLayers"};
TTreeReaderValue<Int_t> lowTrack_NStrLayers = {fReader, "lowTrack_NStrLayers"};
TTreeReaderValue<Int_t> lowTrack_NBPixLayers = {fReader, "lowTrack_NBPixLayers"};
TTreeReaderValue<Int_t> thirdTrack_NPixelHits = {fReader, "thirdTrack_NPixelHits"};
TTreeReaderValue<Int_t> thirdTrack_NStripHits = {fReader, "thirdTrack_NStripHits"};
TTreeReaderValue<Int_t> thirdTrack_NTrackhits = {fReader, "thirdTrack_NTrackhits"};
TTreeReaderValue<Int_t> thirdTrack_NBPixHits = {fReader, "thirdTrack_NBPixHits"};
TTreeReaderValue<Int_t> thirdTrack_NPixLayers = {fReader, "thirdTrack_NPixLayers"};
TTreeReaderValue<Int_t> thirdTrack_NTraLayers = {fReader, "thirdTrack_NTraLayers"};
TTreeReaderValue<Int_t> thirdTrack_NStrLayers = {fReader, "thirdTrack_NStrLayers"};
TTreeReaderValue<Int_t> thirdTrack_NBPixLayers = {fReader, "thirdTrack_NBPixLayers"};




Float_t out_run, out_event, out_lumi, out_numPrimaryVertices, out_trigger;
Float_t out_noFiveCandidates, out_dimuonditrk_id, out_dimuon_id, out_p_id, out_m_id;
Float_t out_t_id, out_five_p4, out_dimuonditrk_p4, out_ditrack_p4, out_dimuon_p4;
Float_t out_lowMuon_p4, out_highMuon_p4, out_highKaon_p4, out_lowKaon_p4, out_thirdKaon_p4;
Float_t out_highPion_p4, out_lowPion_p4, out_thirdPion_p4, out_highProton_p4, out_lowProton_p4;
Float_t out_thirdProton_p4, out_dimuonditrk_m, out_dimuonditrk_pt, out_dimuonditrk_eta, out_dimuonditrk_phi;
Float_t out_dimuonditrk_p, out_dimuon_m, out_dimuon_pt, out_dimuon_eta, out_dimuon_phi;
Float_t out_dimuon_p, out_highTrackMatch, out_lowTrackMatch, out_lowMuonMatch, out_thirdTrackMatch;
Float_t out_ditrack_m, out_ditrackOne_pt, out_ditrackOne_eta, out_ditrackOne_phi, out_ditrackOne_p;
Float_t out_ditrackTwo_pt, out_ditrackTwo_eta, out_ditrackTwo_phi, out_ditrackTwo_p, out_ditrackThree_pt;
Float_t out_ditrackThree_eta, out_ditrackThree_phi, out_ditrackThree_p, out_highMuon_pt, out_highMuon_eta;
Float_t out_highMuon_phi, out_highMuon_charge, out_highMuon_dz, out_highMuon_dxy, out_lowMuon_pt;
Float_t out_lowMuon_eta, out_lowMuon_phi, out_lowMuon_charge, out_lowMuon_dz, out_lowMuon_dxy;
Float_t out_highTrack_pt, out_highTrack_eta, out_highTrack_phi, out_highTrack_charge, out_highTrack_dz;
Float_t out_highTrack_dxy, out_lowTrack_pt, out_lowTrack_eta, out_lowTrack_phi, out_lowTrack_charge;
Float_t out_lowTrack_dz, out_lowTrack_dxy, out_thirdTrack_pt, out_thirdTrack_eta, out_thirdTrack_phi;
Float_t out_thirdTrack_charge, out_thirdTrack_dz, out_thirdTrack_dxy, out_dimuonDiTrkOne_pt, out_dimuonDiTrkOne_eta;
Float_t out_dimuonDiTrkOne_phi, out_dimuonDiTrkOne_charge, out_dimuonDiTrkOne_p, out_dimuonDiTrkTwo_pt, out_dimuonDiTrkTwo_eta;
Float_t out_dimuonDiTrkTwo_phi, out_dimuonDiTrkTwo_charge, out_dimuonDiTrkTwo_p, out_dimuonDiTrkThree_pt, out_dimuonDiTrkThree_eta;
Float_t out_dimuonDiTrkThree_phi, out_dimuonDiTrkThree_charge, out_dimuonDiTrkThree_p, out_dimuon_vProb, out_dimuon_vChi2;
Float_t out_dimuon_DCA, out_dimuon_ctauPV, out_dimuon_ctauErrPV, out_dimuon_cosAlpha, out_triTrack_m;
Float_t out_triTrack_pt, out_triTrack_eta, out_triTrack_phi, out_triTrack_charge, out_dimuonditrk_vProb;
Float_t out_dimuonditrk_vChi2, out_dimuonditrk_nDof, out_dimuonditrk_charge, out_dimuonditrk_cosAlpha, out_dimuonditrk_ctauPV;
Float_t out_dimuonditrk_ctauErrPV, out_dimuonditrk_cosAlphaCA, out_dimuonditrk_ctauPVCA, out_dimuonditrk_ctauErrPVCA, out_dimuonditrk_cosAlphaDZ;
Float_t out_dimuonditrk_ctauPVDZ, out_dimuonditrk_ctauErrPVDZ, out_dimuonditrk_cosAlphaBS, out_dimuonditrk_ctauPVBS, out_dimuonditrk_ctauErrPVBS;
Float_t out_dimuonditrk_vx, out_dimuonditrk_vy, out_dimuonditrk_vz, out_dca_m1m2, out_dca_m1t1;
Float_t out_dca_m1t2, out_dca_m2t1, out_dca_m2t2, out_dca_t1t2, out_dca_m1t3;
Float_t out_dca_m2t3, out_dca_t1t3, out_dca_t2t3, out_highTrackMuonDR, out_highTrackMuonDP;
Float_t out_highTrackMuonDPt, out_lowTrackMuonDR, out_lowTrackMuonDP, out_lowTrackMuonDPt, out_thirdTrackMuonDR;
Float_t out_thirdTrackMuonDP, out_thirdTrackMuonDPt, out_tPFromPV, out_tMFromPV, out_tTFromPV;
Float_t out_tPFromPVCA, out_tMFromPVCA, out_tTFromPVCA, out_tPFromPVDZ, out_tMFromPVDZ;
Float_t out_tTFromPVDZ, out_five_m, out_five_m_ref, out_five_mass_ppk, out_five_mass_kpp;
Float_t out_five_mass_pkp, out_five_mass_ppp, out_five_pt, out_five_eta, out_five_phi;
Float_t out_five_p, out_five_cosAlpha, out_five_ctauPV, out_five_ctauErrPV, out_five_cosAlphaCA;
Float_t out_five_ctauPVCA, out_five_ctauErrPVCA, out_five_cosAlphaDZ, out_five_ctauPVDZ, out_five_ctauErrPVDZ;
Float_t out_five_cosAlphaBS, out_five_ctauPVBS, out_five_ctauErrPVBS, out_five_vProb, out_five_nDof;
Float_t out_five_vChi2, out_five_vx, out_five_vy, out_five_vz, out_bestPV_X;
Float_t out_bestPV_Y, out_bestPV_Z, out_cosAlphaPV_X, out_cosAlphaPV_Y, out_cosAlphaPV_Z;
Float_t out_bS_X, out_bS_Y, out_bS_Z, out_zPV_X, out_zPV_Y;
Float_t out_zPV_Z, out_five_charge, out_lowMuon_isTight, out_lowMuon_isLoose, out_lowMuon_isSoft;
Float_t out_lowMuon_isMedium, out_lowMuon_isHighPt, out_lowMuon_isTracker, out_lowMuon_isGlobal, out_lowMuon_NPixelHits;
Float_t out_lowMuon_NStripHits, out_lowMuon_NTrackhits, out_lowMuon_NBPixHits, out_lowMuon_NPixLayers, out_lowMuon_NTraLayers;
Float_t out_lowMuon_NStrLayers, out_lowMuon_NBPixLayers, out_highMuon_isTight, out_highMuon_isLoose, out_highMuon_isSoft;
Float_t out_highMuon_isMedium, out_highMuon_isHighPt, out_highMuon_isTracker, out_highMuon_isGlobal, out_highMuon_NPixelHits;
Float_t out_highMuon_NStripHits, out_highMuon_NTrackhits, out_highMuon_NBPixHits, out_highMuon_NPixLayers, out_highMuon_NTraLayers;
Float_t out_highMuon_NStrLayers, out_highMuon_NBPixLayers, out_lowMuon_type, out_highMuon_type, out_highTrack_NPixelHits;
Float_t out_highTrack_NStripHits, out_highTrack_NTrackhits, out_highTrack_NBPixHits, out_highTrack_NPixLayers, out_highTrack_NTraLayers;
Float_t out_highTrack_NStrLayers, out_highTrack_NBPixLayers, out_lowTrack_NPixelHits, out_lowTrack_NStripHits, out_lowTrack_NTrackhits;
Float_t out_lowTrack_NBPixHits, out_lowTrack_NPixLayers, out_lowTrack_NTraLayers, out_lowTrack_NStrLayers, out_lowTrack_NBPixLayers;
Float_t out_thirdTrack_NPixelHits, out_thirdTrack_NStripHits, out_thirdTrack_NTrackhits, out_thirdTrack_NBPixHits, out_thirdTrack_NPixLayers;
Float_t out_thirdTrack_NTraLayers, out_thirdTrack_NStrLayers, out_thirdTrack_NBPixLayers;
Float_t out_dimuonDiTrkOne_mmpp, out_dimuonDiTrkTwo_mmpp, out_dimuonDiTrkFour_mmpp, out_dimuonDiTrkOne_mmkk, out_dimuonDiTrkTwo_mmkk, out_dimuonDiTrkFour_mmkk;

   FiveTracks(TTree * /*tree*/ =0) { }
   virtual ~FiveTracks() { }
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

   ClassDef(FiveTracks,0);

};

#endif

#ifdef FiveTracks_cxx
void FiveTracks::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t FiveTracks::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef FiveTracks_cxx
