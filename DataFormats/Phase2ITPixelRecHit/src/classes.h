#ifndef Phase2ITPixelRecHit_CLASSES_H
#define Phase2ITPixelRecHit_CLASSES_H

#include "DataFormats/Phase2ITPixelRecHit/interface/Phase2ITPixelRecHitCollection.h"
#include "DataFormats/Phase2ITPixelRecHit/interface/Phase2ITPixelRecHit.h" 


#include "DataFormats/Common/interface/ClonePolicy.h"
#include "DataFormats/Common/interface/DetSetVector.h" 
#include "DataFormats/Common/interface/OwnVector.h"
#include "DataFormats/Common/interface/RangeMap.h"
#include "DataFormats/Common/interface/Wrapper.h"

#include <boost/cstdint.hpp> 
#include <vector>

namespace DataFormats_Phase2ITPixelRecHit {
  struct dictionary {
    Phase2ITPixelRecHit b1;

    edm::ClonePolicy<Phase2ITPixelRecHit> b2;

    edm::OwnVector<Phase2ITPixelRecHit,
      edm::ClonePolicy<Phase2ITPixelRecHit> > b3;
    edm::OwnVector<Phase2ITPixelRecHit,
      edm::ClonePolicy<Phase2ITPixelRecHit> >::const_iterator it3;


    edm::Wrapper< edm::RangeMap<DetId,
      edm::OwnVector<Phase2ITPixelRecHit,
      edm::ClonePolicy<Phase2ITPixelRecHit> >, 
      edm::ClonePolicy<Phase2ITPixelRecHit> > >  phase2ITPixelRecHitCollectionWrapper;
    edm::RangeMap<DetId,
      edm::OwnVector<Phase2ITPixelRecHit,
      edm::ClonePolicy<Phase2ITPixelRecHit> >, 
      edm::ClonePolicy<Phase2ITPixelRecHit> >::id_iterator itpix;

    edm::Wrapper<edmNew::DetSetVector<Phase2ITPixelRecHit> > wdstvDummy3;

  };
}

#endif // Phase2ITPixelRecHIT_CLASSES_H
