/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:13:24 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/11 17:25:36 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	lonely_philo(t_philo *philos)
{
	print_state(philos->philo_id,
		"has taken a fork", philos->table);
	precise_sleep(philos->table->time_to_eat);
	while (1)
		precise_sleep(philos->table->time_to_sleep);
}

static void	simulation(t_table *table, t_philo *philos)
{
	sem_wait(table->start);
	philos->table->start_time = gettime_ms();
	if (pthread_create(&philos->death_detector, NULL,
			monitor_philo_life, philos))
		exit(EXIT_FAILURE);
	if (table->philo_nbr == 1)
		lonely_philo(philos);
	if (philos->philo_id % 2 != 0)
		precise_sleep(table->time_to_eat);
	while (1)
	{
		eating(table, philos);
		if (philos->table->nbr_limit_meals > 0
			&& philos->_meal.meal_counter >= philos->table->nbr_limit_meals)
			exit(EXIT_SUCCESS);
		sleeping(philos);
		thinking(philos);
	}
}

static void	send_signal(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		kill(table->philos[i].pid, SIGTERM);
		i++;
	}
}

static void	*wait_death(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	sem_wait(table->death);
	send_signal(table);
	return (NULL);
}

int	create_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid == -1)
			return (1);
		if (table->philos[i].pid == 0)
			simulation(table, &table->philos[i]);
		else
			i++;
	}
	if (pthread_create(&table->death_waiter, NULL, wait_death, table))
		return (1);
	i = 0;
	while (i < table->philo_nbr)
	{
		sem_post(table->start);
		i++;
	}
	return (0);
}
