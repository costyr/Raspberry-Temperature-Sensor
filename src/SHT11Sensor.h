/**
 *  
 */

#ifndef _SHT11_SENSOR_H_
#define _SHT11_SENSOR_H_

#include "Common.h"
#include "TemperatureSensor.h"

class SHT11Sensor: public TemperatureSensor
{
public:
  SHT11Sensor(function<void(float)> aTempCallBack, 
              function<void(float)> aHumidityCallBack);

  //----------------------------------------------------------------------------
  // TemperatureSensor interface

  void Init() override;

  void Read() override;

private:
  float mTemperature{0};
  float mHumidity{0};

  function<void(float)> mTempCallBack;
  function<void(float)> mHumidityCallBack;
};

#endif // _SHT11_SENSOR_H_
