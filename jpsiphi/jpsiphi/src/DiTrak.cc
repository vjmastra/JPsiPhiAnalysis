#include "../interface/DiTrak.h"

float DiTrakPAT::DeltaR(const pat::PackedCandidate t1, const pat::TriggerObjectStandAlone t2)
{
   float p1 = t1.phi();
   float p2 = t2.phi();
   float e1 = t1.eta();
   float e2 = t2.eta();
   auto dp=std::abs(p1-p2); if (dp>float(M_PI)) dp-=float(2*M_PI);

   return sqrt((e1-e2)*(e1-e2) + dp*dp);
}

bool DiTrakPAT::MatchByDRDPt(const pat::PackedCandidate t1, const pat::TriggerObjectStandAlone t2)
{
  return (fabs(t1.pt()-t2.pt())/t2.pt()<maxDPtRel &&
	DeltaR(t1,t2) < maxDeltaR);
}

UInt_t DiTrakPAT::getTriggerBits(const edm::Event& iEvent, const edm::Handle< edm::TriggerResults >& triggerResults_handle) {

  UInt_t trigger = 0;
  const edm::TriggerNames & names = iEvent.triggerNames( *triggerResults_handle );

     unsigned int NTRIGGERS = HLTs_.size();

     for (unsigned int i = 0; i < NTRIGGERS; i++) {
        for (int version = 1; version < 20; version++) {
           std::stringstream ss;
           ss << HLTs_[i] << "_v" << version;
           unsigned int bit = names.triggerIndex(edm::InputTag(ss.str()).label());
           if (bit < triggerResults_handle->size() && triggerResults_handle->accept(bit) && !triggerResults_handle->error(bit)) {
              trigger += (1<<i);
              break;
           }
        }
     }

   return trigger;
}

DiTrakPAT::DiTrakPAT(const edm::ParameterSet& iConfig):
traks_(consumes<std::vector<pat::PackedCandidate>>(iConfig.getParameter<edm::InputTag>("Traks"))),
TriggerCollection_(consumes<std::vector<pat::TriggerObjectStandAlone>>(iConfig.getParameter<edm::InputTag>("TriggerInput"))),
triggerResults_Label(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("TriggerResults"))),
thebeamspot_(consumes<reco::BeamSpot>(iConfig.getParameter<edm::InputTag>("BeamSpot"))),
thePVs_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("PrimaryVertex"))),
ditrakSelection_(iConfig.existsAs<std::string>("DiTrakCuts") ? iConfig.getParameter<std::string>("DiTrakCuts") : ""),
massTraks_(iConfig.getParameter<std::vector<double>>("TraksMasses")),
HLTs_(iConfig.getParameter<std::vector<std::string>>("HLTs")),
HLTFilters_(iConfig.getParameter<std::vector<std::string>>("Filters"))
{
  produces<pat::CompositeCandidateCollection>();

  maxDeltaR = 0.01;
  maxDPtRel = 2.0;

}


DiTrakPAT::~DiTrakPAT()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}

const pat::CompositeCandidate DiTrakPAT::makeTTTriggerCandidate(
                                          const pat::TriggerObjectStandAlone& trakP,
                                          const pat::TriggerObjectStandAlone& trakN
                                         ){

  pat::CompositeCandidate TTCand;
  TTCand.addDaughter(trakP,"trigP");
  TTCand.addDaughter(trakN,"trigN");
  TTCand.setCharge(trakP.charge()+trakN.charge());

  double m_kaon1 = massTraks_[0];
  math::XYZVector mom_kaon1 = trakP.momentum();
  double e_kaon1 = sqrt(m_kaon1*m_kaon1 + mom_kaon1.Mag2());
  math::XYZTLorentzVector p4_kaon1 = math::XYZTLorentzVector(mom_kaon1.X(),mom_kaon1.Y(),mom_kaon1.Z(),e_kaon1);
  double m_kaon2 = massTraks_[1];
  math::XYZVector mom_kaon2 = trakN.momentum();
  double e_kaon2 = sqrt(m_kaon2*m_kaon2 + mom_kaon2.Mag2());
  math::XYZTLorentzVector p4_kaon2 = math::XYZTLorentzVector(mom_kaon2.X(),mom_kaon2.Y(),mom_kaon2.Z(),e_kaon2);
  reco::Candidate::LorentzVector vTT = p4_kaon1 + p4_kaon2;
  TTCand.setP4(vTT);

  return TTCand;
}

const pat::CompositeCandidate DiTrakPAT::makeTTCandidate(
                                          const pat::PackedCandidate& trakP,
                                          const pat::PackedCandidate& trakN
                                         ){

  pat::CompositeCandidate trktrkcand;
  trktrkcand.addDaughter(trakP,"trakP");
  trktrkcand.addDaughter(trakN,"trakN");
  trktrkcand.setCharge(trakP.charge()+trakN.charge());

  double m_trakP = massTraks_[0];
  math::XYZVector mom_trakP = trakP.momentum();
  double e_trakP = sqrt(m_trakP*m_trakP + mom_trakP.Mag2());
  math::XYZTLorentzVector p4_trakP = math::XYZTLorentzVector(mom_trakP.X(),mom_trakP.Y(),mom_trakP.Z(),e_trakP);
  double m_trakN = massTraks_[1];
  math::XYZVector mom_trakN = trakN.momentum();
  double e_trakN = sqrt(m_trakN*m_trakN + mom_trakN.Mag2());
  math::XYZTLorentzVector p4_trakN = math::XYZTLorentzVector(mom_trakN.X(),mom_trakN.Y(),mom_trakN.Z(),e_trakN);
  reco::Candidate::LorentzVector vTT = p4_trakP + p4_trakN;
  trktrkcand.setP4(vTT);

  return trktrkcand;
}


void
DiTrakPAT::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;
  typedef Candidate::LorentzVector LorentzVector;

  std::unique_ptr<pat::CompositeCandidateCollection> trakCollection(new pat::CompositeCandidateCollection);

  edm::Handle<std::vector<pat::PackedCandidate> > traks;
  iEvent.getByToken(traks_,traks);

  Vertex thePrimaryV;

  ESHandle<MagneticField> magneticField;
  iSetup.get<IdealMagneticFieldRecord>().get(magneticField);
  const MagneticField* field = magneticField.product();

  edm::Handle<BeamSpot> theBeamSpot;
  iEvent.getByToken(thebeamspot_,theBeamSpot);
  BeamSpot bs = *theBeamSpot;

  edm::Handle<VertexCollection> priVtxs;
  iEvent.getByToken(thePVs_, priVtxs);
  if ( priVtxs->begin() != priVtxs->end() ) {
    thePrimaryV = Vertex(*(priVtxs->begin()));
  }
  else {
    thePrimaryV = Vertex(bs.position(), bs.covariance3D());
  }

  edm::Handle< edm::TriggerResults > triggerResults_handle;
  iEvent.getByToken( triggerResults_Label , triggerResults_handle);

  const edm::TriggerNames & names = iEvent.triggerNames( *triggerResults_handle );

  int trigger = -1;

  if (triggerResults_handle.isValid())
    trigger = getTriggerBits(iEvent,triggerResults_handle);
  else std::cout << "*** NO triggerResults found " << iEvent.id().run() << "," << iEvent.id().event() << std::endl;

  edm::ESHandle<TransientTrackBuilder> theTTBuilder;
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theTTBuilder);
  KalmanVertexFitter vtxFitter(true);

  pat::TriggerObjectStandAloneCollection filteredColl, matchedColl;
  std::vector< pat::PackedCandidate> filteredTracks;
  std::vector < UInt_t > filterResults;

  if( trigger>=0 )
  for ( size_t iTrigObj = 0; iTrigObj < triggerColl->size(); ++iTrigObj ) {

    pat::TriggerObjectStandAlone unPackedTrigger( triggerColl->at( iTrigObj ) );

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

  //Matching

  if( trigger>=0 )
  for (std::vector<pat::PackedCandidate>::const_iterator trak = trakColl->begin(), trakend=trakColl->end(); trak!= trakend; ++trak)
  {
    bool matched = false;
    for (std::vector<pat::TriggerObjectStandAlone>::const_iterator trigger = filteredColl.begin(), triggerEnd=filteredColl.end(); trigger!= triggerEnd; ++trigger)
    {
      if(MatchByDRDPt(*trak,*trigger))
      {
        if(matched)
        {
          if(DeltaR(*trak,matchedColl.back()) > DeltaR(*trak,*trigger))
          {
            matchedColl.pop_back();
            matchedColl.push_back(*trigger);

          }
        }

        if(!matched)
          {
            filteredTracks.push_back(*trak);
            matchedColl.push_back(*trigger);
          }

        matched = true;
      }
    }
  }

  // ParticleMass trakP_mass = massTraks_[0];
  // ParticleMass trakN_mass = massTraks_[1];

  vector<double> ttMasses;
  ttMasses.push_back(massTraks_[0]);
  ttMasses.push_back(massTraks_[1]);

  // float trakP_sigma = trakP_mass*1.e-6;
  // float trakN_sigma = trakN_mass*1.e-6;

  float vProb, vNDF, vChi2, minDz = 999999.;
  float cosAlpha, ctauPV, ctauErrPV, dca;
  float l_xy, lErr_xy;

  if( trigger>=0 )
  for (size_t i = 0; i < filteredTracks.size(); i++)
  {
    auto posTrack = filteredTracks.at(i);

    if(posTrack.charge() <= 0 ) continue;
    if(posTrack.pt()<0.5) continue;
    if(fabs(posTrack.pdgId())!=211) continue;
    if(!posTrack.hasTrackDetails()) continue;

    for (size_t j = 0; j < filteredTracks.size(); j++){

      vProb = -1.0; vNDF = -1.0; vChi2 = -1.0;
      cosAlpha = -1.0; ctauPV = -1.0; ctauErrPV = -1.0;
      dca = -1.0; minDz = 999999.; dca = 1E20;

      if (i == j) continue;

      auto negTrack = filteredTracks.at(j);

      if(negTrack.charge() >= 0 ) continue;
      if(negTrack.pt()<0.5) continue;
      if(fabs(negTrack.pdgId())!=211) continue;
      if(!negTrack.hasTrackDetails()) continue;

      pat::CompositeCandidate trktrkcand = makeTTCandidate(posTrack,negTrack);
      pat::CompositeCandidate TTTrigger = makeTTTriggerCandidate(matchedColl[i],matchedColl[j]);

      vector<TransientVertex> pvs;

      if(!ditrakSelection_(trktrkcand)) continue;

      vector<TransientTrack> tt_ttks;
      tt_ttks.push_back(theTTBuilder->build(negTrack.bestTrack()));  // pass the reco::Track, not  the reco::TrackRef (which can be transient)
      tt_ttks.push_back(theTTBuilder->build(posTrack.bestTrack()));

      TransientVertex ttVertex = vtxFitter.vertex(tt_ttks);
      CachingVertex<5> VtxForInvMass = vtxFitter.vertex( tt_ttks );

      LorentzVector trktrk = posTrack.p4() + negTrack.p4();

      Measurement1D MassWErr(posTrack.mass(),-9999.);
      if ( field->nominalValue() > 0 )
          MassWErr = massCalculator.invariantMass( VtxForInvMass, ttMasses );
      else
          ttVertex = TransientVertex();                      // with no arguments it is invalid

      if (!(ttVertex.isValid()))
          continue;

      vChi2 = ttVertex.totalChiSquared();
      vNDF  = ttVertex.degreesOfFreedom();
      vProb = TMath::Prob(vChi2,(int)vNDF);

      //Vertex parameters
      TVector3 vtx,vtx3D;
      TVector3 pvtx,pvtx3D;
      VertexDistanceXY vdistXY;

      vtx.SetXYZ(ttVertex.position().x(),ttVertex.position().y(),0);
      vtx3D.SetXYZ(ttVertex.position().x(),ttVertex.position().y(),ttVertex.position().z());
      TVector3 pperp(trktrk.px(), trktrk.py(), 0);
      TVector3 pperp3D(trktrk.px(), trktrk.py(), trktrk.pz());
      AlgebraicVector3 vpperp(pperp.x(),pperp.y(),0);
      AlgebraicVector3 vpperp3D(pperp.x(),pperp.y(),pperp.z());

      //Resolving pileup ambiguity with two trak min distance
      TwoTrackMinimumDistance ttmd;
      bool status = ttmd.calculate( GlobalTrajectoryParameters(
        GlobalPoint(ttVertex.position().x(), ttVertex.position().y(), ttVertex.position().z()),
        GlobalVector(trktrkcand.px(),trktrkcand.py(),trktrkcand.pz()),TrackCharge(0),&(*magneticField)),
        GlobalTrajectoryParameters(
          GlobalPoint(bs.position().x(), bs.position().y(), bs.position().z()),
          GlobalVector(bs.dxdz(), bs.dydz(), 1.),TrackCharge(0),&(*magneticField)));

      float extrapZ=-9E20;

      if (status) extrapZ=ttmd.points().first.z();

      for(VertexCollection::const_iterator itv = priVtxs->begin(), itvend = priVtxs->end(); itv != itvend; ++itv)
      {
          float deltaZ = fabs(extrapZ - itv->position().z()) ;
          if ( deltaZ < minDz ) {
              minDz = deltaZ;
              thePrimaryV = Vertex(*itv);
            }
        }

      //Distance of Closest Approach
      TrajectoryStateClosestToPoint mu1TS = tt_ttks[0].impactPointTSCP();
      TrajectoryStateClosestToPoint mu2TS = tt_ttks[1].impactPointTSCP();

      if (mu1TS.isValid() && mu2TS.isValid()) {
        ClosestApproachInRPhi cApp;
        cApp.calculate(mu1TS.theState(), mu2TS.theState());
        if (cApp.status() ) dca = cApp.distance();
      }

      //Lifetime calculations
      pvtx.SetXYZ(thePrimaryV.position().x(),thePrimaryV.position().y(),0);
      TVector3 vdiff = vtx - pvtx;
      cosAlpha = vdiff.Dot(pperp)/(vdiff.Perp()*pperp.Perp());

      Measurement1D distXY = vdistXY.distance(Vertex(ttVertex), thePrimaryV);
      ctauPV = distXY.value()*cosAlpha * trktrkcand.mass()/pperp.Perp();

      GlobalError v1e = (Vertex(ttVertex)).error();
      GlobalError v2e = thePrimaryV.error();
      AlgebraicSymMatrix33 vXYe = v1e.matrix()+ v2e.matrix();
      ctauErrPV = sqrt(ROOT::Math::Similarity(vpperp,vXYe))*trktrkcand.mass()/(pperp.Perp2());

      AlgebraicVector3 vDiff;
      vDiff[0] = vdiff.x(); vDiff[1] = vdiff.y(); vDiff[2] = 0 ;
      l_xy = vdiff.Perp();
      lErr_xy = sqrt(ROOT::Math::Similarity(vDiff,vXYe)) / vdiff.Perp();

      trktrkcand.addDaughter(TTTrigger,"triggerTrakTrak");
      trktrkcand.addDaughter(matchedColl[i],"negTrig");
      trktrkcand.addDaughter(matchedColl[j],"posTrig");

      trktrkcand.addUserFloat("vNChi2",vChi2/vNDF);
      trktrkcand.addUserFloat("vProb",vProb);
      trktrkcand.addUserFloat("DCA", dca );
      trktrkcand.addUserFloat("MassErr",MassWErr.error());
      trktrkcand.addUserFloat("ctauPV",ctauPV);
      trktrkcand.addUserFloat("ctauErrPV",ctauErrPV);
      trktrkcand.addUserFloat("lxy",l_xy);
      trktrkcand.addUserFloat("lErrxy",lErr_xy);
      trktrkcand.addUserFloat("cosAlpha",cosAlpha);
      trktrkcand.addUserData("thePV",Vertex(thePrimaryV));
      trktrkcand.addUserData("theVertex",Vertex(ttVertex));

      trktrkcand.addUserData("vX",Vertex(ttVertex).x());
      trktrkcand.addUserData("vY",Vertex(ttVertex).y());
      trktrkcand.addUserData("vZ",Vertex(ttVertex).z());
      trktrkcand.addUserData("vT",Vertex(ttVertex).t());

      trktrkcand.addUserData("vXErr",Vertex(ttVertex).xError());
      trktrkcand.addUserData("vYErr",Vertex(ttVertex).yError());
      trktrkcand.addUserData("vZErr",Vertex(ttVertex).zError());
      trktrkcand.addUserData("vTErr",Vertex(ttVertex).tError());

      trakCollection->push_back(trktrkcand);


    } // loop over second track
  }

  if( trigger>=0 )
  {
    std::sort(trakCollection->begin(),trakCollection->end(),vPComparator_);
    iEvent.put(std::move(trakCollection));
  }
}


// ------------ method called once each job just before starting event loop  ------------
void
DiTrakPAT::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
DiTrakPAT::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(DiTrakPAT);
