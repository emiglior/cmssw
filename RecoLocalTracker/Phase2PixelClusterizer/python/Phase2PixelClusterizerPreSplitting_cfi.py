
import FWCore.ParameterSet.Config as cms

#
from CondTools.SiPixel.SiPixelGainCalibrationService_cfi import *
from RecoLocalTracker.Phase2PixelClusterizer.Phase2PixelClusterizer_cfi import phase2PixelClusters as _phase2PixelClusters
phase2PixelClustersPreSplitting = _phase2PixelClusters.clone()
