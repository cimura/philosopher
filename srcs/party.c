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
  print_state(gettime_ms(), table->philos->philo_id, "is eating", table);
	ft_mutex(&table->philos->monitor, LOCK);
  table->philos->last_mealtime = gettime_ms();
  precise_sleep(table->time_to_eat);
	ft_mutex(&table->philos->monitor, UNLOCK);
  ft_mutex(&table->philos->left_fork.fork, UNLOCK);
  ft_mutex(&table->philos->right_fork.fork, UNLOCK);
}

static void think(t_table *table)
{
	print_state(gettime_ms(), table->philos->philo_id, "is thinking", table);
}

static void  *simulation(void *info)
{
  t_table *table;

  table = (t_table *)info;
  while (1)
  {
  eat(table);
  think(table);
  precise_sleep(table->time_to_sleep);
  }
  return (NULL);
}

static void	create_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_create(&table->philos[i].philosopher, NULL, simulation, table);
		i++;
	}
}

static void  join_threads(t_table *table)
{
  int i;

  i = 0;
  while (i < table->philo_nbr)
  {
    pthread_join(table->philos[i].philosopher, NULL);
    i++;
  }
}

void	party(t_table *table)
{
  // printf("1pass\n");
  create_philo(table);
  // printf("2pass\n");
  join_threads(table);
  // printf("3pass\n");
}
