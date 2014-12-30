#include "DataFormats/PatCandidates/interface/Muon.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "PhysicsTools/PatAlgos/interface/Zpair.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

/// default constructor 
Zpair::Zpair(const edm::ParameterSet& cfg):
muons_(cfg.getParameter<edm::InputTag>("muons"))
{
}
/// default destructor
Zpair::~Zpair()
{
}
/// sanity check
void 
Zpair::beginJob()
{ 
}

bool
Zpair::filter(edm::Event& event, const edm::EventSetup& setup)
{   
  // fetch the input collection from the event content  
  edm::Handle<std::vector<pat::Muon> > muons;
  event.getByLabel(muons_, muons);
  //  int r = event.id().event();
  // std::cout << "---------------Event ID = "<<r<<"---------------"<<std::endl;
  //std::cout << "Muons size = " <<  muons->size()<<std::endl;

  if( muons->size() <=1 ) return false;
  //  std::cout << "Muons size = " <<  muons->size()<<std::endl;
    /* 
    for (unsigned  ii=0; ii < muons->size(); ++ii){
           std::cout << "| Event ID = " << r << 
			"| Found Muon No  "<< ii+1 << 
			"| pt = "<< (*muons)[ii].pt()<<
			"| abs(eta) = "<< fabs((*muons)[ii].eta())<<
	  		"| Chi2 = " << (*muons)[ii].normChi2()<< 
	       	"| TrackLayer = " << (*muons)[ii].track()->hitPattern().trackerLayersWithMeasurement() <<
	  		"| MuonHits = " << (*muons)[ii].globalTrack()->hitPattern().numberOfValidMuonHits()<<
	  //    	"| Dxy = " <<  (*muons)[ii].userFloat("VertexDxy")<<
	  //    	"| dz-pvz = " << dz_pvz <<
	  		"| validPixelHits = " << (*muons)[ii].innerTrack()->hitPattern().numberOfValidPixelHits()<<
	                 "| stations = " << (*muons)[ii].numberOfMatchedStations()<<
	              "| dB = " << (*muons)[ii].dB()<<
			"| Charge = "<<(*muons)[ii].charge()<<
	              "| DCIsolation = " << (*muons)[ii].userFloat("DeltaCorrectedIso") <<
			"| " <<std::endl;
			} */
  //std::cout << " =============== inside Z Mass Loop =========  " << std::endl; 
double zmass = 91.1876;
double min=1000.;
 int j=0;
 int jj=0;
 int m_i =100;
 int m_ii=100;
 double hard_pt =0.;

 for(std::vector<pat::Muon>::const_iterator muItr = muons->begin(); muItr != muons->end(); muItr++)
   {
     jj=0;
     for(std::vector<pat::Muon>::const_iterator muItr2 = muons->begin(); muItr2 != muons->end(); muItr2++)
       {
	 //	 std::cout<<"charge1 "<<(*muItr).charge()<<"  charge2 "<<(*muItr2).charge() <<std::endl;
	 if(muItr2 > muItr && ( (*muItr).charge()*(*muItr2).charge() ) > 0 ) continue;
	   {
	     double dphi = (*muItr).phi() - (*muItr2).phi();
	     if( fabs(dphi)< 0.5) continue; // 0.1 previous
	     double mass  =  ( (*muItr).p4() + (*muItr2).p4() ).mass();
	     //	     std::cout<<"charge1 "<<(*muItr).charge()<<"  charge2 "<<(*muItr2).charge()<< " Z mass "<< mass << " dphi "<< dphi<<std::endl;
	     if( (*muItr).pt() > (*muItr2).pt() )
	       hard_pt =  (*muItr).pt();
	     else  {
	       hard_pt =  (*muItr2).pt();
	     }
	     double m =  zmass - mass;
	     if(fabs(m) <min  && hard_pt > 20.) {
	       min = fabs(m); m_i = j; m_ii = jj;
	     }
	   }//end of SFOS anti-matching
	 jj++;
       }//end of second loop
     j++;
   }//END OF MV LOOP

 if (min ==1000 || m_i ==100 || m_ii ==100 ) return false;
 // std::cout<<"closest Z mass "<<min<<"  with muon indices : ( "<<m_i<<",   "<<m_ii<<" )"<< " cont size  "<<  muons->size()<<std::endl;
 // std::cout << "----------------------------End of Event ID --------------------------"<<std::endl;
 return true;

}

DEFINE_FWK_MODULE(Zpair);
