#ifndef Phase2PixelRecHit_CLASSES_H
#define Phase2PixelRecHit_CLASSES_H

#include "DataFormats/Phase2PixelRecHit/interface/Phase2PixelRecHitCollection.h"
#include "DataFormats/Phase2PixelRecHit/interface/Phase2PixelRecHit.h" 


#include "DataFormats/Common/interface/ClonePolicy.h"
#include "DataFormats/Common/interface/DetSetVector.h" 
#include "DataFormats/Common/interface/OwnVector.h"
#include "DataFormats/Common/interface/RangeMap.h"
#include "DataFormats/Common/interface/Wrapper.h"

#include <boost/cstdint.hpp> 
#include <vector>

namespace DataFormats_Phase2PixelRecHit {
  struct dictionary {
    Phase2PixelRecHit b1;

    edm::ClonePolicy<Phase2PixelRecHit> b2;

    edm::OwnVector<Phase2PixelRecHit,
      edm::ClonePolicy<Phase2PixelRecHit> > b3;
    edm::OwnVector<Phase2PixelRecHit,
      edm::ClonePolicy<Phase2PixelRecHit> >::const_iterator it3;


    edm::Wrapper< edm::RangeMap<DetId,
      edm::OwnVector<Phase2PixelRecHit,
      edm::ClonePolicy<Phase2PixelRecHit> >, 
      edm::ClonePolicy<Phase2PixelRecHit> > >  phase2PixelRecHitCollectionWrapper;
    edm::RangeMap<DetId,
      edm::OwnVector<Phase2PixelRecHit,
      edm::ClonePolicy<Phase2PixelRecHit> >, 
      edm::ClonePolicy<Phase2PixelRecHit> >::id_iterator itpix;

    edm::Wrapper<edmNew::DetSetVector<Phase2PixelRecHit> > wdstvDummy3;

  };
}

#endif // PHASE2PIXELRECHIT_CLASSES_H
