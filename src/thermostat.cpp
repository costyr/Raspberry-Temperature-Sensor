/**
 * 
 * 
 */

#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <bcm2835.h>
#include "SHT11Sensor.h"

volatile sig_atomic_t done = 0;
 
void term(int signum)
{ 
  done = 1;
}

int main() 
{
  struct sigaction action;
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_handler = term;
  sigaction(SIGTERM, &action, NULL);
  sigaction(SIGINT, &action, NULL);

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

  while (!done) 
  {
    sht11.Read();
    sleep(5);
  }

  printf("Done!");
}
