import FWCore.ParameterSet.Config as cms

noloosemuons = cms.EDFilter("vetomuons",
    muons = cms.InputTag("vetoMuons")
)


