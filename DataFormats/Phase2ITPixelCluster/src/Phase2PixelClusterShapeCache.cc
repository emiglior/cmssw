#include "DataFormats/Phase2ITPixelCluster/interface/Phase2PixelClusterShapeCache.h"
#include "FWCore/Utilities/interface/Exception.h"

Phase2PixelClusterShapeData::~Phase2PixelClusterShapeData() {}

Phase2PixelClusterShapeCache::~Phase2PixelClusterShapeCache() {}

void Phase2PixelClusterShapeCache::checkRef(const ClusterRef& ref) const {
  if(ref.id() != productId_)
    throw cms::Exception("InvalidReference") << "Phase2PixelClusterShapeCache caches values for Phase2PixelClusters with ProductID " << productId_ << ", got Phase2PixelClusterRef with ID " << ref.id();
  if(ref.index() >= data_.size())
    throw cms::Exception("InvalidReference") << "Phase2PixelClusterShapeCache caches values for Phase2PixelClusters with ProductID " << productId_ << " that has " << data_.size() << " clusters, got Phase2PixelClusterRef with index " << ref.index();
}
