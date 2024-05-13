# clkdump

 * **Goal?** Dump clock_gettime(2) output each second.
 * **Why?** Debug clock status across suspend.
 * **What?** Print to stdout every second the current datetime, the
   output of `clock_gettime()` and the delta with the previous output.
   This is done for every clock type.
