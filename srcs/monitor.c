/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:15:50 by sshimura          #+#    #+#             */
/*   Updated: 2024/09/27 23:30:29 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	assign_bool(t_table *table, bool *dst, bool src)
// {
// 	ft_mutex(&table->write, LOCK);
// 	*dst = src;
// 	ft_mutex(&table->write, UNLOCK);
// }

// void	assign_value(t_table *table, long *dst, long src)
// {
// 	ft_mutex(&table->write, LOCK);
// 	*dst = src;
// 	ft_mutex(&table->write, UNLOCK);
// }

static bool	check_starvation(long last_meal, t_philo *philos)
{
	long	now;

  ft_mutex(&philos->meal_monitor, LOCK);
	now = gettime_ms() - philos->table->start_time;
	ft_mutex(&philos->meal_monitor, UNLOCK);
  
  if (now - last_meal > philos->table->time_to_die)
	{
    // ft_mutex(&philos->meal_monitor, LOCK);
		print_state(gettime_ms(), philos->philo_id, "died", philos->table);
		// assign_bool(table, &table->philos->is_dead, true);
		ft_mutex(&philos->meal_monitor, LOCK);
		philos->table->is_end = true;
		ft_mutex(&philos->meal_monitor, UNLOCK);
    // ft_mutex(&philos->meal_monitor, UNLOCK);
		return (false);
	}
	return (true);
}

void	*monitor_philo_life(void *info)
{
	t_philo	*philos;
	long	last_meal;
	int		id;

	philos = (t_philo *)info;
	while (1)
	{
		id = 0;
		while (id < philos->table->philo_nbr)
		{
      ft_mutex(&philos->meal_monitor, LOCK);
			last_meal = philos[id].last_mealtime;
      ft_mutex(&philos->meal_monitor, UNLOCK); 
			if (!check_starvation(last_meal, &philos[id]))
			{
        // printf("is_dead => %d\n", table->philos[id].is_dead);
        // philos->table->is_end = true;
        // stop_simulation(philos);
        return (NULL);
				// exit(EXIT_SUCCESS);
			}
			id++;
      // precise_sleep(5);
		}
		precise_sleep(1);
	}
	return (NULL);
}