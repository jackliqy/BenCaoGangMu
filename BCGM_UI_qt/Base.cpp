/**
  \file Base.cpp

  \author Jack Li
*/

#include "Base.h"

#include <iostream>

#ifdef _WIN32
//#include <winsock2.h>
#include <io.h>
#endif

using namespace std;


void mssleep(int t_ms, bool verbose)
{
    cout.flags(ios::dec);
    if (verbose) {
        cout << "Wait " << t_ms << "ms...";
        cout.flush();
    }
#ifdef _WIN32
    Sleep(t_ms);
#else
    usleep(t_ms * 1000);
#endif
    if (verbose)
        cout << " done." << endl;
}

