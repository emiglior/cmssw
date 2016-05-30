#ifndef DataFormats_Phase2ITPixelCluster_classes_h
#define DataFormats_Phase2ITPixelCluster_classes_h

#include "DataFormats/Common/interface/ContainerMask.h"
#include "DataFormats/Common/interface/Ref.h" 
#include "DataFormats/Common/interface/Wrapper.h"
#include "DataFormats/Phase2ITPixelCluster/interface/Phase2ITPixelCluster.h"
#include "DataFormats/Phase2ITPixelCluster/interface/Phase2ITPixelClusterShapeCache.h"

namespace DataFormats_Phase2ITPixelCluster {
  struct dictionary {

    edm::Wrapper< Phase2ITPixelCluster > w0;

    edm::Wrapper<std::vector< Phase2ITPixelCluster > > w1;
    
    edmNew::DetSetVector< Phase2ITPixelCluster > dsvn;
    edm::Wrapper< edmNew::DetSetVector< Phase2ITPixelCluster > > wdsvn;

    edm::Ref< edmNew::DetSetVector< Phase2ITPixelCluster >, Phase2ITPixelCluster, edmNew::DetSetVector< Phase2ITPixelCluster >::FindForDetSetVector > refNew;

    edm::ContainerMask< edmNew::DetSetVector< Phase2ITPixelCluster > > cm1;
    edm::Wrapper< edm::ContainerMask< edmNew::DetSetVector< Phase2ITPixelCluster > > > w_cm1;

    edm::Wrapper<std::vector< edmNew::DetSet< Phase2ITPixelCluster > > > w2;
    std::vector< edm::Ref< edmNew::DetSetVector< Phase2ITPixelCluster >,Phase2ITPixelCluster,edmNew::DetSetVector< Phase2ITPixelCluster >::FindForDetSetVector > > dummy_v;
    edmNew::DetSetVector< edm::Ref< edmNew::DetSetVector<Phase2ITPixelCluster>,Phase2ITPixelCluster,edmNew::DetSetVector< Phase2ITPixelCluster>::FindForDetSetVector > > dumm_dtvr;
    edm::Wrapper< edmNew::DetSetVector< edm::Ref< edmNew::DetSetVector< Phase2ITPixelCluster >,Phase2ITPixelCluster,edmNew::DetSetVector< Phase2ITPixelCluster>::FindForDetSetVector > > > dumm_dtvr_w;

    Phase2ITPixelClusterShapeCache clusterShapeCache;

    edm::Wrapper< Phase2ITPixelClusterShapeCache > w4;
    edm::Wrapper< std::vector< Phase2ITPixelCluster > > w5;

    Phase2ITPixelClusterCollectionNew c1_new;
    edm::Wrapper< Phase2ITPixelClusterCollectionNew > w1_new;
 
  };
}

#endif // Phase2ITPixelCluster_classes_h
