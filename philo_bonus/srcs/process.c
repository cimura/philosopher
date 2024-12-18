/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:13:24 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/18 17:22:53 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//static void	check_starvation(t_philo *philos, long long last_meal)
//{
//	long long	now;

//	now = gettime_ms() - philos->table->start_time;
//	if (now - last_meal > philos->table->time_to_die)
//	{
//		print_state(philos->philo_id, "died", philos->table);
//		exit(1);
//	}
//}


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
		eating(table, philos);
		if (is_full(philos))
			break ;
		sleeping(philos);
		thinking(philos);
	}
	exit(EXIT_SUCCESS);
}

int	wait_all_philos(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_join(table->death_detector, NULL))
		return (1);
	while (i < table->philo_nbr)
	{
		if (pthread_detach(table->meal_updater[i]))
			return (1);
		i++;
	}
	//while (i < table->philo_nbr)
	//{
	//	waitpid(-1, NULL, 0);
	//	i++;
	//}
	//printf("death wait\n");
	sem_wait(table->death);
	//printf("Lets kill\n");
	send_kill_signal(table);
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
// 	if (pthread_create(&table->death_detector, NULL,
// 			monitor_philo_life, &table->philos))
// 		return (1);
// 	return (0);
// }
