#include "philo.h"

static void	taking_forks(t_philo *philos)
{
  printf(GREEN"philo id is %d\nleft is %d, right is %d\n"RESET, philos->philo_id, philos->left_fork_id,
      philos->right_fork_id);
  if (philos->philo_id % 2 == 0)
  {
    // d("even: before mutex lock");
    // SEGV
    // precise_sleep(100);
    ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
    print_state(gettime_ms(), philos->philo_id, "has taken a fork(left)", philos->table);
    ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
    print_state(gettime_ms(), philos->philo_id, "has taken a fork(right)", philos->table);
  }
  else
  {
    // d("before mutex lock");
    ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
    print_state(gettime_ms(), philos->philo_id, "has taken a fork(right)", philos->table);
    ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
    print_state(gettime_ms(), philos->philo_id, "has taken a fork(left)", philos->table);
  }
}

static void	eating(t_philo *philos)
{
  taking_forks(philos);
  print_state(gettime_ms(), philos->philo_id, "is eating", philos->table);
	ft_mutex(&philos->monitor, LOCK);
  philos->last_mealtime = gettime_ms();
  ft_mutex(&philos->monitor, UNLOCK);
  precise_sleep(philos->table->time_to_eat);

  ft_mutex(&philos->table->forks[philos->left_fork_id], UNLOCK);
  ft_mutex(&philos->table->forks[philos->right_fork_id], UNLOCK);
}

static void thinking(t_philo *philos)
{
	print_state(gettime_ms(), philos->philo_id, "is thinking", philos->table);
}

static void sleeping(t_philo *philos)
{
  print_state(gettime_ms(), philos->philo_id, "is sleeping", philos->table);
  precise_sleep(philos->table->time_to_sleep); 
}

static void  *simulation(void *info)
{
  t_philo *philos;

  philos = (t_philo *)info;
  while (1)
  {
    eating(philos);
    // print_state(gettime_ms(), philos->philo_id, "is sleeping", philos->table);
    // precise_sleep(philos->table->time_to_sleep);
    sleeping(philos);
    thinking(philos);
    philo_died(philos->table);
  }
  return (NULL);
}

static void	create_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_create(&table->philos[i + 1].thread, NULL, simulation, &table->philos[i + 1]);
		i++;
	}
}

static void  join_threads(t_table *table)
{
  int i;

  i = 0;
  while (i < table->philo_nbr)
  {
    pthread_join(table->philos[i + 1].thread, NULL);
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
