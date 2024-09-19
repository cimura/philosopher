#include <sys/time.h>
#include <stdio.h>

int main() {
	struct timeval time;
	gettimeofday(&time, NULL);
	printf("time is %lu\n", time.tv_sec);
}
