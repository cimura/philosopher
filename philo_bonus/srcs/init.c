/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:23 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/17 20:01:44 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->meal_counter = 0;
	table->start_time = gettime_ms();
	table->sem_name = "/dsdadsdsadd";
	table->forks = sem_open(table->sem_name, O_CREAT, 0644, table->philo_nbr);
	if (table->forks == SEM_FAILED)
		return (1);
	while (i < table->philo_nbr)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid == -1)
			return (1);
		if (table->philos[i].pid == 0)
		{
			table->philos[i].table = table;
			table->philos[i].philo_id = i + 1;
			table->philos[i].last_mealtime = 0;
			simulation(table, &table->philos[i]);
		}
		else
			i++;
	}
	return (0);
}

// int	create_death_thread(t_table *table)
// {
// 	if (pthread_create(&table->death_thread, NULL,
// 			monitor_philo_life, &table->philos))
// 		return (1);
// 	return (0);
// }
