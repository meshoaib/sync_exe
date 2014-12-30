import FWCore.ParameterSet.Config as cms

threeMuons = cms.EDFilter("threemuons",
    muons = cms.InputTag("tightMuons")
)


