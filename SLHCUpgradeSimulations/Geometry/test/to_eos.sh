#!/bin/sh 
#BSUB -L /bin/sh 
#BSUB -q cmscaf1nw 
#BSUB -oo /afs/cern.ch/user/e/emiglior/scratch0/log/to_eos.log

# remote file access 
export X509_USER_PROXY=/afs/cern.ch/user/e/emiglior/x509up_u5686 

export REMOTEDIR=$PWD 
echo REMOTEDIR is $REMOTEDIR 

# # IT404
# hadd -f ${REMOTEDIR}/pixelntupleIT404.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT404.0_9.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT404.10_19.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT404.20_29.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT404.30_39.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT404.40_49.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT404.50_59.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT404.60_69.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT404.70_79.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT404.80_89.root

# xrdcp -f ${REMOTEDIR}/pixelntupleIT404.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT404.root

# ls -l ${REMOTEDIR}

# rm ${REMOTEDIR}/pixelntupleIT404.root

# #  IT420 
# hadd -f ${REMOTEDIR}/pixelntupleIT420.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT420.0_9.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT420.10_19.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT420.20_29.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT420.30_39.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT420.40_49.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT420.50_59.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT420.60_69.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT420.70_79.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT420.80_89.root

# xrdcp -f ${REMOTEDIR}/pixelntupleIT420.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT420.root

# ls -l ${REMOTEDIR}

# rm ${REMOTEDIR}/pixelntupleIT420.root

# # IT421
# hadd -f ${REMOTEDIR}/pixelntupleIT421.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT421.0_9.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT421.10_19.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT421.20_29.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT421.30_39.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT421.40_49.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT421.50_59.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT421.60_69.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT421.70_79.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT421.80_89.root

# xrdcp -f ${REMOTEDIR}/pixelntupleIT421.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT421.root

# ls -l ${REMOTEDIR}

# rm ${REMOTEDIR}/pixelntupleIT421.root


# IT405
hadd -f ${REMOTEDIR}/pixelntupleIT405.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT405.0_9.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT405.10_19.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT405.20_29.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT405.30_39.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT405.40_49.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT405.50_59.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT405.60_69.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT405.70_79.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT405.80_89.root

xrdcp -f ${REMOTEDIR}/pixelntupleIT405.root root://eoscms.cern.ch//eos/cms/store/group/upgrade/Tracker/simulation/PhaseII/InnerTracker/CMSSW_10_2_0_pre6/TTbar_14TeV/PU200/pixelntupleIT405.root

ls -l ${REMOTEDIR}

rm ${REMOTEDIR}/pixelntupleIT405.root
