/**
 *
 *
 */

#ifndef _WIN32
#include <bcm2835.h>
#include <string.h>
#endif
#include "SignalHandler.h"

//------------------------------------------------------------------------------
// Public members

SignalHandler::SignalHandler()
{
  mSelf = this;
}

SignalHandler::~SignalHandler()
{
  ResetToDefault();
}

int SignalHandler::Init()
{
#ifdef _WIN32
  signal(SIGTERM, TermSignalHandler);
  signal(SIGINT, TermSignalHandler);
#else

  // Initialize the Raspberry Pi GPIO
  if (!bcm2835_init())
    return 1;

  struct sigaction action;
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_handler = TermSignalHandler;
  sigaction(SIGTERM, &action, NULL);
  sigaction(SIGINT, &action, NULL);
#endif

  return 0;
}

bool SignalHandler::IsDone() const
{
  return mDone;
}

//------------------------------------------------------------------------------
// Private members

/*static*/ SignalHandler * SignalHandler::mSelf = nullptr;

/*static*/ void SignalHandler::TermSignalHandler(int aSignum)
{
  if (mSelf)
    mSelf->mDone = 1;
}

void SignalHandler::ResetToDefault()
{
#ifdef _WIN32
  signal(SIGTERM, SIG_DFL);
  signal(SIGINT, SIG_DFL);
#else
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_handler = SIG_DFL;
  sigaction(SIGTERM, &action, NULL);
  sigaction(SIGINT, &action, NULL);
#endif
}
