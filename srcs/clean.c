#include "philo.h"

void  clean(t_table *table)
{
  int i;

  i = 0;
  while (i < table->philo_nbr)
  {
    ft_mutex(&table->forks[i], DESTROY);
    ft_mutex(&table->philos[i].monitor, DESTROY);
  }
  ft_mutex(&table->write, DESTROY);
}