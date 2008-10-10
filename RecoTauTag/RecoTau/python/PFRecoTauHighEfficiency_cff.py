import FWCore.ParameterSet.Config as cms
import copy

from RecoTauTag.RecoTau.PFRecoTauTagInfoProducer_cfi import *
from RecoTauTag.RecoTau.PFRecoTauProducer_cfi import *
from RecoTauTag.RecoTau.PFRecoTauDiscriminationByIsolation_cfi import *
from RecoTauTag.RecoTau.PFRecoTauDiscriminationByLeadingTrackFinding_cfi import *
from RecoTauTag.RecoTau.PFRecoTauDiscriminationByLeadingTrackPtCut_cfi import *
from RecoTauTag.RecoTau.PFRecoTauDiscriminationAgainstElectron_cfi import *
from RecoTauTag.RecoTau.PFRecoTauDiscriminationAgainstMuon_cfi import *

#copying the PFTau producer and select the shrinkingCone
pfRecoTauProducerHighEfficiency = copy.deepcopy(pfRecoTauProducer)
pfRecoTauProducerHighEfficiency.TrackerSignalConeSizeFormula = '5.0/ET'
pfRecoTauProducerHighEfficiency.TrackerSignalConeSize_min = 0.07
pfRecoTauProducerHighEfficiency.TrackerSignalConeSize_max = 0.15
pfRecoTauProducerHighEfficiency.GammaCand_minPt = 1.5


#copying Discriminator ByLeadingTrack(finding and pt_cut)
pfRecoTauDiscriminationByLeadingTrackFindingHighEfficiency = copy.deepcopy(pfRecoTauDiscriminationByLeadingTrackFinding)
pfRecoTauDiscriminationByLeadingTrackFindingHighEfficiency.PFTauProducer = 'pfRecoTauProducerHighEfficiency'

pfRecoTauDiscriminationByLeadingTrackPtCutHighEfficiency = copy.deepcopy(pfRecoTauDiscriminationByLeadingTrackPtCut)
pfRecoTauDiscriminationByLeadingTrackPtCutHighEfficiency.PFTauProducer = 'pfRecoTauProducerHighEfficiency'

#copying the Discriminator by Isolation
pfRecoTauDiscriminationHighEfficiency = copy.deepcopy(pfRecoTauDiscriminationByIsolation)
pfRecoTauDiscriminationHighEfficiency.PFTauProducer = 'pfRecoTauProducerHighEfficiency'

#copying discriminator against electrons and muons
pfRecoTauDiscriminationAgainstElectronHighEfficiency = copy.deepcopy(pfRecoTauDiscriminationAgainstElectron)
pfRecoTauDiscriminationAgainstElectronHighEfficiency.PFTauProducer = 'pfRecoTauProducerHighEfficiency'

pfRecoTauDiscriminationAgainstMuonHighEfficiency = copy.deepcopy(pfRecoTauDiscriminationAgainstMuon)
pfRecoTauDiscriminationAgainstMuonHighEfficiency.PFTauProducer = 'pfRecoTauProducerHighEfficiency'


