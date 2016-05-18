#ifndef DataFormats_Phase2PixelRecHitCollection_H
#define DataFormats_Phase2PixelRecHitCollection_H

#include "DataFormats/Phase2PixelRecHit/interface/Phase2PixelRecHit.h"

#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"

typedef edmNew::DetSetVector<Phase2PixelRecHit> Phase2PixelRecHitCollection;
typedef Phase2PixelRecHitCollection             Phase2PixelRecHitCollectionNew;

#endif


