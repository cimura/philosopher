#include "philo.h"

void  clean(t_table *table)
{
  ft_mutex(&table->philos->left_fork.fork, DESTROY);
  ft_mutex(&table->philos->right_fork.fork, DESTROY);
  ft_mutex(&table->philos->monitor, DESTROY);
}