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
#include <time.h>

volatile sig_atomic_t done = 0;

void term(int signum)
{
  done = 1;
}

string GetNowDate()
{
  std::time_t now = std::time(nullptr);
  tm          timeBuffer;
#ifdef _WIN32
  localtime_s(&timeBuffer, &now);
#else
  localtime_r(&now, &timeBuffer);
#endif
  string buffer;
  buffer.resize(100);
  // asctime_s(&buffer[0], buffer.size(), &timeBuffer);
  strftime(&buffer[0], buffer.size(), "%A %c", &timeBuffer);
  return buffer;
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
    if (commandLineOptions.LogSensorData())
    {
      printf("Temperature: %0.1f\n", aTemperature);
      fflush(stdout);
    }
    socket.Emit(aTemperature, commandLineOptions.GetRoomId());
  };

  std::function<void(float)> printHumidity = [&socket, &commandLineOptions](float aHumidity) {
    // Print the Humidity to the console
    if (!commandLineOptions.ScanHumidity())
      return;

    if (commandLineOptions.LogSensorData())
    {
      printf("Humidity: %0.1f%%\n", aHumidity);
      fflush(stdout);
    }
    socket.Emit(aHumidity, commandLineOptions.GetRoomId());
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

#ifdef _WIN32
  signal(SIGTERM, SIG_DFL);
  signal(SIGINT, SIG_DFL);
#else
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_handler = SIG_DFL;
  sigaction(SIGTERM, &action, NULL);
  sigaction(SIGINT, &action, NULL);
#endif

  return 0;
}
