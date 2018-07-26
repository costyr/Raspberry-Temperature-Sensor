/**
 *  
 */

#ifndef _SHT11_H_
#define _SHT11_H_

class SHT11
{
  public:
    SHT11(std::function<void(float)> aTempCallBack, std::function<float> aHumidityCallBack);
    
    void Read();
  
  private:
    float mTemperature { 0 };
    float mHumidity { 0 };

    std::function<void(int)> mTempCallBack;
    std::function<int> mHumidityCallBack;
}

#endif // _SHT11_H_