#ifndef RecoLocalTracker_Phase2ITPixelRecHits_Phase2PixelCPEGenericESProducer_h
#define RecoLocalTracker_Phase2ITPixelRecHits_Phase2PixelCPEGenericESProducer_h

#include "FWCore/Framework/interface/ESProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "RecoLocalTracker/Records/interface/TkPixelCPERecord.h"
#include "RecoLocalTracker/ClusterParameterEstimator/interface/Phase2ITPixelClusterParameterEstimator.h"
#include <memory>

class  Phase2PixelCPEGenericESProducer: public edm::ESProducer{
 public:
  Phase2PixelCPEGenericESProducer(const edm::ParameterSet & p);
  virtual ~Phase2PixelCPEGenericESProducer(); 
  std::shared_ptr<Phase2ITPixelClusterParameterEstimator> produce(const TkPixelCPERecord &);
 private:
  std::shared_ptr<Phase2ITPixelClusterParameterEstimator> cpe_;
  edm::ParameterSet pset_;
  edm::ESInputTag magname_;
  bool useLAWidthFromDB_;
  bool useLAAlignmentOffsets_;
};


#endif




