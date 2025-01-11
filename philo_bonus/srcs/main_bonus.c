/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:32 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/11 17:24:25 by sshimura         ###   ########.fr       */
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
			return (clean(&table, "parse error", NULL));
		if (data_init(&table) == 1)
			return (clean(&table, "data init error", NULL));
		if (create_philos(&table) == 1)
			return (clean(&table, "create error", destroy_data));
		if (wait_all_philos(&table) == 1)
			return (clean(&table, "wait error", destroy_data));
		clean(&table, NULL, destroy_data);
	}
	else
		print_error(RED"Wrong input:\n"
			GREEN"example// ./philo_bonus 5 800 200 200 [5]"RESET);
	return (0);
}
