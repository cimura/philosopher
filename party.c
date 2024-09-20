#include "philo.h"

static void	take_fork(t_table *table)
{
  if (table->philos->philo_id % 2 == 0)
  {
    ft_mutex(&table->philos->left_fork.fork, LOCK);
    print_state(gettime_ms(), table->philos->philo_id, "has taken a fork(left)", table);
    ft_mutex(&table->philos->right_fork.fork, LOCK);
    print_state(gettime_ms(), table->philos->philo_id, "has taken a fork(right)", table);
  }
  else
  {
    ft_mutex(&table->philos->right_fork.fork, LOCK);
    print_state(gettime_ms(), table->philos->philo_id, "has taken a fork(right)", table);
    ft_mutex(&table->philos->left_fork.fork, LOCK);
    print_state(gettime_ms(), table->philos->philo_id, "has taken a fork(left)", table);
  }
}

static void	eat(t_table *table)
{
  take_fork(table);
	ft_mutex(&table->philos->monitor, LOCK);
  print_state(gettime_ms(), table->philos->philo_id, "is eating", table);
  table->philos->last_mealtime = gettime_ms();
	ft_mutex(&table->philos->monitor, UNLOCK);
}

static void think(t_table *table)
{
	print_state(gettime_ms(), table->philos->philo_id, "is thinking", table);
}

static void  *simulation(void *info)
{
  t_table *table;

  table = (t_table *)info;
  eat(table);
  precise_sleep();
  think(table);
  return (NULL);
}

static void	born_philo(t_table table)
{
	int	i;

	i = 0;
	while (i < table.philo_nbr)
	{
		pthread_create(&table.philos[i].philosopher, NULL, simulation, &table);
		i++;
	}

}

void	party(t_table table)
{
  born_philo(table);
}
