/**
 *
 */

#include "VirtualTemperatureSensor.h"

VirtualTemperatureSensor::VirtualTemperatureSensor(function<void(float)> aTempCallBack,
                                                   function<void(float)> aHumidityCallBack)
  : mTempCallBack(aTempCallBack)
  , mHumidityCallBack(aHumidityCallBack)
{
}

void VirtualTemperatureSensor::Init()
{
}

void VirtualTemperatureSensor::Read()
{
  if (mPos >= mTemperatures.size())
    mPos = 0;

  auto & currentTemperature = mTemperatures[mPos];

  if (fabs(currentTemperature.first - mTemperature) >= 0.1)
  {
    mTemperature = currentTemperature.first;
    mTempCallBack(mTemperature);
  }

  if (fabs(currentTemperature.second - mHumidity) >= 0.1)
  {
    mHumidity = currentTemperature.second;
    mHumidityCallBack(mHumidity);
  }

  mPos++;
}
