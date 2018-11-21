import FWCore.ParameterSet.Config as cms

# customize the CPE errors
# Pixel CPE for default pixel cell (all modules: 100x150 um2)
pixelCPE_100x150_default = cms.PSet(
    xerr_barrel_small_     = cms.untracked.vdouble(0.00115, 0.00120, 0.00088),
    xerr_barrel_large_     = cms.untracked.vdouble(0.00115, 0.00120, 0.00088),
    xerr_barrel_small_def_ = cms.untracked.double(0.01030),
    xerr_barrel_large_def_ = cms.untracked.double(0.01030),
    yerr_barrel_small_     = cms.untracked.vdouble(0.00375,0.00230,0.00250,0.00250,0.00230,0.00230,0.00210,0.00210,0.00240),
    yerr_barrel_large_     = cms.untracked.vdouble(0.00375,0.00230,0.00250,0.00250,0.00230,0.00230,0.00210,0.00210,0.00240),
    yerr_barrel_small_def_ = cms.untracked.double(0.00210),
    yerr_barrel_large_def_ = cms.untracked.double(0.00210),
    xerr_endcap_small_     = cms.untracked.vdouble(0.0020, 0.0020),
    xerr_endcap_large_     = cms.untracked.vdouble(0.0020, 0.0020),
    xerr_endcap_small_def_ = cms.untracked.double(0.0020),
    xerr_endcap_large_def_ = cms.untracked.double(0.0020),
    yerr_endcap_small_     = cms.untracked.vdouble(0.00210),
    yerr_endcap_large_     = cms.untracked.vdouble(0.00210),
    yerr_endcap_small_def_ = cms.untracked.double(0.00075),
    yerr_endcap_large_def_ = cms.untracked.double(0.00075)
    )

# Pixel CPE for phase2 pixel cell (modules 1x2: 25x100 um2; modules 2x2: 25x100 um2) 
pixelCPE_25x100_phase2 = cms.PSet(
    xerr_barrel_small_     = cms.untracked.vdouble(0.00025, 0.00030, 0.00035, 0.00035),
    xerr_barrel_large_     = cms.untracked.vdouble(0.00025, 0.00030, 0.00035, 0.00035),
    xerr_barrel_small_def_ = cms.untracked.double(0.00035),
    xerr_barrel_large_def_ = cms.untracked.double(0.00035),
    yerr_barrel_small_     = cms.untracked.vdouble(0.00210, 0.00115, 0.00125),
    yerr_barrel_large_     = cms.untracked.vdouble(0.00210, 0.00115, 0.00125),
    yerr_barrel_small_def_ = cms.untracked.double(0.00125),
    yerr_barrel_large_def_ = cms.untracked.double(0.00125),
    xerr_endcap_small_     = cms.untracked.vdouble(0.00072, 0.00025),
    xerr_endcap_large_     = cms.untracked.vdouble(0.00072, 0.00025),
    xerr_endcap_small_def_ = cms.untracked.double(0.00060),
    xerr_endcap_large_def_ = cms.untracked.double(0.00060),
    yerr_endcap_small_     = cms.untracked.vdouble(0.00289, 0.00025),
    yerr_endcap_large_     = cms.untracked.vdouble(0.00289, 0.00025),
    yerr_endcap_small_def_ = cms.untracked.double(0.00180),
    yerr_endcap_large_def_ = cms.untracked.double(0.00180)
    )

# Pixel CPE for phase2 pixel cell (modules 1x2: 50x50 um2; modules 2x2: 50x50 um2) 
pixelCPE_50x50_phase2 = cms.PSet(
    xerr_barrel_small_     = cms.untracked.vdouble(0.00060, 0.00045, 0.00075),
    xerr_barrel_large_     = cms.untracked.vdouble(0.00060, 0.00045, 0.00075),
    xerr_barrel_small_def_ = cms.untracked.double(0.00150),
    xerr_barrel_large_def_ = cms.untracked.double(0.00150),
    yerr_barrel_small_     = cms.untracked.vdouble(0.00100, 0.00045, 0.00075, 0.00075, 0.00080, 0.00080, 0.00080),
    yerr_barrel_large_     = cms.untracked.vdouble(0.00100, 0.00045, 0.00075, 0.00075, 0.00080, 0.00080, 0.00080),
    yerr_barrel_small_def_ = cms.untracked.double(0.00090),
    yerr_barrel_large_def_ = cms.untracked.double(0.00090),
    xerr_endcap_small_     = cms.untracked.vdouble(0.00145, 0.00025),
    xerr_endcap_large_     = cms.untracked.vdouble(0.00145, 0.00025),
    xerr_endcap_small_def_ = cms.untracked.double(0.00085),
    xerr_endcap_large_def_ = cms.untracked.double(0.00085),
    yerr_endcap_small_     = cms.untracked.vdouble(0.00145, 0.00020),
    yerr_endcap_large_     = cms.untracked.vdouble(0.00145, 0.00020),
    yerr_endcap_small_def_ = cms.untracked.double(0.00080),
    yerr_endcap_large_def_ = cms.untracked.double(0.00080)
    )

PixelCPE_dict = { 'pixelCPE_100x150_default' : pixelCPE_100x150_default,
                  'pixelCPE_25x100_phase2'   : pixelCPE_25x100_phase2, 
                  'pixelCPE_50x50_phase2'    : pixelCPE_50x50_phase2 
                  }

PixelCPEGenericESProducer = cms.ESProducer("PixelCPEGenericESProducer",

    ComponentName = cms.string('PixelCPEGeneric'),
    Alpha2Order = cms.bool(True),
    PixelErrorParametrization = cms.string('NOTcmsim'),

    # Allows cuts to be optimized
    eff_charge_cut_lowX = cms.double(0.0),
    eff_charge_cut_lowY = cms.double(0.0),
    eff_charge_cut_highX = cms.double(1.0),
    eff_charge_cut_highY = cms.double(1.0),
    size_cutX = cms.double(3.0),
    size_cutY = cms.double(3.0),

    # Edge cluster errors in microns (determined by looking at residual RMS) 
    EdgeClusterErrorX = cms.double( 50.0 ),                                      
    EdgeClusterErrorY = cms.double( 85.0 ),                                                     

    # ggiurgiu@jhu.edu
    inflate_errors = cms.bool(False),
    inflate_all_errors_no_trk_angle = cms.bool(False),

    # Can use errors predicted by the template code
    # If UseErrorsFromTemplates is False, must also set
    # TruncatePixelCharge, IrradiationBiasCorrection, DoCosmics and LoadTemplatesFromDB to be False                                        
    UseErrorsFromTemplates = cms.bool(True),

    # When set True this gives a slight improvement in resolution at no cost 
    TruncatePixelCharge = cms.bool(True),

    # Turn this ON later
    IrradiationBiasCorrection = cms.bool(False),                                       

    # When set to True we use templates with extended angular acceptance   
    DoCosmics = cms.bool(False),                                      

    LoadTemplatesFromDB = cms.bool(True),                                       

    # petar, for clusterProbability() from TTRHs
    ClusterProbComputationFlag = cms.int32(0),

    # new parameters added in 1/14, dk
    # LA defined by hand, FOR TESTING ONLY, not for production   
    # 0.0 means that the offset is taken from DB        
    #lAOffset = cms..double(0.0),
    #lAWidthBPix = cms.double(0.0),
    #lAWidthFPix = cms.double(0.0),

    # Flag to select the source of LA-Width
    # Normal = True, use LA from DB
    useLAWidthFromDB = cms.bool(True),                             
    # if lAWith=0 and useLAWidthFromDB=false than width is calculated from lAOffset.         
    # Use the LA-Offsets from Alignment instead of our calibration
    useLAAlignmentOffsets = cms.bool(False),                             
                                           
    #MagneticFieldRecord: e.g. "" or "ParabolicMF"
    MagneticFieldRecord = cms.ESInputTag(""),

    # 
    PixelCPEList = PixelCPE_dict['pixelCPE_100x150_default']
)


# This customization will be removed once we get the templates for phase2 pixel
# FIXME::Is the Upgrade variable actually used?
from Configuration.Eras.Modifier_phase2_tracker_cff import phase2_tracker
phase2_tracker.toModify(PixelCPEGenericESProducer, 
  useLAWidthFromDB = False,
  UseErrorsFromTemplates = False,
  LoadTemplatesFromDB = False,
  TruncatePixelCharge = False,
  IrradiationBiasCorrection = False,
  DoCosmics = False,
  Upgrade = cms.bool(True),
  PixelCPEList = PixelCPE_dict['pixelCPE_50x50_phase2']
)

