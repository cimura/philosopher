/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:15:50 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/18 17:22:46 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	check_starvation(t_philo *philos, long long last_meal)
{
	long long	elapsed;

	elapsed = gettime_ms() - philos->table->start_time;
	if (elapsed - last_meal > philos->table->time_to_die)
	{
		//sem_wait(philos->table->write_lock);
		print_state(philos->philo_id, "died", philos->table);
		philos->table->is_dead = true;
		sem_post(philos->table->death);
		//sem_post(philos->table->write_lock);
		return (false);
	}
	return (true);
}

void	*monitor_philo_life(void *arg)
{
	t_philo		*philos;
	int			id;

	philos = (t_philo *)arg;
	while (1)
	{
		id = 0;
		while (id < philos->table->philo_nbr)
		{
			//sem_wait(philos->table->write_lock);
			if (!check_starvation(&philos[id], philos->last_mealtime))
				return (NULL);
			//sem_post(philos->table->write_lock);
			id++;
		}
		precise_sleep(1);
	}
	return (NULL);
}

void	*update_meal_time(void *arg)
{
	t_philo	*philos;
	t_table	*table;

	philos = (t_philo *)arg;
	table = philos->table;
	while (1)
	{
		//printf("update mealtime\n");
		sem_wait(table->meal[philos->philo_id]);
		sem_wait(table->write_lock);
		if (!table->is_dead)
		{
			//printf("last meal: %lld\n", gettime_ms() - table->start_time);
			table->last_mealtime[philos->philo_id] = gettime_ms() - table->start_time;
		}
		sem_post(table->write_lock);
	}
	return (NULL);
}

void	send_kill_signal(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		kill(table->philos[i].pid, SIGKILL);
		i++;
	}
}

//bool	check_full(t_philo *philos)
//{
//	if (philos->table->nbr_limit_meals > 0
//		&& philos->table->meal_counter / philos->table->philo_nbr
//		>= philos->table->nbr_limit_meals)
//	{
//		return (true);
//	}
//	else
//		return (false);
//}

