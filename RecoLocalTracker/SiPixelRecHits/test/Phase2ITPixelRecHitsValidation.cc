#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/CommonDetUnit/interface/GeomDetEnumerators.h"


#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"
#include "DataFormats/SiPixelDetId/interface/PixelSubdetector.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Phase2TrackerCluster/interface/Phase2TrackerCluster1D.h"
#include "DataFormats/TrackerRecHit2D/interface/Phase2TrackerRecHit1D.h"
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHitCollection.h"

#include "SimDataFormats/TrackerDigiSimLink/interface/PixelDigiSimLink.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"

#include "DataFormats/GeometrySurface/interface/LocalError.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

#include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h"                                                                                                                          
#include <TH1D.h>
#include <TH2D.h>

typedef TH1F* TH1Fptr;
typedef TH2F* TH2Fptr;

class Phase2ITPixelRecHitsValidation : public edm::one::EDAnalyzer<> {

public:
  
  explicit Phase2ITPixelRecHitsValidation(const edm::ParameterSet&);
  ~Phase2ITPixelRecHitsValidation();
  void beginJob() override;
  void endJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  
private:
    
  edm::EDGetTokenT< SiPixelRecHitCollectionNew > tokenRecHits_;        
  TrackerHitAssociator::Config trackerHitAssociatorConfig_;

  // histograms
  edm::Service<TFileService> fs_;

  //  TH1D* numberRecHitsPixel;
  //  TH1D* numberRecHitsStrip;
  
  TH2F* trackerLayoutRz_;
  TH2F* trackerLayoutXY_;
  TH2F* trackerLayoutXYBPIX_;
  TH2F* trackerLayoutXYFPIX_[2];
  
  TFileDirectory BPIXdir_;
  TFileDirectory FPIXnegdir_;
  TFileDirectory FPIXposdir_;
  
  const int MAX_BPIX=4;
  const int MAX_FPIX=10;

  // hit maps
  TH2Fptr * h2_yxLocalHitMap_BPIX_;
  TH2Fptr * h2_yxLocalHitMap_FPIXneg_;
  TH2Fptr * h2_yxLocalHitMap_FPIXpos_;

  // SimHit-RecHit residuals
  TH1Fptr * h1_xResiduals_BPIX_;
  TH1Fptr * h1_yResiduals_BPIX_;
  TH2Fptr * h2_xSimVsRec_BPIX_;
  TH2Fptr * h2_ySimVsRec_BPIX_;
  TH1Fptr * h1_xResiduals_FPIXneg_;
  TH1Fptr * h1_yResiduals_FPIXneg_;
  TH1Fptr * h1_xResiduals_FPIXpos_;
  TH1Fptr * h1_yResiduals_FPIXpos_;

};

Phase2ITPixelRecHitsValidation::Phase2ITPixelRecHitsValidation(const edm::ParameterSet& conf) :
  tokenRecHits_(consumes< SiPixelRecHitCollectionNew >(conf.getParameter<edm::InputTag>("phase2ITPixelRecHitSrc"))), 
  trackerHitAssociatorConfig_(conf, consumesCollector())
{
  
  std::cout << "Phase2ITPixelRecHits Validation" << std::endl;

}

Phase2ITPixelRecHitsValidation::~Phase2ITPixelRecHitsValidation() { 

  if ( h2_yxLocalHitMap_BPIX_ )    delete[] h2_yxLocalHitMap_BPIX_ ;  
  if ( h2_yxLocalHitMap_FPIXneg_ ) delete[] h2_yxLocalHitMap_FPIXneg_;  
  if ( h2_yxLocalHitMap_FPIXpos_ ) delete[] h2_yxLocalHitMap_FPIXpos_;  
						     						      
  if ( h1_xResiduals_BPIX_ )    delete[] h1_xResiduals_BPIX_ ;     
  if ( h1_xResiduals_FPIXneg_ ) delete[] h1_xResiduals_FPIXneg_ ;     
  if ( h1_xResiduals_FPIXpos_ ) delete[] h1_xResiduals_FPIXpos_ ;     

  if ( h1_yResiduals_BPIX_ )    delete[] h1_yResiduals_BPIX_ ;     
  if ( h1_yResiduals_FPIXneg_ ) delete[] h1_yResiduals_FPIXneg_ ;     
  if ( h1_yResiduals_FPIXpos_ ) delete[] h1_yResiduals_FPIXpos_ ;     

}

void Phase2ITPixelRecHitsValidation::beginJob() {
  edm::Service<TFileService> fs_; 
  
  TFileDirectory td_ = fs_->mkdir("Common");
  // Create common histograms
  trackerLayoutRz_      = td_.make< TH2F >("RVsZ", "R vs. z position; z [cm]; R [cm]",    6000,-300.0, 300.0, 300, 0.0, 30.0);
  trackerLayoutXY_      = td_.make< TH2F >("XVsY", "x vs. y position; x [cm]; y [cm]",     600, -30.0,  30.0, 600, -30.0, 30.0);

  // hit maps 
  h2_yxLocalHitMap_BPIX_    = new TH2Fptr[MAX_BPIX];
  h2_yxLocalHitMap_FPIXneg_ = new TH2Fptr[MAX_FPIX];
  h2_yxLocalHitMap_FPIXpos_ = new TH2Fptr[MAX_FPIX];

  // residuals
  h1_xResiduals_BPIX_    = new TH1Fptr[MAX_BPIX];
  h1_xResiduals_FPIXneg_ = new TH1Fptr[MAX_FPIX];
  h1_xResiduals_FPIXpos_ = new TH1Fptr[MAX_FPIX];

  h2_xSimVsRec_BPIX_ = new TH2Fptr[MAX_BPIX]; 
  h2_ySimVsRec_BPIX_ = new TH2Fptr[MAX_BPIX];

  h1_yResiduals_BPIX_    = new TH1Fptr[MAX_BPIX];
  h1_yResiduals_FPIXneg_ = new TH1Fptr[MAX_FPIX];
  h1_yResiduals_FPIXpos_ = new TH1Fptr[MAX_FPIX];

  char buff_name[60];
  char buff_title[60];
  
  // BPIX
  BPIXdir_ = fs_->mkdir( "BPIX" );
  trackerLayoutXYBPIX_ = BPIXdir_.make< TH2F >("XVsYBPIX", "x vs. y position; x [cm]; y [cm] ",600, -30.0,  30.0, 600, -30.0, 30.0);
  for ( int i=0; i<MAX_BPIX; i++ ) {
    sprintf(buff_name, "h2_yxLocalHitMap_BPIX_%u",i+1);
    sprintf(buff_title,"h2_yxLocalHitMap_BPIX_%u; y[cm] ; x[cm]",i+1);    
    h2_yxLocalHitMap_BPIX_[i] = BPIXdir_.make<TH2F>( buff_name,buff_title,600,-3.,+3.,100,-1.,+1.);

  }  
  for ( int i=0; i<MAX_BPIX; i++ ) {
    sprintf(buff_name, "h1_xResiduals_BPIX_%u",i+1);
    sprintf(buff_title,"h1_xResiduals_BPIX_%u; [cm]",i+1);    
    h1_xResiduals_BPIX_[i] = BPIXdir_.make<TH1F>( buff_name,buff_title,250,-0.25,+0.25);
  }  
  for ( int i=0; i<MAX_BPIX; i++ ) {
    sprintf(buff_name, "h1_yResiduals_BPIX_%u",i+1);
    sprintf(buff_title,"h1_yResiduals_BPIX_%u; [cm];",i+1);    
    h1_yResiduals_BPIX_[i] = BPIXdir_.make<TH1F>( buff_name,buff_title,250,-0.25,+0.25);
  }  
  for ( int i=0; i<MAX_BPIX; i++ ) {
    sprintf(buff_name, "h2_xSimVsRec_BPIX_%u",i+1);
    sprintf(buff_title,"h2_xSimVsRec_BPIX_%u; rec [cm]; sim [cm]",i+1);    
    h2_xSimVsRec_BPIX_[i] = BPIXdir_.make<TH2F>( buff_name,buff_title,100,-1.5,+1.5,100,-1.5,+1.5);
  }  
  for ( int i=0; i<MAX_BPIX; i++ ) {
    sprintf(buff_name, "h2_ySimVsRec_BPIX_%u",i+1);
    sprintf(buff_title,"h2_ySimVsRec_BPIX_%u; rec [cm]; sim [cm]",i+1);    
    h2_ySimVsRec_BPIX_[i] = BPIXdir_.make<TH2F>( buff_name,buff_title,100,-3.5,+3.5,100,-3.5,+3.5);
  }  


  // FPIX neg
  FPIXnegdir_ = fs_->mkdir( "FPIXneg" );
  trackerLayoutXYFPIX_[0]  = FPIXnegdir_.make< TH2F >("XVsYFPIXneg", "x vs. y position; x [cm]; y [cm]", 600, -30.0, 30.0, 600, -30.0, 30.0);
  for ( int i=0; i<MAX_FPIX; i++ ) {
    sprintf(buff_name, "h2_yxLocalHitMap_FPIXneg_%u",i+1);
    sprintf(buff_title,"h2_yxLocalHitMap_FPIXneg_%u; y [cm]; x [cm]",i+1);    
    h2_yxLocalHitMap_FPIXneg_[i] = FPIXnegdir_.make<TH2F>( buff_name,buff_title,600,-3.,+3.,100,-1.,+1.);
  }
  for ( int i=0; i<MAX_FPIX; i++ ) {
    sprintf(buff_name, "h1_xResiduals_FPIXneg_%u",i+1);
    sprintf(buff_title,"h1_xResiduals_FPIXneg_%u; [cm]",i+1);    
    h1_xResiduals_FPIXneg_[i] = FPIXnegdir_.make<TH1F>( buff_name,buff_title,250,-0.25,+0.25);
  }  
  for ( int i=0; i<MAX_FPIX; i++ ) {
    sprintf(buff_name, "h1_yResiduals_FPIXneg_%u",i+1);
    sprintf(buff_title,"h1_yResiduals_FPIXneg_%u; [cm]",i+1);    
    h1_yResiduals_FPIXneg_[i] = FPIXnegdir_.make<TH1F>( buff_name,buff_title,250,-0.25,+0.25);
  }  

  // FPIX pos
  FPIXposdir_ = fs_->mkdir( "FPIXpos" );
  trackerLayoutXYFPIX_[1] = FPIXposdir_.make< TH2F >("XVsYFPIXpos", "x vs. y position; x [cm]; y [cm]", 600, -30.0, 30.0, 600, -30.0, 30.0);
  for ( int i=0; i<MAX_FPIX; i++ ) {
    sprintf(buff_name, "h2_yxLocalHitMap_FPIXpos_%u",i+1);
    sprintf(buff_title,"h2_yxLocalHitMap_FPIXpos_%u; y [cm]; x [cm]",i+1);    
    h2_yxLocalHitMap_FPIXpos_[i] = FPIXposdir_.make<TH2F>( buff_name,buff_title,600,-3.,+3.,100,-1.,+1.);
  }
  for ( int i=0; i<MAX_FPIX; i++ ) {
    sprintf(buff_name, "h1_xResiduals_FPIXpos_%u",i+1);
    sprintf(buff_title,"h1_xResiduals_FPIXpos_%u; [cm]",i+1);    
    h1_xResiduals_FPIXpos_[i] = FPIXposdir_.make<TH1F>( buff_name,buff_title,250,-0.25,+0.25);
  }  
  for ( int i=0; i<MAX_FPIX; i++ ) {
    sprintf(buff_name, "h1_yResiduals_FPIXpos_%u",i+1);
    sprintf(buff_title,"h1_yResiduals_FPIXpos_%u; [cm]",i+1);    
    h1_yResiduals_FPIXpos_[i] = FPIXposdir_.make<TH1F>( buff_name,buff_title,250,-0.25,+0.25);
  }  

  
}


void Phase2ITPixelRecHitsValidation::endJob() { }

void Phase2ITPixelRecHitsValidation::analyze(const edm::Event& event, const edm::EventSetup& eventSetup) {

    std::cout << "PROCESSING RECHIT EVENT" << std::endl;

    /*
     * Get the needed objects
     */

    // Get the RecHits
    edm::Handle< SiPixelRecHitCollectionNew > rechits;
    event.getByToken(tokenRecHits_, rechits);

    // Get the geometry
    edm::ESHandle< TrackerGeometry > tGeomHandle;
    eventSetup.get< TrackerDigiGeometryRecord >().get(tGeomHandle);
    const TrackerGeometry* trackerGeometry = &(*tGeomHandle);

    edm::ESHandle< TrackerTopology > tTopoHandle;
    eventSetup.get< TrackerTopologyRcd >().get(tTopoHandle);
    const TrackerTopology* trackerTopology = tTopoHandle.product();

    /*
     * Validation: hit maps
     */

    // Loop over modules
    for (SiPixelRecHitCollectionNew::const_iterator DSViter = rechits->begin(); DSViter != rechits->end(); ++DSViter) {
      
      // Get the detector unit's id
      unsigned int rawid(DSViter->detId()); 
      DetId detId(rawid);
      
      //      std::cout << "detId/trackerGeometry->idToDetUnit(detId) " << rawid << " " << trackerGeometry->idToDetUnit(detId) << std::endl;

      // Get the geometry of the tracker
      const GeomDetUnit* geomDetUnit(trackerGeometry->idToDetUnit(detId));
      //      const PixelGeomDetUnit* theGeomDet = dynamic_cast< const PixelGeomDetUnit* >(geomDetUnit);
      //      const PixelTopology& topol = theGeomDet->specificTopology();
      
      if (!geomDetUnit) break;
      
      // Number of clusters
      //      unsigned int nRecHitsPixel(0), nRecHitsStrip(0);
      
      // Loop over the clusters in the detector unit
      for (edmNew::DetSet< SiPixelRecHit >::const_iterator rechitIt = DSViter->begin(); rechitIt != DSViter->end(); ++rechitIt) {
	
	/*
	 * Cluster related variables
	 */
	  
	LocalPoint localPosClu = rechitIt->localPosition();
	Global3DPoint globalPosClu = geomDetUnit->surface().toGlobal(localPosClu);
	
	// Fill the position histograms
	trackerLayoutRz_->Fill(globalPosClu.z(), globalPosClu.perp());
	trackerLayoutXY_->Fill(globalPosClu.x(), globalPosClu.y());

	//###

	if ( detId.subdetId() == PixelSubdetector::PixelBarrel) {
	  // BPIX
	  trackerLayoutXYBPIX_->Fill(globalPosClu.x(), globalPosClu.y());
	  int layer = trackerTopology->pxbLayer(detId);
	  h2_yxLocalHitMap_BPIX_[layer-1]->Fill(localPosClu.y(),localPosClu.x());
	} else if (detId.subdetId() == PixelSubdetector::PixelEndcap) {
	  int layer = trackerTopology->pxfDisk(detId);
	  if ( trackerTopology->pxfSide(detId) == 1 ) { 
	    // FPIX z<0
	    trackerLayoutXYFPIX_[0]->Fill(globalPosClu.x(), globalPosClu.y());
	    h2_yxLocalHitMap_FPIXneg_[layer-1]->Fill(localPosClu.y(),localPosClu.x());
	  } else if ( trackerTopology->pxfSide(detId) == 2 ) { 
	    // FPIX z>0
	    trackerLayoutXYFPIX_[1]->Fill(globalPosClu.x(), globalPosClu.y());
	    h2_yxLocalHitMap_FPIXpos_[layer-1]->Fill(localPosClu.y(),localPosClu.x());
	  }
	}
      } // end of loop on RecHits
    } // end of loop od DetSet

    /*
     * Validation: residuals
     */
    
    std::vector<PSimHit> matched;
    int pixelcounter = 0;

    // loop over detunits
    for(TrackerGeometry::DetContainer::const_iterator it = tGeomHandle->dets().begin(); it != tGeomHandle->dets().end(); it++){
      uint32_t myid=((*it)->geographicalId()).rawId();       
      DetId detId = ((*it)->geographicalId());
      
      //construct the associator object
      TrackerHitAssociator  associate(event,trackerHitAssociatorConfig_);
     
	
      SiPixelRecHitCollectionNew::DetSet::const_iterator pixelrechitRangeIteratorBegin(0);
      SiPixelRecHitCollectionNew::DetSet::const_iterator pixelrechitRangeIteratorEnd = pixelrechitRangeIteratorBegin;
      SiPixelRecHitCollectionNew::const_iterator pixelrechitMatch = rechits->find(detId);
      if ( pixelrechitMatch != rechits->end()) {
	SiPixelRecHitCollectionNew::DetSet pixelrechitRange = *pixelrechitMatch;
	pixelrechitRangeIteratorBegin = pixelrechitRange.begin();
	pixelrechitRangeIteratorEnd   = pixelrechitRange.end();
      }
      SiPixelRecHitCollectionNew::DetSet::const_iterator pixeliter = pixelrechitRangeIteratorBegin;
      
      // Do the pixels
      for ( ; pixeliter != pixelrechitRangeIteratorEnd; ++pixeliter) {
	pixelcounter++;
	//	std::cout << pixelcounter <<") Phase2ITPixel RecHit DetId " << detId.rawId() << " Pos = " << pixeliter->localPosition() << std::endl;
	
	matched.clear();
	matched = associate.associateHit(*pixeliter);
	if(!matched.empty()){
	  //	  std::cout << " PIX detector =  " << myid << " PIX Rechit = " << pixeliter->localPosition() << std::endl; 
	  //	  std::cout << " PIX matched = " << matched.size() << std::endl;
	  for(std::vector<PSimHit>::const_iterator m=matched.begin(); m<matched.end(); m++){
	    //  std::cout << " PIX hit  ID = " << (*m).trackId() << " PIX Simhit x = " << (*m).localPosition() << std::endl;

	    if ( detId.subdetId() == PixelSubdetector::PixelBarrel) {
	      // BPIX
	      int layer = trackerTopology->pxbLayer(detId);
	      h1_xResiduals_BPIX_[layer-1]->Fill((*m).localPosition().x()-pixeliter->localPosition().x());
	      h1_yResiduals_BPIX_[layer-1]->Fill((*m).localPosition().y()-pixeliter->localPosition().y());

	      h2_xSimVsRec_BPIX_[layer-1]->Fill(pixeliter->localPosition().x(),(*m).localPosition().x());
	      h2_ySimVsRec_BPIX_[layer-1]->Fill(pixeliter->localPosition().y(),(*m).localPosition().y());

	    } else if (detId.subdetId() == PixelSubdetector::PixelEndcap) {
	      int layer = trackerTopology->pxfDisk(detId);
	      if ( trackerTopology->pxfSide(detId) == 1 ) { 
		// FPIX z<0
		h1_xResiduals_FPIXneg_[layer-1]->Fill((*m).localPosition().x()-pixeliter->localPosition().x());
		h1_yResiduals_FPIXneg_[layer-1]->Fill((*m).localPosition().y()-pixeliter->localPosition().y());
	      } else if ( trackerTopology->pxfSide(detId) == 2 ) { 
		// FPIX z>0
		h1_xResiduals_FPIXpos_[layer-1]->Fill((*m).localPosition().x()-pixeliter->localPosition().x());
		h1_yResiduals_FPIXpos_[layer-1]->Fill((*m).localPosition().y()-pixeliter->localPosition().y());
	      }
	    }


	  }
	}  
      }
    }
    

}


DEFINE_FWK_MODULE(Phase2ITPixelRecHitsValidation);
