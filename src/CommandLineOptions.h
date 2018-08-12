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

  int ParseCommandLine(int argc, char * argv[]);

  bool HasExpectedOptions() const;

  const string & GetServerURL() const;

  const string & GetServerToken() const;

  const string & GetRoomId() const;

private:
  vector<pair<string, function<int(int &, int, char * [])>>> kOptionHandlers;

  string mServerURL;
  string mServerToken;
  string mRoomId;

  int ParseStringValue(string & aValueToSet, int & aPos, int argc, char * argv[]);
};

#endif  // _COMMANDLINE_OPTIONS_H_
