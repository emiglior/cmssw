# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step2 --conditions auto:phase2_realistic -s DIGI:pdigi_valid,L1,L1TrackTrigger,DIGI2RAW,HLT:@fake2,RAW2DIGI,L1Reco,RECO --datatier GEN-SIM-RECO -n 10 --geometry Extended2023D21 --era Phase2 --eventcontent FEVTDEBUGHLT --filein file:SingleMuPt1000_pythia8_cfi_GEN_SIM.root --runUnscheduled --no_exec


# how-to run
# cmsRun phase2_digi_reco_pixelntuple_IT404_cfg.py firstFile=1 lastFile=10  geometry=IT404

import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras


#The line below always has to be included to make VarParsing work 
from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process('Phase2PixelNtuple',eras.Phase2)

# In the line below 'analysis' is an instance of VarParsing object 
options = VarParsing('analysis')

# Here we have defined our own two VarParsing options  (first/last file)
options.register('firstFile',
                 0,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.int,
                 "first file")
options.register ('lastFile',
                  1,
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.int,
                  "last file")
options.register ('geometry',
                  "IT4xx",
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.string,
                  "geometry")
options.register ('outdir',
                  ".",
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.string,
                  "output dir")

options.parseArguments()

print options.firstFile, options.lastFile, options.geometry

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
#process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('SimGeneral.MixingModule.mix_POISSON_average_cfi')
process.load('Configuration.Geometry.GeometryExtended2023D21Reco_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.L1TrackTrigger_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_Fake2_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# cff with the full list of input files
from SLHCUpgradeSimulations.Geometry.RelValTTbar_14TeV_2023D21PU200_cff import readFiles

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(readFiles[options.firstFile : options.lastFile+1])
)



process.options = cms.untracked.PSet(
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step2 nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# MC vertice analyzer
process.load("Validation.RecoVertex.mcverticesanalyzer_cfi")
process.mcverticesanalyzer.pileupSummaryCollection = cms.InputTag("addPileupInfo","","HLT")

# Output definition

#process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
#    dataset = cms.untracked.PSet(
#        dataTier = cms.untracked.string('GEN-SIM-RECO'),
#        filterName = cms.untracked.string('')
#    ),
#    fileName = cms.untracked.string('step2_DIGI_L1_L1TrackTrigger_DIGI2RAW_HLT_RAW2DIGI_L1Reco_RECO.root'),
#    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
#    splitLevel = cms.untracked.int32(0)
#)
process.ReadLocalMeasurement = cms.EDAnalyzer("Phase2PixelNtuple",
   trackProducer = cms.InputTag("generalTracks"),
   #verbose = cms.untracked.bool(True),
   #picky = cms.untracked.bool(False),                                             
   ### for using track hit association
   associatePixel = cms.bool(True),
   associateStrip = cms.bool(False),
   associateRecoTracks = cms.bool(False),
   ROUList = cms.vstring('TrackerHitsPixelBarrelLowTof',
                         'TrackerHitsPixelBarrelHighTof',
                         'TrackerHitsPixelEndcapLowTof',
                         'TrackerHitsPixelEndcapHighTof'),
   usePhase2Tracker = cms.bool(True),
   pixelSimLinkSrc = cms.InputTag("simSiPixelDigis", "Pixel"),
   phase2TrackerSimLinkSrc = cms.InputTag("simSiPixelDigis", "Tracker")
)


# Additional output definition

# Other statements
process.mix.input.nbPileupEvents.averageNumber = cms.double(200.000000)
process.mix.input.seed = cms.int32(options.firstFile)
process.mix.bunchspace = cms.int32(25)
process.mix.minBunch = cms.int32(-3)
process.mix.maxBunch = cms.int32(3)
# pile-up 100k events from  /RelValMinBias_14TeV/CMSSW_10_2_0_pre5-102X_upgrade2023_realistic_v1_2023D21noPU-v1/GEN-SIM
process.mix.input.fileNames = cms.untracked.vstring([
'/store/relval/CMSSW_10_2_0_pre5/RelValMinBias_14TeV/GEN-SIM/102X_upgrade2023_realistic_v1_2023D21noPU-v1/10000/0025ED4F-2E7B-E811-A291-0CC47A4D7650.root',
'/store/relval/CMSSW_10_2_0_pre5/RelValMinBias_14TeV/GEN-SIM/102X_upgrade2023_realistic_v1_2023D21noPU-v1/10000/24D1B6D0-137B-E811-97DF-0CC47A74524E.root',
'/store/relval/CMSSW_10_2_0_pre5/RelValMinBias_14TeV/GEN-SIM/102X_upgrade2023_realistic_v1_2023D21noPU-v1/10000/44D05202-187B-E811-9C05-0CC47A4D76B2.root',
'/store/relval/CMSSW_10_2_0_pre5/RelValMinBias_14TeV/GEN-SIM/102X_upgrade2023_realistic_v1_2023D21noPU-v1/10000/4C13E96E-1F7B-E811-8621-0025905A606A.root',
'/store/relval/CMSSW_10_2_0_pre5/RelValMinBias_14TeV/GEN-SIM/102X_upgrade2023_realistic_v1_2023D21noPU-v1/10000/5C59BB97-2D7B-E811-BAAF-0CC47A4D76D2.root',
'/store/relval/CMSSW_10_2_0_pre5/RelValMinBias_14TeV/GEN-SIM/102X_upgrade2023_realistic_v1_2023D21noPU-v1/10000/6012982C-227B-E811-9805-0CC47A78A3F4.root',
'/store/relval/CMSSW_10_2_0_pre5/RelValMinBias_14TeV/GEN-SIM/102X_upgrade2023_realistic_v1_2023D21noPU-v1/10000/8053C846-2B7B-E811-AAB9-0025905A48C0.root',
'/store/relval/CMSSW_10_2_0_pre5/RelValMinBias_14TeV/GEN-SIM/102X_upgrade2023_realistic_v1_2023D21noPU-v1/10000/82E89188-107B-E811-A890-0CC47A4C8F2C.root',
'/store/relval/CMSSW_10_2_0_pre5/RelValMinBias_14TeV/GEN-SIM/102X_upgrade2023_realistic_v1_2023D21noPU-v1/10000/9AD90AF7-247B-E811-B9B3-0025905AA9F0.root',
'/store/relval/CMSSW_10_2_0_pre5/RelValMinBias_14TeV/GEN-SIM/102X_upgrade2023_realistic_v1_2023D21noPU-v1/10000/A8241AAF-277B-E811-B4C4-0CC47A4D7674.root',
'/store/relval/CMSSW_10_2_0_pre5/RelValMinBias_14TeV/GEN-SIM/102X_upgrade2023_realistic_v1_2023D21noPU-v1/10000/C87DBC82-297B-E811-A315-0025905B855C.root',
'/store/relval/CMSSW_10_2_0_pre5/RelValMinBias_14TeV/GEN-SIM/102X_upgrade2023_realistic_v1_2023D21noPU-v1/10000/DEE5E128-1C7B-E811-8A3C-0CC47A4D76D6.root'
])

process.mix.digitizers = cms.PSet(process.theDigitizersValid)
# This pset is specific for producing simulated events for the designers of the PROC (InnerTracker)
# They need pixel RecHits where the charge is stored with high-granularity and large dinamic range
process.mix.digitizers.pixel.PixelDigitizerAlgorithm.AdcFullScale   = cms.int32(255)
process.mix.digitizers.pixel.PixelDigitizerAlgorithm.ElectronPerAdc = cms.double(135.)
process.siPixelClusters.ElectronPerADCGain=cms.double(135.)
process.siPixelClustersPreSplitting.ElectronPerADCGain=cms.double(135.)

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase2_realistic', '')

# Path and EndPath definitions
process.digitisation_step = cms.Path(process.pdigi_valid)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.L1TrackTrigger_step = cms.Path(process.L1TrackTrigger)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.user_step = cms.Path(process.ReadLocalMeasurement + process.mcverticesanalyzer)
process.endjob_step = cms.EndPath(process.endOfProcess)
#process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

# Schedule definidtion
process.schedule = cms.Schedule(process.digitisation_step,process.L1simulation_step,process.L1TrackTrigger_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.user_step,process.endjob_step])
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

# customisation of the process.

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)

# End of customisation functions
#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)


# Customisation from command line

#Have logErrorHarvester wait for the same EDProducers to finish as those providing data for the OutputModule
from FWCore.Modules.logErrorHarvester_cff import customiseLogErrorHarvesterUsingOutputCommands
process = customiseLogErrorHarvesterUsingOutputCommands(process)

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)

# End adding early deletion
process.TFileService = cms.Service('TFileService',
                                   fileName = cms.string(options.outdir+"/pixelntuple"+options.geometry+"."+str(options.firstFile)+"_"+str(options.lastFile)+".root")
)

