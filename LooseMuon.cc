#include "DataFormats/PatCandidates/interface/Muon.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "PhysicsTools/PatAlgos/interface/LooseMuon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

/// default constructor 
LooseMuon::LooseMuon(const edm::ParameterSet& cfg):
  muons_    (cfg.getParameter<edm::InputTag>(       "muons"  ))

{
}

/// default destructor
LooseMuon::~LooseMuon()
{
}

/// sanity check
void 
LooseMuon::beginJob()
{ 

}


bool
LooseMuon::filter(edm::Event& event, const edm::EventSetup& setup){
   
  // fetch the input collection from the event content  
  edm::Handle<std::vector<pat::Muon> > muons;
  event.getByLabel(muons_, muons);

    if(muons->size() <=1) return false;
  
    int r = event.id().event();
    std::cout << "---------------Event ID = "<<r<<"---------------"<<std::endl;
    std::cout << "Muons size = " <<  muons->size()<<std::endl;
    /*    
    for (unsigned  ii=0; ii < muons->size(); ++ii){
	std::cout << "| Event ID = " << r << 
			"| Found Muon No  "<< ii+1 << 
			"| pt = "<< (*muons)[ii].pt()<<
			"| abs(eta) = "<< fabs((*muons)[ii].eta())<<
			"| Charge = "<<(*muons)[ii].charge()<<
			"| " <<std::endl;
			}*/
      //std::cout << "  " << std::endl; 
return true;

}

DEFINE_FWK_MODULE( LooseMuon );
