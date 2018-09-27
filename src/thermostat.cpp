/**
 *
 *
 */

#ifndef _WIN32
#include <string.h>
#endif
#include "CommandLineOptions.h"
#include "Common.h"
#include "SignalHandler.h"
#include "SocketIOConnection.h"
#include "TemperatureSensorFactory.h"
#include <time.h>

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

float RoundToNearstHalf(float aNumber)
{
  return std::floor((aNumber * 2) + 0.5f) / 2;
}

int main(int argc, char * argv[])
{
  SignalHandler signalHandler;

  int ret = signalHandler.Init();

  if (ret != 0)
    return ret;

  CommandLineOptions commandLineOptions;

  ret = commandLineOptions.ParseCommandLine(argc, argv);

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
    socket.Emit(RoundToNearstHalf(aTemperature), commandLineOptions.GetRoomId());
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
    return 1;

  temperatureSensor->Init();

  while (!signalHandler.IsDone())
  {
    if (socket.ConnectionFailed() || socket.ConnectionClosed())
      return ECONNABORTED;

    temperatureSensor->Read();
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }

  printf("Done!\n");

  return 0;
}
