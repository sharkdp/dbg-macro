#include <string>
#include <cstring>
#include <iostream>
#include <time.h>
#include "dbg.h"

#define SECS_TO_RUN 3

int main(int argc, char** argv) {
  bool use_dbg = (argc > 1 && !strcmp(argv[1], "on"));
  time_t start = time(NULL);

  int i = 0;
  while (1) {
    if (++i % 10000000 == 0) { // amortize cost of time() call
      time_t curtime = time(NULL);
      if (curtime - start >= SECS_TO_RUN) {
	std::cout << i << " iterations in " << SECS_TO_RUN << " secs = " << (i/((float)SECS_TO_RUN)) << " iters/sec (compiled-out)." << std::endl;
	break;
      }
    }
  }

  while (1) {
    // unroll 10x to dominate the looping costs
    if (use_dbg) dbg("some reasonable sized message... that nobody will ever see!");
    if (use_dbg) dbg("some reasonable sized message... that nobody will ever see!");
    if (use_dbg) dbg("some reasonable sized message... that nobody will ever see!");
    if (use_dbg) dbg("some reasonable sized message... that nobody will ever see!");
    if (use_dbg) dbg("some reasonable sized message... that nobody will ever see!");
    if (use_dbg) dbg("some reasonable sized message... that nobody will ever see!");
    if (use_dbg) dbg("some reasonable sized message... that nobody will ever see!");
    if (use_dbg) dbg("some reasonable sized message... that nobody will ever see!");
    if (use_dbg) dbg("some reasonable sized message... that nobody will ever see!");
    if (use_dbg) dbg("some reasonable sized message... that nobody will ever see!");
    if (++i % 10000000 == 0) { // amortize cost of time() call
      time_t curtime = time(NULL);
      if (curtime - start >= SECS_TO_RUN) {
	std::cout << i << " iterations in " << SECS_TO_RUN << " secs = " << (i/((float)SECS_TO_RUN)) << " iters/sec (dynamically disabled)." << std::endl;
	break;
      }
    }
  }
}
