import FWCore.ParameterSet.Config as cms

#
# activate signal shape in IT only
#

def customizeSiPhase2ITSignalShape(process):
    ## for standard mixing
    if hasattr(process,'mix') and hasattr(process.mix,'digitizers') and hasattr(process.mix.digitizers,'pixel'): 
        if hasattr(process.mix.digitizers.pixel,'PixelDigitizerAlgorithm'):
            print("# Activating signal shape emulation in IT pixel (planar)")
            process.mix.digitizers.pixel.PixelDigitizerAlgorithm.ApplyTimewalk = cms.bool(True)
            process.mix.digitizers.pixel.PixelDigitizerAlgorithm.minBunch = cms.int32(-5)
            process.mix.digitizers.pixel.PixelDigitizerAlgorithm.maxBunch = cms.int32(1)
            process.mix.digitizers.pixel.PixelDigitizerAlgorithm.TofLowerCut = cms.double(-5.)
            process.mix.digitizers.pixel.PixelDigitizerAlgorithm.TofUpperCut = cms.double(+20.)
        if hasattr(process.mix.digitizers.pixel,'Pixel3DDigitizerAlgorithm'):
            print("# Activating signal shape emulation in IT pixel (3D)")
            process.mix.digitizers.pixel.Pixel3DDigitizerAlgorithm.ApplyTimewalk = cms.bool(True)
            process.mix.digitizers.pixel.Pixel3DDigitizerAlgorithm.minBunch = cms.int32(-5)
            process.mix.digitizers.pixel.Pixel3DDigitizerAlgorithm.maxBunch = cms.int32(1)
            process.mix.digitizers.pixel.Pixel3DDigitizerAlgorithm.TofLowerCut = cms.double(-5.)
            process.mix.digitizers.pixel.Pixel3DDigitizerAlgorithm.TofUpperCut = cms.double(+20.)


    ## for pre-mixing
    if hasattr(process, "mixData") and hasattr(process.mixData, "workers") and hasattr(process.mixData.workers, "pixel"):
        if hasattr(process.mixData.workers.pixel,'PixelDigitizerAlgorithm'):
            print("# Activating signal shape emulation in IT pixel (planar)")
            process.mixData.workers.pixel.PixelDigitizerAlgorithm.ApplyTimewalk = cms.bool(True)
            process.mixData.workers.pixel.PixelDigitizerAlgorithm.minBunch = cms.int32(-5)
            process.mixData.workers.pixel.PixelDigitizerAlgorithm.maxBunch = cms.int32(1)
            process.mixData.workers.pixel.PixelDigitizerAlgorithm.TofLowerCut = cms.double(-5.)
            process.mixData.workers.pixel.PixelDigitizerAlgorithm.TofUpperCut = cms.double(+20.)
        if hasattr(process.mixData.workers.pixel,'Pixel3DDigitizerAlgorithm'):
            print("# Activating signal shape emulation in IT pixel (3D)")
            process.mixData.workers.pixel.Pixel3DDigitizerAlgorithm.ApplyTimewalk = cms.bool(True)
            process.mixData.workers.pixel.Pixel3DDigitizerAlgorithm.minBunch = cms.int32(-5)
            process.mixData.workers.pixel.Pixel3DDigitizerAlgorithm.maxBunch = cms.int32(1)
            process.mixData.workers.pixel.Pixel3DDigitizerAlgorithm.TofLowerCut = cms.double(-5.)
            process.mixData.workers.pixel.Pixel3DDigitizerAlgorithm.TofUpperCut = cms.double(+20.)

    return process


def customizeSiPhase2ITSignalShapeTOF(process):
    if hasattr(process,'mix') and hasattr(process.mix,'digitizers') and hasattr(process.mix.digitizers,'pixel'): 
        if hasattr(process.mix.digitizers.pixel,'PixelDigitizerAlgorithm'):
            process.mix.digitizers.pixel.PixelDigitizerAlgorithm.minBunch = cms.int32(-5)
            process.mix.digitizers.pixel.PixelDigitizerAlgorithm.maxBunch = cms.int32(1)
            process.mix.digitizers.pixel.PixelDigitizerAlgorithm.TofLowerCut = cms.double(-5.)
            process.mix.digitizers.pixel.PixelDigitizerAlgorithm.TofUpperCut = cms.double(+20.)
        if hasattr(process.mix.digitizers.pixel,'Pixel3DDigitizerAlgorithm'):
            process.mix.digitizers.pixel.Pixel3DDigitizerAlgorithm.minBunch = cms.int32(-5)
            process.mix.digitizers.pixel.Pixel3DDigitizerAlgorithm.maxBunch = cms.int32(1)
            process.mix.digitizers.pixel.Pixel3DDigitizerAlgorithm.TofLowerCut = cms.double(-5.)
            process.mix.digitizers.pixel.Pixel3DDigitizerAlgorithm.TofUpperCut = cms.double(+20.)

    return process


# def _CustomizeForOTTrackerSignalShape(process):
#     ## for standard mixing
#     if hasattr(process,'mix') and hasattr(process.mix,'digitizers') and hasattr(process.mix.digitizers,'pixel'): 
#         if hasattr(process.mix.digitizers.pixel,'SSDigitizerAlgorithm'):
#             print("# Activating signal shape emulation in OT 2S modules)")
#             process.mix.digitizers.pixel.SSDigitizerAlgorithm.HitDetectionMode = cms.int32(1)

#     ## for pre-mixing
#     if hasattr(process, "mixData") and hasattr(process.mixData, "workers") and hasattr(process.mixData.workers, "pixel"):
#         if hasattr(process.mixData.workers.pixel,'SSDigitizerAlgorithm'):
#             print("# Activating signal shape emulation in OT 2S modules")
#             process.mixData.workers.pixel.SSDigitizerAlgorithm.HitDetectionMode = cms.int32(1)

#     return process



