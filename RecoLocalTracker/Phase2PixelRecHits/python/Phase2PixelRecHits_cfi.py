import FWCore.ParameterSet.Config as cms

phase2PixelRecHits = cms.EDProducer("Phase2PixelRecHitConverter",
    src = cms.InputTag("Phase2PixelClusters"),
    CPE = cms.string('PixelCPEGeneric'),
    VerboseLevel = cms.untracked.int32(0),

)

phase2PixelRecHitsPreSplitting = phase2PixelRecHits.clone(
    src = 'phase2PixelClustersPreSplitting'
)
