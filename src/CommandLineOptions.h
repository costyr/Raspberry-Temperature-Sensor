/**
 * 
 * 
 */

#ifndef _COMMANDLINE_OPTIONS_H_
#define _COMMANDLINE_OPTIONS_H_

#include "Common.h"

class CommandLineOptions 
{
public:
  CommandLineOptions();

  int ParseCommandLine(int argc, char *argv[]);

  const string & GetServerURL() const;

  const string & GetServerToken() const;
 
private:
  vector<pair<string, function<int(int &, int, char * [])>>> kOptionHandlers;

  string mServerURL;
  string mServerToken;
};

#endif // _COMMANDLINE_OPTIONS_H_
