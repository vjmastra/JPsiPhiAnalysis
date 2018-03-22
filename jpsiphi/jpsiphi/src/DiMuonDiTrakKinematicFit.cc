// -*- C++ -*-
//
// Package:    DiMuonDiTrakKinematicFit
// Class:      DiMuonDiTrakKinematicFit
//
/**\class DiMuonDiTrakKinematicFit jpsiphi/jpsiphi/src/DiMuonDiTrakKinematicFit.cc

 Description: performs vertex kinematical fit for DiMuon-DiTrack

**/
//
// Original Author:  Adriano Di Florio
//         Created:  Based on Alberto Sanchez Hernandez PsiTrkTrk Code

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

///For kinematic fit:
#include <DataFormats/PatCandidates/interface/Muon.h>
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/PatCandidates/interface/UserData.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"


#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "CommonTools/Statistics/interface/ChiSquaredProbability.h"

#include "RecoVertex/KinematicFit/interface/KinematicParticleVertexFitter.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticleFactoryFromTransientTrack.h"
#include "RecoVertex/KinematicFit/interface/MassKinematicConstraint.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleFitter.h"
#include "RecoVertex/KinematicFitPrimitives/interface/MultiTrackKinematicConstraint.h"
#include "RecoVertex/KinematicFit/interface/KinematicConstrainedVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/TwoTrackMassKinematicConstraint.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/RefCountedKinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/TransientTrackKinematicParticle.h"

#include "RecoVertex/VertexTools/interface/VertexDistanceXY.h"
#include "TMath.h"
#include "Math/VectorUtil.h"
#include "TVector3.h"
#include <DataFormats/VertexReco/interface/VertexFwd.h>

#include <boost/foreach.hpp>
#include <string>

//
// class declaration
//

class DiMuonDiTrakKinematicFit : public edm::EDProducer {
   public:
      explicit DiMuonDiTrakKinematicFit(const edm::ParameterSet&);
      ~DiMuonDiTrakKinematicFit() override;

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      void beginJob() override ;
      void produce(edm::Event&, const edm::EventSetup&) override;
      void endJob() override ;

      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

// ----------member data ---------------------------
  edm::EDGetTokenT<pat::CompositeCandidateCollection> DiMuonTTCand_;
  double DiMuonMass_;
  std::vector<double> DiMuonTTMassCuts_;
  std::vector<double> MassTraks_;
  std::string Product_name_;

  template<typename T>
  struct GreaterByVProb {
     typedef T first_argument_type;
     typedef T second_argument_type;
     bool operator()( const T & t1, const T & t2 ) const {
        return t1.userFloat("vProb") > t2.userFloat("vProb");
     }
  };
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DiMuonDiTrakKinematicFit::DiMuonDiTrakKinematicFit(const edm::ParameterSet& iConfig) {
  DiMuonTTCand_       = consumes<pat::CompositeCandidateCollection>(iConfig.getParameter<edm::InputTag>("DiMuonDiTrak"));
  DiMuonMass_         = iConfig.getParameter<double>("DiMuonMass");
  DiMuonTTMassCuts_   = iConfig.getParameter<std::vector<double>>("DiMuonTrakTrakMassCuts");
  MassTraks_          = iConfig.getParameter<std::vector<double>>("MassTraks");
  Product_name_       = iConfig.getParameter<std::string>("Product");

// kinematic refit collections
  produces<pat::CompositeCandidateCollection>(Product_name_);

// now do what ever other initialization is needed
}

DiMuonDiTrakKinematicFit::~DiMuonDiTrakKinematicFit() {
// do anything here that needs to be done at desctruction time
// (e.g. close files, deallocate resources etc.)
}

//
// member functions
//

// ------------ method called to produce the data  ------------
void DiMuonDiTrakKinematicFit::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

  // Grab paramenters
  edm::Handle<pat::CompositeCandidateCollection> PsiTCandHandle;
  iEvent.getByToken(DiMuonTTCand_, PsiTCandHandle);

// Kinematic refit collection
  std::unique_ptr< pat::CompositeCandidateCollection > PsiTCandRefitColl(new pat::CompositeCandidateCollection);

// Kinematic fit
  edm::ESHandle<TransientTrackBuilder> theB;
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);

  int indexPsiT=-1;
  for (pat::CompositeCandidateCollection::const_iterator dimuontt=PsiTCandHandle->begin(); dimuontt!=PsiTCandHandle->end(); ++dimuontt) {

    const pat::CompositeCandidate *dimuonC = dynamic_cast<const pat::CompositeCandidate *>(dimuontt->daughter("dimuon"));
    const pat::CompositeCandidate *ditrakC = dynamic_cast<const pat::CompositeCandidate*>(dimuontt->daughter("ditrak"));

    if(dimuonC->userFloat("vProb")<0.0)
      continue;

    indexPsiT++;

    std::vector <reco::Track> JpsiTk;

    const pat::PackedCandidate *trakP = dynamic_cast<const pat::PackedCandidate*>(ditrakC->daughter("trakP"));
    const pat::PackedCandidate *trakN = dynamic_cast<const pat::PackedCandidate*>(ditrakC->daughter("trakN"));

    JpsiTk.push_back(*( dynamic_cast<const pat::Muon*>(dimuontt->daughter("dimuon")->daughter("muon1") ) )->innerTrack());
    JpsiTk.push_back(*( dynamic_cast<const pat::Muon*>(dimuontt->daughter("dimuon")->daughter("muon2") ) )->innerTrack());

    std::vector<reco::TransientTrack> MuMuTT;
    MuMuTT.push_back((*theB).build(&JpsiTk[0]));
    MuMuTT.push_back((*theB).build(&JpsiTk[1]));

    if(!trakP->hasTrackDetails())
      continue;
    else if(trakP->bestTrack())
      MuMuTT.push_back((*theB).build(*(trakP->bestTrack()))); // K+
    else
      MuMuTT.push_back((*theB).build((trakP->pseudoTrack()))); // K+


    if(!trakN->hasTrackDetails())
      continue;
    else if(trakN->bestTrack())
      MuMuTT.push_back((*theB).build(*(trakN->bestTrack()))); // K+
    else
      MuMuTT.push_back((*theB).build((trakN->pseudoTrack()))); // K+

    const reco::Vertex thePrimaryV = *dimuonC->userData<reco::Vertex>("PVwithmuons");

    KinematicParticleFactoryFromTransientTrack pFactory;

    const ParticleMass muonMass(0.1056583);
    float muonSigma = muonMass*1E-6;
    const ParticleMass trakMass1(MassTraks_[0]);
    float trakSigma1 = trakMass1*1E-6;
    const ParticleMass trakMass2(MassTraks_[1]);
    float trakSigma2 = trakMass2*1E-6;

    std::vector<RefCountedKinematicParticle> allPsiTDaughters;
    allPsiTDaughters.push_back(pFactory.particle (MuMuTT[0], muonMass, float(0), float(0), muonSigma));
    allPsiTDaughters.push_back(pFactory.particle (MuMuTT[1], muonMass, float(0), float(0), muonSigma));
    allPsiTDaughters.push_back(pFactory.particle (MuMuTT[2], trakMass1, float(0), float(0), trakSigma1));
    allPsiTDaughters.push_back(pFactory.particle (MuMuTT[3], trakMass2, float(0), float(0), trakSigma2));

    KinematicConstrainedVertexFitter constVertexFitter;
    MultiTrackKinematicConstraint *dimuon_mtc = new  TwoTrackMassKinematicConstraint(DiMuonMass_);
    RefCountedKinematicTree PsiTTree = constVertexFitter.fit(allPsiTDaughters,dimuon_mtc);

    if (!PsiTTree->isEmpty()) {
       PsiTTree->movePointerToTheTop();
       RefCountedKinematicParticle fitPsiT = PsiTTree->currentParticle();
       RefCountedKinematicVertex PsiTDecayVertex = PsiTTree->currentDecayVertex();
// Get PsiT reffited
       double dimuontt_ma_fit = 14000.;
       double dimuontt_vp_fit = -9999.;
       double dimuontt_x2_fit = 10000.;

       if (fitPsiT->currentState().isValid()) {
         dimuontt_ma_fit = fitPsiT->currentState().mass();
         dimuontt_x2_fit = PsiTDecayVertex->chiSquared();
         dimuontt_vp_fit = ChiSquaredProbability(dimuontt_x2_fit,
                                              (double)(PsiTDecayVertex->degreesOfFreedom()));
       }

       if ( dimuontt_ma_fit > DiMuonTTMassCuts_[0] && dimuontt_ma_fit < DiMuonTTMassCuts_[1] && dimuontt_vp_fit > 0.0 ) {
            TVector3 vtx;
            TVector3 pvtx;
            VertexDistanceXY vdistXY;
            int   dimuontt_ch_fit = dimuontt->charge();
            double dimuontt_px_fit = fitPsiT->currentState().kinematicParameters().momentum().x();
            double dimuontt_py_fit = fitPsiT->currentState().kinematicParameters().momentum().y();
            double dimuontt_pz_fit = fitPsiT->currentState().kinematicParameters().momentum().z();
            double dimuontt_en_fit = sqrt(dimuontt_ma_fit*dimuontt_ma_fit+dimuontt_px_fit*dimuontt_px_fit+
                                      dimuontt_py_fit*dimuontt_py_fit+dimuontt_pz_fit*dimuontt_pz_fit);
            double dimuontt_vx_fit = PsiTDecayVertex->position().x();
	          double dimuontt_vy_fit = PsiTDecayVertex->position().y();
            double dimuontt_vz_fit = PsiTDecayVertex->position().z();

            vtx.SetXYZ(dimuontt_vx_fit,dimuontt_vy_fit,0);
            TVector3 pperp(dimuontt_px_fit, dimuontt_py_fit, 0);
            AlgebraicVector3 vpperp(pperp.x(),pperp.y(),0);
            pvtx.SetXYZ(thePrimaryV.position().x(),thePrimaryV.position().y(),0);
            TVector3 vdiff = vtx - pvtx;
            double cosAlpha = vdiff.Dot(pperp)/(vdiff.Perp()*pperp.Perp());
            Measurement1D distXY = vdistXY.distance(reco::Vertex(*PsiTDecayVertex), thePrimaryV);
            double ctauPV = distXY.value()*cosAlpha * dimuontt_ma_fit/pperp.Perp();
            GlobalError v1e = (reco::Vertex(*PsiTDecayVertex)).error();
            GlobalError v2e = thePrimaryV.error();
            AlgebraicSymMatrix33 vXYe = v1e.matrix()+ v2e.matrix();
            double ctauErrPV = sqrt(ROOT::Math::Similarity(vpperp,vXYe))*dimuontt_ma_fit/(pperp.Perp2());

	    reco::CompositeCandidate recoPsiT(dimuontt_ch_fit,math::XYZTLorentzVector(dimuontt_px_fit,dimuontt_py_fit,dimuontt_pz_fit,dimuontt_en_fit),
                                               math::XYZPoint(dimuontt_vx_fit,dimuontt_vy_fit,dimuontt_vz_fit),531);
	    pat::CompositeCandidate patPsiT(recoPsiT);
            patPsiT.addUserFloat("vProb",dimuontt_vp_fit);
            patPsiT.addUserFloat("vChi2",dimuontt_x2_fit);
            patPsiT.addUserFloat("cosAlpha",cosAlpha);
            patPsiT.addUserFloat("ctauPV",ctauPV);
            patPsiT.addUserFloat("ctauErrPV",ctauErrPV);
            patPsiT.addUserFloat("tPMatch",PsiTCandHandle->userInt("tPMatch"));
            patPsiT.addUserFloat("tNMatch",PsiTCandHandle->userInt("tNMatch"));

            patPsiT.addUserInt("bIndex",indexPsiT);

// get first muon
            bool child = PsiTTree->movePointerToTheFirstChild();
            RefCountedKinematicParticle fitMu1 = PsiTTree->currentParticle();
            if (!child) break;
            float m1_ma_fit = fitMu1->currentState().mass();
            int   m1_ch_fit = fitMu1->currentState().particleCharge();
            float m1_px_fit = fitMu1->currentState().kinematicParameters().momentum().x();
            float m1_py_fit = fitMu1->currentState().kinematicParameters().momentum().y();
            float m1_pz_fit = fitMu1->currentState().kinematicParameters().momentum().z();
            float m1_en_fit = sqrt(m1_ma_fit*m1_ma_fit+m1_px_fit*m1_px_fit+m1_py_fit*m1_py_fit+m1_pz_fit*m1_pz_fit);
            reco::CompositeCandidate recoMu1(m1_ch_fit,math::XYZTLorentzVector(m1_px_fit,m1_py_fit,m1_pz_fit,m1_en_fit),
                                             math::XYZPoint(dimuontt_vx_fit,dimuontt_vy_fit,dimuontt_vz_fit),13);
            pat::CompositeCandidate patMu1(recoMu1);
// get second muon
            child = PsiTTree->movePointerToTheNextChild();
            RefCountedKinematicParticle fitMu2 = PsiTTree->currentParticle();
            if (!child) break;
            float m2_ma_fit = fitMu2->currentState().mass();
            int   m2_ch_fit = fitMu2->currentState().particleCharge();
            float m2_px_fit = fitMu2->currentState().kinematicParameters().momentum().x();
            float m2_py_fit = fitMu2->currentState().kinematicParameters().momentum().y();
            float m2_pz_fit = fitMu2->currentState().kinematicParameters().momentum().z();
            float m2_en_fit = sqrt(m2_ma_fit*m2_ma_fit+m2_px_fit*m2_px_fit+m2_py_fit*m2_py_fit+m2_pz_fit*m2_pz_fit);
            reco::CompositeCandidate recoMu2(m2_ch_fit,math::XYZTLorentzVector(m2_px_fit,m2_py_fit,m2_pz_fit,m2_en_fit),
                                             math::XYZPoint(dimuontt_vx_fit,dimuontt_vy_fit,dimuontt_vz_fit),13);
            pat::CompositeCandidate patMu2(recoMu2);

// Define psi from two muons
	          pat::CompositeCandidate psi;
	          psi.addDaughter(patMu1,"muon1");
            psi.addDaughter(patMu2,"muon2");
            psi.setP4(patMu1.p4()+patMu2.p4());
// get kaon
            child = PsiTTree->movePointerToTheNextChild();
            RefCountedKinematicParticle fitTrk = PsiTTree->currentParticle();
            if (!child) break;
            float tk_ma_fit = fitTrk->currentState().mass();
            int   tk_ch_fit = fitTrk->currentState().particleCharge();
            float tk_px_fit = fitTrk->currentState().kinematicParameters().momentum().x();
            float tk_py_fit = fitTrk->currentState().kinematicParameters().momentum().y();
            float tk_pz_fit = fitTrk->currentState().kinematicParameters().momentum().z();
            float tk_en_fit = sqrt(tk_ma_fit*tk_ma_fit+tk_px_fit*tk_px_fit+tk_py_fit*tk_py_fit+tk_pz_fit*tk_pz_fit);
            reco::CompositeCandidate recoTk(tk_ch_fit,math::XYZTLorentzVector(tk_px_fit,tk_py_fit,tk_pz_fit,tk_en_fit),
                                             math::XYZPoint(dimuontt_vx_fit,dimuontt_vy_fit,dimuontt_vz_fit),321);
            pat::CompositeCandidate patTk(recoTk);

// get kaon2
            child = PsiTTree->movePointerToTheNextChild();
            RefCountedKinematicParticle fitTrk2 = PsiTTree->currentParticle();
            if (!child) break;
            float tk2_ma_fit = fitTrk2->currentState().mass();
            int   tk2_ch_fit = fitTrk2->currentState().particleCharge();
            float tk2_px_fit = fitTrk2->currentState().kinematicParameters().momentum().x();
            float tk2_py_fit = fitTrk2->currentState().kinematicParameters().momentum().y();
            float tk2_pz_fit = fitTrk2->currentState().kinematicParameters().momentum().z();
            float tk2_en_fit = sqrt(tk2_ma_fit*tk2_ma_fit+tk2_px_fit*tk2_px_fit+tk2_py_fit*tk2_py_fit+tk2_pz_fit*tk2_pz_fit);
            reco::CompositeCandidate recoTk2(tk2_ch_fit,math::XYZTLorentzVector(tk2_px_fit,tk2_py_fit,tk2_pz_fit,tk2_en_fit),
                                             math::XYZPoint(dimuontt_vx_fit,dimuontt_vy_fit,dimuontt_vz_fit),321);
            pat::CompositeCandidate patTk2(recoTk2);

// Define psi from two muons
            pat::CompositeCandidate phi;
            phi.addDaughter(patTk,"trakP");
            phi.addDaughter(patTk2,"trakN");
            phi.setP4(patTk.p4()+patTk2.p4());

	          patPsiT.addDaughter(psi,"dimuon");
	          patPsiT.addDaughter(phi,"ditrak");

            PsiTCandRefitColl->push_back(patPsiT);
          }
	}
  }
// End kinematic fit

// now sort by vProb
  DiMuonDiTrakKinematicFit::GreaterByVProb<pat::CompositeCandidate> vPComparator;
  std::sort(PsiTCandRefitColl->begin(),PsiTCandRefitColl->end(),vPComparator);

  iEvent.put(std::move(PsiTCandRefitColl),Product_name_);
  // std::cout << "PsiTCandRefitColl size: "<< PsiTCandRefitColl->size()<<std::endl;
}

// ------------ method called once each job just before starting event loop  ------------
void DiMuonDiTrakKinematicFit::beginJob() {}

// ------------ method called once each job just after ending the event loop  ------------
void DiMuonDiTrakKinematicFit::endJob() {}

// ------------ method called when starting to processes a run  ------------
void DiMuonDiTrakKinematicFit::beginRun(edm::Run&, edm::EventSetup const&) {}

// ------------ method called when ending the processing of a run  ------------
void DiMuonDiTrakKinematicFit::endRun(edm::Run&, edm::EventSetup const&) {}

// ------------ method called when starting to processes a luminosity block  ------------
void DiMuonDiTrakKinematicFit::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&) {}

// ------------ method called when ending the processing of a luminosity block  ------------
void DiMuonDiTrakKinematicFit::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&) {}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void DiMuonDiTrakKinematicFit::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DiMuonDiTrakKinematicFit);
