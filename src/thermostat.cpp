/**
 * 
 * 
 */

#include <bcm2835.h>
#include "SHT11Sensor.h"

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
  };

  //Initialise the Raspberry Pi GPIO
  if(!bcm2835_init())
	  return 1;

  SHT11Sensor sht11(printTemperature, printHumidity);
  sht11.Init();
  sht11.Read();
}
