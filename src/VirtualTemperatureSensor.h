/**
 *
 */

#ifndef _VIRTUAL_TEMPERATURE_SENSOR_H_
#define _VIRTUAL_TEMPERATURE_SENSOR_H_

#include "Common.h"
#include "TemperatureSensor.h"

class VirtualTemperatureSensor : public TemperatureSensor
{
public:
  VirtualTemperatureSensor(function<void(float)> aTempCallBack,
                           function<void(float)> aHumidityCallBack);

  //----------------------------------------------------------------------------
  // TemperatureSensor interface

  void Init() override;

  void Read() override;

private:
  size_t mPos = 0;

  vector<pair<float, float>> mTemperatures = { { 28.74F, 60.0F }, { 28.75F, 60.0F },
                                               { 28.76F, 60.0F }, { 28.78F, 60.0F },
                                               { 28.79F, 60.0F }, { 27.0F, 61.1F },
                                               { 28.3F, 59.0F },  { 26.9F, 58.2F } };

  float mTemperature{ 0 };
  float mHumidity{ 0 };

  function<void(float)> mTempCallBack;
  function<void(float)> mHumidityCallBack;
};

#endif  // _VIRTUAL_TEMPERATURE_SENSOR_H_
