#ifndef DataFormats_Phase2PixelRecHit_h
#define DataFormats_Phase2PixelRecHit_h 1

//---------------------------------------------------------------------------
//!  \class Phase2PixelRecHit
//!  \brief Pixel Reconstructed Hit
//!
//!  A pixel hit is a 2D position and error in a given
//!  pixel sensor. It contains a persistent reference edm::Ref to the
//!  pixel cluster. 
//!
// EM 2016.05 development for phase2 pixel
// The IT IS chain should be  Phase2PixelRecHit->TrackerSingleRecHit->BaseTrackerRecHit-> TrackingRecHit
//---------------------------------------------------------------------------


#include "DataFormats/Common/interface/DetSetVectorNew.h"


#include "DataFormats/GeometrySurface/interface/LocalError.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h"

#include "DataFormats/Phase2ITPixelCluster/interface/Phase2PixelCluster.h"
// It contains the typedef used here 
// typedef edmNew::DetSetVector<Phase2PixelCluster> Phase2PixelClusterCollectionNew;
// typedef edm::Ref<Phase2PixelClusterCollectionNew, Phase2PixelCluster> Phase2PixelClusterRefNew;

//! Our base class
// #include "DataFormats/TrackerRecHit2D/interface/TrackerSingleRecHit.h"

// 

class Phase2PixelRecHit {
  
public:
  Phase2PixelRecHit()  {;}  
  ~Phase2PixelRecHit() {;}
  Phase2PixelRecHit( const LocalPoint& pos , const LocalError& err, 
		     GeomDet const & idet, // not used for the moment 
		     Phase2PixelClusterRefNew const&  cluster) : pos_(pos), err_(err), cluster_(cluster) {;}

  LocalPoint localPosition()      const { return pos_; }
  LocalError localPositionError() const { return err_; }
  Phase2PixelClusterRefNew cluster() const { return cluster_; }
   
  
private:
  LocalPoint pos_;
  LocalError err_;
  Phase2PixelClusterRefNew cluster_;
  
};

#endif
