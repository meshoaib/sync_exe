## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *


## ------------------------------------------------------
#  NOTE: you can use a bunch of core tools of PAT to
#  taylor your PAT configuration; for a few examples
#  uncomment the lines below
## ------------------------------------------------------
from PhysicsTools.PatAlgos.tools.coreTools import *

## remove MC matching from the default sequence
# removeMCMatching(process, ['Muons'])
# runOnData(process)

## remove certain objects from the default sequence
removeAllPATObjectsBut(process, ['Muons'])
#removeSpecificPATObjects(process, ['Electrons','Jets', 'Taus'])

## The iso-based HBHE noise filter ___________________________________________||
process.load('CommonTools.RecoAlgos.HBHENoiseFilter_cfi')

## The CSC beam halo tight filter ____________________________________________||
process.load('RecoMET.METAnalyzers.CSCHaloFilter_cfi')

## The HCAL laser filter _____________________________________________________||
process.load('RecoMET.METFilters.hcalLaserEventFilter_cfi')

## The ECAL dead cell trigger primitive filter _______________________________||
process.load('RecoMET.METFilters.EcalDeadCellTriggerPrimitiveFilter_cfi') 

## The EE bad SuperCrystal filter ____________________________________________||
process.load('RecoMET.METFilters.eeBadScFilter_cfi') 

## The ECAL laser correction filter
process.load('RecoMET.METFilters.ecalLaserCorrFilter_cfi')

## The tracking failure filter _______________________________________________||
process.load('RecoMET.METFilters.trackingFailureFilter_cfi')

## The tracking POG filters __________________________________________________||
process.load('RecoMET.METFilters.trackingPOGFilters_cff')


## The beam scraping filter __________________________________________________||
process.noscraping = cms.EDFilter(
    "FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
    )

## The iso-based HBHE noise filter ___________________________________________||
process.load('CommonTools.RecoAlgos.HBHENoiseFilter_cfi')




## let it run
process.p = cms.Path(
    process.patDefaultSequence #+
    )

# Veto leptons
process.load("PhysicsTools.PatAlgos.userDataLeptonProducers_cfi")

process.vetoMuons = process.userDataMuons.clone(
    cut = cms.string(" (isGlobalMuon || isTrackerMuon) " +
                     "& pt >= 10 & abs(eta) <= 2.4 ")# +
                    # "& userFloat(\"DeltaCorrectedIso\") <0.2 ")
)

# Tight leptons
process.tightMuons = process.userDataMuons.clone(
    cut = cms.string("pt >= 20 &(isGlobalMuon && isTrackerMuon)& isPFMuon & abs(eta) <= 2.4 & (normChi2 < 10&& normChi2>0)"+
                     "& track.hitPattern.trackerLayersWithMeasurement>5 "+
                     "& numberOfMatchedStations() > 1 & innerTrack.hitPattern.numberOfValidPixelHits > 0 " +
                     "& globalTrack.hitPattern.numberOfValidMuonHits > 0" +
                    # "& userFloat('VertexDxy')<0.02" +
                     "& abs(dB) < 0.02" )#+
                    # "& userFloat('VertexDz')<0.5" +
                    # "& userFloat(\"DeltaCorrectedIso\") <=0.20 " +
                    # "& userFloat(\"RhoCorrectedIso\") <= 0.20 " ) 
)


'''
process.load("PhysicsTools.PatAlgos.LooseMuon_cfi")
process.vetoMuons = process.LooseMuons.clone(
)


process.load("PhysicsTools.PatAlgos.TightMuon_cfi")
process.tightMuons = process.TightMuons.clone(

)
'''
process.basePath = cms.Sequence(
       process.vetoMuons +
       process.tightMuons
    )

process.load("PhysicsTools.PatAlgos.TwoLooseMuon_cfi")
process.step0 = process.TwoLooseMuon.clone(
#    muons = cms.InputTag("vetoMuons")
    muons = cms.InputTag("selectedPatMuons")
)


process.load("PhysicsTools.PatAlgos.DiMuon_cfi")
process.step1 = process.MuonPair.clone(
    muons = cms.InputTag("tightMuons")
#    muons = cms.InputTag("selectedPatMuons")

)

process.load("PhysicsTools.PatAlgos.ThreeMuons_cfi")
process.step2 = process.threeMuons.clone(
    muons = cms.InputTag("tightMuons")
#    muons = cms.InputTag("selectedPatMuons")                                                                                            
)


process.load("PhysicsTools.PatAlgos.NoLooseMuons_cfi")
process.step2a = process.noloosemuons.clone(
    muons = cms.InputTag("vetoMuons")
)


## ------------------------------------------------------

# process.GlobalTag.globaltag =  ...   
process.out.fileName = 'patTuple_standard.root'

process.load("PhysicsTools.PatAlgos.SingleTopEventFilters_cff")
process.filtersSeq = cms.Sequence(
  # process.primaryVertexFilter * #for MC, only filter for Duncan
   #process.noscraping *
   process.HBHENoiseFilter* 
  # process.CSCTightHaloFilter *
   process.hcalLaserEventFilter *
   process.EcalDeadCellTriggerPrimitiveFilter *
  # process.trackingFailureFilter *
   process.eeBadScFilter *
   process.ecalLaserCorrFilter *
   process.trkPOGFilters *
   process.basePath
)

process.p1 = cms.Path()
process.p1 += process.filtersSeq
process.p1 += process.step0
process.p1 += process.step1
process.p1 += process.step2
process.p1 += process.step2a
