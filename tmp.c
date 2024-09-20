#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

#define BOLD_RED "\033[1;31m"
#define RESET "\033[0m"


long  gettime_ms(void)
{
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1e6 + tv.tv_usec); 
}

void  ft_usleep(long ms)
{
  long start = gettime_ms();
  while (gettime_ms() - start < ms)
    usleep(60);
}

void precise_sleep(long milisec)
{
    long start;
    long elapsed;
    long  rem;

    start = gettime_ms();
    while (gettime_ms() - start < milisec)
    {
      elapsed = gettime_ms() - start;
      rem = milisec - elapsed;
      if (rem > 1e3)
        usleep(milisec / 2);
      else
      {
        while (gettime_ms() - start < milisec)
        {;}
      }
    } 
}

int main() {
    struct timeval start;
    struct timeval end;
    long seconds;
    long microseconds;
    double elapsed;

    gettimeofday(&start, NULL);
    precise_sleep(500);
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - start.tv_sec;
    microseconds = end.tv_usec - start.tv_usec;
    elapsed = seconds + microseconds * 1e-6;

    printf("Expected sleep duration: "BOLD_RED"\t500"RESET" mili seconds\n");
    printf("Actual sleep duration: "BOLD_RED"\t\t%f"RESET" mili seconds\n\n", elapsed*1e3);
    printf("Loop sleep duration: "BOLD_RED"\t\t%f"RESET" mili seconds\n\n", elapsed*1e3);
}