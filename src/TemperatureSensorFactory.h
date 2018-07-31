/**
 *
 */

#ifndef _TEMPERATURE_SENSOR_FACTORY_H_
#define _TEMPERATURE_SENSOR_FACTORY_H_

#include "Common.h"
#include "TemperatureSensor.h"

class TemperatureSensorFactory 
{
public:
  TemperatureSensorFactory();

  unique_ptr<TemperatureSensor> CreateTemperatureSensor(
    function<void(float)> aTempCallBack,
    function<void(float)> aHumidityCallBack);
};

#endif // _TEMPERATURE_SENSOR_FACTORY_H_
