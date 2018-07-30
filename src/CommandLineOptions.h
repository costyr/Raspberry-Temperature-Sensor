/**
 * 
 * 
 */

#ifndef _COMMANDLINE_OPTIONS_H_
#define _COMMANDLINE_OPTIONS_H_

#include <string>
#include <vector>
#include <utility>
#include <functional>

class CommandLineOptions 
{
public:
  CommandLineOptions();

  int ParseCommandLine(int argc, char *argv[]);

  const string & GetServerURL() const;

  const string & GetServerToken() const;
 
private:
  vector<pair<string, std::function<void(int &)>>> kOptionHandlers;

  string mServerURL;
  string mServerToken;
};

#endif // _COMMANDLINE_OPTIONS_H_