#include "philo.h"

void  clean(t_table *table)
{
  // exit(1);
  // (void)tale;
  int i;

  i = 0;
  while (i < table->philo_nbr)
  {
    ft_mutex(&table->forks[i + 1], DESTROY);
    ft_mutex(&table->philos[i].dead_monitor, DESTROY);
    ft_mutex(&table->philos[i].meal_monitor, DESTROY);
  }
  ft_mutex(&table->write, DESTROY);
  // printf("Let s EXIT\n");
  // exit(0);
}