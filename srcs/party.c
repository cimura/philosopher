#include "philo.h"

static void	taking_forks(t_philo *philos)
{
  // ft_mutex(&philos->meal_monitor, LOCK);
  if (is_dead(philos))
    return ;
  if (philos->philo_id % 2 == 0)
  {
    ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
    print_state(gettime_ms(), philos->philo_id, "has taken a fork", philos->table);
    ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
    print_state(gettime_ms(), philos->philo_id, "has taken a fork", philos->table);
  }
  else
  {
    // precise_sleep(philos->table->time_to_eat);
    ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
    print_state(gettime_ms(), philos->philo_id, "has taken a fork", philos->table);
    ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
    print_state(gettime_ms(), philos->philo_id, "has taken a fork", philos->table);
  }
  // ft_mutex(&philos->meal_monitor, UNLOCK);
}

static void	eating(t_philo *philos)
{
  if (philos->table->nbr_limit_meals * philos->table->philo_nbr
       == philos->table->meal_counter)
    exit(EXIT_SUCCESS);
  taking_forks(philos);
  print_state(gettime_ms(), philos->philo_id, "is eating", philos->table);
  precise_sleep(philos->table->time_to_eat);
  philos->table->meal_counter++;
	ft_mutex(&philos->meal_monitor, LOCK);
  philos->last_mealtime = gettime_ms() - philos->table->start_time;
  ft_mutex(&philos->meal_monitor, UNLOCK);

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
  precise_sleep(philos->table->time_to_sleep);
}

bool is_dead(t_philo *philos)
{
  bool  dead;

  ft_mutex(&philos->dead_monitor, LOCK);
  dead = philos->table->is_end;
  ft_mutex(&philos->dead_monitor, UNLOCK);
  return (dead);
}

void stop_simulation(t_philo *philos)
{
  ft_mutex(&philos->dead_monitor, LOCK);
  philos->table->is_end = true;
  ft_mutex(&philos->dead_monitor, UNLOCK);
  exit(EXIT_FAILURE);
}

static void  *simulation(void *info)
{
  t_philo *philos;

  philos = (t_philo *)info;
  // while (1)
  // {
    while (!is_dead(philos))
    {
      // printf("in simulatin... is_dead-->> %d\n", philos->table->is_end);
      // precise_sleep(1);
      // if (philos->philo_id % 2 != 0)
      //   precise_sleep(philos->table->time_to_eat);
      eating(philos);
      if (is_dead(philos)) break ;
      sleeping(philos);
      if (is_dead(philos)) break ;
      thinking(philos);
      // philo_died(philos);
    }
  // }
  // stop_simulation(philos);
  // printf("Out of simulation\n");
  return (NULL);
}

static bool	create_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philos[i].thread, NULL, simulation, &table->philos[i]))
      return (false);
		i++;
	}
  if (pthread_create(&table->death_thread, NULL, monitor_philo_life, &table->philos))
  {
    printf("create death monitor NULL\n");
    return (false);
  }
  return (true);
}

static bool  join_threads(t_table *table)
{
  int i;

  i = 0;
  if (pthread_join(table->death_thread, NULL))
  {
    printf("death monitor NULL\n");
    return (false);
  }
  while (i < table->philo_nbr)
  {
    if (pthread_join(table->philos[i].thread, NULL))
      return (false);
    i++;
  }
  return (true);
}

void	party(t_table *table)
{
  // printf("philo nbr => %d\n", table->philo_nbr);
  if (!create_philos(table))
  {
    stop_simulation(table->philos);
    printf("return from create_philos\n");
    return ;
  }
  if (!join_threads(table))
  {
   
    printf("return from join\n");
    return ;
  }
}
