import FWCore.ParameterSet.Config as cms

MuonPair = cms.EDFilter("Zpair",
    muons = cms.InputTag("tightMuons")
)


