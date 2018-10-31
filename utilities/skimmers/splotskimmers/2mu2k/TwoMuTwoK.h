//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Sep 13 02:14:52 2018 by ROOT version 6.12/07
// from TTree JPsiPhiTree/Tree of DiMuon and DiTrak
// found on file: ../../../../../CMSSW_10_2_1/src/jpsiphi/jpsiphi/test/rootuple-2018-dimuonditrak_bbbar_hard_0.root
//////////////////////////////////////////////////////////

#ifndef TwoMuTwoK_h
#define TwoMuTwoK_h

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



class TwoMuTwoK : public TSelector {
  public :
  TTreeReader     fReader;  //!the tree reader
  TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

  Float_t JPsi_mass, Phi_mass, Phi_mean, Phi_sigma;
  TTree *outTree;

  //Double_t out;

  // Readers to access the data (delete the ones you do not need).
  TTreeReaderValue<Int_t> run = {fReader, "run"};
  TTreeReaderValue<Int_t> event = {fReader, "event"};
  TTreeReaderValue<Int_t> lumi = {fReader, "lumi"};
  TTreeReaderValue<Int_t> numPrimaryVertices = {fReader, "numPrimaryVertices"};
  TTreeReaderValue<Int_t> trigger = {fReader, "trigger"};
  TTreeReaderValue<Int_t> noXCandidates = {fReader, "noXCandidates"};
  TTreeReaderValue<TLorentzVector> dimuonditrk_p4 = {fReader, "dimuonditrk_p4"};
  TTreeReaderValue<TLorentzVector> ditrak_p4 = {fReader, "ditrak_p4"};
  TTreeReaderValue<TLorentzVector> dimuon_p4 = {fReader, "dimuon_p4"};
  TTreeReaderValue<TLorentzVector> lowMuon_p4 = {fReader, "lowMuon_p4"};
  TTreeReaderValue<TLorentzVector> highMuon_p4 = {fReader, "highMuon_p4"};
  TTreeReaderValue<TLorentzVector> highKaon_p4 = {fReader, "highKaon_p4"};
  TTreeReaderValue<TLorentzVector> lowKaon_p4 = {fReader, "lowKaon_p4"};
  TTreeReaderValue<TLorentzVector> dimuonditrk_rf_p4 = {fReader, "dimuonditrk_rf_p4"};
  TTreeReaderValue<TLorentzVector> ditrak_rf_p4 = {fReader, "ditrak_rf_p4"};
  TTreeReaderValue<TLorentzVector> dimuon_rf_p4 = {fReader, "dimuon_rf_p4"};
  TTreeReaderValue<TLorentzVector> lowMuon_rf_p4 = {fReader, "lowMuon_rf_p4"};
  TTreeReaderValue<TLorentzVector> highMuon_rf_p4 = {fReader, "highMuon_rf_p4"};
  TTreeReaderValue<TLorentzVector> kaonp_rf_p4 = {fReader, "kaonp_rf_p4"};
  TTreeReaderValue<TLorentzVector> kaonn_rf_p4 = {fReader, "kaonn_rf_p4"};
  TTreeReaderValue<Double_t> dimuonditrk_m = {fReader, "dimuonditrk_m"};
  TTreeReaderValue<Double_t> dimuonditrk_m_rf = {fReader, "dimuonditrk_m_rf"};
  TTreeReaderValue<Double_t> dimuonditrk_m_rf_d_c = {fReader, "dimuonditrk_m_rf_d_c"};
  TTreeReaderValue<Double_t> dimuonditrk_m_rf_c = {fReader, "dimuonditrk_m_rf_c"};
  TTreeReaderValue<Double_t> dimuonditrk_pt = {fReader, "dimuonditrk_pt"};
  TTreeReaderValue<Double_t> dimuonditrk_eta = {fReader, "dimuonditrk_eta"};
  TTreeReaderValue<Double_t> dimuonditrk_phi = {fReader, "dimuonditrk_phi"};
  TTreeReaderValue<Double_t> dimuonditrk_y = {fReader, "dimuonditrk_y"};
  TTreeReaderValue<Double_t> dimuonditrk_vx = {fReader, "dimuonditrk_vx"};
  TTreeReaderValue<Double_t> dimuonditrk_vy = {fReader, "dimuonditrk_vy"};
  TTreeReaderValue<Double_t> dimuonditrk_vz = {fReader, "dimuonditrk_vz"};
  TTreeReaderValue<Double_t> pv_x = {fReader, "pv_x"};
  TTreeReaderValue<Double_t> pv_y = {fReader, "pv_y"};
  TTreeReaderValue<Double_t> pv_z = {fReader, "pv_z"};
  TTreeReaderValue<Double_t> dimuon_m = {fReader, "dimuon_m"};
  TTreeReaderValue<Double_t> dimuon_pt = {fReader, "dimuon_pt"};
  TTreeReaderValue<Double_t> ditrak_m = {fReader, "ditrak_m"};
  TTreeReaderValue<Double_t> ditrak_pt = {fReader, "ditrak_pt"};
  TTreeReaderValue<Double_t> highKaon_pt = {fReader, "highKaon_pt"};
  TTreeReaderValue<Double_t> lowKaon_pt = {fReader, "lowKaon_pt"};
  TTreeReaderValue<Double_t> highMuon_pt = {fReader, "highMuon_pt"};
  TTreeReaderValue<Double_t> lowMuon_pt = {fReader, "lowMuon_pt"};
  TTreeReaderValue<Double_t> highKaon_eta = {fReader, "highKaon_eta"};
  TTreeReaderValue<Double_t> lowKaon_eta = {fReader, "lowKaon_eta"};
  TTreeReaderValue<Double_t> highMuon_eta = {fReader, "highMuon_eta"};
  TTreeReaderValue<Double_t> lowMuon_eta = {fReader, "lowMuon_eta"};
  TTreeReaderValue<Double_t> highKaon_phi = {fReader, "highKaon_phi"};
  TTreeReaderValue<Double_t> lowKaon_phi = {fReader, "lowKaon_phi"};
  TTreeReaderValue<Double_t> highMuon_phi = {fReader, "highMuon_phi"};
  TTreeReaderValue<Double_t> lowMuon_phi = {fReader, "lowMuon_phi"};
  TTreeReaderValue<Double_t> highKaon_dxy = {fReader, "highKaon_dxy"};
  TTreeReaderValue<Double_t> lowKaon_dxy = {fReader, "lowKaon_dxy"};
  TTreeReaderValue<Double_t> highMuon_dxy = {fReader, "highMuon_dxy"};
  TTreeReaderValue<Double_t> lowMuon_dxy = {fReader, "lowMuon_dxy"};
  TTreeReaderValue<Double_t> highKaon_dz = {fReader, "highKaon_dz"};
  TTreeReaderValue<Double_t> lowKaon_dz = {fReader, "lowKaon_dz"};
  TTreeReaderValue<Double_t> highMuon_dz = {fReader, "highMuon_dz"};
  TTreeReaderValue<Double_t> lowMuon_dz = {fReader, "lowMuon_dz"};
  TTreeReaderValue<Double_t> dimuonditrk_refPK_mass = {fReader, "dimuonditrk_refPK_mass"};
  TTreeReaderValue<Double_t> dimuonditrk_refKP_mass = {fReader, "dimuonditrk_refKP_mass"};
  TTreeReaderValue<Double_t> dimuonditrk_refPP_mass = {fReader, "dimuonditrk_refPP_mass"};
  TTreeReaderValue<Double_t> dimuonditrk_refPK_vChi2 = {fReader, "dimuonditrk_refPK_vChi2"};
  TTreeReaderValue<Double_t> dimuonditrk_refKP_vChi2 = {fReader, "dimuonditrk_refKP_vChi2"};
  TTreeReaderValue<Double_t> dimuonditrk_refPP_vChi2 = {fReader, "dimuonditrk_refPP_vChi2"};
  TTreeReaderValue<Double_t> dimuonditrk_refPK_nDof = {fReader, "dimuonditrk_refPK_nDof"};
  TTreeReaderValue<Double_t> dimuonditrk_refKP_nDof = {fReader, "dimuonditrk_refKP_nDof"};
  TTreeReaderValue<Double_t> dimuonditrk_refPP_nDof = {fReader, "dimuonditrk_refPP_nDof"};
  TTreeReaderValue<Double_t> dimuonditrk_refPK_vProb = {fReader, "dimuonditrk_refPK_vProb"};
  TTreeReaderValue<Double_t> dimuonditrk_refKP_vProb = {fReader, "dimuonditrk_refKP_vProb"};
  TTreeReaderValue<Double_t> dimuonditrk_refPP_vProb = {fReader, "dimuonditrk_refPP_vProb"};
  TTreeReaderValue<Double_t> dimuon_vProb = {fReader, "dimuon_vProb"};
  TTreeReaderValue<Double_t> dimuon_vChi2 = {fReader, "dimuon_vChi2"};
  TTreeReaderValue<Double_t> dimuon_DCA = {fReader, "dimuon_DCA"};
  TTreeReaderValue<Double_t> dimuon_ctauPV = {fReader, "dimuon_ctauPV"};
  TTreeReaderValue<Double_t> dimuon_ctauErrPV = {fReader, "dimuon_ctauErrPV"};
  TTreeReaderValue<Double_t> dimuon_cosAlpha = {fReader, "dimuon_cosAlpha"};
  TTreeReaderValue<Int_t> dimuon_triggerMatch = {fReader, "dimuon_triggerMatch"};
  TTreeReaderValue<Double_t> dimuonditrk_vProb = {fReader, "dimuonditrk_vProb"};
  TTreeReaderValue<Double_t> dimuonditrk_vChi2 = {fReader, "dimuonditrk_vChi2"};
  TTreeReaderValue<Double_t> dimuonditrk_nDof = {fReader, "dimuonditrk_nDof"};
  TTreeReaderValue<Int_t> dimuonditrk_charge = {fReader, "dimuonditrk_charge"};
  TTreeReaderValue<Double_t> dimuonditrk_cosAlpha = {fReader, "dimuonditrk_cosAlpha"};
  TTreeReaderValue<Double_t> dimuonditrk_ctauPV = {fReader, "dimuonditrk_ctauPV"};
  TTreeReaderValue<Double_t> dimuonditrk_ctauErrPV = {fReader, "dimuonditrk_ctauErrPV"};
  TTreeReaderValue<Double_t> dimuonditrk_tPFromPV = {fReader, "dimuonditrk_tPFromPV"};
  TTreeReaderValue<Double_t> dimuonditrk_tMFromPV = {fReader, "dimuonditrk_tMFromPV"};
  TTreeReaderValue<Double_t> dimuonditrk_cosAlphaDZ = {fReader, "dimuonditrk_cosAlphaDZ"};
  TTreeReaderValue<Double_t> dimuonditrk_ctauPVDZ = {fReader, "dimuonditrk_ctauPVDZ"};
  TTreeReaderValue<Double_t> dimuonditrk_ctauErrPVDZ = {fReader, "dimuonditrk_ctauErrPVDZ"};
  TTreeReaderValue<Double_t> dimuonditrk_tPFromPVDZ = {fReader, "dimuonditrk_tPFromPVDZ"};
  TTreeReaderValue<Double_t> dimuonditrk_tMFromPVDZ = {fReader, "dimuonditrk_tMFromPVDZ"};
  TTreeReaderValue<Double_t> dimuonditrk_cosAlphaBS = {fReader, "dimuonditrk_cosAlphaBS"};
  TTreeReaderValue<Double_t> dimuonditrk_ctauPVBS = {fReader, "dimuonditrk_ctauPVBS"};
  TTreeReaderValue<Double_t> dimuonditrk_ctauErrPVBS = {fReader, "dimuonditrk_ctauErrPVBS"};
  TTreeReaderValue<Double_t> dimuonditrk_tPFromPVBS = {fReader, "dimuonditrk_tPFromPVBS"};
  TTreeReaderValue<Double_t> dimuonditrk_tMFromPVBS = {fReader, "dimuonditrk_tMFromPVBS"};
  TTreeReaderValue<Double_t> dimuonditrk_dca_m1m2 = {fReader, "dimuonditrk_dca_m1m2"};
  TTreeReaderValue<Double_t> dimuonditrk_dca_m1t1 = {fReader, "dimuonditrk_dca_m1t1"};
  TTreeReaderValue<Double_t> dimuonditrk_dca_m1t2 = {fReader, "dimuonditrk_dca_m1t2"};
  TTreeReaderValue<Double_t> dimuonditrk_dca_m2t1 = {fReader, "dimuonditrk_dca_m2t1"};
  TTreeReaderValue<Double_t> dimuonditrk_dca_m2t2 = {fReader, "dimuonditrk_dca_m2t2"};
  TTreeReaderValue<Double_t> dimuonditrk_dca_t1t2 = {fReader, "dimuonditrk_dca_t1t2"};
  TTreeReaderValue<Double_t> dimuonditrk_rf_vProb = {fReader, "dimuonditrk_rf_vProb"};
  TTreeReaderValue<Double_t> dimuonditrk_rf_vChi2 = {fReader, "dimuonditrk_rf_vChi2"};
  TTreeReaderValue<Double_t> dimuonditrk_rf_nDof = {fReader, "dimuonditrk_rf_nDof"};
  TTreeReaderValue<Double_t> dimuonditrk_rf_cosAlpha = {fReader, "dimuonditrk_rf_cosAlpha"};
  TTreeReaderValue<Double_t> dimuonditrk_rf_ctauPV = {fReader, "dimuonditrk_rf_ctauPV"};
  TTreeReaderValue<Double_t> dimuonditrk_rf_ctauErrPV = {fReader, "dimuonditrk_rf_ctauErrPV"};
  TTreeReaderValue<Double_t> dimuonditrk_rf_c_vProb = {fReader, "dimuonditrk_rf_c_vProb"};
  TTreeReaderValue<Double_t> dimuonditrk_rf_c_vChi2 = {fReader, "dimuonditrk_rf_c_vChi2"};
  TTreeReaderValue<Double_t> dimuonditrk_rf_c_nDof = {fReader, "dimuonditrk_rf_c_nDof"};
  TTreeReaderValue<Double_t> dimuonditrk_rf_c_cosAlpha = {fReader, "dimuonditrk_rf_c_cosAlpha"};
  TTreeReaderValue<Double_t> dimuonditrk_rf_c_ctauPV = {fReader, "dimuonditrk_rf_c_ctauPV"};
  TTreeReaderValue<Double_t> dimuonditrk_rf_c_ctauErrPV = {fReader, "dimuonditrk_rf_c_ctauErrPV"};
  TTreeReaderValue<Int_t> highKaonMatch = {fReader, "highKaonMatch"};
  TTreeReaderValue<Int_t> lowKaonMatch = {fReader, "lowKaonMatch"};
  TTreeReaderValue<Int_t> lowMuonMatch = {fReader, "lowMuonMatch"};
  TTreeReaderValue<Int_t> highMuonMatch = {fReader, "highMuonMatch"};
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
  TTreeReaderValue<Int_t> highKaon_NPixelHits = {fReader, "highKaon_NPixelHits"};
  TTreeReaderValue<Int_t> highKaon_NStripHits = {fReader, "highKaon_NStripHits"};
  TTreeReaderValue<Int_t> highKaon_NTrackhits = {fReader, "highKaon_NTrackhits"};
  TTreeReaderValue<Int_t> highKaon_NBPixHits = {fReader, "highKaon_NBPixHits"};
  TTreeReaderValue<Int_t> highKaon_NPixLayers = {fReader, "highKaon_NPixLayers"};
  TTreeReaderValue<Int_t> highKaon_NTraLayers = {fReader, "highKaon_NTraLayers"};
  TTreeReaderValue<Int_t> highKaon_NStrLayers = {fReader, "highKaon_NStrLayers"};
  TTreeReaderValue<Int_t> highKaon_NBPixLayers = {fReader, "highKaon_NBPixLayers"};
  TTreeReaderValue<Int_t> lowKaon_NPixelHits = {fReader, "lowKaon_NPixelHits"};
  TTreeReaderValue<Int_t> lowKaon_NStripHits = {fReader, "lowKaon_NStripHits"};
  TTreeReaderValue<Int_t> lowKaon_NTrackhits = {fReader, "lowKaon_NTrackhits"};
  TTreeReaderValue<Int_t> lowKaon_NBPixHits = {fReader, "lowKaon_NBPixHits"};
  TTreeReaderValue<Int_t> lowKaon_NPixLayers = {fReader, "lowKaon_NPixLayers"};
  TTreeReaderValue<Int_t> lowKaon_NTraLayers = {fReader, "lowKaon_NTraLayers"};
  TTreeReaderValue<Int_t> lowKaon_NStrLayers = {fReader, "lowKaon_NStrLayers"};
  TTreeReaderValue<Int_t> lowKaon_NBPixLayers = {fReader, "lowKaon_NBPixLayers"};

  TTreeReaderValue<Bool_t> isBestCandidate = {fReader, "isBestCandidate"};

  // In data the gen variables are empty and if
  // uncommented rise conflicts in PROOF
  // (it seems it douesn't like empty leaves)

  /*
  TTreeReaderValue<TLorentzVector> gen_dimuonditrk_p4 = {fReader, "gen_dimuonditrk_p4"};
  TTreeReaderValue<TLorentzVector> gen_jpsi_p4 = {fReader, "gen_jpsi_p4"};
  TTreeReaderValue<TLorentzVector> gen_phi_p4 = {fReader, "gen_phi_p4"};
  TTreeReaderValue<TLorentzVector> gen_highKaon_p4 = {fReader, "gen_highKaon_p4"};
  TTreeReaderValue<TLorentzVector> gen_lowMuon_p4 = {fReader, "gen_lowMuon_p4"};
  TTreeReaderValue<TLorentzVector> gen_highMuon_p4 = {fReader, "gen_highMuon_p4"};
  TTreeReaderValue<TLorentzVector> gen_lowKaon_p4 = {fReader, "gen_lowKaon_p4"};

  TTreeReaderValue<Double_t> gen_dimuonditrk_pdg = {fReader, "gen_dimuonditrk_pdg"};
  TTreeReaderValue<Double_t> gen_phi_pdg = {fReader, "gen_phi_pdg"};
  TTreeReaderValue<Double_t> gen_jpsi_pdg = {fReader, "gen_jpsi_pdg"};
  TTreeReaderValue<Double_t> gen_lowMuon_pdg = {fReader, "gen_lowMuon_pdg"};
  TTreeReaderValue<Double_t> gen_highMuon_pdg = {fReader, "gen_highMuon_pdg"};
  TTreeReaderValue<Double_t> gen_highKaon_pdg = {fReader, "gen_highKaon_pdg"};
  TTreeReaderValue<Double_t> gen_lowKaon_pdg = {fReader, "gen_lowKaon_pdg"};
  TTreeReaderValue<Double_t> gen_lowMuon_mompdg = {fReader, "gen_lowMuon_mompdg"};
  TTreeReaderValue<Double_t> gen_highMuon_mompdg = {fReader, "gen_highMuon_mompdg"};
  TTreeReaderValue<Double_t> gen_highKaon_mompdg = {fReader, "gen_highKaon_mompdg"};
  TTreeReaderValue<Double_t> gen_lowKaon_mompdg = {fReader, "gen_lowKaon_mompdg"};
  TTreeReaderValue<Double_t> gen_lowMuon_status = {fReader, "gen_lowMuon_status"};
  TTreeReaderValue<Double_t> gen_highMuon_status = {fReader, "gen_highMuon_status"};
  TTreeReaderValue<Double_t> gen_highKaon_status = {fReader, "gen_highKaon_status"};
  TTreeReaderValue<Double_t> gen_lowKaon_status = {fReader, "gen_lowKaon_status"};
  TTreeReaderValue<Double_t> gen_lowMuon_p = {fReader, "gen_lowMuon_p"};
  TTreeReaderValue<Double_t> gen_highMuon_p = {fReader, "gen_highMuon_p"};
  TTreeReaderValue<Double_t> gen_highKaon_p = {fReader, "gen_highKaon_p"};
  TTreeReaderValue<Double_t> gen_lowKaon_p = {fReader, "gen_lowKaon_p"};
  TTreeReaderValue<Double_t> gen_lowMuon_pt = {fReader, "gen_lowMuon_pt"};
  TTreeReaderValue<Double_t> gen_highMuon_pt = {fReader, "gen_highMuon_pt"};
  TTreeReaderValue<Double_t> gen_highKaon_pt = {fReader, "gen_highKaon_pt"};
  TTreeReaderValue<Double_t> gen_lowKaon_pt = {fReader, "gen_lowKaon_pt"};
  TTreeReaderValue<Double_t> gen_lowMuon_eta = {fReader, "gen_lowMuon_eta"};
  TTreeReaderValue<Double_t> gen_highMuon_eta = {fReader, "gen_highMuon_eta"};
  TTreeReaderValue<Double_t> gen_highKaon_eta = {fReader, "gen_highKaon_eta"};
  TTreeReaderValue<Double_t> gen_lowKaon_eta = {fReader, "gen_lowKaon_eta"};
  TTreeReaderValue<Double_t> gen_lowMuon_phi = {fReader, "gen_lowMuon_phi"};
  TTreeReaderValue<Double_t> gen_highMuon_phi = {fReader, "gen_highMuon_phi"};
  TTreeReaderValue<Double_t> gen_highKaon_phi = {fReader, "gen_highKaon_phi"};
  TTreeReaderValue<Double_t> gen_lowKaon_phi = {fReader, "gen_lowKaon_phi"};
  TTreeReaderValue<Double_t> gen_dimuonditrk_prompt = {fReader, "gen_dimuonditrk_prompt"};
  TTreeReaderValue<Double_t> gen_phi_prompt = {fReader, "gen_phi_prompt"};
  TTreeReaderValue<Double_t> gen_jpsi_prompt = {fReader, "gen_jpsi_prompt"};
  TTreeReaderValue<Double_t> gen_dimuonditrk_pt = {fReader, "gen_dimuonditrk_pt"};
  TTreeReaderValue<Double_t> phigen_phi_pt_pt = {fReader, "gen_phi_pt"};
  TTreeReaderValue<Double_t> gen_jpsi_pt = {fReader, "gen_jpsi_pt"};
  TTreeReaderValue<Double_t> gen_dimuonditrk_p = {fReader, "gen_dimuonditrk_p"};
  TTreeReaderValue<Double_t> phigen_phi_p_p = {fReader, "gen_phi_p"};
  TTreeReaderValue<Double_t> gen_jpsi_p = {fReader, "gen_jpsi_p"};
  TTreeReaderValue<Double_t> gen_dimuonditrk_eta = {fReader, "gen_dimuonditrk_eta"};
  TTreeReaderValue<Double_t> gen_phi_eta = {fReader, "gen_phi_eta"};
  TTreeReaderValue<Double_t> gen_jpsi_eta = {fReader, "gen_jpsi_eta"};
  TTreeReaderValue<Double_t> gen_dimuonditrk_phi = {fReader, "gen_dimuonditrk_phi"};
  TTreeReaderValue<Double_t> gen_phi_phi = {fReader, "gen_phi_phi"};
  TTreeReaderValue<Double_t> gen_jpsi_phi = {fReader, "gen_jpsi_phi"};
  */


  //Output variables
  Float_t out_run, out_event, out_lumi, out_numPrimaryVertices, out_trigger;

  Float_t out_dimuonditrk_vProb, out_out_dimuonditrk_vChi2;
  Float_t out_dimuonditrk_rf_vProb, out_dimuonditrk_rf_vChi2, out_dimuonditrk_rf_nDof, out_dimuonditrk_rf_cosAlpha, out_dimuonditrk_rf_ctauPV, out_dimuonditrk_rf_ctauErrPV;
  Float_t out_dimuonditrk_rf_c_vProb, out_dimuonditrk_rf_c_vChi2, out_dimuonditrk_rf_c_nDof, out_dimuonditrk_rf_c_cosAlpha, out_dimuonditrk_rf_c_ctauPV, out_dimuonditrk_rf_c_ctauErrPV;
  Float_t out_dimuonditrk_pt, out_dimuonditrk_eta, out_dimuonditrk_phi, out_dimuonditrk_y, out_dimuonditrk_vx, out_dimuonditrk_vy, out_dimuonditrk_vz;

  Float_t out_pv_x, out_pv_y, out_pv_z;

  Float_t out_dimuon_triggerMatch, out_dimuonditrk_vChi2, out_dimuonditrk_charge;

  Float_t out_dimuonditrk_cosAlpha, out_dimuonditrk_ctauPV, out_dimuonditrk_ctauErrPV, out_dimuonditrk_countTksOfPV, out_dimuonditrk_vertexWeight;
  Float_t out_dimuonditrk_sumPTPV, out_dimuonditrk_mu1FromPV, out_dimuonditrk_mu2FromPV, out_dimuonditrk_tPFromPV, out_dimuonditrk_tMFromPV;
  Float_t out_dimuonditrk_mu1W, out_dimuonditrk_mu2W, out_dimuonditrk_tPW, out_dimuonditrk_tMW;

  Float_t out_dimuonditrk_cosAlphaDZ, out_dimuonditrk_ctauPVDZ, out_dimuonditrk_ctauErrPVDZ, out_dimuonditrk_countTksOfPVDZ, out_dimuonditrk_vertexWeightDZ;
  Float_t out_dimuonditrk_sumPTPVDZ, out_dimuonditrk_mu1FromPVDZ, out_dimuonditrk_mu2FromPVDZ, out_dimuonditrk_tPFromPVDZ, out_dimuonditrk_tMFromPVDZ;
  Float_t out_dimuonditrk_mu1DZW, out_dimuonditrk_mu2DZW, out_dimuonditrk_tPDZW, out_dimuonditrk_tMDZW;

  Float_t out_dimuonditrk_cosAlphaBS, out_dimuonditrk_ctauPVBS, out_dimuonditrk_ctauErrPVBS, out_dimuonditrk_countTksOfPVBS, out_dimuonditrk_vertexWeightBS;
  Float_t out_dimuonditrk_sumPTPVBS, out_dimuonditrk_mu1FromPVBS, out_dimuonditrk_mu2FromPVBS, out_dimuonditrk_tPFromPVBS, out_dimuonditrk_tMFromPVBS;
  Float_t out_dimuonditrk_mu1BSW, out_dimuonditrk_mu2BSW, out_dimuonditrk_tPBSW, out_dimuonditrk_tMBSW;

  Float_t out_dimuonditrk_dca_m1m2, out_dimuonditrk_dca_m1t1, out_dimuonditrk_dca_m1t2, out_dimuonditrk_dca_m2t1, out_dimuonditrk_dca_m2t2, out_dimuonditrk_dca_t1t2;
  Float_t out_dimuon_vProb, out_dimuon_vChi2, out_dimuon_DCA, out_dimuon_ctauPV, out_dimuon_ctauErrPV, out_dimuon_cosAlpha;

  Float_t out_gen_dimuonditrk_m, out_dimuonditrk_m, out_dimuon_m, out_dimuon_pt, out_ditrak_m, out_ditrak_pt;
  Float_t out_highKaon_pt, out_lowKaon_pt, out_highMuon_pt, out_lowMuon_pt, out_dimuonditrk_nDof, out_dimuonditrk_m_rf, out_dimuonditrk_m_rf_c, out_dimuonditrk_m_rf_d_c;

  Float_t out_lowMuon_isLoose, out_lowMuon_isSoft, out_lowMuon_isMedium, out_lowMuon_isHighPt, out_lowMuon_isTight;
  Float_t out_highMuon_isLoose, out_highMuon_isSoft, out_highMuon_isMedium, out_highMuon_isHighPt, out_highMuon_isTight;

  Float_t out_lowMuon_isTracker, out_lowMuon_isGlobal, out_highMuon_isTracker, out_highMuon_isGlobal;
  Float_t out_lowMuon_type, out_highMuon_type;

  Float_t out_lowMuon_rf_isLoose, out_lowMuon_rf_isSoft, out_lowMuon_rf_isMedium, out_lowMuon_rf_isHighPt;
  Float_t out_highMuon_rf_isLoose, out_highMuon_rf_isSoft, out_highMuon_rf_isMedium, out_highMuon_rf_isHighPt;

  Float_t out_lowMuon_rf_isTracker, out_lowMuon_rf_isGlobal, out_highMuon_rf_isTracker, out_highMuon_rf_isGlobal;
  Float_t out_lowMuon_rf_type, out_highMuon_rf_type;

  Float_t out_lowMuon_NPixelHits, out_lowMuon_NStripHits, out_lowMuon_NTrackhits, out_lowMuon_NBPixHits, out_lowMuon_NPixLayers, out_lowMuon_NTraLayers, out_lowMuon_NStrLayers, out_lowMuon_NBPixLayers;
  Float_t out_highMuon_NPixelHits, out_highMuon_NStripHits, out_highMuon_NTrackhits, out_highMuon_NBPixHits, out_highMuon_NPixLayers, out_highMuon_NTraLayers, out_highMuon_NStrLayers, out_highMuon_NBPixLayers;

  Float_t out_dimuonditrk_refPK_mass, out_dimuonditrk_refKP_mass, out_dimuonditrk_refPP_mass, out_dimuonditrk_refPK_vChi2;
  Float_t out_dimuonditrk_refKP_vChi2, out_dimuonditrk_refPP_vChi2, out_dimuonditrk_refPK_nDof, out_dimuonditrk_refKP_nDof;
  Float_t out_dimuonditrk_refPP_nDof, out_dimuonditrk_refPK_vProb, out_dimuonditrk_refKP_vProb, out_dimuonditrk_refPP_vProb;

  Float_t out_highKaon_eta, out_lowKaon_eta, out_highMuon_eta, out_lowMuon_eta, out_highKaon_phi, out_lowKaon_phi, out_highMuon_phi, out_lowMuon_phi;
  Float_t out_highKaon_dz, out_lowKaon_dz, out_highMuon_dz, out_lowMuon_dz, out_highKaon_dxy, out_lowKaon_dxy, out_highMuon_dxy, out_lowMuon_dxy;

  Float_t out_highKaon_NPixelHits, out_highKaon_NStripHits, out_highKaon_NTrackhits, out_highKaon_NBPixHits, out_highKaon_NPixLayers;
  Float_t out_highKaon_NTraLayers, out_highKaon_NStrLayers, out_highKaon_NBPixLayers, out_lowKaon_NPixelHits, out_lowKaon_NStripHits;
  Float_t out_lowKaon_NTrackhits, out_lowKaon_NBPixHits, out_lowKaon_NPixLayers, out_lowKaon_NTraLayers, out_lowKaon_NStrLayers, out_lowKaon_NBPixLayers;

  Float_t out_highKaonMatch, out_lowKaonMatch, out_lowMuonMatch, out_highMuonMatch;

  Float_t out_dimuonditrk_rf_bindx;

  Float_t out_noXCandidates;

  Float_t out_isBestCandidate;

  TwoMuTwoK(TTree * /*tree*/ =0) { }
  virtual ~TwoMuTwoK() { }
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

  ClassDef(TwoMuTwoK,0);

};

#endif

#ifdef TwoMuTwoK_cxx
void TwoMuTwoK::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the reader is initialized.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  fReader.SetTree(tree);
}

Bool_t TwoMuTwoK::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}


#endif // #ifdef TwoMuTwoK_cxx
