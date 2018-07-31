/**
 *
 */

#ifndef _TEMPERATURE_SENSOR_H_
#define _TEMPERATURE_SENSOR_H_

class TemperatureSensor 
{
public:

  virtual ~TemperatureSensor() {};

  virtual void Init() = 0;

  virtual void Read() = 0;

};

#endif // _TEMPERATURE_SENSOR_H_
