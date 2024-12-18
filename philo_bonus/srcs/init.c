/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:23 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/19 00:57:10 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//void	*wait_death(void *arg)
//{
//	t_table	*table;

//	table = (t_table *)arg;
//	sem_wait(table->death);
//	send_kill_signal(table);
//	return (NULL);
//}

int	data_init(t_table *table)
{
	table->meal_counter = 0;
	table->start_time = gettime_ms();

	sem_unlink("/forks");
	table->sem_name = "/forks";
	table->forks = sem_open(table->sem_name, O_CREAT, 0644, table->philo_nbr);
	if (table->forks == SEM_FAILED)
		return (1);
	sem_unlink("/death");
	table->sem_name = "/death";
	table->death = sem_open(table->sem_name, O_CREAT, 0644, 0);
	if (table->death == SEM_FAILED)
		return (1);
	sem_unlink("/write_lock");
	table->sem_name = "/write_lock";
	table->write_lock = sem_open(table->sem_name, O_CREAT, 0644, 1);
	if (table->write_lock == SEM_FAILED)
		return (1);
	int	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1;
		table->philos[i].last_mealtime = 0;
		table->philos[i].pid = fork();
		if (table->philos[i].pid == -1)
			return (1);
		if (table->philos[i].pid == 0)
		{
			sem_unlink("/lastmeal");
			table->sem_name = "/lastmeal";
			table->philos->last_meal = sem_open(table->sem_name, O_CREAT, 0644, 1);
			if (table->philos->last_meal == SEM_FAILED)
				return (1);
			if (pthread_create(&table->philos[i].death_detector, NULL,
				monitor_philo_life, &table->philos[i]))
				return (1);
			simulation(table, &table->philos[i]);
		}
		else
			i++;
	}
	//if (pthread_create(&table->death_waiter, NULL, wait_death, table))
	//	return (1);
	return (0);
}


//int	create_death_waiter(t_table *table)
//{
//	//int	i;
//	//i = 0;
//	//while (i < table->philo_nbr)
//	//{
//	//	if (pthread_create(&table->meal_updater[i], NULL,
//	//			update_meal_time, &table->philos[i]))
//	//		return (1);
//	//	i++;
//	//}
//	if (pthread_create(&table->death_waiter, NULL,
//			wait_death, table->philos))
//		return (1);
//	return (0);
//}
