/**
 *
 *
 */

#include <signal.h>

#ifndef _SIGNAL_HANDLER_H_
#define _SIGNAL_HANDLER_H_

class SignalHandler
{
public:
  SignalHandler();

  ~SignalHandler();

  int Init();

  bool IsDone() const;

private:
#ifndef _WIN32
  struct sigaction mAction;
#endif

  static SignalHandler * mSelf;

  volatile sig_atomic_t mDone = 0;

  void ResetToDefault();

  static void TermSignalHandler(int aSignum);
};

#endif  // _SIGNAL_HANDLER_H_
