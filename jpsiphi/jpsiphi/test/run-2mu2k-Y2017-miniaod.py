import FWCore.ParameterSet.Config as cms
process = cms.Process('PSIKK')

from FWCore.ParameterSet.VarParsing import VarParsing
from Y_MC_Files import *

options = VarParsing ('analysis')

options.register ('yMass',
				  4700,
				  VarParsing.multiplicity.singleton,
				  VarParsing.varType.int,
				  "MC sample Y mass ")

options.register ('trigger',
				  True,
				  VarParsing.multiplicity.singleton,
				  VarParsing.varType.bool,
				  "Adding triggers")

options.parseArguments()

#
# gen_file = "file:32B83273-030F-E811-9105-E0071B7AF7C0.root"
# input_file = "file:006425F0-6DED-E711-850C-0025904C66E8.root"
# mc_file = "file:py8_JPsiMM_EvtGen_13TeV_TuneCP5_cfi.root"
# mc_file = "file:02CA3723-CEF3-E711-B1CC-4C79BA1810EF.root"
# mc_file = "file:FCD01A2E-A6F5-E711-ACA1-003048F5ADF6.root"
# input_file = mc_file #gen_file

Y = str(options.yMass)

input_files = {"4700" : input_files_4700,"4500" : input_files_4500,"4300" : input_files_4300,"4100" : input_files_4100}
YMassCuts   = {"4700" : cms.vdouble(4.0,5.4),"4500" : cms.vdouble(3.9,5.1),"4300" : cms.vdouble(3.7,4.9),"4100" : cms.vdouble(3.5,4.7)}
motherPdgs  = {"4700" : 10441, "B" : 532 , "4100" : 20443, "4300": 20443, "4500": 10441}

motherPdg = motherPdgs[Y]
input_file = input_files[Y]
YMassCut = YMassCuts[Y]

process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("SimTracker.TrackerHitAssociation.tpClusterProducer_cfi")
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_ReReco_EOY17_v1')
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_ReReco_EOY17_v2') #F
process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v11')

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 500

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(input_file)
)

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

filename = "rootuple-2017_MC_Y_" + str(Y) + "_dimuonditrak.root"

process.TFileService = cms.Service("TFileService",
        fileName = cms.string(filename),
)

kaonmass = 0.493677
pionmass = 0.13957061

process.load("jpsiphi.jpsiphi.slimmedMuonsTriggerMatcher2017_cfi")
# process.load("jpsiphi.jpsiphi.slimmedTracksTriggerMatcher2017_cfi")

charmoniumHLT = [
#Phi
'HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi',
#JPsi
'HLT_DoubleMu4_JpsiTrkTrk_Displaced',
'HLT_DoubleMu4_JpsiTrk_Displaced',
'HLT_DoubleMu4_Jpsi_Displaced',
'HLT_DoubleMu4_3_Jpsi_Displaced',
'HLT_Dimuon20_Jpsi_Barrel_Seagulls',
'HLT_Dimuon25_Jpsi',
]

hltList = charmoniumHLT #muoniaHLT

hltpaths = cms.vstring(hltList)

hltpathsV = cms.vstring([h + '_v*' for h in hltList])

filters = cms.vstring(
                                #HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi
                                #'hltDoubleMu2JpsiDoubleTrkL3Filtered',
                                'hltDoubleTrkmumuFilterDoubleMu2Jpsi',
                                'hltJpsiTkTkVertexFilterPhiDoubleTrk1v2',
                                #HLT_DoubleMu4_JpsiTrkTrk_Displaced_v4
                                'hltDoubleMu4JpsiDisplacedL3Filtered'
                                'hltDisplacedmumuFilterDoubleMu4Jpsi',
                                'hltJpsiTkTkVertexFilterPhiKstar',
                                #HLT_DoubleMu4_JpsiTrk_Displaced_v12
                                #'hltDoubleMu4JpsiDisplacedL3Filtered',
                                'hltDisplacedmumuFilterDoubleMu4Jpsi',
                                #'hltJpsiTkVertexProducer',
                                #'hltJpsiTkVertexFilter',
                                #HLT_DoubleMu4_Jpsi_Displaced
                                #'hltDoubleMu4JpsiDisplacedL3Filtered',
                                #'hltDisplacedmumuVtxProducerDoubleMu4Jpsi',
                                'hltDisplacedmumuFilterDoubleMu4Jpsi',
                                #HLT_DoubleMu4_3_Jpsi_Displaced
                                #'hltDoubleMu43JpsiDisplacedL3Filtered',
                                'hltDisplacedmumuFilterDoubleMu43Jpsi',
                                #HLT_Dimuon20_Jpsi_Barrel_Seagulls
                                #'hltDimuon20JpsiBarrelnoCowL3Filtered',
                                'hltDisplacedmumuFilterDimuon20JpsiBarrelnoCow',
                                #HLT_Dimuon25_Jpsi
                                'hltDisplacedmumuFilterDimuon25Jpsis'
                                )

process.yfilter = cms.EDFilter("GenFilter",
								PdgId = cms.uint32(motherPdg)
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
        higherPuritySelection       = cms.string(""),
        lowerPuritySelection        = cms.string(""),
        dimuonSelection             = cms.string("2.95 < mass && mass < 3.25 && charge==0"),
        addCommonVertex             = cms.bool(True),
        addMuonlessPrimaryVertex    = cms.bool(False),
        addMCTruth                  = cms.bool(True),
        resolvePileUpAmbiguity      = cms.bool(True),
        HLTFilters                  = filters
)

process.JPsi2MuMuFilter = cms.EDProducer('DiMuonFilter',
      OniaTag             = cms.InputTag("JPsi2MuMuPAT"),
      singlemuonSelection = cms.string(""),
      dimuonSelection     = cms.string("2.95 < mass && mass < 3.25 && userFloat('vProb') > 0.01 && pt > 2.0"),
      do_trigger_match    = cms.bool(False),
      HLTFilters          = filters
)

process.PsiPhiProducer = cms.EDProducer('DiMuonDiTrakProducer',
    DiMuon = cms.InputTag('JPsi2MuMuPAT'),
    PFCandidates = cms.InputTag('packedPFCandidates'),
    TriggerInput            = cms.InputTag("unpackPatTriggers"),
    TriggerResults = cms.InputTag("TriggerResults", "", "HLT"),
    DiMuonMassCuts = cms.vdouble(2.95,3.25),      # J/psi mass window 3.096916 +/- 0.150
    TrakTrakMassCuts = cms.vdouble(1.0,1.04),  # phi mass window 1.019461 +/- .015
    DiMuonDiTrakMassCuts = YMassCut,            # b-hadron mass window
    MassTraks = cms.vdouble(kaonmass,kaonmass),         # traks masses
    OnlyBest  = cms.bool(False),
    Product = cms.string("DiMuonDiTrakCandidates"),
    Filters = filters,
    IsMC = cms.bool(True),
)


# process.PsiPhiFitter = cms.EDProducer('DiMuonDiTrakKinematicFit',
#     DiMuonDiTrak              = cms.InputTag('PsiPhiProducer','DiMuonDiTrakCandidates'),
#     DiMuonMass                = cms.double(3.096916),              # J/psi mass in GeV
#     DiMuonTrakTrakMassCuts    = YMassCut,            # b-hadron mass window
#     MassTraks                 = cms.vdouble(kaonmass,kaonmass),         # traks masses
#     Product                   = cms.string('DiMuonDiTrakCandidatesRef')
# )

process.PsiPhiFitter = cms.EDProducer('DiMuonDiTrakKinematicFit',
    DiMuonDiTrak              = cms.InputTag('PsiPhiProducer','DiMuonDiTrakCandidates'),
    JPsiMass                  = cms.double(3.096916),
    PhiMass                   = cms.double(1.019461),              # J/psi mass in GeV
    DiMuonTrakTrakMassCuts    = YMassCut,            # b-hadron mass window
    MassTraks                 = cms.vdouble(kaonmass,kaonmass),         # traks masses
    Product                   = cms.string('DiMuonDiTrakCandidatesRef')
)


process.rootuple = cms.EDAnalyzer('DiMuonDiTrakRootupler',
    dimuonditrk_cand = cms.InputTag('PsiPhiProducer','DiMuonDiTrakCandidates'),
    dimuonditrk_rf_cand = cms.InputTag("PsiPhiFitter","DiMuonDiTrakCandidatesRef"),
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    primaryVertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    TriggerResults = cms.InputTag("TriggerResults", "", "HLT"),
    isMC = cms.bool(True),
    OnlyBest = cms.bool(False),
    OnlyGen = cms.bool(False),
    Mother_pdg = cms.uint32(motherPdg), #20443 #10441
    JPsi_pdg = cms.uint32(443),
    Phi_pdg = cms.uint32(333),
    HLTs = hltpaths,
    Filters = filters,
    TreeName = cms.string('JPsi Phi Tree')
)

process.rootupleMuMu = cms.EDAnalyzer('DiMuonRootupler',
                          dimuons = cms.InputTag("JPsi2MuMuFilter"),
                          muons = cms.InputTag("replaceme"),
                          primaryVertices = cms.InputTag("offlinePrimaryVertices"),
                          TriggerResults = cms.InputTag("TriggerResults", "", "HLT"),
                          dimuon_pdgid = cms.uint32(443),
                          dimuon_mass_cuts = cms.vdouble(2.5,3.5),
                          isMC = cms.bool(True),
                          OnlyBest = cms.bool(False),
                          OnlyGen = cms.bool(False),
                          HLTs = hltpaths
                          )
if options.trigger:
    process.sequence = cms.Sequence(process.yfilter*
                         process.triggerSelection *
                         process.slimmedMuonsWithTriggerSequence *
                         process.unpackPatTriggers *
                         #process.softMuons *
                         process.JPsi2MuMuPAT *
                         process.JPsi2MuMuFilter*
                         process.PsiPhiProducer *
                         process.PsiPhiFitter *
                         process.rootuple *
                         #process.rootupleMuMu
                         )# * process.Phi2KKPAT * process.patSelectedTracks *process.rootupleKK)
else:
    process.sequence = cms.Sequence(
                         process.yfilter*
                         process.slimmedMuonsWithTriggerSequence *
                         process.unpackPatTriggers *
                         #process.softMuons *
                         process.JPsi2MuMuPAT *
                         process.JPsi2MuMuFilter*
                         process.PsiPhiProducer *
                         process.PsiPhiFitter *
                         process.rootuple *
                         #process.rootupleMuMu
                         )

process.p = cms.Path(process.sequence)
