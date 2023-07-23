#ifndef CondFormats_PTrackerAdditionalParametersPerDet_h
#define CondFormats_PTrackerAdditionalParametersPerDet_h

#include "CondFormats/Serialization/interface/Serializable.h"

#include <vector>
#include <string>

class PTrackerAdditionalParametersPerDet {
public:
  PTrackerAdditionalParametersPerDet() {
    intParams_.resize(ISIZE, std::vector<int>(0, 0));
    floatParams_.resize(FSIZE, std::vector<float>(0, 0.));
    boolParams_.resize(BSIZE, std::vector<bool>(0, false));
  };
  ~PTrackerAdditionalParametersPerDet(){};

  enum IntParamIndex { GEOGRAPHICAL_ID = 0, ISIZE = 1 };
  enum BoolParamIndex { BIGPIXELS_X = 0, BIGPIXELS_Y = 1, BSIZE = 2 };
  enum FloatParamIndex { FSIZE = 0 };

  int getGeographicalId(int theIndex) const;
  bool getBigPixelsX(int theIndex) const;
  bool getBigPixelsY(int theIndex) const ;
  std::vector<int> getAllGeographicalIds() const;
  std::vector<bool> getAllBigPixelsXs() const;
  std::vector<bool> getAllBigPixelsYs() const;


  void setGeographicalId(int geographicalId);
  void setBigPixelsX(bool bigPixelsX);
  void setBigPixelsY(bool bigPixelsY);

  std::vector<std::vector<int>> intParams_;
  std::vector<std::vector<bool>> boolParams_;
  std::vector<std::vector<float>> floatParams_;

  COND_SERIALIZABLE;
};

#endif
