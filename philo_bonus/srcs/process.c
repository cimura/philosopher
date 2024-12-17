/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:13:24 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/17 22:55:56 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	check_starvation(t_philo *philos, long long last_meal)
{
	long long	now;

	now = gettime_ms() - philos->table->start_time;
	printf("[%d] last meal: %lld\n", philos->philo_id, last_meal);
	if (now - last_meal > philos->table->time_to_die)
	{
		print_state(philos->philo_id, "died", philos->table);
		exit(1);
	}
}


static bool is_full(t_philo *philos)
{
	if (philos->table->nbr_limit_meals > 0
			&& philos->table->meal_counter / philos->table->philo_nbr
			>= philos->table->nbr_limit_meals)
	{
		return (true);
	}
	else
		return (false);
}


static void	lonely_philo(t_philo *philos)
{
	print_state(philos->philo_id,
		"has taken a fork", philos->table);
	precise_sleep(philos->table->time_to_eat);
	while (1)
	{
		check_starvation(philos, philos->last_mealtime);
		precise_sleep(philos->table->time_to_sleep);
	}
}

void	simulation(t_table *table, t_philo *philos)
{
	if (table->philo_nbr == 1)
		lonely_philo(philos);
	if (philos->philo_id % 2 == 0)
		precise_sleep(table->time_to_eat);
	while (1)
	{
		check_starvation(philos, philos->last_mealtime);
		eating(table, philos);
		 check_starvation(philos, philos->last_mealtime);
		if (is_full(philos))
			break ;
		 check_starvation(philos, philos->last_mealtime);
		sleeping(philos);
		 check_starvation(philos, philos->last_mealtime);
		thinking(philos);
	}
	exit(EXIT_SUCCESS);
}

int	wait_all_philos(t_table *table)
{
	int	i;
	int	status;

	i = 0;
	while (i < table->philo_nbr)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			printf("philo died....");
			int	j = 0;
			while (j < table->philo_nbr)
			{
				kill(table->philos[j].pid, SIGKILL);
				j++;
			}
			printf("Finished child process");
			break ;
		}
		i++;
	}
	return (0);
}

// int	create_philos(t_table *table)
// {
// 	int	i;

// 	i = 0;
// 	while (i < table->philo_nbr)
// 	{
// 		if (pthread_create(&table->philos[i].thread, NULL,
// 				simulation, &table->philos[i]))
// 			return (1);
// 		i++;
// 	}
// 	if (pthread_create(&table->death_thread, NULL,
// 			monitor_philo_life, &table->philos))
// 		return (1);
// 	return (0);
// }
