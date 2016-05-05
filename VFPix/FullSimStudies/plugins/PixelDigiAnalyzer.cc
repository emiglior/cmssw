#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"
#include "DataFormats/SiPixelDigi/interface/PixelDigi.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "Geometry/Records/interface/TrackerTopologyRcd.h"

#include "VFPix/FullSimStudies/plugins/PixelDigiAnalyzer.h"

PixelDigiAnalyzer::PixelDigiAnalyzer (const edm::ParameterSet &cfg) :
  simSiPixelDigis_src_ (cfg.getParameter<edm::InputTag> ("pixelDigis"))
{
  //  TH1::SetDefaultSumw2 ();

  h1_adc_BPIX_    = new TH1Fptr[MAX_BPIX];
  h1_adc_FPIXneg_ = new TH1Fptr[MAX_FPIX];
  h1_adc_FPIXpos_ = new TH1Fptr[MAX_FPIX];

  h2_colrowHitMap_BPIX_    = new TH2Fptr[MAX_BPIX];
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
}

PixelDigiAnalyzer::~PixelDigiAnalyzer ()
{
}

void
PixelDigiAnalyzer::analyze (const edm::Event &event, const edm::EventSetup &setup)
{

  edm::Handle<edm::DetSetVector<PixelDigi> > pixelDigis;
  event.getByToken (pixelDigiToken_, pixelDigis);

  // Retrieve tracker topology from geometry
  edm::ESHandle<TrackerTopology> theTrackerTopologyHandle;
  setup.get<TrackerTopologyRcd> ().get(theTrackerTopologyHandle);
  const TrackerTopology* const theTrackerTopology = theTrackerTopologyHandle.product();

  edm::DetSetVector<PixelDigi>::const_iterator DSViter;
  edm::DetSet<PixelDigi>::const_iterator pixelDigi; 
  for(DSViter = pixelDigis->begin(); DSViter != pixelDigis->end(); DSViter++) {
    DetId theDetUnitId(DSViter->id);

    // loop on all digis on this Det
    for ( pixelDigi= DSViter->begin(); pixelDigi != DSViter->end(); pixelDigi++) {
      //       std::cout << pixelDigi->adc() << std::endl; // adc = 255 (always!)
      if (theDetUnitId.subdetId() == PixelSubdetector::PixelBarrel) {
	int layer = theTrackerTopology->pxbLayer(theDetUnitId);
	h2_colrowHitMap_BPIX_[layer-1]->Fill(pixelDigi->column(),pixelDigi->row());
	h1_adc_BPIX_[layer-1]->Fill(pixelDigi->adc());
      } else if (theDetUnitId.subdetId() == PixelSubdetector::PixelEndcap) {
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
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(PixelDigiAnalyzer);
