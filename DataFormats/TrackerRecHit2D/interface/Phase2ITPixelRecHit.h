#ifndef DataFormats_Phase2ITPixelRecHit_h
#define DataFormats_Phase2ITPixelRecHit_h 1

//---------------------------------------------------------------------------
//!  \class Phase2ITPixelRecHit
//!  \brief Pixel Reconstructed Hit
//!
//!  A pixel hit is a 2D position and error in a given
//!  pixel sensor. It contains a persistent reference edm::Ref to the
//!  pixel cluster. 
//!
// EM 2016.05 development for phase2 pixel
// The IT IS chain should be  Phase2ITPixelRecHit->TrackerSingleRecHit->BaseTrackerRecHit-> TrackingRecHit
//---------------------------------------------------------------------------


#include "DataFormats/Common/interface/DetSetVectorNew.h"


#include "DataFormats/GeometrySurface/interface/LocalError.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h"

#include "DataFormats/Phase2ITPixelCluster/interface/Phase2ITPixelCluster.h"
// It contains the typedef used here 
// typedef edmNew::DetSetVector<Phase2ITPixelCluster> Phase2ITPixelClusterCollectionNew;
// typedef edm::Ref<Phase2ITPixelClusterCollectionNew, Phase2ITPixelCluster> Phase2ITPixelClusterRefNew;

//! Our base class
// #include "DataFormats/TrackerRecHit2D/interface/TrackerSingleRecHit.h"

// 

class Phase2ITPixelRecHit {
  
public:
  Phase2ITPixelRecHit()  {;}  
  ~Phase2ITPixelRecHit() {;}
  Phase2ITPixelRecHit( const LocalPoint& pos , const LocalError& err, 
		     GeomDet const & idet, // not used for the moment 
		     Phase2ITPixelClusterRefNew const&  cluster) : pos_(pos), err_(err), cluster_(cluster) {;}

  LocalPoint localPosition()      const { return pos_; }
  LocalError localPositionError() const { return err_; }
  Phase2ITPixelClusterRefNew cluster() const { return cluster_; }
   
  
private:
  LocalPoint pos_;
  LocalError err_;
  Phase2ITPixelClusterRefNew cluster_;
  
};

#endif
