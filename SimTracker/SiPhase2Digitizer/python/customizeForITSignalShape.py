import FWCore.ParameterSet.Config as cms

#
# activate signal shape in IT only
#

def _commonCustomizeSiPhase2ITSignalShape(process):
    ## for standard mixing
    if hasattr(process,'mix') and hasattr(process.mix,'digitizers') and hasattr(process.mix.digitizers,'pixel'): 
        if hasattr(process.mix.digitizers.pixel,'PixelDigitizerAlgorithm'):
            print("# Activating signal shape emulation in IT pixel (planar)")
            process.mix.digitizers.pixel.PixelDigitizerAlgorithm.ApplyTimewalk = cms.bool(True)

    ## for pre-mixing
    if hasattr(process, "mixData") and hasattr(process.mixData, "workers") and hasattr(process.mixData.workers, "pixel"):
        if hasattr(process.mixData.workers.pixel,'PixelDigitizerAlgorithm'):
            print("# Activating signal shape emulation in IT pixel (planar)")
            process.mixData.workers.pixel.PixelDigitizerAlgorithm.ApplyTimewalk = cms.bool(True)

    return process

def customizeSiPhase2ITSignalShape12p5ns(process):
    _commonCustomizeSiPhase2ITSignalShape(process)

    process.mix.minBunch = cms.int32(0)
    process.mix.maxBunch = cms.int32(0)

    return process

def customizeSiPhase2ITSignalShape37p5ns(process):
    _commonCustomizeSiPhase2ITSignalShape(process)

    process.mix.minBunch = cms.int32(-1)
    process.mix.maxBunch = cms.int32(1)

    return process

def customizeSiPhase2ITSignalShape87p5ns(process):
    _commonCustomizeSiPhase2ITSignalShape(process)

    process.mix.minBunch = cms.int32(-3)
    process.mix.maxBunch = cms.int32(1)

    return process

def customizeSiPhase2ITSignalShape137p5ns(process):
    _commonCustomizeSiPhase2ITSignalShape(process)

    process.mix.minBunch = cms.int32(-5)
    process.mix.maxBunch = cms.int32(1)

    return process


