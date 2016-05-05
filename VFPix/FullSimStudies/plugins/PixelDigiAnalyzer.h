#ifndef PIXEL_DIGI_ANALYZER
#define PIXEL_DIGI_ANALYZER

#include <string>

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Common/interface/DetSetVector.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "TH1F.h"
#include "TH2F.h"

using namespace std;

class PixelDigi;
class Phase2TrackerDigi;

typedef TH1F* TH1Fptr;
typedef TH2F* TH2Fptr;

class PixelDigiAnalyzer : public edm::EDAnalyzer
{
  public:
    PixelDigiAnalyzer (const edm::ParameterSet &);
    ~PixelDigiAnalyzer ();

    void analyze (const edm::Event &, const edm::EventSetup &);

  private:
    edm::Service<TFileService> fs_;

    edm::InputTag simSiPixelDigis_src_;
    edm::EDGetTokenT<edm::DetSetVector<PixelDigi> > pixelDigiToken_;

    edm::InputTag simPhase2TrackerDigis_src_;
    edm::EDGetTokenT<edm::DetSetVector<Phase2TrackerDigi> > phase2TrackerDigiToken_;

    TFileDirectory BPIXdir_;     // InnerPixel barrel
    TFileDirectory OTPIXdir_;    // OutreTracker pixel (PS)
    TFileDirectory FPIXnegdir_;  // InnerPixel forward z-
    TFileDirectory FPIXposdir_;  // InnerPixel forward z+

    const int MAX_BPIX=4;
    const int MAX_OTPIX=3;
    const int MAX_FPIX=10;

    TH2Fptr * h2_colrowHitMap_BPIX_;
    TH2Fptr * h2_colrowHitMap_OTPIX_;
    TH2Fptr * h2_colrowHitMap_FPIXneg_;
    TH2Fptr * h2_colrowHitMap_FPIXpos_;

    TH1Fptr * h1_adc_BPIX_;
    TH1Fptr * h1_adc_OTPIX_;
    TH1Fptr * h1_adc_FPIXneg_;
    TH1Fptr * h1_adc_FPIXpos_;

};
#endif
