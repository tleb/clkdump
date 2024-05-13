# clkdump

 - **Goal?** Dump `clock_gettime(2)` output each second.
 - **Why?** Debug clock status across kernel suspend.
 - **What?** Print to stdout every second the current datetime, the
   output of `clock_gettime()` and the delta with the previous output.
   This is done for every clock type.

Example usage below.

 - First column is `gmtime(time(NULL))` formatted output.
 - Second column is clock name.
 - Third column is clock value (`struct timespec` has seconds and
   nanoseconds).
 - Fourth column is delta with previous value of the same clock.

```
./clkdump | grep -e 'MONOTONIC\s' -e 'TAI'
Sat, 1 Jan 2000 00:35:10 GMT    CLOCK_TAI          946686910 s + 738663970 ns     1.000084 s
Sat, 1 Jan 2000 00:35:10 GMT    CLOCK_MONOTONIC         1908 s + 984282665 ns     1.000084 s
Sat, 1 Jan 2000 00:35:11 GMT    CLOCK_TAI          946686911 s + 738747045 ns     1.000083 s
Sat, 1 Jan 2000 00:35:11 GMT    CLOCK_MONOTONIC         1909 s + 984365775 ns     1.000083 s
Sat, 1 Jan 2000 00:35:12 GMT    CLOCK_TAI          946686912 s + 738827060 ns     1.000080 s
Sat, 1 Jan 2000 00:35:12 GMT    CLOCK_MONOTONIC         1910 s + 984445785 ns     1.000080 s
Sat, 1 Jan 2000 00:35:55 GMT    CLOCK_TAI          946686955 s + 834063590 ns    43.095237 s
Sat, 1 Jan 2000 00:35:55 GMT    CLOCK_MONOTONIC         1954 s +  79683035 ns    43.095237 s
Sat, 1 Jan 2000 00:35:56 GMT    CLOCK_TAI          946686956 s + 834202020 ns     1.000138 s
Sat, 1 Jan 2000 00:35:56 GMT    CLOCK_MONOTONIC         1955 s +  79820815 ns     1.000138 s
Sat, 1 Jan 2000 00:35:57 GMT    CLOCK_TAI          946686957 s + 834299360 ns     1.000097 s
Sat, 1 Jan 2000 00:35:57 GMT    CLOCK_MONOTONIC         1956 s +  79918115 ns     1.000097 s
Sat, 1 Jan 2000 00:35:58 GMT    CLOCK_TAI          946686958 s + 834427260 ns     1.000128 s
Sat, 1 Jan 2000 00:35:58 GMT    CLOCK_MONOTONIC         1957 s +  80046225 ns     1.000128 s
```
