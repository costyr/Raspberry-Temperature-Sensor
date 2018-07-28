/**
 *  
 */

#ifndef _SHT11_H_
#define _SHT11_H_

#include <functional>

class SHT11
{
public:
  SHT11(std::function<void(float)> aTempCallBack, std::function<void(float)> aHumidityCallBack);

  void Read();

private:
  float mTemperature{0};
  float mHumidity{0};

  std::function<void(float)> mTempCallBack;
  std::function<void(float)> mHumidityCallBack;
}

#endif // _SHT11_H_