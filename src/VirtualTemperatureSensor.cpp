/**
 * 
 */

#include "VirtualTemperatureSensor.h"

VirtualTemperatureSensor::VirtualTemperatureSensor(function<void(float)> aTempCallBack,
                                                   function<void(float)> aHumidityCallBack)
: mTempCallBack(aTempCallBack),
  mHumidityCallBack(aHumidityCallBack)
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

  if (currentTemperature.first != mTemperature)
  {
    mTemperature = currentTemperature.first;
    mTempCallBack(mTemperature);
  }

  if (currentTemperature.second != mHumidity)
  {
    mHumidity = currentTemperature.second;
    mHumidityCallBack(mHumidity);
  }

  mPos++;
}
