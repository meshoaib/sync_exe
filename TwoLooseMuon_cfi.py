import FWCore.ParameterSet.Config as cms

TwoLooseMuon = cms.EDFilter("LooseMuon",

    ## sources
    muons = cms.InputTag("selectedPatMuons")

                              
)


