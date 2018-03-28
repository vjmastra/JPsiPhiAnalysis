// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include <DataFormats/TrackReco/interface/TrackFwd.h>
#include <DataFormats/TrackReco/interface/Track.h>
#include <DataFormats/PatCandidates/interface/UserData.h>
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/PatternTools/interface/TwoTrackMinimumDistance.h"
#include "TrackingTools/IPTools/interface/IPTools.h"
#include "TrackingTools/PatternTools/interface/ClosestApproachInRPhi.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/VertexTools/interface/VertexDistanceXY.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "TMath.h"
#include "Math/VectorUtil.h"
#include "TVector3.h"

#include "RecoVertex/VertexTools/interface/InvariantMassFromVertex.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TLorentzVector.h"
#include "TTree.h"

//
// class declaration
//

class DiMuonDiTrakMLAnalyzer:public edm::EDAnalyzer {
      public:
	explicit DiMuonDiTrakMLAnalyzer(const edm::ParameterSet &);
	~DiMuonDiTrakMLAnalyzer() override;

	static void fillDescriptions(edm::ConfigurationDescriptions & descriptions);

      private:
        UInt_t getTriggerBits(const edm::Event &);
        bool   isAncestor(const reco::Candidate *, const reco::Candidate *);
        const  reco::Candidate* GetAncestor(const reco::Candidate *);

	void beginJob() override;
	void analyze(const edm::Event &, const edm::EventSetup &) override;
	void endJob() override;

	void beginRun(edm::Run const &, edm::EventSetup const &) override;
	void endRun(edm::Run const &, edm::EventSetup const &) override;
	void beginLuminosityBlock(edm::LuminosityBlock const &, edm::EventSetup const &) override;
	void endLuminosityBlock(edm::LuminosityBlock const &, edm::EventSetup const &) override;

	// ----------member data ---------------------------
	std::string file_name;
  edm::EDGetTokenT<reco::MuonCollection> muons_;
  edm::EDGetTokenT<reco::TrackCollection> traks_;
  edm::EDGetTokenT<reco::BeamSpot> thebeamspot_;
  edm::EDGetTokenT<reco::VertexCollection> thePVs_;
  edm::EDGetTokenT<edm::TriggerResults> triggerResults_;
  std::vector<double> DiMuonMassCuts_;
  std::vector<double> DiTrakMassCuts_;
  std::vector<double> DiMuonDiTrakMassCuts_;
  std::vector<double> massCands_;

  float muon_mass;
  bool addTrigger_;
  bool OnlyBest_;
  std::vector<std::string>  HLTs_;
  std::vector<std::string>  HLTFilters_;

	UInt_t    run;
	ULong64_t event;
  UInt_t    lumiblock;
  UInt_t    nditrak;
  UInt_t    trigger;
  Int_t     charge;

	TLorentzVector ditrak_p4;
	TLorentzVector trakP_p4;
	TLorentzVector trakN_p4;

  std::vector < Float_t > trigs_pt;
  std::vector < Float_t > trigs_eta;
  std::vector < Float_t > trigs_phi;
  std::vector < Float_t > trigs_m;
  std::vector < UInt_t > trigs_filters;

  Bool_t isBest;

  Float_t MassErr;
  Float_t vProb;
  Float_t DCA;
  Float_t ctauPV;
  Float_t ctauErrPV;
  Float_t cosAlpha;
  Float_t lxyPV;
  Float_t lxyErrPV;

	UInt_t numPrimaryVertices;

	TTree *ml_tree;

  InvariantMassFromVertex massCalculator;

};
