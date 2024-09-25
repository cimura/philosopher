#include "philo.h"

static void	taking_forks(t_philo *philos)
{
  ft_mutex(&philos->meal_monitor, LOCK);

  if (philos->philo_id % 2 == 0)
  {
    ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
    print_state(gettime_ms(), philos->philo_id, "has taken a fork", philos->table);
    ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
    print_state(gettime_ms(), philos->philo_id, "has taken a fork", philos->table);
  }
  else
  {
    precise_sleep(1);
    ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
    print_state(gettime_ms(), philos->philo_id, "has taken a fork", philos->table);
    ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
    print_state(gettime_ms(), philos->philo_id, "has taken a fork", philos->table);
  }
  ft_mutex(&philos->meal_monitor, UNLOCK);
}

static void	eating(t_philo *philos)
{
  taking_forks(philos);
	ft_mutex(&philos->meal_monitor, LOCK);
  print_state(gettime_ms(), philos->philo_id, "is eating", philos->table);
  philos->table->meal_counter++;
  if (philos->table->nbr_limit_meals * philos->table->philo_nbr
       == philos->table->meal_counter)
    exit(EXIT_SUCCESS);
  ft_mutex(&philos->meal_monitor, UNLOCK);
  philos->last_mealtime = gettime_ms() - philos->table->start_time;
  precise_sleep(philos->table->time_to_eat);

  if (philos->philo_id % 2 == 0)
   {
    ft_mutex(&philos->table->forks[philos->left_fork_id], UNLOCK);
    ft_mutex(&philos->table->forks[philos->right_fork_id], UNLOCK);
   }
  else
   {
  	ft_mutex(&philos->table->forks[philos->right_fork_id], UNLOCK);
    ft_mutex(&philos->table->forks[philos->left_fork_id], UNLOCK);
   }
}

static void thinking(t_philo *philos)
{
	print_state(gettime_ms(), philos->philo_id, "is thinking", philos->table);
}

static void sleeping(t_philo *philos)
{
  print_state(gettime_ms(), philos->philo_id, "is sleeping", philos->table);
  // printf("sleeping time => %lu", philos->table->time_to_sleep);
  precise_sleep(philos->table->time_to_sleep);
}

static void  *simulation(void *info)
{
  t_philo *philos;

  philos = (t_philo *)info;
  while (1)
  {
    // while (!philo_died(philos))
    // {
      precise_sleep(1);
      eating(philos);
      sleeping(philos);
      thinking(philos);
      // philo_died(philos);
    // }
  }
  return (NULL);
}

static bool	create_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philos[i].thread, NULL, simulation, &table->philos[i]))
      return (false);
		i++;
	}
  if (pthread_create(&table->death_thread, NULL, monitor_philo_life, table))
    return (false);
  else
    return (true);
}

static bool  join_threads(t_table *table)
{
  int i;

  i = 0;
  while (i < table->philo_nbr)
  {
    if (pthread_join(table->philos[i].thread, NULL))
      return (false);
    i++;
  }
  if (pthread_join(table->death_thread, NULL))
    return (false);
  else
    return (true);
}

void	party(t_table *table)
{
  if (!create_philo(table))
    return ;
  if (!join_threads(table))
    return ;
}
