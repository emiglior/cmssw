import ROOT
import math
from os import path, system
#from subprocess import call


EOS_PATH='root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200'

list_of_rootfilenames = [
   'pixelntupleIT404.root', 'pixelntupleIT420.root', 'pixelntupleIT421.root'
#  'pixelntupleIT404.0_9.root',
#  'pixelntupleIT404.10_19.root',
#  'pixelntupleIT404.20_29.root',
#  'pixelntupleIT404.30_39.root',
#  'pixelntupleIT404.40_49.root',
#  'pixelntupleIT404.50_59.root',
#  'pixelntupleIT404.60_69.root',
#  'pixelntupleIT404.70_79.root',
#  'pixelntupleIT404.80_89.root'
    # 'pixelntupleIT4025.0_1.root',
    # 'pixelntupleIT4025.2_3.root',
    # 'pixelntupleIT4025.4_5.root',
    # 'pixelntupleIT4025.6_7.root',
    # 'pixelntupleIT4025.8_9.root',
    # 'pixelntupleIT4025.10_11.root',
    # 'pixelntupleIT4025.14_15.root',
    # 'pixelntupleIT4025.16_17.root',
    # 'pixelntupleIT4025.18_19.root',
    # 'pixelntupleIT4025.22_23.root',
    # 'pixelntupleIT4025.24_25.root',
    # 'pixelntupleIT4025.26_27.root',
    # 'pixelntupleIT4025.28_29.root',
    # 'pixelntupleIT4025.30_31.root',
    # 'pixelntupleIT4025.32_33.root',
    # 'pixelntupleIT4025.34_35.root',
    # 'pixelntupleIT4025.36_37.root',
    # 'pixelntupleIT4025.38_39.root'
    ]

list_of_rootfile_to_add = []

the_hadd_command = 'hadd -f /tmp/emiglior/pixelntupleIT404.root '

for root_filename in list_of_rootfilenames:
    root_file = ROOT.TFile(path.join(EOS_PATH,root_filename))
    h1_nvtx = root_file.Get('mcverticesanalyzer/nvtx')
    tree    = root_file.Get('ReadLocalMeasurement/PixelNtuple')
    print 'Inspecting file:', root_filename 
    print 'nvtx: entries {}, mean {:5.1f}'.format(h1_nvtx.GetEntries(), h1_nvtx.GetMean())                          
    print 'TTree: entries {}'.format(tree.GetEntries())
    ratio = tree.GetEntries()/h1_nvtx.GetEntries()
    err_ratio = ratio * math.sqrt( 1./tree.GetEntries() + 1./h1_nvtx.GetEntries() )
    print 'TTree/nvtx {:.3g} +- {:.3g} \n'.format(ratio, err_ratio)
    root_file.Close()    
    the_hadd_command = the_hadd_command + ' ' + path.join(EOS_PATH,root_filename)

print the_hadd_command
#call(the_hadd_command)
