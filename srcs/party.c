#include "philo.h"

static void	take_fork(t_philo *philos)
{
  // printf("philo id is %d\nleft is %d, right is %d\n", philos->philo_id, philos->left_fork_id,
  //     philos->right_fork_id);
  if (philos->philo_id % 2 == 0)
  {
    d("even: before mutex lock");
    ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
    d("after mutex lock");

    print_state(gettime_ms(), philos->philo_id, "has taken a fork(left)", philos->table);
    ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
    print_state(gettime_ms(), philos->philo_id, "has taken a fork(right)", philos->table);
  }
  else
  {
    d("before mutex lock");
    ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
    print_state(gettime_ms(), philos->philo_id, "has taken a fork(right)", philos->table);
    ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
    print_state(gettime_ms(), philos->philo_id, "has taken a fork(left)", philos->table);
  }
}

static void	eat(t_philo *philos)
{
	ft_mutex(&philos->monitor, LOCK);
  take_fork(philos);
  print_state(gettime_ms(), philos->philo_id, "is eating", philos->table);
  philos->last_mealtime = gettime_ms();
  precise_sleep(philos->table->time_to_eat);

  ft_mutex(&philos->table->forks[philos->left_fork_id], UNLOCK);
  ft_mutex(&philos->table->forks[philos->right_fork_id], UNLOCK);

  ft_mutex(&philos->monitor, UNLOCK);
}

static void think(t_philo *philo)
{
	print_state(gettime_ms(), philo->philo_id, "is thinking", philo->table);
}

static void  *simulation(void *info)
{
  t_philo *philos;

  philos = (t_philo *)info;
  while (1)
  {
    eat(philos);
    think(philos);
    precise_sleep(philos->table->time_to_sleep);
    philo_died(philos->table);
  }
  return (NULL);
}

static void	create_philo(t_table *table)
{
	int	i;

	i = 1;
	while (i < table->philo_nbr)
	{
		pthread_create(&table->philos[i].thread, NULL, simulation, &table->philos[i]);
		i++;
	}
}

static void  join_threads(t_table *table)
{
  int i;

  i = 1;
  while (i < table->philo_nbr)
  {
    pthread_join(table->philos[i].thread, NULL);
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
