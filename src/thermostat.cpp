/**
 *
 *
 */

#ifndef _WIN32
#include <bcm2835.h>
#include <string.h>
#endif
#include "CommandLineOptions.h"
#include "Common.h"
#include "SocketIOConnection.h"
#include "TemperatureSensorFactory.h"
#include <signal.h>

volatile sig_atomic_t done = 0;

void term(int signum)
{
  done = 1;
}

int main(int argc, char * argv[])
{
#ifdef _WIN32
  signal(SIGTERM, term);
  signal(SIGINT, term);
#else

  // Initialize the Raspberry Pi GPIO
  if (!bcm2835_init())
    return 1;

  struct sigaction action;
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_handler = term;
  sigaction(SIGTERM, &action, NULL);
  sigaction(SIGINT, &action, NULL);
#endif

  CommandLineOptions commandLineOptions;

  int ret = commandLineOptions.ParseCommandLine(argc, argv);

  if (ret != 0)
  {
    printf("Invalid command line!\n");
    return ret;
  }

  if (!commandLineOptions.HasExpectedOptions())
  {
    printf("Invalid command line!\n");
    return EINVAL;
  }

  SocketIOConnection socket(commandLineOptions.GetServerToken());

  auto serverUrl = commandLineOptions.GetServerURL();
  socket.Connect(serverUrl);

  std::function<void(float)> printTemperature = [&socket, &commandLineOptions](float aTemperature) {
    // Print the Temperature to the console
    printf("Temperature: %0.1f\n", aTemperature);
    socket.Emit(aTemperature, commandLineOptions.GetRoomId());
  };

  std::function<void(float)> printHumidity = [](float aHumidity) {
    // Print the Humidity to the console
    printf("Humidity: %0.1f%%\n", aHumidity);
  };

  TemperatureSensorFactory temperatureSensorFactory;

  std::unique_ptr<TemperatureSensor> temperatureSensor =
    temperatureSensorFactory.CreateTemperatureSensor(printTemperature, printHumidity);

  if (!temperatureSensor)
    return -1;

  temperatureSensor->Init();

  while (!done && !socket.ConnectionFailed())
  {
    temperatureSensor->Read();
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }

  printf("Done!\n");
}
