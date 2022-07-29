#pragma once

#include <time.h>

#undef timeval
struct timeval
{
    __time64_t tv_sec;	/* Seconds.  */
    long tv_usec;	    /* Microseconds.  */
};

#undef timespec
struct timespec
{
    __time64_t tv_sec;	/* Seconds.  */
    long int tv_nsec;   /* Nanoseconds.  */
};

int gettimeofday(struct timeval* tv, struct timezone* tz) {
    return 0;
}