/**
 * 
 * 
 */

#include "SHT11.h"

int main() 
{
  std::function<void(float)> printTemperature = [](float aTemperature) 
  {
    //Print the Temperature to the console
    printf("Temperature: %0.1f\n", aTemperature); 
  };

  std::function<void(float)> printHumidity = [](float aHumidity) 
  {
    //Print the Humidity to the console
    printf("Humidity: %0.1f%%\n", aHumidity);
  }

  SHT11 sht11(printTemperature, printHumidity);
  stt11.Read();
}
