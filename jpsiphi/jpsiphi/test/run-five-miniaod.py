import FWCore.ParameterSet.Config as cms
process = cms.Process('PSIKK')

from FWCore.ParameterSet.VarParsing import VarParsing

from bbbar_filelist import *
from bbbar_soft_list import *
from y4140_lhcb_filelist import *
from y4140_zero_filelist import *
from y4273_lhcb_filelist import *
from y4273_zero_filelist import *
from y4704_zero_filelist import *
from y4704_lhcb_filelist import *
from y4506_lhcb_filelist import *
from y4506_zero_filelist import *

par = VarParsing ('analysis')

par.register ('gtag',
                                  "101X_dataRun2_Prompt_v11",
                                  VarParsing.multiplicity.singleton,
                                  VarParsing.varType.string,
                                  "Global Tag")
par.register ('mc',
                                  "y4506_lhcb",
                                  VarParsing.multiplicity.singleton,
                                  VarParsing.varType.string,
                                  "MC Dataset")

par.register ('ss',
                                  False,
                                  VarParsing.multiplicity.singleton,
                                  VarParsing.varType.bool,
                                  "Do Same Sign")

par.register ('kMass',
                                  0.493677,
                                  VarParsing.multiplicity.singleton,
                                  VarParsing.varType.bool,
                                  "KMass")

par.register ('i',
                                  0,
                                  VarParsing.multiplicity.singleton,
                                  VarParsing.varType.int,
                                  "i")
par.parseArguments()

i = par.i

gen_file = "file:32B83273-030F-E811-9105-E0071B7AF7C0.root"
input_file = "file:006425F0-6DED-E711-850C-0025904C66E8.root"
mc_file = "file:py8_JPsiMM_EvtGen_13TeV_TuneCP5_cfi.root"
mc_file = "file:02CA3723-CEF3-E711-B1CC-4C79BA1810EF.root"
mc_file = "file:FCD01A2E-A6F5-E711-ACA1-003048F5ADF6.root"
runb2018 = "file:1401AF4A-447C-E811-8EEB-FA163E35DF95.root"
input_file = runb2018 #gen_file

n=400
filename = par.mc

fileLists = {"bbbar_hard" : bbbar_file_list, "y4273_zero" : y4273_zero_filelist, "y4273_lhcb" : y4273_lhcb_filelist ,
             "y4140_lhcb" : y4140_lhcb_filelist, "y4140_zero" : y4140_zero_filelist,
             "y4506_lhcb" : y4506_lhcb_filelist, "y4506_zero" : y4506_zero_filelist,
             "y4704_lhcb" : y4704_lhcb_filelist, "y4704_zero" : y4704_zero_filelist }

filelist = fileLists[filename] #bbbar_soft_list#bbbar_file_list
size = (len(filelist) + n) / n
input_file = filelist[min(i*size,len(filelist)):min((i+1)*size,len(filelist))]
print min((i+1)*size,len(filelist))

process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("SimTracker.TrackerHitAssociation.tpClusterProducer_cfi")
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_ReReco_EOY17_v1')
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_ReReco_EOY17_v2') #F
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v11')
process.GlobalTag = GlobalTag(process.GlobalTag, par.gtag)

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 500

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(input_file)
)

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.TFileService = cms.Service("TFileService",
        fileName = cms.string('rootuple-2017-dimuonditrak.root'),
)

kaonmass = 0.493677
pionmass = 0.13957061

process.load("jpsiphi.jpsiphi.slimmedMuonsTriggerMatcher2017_cfi")
# process.load("jpsiphi.jpsiphi.slimmedTracksTriggerMatcher2017_cfi")

charmoniumHLT = [
#Phi
'HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi1p05',
#JPsi
#'HLT_DoubleMu4_JpsiTrkTrk_Displaced',
#'HLT_DoubleMu4_JpsiTrk_Displaced',
#'HLT_DoubleMu4_Jpsi_Displaced',
#'HLT_DoubleMu4_3_Jpsi_Displaced',
#'HLT_Dimuon20_Jpsi_Barrel_Seagulls',
#'HLT_Dimuon25_Jpsi',
]

hltList = charmoniumHLT #muoniaHLT

hltpaths = cms.vstring(hltList)

hltpathsV = cms.vstring([h + '_v*' for h in hltList])

filters = cms.vstring(
                                #HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi
                                #'hltDoubleMu2JpsiDoubleTrkL3Filtered',
                                'hltDoubleTrkmumuFilterDoubleMu2Jpsi',
								'hltJpsiTkTkVertexFilterPhiDoubleTrk1v1',
                                'hltJpsiTkTkVertexFilterPhiDoubleTrk1v2',
								'hltJpsiTkTkVertexFilterPhiDoubleTrk1v3',
								'hltJpsiTkTkVertexFilterPhiDoubleTrk1v4',
								'hltJpsiTkTkVertexFilterPhiDoubleTrk1v5',
								'hltJpsiTkTkVertexFilterPhiDoubleTrk1v6',
								'hltJpsiTrkTrkVertexProducerPhiDoubleTrk1v1',
								'hltJpsiTrkTrkVertexProducerPhiDoubleTrk1v2',
								'hltJpsiTrkTrkVertexProducerPhiDoubleTrk1v3',
								'hltJpsiTrkTrkVertexProducerPhiDoubleTrk1v4',
								'hltJpsiTrkTrkVertexProducerPhiDoubleTrk1v5',
								'hltJpsiTrkTrkVertexProducerPhiDoubleTrk1v6',
                                #HLT_DoubleMu4_JpsiTrkTrk_Displaced_v4
                                # 'hltDoubleMu4JpsiDisplacedL3Filtered'
                                # 'hltDisplacedmumuFilterDoubleMu4Jpsi',
                                # 'hltJpsiTkTkVertexFilterPhiKstar',
                                # #HLT_DoubleMu4_JpsiTrk_Displaced_v12
                                # #'hltDoubleMu4JpsiDisplacedL3Filtered',
                                # 'hltDisplacedmumuFilterDoubleMu4Jpsi',
                                # #'hltJpsiTkVertexProducer',
                                # #'hltJpsiTkVertexFilter',
                                # #HLT_DoubleMu4_Jpsi_Displaced
                                # #'hltDoubleMu4JpsiDisplacedL3Filtered',
                                # #'hltDisplacedmumuVtxProducerDoubleMu4Jpsi',
                                # 'hltDisplacedmumuFilterDoubleMu4Jpsi',
                                # #HLT_DoubleMu4_3_Jpsi_Displaced
                                # #'hltDoubleMu43JpsiDisplacedL3Filtered',
                                # 'hltDisplacedmumuFilterDoubleMu43Jpsi',
                                # #HLT_Dimuon20_Jpsi_Barrel_Seagulls
                                # #'hltDimuon20JpsiBarrelnoCowL3Filtered',
                                # 'hltDisplacedmumuFilterDimuon20JpsiBarrelnoCow',
                                # #HLT_Dimuon25_Jpsi
                                # 'hltDisplacedmumuFilterDimuon25Jpsis'
                                )

process.triggerSelection = cms.EDFilter("TriggerResultsFilter",
                                        triggerConditions = cms.vstring(hltpathsV),
                                        hltResults = cms.InputTag( "TriggerResults", "", "HLT" ),
                                        l1tResults = cms.InputTag( "" ),
                                        throw = cms.bool(False)
                                        )

process.unpackPatTriggers = cms.EDProducer("PATTriggerObjectStandAloneUnpacker",
  patTriggerObjectsStandAlone = cms.InputTag( 'slimmedPatTrigger' ), #selectedPatTrigger for MC
  triggerResults              = cms.InputTag( 'TriggerResults::HLT' ),
  unpackFilterLabels          = cms.bool( True )
)
# process.softMuons = cms.EDFilter('PATMuonSelector',
#    src = cms.InputTag('slimmedMuonsWithTrigger'),
#    cut = cms.string('muonID(\"TMOneStationTight\")'
#                     ' && abs(innerTrack.dxy) < 0.3'
#                     ' && abs(innerTrack.dz)  < 20.'
#                     ' && innerTrack.hitPattern.trackerLayersWithMeasurement > 5'
#                     ' && innerTrack.hitPattern.pixelLayersWithMeasurement > 0'
#                     ' && innerTrack.quality(\"highPurity\")'
#    ),
#    filter = cms.bool(True)
# )
process.JPsi2MuMuPAT = cms.EDProducer('DiMuonProducerPAT',
        muons                       = cms.InputTag('slimmedMuonsWithTrigger'),
        primaryVertexTag            = cms.InputTag('offlineSlimmedPrimaryVertices'),
        beamSpotTag                 = cms.InputTag('offlineBeamSpot'),
        dimuonSelection             = cms.string("2.95 < mass && mass < 3.25 && charge==0"),
        addCommonVertex             = cms.bool(True),
        addMuonlessPrimaryVertex    = cms.bool(False),
        addMCTruth                  = cms.bool(True),
        resolvePileUpAmbiguity      = cms.bool(True),
        TriggerResults              = cms.InputTag("TriggerResults", "", "HLT"),
        HLTFilters                  = filters,
        TriggerInput                = cms.InputTag("unpackPatTriggers"),
)

process.JPsi2MuMuFilter = cms.EDProducer('DiMuonFilter',
      OniaTag             = cms.InputTag("JPsi2MuMuPAT"),
      singlemuonSelection = cms.string(""),
      dimuonSelection     = cms.string("2.95 < mass && mass < 3.25 && userFloat('vProb') > 0.01 && pt > 2.0"),
      do_trigger_match    = cms.bool(False),
      HLTFilters          = filters
)

# process.PsiPhiProducer = cms.EDProducer('DiMuonDiTrakProducer',
#     DiMuon = cms.InputTag('JPsi2MuMuPAT'),
#     PFCandidates = cms.InputTag('packedPFCandidates'),
#     TriggerInput            = cms.InputTag("unpackPatTriggers"),
#     TriggerResults = cms.InputTag("TriggerResults", "", "HLT"),
#     DiMuonMassCuts = cms.vdouble(2.95,3.25),      # J/psi mass window 3.096916 +/- 0.150
#     TrakTrakMassCuts = cms.vdouble(1.0,1.04),  # phi mass window 1.019461 +/- .015
#     DiMuonDiTrakMassCuts = cms.vdouble(4.0,5.8),            # b-hadron mass window
#     MassTraks = cms.vdouble(kaonmass,kaonmass),         # traks masses
#     OnlyBest  = cms.bool(False),
#     Product = cms.string("DiMuonDiTrakCandidates"),
#     Filters = filters,
#     IsMC = cms.bool(True),
# )

# process.PsiPhiFitter = cms.EDProducer('DiMuonDiTrakKinematicFit',
#     DiMuonDiTrak              = cms.InputTag('PsiPhiProducer','DiMuonDiTrakCandidates'),
#     DiMuonMass                = cms.double(3.096916),              # J/psi mass in GeV
#     DiMuonTrakTrakMassCuts    = cms.vdouble(4.1,5.5),            # b-hadron mass window
#     MassTraks                 = cms.vdouble(kaonmass,kaonmass),         # traks masses
#     Product                   = cms.string('DiMuonDiTrakCandidatesRef')
# )

# process.rootuple = cms.EDAnalyzer('DiMuonDiTrakRootupler',
#     dimuonditrk_cand = cms.InputTag('PsiPhiProducer','DiMuonDiTrakCandidates'),
#     dimuonditrk_rf_cand = cms.InputTag("PsiPhiFitter","DiMuonDiTrakCandidatesRef"),
#     beamSpotTag = cms.InputTag("offlineBeamSpot"),
#     primaryVertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
#     TriggerResults = cms.InputTag("TriggerResults", "", "HLT"),
#     isMC = cms.bool(True),
#     OnlyBest = cms.bool(False),
#     OnlyGen = cms.bool(False),
#     Mother_pdg = cms.uint32(10441), #20443 #10441
#     JPsi_pdg = cms.uint32(443),
#     Phi_pdg = cms.uint32(333),
#     HLTs = hltpaths,
#     Filters = filters,
#     TreeName = cms.string('JPsi Phi Tree')
# )


process.PsiPhiProducer = cms.EDProducer('DiMuonDiTrakProducerFit',
    DiMuon = cms.InputTag('JPsi2MuMuPAT'),
    PFCandidates = cms.InputTag('packedPFCandidates'),
	beamSpotTag                 = cms.InputTag('offlineBeamSpot'),
	primaryVertexTag = cms.InputTag("offlineSlimmedPrimaryVertices"),
    TriggerInput            = cms.InputTag("unpackPatTriggers"),
    TriggerResults = cms.InputTag("TriggerResults", "", "HLT"),
    DiMuonMassCuts = cms.vdouble(2.95,3.25),      # J/psi mass window 3.096916 +/- 0.150
    TrakTrakMassCuts = cms.vdouble(1.0,1.04),  # phi mass window 1.019461 +/- .015
    DiMuonDiTrakMassCuts = cms.vdouble(4.0,5.8),            # b-hadron mass window
    MassTraks = cms.vdouble(kaonmass,kaonmass),         # traks masses
	JPsiMass = cms.double(3.096916),
	PhiMass  = cms.double(1.019461),
    OnlyBest  = cms.bool(False),
    Product = cms.string("DiMuonDiTrakCandidates"),
    Filters = filters,
    IsMC = cms.bool(False),
    AddMCTruth = cms.bool(False),
	DoDouble = cms.bool(False),
	AddSS    = cms.bool(True),
	PionRefit = cms.bool(True)
)

process.FiveTracksProducer = cms.EDProducer('FiveTracksProducerFit',
    DiMuoDiTrak = cms.InputTag('PsiPhiProducer','DiMuonDiTrakCandidates'),
    PFCandidates = cms.InputTag('packedPFCandidates'),
	beamSpotTag                 = cms.InputTag('offlineBeamSpot'),
	primaryVertexTag = cms.InputTag("offlineSlimmedPrimaryVertices"),
    TriggerInput            = cms.InputTag("unpackPatTriggers"),
    TriggerResults = cms.InputTag("TriggerResults", "", "HLT"),      # b-hadron mass window
    FiveTrakCuts = cms.vdouble(4.0,6.8),         # traks masses
)

# process.PsiPhiFitter = cms.EDProducer('DiMuonDiTrakKinematicFit',
#     DiMuonDiTrak              = cms.InputTag('PsiPhiProducer','DiMuonDiTrakCandidates'),
#     DiMuonMass                = cms.double(3.096916),              # J/psi mass in GeV
#     DiMuonTrakTrakMassCuts    = YMassCut,            # b-hadron mass window
#     MassTraks                 = cms.vdouble(kaonmass,kaonmass),         # traks masses
#     Product                   = cms.string('DiMuonDiTrakCandidatesRef')
# )

# process.PsiPhiFitter = cms.EDProducer('DiMuonDiTrakFits',
#     DiMuonDiTrak              = cms.InputTag('PsiPhiProducer','DiMuonDiTrakCandidates'),
#     JPsiMass                  = cms.double(3.096916),
#     PhiMass                   = cms.double(1.019461),              # J/psi mass in GeV
#     DiMuonTrakTrakMassCuts    = YMassCut,            # b-hadron mass window
#     MassTraks                 = cms.vdouble(kaonmass,kaonmass),         # traks masses
#     Product                   = cms.string('DiMuonDiTrakCandidatesRef')
# )


# process.rootuple = cms.EDAnalyzer('DiMuonDiTrakRootuplerFit',
#     dimuonditrk_cand = cms.InputTag('PsiPhiProducer','DiMuonDiTrakCandidates'),
#     beamSpotTag = cms.InputTag("offlineBeamSpot"),
#     primaryVertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
#     TriggerResults = cms.InputTag("TriggerResults", "", "HLT"),
#     isMC = cms.bool(False),
#     OnlyBest = cms.bool(False),
#     OnlyGen = cms.bool(False),
#     Mother_pdg = cms.uint32(20443), #20443 #10441
#     JPsi_pdg = cms.uint32(443),
#     Phi_pdg = cms.uint32(333),
#     HLTs = hltpaths,
#     Filters = filters,
#     TreeName = cms.string('JPsiPhiTree')
# )

process.rootuple = cms.EDAnalyzer('DiMuonDiTrakFiveRootuplerFit',
    DiMuoDiTrak = cms.InputTag('PsiPhiProducer','DiMuonDiTrakCandidates'),
	FiveTrakPos = cms.InputTag('FiveTracksProducer','FiveTracksPos'),
	FiveTrakNeg = cms.InputTag('FiveTracksProducer','FiveTracksNeg'),
	FiveTrakNeu = cms.InputTag('FiveTracksProducer','FiveTracksNeu'),
    PrimaryVertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    TriggerResults = cms.InputTag("TriggerResults", "", "HLT"),
    isMC = cms.bool(False),
    OnlyBest = cms.bool(False),
    OnlyGen = cms.bool(False),
    Mother_pdg = cms.uint32(20443), #20443 #10441
    JPsi_pdg = cms.uint32(443),
    Phi_pdg = cms.uint32(333),
    HLTs = hltpaths,
    Filters = filters,
    TreeName = cms.string('JPsiPhiTree')
)


process.rootuplefive = cms.EDAnalyzer('FiveTracksRootupler',
    FiveTracksCand = cms.InputTag('FiveTracksProducer','FiveTracksPos'),
	beamSpotTag                 = cms.InputTag('offlineBeamSpot'),
    PrimaryVertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    TriggerResults = cms.InputTag("TriggerResults", "", "HLT"),
    isMC = cms.bool(False),
    OnlyBest = cms.bool(False),
    OnlyGen = cms.bool(False),
    Mother_pdg = cms.uint32(20443), #20443 #10441
    JPsi_pdg = cms.uint32(443),
    Phi_pdg = cms.uint32(333),
    HLTs = hltpaths,
    Filters = filters,
    TreeName = cms.string('FiveTracksTree')
)


process.rootupleMuMu = cms.EDAnalyzer('DiMuonRootupler',
                          dimuons = cms.InputTag("JPsi2MuMuFilter"),
                          muons = cms.InputTag("replaceme"),
                          primaryVertices = cms.InputTag("offlinePrimaryVertices"),
                          TriggerResults = cms.InputTag("TriggerResults", "", "HLT"),
                          dimuon_pdgid = cms.uint32(443),
                          dimuon_mass_cuts = cms.vdouble(2.5,3.5),
                          isMC = cms.bool(False),
                          OnlyBest = cms.bool(False),
                          OnlyGen = cms.bool(False),
                          HLTs = hltpaths
                          )

process.p = cms.Path(process.triggerSelection *
                     process.slimmedMuonsWithTriggerSequence *
                     process.unpackPatTriggers *
                     #process.softMuons *
                     process.JPsi2MuMuPAT *
                     process.JPsi2MuMuFilter*
                     process.PsiPhiProducer *
                     #process.PsiPhiFitter *
                     proces.FiveTracksProducer *
					 process.rootuplefive *
                     #process.rootuplefive *
                     process.rootupleMuMu)# * process.Phi2KKPAT * process.patSelectedTracks *process.rootupleKK)