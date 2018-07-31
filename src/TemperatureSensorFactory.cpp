/**
 *
 */

#include "TemperatureSensorFactory.h"
#ifdef _WIN32
#include "VirtualTemperatureSensor.h"
#else 
#include "SHT11Sensor.h"
#endif

TemperatureSensorFactory::TemperatureSensorFactory() 
{
}

unique_ptr<TemperatureSensor> TemperatureSensorFactory::CreateTemperatureSensor(
  function<void(float)> aTempCallBack,
  function<void(float)> aHumidityCallBack)
{
#ifdef _WIN32
  return make_unique<VirtualTemperatureSensor>(aTempCallBack, aHumidityCallBack);
#else
  return make_unique<SHT11Sensor>(aTempCallBack, aHumidityCallBack);
#endif
}
