/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:32 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/28 16:23:36 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	wait_all_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (waitpid(table->philos[i].pid, NULL, 0) == -1)
			return (1);
		i++;
	}
	sem_post(table->death);
	pthread_join(table->death_waiter, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (5 == argc || 6 == argc)
	{
		if (parse_input(&table, argv) == PARSE_ERR)
			return (1);
		if (data_init(&table) == 1)
			return (1);
		if (create_philos(&table) == 1)
			return (clean(&table), 1);
		if (wait_all_philos(&table) == 1)
			return (clean(&table), 1);
		clean(&table);
	}
	else
		print_error("Wrong input:\n"
			GREEN"example// ./philo 5 800 200 200 [5]"RESET);
	return (0);
}
