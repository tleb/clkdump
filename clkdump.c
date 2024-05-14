#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

struct clk_info {
	clockid_t id;
	const char *name;
	struct timespec previous;
};

#define CLK_INFO(x) { .id = x, .name = #x }

static struct clk_info clks[] = {
	CLK_INFO(CLOCK_REALTIME),
	CLK_INFO(CLOCK_REALTIME_ALARM),
	CLK_INFO(CLOCK_REALTIME_COARSE),
	CLK_INFO(CLOCK_TAI),
	CLK_INFO(CLOCK_MONOTONIC),
	CLK_INFO(CLOCK_MONOTONIC_COARSE),
	CLK_INFO(CLOCK_MONOTONIC_RAW),
	CLK_INFO(CLOCK_BOOTTIME),
	CLK_INFO(CLOCK_BOOTTIME_ALARM),
	CLK_INFO(CLOCK_PROCESS_CPUTIME_ID),
	CLK_INFO(CLOCK_THREAD_CPUTIME_ID),
};

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// https://stackoverflow.com/a/64454229/4255615
static void formatted_date(char *buf, size_t buf_len)
{
	time_t now = time(NULL);
	assert(now != ((time_t)-1));

	struct tm *tm = gmtime(&now);
	assert(tm != NULL);

	const char *days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
			"Aug", "Sep", "Oct", "Nov", "Dec"};

	int ret = snprintf(buf, buf_len, "%s, %d %s %d %02d:%02d:%02d GMT",
			days[tm->tm_wday], tm->tm_mday, months[tm->tm_mon],
			tm->tm_year + 1900, tm->tm_hour, tm->tm_min, tm->tm_sec);
	assert(ret > 0 && (size_t)ret < buf_len);
}

// Return time difference between a and b. Assume a <= b.
static double timespec_delta(struct timespec a, struct timespec b)
{
	assert(a.tv_sec <= b.tv_sec);
	assert(a.tv_sec < b.tv_sec || a.tv_nsec <= b.tv_nsec);

	time_t delta_secs = b.tv_sec - a.tv_sec;
	long long delta_nsecs = b.tv_nsec - a.tv_nsec;

	return (double)delta_secs + (double)delta_nsecs / 1e9;
}

int main(void)
{
	while (1) {
		char date_buf[512];

		formatted_date(date_buf, sizeof(date_buf));

		for (size_t i = 0; i < ARRAY_SIZE(clks); i++) {
			struct timespec tp;
			int ret;

			ret = clock_gettime(clks[i].id, &tp);
			if (ret) {
				fprintf(stderr, "clock_gettime(%s) failed: %s\n",
					clks[i].name, strerror(errno));
				continue;
			}

			double delta = timespec_delta(clks[i].previous, tp);
			clks[i].previous = tp;

			printf("%s\t%-25s\t%10ld s + %10ld ns\t%10f s\n",
				date_buf, clks[i].name, tp.tv_sec, tp.tv_nsec,
				delta);
		}

		fflush(stdout);
		fflush(stderr);
		sleep(1);
	}
}
