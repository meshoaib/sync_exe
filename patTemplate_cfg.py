import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

## Options and Output Report
#process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    FailPath = cms.untracked.vstring('ProductNotFound','Type Mismatch')
    )
process.MessageLogger.cerr.FwkReport.reportEvery = 500
## Source
process.source = cms.Source("PoolSource",
  #  fileNames = cms.untracked.vstring("file:/afs/cern.ch/work/m/mwaqas/public/00037C53-AAD1-E111-B1BE-003048D45F38.root")
    fileNames = cms.untracked.vstring("file:/afs/cern.ch/work/j/jandrea/public/147DB408-446A-E311-8E63-00259073E32A.root")

)
## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000))
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))

## Geometry and Detector Conditions (needed for a few patTuple production steps)
#process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )
process.load("Configuration.StandardSequences.MagneticField_cff")

## Test JEC from test instances of the global DB
#process.load("PhysicsTools.PatAlgos.patTestJEC_cfi")

## Test JEC from local sqlite file
#process.load("PhysicsTools.PatAlgos.patTestJEC_local_cfi")
#process.patJets.addTagInfos = False
## Standard PAT Configuration File
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## Output Module Configuration (expects a path 'p')
#from PhysicsTools.PatAlgos.patEventContent_cff import patEventContent

from PhysicsTools.PatAlgos.patEventContent_cff import patEventContentNoCleaning
'''
#Objects included in the pat-tuples
savePatTupleSkimLoose = cms.untracked.vstring(
    'drop *',
    'keep *_*Muons_*_*',
    'keep patMuons_selectedPatMuons_*_*',
    'keep patMuons_vetoMuons_*_*',
    'keep patMuons_tightMuons_*_*',
)


process.singleTopPatTuple = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('singleTopSk.root'),
#    SelectEvents   = cms.untracked.PSet(
#      SelectEvents = cms.vstring(
#        'preselection')
#      ),
    outputCommands = savePatTupleSkimLoose
    )

'''

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('patTuple.root'),
                               # save only events passing the full path
                               #SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('process.basePath') ),
                               #SkipEvent   = cms.untracked.PSet( SkipEvent = cms.vstring('ProductNotFound') ),
                               #SkipEvent = cms.untracked.vstring('ProductNotFound'),
                               # save PAT Layer 1 output; you need a '*' to
                               # unpack the list of commands 'patEventContent'
                               outputCommands = cms.untracked.vstring('drop *', *patEventContentNoCleaning )
                 
             )

process.outpath = cms.EndPath(process.out)


#process.outpath = cms.EndPath(process.singleTopPatTuple)

