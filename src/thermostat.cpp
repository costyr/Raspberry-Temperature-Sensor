/**
 * 
 * 
 */

#ifndef _WIN32
#include <bcm2835.h>
#endif
#include "Common.h"
#include <signal.h>
#include "TemperatureSensorFactory.h"

volatile sig_atomic_t done = 0;
 
void term(int signum)
{ 
  done = 1;
}

int main() 
{
#ifdef _WIN32
  signal(SIGTERM, term);
  signal(SIGINT, term);
#else

  //Initialize the Raspberry Pi GPIO
  if (!bcm2835_init())
    return 1;

  struct sigaction action;
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_handler = term;
  sigaction(SIGTERM, &action, NULL);
  sigaction(SIGINT, &action, NULL);
#endif

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

  TemperatureSensorFactory temperatureSensorFactory;

  std::unique_ptr<TemperatureSensor> temperatureSensor = 
    temperatureSensorFactory.CreateTemperatureSensor(printTemperature, printHumidity);

  if (!temperatureSensor)
    return -1;

  temperatureSensor->Init();

  while (!done) 
  {
    temperatureSensor->Read();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  printf("Done!\n");
}
