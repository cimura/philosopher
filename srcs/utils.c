#include "philo.h"

// for debug
void d(const char *msg)
{
  printf(GREEN"%s\n"RESET, msg);
}

long  gettime_ms(void)
{
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000 + tv.tv_usec / 1000); 
}

void precise_sleep(long milisec)
{
    long start;
    long elapsed;
    long  time_left;
    start = gettime_ms();
    while (gettime_ms() - start < milisec)
    {
      elapsed = gettime_ms() - start;
      time_left = milisec - elapsed;
      if (time_left * 2 < milisec)
        usleep(milisec / 4);
      else
      {
        while (gettime_ms() - start < milisec)
        {
          ;
        }
      }
    }
}

void	error_exit(const char *message)
{
  // pthread_mutex_t write;

	// ft_mutex(&write, LOCK);
  printf(RED"%s\n"RESET,message);
	// ft_mutex(&write, UNLOCK);
  exit(EXIT_FAILURE);
}

void print_state(long timestamp, int id, const char *state, t_table *table)
{
  // printf(RED"hello\n"RESET);
    // Ensure that the printing is thread-safe
    // d("1 hello");
    precise_sleep(1);
    if (is_dead(table->philos))
      return ;
    ft_mutex(&table->write, LOCK);
    printf("%ld %d %s\n", timestamp - table->start_time, id, state);
    // d("2 hello");
    ft_mutex(&table->write, UNLOCK);
}

// bool  philo_died(t_philo *philos)
// {
//   ft_mutex(&philos->dead_monitor, LOCK);
//   // printf("gettime - lastmeal => %lu\n", gettime_ms() - philos->last_mealtime);
//   // printf("philos->lastmeal => %lu\n", philos->last_mealtime);
//   // printf("gettime => %lu\n", philos->table->time_to_die);

//   if (gettime_ms() - philos->last_mealtime > philos->table->time_to_die)
//   {
//     print_state(gettime_ms(), philos->philo_id, "died", philos->table);
//     philos->is_dead = true;
//     ft_mutex(&philos->dead_monitor, UNLOCK);
//     return (true);
//   }
//   ft_mutex(&philos->dead_monitor, UNLOCK);
//   return (false);
// }