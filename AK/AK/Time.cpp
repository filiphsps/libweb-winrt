#include "pch.h"
#include "Time.h"

unsigned AK::day_of_week(int year, unsigned month, int day)
{
    VERIFY(month >= 1 && month <= 12);
    constexpr Array seek_table = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    if (month < 3)
        --year;

    return (year + year / 4 - year / 100 + year / 400 + seek_table[month - 1] + day) % 7;
}
