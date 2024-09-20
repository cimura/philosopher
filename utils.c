#include "philo.h"

long  gettime_ms(void)
{
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000 + tv.tv_usec / 1000); 
}

void  precise_sleep(long milisec, t_table *table)
{
  long  start;

  start = gettime_ms();
  while (gettime_ms() - start < milisec)
    usleep(60);
}

void	error_exit(const char *message)
{
	printf(RED"%s\n"RESET,message);
	exit(EXIT_FAILURE);
}

void print_state(long timestamp, int id, const char *state, t_table *table)
{
    // Ensure that the printing is thread-safe
    // pthread_mutex_lock(&meal_check); // Reusing the meal_check mutex for simplicity
    printf("%ld %d %s\n", timestamp - table->start_time, id, state);
    // pthread_mutex_unlock(&meal_check);
}