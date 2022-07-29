#pragma once

#include <time.h>

struct timeval
{
    __time64_t tv_sec;	/* Seconds.  */
    long tv_usec;	    /* Microseconds.  */
};
struct timespec
{
    __time64_t tv_sec;	/* Seconds.  */
    long int tv_nsec;   /* Nanoseconds.  */
};

int gettimeofday(struct timeval* tv, struct timezone* tz) {
    return 0;
}