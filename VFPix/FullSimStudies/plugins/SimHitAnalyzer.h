#ifndef SIM_HIT_ANALYZER
#define SIM_HIT_ANALYZER

#include <unordered_map>
#include <string>

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TH2F.h"

using namespace std;

typedef TH2F* TH2Fptr;

class SimHitAnalyzer : public edm::EDAnalyzer
{
  public:
    SimHitAnalyzer (const edm::ParameterSet &);
    ~SimHitAnalyzer ();

    void analyze (const edm::Event &, const edm::EventSetup &);

  private:
    edm::Service<TFileService> fs_;
    unordered_map<string, TH1D *> oneDHists_;
    unordered_map<string, TH2D *> twoDHists_;

    edm::InputTag simHitsBarrelHighTof_src_;
    edm::InputTag simHitsBarrelLowTof_src_;
    edm::InputTag simHitsEndcapHighTof_src_;
    edm::InputTag simHitsEndcapLowTof_src_;

    edm::EDGetTokenT<vector<PSimHit> > simHitsBarrelHighTofToken_;
    edm::EDGetTokenT<vector<PSimHit> > simHitsBarrelLowTofToken_;
    edm::EDGetTokenT<vector<PSimHit> > simHitsEndcapHighTofToken_;
    edm::EDGetTokenT<vector<PSimHit> > simHitsEndcapLowTofToken_;

    TFileDirectory BPIXdir_;
    TFileDirectory FPIXnegdir_;
    TFileDirectory FPIXposdir_;

    const int MAX_BPIX=4;
    const int MAX_FPIX=10;
    TH2Fptr * h2_yxHitMap_BPIX_;
    TH2Fptr * h2_yxHitMap_FPIXneg_;
    TH2Fptr * h2_yxHitMap_FPIXpos_;

};
#endif
