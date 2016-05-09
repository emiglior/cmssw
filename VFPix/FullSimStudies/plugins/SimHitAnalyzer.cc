#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>


#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/CommonDetUnit/interface/GeomDetEnumerators.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"

#include "VFPix/FullSimStudies/plugins/SimHitAnalyzer.h"

SimHitAnalyzer::SimHitAnalyzer (const edm::ParameterSet &cfg) :
  simHitsBarrelHighTof_src_ (cfg.getParameter<edm::InputTag> ("simHitsBarrelHighTof")),
  simHitsBarrelLowTof_src_ (cfg.getParameter<edm::InputTag>  ("simHitsBarrelLowTof")),
  simHitsEndcapHighTof_src_ (cfg.getParameter<edm::InputTag> ("simHitsEndcapHighTof")),
  simHitsEndcapLowTof_src_ (cfg.getParameter<edm::InputTag>  ("simHitsEndcapLowTof"))
{
  //  TH1::SetDefaultSumw2 ();

  oneDHists_["rho"] = fs_->make<TH1D> ("rho", ";#rho [cm]", 500, 0.0, 50.0);
  twoDHists_["rhoPhi"] = fs_->make<TH2D> ("rhoPhi", ";x [cm];y [cm]", 600, 0.0,  60.0, 600, 0.0, 60.0);
  twoDHists_["rhoZ"] = fs_->make<TH2D> ("rhoZ", ";z [cm]; #rho [cm]" , 500, 0.0, 300.0, 600, 0.0, 60.0);

  h2_yxHitMap_BPIX_ = new TH2Fptr[MAX_BPIX];
  h2_yxHitMap_FPIXneg_ = new TH2Fptr[MAX_FPIX];
  h2_yxHitMap_FPIXpos_ = new TH2Fptr[MAX_FPIX];

  char buff_name[50];
  char buff_title[50];

  // BPIX
  BPIXdir_ = fs_->mkdir( "BPIX" );
  for ( int i=0; i<MAX_BPIX; i++ ) {
    sprintf(buff_name, "h2_yxHitMap_BPIX_%u",i+1);
    sprintf(buff_title,"h2_yxHitMap_BPIX_%u; y[cm] ; x[cm]",i+1);    
    h2_yxHitMap_BPIX_[i] = BPIXdir_.make<TH2F>( buff_name,buff_title,350,-3.5,+3.5,100,-1.,+1.);
  }

  // hCol = 380*3;
  // hRow = 340;
  // hCol = 190*3;
  // hRow = 170;

  // FPIX neg
  FPIXnegdir_ = fs_->mkdir( "FPIXneg" );
  // hCol = 380*3;
  // hRow = 340;
  for ( int i=0; i<MAX_FPIX; i++ ) {
    sprintf(buff_name, "h2_yxHitMap_FPIXneg_%u",i+1);
    sprintf(buff_title,"h2_yxHitMap_FPIXneg_%u; y [cm]; x [cm]",i+1);    
    h2_yxHitMap_FPIXneg_[i] = FPIXnegdir_.make<TH2F>( buff_name,buff_title,350,-3.5,+3.5,100,-1.,+1.);
  }
  // FPIX pos
  FPIXposdir_ = fs_->mkdir( "FPIXpos" );
  // hCol = 380*3;
  // hRow = 340;
  for ( int i=0; i<MAX_FPIX; i++ ) {
    sprintf(buff_name, "h2_yxHitMap_FPIXpos_%u",i+1);
    sprintf(buff_title,"h2_yxHitMap_FPIXpos_%u; y [cm]; x [cm]",i+1);    
    h2_yxHitMap_FPIXpos_[i] = FPIXposdir_.make<TH2F>( buff_name,buff_title,350,-3.5,+3.5,100,-1.,+1.);
  }

  simHitsBarrelHighTofToken_ = consumes<vector<PSimHit> > (simHitsBarrelHighTof_src_);
  simHitsBarrelLowTofToken_  = consumes<vector<PSimHit> > (simHitsBarrelLowTof_src_);
  simHitsEndcapHighTofToken_ = consumes<vector<PSimHit> > (simHitsEndcapHighTof_src_);
  simHitsEndcapLowTofToken_  = consumes<vector<PSimHit> > (simHitsEndcapLowTof_src_);
}

SimHitAnalyzer::~SimHitAnalyzer ()
{
}

void
SimHitAnalyzer::analyze (const edm::Event &event, const edm::EventSetup &setup)
{
  edm::Handle<vector<PSimHit> > simHitsBarrelHighTof;
  event.getByToken (simHitsBarrelHighTofToken_, simHitsBarrelHighTof);
  edm::Handle<vector<PSimHit> > simHitsBarrelLowTof;
  event.getByToken (simHitsBarrelLowTofToken_, simHitsBarrelLowTof);
  edm::Handle<vector<PSimHit> > simHitsEndcapHighTof;
  event.getByToken (simHitsEndcapHighTofToken_, simHitsEndcapHighTof);
  edm::Handle<vector<PSimHit> > simHitsEndcapLowTof;
  event.getByToken (simHitsEndcapLowTofToken_, simHitsEndcapLowTof);

  edm::ESHandle<TrackerGeometry> theTrackerGeometry;
  setup.get<TrackerDigiGeometryRecord> ().get (theTrackerGeometry);
  const TrackerGeometry &theTracker (*theTrackerGeometry);

  // Retrieve tracker topology from geometry
  edm::ESHandle<TrackerTopology> theTrackerTopologyHandle;
  setup.get<TrackerTopologyRcd> ().get(theTrackerTopologyHandle);
  const TrackerTopology* const theTrackerTopology = theTrackerTopologyHandle.product();

  // if ( theTracker.isThere(GeomDetEnumerators::P2OTB) ) 
  //   std::cout << " theTracker.isThere(GeomDetEnumerators::P2OTB) " << std::endl;
  // if ( theTracker.isThere(GeomDetEnumerators::P1PXB) ) 
  //   std::cout << " theTracker.isThere(GeomDetEnumerators::P1PXB) " << std::endl;
  // if ( theTracker.isThere(GeomDetEnumerators::P2PXEC) ) 
  //   std::cout << " theTracker.isThere(GeomDetEnumerators::P2PXEC) " << std::endl;



  for (const auto &simHit : *simHitsBarrelHighTof)
    {
      edm::LogInfo("SimHitAnalyzer::analyze B HighTof/1 ") << simHit.detUnitId ();
      DetId theDetUnitId (simHit.detUnitId ());
      edm::LogInfo("SimHitAnalyzer::analyze B HighTof/2 ");

      if (theDetUnitId.subdetId() != GeomDetEnumerators::invalidDet ) {
	const GeomDet *theDet = theTracker.idToDet (theDetUnitId);
	edm::LogInfo("SimHitAnalyzer::analyze B HighTof/3 ");

	double x, y, z;
	x = theDet->surface ().toGlobal (simHit.localPosition ()).x ();
	y = theDet->surface ().toGlobal (simHit.localPosition ()).y ();
	z = theDet->surface ().toGlobal (simHit.localPosition ()).z ();
	
	oneDHists_.at ("rho")->Fill (sqrt(x*x+y*y));
	twoDHists_.at ("rhoPhi")->Fill (x, y);
	twoDHists_.at ("rhoZ")->Fill (z, hypot (x, y));
	
      } else  {
	std::cout << "BarrelHighTof InvalidDet(): " <<  simHit.detUnitId () << std::endl;
      }


    }
  for (const auto &simHit : *simHitsBarrelLowTof)
    {
      edm::LogInfo("SimHitAnalyzer::analyze B LowTof/1 ") << simHit.detUnitId ();
      DetId theDetUnitId (simHit.detUnitId ());
      edm::LogInfo("SimHitAnalyzer::analyze B LowTof/2 ");

      if (theDetUnitId.subdetId() != GeomDetEnumerators::invalidDet ) {
	edm::LogInfo("SimHitAnalyzer::analyze B LowTof/3a ") << theDetUnitId.subdetId();
	const GeomDet *theDet = theTracker.idToDet (theDetUnitId);
	edm::LogInfo("SimHitAnalyzer::analyze B LowTof/3b ");

	double x, y, z;
	x = theDet->surface ().toGlobal (simHit.localPosition ()).x ();
	y = theDet->surface ().toGlobal (simHit.localPosition ()).y ();
	z = theDet->surface ().toGlobal (simHit.localPosition ()).z ();
	
	oneDHists_.at ("rho")->Fill (sqrt(x*x+y*y));
	twoDHists_.at ("rhoPhi")->Fill (x, y);
	twoDHists_.at ("rhoZ")->Fill (z, hypot (x, y));
	
	// Get the geom-detector
	// const PixelGeomDetUnit * thePixelGeomDet = dynamic_cast<const PixelGeomDetUnit*> ( theDet );
	// Get the pixel Topology
	// const PixelTopology &topology = thePixelGeomDet->specificTopology();
	
	// Local (x,y) HitMap
	if (theDetUnitId.subdetId() == PixelSubdetector::PixelBarrel) {
	  int layer = theTrackerTopology->pxbLayer(theDetUnitId);
	  edm::LogInfo("SimHitAnalyzer::analyze B LowTof/4 ") << layer;
	  h2_yxHitMap_BPIX_[layer-1]->Fill(simHit.localPosition().y(),simHit.localPosition().x());
	}
      } else  {
	std::cout << "BarrelLowTof InvalidDet(): " <<  simHit.detUnitId () << std::endl;
      }
      

    }
  for (const auto &simHit : *simHitsEndcapHighTof)
    {
      edm::LogInfo("SimHitAnalyzer::analyze E HighTof/1") << simHit.detUnitId ();
      DetId theDetUnitId (simHit.detUnitId ());
      edm::LogInfo("SimHitAnalyzer::analyze E HighTof/2 ");

      if (theDetUnitId.subdetId() != GeomDetEnumerators::invalidDet ) {
	const GeomDet *theDet = theTracker.idToDet (theDetUnitId);
	edm::LogInfo("SimHitAnalyzer::analyze E HighTof/3");

	double x, y, z;
	x = theDet->surface ().toGlobal (simHit.localPosition ()).x ();
	y = theDet->surface ().toGlobal (simHit.localPosition ()).y ();
	z = theDet->surface ().toGlobal (simHit.localPosition ()).z ();
	
	twoDHists_.at ("rhoZ")->Fill (z, hypot (x, y));
      } else {
	std::cout << "EndcapHighTof InvalidDet(): " <<  simHit.detUnitId () << std::endl;
      }

    }
  for (const auto &simHit : *simHitsEndcapLowTof)
    {
      edm::LogInfo("SimHitAnalyzer::analyze E LowTof/1 ") << simHit.detUnitId ();
      DetId theDetUnitId (simHit.detUnitId ());
      edm::LogInfo("SimHitAnalyzer::analyze E LowTof/2 ");

      if (theDetUnitId.subdetId() != GeomDetEnumerators::invalidDet ) {
	const GeomDet *theDet = theTracker.idToDet (theDetUnitId);
	edm::LogInfo("SimHitAnalyzer::analyze E LowTof/3");

	double x, y, z;
	x = theDet->surface ().toGlobal (simHit.localPosition ()).x ();
	y = theDet->surface ().toGlobal (simHit.localPosition ()).y ();
	z = theDet->surface ().toGlobal (simHit.localPosition ()).z ();
	
	twoDHists_.at ("rhoZ")->Fill (z, hypot (x, y));
	
	// Get the geom-detector
	// const PixelGeomDetUnit * thePixelGeomDet = dynamic_cast<const PixelGeomDetUnit*> ( theDet );
	// Get the pixel Topology
	// const PixelTopology &topology = thePixelGeomDet->specificTopology();
	
	if (theDetUnitId.subdetId() == PixelSubdetector::PixelEndcap) {
	  int layer = theTrackerTopology->pxfDisk(theDetUnitId);
	  edm::LogInfo("SimHitAnalyzer::analyze E LowTof/4 ") << layer;
	  if ( theTrackerTopology->pxfSide(theDetUnitId) == 1 ) { 
	    h2_yxHitMap_FPIXneg_[layer-1]->Fill(simHit.localPosition().y(),simHit.localPosition().x());
	  } else if ( theTrackerTopology->pxfSide(theDetUnitId) == 2 ) { 
	    h2_yxHitMap_FPIXpos_[layer-1]->Fill(simHit.localPosition().y(),simHit.localPosition().x());
	  }
	}
      } else {
	std::cout << "EndcapLowTof InvalidDet(): " <<  simHit.detUnitId () << std::endl;
      }


    }
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(SimHitAnalyzer);
