# Auto generated configuration file
# using: 
# Revision: 1.20 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: TTbar_cfi --conditions auto:upgradePLS3 -n 2 --eventcontent FEVTDEBUG -s GEN,SIM --datatier GEN-SIM --beamspot HLLHC --customise SLHCUpgradeSimulations/Configuration/combinedCustoms.cust_2023Muon --geometry Extended2023Muon,Extended2023MuonReco --magField 38T_PostLS1 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('ANA')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometryExtended2023tiltedReco_cff')
process.load('Configuration.Geometry.GeometryExtended2023tilted_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic50ns13TeVCollision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.trackerGeometry.applyAlignment = cms.bool(False)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source ("PoolSource",
    fileNames = cms.untracked.vstring ([
        "file:/afs/cern.ch/work/e/emiglior/public/TMP/ToGIT/Test810_largeStat/step2_2023tilted.root"
    ])
)

process.options = cms.untracked.PSet(

)

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

process.TFileService = cms.Service ("TFileService",
    fileName = cms.string ("histDigiTilted.root")
)

process.pixelDigiAnalyzer = cms.EDAnalyzer ("PixelDigiAnalyzer",
    pixelDigis          =  cms.InputTag  ("simSiPixelDigis",  "Pixel"),
    phase2TrackerDigis  =  cms.InputTag  ("mix",  "Tracker")
)

process.myPath = cms.Path (process.pixelDigiAnalyzer)
