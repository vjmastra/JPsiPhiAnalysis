#include "../interface/DiMuonDiTrackProducer.h"


float DiMuonDiTrackProducer::DeltaR(const pat::PackedCandidate t1, const pat::TriggerObjectStandAlone t2)
{
   float p1 = t1.phi();
   float p2 = t2.phi();
   float e1 = t1.eta();
   float e2 = t2.eta();
   auto dp=std::abs(p1-p2); if (dp>float(M_PI)) dp-=float(2*M_PI);

   return sqrt((e1-e2)*(e1-e2) + dp*dp);
}

float DiMuonDiTrackProducer::DeltaPt(const pat::PackedCandidate t1, const pat::TriggerObjectStandAlone t2)
{
   return (fabs(t1.pt()-t2.pt())/t2.pt());
}

bool DiMuonDiTrackProducer::MatchByDRDPt(const pat::PackedCandidate t1, const pat::TriggerObjectStandAlone t2)
{
  return (fabs(t1.pt()-t2.pt())/t2.pt()<MaxDPtRel_ &&
	DeltaR(t1,t2) < MaxDeltaR_);
}

bool
DiMuonDiTrackProducer::isAbHadron(int pdgID) {

  if (abs(pdgID) == 511 || abs(pdgID) == 521 || abs(pdgID) == 531 || abs(pdgID) == 5122) return true;
  return false;

}

bool
DiMuonDiTrackProducer::isAMixedbHadron(int pdgID, int momPdgID) {

  if ((abs(pdgID) == 511 && abs(momPdgID) == 511 && pdgID*momPdgID < 0) ||
  (abs(pdgID) == 531 && abs(momPdgID) == 531 && pdgID*momPdgID < 0))
  return true;
  return false;

}

bool
DiMuonDiTrackProducer::isTheCandidate(reco::GenParticleRef genY) {

  bool goToJPsi = false;
  bool goToPhi = false;

  for(size_t j = 0; j < genY->numberOfDaughters(); ++j)
  {

    const reco::Candidate * daughter = genY->daughter(j);
    if(daughter->pdgId() == 443)
      goToJPsi=true;
    if(daughter->pdgId() == 333)
    {
      bool kP = false, kN = false;
      for(size_t k = 0; k <daughter->numberOfDaughters(); ++k)
      {
        const reco::Candidate * gdaughter = daughter->daughter(k);

        if(goToPhi && goToJPsi)
        {
          if(gdaughter->pdgId()==321)
            kP=true;
          if(gdaughter->pdgId()==-321)
            kN=true;
        }

      }
      goToPhi = kP && kN;
    }

  }

  return (goToJPsi && goToPhi);

}

bool DiMuonDiTrackProducer::isSameTrack(reco::Track t1, reco::Track t2)
{

  float p1 = t1.phi();
  float p2 = t2.phi();
  float e1 = t1.eta();
  float e2 = t2.eta();
  auto dp=std::abs(p1-p2); if (dp>float(M_PI)) dp-=float(2*M_PI);

  float deltaR = sqrt((e1-e2)*(e1-e2) + dp*dp);
  float deltaPt = ((t1.pt() - t2.pt())/t1.pt());

  return (deltaR <= 0.01) &&( deltaPt <= 0.01);

}


std::tuple<int, float, float>
DiMuonDiTrackProducer::findJpsiMCInfo(reco::GenParticleRef genJpsi) {

  // std::cout << "findJpsiMCInfo 1 " << std::endl;
  int momJpsiID = 0;
  float trueLife = -99.;
  float isPrompt = -99.;
  if (genJpsi->numberOfMothers()>0) {

    // std::cout << "findJpsiMCInfo 1 " << std::endl;

    TVector3 trueVtx(0.0,0.0,0.0);
    TVector3 trueP(0.0,0.0,0.0);
    TVector3 trueVtxMom(0.0,0.0,0.0);

    trueVtx.SetXYZ(genJpsi->vertex().x(),genJpsi->vertex().y(),genJpsi->vertex().z());
    trueP.SetXYZ(genJpsi->momentum().x(),genJpsi->momentum().y(),genJpsi->momentum().z());

    reco::GenParticleRef Jpsimom = genJpsi->motherRef();       // find mothers
    // std::cout << "findJpsiMCInfo 1 " << std::endl;
    if (Jpsimom.isNull()) {
      std::tuple<int, float, float> result = std::make_tuple(momJpsiID, trueLife,isPrompt);
      return result;
    } else
    {
      if(!isTheCandidate(Jpsimom))
      {
        std::tuple<int, float, float> result = std::make_tuple(momJpsiID, trueLife,isPrompt);
        return result;
      }
      momJpsiID = Jpsimom->pdgId();
      Jpsimom->isPromptDecayed();
      trueVtxMom.SetXYZ(Jpsimom->vertex().x(),Jpsimom->vertex().y(),Jpsimom->vertex().z());
      TVector3 vdiff = trueVtx - trueVtxMom;
      trueLife = vdiff.Perp()*genJpsi->mass()/trueP.Perp();
  }
}
  std::tuple<int,float,float> result = std::make_tuple(momJpsiID, trueLife,isPrompt);
  return result;

}

const pat::CompositeCandidate DiMuonDiTrackProducer::makeTTTriggerCandidate(
                                          const pat::TriggerObjectStandAlone& highTrack,
                                          const pat::TriggerObjectStandAlone& lowTrack
                                         ){

  pat::CompositeCandidate TTCand;
  TTCand.addDaughter(highTrack,"highTrack");
  TTCand.addDaughter(lowTrack,"lowTrack");
  TTCand.setCharge(highTrack.charge()+lowTrack.charge());

  double m_kaon1 = MassTracks_[0];
  math::XYZVector mom_kaon1 = highTrack.momentum();
  double e_kaon1 = sqrt(m_kaon1*m_kaon1 + mom_kaon1.Mag2());
  math::XYZTLorentzVector p4_kaon1 = math::XYZTLorentzVector(mom_kaon1.X(),mom_kaon1.Y(),mom_kaon1.Z(),e_kaon1);
  double m_kaon2 = MassTracks_[1];
  math::XYZVector mom_kaon2 = lowTrack.momentum();
  double e_kaon2 = sqrt(m_kaon2*m_kaon2 + mom_kaon2.Mag2());
  math::XYZTLorentzVector p4_kaon2 = math::XYZTLorentzVector(mom_kaon2.X(),mom_kaon2.Y(),mom_kaon2.Z(),e_kaon2);
  reco::Candidate::LorentzVector vTT = p4_kaon1 + p4_kaon2;
  TTCand.setP4(vTT);

  return TTCand;
}

const pat::CompositeCandidate DiMuonDiTrackProducer::makeTTTriggerMixedCandidate(
                                          const pat::PackedCandidate& highTrack,
                                          const pat::TriggerObjectStandAlone& lowTrack
                                         ){

  pat::CompositeCandidate TTCand;
  TTCand.addDaughter(highTrack,"highTrack");
  TTCand.addDaughter(lowTrack,"lowTrack");
  TTCand.setCharge(highTrack.charge()+lowTrack.charge());

  double m_kaon1 = MassTracks_[0];
  math::XYZVector mom_kaon1 = highTrack.momentum();
  double e_kaon1 = sqrt(m_kaon1*m_kaon1 + mom_kaon1.Mag2());
  math::XYZTLorentzVector p4_kaon1 = math::XYZTLorentzVector(mom_kaon1.X(),mom_kaon1.Y(),mom_kaon1.Z(),e_kaon1);
  double m_kaon2 = MassTracks_[1];
  math::XYZVector mom_kaon2 = lowTrack.momentum();
  double e_kaon2 = sqrt(m_kaon2*m_kaon2 + mom_kaon2.Mag2());
  math::XYZTLorentzVector p4_kaon2 = math::XYZTLorentzVector(mom_kaon2.X(),mom_kaon2.Y(),mom_kaon2.Z(),e_kaon2);
  reco::Candidate::LorentzVector vTT = p4_kaon1 + p4_kaon2;
  TTCand.setP4(vTT);

  return TTCand;
}

DiMuonDiTrackProducer::DiMuonDiTrackProducer(const edm::ParameterSet& iConfig):
  DiMuonCollection_(consumes<pat::CompositeCandidateCollection>(iConfig.getParameter<edm::InputTag>("DiMuon"))),
  TrackCollection_(consumes<edm::View<pat::PackedCandidate>>(iConfig.getParameter<edm::InputTag>("PFCandidates"))),
  TrackPtCut_(iConfig.existsAs<double>("TrackPtCut") ? iConfig.getParameter<double>("TrackPtCut") : 0.7),
  MaxDeltaR_(iConfig.existsAs<double>("DRCut") ? iConfig.getParameter<double>("DRCut") : 0.01),
  MaxDPtRel_(iConfig.existsAs<double>("DPtCut") ? iConfig.getParameter<double>("DPtCut") : 2.0),
  TrackGenMap_(consumes<edm::Association<reco::GenParticleCollection>>(iConfig.getParameter<edm::InputTag>("TrackMatcher"))),
  //DiMuonGenMap_(iConfig.existsAs<edm::InputTag>("DiMuonMatcher") ? consumes<edm::Association<reco::GenParticleCollection>>(iConfig.getParameter<edm::InputTag>("DiMuonMatcher"))),
  thebeamspot_(consumes<reco::BeamSpot>(iConfig.getParameter<edm::InputTag>("BeamSpot"))),
  thePVs_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("PrimaryVertex"))),
  TriggerCollection_(consumes<std::vector<pat::TriggerObjectStandAlone>>(iConfig.getParameter<edm::InputTag>("TriggerInput"))),
  TriggerResults_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("TriggerResults"))),
  DiMuonMassCuts_(iConfig.getParameter<std::vector<double>>("DiMuonMassCuts")),
  TrackTrackMassCuts_(iConfig.getParameter<std::vector<double>>("TrackTrackMassCuts")),
  DiMuonDiTrackMassCuts_(iConfig.getParameter<std::vector<double>>("DiMuonDiTrackMassCuts")),
  MassTracks_(iConfig.getParameter<std::vector<double>>("MassTracks")),
  JPsiMass_(iConfig.getParameter<double>("JPsiMass")),
  PhiMass_(iConfig.getParameter<double>("PhiMass")),
  product_name_(iConfig.getParameter<std::string>("Product")),
  HLTFilters_(iConfig.getParameter<std::vector<std::string>>("Filters")),
  IsMC_(iConfig.getParameter<bool>("IsMC")),
  AddSameSig_(iConfig.getParameter<bool>("AddSS")),
  doPionRefit_(iConfig.getParameter<bool>("PionRefit"))
{
  produces<pat::CompositeCandidateCollection>(product_name_);
  candidates = 0;
  nevents = 0;
  ndimuon = 0;
  nreco = 0;

  maxDeltaR = 0.1;
  maxDPtRel = 2.0;

  packCands_ = consumes<pat::PackedGenParticleCollection>((edm::InputTag)"packedGenParticles");
  allMuons_ = consumes<pat::MuonCollection>((edm::InputTag)"slimmedMuons");

  //TrackGenMap_ = consumes<edm::Association<reco::GenParticleCollection>>((edm::InputTag)"trackMatch");

}

void DiMuonDiTrackProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){

  // int debug = 1;

  // std::cout << "debug    2 "<< std::endl;
  std::unique_ptr<pat::CompositeCandidateCollection> DiMuonTTCandColl(new pat::CompositeCandidateCollection);

  bool ptLeading = false;

  edm::Handle<pat::MuonCollection> muons;
  iEvent.getByToken(allMuons_,muons);

  edm::Handle<pat::CompositeCandidateCollection> dimuon;
  iEvent.getByToken(DiMuonCollection_,dimuon);

  edm::Handle<edm::View<pat::PackedCandidate> > track;
  iEvent.getByToken(TrackCollection_,track);

  edm::Handle<std::vector<pat::TriggerObjectStandAlone>> trig;
  iEvent.getByToken(TriggerCollection_,trig);

  edm::Handle< edm::TriggerResults > triggerResults_handle;
  iEvent.getByToken( TriggerResults_ , triggerResults_handle);

  edm::Handle<pat::PackedGenParticleCollection> packed;
  iEvent.getByToken(packCands_,  packed);

  edm::Handle<reco::BeamSpot> theBeamSpot;
  iEvent.getByToken(thebeamspot_,theBeamSpot);

  edm::Handle<edm::Association<reco::GenParticleCollection>> theGenMap;
  iEvent.getByToken(TrackGenMap_,theGenMap);

  reco::BeamSpot bs = *theBeamSpot;
  reco::Vertex theBeamSpotV = reco::Vertex(bs.position(), bs.covariance3D());

  edm::Handle<reco::VertexCollection> priVtxs;
  iEvent.getByToken(thePVs_, priVtxs);

  edm::ESHandle<MagneticField> magneticField;
  iSetup.get<IdealMagneticFieldRecord>().get(magneticField);

  const edm::TriggerNames & names = iEvent.triggerNames( *triggerResults_handle );

  // Kinematic fit
  edm::ESHandle<TransientTrackBuilder> theB;
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);

  uint ncombo = 0;
  float DiMuonMassMax_ = DiMuonMassCuts_[1];
  float DiMuonMassMin_ = DiMuonMassCuts_[0];
  float TrackTrackMassMax_ = TrackTrackMassCuts_[1];
  float TrackTrackMassMin_ = TrackTrackMassCuts_[0];
  float DiMuonDiTrackMassMax_ = DiMuonDiTrackMassCuts_[1];
  float DiMuonDiTrackMassMin_ = DiMuonDiTrackMassCuts_[0];

  pat::TriggerObjectStandAloneCollection filteredColl;
  std::map<int,pat::TriggerObjectStandAlone> matchedColl;
  std::map<size_t,double> trackDeltaR,trackDeltaPt;
  std::vector < UInt_t > filterResults;
  std::map<int,UInt_t> filters;


  //Trigger Collections
  for ( size_t iTrigObj = 0; iTrigObj < trig->size(); ++iTrigObj ) {

    pat::TriggerObjectStandAlone unPackedTrigger( trig->at( iTrigObj ) );

    unPackedTrigger.unpackPathNames( names );
    unPackedTrigger.unpackFilterLabels(iEvent,*triggerResults_handle);

    bool filtered = false;
    UInt_t thisFilter = 0;

    for (size_t i = 0; i < HLTFilters_.size(); i++)
      if(unPackedTrigger.hasFilterLabel(HLTFilters_[i]))
        {
          thisFilter += (1<<i);
          filtered = true;
        }

    if(filtered)
    {
      filteredColl.push_back(unPackedTrigger);
      filterResults.push_back(thisFilter);
    }
  }

  //Tracks Collections Trigger Matching
  for (size_t i = 0; i < track->size(); i++) {

    auto t = track->at(i);

    bool matched = false;
    for (std::vector<pat::TriggerObjectStandAlone>::const_iterator trigger = filteredColl.begin(), triggerEnd=filteredColl.end(); trigger!= triggerEnd; ++trigger)
  for ( size_t iTrigObj = 0; iTrigObj < filteredColl.size(); ++iTrigObj )
    {
      auto thisTrig = filteredColl.at(iTrigObj);
      if(MatchByDRDPt(t,filteredColl[iTrigObj]))
      {
        if(matched)
        {
          if(trackDeltaR[i] > DeltaR(t,thisTrig))
          {
            filters[i] = filterResults[iTrigObj];
            matchedColl[i] = thisTrig;
            trackDeltaR[i] = fabs(DeltaR(t,thisTrig));
            trackDeltaPt[i] = fabs(DeltaPt(t,thisTrig));
          }
        }else
        {
          filters[i] = filterResults[iTrigObj];
          matchedColl[i] = thisTrig;
          trackDeltaR[i] = fabs(DeltaR(t,thisTrig));
          trackDeltaPt[i] = fabs(DeltaPt(t,thisTrig));
        }

        matched = true;
      }
    }
    if(!matched)
    {
      filters[i] = 0;
      trackDeltaR[i] = -1.0;
      trackDeltaPt[i] = -1.0;
    }

  }


  // std::cout << "debug    4 "<< std::endl;
// Note: Dimuon cand are sorted by decreasing vertex probability then first is associated with "best" dimuon

  int dimuonCounter = -1;

  for (pat::CompositeCandidateCollection::const_iterator dimuonCand = dimuon->begin(); dimuonCand != dimuon->end(); ++dimuonCand){
     dimuonCounter++;
     if ( dimuonCand->mass() < DiMuonMassMax_  && dimuonCand->mass() > DiMuonMassMin_ ) {
       // std::cout << "debug    5 "<< std::endl;
       if(dimuonCand->userFloat("vProb")<0.001)
         continue;

       // const reco::Vertex thePrimaryV = *dimuonCand->userData<reco::Vertex>("PVwithmuons");

       const pat::Muon *pmu1 = dynamic_cast<const pat::Muon*>(dimuonCand->daughter("highMuon"));
       const pat::Muon *pmu2 = dynamic_cast<const pat::Muon*>(dimuonCand->daughter("lowMuon"));
       // const reco::Muon *rmu1 = dynamic_cast<const reco::Muon *>(pmu1->originalObject());
       // const reco::Muon *rmu2 = dynamic_cast<const reco::Muon *>(pmu2->originalObject());


// loop on track candidates, make DiMuonT candidate, positive charge
       // for (std::vector<pat::PackedCandidate>::const_iterator posTrack = track->begin(), trackend=track->end(); posTrack!= trackend; ++posTrack){
       for (size_t i = 0; i < track->size(); i++) {
         auto posTrack = track->at(i);

         if(!AddSameSig_ && posTrack.charge()<=0) continue;
         if(posTrack.pt()<TrackPtCut_) continue;
	       //if(!IsMC_ and fabs(posTrack.pdgId())!=211) continue;
	       if(!(posTrack.trackHighPurity())) continue;
         if(!(posTrack.hasTrackDetails())) continue;



         if ( IsTheSame(posTrack,*pmu1) || IsTheSame(posTrack,*pmu2)) continue;
         // std::cout << "debug    6 "<< std::endl;
// loop over second track candidate, negative charge
         // for (std::vector<pat::PackedCandidate>::const_iterator negTrack = track->begin(); negTrack!= trackend; ++negTrack){
         int jstart = 0;
         if(AddSameSig_) jstart = i+1;
         for (size_t j = jstart; j < track->size(); j++) {

           auto negTrack = track->at(j);

           if(!AddSameSig_ && negTrack.charge()>=0) continue;
           if(negTrack.pt()<TrackPtCut_) continue;

           bool sameSign = posTrack.charge()*negTrack.charge()<0.;

  	       //if(!IsMC_ and fabs(negTrack.pdgId())!=211) continue;
  	       if(!(negTrack.trackHighPurity())) continue;
           if(!(negTrack.hasTrackDetails())) continue;

           if (i == j) continue;
           if ( IsTheSame(negTrack,*pmu1) || IsTheSame(negTrack,*pmu2) ) continue;

           auto highTrack = track->at(i);
           auto lowTrack  = track->at(j);

           if(sameSign || ptLeading)
           {
             if(posTrack.pt()<negTrack.pt())
              {
                highTrack = negTrack;
                lowTrack  = posTrack;
              }
           }else
           {
             if(posTrack.charge()<negTrack.charge())
              {
                highTrack = negTrack;
                lowTrack  = posTrack;
              }
           }

           pat::CompositeCandidate TTCand = makeTTCandidate(highTrack,lowTrack);
           //
           // if(sameSign || ptLeading)
           // {
           //   if(posTrack.pt()>negTrack.pt())
           //    TTCand = makeTTCandidate(posTrack, negTrack);
           //   else
           //    TTCand = makeTTCandidate(negTrack,posTrack);
           // }else
           // {
           //   if(posTrack.charge()>negTrack.charge())
           //    TTCand = makeTTCandidate(posTrack, negTrack);
           //   else
           //    TTCand = makeTTCandidate(negTrack,posTrack);
           // }

           if ( !(TTCand.mass() < TrackTrackMassMax_ && TTCand.mass() > TrackTrackMassMin_) ) continue;

           pat::CompositeCandidate DiMuonTTCand = makeDiMuonTTCandidate(*dimuonCand, *&TTCand);

           if (DiMuonTTCand.mass() > DiMuonDiTrackMassMax_ || DiMuonTTCand.mass() < DiMuonDiTrackMassMin_) continue;


           // float refittedMass = -1.0, mumuVtxCL = -1.0;
           const ParticleMass muonMass(0.1056583);
           float muonSigma = muonMass*1E-6;
           const ParticleMass trackMass1(MassTracks_[0]);
           float trackSigma1 = trackMass1*1E-6;
           const ParticleMass trackMass2(MassTracks_[1]);
           float trackSigma2 = trackMass2*1E-6;

           std::vector<reco::TransientTrack> xTracks;
           KinematicParticleFactoryFromTransientTrack pFactory;
           std::vector<RefCountedKinematicParticle> xParticles;

           float kinChi = 0.;
           float kinNdf = 0.;
           // std::cout << "debug    7 "<< std::endl;
           xTracks.push_back((*theB).build(*(pmu1->innerTrack()))); // µ+
           xTracks.push_back((*theB).build(*(pmu2->innerTrack()))); // µ+

           xTracks.push_back((*theB).build(*(posTrack.bestTrack()))); // K+
           xTracks.push_back((*theB).build(*(negTrack.bestTrack()))); // K+

           if(posTrack.pt()>=negTrack.pt() || !ptLeading)
           {
             xTracks.push_back((*theB).build(*(posTrack.bestTrack()))); // K+
             xTracks.push_back((*theB).build(*(negTrack.bestTrack()))); // K+
           }else
           {
             xTracks.push_back((*theB).build(*(negTrack.bestTrack()))); // K+
             xTracks.push_back((*theB).build(*(posTrack.bestTrack()))); // K+
           }

           xParticles.push_back(pFactory.particle(xTracks[0],muonMass,kinChi,kinNdf,muonSigma));
           xParticles.push_back(pFactory.particle(xTracks[1],muonMass,kinChi,kinNdf,muonSigma));
           xParticles.push_back(pFactory.particle(xTracks[2],trackMass1,kinChi,kinNdf,trackSigma1));
           xParticles.push_back(pFactory.particle(xTracks[3],trackMass2,kinChi,kinNdf,trackSigma2));

           KinematicParticleVertexFitter kFitter;
           RefCountedKinematicTree xVertexFitTree;
           xVertexFitTree = kFitter.fit(xParticles);

           if (xVertexFitTree->isEmpty()) continue;

           xVertexFitTree->movePointerToTheTop();
           RefCountedKinematicParticle fitX = xVertexFitTree->currentParticle();
           RefCountedKinematicVertex fitXVertex = xVertexFitTree->currentDecayVertex();

           double x_ma_fit = 14000.;
           double x_vp_fit = -9999.;
           double x_x2_fit = 10000.;
           double x_ndof_fit = 10000.;

           if (!(fitX->currentState().isValid())) continue;

           // std::cout << "debug    8 "<< std::endl;
           x_ma_fit = fitX->currentState().mass();
           x_x2_fit = fitXVertex->chiSquared();
           x_vp_fit = ChiSquaredProbability(x_x2_fit,
                                                (double)(fitXVertex->degreesOfFreedom()));
           x_ndof_fit = (double)(fitXVertex->degreesOfFreedom());


           if(x_vp_fit < 0.001) continue;

           float minDR_pos = 10000.0, minDR_neg = 10000.0;
           float minDP_pos = 10000.0, minDP_neg = 10000.0;
           float minDPt_pos = 10000.0, minDPt_neg = 10000.0;

           for (size_t ii = 0; ii < muons->size(); ii++)
           {
              auto thisMuon = muons->at(ii);

              float DeltaEta = fabs(thisMuon.eta()-posTrack.eta());
              float DeltaP   = fabs(thisMuon.p()-posTrack.p());
              float DeltaPt = ((posTrack.pt() - thisMuon.pt())/posTrack.pt());

              minDR_pos = -std::max(minDR_pos,DeltaEta);
              minDP_pos = -std::max(minDP_pos,DeltaP);
              minDPt_pos = -std::max(minDPt_pos,DeltaPt);
           }

           for (size_t ii = 0; ii < muons->size(); ii++)
           {
              auto thisMuon = muons->at(ii);

              float DeltaEta = fabs(thisMuon.eta()-negTrack.eta());
              float DeltaP   = fabs(thisMuon.p()-negTrack.p());
              float DeltaPt = ((negTrack.pt() - thisMuon.pt())/negTrack.pt());

              minDR_pos = -std::max(-minDR_pos,-DeltaEta);
              minDP_pos = -std::max(-minDP_pos,-DeltaP);
              minDPt_pos = -std::max(-minDPt_pos,-DeltaPt);

           }


           DiMuonTTCand.addUserFloat("mass_rf",x_ma_fit);
           DiMuonTTCand.addUserFloat("vProb",x_vp_fit);
           DiMuonTTCand.addUserFloat("vChi2",x_x2_fit);
           DiMuonTTCand.addUserFloat("nDof",x_ndof_fit);
           DiMuonTTCand.addUserInt("pId",i);
           DiMuonTTCand.addUserInt("mId",j);


           if(ptLeading || sameSign) //pt leading ordering if ptLeading or samesign
           {
             if(posTrack.pt()>=negTrack.pt())
             {
               DiMuonTTCand.addUserFloat("highKaonMuonDR",minDR_pos);
               DiMuonTTCand.addUserFloat("highKaonMuonDP",minDP_pos);
               DiMuonTTCand.addUserFloat("highKaonMuonDPt",minDPt_pos);

               DiMuonTTCand.addUserFloat("lowKaonMuonDR",minDR_neg);
               DiMuonTTCand.addUserFloat("lowKaonMuonDP",minDP_neg);
               DiMuonTTCand.addUserFloat("lowKaonMuonDPt",minDPt_neg);

             }else
             {
               DiMuonTTCand.addUserFloat("lowKaonMuonDR",minDR_pos);
               DiMuonTTCand.addUserFloat("lowKaonMuonDP",minDP_pos);
               DiMuonTTCand.addUserFloat("lowKaonMuonDPt",minDPt_pos);

               DiMuonTTCand.addUserFloat("highKaonMuonDR",minDR_neg);
               DiMuonTTCand.addUserFloat("highKaonMuonDP",minDP_neg);
               DiMuonTTCand.addUserFloat("highKaonMuonDPt",minDPt_neg);
             }
           }
           else
           {
             if(posTrack.charge()>negTrack.charge())   //charge ordering
             {
               DiMuonTTCand.addUserFloat("highKaonMuonDR",minDR_pos);
               DiMuonTTCand.addUserFloat("highKaonMuonDP",minDP_pos);
               DiMuonTTCand.addUserFloat("highKaonMuonDPt",minDPt_pos);

               DiMuonTTCand.addUserFloat("lowKaonMuonDR",minDR_neg);
               DiMuonTTCand.addUserFloat("lowKaonMuonDP",minDP_neg);
               DiMuonTTCand.addUserFloat("lowKaonMuonDPt",minDPt_neg);

             }else
             {
               DiMuonTTCand.addUserFloat("lowKaonMuonDR",minDR_pos);
               DiMuonTTCand.addUserFloat("lowKaonMuonDP",minDP_pos);
               DiMuonTTCand.addUserFloat("lowKaonMuonDPt",minDPt_pos);

               DiMuonTTCand.addUserFloat("highKaonMuonDR",minDR_neg);
               DiMuonTTCand.addUserFloat("highKaonMuonDP",minDP_neg);
               DiMuonTTCand.addUserFloat("highKaonMuonDPt",minDPt_neg);
             }
           }

           DiMuonTTCand.addUserFloat("isSameSign",float(sameSign));
           //////////////////////////////////////////////////////////////////////////////
           //PV Selection(s)

           std::vector <double> sumPTPV,cosAlpha,ctauPV,ctauErrPV;
           // std::cout << "debug    9 "<< std::endl;
           TVector3 vtx, vdiff, pvtx;
           VertexDistanceXY vdistXY;
           reco::Vertex thePrimaryVDZ, thePrimaryZero, thePrimaryVCA;
           TwoTrackMinimumDistance ttmd;

           double x_px_fit = fitX->currentState().kinematicParameters().momentum().x();
           double x_py_fit = fitX->currentState().kinematicParameters().momentum().y();
           double x_pz_fit = fitX->currentState().kinematicParameters().momentum().z();
           // double x_en_fit = sqrt(x_ma_fit*x_ma_fit+x_px_fit*x_px_fit+x_py_fit*x_py_fit+x_pz_fit*x_pz_fit);
           double x_vx_fit = fitXVertex->position().x();
	         double x_vy_fit = fitXVertex->position().y();
           double x_vz_fit = fitXVertex->position().z();
           vtx.SetXYZ(x_vx_fit,x_vy_fit,0);

           bool status = ttmd.calculate( GlobalTrajectoryParameters(
             GlobalPoint(x_vx_fit,x_vy_fit,x_vz_fit),
             GlobalVector(x_px_fit,x_py_fit,x_pz_fit),TrackCharge(0),&(*magneticField)),
             GlobalTrajectoryParameters(
               GlobalPoint(bs.position().x(), bs.position().y(), bs.position().z()),
               GlobalVector(bs.dxdz(), bs.dydz(), 1.),TrackCharge(0),&(*magneticField)));
           float extrapZ=-9E20;

           if (status) extrapZ=ttmd.points().first.z();

           TVector3 pperp(x_px_fit, x_py_fit, 0);
           AlgebraicVector3 vpperp(pperp.x(),pperp.y(),0);

           reco::VertexCollection verteces;
           std::vector<int> vKeys;
           verteces.push_back(theBeamSpotV);
           vKeys.push_back(0);

           thePrimaryZero = reco::Vertex(*(priVtxs->begin()));
           verteces.push_back(thePrimaryZero);
           vKeys.push_back(0);

           float minDz = 999999.;
           double maxCosAlpha = -1.0;
           if ( (priVtxs->begin() == priVtxs->end()) )
           {
             // std::cout << "debug    10 "<< std::endl;
             thePrimaryVCA = reco::Vertex(*(priVtxs->begin()));
             thePrimaryVDZ = reco::Vertex(*(priVtxs->begin()));
             verteces.push_back(thePrimaryVCA);
             verteces.push_back(thePrimaryVDZ);
             vKeys.push_back(0);
             vKeys.push_back(0);
           }else
           {

             reco::Vertex p,pz;
             int thisp,thispz;
             for(size_t pV = 0; pV<priVtxs->size();++pV)
             {
               auto thisPV = priVtxs->at(pV);

               pvtx.SetXYZ(thePrimaryVCA.position().x(),thePrimaryVCA.position().y(),0);
               vdiff = vtx - pvtx;
               double thisCosAlpha = vdiff.Dot(pperp)/(vdiff.Perp()*pperp.Perp());
               if(thisCosAlpha>maxCosAlpha)
               {
                 thePrimaryVCA = reco::Vertex(thisPV);
                 maxCosAlpha = thisCosAlpha;
                 p = reco::Vertex(thisPV);
                 thisp = pV;
               }

               float deltaZ = fabs(extrapZ - thisPV.position().z()) ;
               if ( deltaZ < minDz ) {
                 minDz = deltaZ;
                 pz = reco::Vertex(thisPV);
                 thispz =pV;
               }
             }
             verteces.push_back(p);
             vKeys.push_back(thisp);
             verteces.push_back(pz);
             vKeys.push_back(thispz);
           }
           // std::cout << "debug    11 "<< std::endl;
           //////////////////////////////////////////////////
           //Refit PVs (not BS)

           std::vector<TransientVertex> pvs;
           std::vector<float> tPFromPV,tMFromPV;

           for(size_t i = 0; i < verteces.size(); i++)
           {
             tPFromPV.push_back(0.0);
             tMFromPV.push_back(0.0);
           }

           for(size_t i = 1; i < verteces.size(); i++)
           {
             tPFromPV[i] = posTrack.fromPV(vKeys[i]);
             tMFromPV[i] = negTrack.fromPV(vKeys[i]);
           }
           // std::cout << "debug    13 "<< std::endl;
           for(size_t i = 0; i < verteces.size(); i++)
           {
             pvtx.SetXYZ(verteces[i].position().x(),verteces[i].position().y(),0);
             vdiff = vtx - pvtx;
             cosAlpha.push_back(vdiff.Dot(pperp)/(vdiff.Perp()*pperp.Perp()));
             Measurement1D distXY = vdistXY.distance(reco::Vertex(*fitXVertex), verteces[i]);
             ctauPV.push_back(distXY.value()*cosAlpha[i] * x_ma_fit/pperp.Perp());
             GlobalError v1e = (reco::Vertex(*fitXVertex)).error();
             GlobalError v2e = verteces[i].error();
             AlgebraicSymMatrix33 vXYe = v1e.matrix()+ v2e.matrix();
             ctauErrPV.push_back(sqrt(ROOT::Math::Similarity(vpperp,vXYe))*x_ma_fit/(pperp.Perp2()));
           }

           float candRef = -1.0, cand_const_ref = -1.0;

          if(posTrack.pt()>=negTrack.pt() || !ptLeading)
           {
             DiMuonTTCand.addUserInt("highKaonMatch",filters[i]);
             DiMuonTTCand.addUserInt("lowKaonMatch",filters[j]);
          }else
          {
            DiMuonTTCand.addUserInt("lowKaonMatch",filters[i]);
            DiMuonTTCand.addUserInt("highKaonMatch",filters[j]);
          }

           DiMuonTTCand.addUserInt("dimuon_id",int(dimuonCounter));

           DiMuonTTCand.addUserData("bestPV",reco::Vertex(thePrimaryZero));
           DiMuonTTCand.addUserData("cosPV",reco::Vertex(thePrimaryVCA));
           DiMuonTTCand.addUserData("zPV",reco::Vertex(thePrimaryVDZ));
           DiMuonTTCand.addUserData("bs",reco::Vertex(theBeamSpotV));

           DiMuonTTCand.addUserFloat("vtxX",x_vx_fit);
           DiMuonTTCand.addUserFloat("vtxY",x_vy_fit);
           DiMuonTTCand.addUserFloat("vtxZ",x_vz_fit);


           DiMuonTTCand.addUserFloat("cosAlphaBS",cosAlpha[0]);
           DiMuonTTCand.addUserFloat("ctauPVBS",ctauPV[0]);
           DiMuonTTCand.addUserFloat("ctauErrPVBS",ctauErrPV[0]);

           // DiMuonTTCand.addUserFloat("tPFromPVBS",float(tPFromPV[0]));
           // DiMuonTTCand.addUserFloat("tMFromPVBS",float(tMFromPV[0]));


           DiMuonTTCand.addUserFloat("cosAlpha",cosAlpha[1]);
           DiMuonTTCand.addUserFloat("ctauPV",ctauPV[1]);
           DiMuonTTCand.addUserFloat("ctauErrPV",ctauErrPV[1]);

           DiMuonTTCand.addUserFloat("tPFromPV",float(tPFromPV[1]));
           DiMuonTTCand.addUserFloat("tMFromPV",float(tMFromPV[1]));


           DiMuonTTCand.addUserFloat("cosAlphaCA",cosAlpha[2]);
           DiMuonTTCand.addUserFloat("ctauPVCA",ctauPV[2]);
           DiMuonTTCand.addUserFloat("ctauErrPVCA",ctauErrPV[2]);

           DiMuonTTCand.addUserFloat("tPFromPVCA",float(tPFromPV[2]));
           DiMuonTTCand.addUserFloat("tMFromPVCA",float(tMFromPV[2]));


           DiMuonTTCand.addUserFloat("cosAlphaDZ",cosAlpha[3]);
           DiMuonTTCand.addUserFloat("ctauPVDZ",ctauPV[3]);
           DiMuonTTCand.addUserFloat("ctauErrPVDZ",ctauErrPV[3]);

           DiMuonTTCand.addUserFloat("tPFromPVDZ",float(tPFromPV[3]));
           DiMuonTTCand.addUserFloat("tMFromPVDZ",float(tMFromPV[3]));

           ///DCA
           std::vector<float> DCAs;
           for(size_t i = 0; i < xTracks.size();++i)
           {
             TrajectoryStateClosestToPoint TS1 = xTracks[i].impactPointTSCP();
             for(size_t j = i+1; j < xTracks.size();++j)
             {

               TrajectoryStateClosestToPoint TS2 = xTracks[j].impactPointTSCP();
               float dca = 1E20;
               if (TS1.isValid() && TS2.isValid()) {
                 ClosestApproachInRPhi cApp;
                 cApp.calculate(TS1.theState(), TS2.theState());
                 if (cApp.status() ) dca = cApp.distance();
               }
               DCAs.push_back(dca);
             }
           }

           DiMuonTTCand.addUserFloat("dca_m1m2",DCAs[0]);
           DiMuonTTCand.addUserFloat("dca_m1t1",DCAs[1]);
           DiMuonTTCand.addUserFloat("dca_m1t2",DCAs[2]);
           DiMuonTTCand.addUserFloat("dca_m2t1",DCAs[3]);
           DiMuonTTCand.addUserFloat("dca_m2t2",DCAs[4]);
           DiMuonTTCand.addUserFloat("dca_t1t2",DCAs[5]);

           //Mass Constrained fit
           KinematicConstrainedVertexFitter vertexFitter;
           MultiTrackKinematicConstraint *jpsi_mtc = new  TwoTrackMassKinematicConstraint(JPsiMass_);
           RefCountedKinematicTree PsiTrTrTree = vertexFitter.fit(xParticles,jpsi_mtc);
           // std::cout << "debug    16 "<< std::endl;

           if (PsiTrTrTree->isEmpty()) continue;

           double dimuontt_vp_fit = -9999.;

           if (!PsiTrTrTree->isEmpty()) {

              PsiTrTrTree->movePointerToTheTop();
              RefCountedKinematicParticle fitPsiTrTr = PsiTrTrTree->currentParticle();
              RefCountedKinematicVertex PsiTDecayVertex = PsiTrTrTree->currentDecayVertex();
       // Get PsiT reffited
              double dimuontt_ma_fit = 14000.;
              dimuontt_vp_fit = -9999.;
              double dimuontt_x2_fit = 10000.;
              double dimuontt_ndof_fit = 10000.;

              if (fitPsiTrTr->currentState().isValid()) {
                dimuontt_ma_fit = fitPsiTrTr->currentState().mass();
                dimuontt_x2_fit = PsiTDecayVertex->chiSquared();
                dimuontt_vp_fit = ChiSquaredProbability(dimuontt_x2_fit,
                                                     (double)(PsiTDecayVertex->degreesOfFreedom()));
                dimuontt_ndof_fit = (double)(PsiTDecayVertex->degreesOfFreedom());
              }

              if ( dimuontt_vp_fit > 0.0 ) {

                   TVector3 vtx;
                   TVector3 pvtx;
                   VertexDistanceXY vdistXY;
                   int   dimuontt_ch_fit = DiMuonTTCand.charge();
                   double dimuontt_px_fit = fitPsiTrTr->currentState().kinematicParameters().momentum().x();
                   double dimuontt_py_fit = fitPsiTrTr->currentState().kinematicParameters().momentum().y();
                   double dimuontt_pz_fit = fitPsiTrTr->currentState().kinematicParameters().momentum().z();
                   double dimuontt_en_fit = sqrt(dimuontt_ma_fit*dimuontt_ma_fit+dimuontt_px_fit*dimuontt_px_fit+
                                             dimuontt_py_fit*dimuontt_py_fit+dimuontt_pz_fit*dimuontt_pz_fit);
                   double dimuontt_vx_fit = PsiTDecayVertex->position().x();
                   double dimuontt_vy_fit = PsiTDecayVertex->position().y();
                   double dimuontt_vz_fit = PsiTDecayVertex->position().z();

                   vtx.SetXYZ(dimuontt_vx_fit,dimuontt_vy_fit,0);
                   TVector3 pperp(dimuontt_px_fit, dimuontt_py_fit, 0);
                   AlgebraicVector3 vpperp(pperp.x(),pperp.y(),0);
                   pvtx.SetXYZ(thePrimaryZero.position().x(),thePrimaryZero.position().y(),0);
                   TVector3 vdiff = vtx - pvtx;
                   double cosAlpha = vdiff.Dot(pperp)/(vdiff.Perp()*pperp.Perp());
                   Measurement1D distXY = vdistXY.distance(reco::Vertex(*PsiTDecayVertex), thePrimaryZero);
                   double ctauPV = distXY.value()*cosAlpha * dimuontt_ma_fit/pperp.Perp();
                   GlobalError v1e = (reco::Vertex(*PsiTDecayVertex)).error();
                   GlobalError v2e = thePrimaryZero.error();
                   AlgebraicSymMatrix33 vXYe = v1e.matrix()+ v2e.matrix();
                   double ctauErrPV = sqrt(ROOT::Math::Similarity(vpperp,vXYe))*dimuontt_ma_fit/(pperp.Perp2());

                   reco::CompositeCandidate recoPsiTT_rf(dimuontt_ch_fit,math::XYZTLorentzVector(dimuontt_px_fit,dimuontt_py_fit,dimuontt_pz_fit,dimuontt_en_fit),
                                                      math::XYZPoint(dimuontt_vx_fit,dimuontt_vy_fit,dimuontt_vz_fit),531);

                   pat::CompositeCandidate DiMuonTTCand_rf(recoPsiTT_rf);

                   DiMuonTTCand.addUserFloat("vProb_ref",dimuontt_vp_fit);
                   DiMuonTTCand.addUserFloat("vChi2_ref",dimuontt_x2_fit);
                   DiMuonTTCand.addUserFloat("nDof_ref",dimuontt_ndof_fit);
                   DiMuonTTCand.addUserFloat("cosAlpha_ref",cosAlpha);
                   DiMuonTTCand.addUserFloat("ctauPV_ref",ctauPV);
                   DiMuonTTCand.addUserFloat("ctauErrPV_ref",ctauErrPV);
                   // std::cout << "debug    17 "<< std::endl;
       // get first muon
                   bool child = PsiTrTrTree->movePointerToTheFirstChild();
                   RefCountedKinematicParticle fitMu1 = PsiTrTrTree->currentParticle();
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
                   child = PsiTrTrTree->movePointerToTheNextChild();
                   RefCountedKinematicParticle fitMu2 = PsiTrTrTree->currentParticle();
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
       	           psi.addDaughter(patMu1,"highMuon");
                   psi.addDaughter(patMu2,"lowMuon");
                   psi.setP4(patMu1.p4()+patMu2.p4());
       // get kaon
                   child = PsiTrTrTree->movePointerToTheNextChild();
                   RefCountedKinematicParticle fitTrk = PsiTrTrTree->currentParticle();
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
                   child = PsiTrTrTree->movePointerToTheNextChild();
                   RefCountedKinematicParticle fitTrk2 = PsiTrTrTree->currentParticle();
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

       // Define phi from two kaons
                   pat::CompositeCandidate phi;
                   if(patTk.pt()>=patTk2.pt())
                   {
                     phi.addDaughter(patTk,"highTrack");
                     phi.addDaughter(patTk2,"lowTrack");
                   }else
                   {
                     phi.addDaughter(patTk2,"highTrack");
                     phi.addDaughter(patTk,"lowTrack");
                   }

                   phi.setP4(patTk.p4()+patTk2.p4());
                   candRef = 1.0;
                   DiMuonTTCand_rf.addDaughter(phi,"ditrack");
                   DiMuonTTCand_rf.addDaughter(psi,"dimuon");
                   DiMuonTTCand.addDaughter(DiMuonTTCand_rf,"ref_cand");
                 }
              }

           if(dimuontt_vp_fit<0.001) continue;

           std::vector<float> massPionRefits,massPionRefits_ref,vProbPionRefits,chi2PionRefits,nDofPionRefits;

           for(int i = 0; i < 3; ++i)
           {
             massPionRefits.push_back(-1.0);
             massPionRefits_ref.push_back(-1.0);
             chi2PionRefits.push_back(-1.0);
             nDofPionRefits.push_back(-1.0);
             vProbPionRefits.push_back(-1.0);
           }

           if(doPionRefit_)
           {
             KinematicParticleFactoryFromTransientTrack pFactory;
             std::vector<RefCountedKinematicParticle> pkParticles;

             double pionmass = 0.13957061;


             std::vector<float> oneMasses,twoMasses;
             oneMasses.push_back(MassTracks_[0]); oneMasses.push_back(pionmass);oneMasses.push_back(pionmass);
             twoMasses.push_back(pionmass); twoMasses.push_back(MassTracks_[0]);twoMasses.push_back(pionmass);


             for(int iP = 0; iP < 3; ++iP)
             {
                 const ParticleMass oneMass(oneMasses[iP]);
                 const ParticleMass twoMass(twoMasses[iP]);

                 float trackSigma1 = oneMass*1E-6;
                 float trackSigma2 = twoMass*1E-6;

                 kinChi = 0.;
                 kinNdf = 0.;

                 pat::CompositeCandidate otherTTCand = makeTTCandidate(posTrack,negTrack);

                 double m_kaon1 = oneMasses[iP];
                 math::XYZVector mom_kaon1 = posTrack.momentum();
                 double e_kaon1 = sqrt(m_kaon1*m_kaon1 + mom_kaon1.Mag2());
                 math::XYZTLorentzVector p4_kaon1 = math::XYZTLorentzVector(mom_kaon1.X(),mom_kaon1.Y(),mom_kaon1.Z(),e_kaon1);
                 double m_kaon2 = twoMasses[iP];
                 math::XYZVector mom_kaon2 = negTrack.momentum();
                 double e_kaon2 = sqrt(m_kaon2*m_kaon2 + mom_kaon2.Mag2());
                 math::XYZTLorentzVector p4_kaon2 = math::XYZTLorentzVector(mom_kaon2.X(),mom_kaon2.Y(),mom_kaon2.Z(),e_kaon2);
                 reco::Candidate::LorentzVector vTT = p4_kaon1 + p4_kaon2;

                 reco::Candidate::LorentzVector vDiMuonT = dimuonCand->p4() + vTT;

                 massPionRefits[iP] = vDiMuonT.mass();

                 pkParticles.clear();
                 pkParticles.push_back(pFactory.particle(xTracks[0],muonMass,kinChi,kinNdf,muonSigma));
                 pkParticles.push_back(pFactory.particle(xTracks[1],muonMass,kinChi,kinNdf,muonSigma));
                 pkParticles.push_back(pFactory.particle(xTracks[2],oneMass,kinChi,kinNdf,trackSigma1));
                 pkParticles.push_back(pFactory.particle(xTracks[3],twoMass,kinChi,kinNdf,trackSigma2));

                 //RefCountedKinematicTree pkTree = pFitter.fit(pkParticles,jpsi_mtc);
                 KinematicConstrainedVertexFitter pFitter;
                 RefCountedKinematicTree pkTree;
                 pkTree = pFitter.fit(xParticles);

                 if (!pkTree->isEmpty()) {

                    pkTree->movePointerToTheTop();
                    RefCountedKinematicParticle fitPion = pkTree->currentParticle();
                    RefCountedKinematicVertex vPion = pkTree->currentDecayVertex();

                    if (fitPion->currentState().isValid())
                    {
                      massPionRefits_ref[iP] = fitPion->currentState().mass();
                      chi2PionRefits[iP] = vPion->chiSquared();
                      nDofPionRefits[iP] = (double)(vPion->degreesOfFreedom());
                      vProbPionRefits[iP] = ChiSquaredProbability(chi2PionRefits[iP],nDofPionRefits[iP]);
                    }
                    }
             }

           }


           if(IsMC_)
            {
              float hasHighGen = -1.0,hasLowGen = -1.0;

              if(theGenMap.isValid())
              {
                //posTrack
                auto refPosTrack = track->refAt(i);
                auto refNegTrack = track->refAt(j);

                if(theGenMap->contains(refPosTrack.id()))
                {
                 if(((*theGenMap)[edm::Ref<edm::View<pat::PackedCandidate>>(track, i)]).isNonnull())
                 {
                   auto genP = ((*theGenMap)[edm::Ref<edm::View<pat::PackedCandidate>>(track, i)]);
                   if(posTrack.pt()>=negTrack.pt() || !ptLeading)
                   {
                     DiMuonTTCand.addDaughter(*genP,"highKaonGen");
                     hasHighGen = 1.0;
                   }
                   else
                   {
                     DiMuonTTCand.addDaughter(*genP,"lowKaonGen");
                     hasLowGen = 1.0;
                   }
                  }
                }

                if(theGenMap->contains(refNegTrack.id()))
                {
                  if(((*theGenMap)[edm::Ref<edm::View<pat::PackedCandidate>>(track, j)]).isNonnull())
                  {
                    auto genP = ((*theGenMap)[edm::Ref<edm::View<pat::PackedCandidate>>(track, j)]);
                    if(posTrack.pt()<negTrack.pt() || !ptLeading)
                    {
                      DiMuonTTCand.addDaughter(*genP,"lowKaonGen");
                      hasHighGen = 1.0;
                    }
                    else
                    {
                      DiMuonTTCand.addDaughter(*genP,"highKaonGen");
                      hasLowGen = 1.0;
                    }
                  }
                }
              }
              // if(hasHighGen * hasLowGen >= 0.0)
              //   std::cout << "Has some gen ref " << std::endl;
              DiMuonTTCand.addUserFloat("hasHighGen",hasHighGen);
              DiMuonTTCand.addUserFloat("hasLowGen",hasLowGen);

            }

           DiMuonTTCand.addUserFloat("has_ref",candRef);
           DiMuonTTCand.addUserFloat("has_const_ref",cand_const_ref);

           DiMuonTTCand.addUserFloat("massPKRefit",massPionRefits[0]);
           DiMuonTTCand.addUserFloat("massKPRefit",massPionRefits[1]);
           DiMuonTTCand.addUserFloat("massPPRefit",massPionRefits[2]);

           DiMuonTTCand.addUserFloat("massPKRefitRef",massPionRefits_ref[0]);
           DiMuonTTCand.addUserFloat("massKPRefitRef",massPionRefits_ref[1]);
           DiMuonTTCand.addUserFloat("massPPRefitRef",massPionRefits_ref[2]);

           DiMuonTTCand.addUserFloat("vChi2PKRefit",chi2PionRefits[0]);
           DiMuonTTCand.addUserFloat("vChi2KPRefit",chi2PionRefits[1]);
           DiMuonTTCand.addUserFloat("vChi2PPRefit",chi2PionRefits[2]);

           DiMuonTTCand.addUserFloat("nDofPKRefit",nDofPionRefits[0]);
           DiMuonTTCand.addUserFloat("nDofKPRefit",nDofPionRefits[1]);
           DiMuonTTCand.addUserFloat("nDofPPRefit",nDofPionRefits[2]);

           DiMuonTTCand.addUserFloat("vProbPKRefit",vProbPionRefits[0]);
           DiMuonTTCand.addUserFloat("vProbKPRefit",vProbPionRefits[1]);
           DiMuonTTCand.addUserFloat("vProbPPRefit",vProbPionRefits[2]);

           DiMuonTTCandColl->push_back(DiMuonTTCand);
           candidates++;
           ncombo++;


         }
         } // loop over second track
       }   // loop on track candidates
     }

  if ( ncombo != DiMuonTTCandColl->size() ) std::cout <<"ncombo ("<<ncombo<< ") != DiMuonTTCand ("<<DiMuonTTCandColl->size()<<")"<< std::endl;
  if ( !dimuon->empty() )  ndimuon++;
  if ( ncombo > 0 ) nreco++;

  iEvent.put(std::move(DiMuonTTCandColl),product_name_);
  nevents++;
}

void DiMuonDiTrackProducer::endJob(){
  std::cout << "#########################################" << std::endl;
  std::cout << "DiMuonDiTrackFit Candidate producer report:" << std::endl;
  std::cout << "#########################################" << std::endl;
  std::cout << "Found " << nevents << " Events" << std::endl;
  std::cout << "Events with DiMuon candidates " << ndimuon << std::endl;
  std::cout << "Events with DiMuonDiTrack candidates " << nreco << std::endl;
  std::cout << "#########################################" << std::endl;
  std::cout << "Found " << candidates << " DiMuonDiTrack candidates." << std::endl;
  std::cout << "#########################################" << std::endl;
}

bool DiMuonDiTrackProducer::IsTheSame(const pat::PackedCandidate& tk, const pat::Muon& mu){
  float DeltaEta = fabs(mu.eta()- tk.eta());
  float DeltaP   = fabs(mu.p()- tk.p());
  float DeltaPt = ((tk.pt() - mu.pt())/tk.pt());

  if (DeltaEta < 0.02 && DeltaP < 0.02 && DeltaPt < 0.1) return true;
  return false;
}

pat::CompositeCandidate DiMuonDiTrackProducer::makeDiMuonTTCandidate(
                                          const pat::CompositeCandidate& dimuon,
				          const pat::CompositeCandidate& tt
                                         ){

  pat::CompositeCandidate DiMuonTCand;
  DiMuonTCand.addDaughter(dimuon,"dimuon");
  DiMuonTCand.addDaughter(tt,"ditrack");
  DiMuonTCand.setVertex(dimuon.vertex());
  DiMuonTCand.setCharge(tt.charge());

  reco::Candidate::LorentzVector vDiMuonT = dimuon.p4() + tt.p4();
  DiMuonTCand.setP4(vDiMuonT);

  return DiMuonTCand;

}

pat::CompositeCandidate DiMuonDiTrackProducer::makeTTCandidate(
                                          const pat::PackedCandidate& highTrack,
                                          const pat::PackedCandidate& lowTrack
                                         ){

  pat::CompositeCandidate TTCand;

  TTCand.addDaughter(lowTrack,"highTrack");
  TTCand.addDaughter(highTrack,"lowTrack");

  TTCand.setCharge(highTrack.charge()+lowTrack.charge());

  double m_kaon1 = MassTracks_[0];
  math::XYZVector mom_kaon1 = highTrack.momentum();
  double e_kaon1 = sqrt(m_kaon1*m_kaon1 + mom_kaon1.Mag2());
  math::XYZTLorentzVector p4_kaon1 = math::XYZTLorentzVector(mom_kaon1.X(),mom_kaon1.Y(),mom_kaon1.Z(),e_kaon1);
  double m_kaon2 = MassTracks_[1];
  math::XYZVector mom_kaon2 = lowTrack.momentum();
  double e_kaon2 = sqrt(m_kaon2*m_kaon2 + mom_kaon2.Mag2());
  math::XYZTLorentzVector p4_kaon2 = math::XYZTLorentzVector(mom_kaon2.X(),mom_kaon2.Y(),mom_kaon2.Z(),e_kaon2);
  reco::Candidate::LorentzVector vTT = p4_kaon1 + p4_kaon2;
  TTCand.setP4(vTT);

  return TTCand;
}


reco::Candidate::LorentzVector DiMuonDiTrackProducer::convertVector(const math::XYZTLorentzVectorF& v){

  return reco::Candidate::LorentzVector(v.x(),v.y(), v.z(), v.t());
}
//define this as a plug-in
DEFINE_FWK_MODULE(DiMuonDiTrackProducer);