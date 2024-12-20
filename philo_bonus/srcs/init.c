/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:23 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/20 17:43:14 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*wait_death(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	sem_wait(table->death);
	send_kill_signal(table);
	return (NULL);
}

int	data_init(t_table *table)
{
	sem_unlink("/forks");
	sem_unlink("/death");
	sem_unlink("/write_lock");

	table->meal_counter = 0;
	//table->is_end = false;
	table->forks = sem_open("/forks", O_CREAT, 0644, table->philo_nbr);
	if (table->forks == SEM_FAILED)
		return (1);
	table->death = sem_open("/death", O_CREAT, 0644, 0);
	if (table->death == SEM_FAILED)
		return (1);
	table->write_lock = sem_open("write_lock", O_CREAT, 0644, 1);
	if (table->write_lock == SEM_FAILED)
		return (1);
	table->start_time = gettime_ms();
	int	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1;
		table->philos[i].last_mealtime = 0;
		char	*uniq_id = ft_itoa(table->philos[i].philo_id);
		char	*name = ft_strjoin("/sem_meal", uniq_id);
		//printf("name: %s\n", name);
		sem_unlink(name);
		table->philos[i].meal_lock = sem_open(name, O_CREAT, 0644, 1);
		if (table->philos[i].meal_lock == SEM_FAILED)
			return (1);
		//sem_unlink(name);
		free(name);
		free(uniq_id);
		i++;
	}
	// create philo process
	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid == -1)
			return (1);
		if (table->philos[i].pid == 0)
		{
			if (pthread_create(&table->philos[i].death_detector, NULL,
				monitor_philo_life, &table->philos[i]))
				return (1);
			simulation(table, &table->philos[i]);
			pthread_join(table->philos[i].death_detector, NULL);
		}
		else
			i++;
	}
	if (pthread_create(&table->death_waiter, NULL, wait_death, table))
		return (1);
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
