#include "DataFormats/PatCandidates/interface/Muon.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "PhysicsTools/PatAlgos/interface/threemuons.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/MuonReco/interface/MuonPFIsolation.h"
/// default constructor 
threemuons::threemuons(const edm::ParameterSet& cfg):
  muons_    (cfg.getParameter<edm::InputTag>(       "muons"  ))
{
}

/// default destructor
threemuons::~threemuons()
{
}

/// sanity check
void 
threemuons::beginJob()
{ 
}


bool
threemuons::filter(edm::Event& event, const edm::EventSetup& setup)
{   
  // fetch the input collection from the event content  
  edm::Handle<std::vector<pat::Muon> > muons;
  event.getByLabel(muons_, muons);

  //    if(muons->size() <=1) return false;

  
    if(muons->size()<=2 || muons->size() >3) return false;
    if(muons->size() !=3) return false;
    int r = event.id().event();
 
  std::cout << "---------------Event ID = "<<r<<"---------------"<<std::endl;
    
  std::cout << "Muons size = " <<  muons->size()<<std::endl;

  edm::Handle<edm::View<reco::Vertex> > vertices;
  event.getByLabel("offlinePrimaryVertices",vertices);

    for (unsigned  ii=0; ii < muons->size(); ++ii){
       double RelIso = -999;
       double dz_pvz = -999;
       	for(size_t v = 0; v < vertices->size(); ++v){
      		if((*muons)[ii].vertex().z()-vertices->at(0).z() <= 0.5) 
      		dz_pvz = fabs((*muons)[ii].vertex().z()-vertices->at(0).z()); 
	      		}
 	//std::cout<<"dz_pvz = "<<dz_pvz<<std::endl;
		if (dz_pvz >= 0.5) return false;
	
		//double RelIso = (((*muons)[ii].chargedHadronIso() + std::max(0., (*muons)[ii].neutralHadronIso() + (*muons)[ii].photonIso() - 
		//					     0.5*(*muons)[ii].puChargedHadronIso())))/((*muons)[ii].pt());

double RelIso = ((*muons)[ii].pfIsolationR04().sumChargedHadronPt + std::max(0., (*muons)[ii].pfIsolationR04().sumNeutralHadronEt + 
	     (*muons)[ii].pfIsolationR04().sumPhotonEt - 0.5*(*muons)[ii].pfIsolationR04().sumPUPt))/((*muons)[ii].pt());


 if (RelIso > 0.2) return false;

	std::cout << "| Event ID = " << r << 
			"| Found Muon No  "<< ii+1 << 
			"| pt = "<< (*muons)[ii].pt()<<
			"| abs(eta) = "<< fabs((*muons)[ii].eta())<<
	  		"| Chi2 = " << (*muons)[ii].normChi2()<< 
	        	"| TrackLayer = " << (*muons)[ii].track()->hitPattern().trackerLayersWithMeasurement() <<
	  		"| MuonHits = " << (*muons)[ii].globalTrack()->hitPattern().numberOfValidMuonHits()<<
     	                "| dB = " << (*muons)[ii].dB()<<
	         	"| dz-pvz = " << dz_pvz <<
	  		"| validPixelHits = " << (*muons)[ii].innerTrack()->hitPattern().numberOfValidPixelHits()<<
	  		"| stations = " << (*muons)[ii].numberOfMatchedStations()<<
	                "| sumChargedHadronPt = " << (*muons)[ii].pfIsolationR04().sumChargedHadronPt <<
	                "| NeutalHadronIso = " << (*muons)[ii].neutralHadronIso() <<
	                "| PhotonIso = " << (*muons)[ii].photonIso() <<
	                "| PuChargedHadronIso = " << (*muons)[ii].pfIsolationR04().sumPhotonEt <<
	                "| RelIso(dBeta) = " <<  RelIso <<
	                "| " <<std::endl;
}
    
    
    std::cout << "---------------End of Event --------------------------"<<std::endl;
    std::cout << "  " << std::endl;


 return true;

}

DEFINE_FWK_MODULE( threemuons );
