/**
 *
 *
 */

#include "CommandLineOptions.h"

CommandLineOptions::CommandLineOptions()
{
  auto urlHandler = [this](int & aPos, int argc, char * argv[]) {
    return ParseStringValue(mServerURL, aPos, argc, argv);
  };

  auto tokenHandler = [this](int & aPos, int argc, char * argv[]) {
    return ParseStringValue(mServerToken, aPos, argc, argv);
  };

  kOptionHandlers = { { "--server_url", urlHandler }, { "--server_token", tokenHandler } };
}

int CommandLineOptions::ParseCommandLine(int argc, char * argv[])
{
  for (int i = 0; i < argc; i++)
  {
    string commandLineOption(argv[i]);

    auto it =
      find_if(kOptionHandlers.begin(), kOptionHandlers.end(),
              [&commandLineOption](auto & aElem) { return (commandLineOption == aElem.first); });

    if (it != kOptionHandlers.end())
    {
      int ret = it->second(i, argc, argv);
      if (ret != 0)
        return ret;
    }
  }

  return 0;
}

bool CommandLineOptions::HasExpectedOptions() const
{
  if (mServerURL.empty() || mServerToken.empty())
    return false;

  return true;
}

const string & CommandLineOptions::GetServerURL() const
{
  return mServerURL;
}

const string & CommandLineOptions::GetServerToken() const
{
  return mServerToken;
}

//----------------------------------------------------------------
// Private members

int CommandLineOptions::ParseStringValue(string & aValueToSet, int & aPos, int argc, char * argv[])
{
  aPos++;
  if (aPos >= argc)
    return EINVAL;
  aValueToSet = argv[aPos];
  return 0;
}
