/**
 * 
 * 
 */

#include "CommandLineOptions.h"

CommandLineOptions::CommandLineOptions()
{
    kOptionHandlers =
    {
        { "server_url", [this](int &aPos, int argc, char *argv[]) 
          { 
            if (aPos < argc) 
              return 1; 
            mServerURL = argv[aPos]; 
            aPos++; 
            return 0; 
          }
        },
        { "server_token", [this](int &aPos, int argc, char *argv[]) 
          {   
            if (aPos < argc) 
              return 1; 
            mServerToken = argv[aPos]; 
            aPos++; 
            return 0; 
          }
        }
    }
}

int CommandLineOptions::ParseCommandLine(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
    {
      string commandLineOption(argv[i]);

      auto it = std::find(kOptionHandlers.begin(), kOptionHandlers.end(), commandLineOption);

      if (it != kOptionHandlers.end()) 
      {
        if (it->second(i, argc, argv) != 0)
          return -1;
      }
    }

    return 0;
}

const string &CommandLineOptions::GetServerURL() const
{
    return mServerURL;
}

const string &CommandLineOptions::GetServerToken() const
{
    return mServerToken;
}

//----------------------------------------------------------------
