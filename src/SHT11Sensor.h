/**
 *  
 */

#ifndef _SHT11_SENSOR_H_
#define _SHT11_SENSOR_H_

#include <functional>

class SHT11Sensor
{
public:
  SHT11Sensor(std::function<void(float)> aTempCallBack, std::function<void(float)> aHumidityCallBack);

  void Init();

  void Read();

private:
  float mTemperature{0};
  float mHumidity{0};

  std::function<void(float)> mTempCallBack;
  std::function<void(float)> mHumidityCallBack;
}

#endif // _SHT11_SENSOR_H_