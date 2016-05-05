#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"
#include "DataFormats/SiPixelDigi/interface/PixelDigi.h"
#include "DataFormats/Phase2TrackerDigi/interface/Phase2TrackerDigi.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerTopologyRcd.h"
#include "Geometry/CommonDetUnit/interface/GeomDetEnumerators.h"

#include "VFPix/FullSimStudies/plugins/PixelDigiAnalyzer.h"

PixelDigiAnalyzer::PixelDigiAnalyzer (const edm::ParameterSet &cfg) :
  simSiPixelDigis_src_ (cfg.getParameter<edm::InputTag> ("pixelDigis")),
  simPhase2TrackerDigis_src_ (cfg.getParameter<edm::InputTag> ("phase2TrackerDigis"))
{
  //  TH1::SetDefaultSumw2 ();

  h1_adc_BPIX_    = new TH1Fptr[MAX_BPIX];
  h1_adc_OTPIX_   = new TH1Fptr[MAX_OTPIX];
  h1_adc_FPIXneg_ = new TH1Fptr[MAX_FPIX];
  h1_adc_FPIXpos_ = new TH1Fptr[MAX_FPIX];

  h2_colrowHitMap_BPIX_    = new TH2Fptr[MAX_BPIX];
  h2_colrowHitMap_OTPIX_   = new TH2Fptr[MAX_OTPIX];
  h2_colrowHitMap_FPIXneg_ = new TH2Fptr[MAX_FPIX];
  h2_colrowHitMap_FPIXpos_ = new TH2Fptr[MAX_FPIX];

  char buff_name[50];
  char buff_title[50];

  int hCol, hRow;
  
  //-- BPIX
  BPIXdir_ = fs_->mkdir( "BPIX" );
  for ( int i=0; i<MAX_BPIX; i++ ) {
    // HitMap
    sprintf(buff_name, "h2_colrowHitMap_BPIX_%u",i+1);
    sprintf(buff_title,"h2_colrowHitMap_BPIX_%u; col; row",i+1);    
    if ( i < 2 )  {
      hCol = 380*3;
      hRow = 340;
    } else {
      hCol = 190*3;
      hRow = 170;
    }
    h2_colrowHitMap_BPIX_[i] = BPIXdir_.make<TH2F>( buff_name,buff_title,hCol,-0.5,-0.5+hCol,hRow,-0.5,-0.5+hRow);

    // adc
    sprintf(buff_name, "h1_adc_BPIX_%u",i+1);
    sprintf(buff_title,"h1_adc_BPIX_%u ; col; row",i+1);    
    h1_adc_BPIX_[i] = BPIXdir_.make<TH1F>( buff_name,buff_title,512,-0.5,511.5);

  }

  //-- OTPIX (OuterTracker)
  OTPIXdir_ = fs_->mkdir( "OTPIX" );
  for ( int i=0; i<MAX_OTPIX; i++ ) {
    // HitMap
    sprintf(buff_name, "h2_colrowHitMap_OTPIX_%u",i+1);
    sprintf(buff_title,"h2_colrowHitMap_OTPIX_%u; col; row",i+1);    
    hCol = 64;
    hRow = 1024;
    h2_colrowHitMap_OTPIX_[i] = OTPIXdir_.make<TH2F>( buff_name,buff_title,hCol,-0.5,-0.5+hCol,hRow,-0.5,-0.5+hRow);

    // adc
    sprintf(buff_name, "h1_adc_OTPIX_%u",i+1);
    sprintf(buff_title,"h1_adc_OTPIX_%u ; col; row",i+1);    
    h1_adc_OTPIX_[i] = OTPIXdir_.make<TH1F>( buff_name,buff_title,512,-0.5,511.5);

  }

  //-- FPIX neg
  FPIXnegdir_ = fs_->mkdir( "FPIXneg" );
  hCol = 380*3;
  hRow = 340;
  for ( int i=0; i<MAX_FPIX; i++ ) {
    // HitMap
    sprintf(buff_name, "h2_colrowHitMap_FPIXneg_%u",i+1);
    sprintf(buff_title,"h2_colrowHitMap_FPIXneg_%u ; col; row",i+1);    
    h2_colrowHitMap_FPIXneg_[i] = FPIXnegdir_.make<TH2F>( buff_name,buff_title,hCol,-0.5,-0.5+hCol,hRow,-0.5,-0.5+hRow);

    // adc
    sprintf(buff_name, "h1_adc_FPIXneg_%u",i+1);
    sprintf(buff_title,"h1_adc_FPIXneg_%u",i+1);    
    h1_adc_FPIXneg_[i] = FPIXnegdir_.make<TH1F>( buff_name,buff_title,512,-0.5,511.5);
  }

  //-- FPIX pos
  FPIXposdir_ = fs_->mkdir( "FPIXpos" );
  hCol = 380*3;
  hRow = 340;
  for ( int i=0; i<MAX_FPIX; i++ ) {
    // HitMap
    sprintf(buff_name, "h2_colrowHitMap_FPIXpos_%u",i+1);
    sprintf(buff_title,"h2_colrowHitMap_FPIXpos_%u",i+1);    
    h2_colrowHitMap_FPIXpos_[i] = FPIXposdir_.make<TH2F>( buff_name,buff_title,hCol,-0.5,-0.5+hCol,hRow,-0.5,-0.5+hRow);

    // adc
    sprintf(buff_name, "h1_adc_FPIXpos_%u",i+1);
    sprintf(buff_title,"h1_adc_FPIXpos_%u",i+1);    
    h1_adc_FPIXpos_[i] = FPIXposdir_.make<TH1F>( buff_name,buff_title,512,-0.5,511.5);
  }

  pixelDigiToken_ = consumes<edm::DetSetVector<PixelDigi> > (simSiPixelDigis_src_);
  phase2TrackerDigiToken_ = consumes<edm::DetSetVector<Phase2TrackerDigi> > (simPhase2TrackerDigis_src_);
}

PixelDigiAnalyzer::~PixelDigiAnalyzer ()
{
}

void
PixelDigiAnalyzer::analyze (const edm::Event &event, const edm::EventSetup &setup)
{

  // tracker geometry
  edm::ESHandle<TrackerGeometry> theTrackerGeometry;
  setup.get<TrackerDigiGeometryRecord> ().get (theTrackerGeometry);
  const TrackerGeometry &theTracker (*theTrackerGeometry);

  // Retrieve tracker topology from geometry
  edm::ESHandle<TrackerTopology> theTrackerTopologyHandle;
  setup.get<TrackerTopologyRcd> ().get(theTrackerTopologyHandle);
  const TrackerTopology* const theTrackerTopology = theTrackerTopologyHandle.product();


  // InnerPixel
  //-----------
  edm::Handle<edm::DetSetVector<PixelDigi> > pixelDigis;
  event.getByToken (pixelDigiToken_, pixelDigis);

  edm::DetSetVector<PixelDigi>::const_iterator DSViter;
  edm::DetSet<PixelDigi>::const_iterator pixelDigi; 
  for(DSViter = pixelDigis->begin(); DSViter != pixelDigis->end(); DSViter++) {
    DetId theDetUnitId(DSViter->id);

    // loop on all digis on this Det
    for ( pixelDigi= DSViter->begin(); pixelDigi != DSViter->end(); pixelDigi++) {
      //       std::cout << pixelDigi->adc() << std::endl; // adc = 255 (always!)
      if ( theTracker.geomDetSubDetector(theDetUnitId.subdetId()) == GeomDetEnumerators::P1PXB ) {                    // old-style PixelSubdetector::PixelBarrel
	int layer = theTrackerTopology->pxbLayer(theDetUnitId);
	h2_colrowHitMap_BPIX_[layer-1]->Fill(pixelDigi->column(),pixelDigi->row());
	h1_adc_BPIX_[layer-1]->Fill(pixelDigi->adc());
      } else if ( theTracker.geomDetSubDetector(theDetUnitId.subdetId()) == GeomDetEnumerators::P2PXEC ) {             // old-style PixelSubdetector::PixelEndcap
	int layer = theTrackerTopology->pxfDisk(theDetUnitId);
	if ( theTrackerTopology->pxfSide(theDetUnitId) == 1 ) { 
	  h2_colrowHitMap_FPIXneg_[layer-1]->Fill(pixelDigi->column(),pixelDigi->row());
	  h1_adc_FPIXneg_[layer-1]->Fill(pixelDigi->adc());
	} else if ( theTrackerTopology->pxfSide(theDetUnitId) == 2 ) { 
	  h2_colrowHitMap_FPIXpos_[layer-1]->Fill(pixelDigi->column(),pixelDigi->row());
	  h1_adc_FPIXpos_[layer-1]->Fill(pixelDigi->adc());
	}
      }
    }
  }

  // OuterTracker
  //--------------
  edm::Handle<edm::DetSetVector<Phase2TrackerDigi> > phase2TrackerDigis;
  event.getByToken (phase2TrackerDigiToken_, phase2TrackerDigis);

  edm::DetSetVector<Phase2TrackerDigi>::const_iterator DSViter2;
  edm::DetSet<Phase2TrackerDigi>::const_iterator phase2TrackerDigi; 

  for(DSViter2 = phase2TrackerDigis->begin(); DSViter2 != phase2TrackerDigis->end(); DSViter2++) {
    DetId theDetUnitId(DSViter2->id);
    // loop on all digis on this Det
    for ( phase2TrackerDigi= DSViter2->begin(); phase2TrackerDigi != DSViter2->end(); phase2TrackerDigi++) {
      if ( theTracker.geomDetSubDetector(theDetUnitId.subdetId()) == GeomDetEnumerators::P2OTB ) { 
	if ( theTracker.getDetectorType(theDetUnitId) == TrackerGeometry::ModuleType::Ph2PSP ) {
	  //  layer() method explained in Geometry/TrackerNumberingBuilder/README.md
	  int layer = theTrackerTopology->layer(theDetUnitId);
	  h2_colrowHitMap_OTPIX_[layer-1]->Fill(phase2TrackerDigi->column(),phase2TrackerDigi->row());
	  //	  h1_adc_OTPIX_[layer-1]->Fill(phase2TrackerDigi->adc());	
	}

      }
    }
  }


  
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(PixelDigiAnalyzer);
