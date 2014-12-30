#include "DataFormats/PatCandidates/interface/Muon.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "PhysicsTools/PatAlgos/interface/vetomuons.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/MuonReco/interface/MuonPFIsolation.h"
/// default constructor 
vetomuons::vetomuons(const edm::ParameterSet& cfg):
  muons_    (cfg.getParameter<edm::InputTag>(       "muons"  ))
{
}

/// default destructor
vetomuons::~vetomuons()
{
}

/// sanity check
void 
vetomuons::beginJob()
{ 
}


bool
vetomuons::filter(edm::Event& event, const edm::EventSetup& setup)
{   
  // fetch the input collection from the event content  
  edm::Handle<std::vector<pat::Muon> > muons;
  event.getByLabel(muons_, muons);

      if(muons->size() > 3) return false;
 
 return true;

}

DEFINE_FWK_MODULE( vetomuons );
